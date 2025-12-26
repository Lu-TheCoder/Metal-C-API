//
//  main.c
//  Metal C
//
//  Created by Lungile Maseko on 2024/04/27.
//

#include <stdio.h>
#include "Metal/Metal.h"
#include "Platform/platform.h"
#include "Metal/MTFoundation/Foundation.h"
#include "shaders/shaderInterface.h"
#include <dispatch/semaphore.h>
#include <mach/mach_time.h>
#include <simd/simd.h>
#include "loaders/obj_loader.h"
#include "Math/GMath.h"

#define STB_IMAGE_IMPLEMENTATION
#include "vendors/stb_image.h"

void* load_raw_texture_data(const char* path, size_t* out_size) {
    FILE* file = fopen(path, "rb");
    if (!file) return NULL;

    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    rewind(file);

    void* data = malloc(size);
    if (!data) {
        fclose(file);
        return NULL;
    }

    fread(data, 1, size, file);
    fclose(file);

    *out_size = size;
    return data;
}

void save_texture_as_gpu_ready_bin(const char* pngPath, const char* outPath) {
    int width, height, channels;
    unsigned char* pixels = stbi_load(pngPath, &width, &height, &channels, 4);
    if (!pixels) {
        fprintf(stderr, "Failed to load image: %s\n", pngPath);
        return;
    }

    FILE* f = fopen(outPath, "wb");
    if (!f) {
        fprintf(stderr, "Failed to open output file: %s\n", outPath);
        stbi_image_free(pixels);
        return;
    }

    size_t imageSize = width * height * 4;
    fwrite(pixels, 1, imageSize, f);

    fclose(f);
    stbi_image_free(pixels);
}

void my_callback(void *userdata, MTLibrary lib, MTError *err) {
    const char *name = userdata;
    if (err) {
        printf("callback Failed to load library %s\n", mt_error_get_localized_description(err));
    } else {
        printf("callback successfully loaded library %s\n", name);
    }
    
}


void print_mt_resource_options(MTResourceOptions options) {
    // CPU Cache Mode (bits 0-3)
    unsigned long cpuCacheMode = options & 0xF; // mask lower 4 bits for CPU cache mode
    if (cpuCacheMode == MTResourceCPUCacheModeDefaultCache) {
        printf("CPU Cache Mode: Default Cache\n");
    } else if (cpuCacheMode == MTResourceCPUCacheModeWriteCombined) {
        printf("CPU Cache Mode: Write Combined\n");
    } else {
        printf("CPU Cache Mode: Unknown (%lu)\n", cpuCacheMode);
    }

    // Storage Mode (bits 4-7)
    unsigned long storageMode = options & 0xF0; // mask bits 4-7
    switch (storageMode) {
        case MTResourceStorageModeShared:
            printf("Storage Mode: Shared\n");
            break;
        case MTResourceStorageModeManaged:
            printf("Storage Mode: Managed\n");
            break;
        case MTResourceStorageModePrivate:
            printf("Storage Mode: Private\n");
            break;
        case MTResourceStorageModeMemoryless:
            printf("Storage Mode: Memoryless\n");
            break;
        default:
            printf("Storage Mode: Unknown (%lu)\n", storageMode);
            break;
    }

    // Hazard Tracking Mode (bits 8-11)
    unsigned long hazardTrackingMode = options & 0xF00; // mask bits 8-11
    switch (hazardTrackingMode) {
        case MTResourceHazardTrackingModeDefault:
            printf("Hazard Tracking Mode: Default\n");
            break;
        case MTResourceHazardTrackingModeUntracked:
            printf("Hazard Tracking Mode: Untracked\n");
            break;
        case MTResourceHazardTrackingModeTracked:
            printf("Hazard Tracking Mode: Tracked\n");
            break;
        default:
            printf("Hazard Tracking Mode: Unknown (%lu)\n", hazardTrackingMode);
            break;
    }
}

//#include <sys/sysctl.h>
double osxGetCurrentTimeInSeconds(mach_timebase_info_data_t tb)
{
    uint64_t timeInNanoSecs =  mach_absolute_time() * tb.numer / tb.denom;
    return (double)timeInNanoSecs * 1.0E-9;
}

