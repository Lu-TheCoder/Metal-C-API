//
//  main.c
//  Metal C
//
//  Created by Lungile Maseko on 2024/04/27.
//

#include <stdio.h>
#include "Metal/Metal.h"
#include "Platform/platform.h"
#include "Metal/Foundation/Foundation.h"
#include "shaders/shaderInterface.h"
#include <dispatch/semaphore.h>
#include <mach/mach_time.h>
#include <simd/simd.h>

#define STB_IMAGE_IMPLEMENTATION
#include "vendors/stb_image.h"

//#include <sys/sysctl.h>
double osxGetCurrentTimeInSeconds(mach_timebase_info_data_t tb)
{
    uint64_t timeInNanoSecs =  mach_absolute_time() * tb.numer / tb.denom;
    return (double)timeInNanoSecs * 1.0E-9;
}

int main(int argc, const char * argv[]) {
    
    platform_system_config config = {
        .application_name = "Engine",
        .width = 1024,
        .height = 768,
        .flags = 0
    };
    
    if(!platform_system_startup(&config)){
        printf("Failed to startup platform.\n");
    }
    
    MTDevice* device = mt_create_system_default_device();
    
    MTCommandQueue* queue = mt_commandQueue_new(device);

//    char buffer[256];
//    size_t buffer_len = 256;
//    if (sysctlbyname("machdep.cpu.brand_string", &buffer, &buffer_len, 0, 0) == 0) {
//        printf("%s\n",buffer);
//    }
    
    bool isRunning = true;
    
    MTBundle* bundle = mt_bundle_new();
    MTString* lib_path = mt_bundle_get_lib_path(bundle, mt_string_utf8String("default"), mt_string_utf8String("metallib"));
    MTURL* fileURL = mt_url_init_with_path(lib_path);
    
    MTError* error = NULL;
    MTLibrary* library = mt_library_new_library_withURL(device, fileURL, &error);
//    MTLibrary* library = mtNewDefaultLibrary(device);

    if(!library){
        printf("Failed to load library. Error %s\n", mt_error_get_localized_description(error));
    }
    
    MTFunction* vertFunction = mt_library_new_function(library, mt_string_utf8String("vert"));
    MTFunction* fragFunction = mt_library_new_function(library, mt_string_utf8String("frag"));
    
    assert(vertFunction);
    assert(fragFunction);
    
    mt_release(library);
    
    simd_float2 vertexData[] = {
        {-0.5f,  0.5f},
        {-0.5f, -0.5f},
        {0.5f, -0.5f},
        {-0.5f,  0.5f},
        {0.5f, -0.5f},
        {0.5f,  0.5f}
    };
    
    MTBuffer* vertexBuffer = mt_device_buffer_new_buffer_with_bytes(device, vertexData, sizeof(vertexData), MTResourceCPUCacheModeDefaultCache);
    
    // Create uniform Buffers
    const uint32_t MAX_FRAMES_IN_FLIGHT = 2;
    MTBuffer** uniformBuffers = malloc(sizeof(MTBuffer*)* MAX_FRAMES_IN_FLIGHT);
    uniformBuffers[0] = mt_device_buffer_new_buffer_with_length(device, sizeof(Uniforms), MTResourceCPUCacheModeWriteCombined);
    uniformBuffers[1] = mt_device_buffer_new_buffer_with_length(device, sizeof(Uniforms), MTResourceCPUCacheModeWriteCombined);
    int currentUniformBufferIndex = 0;
    
    dispatch_semaphore_t uniformBufferSemaphore = dispatch_semaphore_create(MAX_FRAMES_IN_FLIGHT);
    
    int texWidth, texHeight, texNumChannels;
    int texForceNumChannels = 4;
    unsigned char* textureBytes = stbi_load("testTexture.png", &texWidth, &texHeight, &texNumChannels, texForceNumChannels);
    int texBytesPerRow = 4 * texWidth;
    
    MTTextureDescriptor* texture_desc2 = mt_textureDescriptor_new_2D_descriptor(MTPixelFormatRGBA8Unorm, texWidth, texHeight, false);
    
    MTTexture* texture = mt_device_texture_new_texture_with_descriptor(device, texture_desc2);
    mt_release(texture_desc2);
    
    // Copy loaded image into MTTextureObject
    mt_texture_replaceRegion(texture, mtRegionMake2D(0, 0, texWidth, texHeight), 0, textureBytes, texBytesPerRow);
    
    stbi_image_free(textureBytes);
    
    // Create a Sampler State
    MTSamplerDescriptor* samplerDesc = mt_samplerDescriptor_new();
    mt_samplerDescriptor_set_minFilter(samplerDesc, MTSamplerMinMagFilterLinear);
    mt_samplerDescriptor_set_magFilter(samplerDesc, MTSamplerMinMagFilterLinear);

    MTSamplerState* samplerState = mt_device_sampler_state_new(device, samplerDesc);
    
    mt_release(samplerDesc);
    
    MTVertexDescriptor* vertDesc = mt_vertexDescriptor_new();
    MTVertexAttributeDescriptorArray* attributes = mt_vertexDescriptor_get_attributes(vertDesc);
    MTVertexBufferLayoutDescriptorArray* layouts = mt_vertexDescriptor_get_layouts(vertDesc);
    
    mt_vertexAttribute_set_format(attributes, VertexAttributeIndex_Position, MTVertexFormatFloat2);
    mt_vertexAttribute_set_offset(attributes, VertexAttributeIndex_Position, 0);
    mt_vertexAttribute_set_buffer_index(attributes, VertexAttributeIndex_Position, VertexBufferIndex_Attributes);
    
    mt_vertexBufferLayout_set_stride(layouts, VertexBufferIndex_Attributes, 2 * sizeof(float));
    mt_vertexBufferLayout_set_stepRate(layouts, VertexBufferIndex_Attributes, 1);
    mt_vertexBufferLayout_set_stepFunction(layouts, VertexBufferIndex_Attributes, MTVertexStepFunctionPerVertex);
    
    MTRenderPipelineDescriptor* renderPipelineDesc = mt_renderPipeline_descriptor_new();
    mt_renderPipeline_descriptor_set_vertex_function(renderPipelineDesc, vertFunction);
    mt_renderPipeline_descriptor_set_fragment_function(renderPipelineDesc, fragFunction);
    mt_renderPipeline_descriptor_set_vertex_descriptor(renderPipelineDesc, vertDesc);
    mt_renderPipeline_descriptor_set_color_attachments_pixel_format(renderPipelineDesc, 0, (MTPixelFormat)platform_get_drawable_pixelFormat());
    
    MTRenderPipelineState* renderPipelineState = mt_device_renderPipeline_state_new(device, renderPipelineDesc, &error);
    
    if (!renderPipelineState) {
        printf("Failed to create pipeline state. Error: %s\n", mt_error_get_localized_description(error));
        return(1);
    }

    mt_release(vertFunction);
    mt_release(fragFunction);
    mt_release(vertDesc);
    mt_release(renderPipelineDesc);
    
    // Timing
   mach_timebase_info_data_t machTimebaseInfoData;
   mach_timebase_info(&machTimebaseInfoData);
   assert(machTimebaseInfoData.denom != 0);
   double currentTimeInSeconds = osxGetCurrentTimeInSeconds(machTimebaseInfoData);

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
        vfloat2 playerPos = {};
        const float posCycleAmplitude = 0.5f;
        const float posCyclePeriod = 3.f; // in seconds
        const float posCycleFreq = 2 * M_PI / posCyclePeriod;
        playerPos.y = posCycleAmplitude * sinf(posCycleFreq * currentTimeInSeconds);

        // Cycle player color
        vfloat4 playerColor;
        const float colorCyclePeriod = 5.f; //in seconds
        const float colorCycleFreq = 2 * M_PI / colorCyclePeriod;
        playerColor.r = 0.5f * (sinf(colorCycleFreq * currentTimeInSeconds) + 1);
        playerColor.g = 1 - playerColor.r;
        playerColor.b = 0.f;
        playerColor.a = 1.f;

        // Update uniforms
        Uniforms uniforms;
        uniforms.pos = playerPos;
        uniforms.color = playerColor;
        memcpy(mt_buffer_get_contents(uniformBuffers[currentUniformBufferIndex]), &uniforms, sizeof(Uniforms));

        MTAutoreleasePool* pool =  mt_autoreleasepool_new();
        mt_autoreleasepool_init(pool);
        
        void* drawable = platform_get_next_drawable();
        
        MTRenderPassDescriptor* renderPass = mt_renderpass_descriptor_new();
        MTCommandBuffer* cmdBuffer = mt_commandBuffer_new(queue);
        
        MTRenderPassColorAttachmentDescriptorArray* colorAttachments = mt_renderpass_color_attachment_get_color_attachments(renderPass);
        MTRenderPassColorAttachmentDescriptor* colorAttachment = mt_renderpass_get_color_attachment_at_index(colorAttachments, 0);
        mt_renderpass_color_attachment_set_texture(colorAttachment, platform_get_next_drawable_texture(drawable));
        mt_renderpass_color_attachment_set_loadAction(colorAttachment, MTLoadActionClear);
        mt_renderpass_color_attachment_set_storeAction(colorAttachment, MTStoreActionStore);
        mt_renderpass_color_attachment_set_clearColor(colorAttachment, mt_clear_color_make(0.2f, 0.22f, 0.24f, 1.0f));
        
        MTRenderCommandEncoder* renderCommandEncoder = mt_renderCommand_encoder_new(cmdBuffer, renderPass);
        mt_release(renderPass);
        
        mt_renderCommand_encoder_set_viewport(renderCommandEncoder, mt_viewport_make(0, 0,
                                                                           platform_get_drawable_width(),
                                                                           platform_get_drawable_height(),
                                                                           0, 1));
        
        mt_renderCommand_encoder_set_pipeline_state(renderCommandEncoder, renderPipelineState);
        mt_renderCommand_encoder_set_vertex_buffer(renderCommandEncoder, vertexBuffer, 0, VertexBufferIndex_Attributes);
        mt_renderCommand_encoder_set_vertex_buffer(renderCommandEncoder, uniformBuffers[currentUniformBufferIndex], 0, VertexBufferIndex_Uniforms);
        mt_renderCommand_encoder_set_fragment_texture_at_index(renderCommandEncoder, texture, 0);
        mt_renderCommand_encoder_set_fragment_sampler_state_at_index(renderCommandEncoder, samplerState, 0);
        mt_renderCommand_encoder_draw_primitives(renderCommandEncoder, MTPrimitiveTypeTriangle, 0, 6);
        mt_renderCommand_encoder_end_encoding(renderCommandEncoder);
        
        mt_commandBuffer_present_drawable(cmdBuffer, drawable);
        
        dispatch_semaphore_signal(uniformBufferSemaphore);
        
        mt_commandBuffer_commit(cmdBuffer);
        
        mt_commandBuffer_wait_until_completed(cmdBuffer);
        
        mt_autoreleasepool_release(pool);

        currentUniformBufferIndex = (currentUniformBufferIndex + 1) % MAX_FRAMES_IN_FLIGHT;
    }
    
//    platform_system_shutdown();
    
    return 0;
}