int main(int argc, const char * argv[]) {
    
//    Mesh cube;
//    parse_obj("./my_cube.obj", &cube);
//    
//    printf("Mesh Vertex Count: %zu\n", cube.vertex_count);
//    printf("Mesh Index Count: %zu\n", cube.index_count);
//    
    Mesh mesh;
    load_obj("my_hammer2.obj", &mesh);

    printf("Vertex count: %zu \n", mesh.vertex_count);
    printf("Index count: %zu \n", mesh.index_count);
        
    platform_system_config config = {
        .application_name = "Engine",
        .width = 1024,
        .height = 768,
        .flags = 0
    };
    
    if(!platform_system_startup(&config)){
        printf("Failed to startup platform.\n");
    }
    
    MTDevice device = mt_create_system_default_device();
    
    MTCommandQueue queue = mt_device_create_command_queue(device);
    
    bool isRunning = true;
    
    MTURL fileURL = mt_bundle_url_for_resource_(mt_string_from_utf8("default"), mt_string_from_utf8("metallib"));
    MTURL gizmo_shaderURL = mt_bundle_url_for_resource_(mt_string_from_utf8("gizmo_shader"), mt_string_from_utf8("metallib"));

    MTError* error = NULL;
    
    MTLibrary library = mt_device_create_library_withURL(device, fileURL, &error);
    MTLibrary gizmo_library = mt_device_create_library_withURL(device, gizmo_shaderURL, &error);
    mt_release(fileURL);

    MTString src = mt_string_from_utf8("kernel void test(device float *a [[ buffer(0) ]]) { a[0] = 42.0; }");
    MTCompileOptions copts = mt_compile_options_new();
    mt_device_create_library_with_source_async(device, src, copts, my_callback, "My Custom source shader");
    mt_nsstring_release(src);
    mt_release(copts);

    if(!library){
        printf("Failed to load library. Error %s\n", mt_error_get_localized_description(error));
    }
    
    if(!gizmo_library){
        printf("Failed to load gizmo library. Error %s\n", mt_error_get_localized_description(error));
    }
    
    MTFunction vertFunction = mt_library_create_function(library, mt_string_from_utf8("vert"));
    MTFunction fragFunction = mt_library_create_function(library, mt_string_from_utf8("frag"));
    
    MTFunction gizmo_vertFunction = mt_library_create_function(gizmo_library, mt_string_from_utf8("gizmo_vertex"));
    MTFunction gizmo_fragFunction = mt_library_create_function(gizmo_library, mt_string_from_utf8("gizmo_fragment"));
    
    
    MTIOCommandQueueDescriptor ioc_d = mt_io_command_queue_descriptor_create();
    mt_io_command_queue_descriptor_set_type(ioc_d, MTIOCommandQueueTypeConcurrent);
    
    MTIOCommandQueue io_cmq = mt_device_new_io_command_queue(device, ioc_d, &error);
    
    MTIOCommandBuffer io_cmb = mt_io_command_queue_command_buffer(io_cmq);
    
    assert(vertFunction);
    assert(fragFunction);
    
    assert(gizmo_vertFunction);
    assert(gizmo_fragFunction);
    
    mt_release(library);
    mt_release(gizmo_library);
    

    int vertCountX, vertCountY, vertCountZ;
    
    vector_float4 red   = COLOR(180, 0, 0, 200);
    vector_float4 green = COLOR(0, 180, 0, 200);
    vector_float4 blue  = COLOR(0, 0, 180, 200);
    
    vector_float4 red_   = COLOR(180, 0, 0, 100);
    vector_float4 green_ = COLOR(0, 180, 0, 100);
    vector_float4 blue_  = COLOR(0, 0, 180, 100);

    GizmoVertex* cylinderX = generate_cylinder_strip((vector_float3){0, 0, 0}, (vector_float3){1, 0, 0}, red, &vertCountX);
    GizmoVertex* cylinderY = generate_cylinder_strip((vector_float3){0, 0, 0}, (vector_float3){0, 1, 0}, green, &vertCountY);
    GizmoVertex* cylinderZ = generate_cylinder_strip((vector_float3){0, 0, 0}, (vector_float3){0, 0, 1}, blue, &vertCountZ);
    
    int coneCountX, coneCountY, coneCountZ;

    GizmoVertex* coneX = generate_cone_triangles(
        (vector_float3){1, 0, 0}, // base center at cylinder end
        (vector_float3){1, 0, 0}, // direction same as axis
        CONE_HEIGHT,
        CONE_RADIUS,
        red_,
        &coneCountX);

    GizmoVertex* coneY = generate_cone_triangles(
        (vector_float3){0, 1, 0},
        (vector_float3){0, 1, 0},
        CONE_HEIGHT,
        CONE_RADIUS,
        green_,
        &coneCountY);

    GizmoVertex* coneZ = generate_cone_triangles(
        (vector_float3){0, 0, 1},
        (vector_float3){0, 0, 1},
        CONE_HEIGHT,
        CONE_RADIUS,
        blue_,
        &coneCountZ);
    
    int totalVertCount = vertCountX + vertCountY + vertCountZ + coneCountX + coneCountY + coneCountZ;
    GizmoVertex* allVertices = malloc(sizeof(GizmoVertex) * totalVertCount);
    int offset = 0;
    memcpy(allVertices + offset, cylinderX, sizeof(GizmoVertex) * vertCountX); offset += vertCountX;
    memcpy(allVertices + offset, cylinderY, sizeof(GizmoVertex) * vertCountY); offset += vertCountY;
    memcpy(allVertices + offset, cylinderZ, sizeof(GizmoVertex) * vertCountZ); offset += vertCountZ;
    memcpy(allVertices + offset, coneX, sizeof(GizmoVertex) * coneCountX); offset += coneCountX;
    memcpy(allVertices + offset, coneY, sizeof(GizmoVertex) * coneCountY); offset += coneCountY;
    memcpy(allVertices + offset, coneZ, sizeof(GizmoVertex) * coneCountZ); offset += coneCountZ;
    
    
    MTBuffer vertexBuffer = mt_device_create_buffer_with_bytes(device, allVertices, sizeof(GizmoVertex) * totalVertCount, MTResourceCPUCacheModeDefaultCache);

//    MTBuffer vertexBuffer = mt_device_create_buffer_with_bytes(device, gizmoVertices, sizeof(gizmoVertices), MTResourceCPUCacheModeDefaultCache);
    
//    MTBuffer vertexBuffer = mt_device_create_buffer_with_bytes(device, mesh.vertex_data, mesh.vertex_count * sizeof(Vertex), MTResourceCPUCacheModeDefaultCache);
//    
//    MTBuffer indexBuffer = mt_device_create_buffer_with_bytes(device, mesh.index_data, mesh.index_count * sizeof(uint32_t), MTResourceCPUCacheModeDefaultCache);
    
    // Create uniform Buffers
    const uint32_t MAX_FRAMES_IN_FLIGHT = 2;
    MTBuffer** uniformBuffers = malloc(sizeof(MTBuffer*)* MAX_FRAMES_IN_FLIGHT);
    uniformBuffers[0] = mt_device_create_buffer_with_length(device, sizeof(Uniforms), MTResourceCPUCacheModeWriteCombined);
    uniformBuffers[1] = mt_device_create_buffer_with_length(device, sizeof(Uniforms), MTResourceCPUCacheModeWriteCombined);
    int currentUniformBufferIndex = 0;
    
    dispatch_semaphore_t uniformBufferSemaphore = dispatch_semaphore_create(MAX_FRAMES_IN_FLIGHT);
    
    int texWidth, texHeight, texNumChannels;
    int texForceNumChannels = 4;
    unsigned char* textureBytes = stbi_load("./testTexture.png", &texWidth, &texHeight, &texNumChannels, texForceNumChannels);

    save_texture_as_gpu_ready_bin("./testTexture.png", "./testTexture.bin");
    
    MTTextureDescriptor texture_desc2 = mt_texture_descriptor_create(MTPixelFormatRGBA8Unorm, texWidth, texHeight, false);
    mt_texture_descriptor_set_storage_mode(texture_desc2, MTStorageModeShared);
    
    MTURL path_url = mt_url_init_with_path(mt_string_from_utf8("./testTexture.bin"));
    MTIOFileHandle file = mt_device_new_io_file_handle(device, path_url, &error);
    MTTexture texture = mt_device_create_texture_with_descriptor(device, texture_desc2);
    
    uint32_t width = 512;
    uint32_t height = 512;
    mt_io_command_buffer_load_texture(
        io_cmb,                  // MTIOCommandBuffer
        texture,                 // MTTexture (your destination texture)
        0,                       // slice (typically 0 for 2D textures)
        0,                       // level (mipmap level, 0 = base level)
        (MTSize){ width, height, 1 },      // size to load (MTSize struct)
        width * 4,               // sourceBytesPerRow (e.g. 4 bytes per pixel for RGBA8)
        width * height * 4,      // sourceBytesPerImage (entire image size in bytes)
        (MTOrigin){ 0, 0, 0 },   // destinationOrigin in texture (x=0, y=0, z=0)
        file,                    // MTIOFileHandle (source handle to mapped file)
        0                   // offset in file to the start of texture data
    );
    
    mt_io_command_buffer_commit(io_cmb);
    mt_io_command_buffer_wait_until_completed(io_cmb);
    
    mt_release(texture_desc2);
  
    stbi_image_free(textureBytes);
    
    // Create a Sampler State
    MTSamplerDescriptor* samplerDesc = mt_sampler_descriptor_new();
    mt_sampler_descriptor_set_min_filter(samplerDesc, MTSamplerMinMagFilterLinear);
    mt_sampler_descriptor_set_mag_filter(samplerDesc, MTSamplerMinMagFilterLinear);

    MTSamplerState* samplerState = mt_device_create_sampler_state(device, samplerDesc);
    
    mt_release(samplerDesc);
    
    MTVertexDescriptor vertDesc = mt_vertex_descriptor_create();
    mt_vertex_descriptor_set_vertex_attribute_format(vertDesc, VertexAttributeIndex_Position, MTVertexFormatFloat3);
    mt_vertex_descriptor_set_vertex_attribute_offset(vertDesc, VertexAttributeIndex_Position, 0);
    mt_vertex_descriptor_set_vertex_attribute_buffer_index(vertDesc, VertexAttributeIndex_Position, VertexBufferIndex_Attributes);
    
    mt_vertex_descriptor_set_vertex_attribute_format(vertDesc, VertexAttributeIndex_Normal, MTVertexFormatFloat3);
    mt_vertex_descriptor_set_vertex_attribute_offset(vertDesc, VertexAttributeIndex_Normal, 12);
    mt_vertex_descriptor_set_vertex_attribute_buffer_index(vertDesc, VertexAttributeIndex_Normal, VertexBufferIndex_Attributes);
    
    mt_vertex_descriptor_set_vertex_attribute_format(vertDesc, VertexAttributeIndex_UV, MTVertexFormatFloat2);
    mt_vertex_descriptor_set_vertex_attribute_offset(vertDesc, VertexAttributeIndex_UV, 24);
    mt_vertex_descriptor_set_vertex_attribute_buffer_index(vertDesc, VertexAttributeIndex_UV, VertexBufferIndex_Attributes);

    mt_vertex_descriptor_set_vertex_layout_stride(vertDesc, VertexBufferIndex_Attributes, 32);
    mt_vertex_descriptor_set_vertex_layout_step_rate(vertDesc, VertexBufferIndex_Attributes, 1);
    mt_vertex_descriptor_set_vertex_layout_step_function(vertDesc, VertexBufferIndex_Attributes, MTVertexStepFunctionPerVertex);
    
    MTRenderPipelineDescriptor renderPipelineDesc = mt_render_pipeline_descriptor_new();
    mt_render_pipeline_descriptor_set_label(renderPipelineDesc, "My Renderpipeline");
    mt_render_pipeline_descriptor_set_vertex_function(renderPipelineDesc, vertFunction);
    mt_render_pipeline_descriptor_set_fragment_function(renderPipelineDesc, fragFunction);
    mt_render_pipeline_descriptor_set_vertex_descriptor(renderPipelineDesc, vertDesc);
    mt_render_pipeline_descriptor_set_color_attachments_pixel_format(renderPipelineDesc, 0, (MTPixelFormat)platform_get_drawable_pixelFormat());

    MTRenderPipelineColorAttachmentDescriptor ca = mt_render_pipeline_descriptor_get_color_attachment_at_index(renderPipelineDesc, 0);
    mt_color_attachment_set_pixel_format(ca, MTPixelFormatBGRA8Unorm);
    mt_color_attachment_set_blending(ca, true);
    mt_color_attachment_set_rgb_blend_op(ca, MTBlendOperationAdd);
    mt_color_attachment_set_alpha_blend_op(ca, MTBlendOperationAdd);
    mt_color_attachment_set_src_rgb_blend(ca, MTBlendFactorSourceAlpha);
    mt_color_attachment_set_src_alpha_blend(ca, MTBlendFactorSourceAlpha);
    mt_color_attachment_set_dst_rgb_blend(ca, MTBlendFactorOneMinusSourceAlpha);
    mt_color_attachment_set_dst_alpha_blend(ca, MTBlendFactorOneMinusSourceAlpha);
    
    MTVertexDescriptor gizmo_vertDesc = mt_vertex_descriptor_create();
    mt_vertex_descriptor_set_vertex_attribute_format(gizmo_vertDesc, VertexAttributeIndex_Position, MTVertexFormatFloat3);
    mt_vertex_descriptor_set_vertex_attribute_offset(gizmo_vertDesc, VertexAttributeIndex_Position, 0);
    mt_vertex_descriptor_set_vertex_attribute_buffer_index(gizmo_vertDesc, VertexAttributeIndex_Position, VertexBufferIndex_Attributes);
    
    mt_vertex_descriptor_set_vertex_attribute_format(gizmo_vertDesc, 1, MTVertexFormatFloat4);
    mt_vertex_descriptor_set_vertex_attribute_offset(gizmo_vertDesc, 1, 16);
    mt_vertex_descriptor_set_vertex_attribute_buffer_index(gizmo_vertDesc, 1, VertexBufferIndex_Attributes);
    
    mt_vertex_descriptor_set_vertex_layout_stride(gizmo_vertDesc, VertexBufferIndex_Attributes, 32);
    mt_vertex_descriptor_set_vertex_layout_step_rate(gizmo_vertDesc, VertexBufferIndex_Attributes, 1);
    mt_vertex_descriptor_set_vertex_layout_step_function(gizmo_vertDesc, VertexBufferIndex_Attributes, MTVertexStepFunctionPerVertex);
    
    MTRenderPipelineDescriptor gizmo_renderPipelineDesc = mt_render_pipeline_descriptor_new();
    mt_render_pipeline_descriptor_set_label(gizmo_renderPipelineDesc, "Gizmo Renderpipeline");
    mt_render_pipeline_descriptor_set_vertex_function(gizmo_renderPipelineDesc, gizmo_vertFunction);
    mt_render_pipeline_descriptor_set_fragment_function(gizmo_renderPipelineDesc, gizmo_fragFunction);
    mt_render_pipeline_descriptor_set_vertex_descriptor(gizmo_renderPipelineDesc, gizmo_vertDesc);
    mt_render_pipeline_descriptor_set_color_attachments_pixel_format(gizmo_renderPipelineDesc, 0, (MTPixelFormat)platform_get_drawable_pixelFormat());
    
    MTRenderPipelineColorAttachmentDescriptor ca2 = mt_render_pipeline_descriptor_get_color_attachment_at_index(gizmo_renderPipelineDesc, 0);
    mt_color_attachment_set_pixel_format(ca2, MTPixelFormatBGRA8Unorm);
    mt_color_attachment_set_blending(ca2, true);
    mt_color_attachment_set_rgb_blend_op(ca2, MTBlendOperationAdd);
    mt_color_attachment_set_alpha_blend_op(ca2, MTBlendOperationAdd);
    mt_color_attachment_set_src_rgb_blend(ca2, MTBlendFactorSourceAlpha);
    mt_color_attachment_set_src_alpha_blend(ca2, MTBlendFactorSourceAlpha);
    mt_color_attachment_set_dst_rgb_blend(ca2, MTBlendFactorOneMinusSourceAlpha);
    mt_color_attachment_set_dst_alpha_blend(ca2, MTBlendFactorOneMinusSourceAlpha);

    
    MTRenderPipelineState renderPipelineState = mt_device_create_render_pipeline_state(device, renderPipelineDesc, &error);
    MTRenderPipelineState gizmo_renderPipelineState = mt_device_create_render_pipeline_state(device, gizmo_renderPipelineDesc, &error);
    
    if (!renderPipelineState) {
        printf("Failed to create pipeline state. Error: %s\n", mt_error_get_localized_description(error));
        return(1);
    }
    
    if (!gizmo_renderPipelineState) {
        printf("Failed to create gizmo pipeline state. Error: %s\n", mt_error_get_localized_description(error));
        return(1);
    }

    mt_release(vertFunction);
    mt_release(fragFunction);
    mt_release(gizmo_vertFunction);
    mt_release(gizmo_fragFunction);
    mt_release(vertDesc);
    mt_release(gizmo_vertDesc);
    mt_release(renderPipelineDesc);
    mt_release(gizmo_renderPipelineDesc);
    
    // Timing
    mach_timebase_info_data_t machTimebaseInfoData;
    mach_timebase_info(&machTimebaseInfoData);
    assert(machTimebaseInfoData.denom != 0);
    double currentTimeInSeconds = osxGetCurrentTimeInSeconds(machTimebaseInfoData);
    
//    MARK: Test Binary Data Compression
    
    const char* input_path = "./testTexture.bin";
    const char* output_path = "./testTexture.binpack";
    size_t chunk_size = MTLIOCompressionContextDefaultChunkSize();

    size_t data_size = 0;
    void* data = load_raw_texture_data(input_path, &data_size);
    if (!data) {
       perror("Failed to load input file");
       return 1;
    }

    MTIOCompressionContext ctx = MTLIOCreateCompressionContext(output_path, MTIOCompressionMethod_ZLib, chunk_size);
    if (!ctx) {
       perror("Failed to create compression context");
       free(data);
       return 1;
    }
    
    // get uncompressed file
    MTLIOCompressionContextAppendData(ctx, data, data_size);

    //  Compress the data and pack into a chunck data file for faster reads
    MTIOCompressionStatus status = MTLIOFlushAndDestroyCompressionContext(ctx);
    if (status != MTIOCompressionStatusComplete) {
       fprintf(stderr, "Compression failed.\n");
       free(data);
       return 1;
    }

    printf("Compressed and saved to %s\n", output_path);
    free(data);

    while (isRunning){
        
        dispatch_semaphore_wait(uniformBufferSemaphore, DISPATCH_TIME_FOREVER);
        
        double previousTimeInSeconds = currentTimeInSeconds;
        currentTimeInSeconds = osxGetCurrentTimeInSeconds(machTimebaseInfoData);
        float dt = currentTimeInSeconds - previousTimeInSeconds;

        if(dt > (1.f / 60.f))
            dt = (1.f / 60.f);
        
        if(!platform_pump_messages()){
            isRunning = false;
        }
        
        // Modulate player's y-position
        vector_float4 playerPos = {};
        const float posCycleAmplitude = 0.5f;
        const float posCyclePeriod = 3.f; // in seconds
        const float posCycleFreq = 2 * M_PI / posCyclePeriod;
        playerPos.z = 1;
        playerPos.y = posCycleAmplitude * sinf(posCycleFreq * currentTimeInSeconds);

        // Cycle player color
        vector_float4 playerColor;
        const float colorCyclePeriod = 5.f; //in seconds
        const float colorCycleFreq = 2 * M_PI / colorCyclePeriod;
        playerColor.r = 0.5f * (sinf(colorCycleFreq * currentTimeInSeconds) + 1);
        playerColor.g = 1 - playerColor.r;
        playerColor.b = 0.f;
        playerColor.a = 1.f;

        // Update uniforms
        float aspectRatio = platform_get_drawable_width() / (float)platform_get_drawable_height();
        matrix_float4x4 projection = make_perspective_matrix(M_PI / 4.0f, aspectRatio, 0.1f, 100.0f);
        matrix_float4x4 model = matrix_multiply(make_translation(0, -2, -10), rotate_y(currentTimeInSeconds));
        matrix_float4x4 mvp = matrix_multiply(projection, model);

        Uniforms uniforms;
        uniforms.mvp = mvp;
        uniforms.color = playerColor;
        memcpy(mt_buffer_get_contents(uniformBuffers[currentUniformBufferIndex]), &uniforms, sizeof(Uniforms));

        MTAutoreleasePool* pool =  mt_autoreleasepool_create();
        
        MTDrawable drawable = platform_get_next_drawable();
        
        MTRenderPassDescriptor renderPass = mt_renderpass_new();
        MTCommandBuffer cmdBuffer = mt_command_queue_create_commandBuffer(queue);
        
        // Single-step color attachment access - much cleaner!
        MTRenderPassColorAttachmentDescriptor ca = mt_renderpass_color_attachment(renderPass, 0);
        mt_renderpass_color_attachment_set_texture(ca, cametal_drawable_get_texture(drawable));
        mt_renderpass_color_attachment_set_load_action(ca, MTLoadActionClear);
        mt_renderpass_color_attachment_set_store_action(ca, MTStoreActionStore);
        mt_renderpass_color_attachment_set_clear_color(ca, mt_clear_color(0.1, 0.1, 0.1, 1.0));
        
        
        MTRenderCommandEncoder renderCommandEncoder = mt_renderCommand_encoder_new(cmdBuffer, renderPass);
        mt_release(renderPass);
        
        mt_renderCommand_encoder_set_viewport(renderCommandEncoder, mt_viewport_make(
                                                                    0, 0,
                                                                    platform_get_drawable_width(),
                                                                    platform_get_drawable_height(),
                                                                    0, 1));
        
//        mt_renderCommand_encoder_set_cull_mode(renderCommandEncoder, MTCullModeBack);
//        mt_renderCommand_encoder_set_front_facing_winding(renderCommandEncoder, MTWindingCounterClockwise);
    
//        mt_renderCommand_encoder_set_triangle_fill_mode(renderCommandEncoder, MTTriangleFillModeLines);
        
//        mt_renderCommand_encoder_set_pipeline_state(renderCommandEncoder, renderPipelineState);
        mt_renderCommand_encoder_set_pipeline_state(renderCommandEncoder, gizmo_renderPipelineState);
        
        mt_renderCommand_encoder_set_vertex_buffer(renderCommandEncoder, vertexBuffer, 0, VertexBufferIndex_Attributes);
        
        mt_renderCommand_encoder_set_vertex_buffer(renderCommandEncoder, uniformBuffers[currentUniformBufferIndex], 0, VertexBufferIndex_Uniforms);
        
        mt_renderCommand_encoder_set_fragment_texture(renderCommandEncoder, texture, 0);
        
        mt_renderCommand_encoder_set_fragment_sampler_state(renderCommandEncoder, samplerState, 0);
        
        int drawOffset = 0;
        mt_renderCommand_encoder_draw_primitives(renderCommandEncoder, MTPrimitiveTypeTriangleStrip, drawOffset, vertCountX); drawOffset += vertCountX;
        mt_renderCommand_encoder_draw_primitives(renderCommandEncoder, MTPrimitiveTypeTriangleStrip, drawOffset, vertCountY); drawOffset += vertCountY;
        mt_renderCommand_encoder_draw_primitives(renderCommandEncoder, MTPrimitiveTypeTriangleStrip, drawOffset, vertCountZ); drawOffset += vertCountZ;

        mt_renderCommand_encoder_draw_primitives(renderCommandEncoder, MTPrimitiveTypeTriangle, drawOffset, coneCountX); drawOffset += coneCountX;
        mt_renderCommand_encoder_draw_primitives(renderCommandEncoder, MTPrimitiveTypeTriangle, drawOffset, coneCountY); drawOffset += coneCountY;
        mt_renderCommand_encoder_draw_primitives(renderCommandEncoder, MTPrimitiveTypeTriangle, drawOffset, coneCountZ); drawOffset += coneCountZ;
        
//        mt_renderCommand_encoder_draw_indexed_primitives(renderCommandEncoder, MTPrimitiveTypeTriangle, mesh.index_count, MTIndexTypeUInt32, indexBuffer, 0);
        
        
        mt_renderCommand_encoder_end_encoding(renderCommandEncoder);
        
        mt_commandBuffer_present_drawable(cmdBuffer, drawable);
        
        // Calculate FPS:
        static double frameStartTime = 0.0;
        static double frameDeltaTime = 0.0;
        static int frameCount = 0;
        static double accumulatedTime = 0.0;

        frameDeltaTime = currentTimeInSeconds - frameStartTime;
        frameStartTime = currentTimeInSeconds;

        accumulatedTime += frameDeltaTime;
        frameCount++;

        if (accumulatedTime >= 1.0) {
//            printf("FPS: %d\n", frameCount);
            accumulatedTime = 0.0;
            frameCount = 0;
        }
        
        dispatch_semaphore_signal(uniformBufferSemaphore);
        
        mt_commandBuffer_commit(cmdBuffer);
        
        mt_commandBuffer_wait_until_completed(cmdBuffer);
        
        mt_autoreleasepool_drain(pool);

        currentUniformBufferIndex = (currentUniformBufferIndex + 1) % MAX_FRAMES_IN_FLIGHT;
    }
    
//    platform_system_shutdown();
    
    return 0;
}
