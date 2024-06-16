//
//  main.c
//  Metal C
//
//  Created by Lungile Maseko on 2024/04/27.
//

#include <stdio.h>
#include <stdlib.h>
#include "Metal/Metal.h"
#include "Platform/platform.h"
#include "Metal/Foundation/Foundation.h"
#include "shaders/shaderInterface.h"
#include <dispatch/dispatch.h>
#include <mach/mach_time.h>
#include <simd/simd.h>
#include "VertexData.h"
#include "MathUtilities.h"
#include "Engine/core/event.h"
#include "Engine/core/input.h"

#define STB_IMAGE_IMPLEMENTATION
#include "vendors/stb_image.h"

typedef struct Systems {
    uint64_t event_system_memory_requirement;
    struct event_state* event_system;
    uint64_t input_system_memory_requirement;
    struct input_state* input_system;
}Systems;

typedef struct Engine_State {
    MTDevice* device;
    MTRenderPipelineState* renderPipelineState;
    MTRenderPassDescriptor* renderPassDescriptor;
    MTRenderPassColorAttachmentDescriptorArray* colorAttachments;
    MTRenderPassDepthAttachmentDescriptor* depthAttachment;
    void* drawable;
    uint32_t sampleCount;
    MTTexture* msaaRenderTargetTexture;
    MTTexture* depthTexture;
}Engine_State;

static Engine_State* engine;

void create_depth_and_msaa_textures(void){
    // Create Depth & MSAA Textures
    MTTextureDescriptor* msaaTextureDescriptor = mt_textureDescriptor_new();
    mt_textureDescriptor_set_textureType(msaaTextureDescriptor, MTTextureType2DMultisample);
    mt_textureDescriptor_set_pixelFormat(msaaTextureDescriptor, MTPixelFormatBGRA8Unorm);
    mt_textureDescriptor_set_width(msaaTextureDescriptor, platform_get_drawable_width());
    mt_textureDescriptor_set_height(msaaTextureDescriptor, platform_get_drawable_height());
    mt_textureDescriptor_set_usage(msaaTextureDescriptor, MTTextureUsageRenderTarget);
    mt_textureDescriptor_set_sampleCount(msaaTextureDescriptor, engine->sampleCount);
    
    engine->msaaRenderTargetTexture = mt_device_texture_new_texture_with_descriptor(engine->device, msaaTextureDescriptor);
    
    MTTextureDescriptor* depthTextureDescriptor = mt_textureDescriptor_new();
    mt_textureDescriptor_set_textureType(depthTextureDescriptor, MTTextureType2DMultisample);
    mt_textureDescriptor_set_pixelFormat(depthTextureDescriptor, MTPixelFormatDepth32Float);
    mt_textureDescriptor_set_width(depthTextureDescriptor, platform_get_drawable_width());
    mt_textureDescriptor_set_height(depthTextureDescriptor, platform_get_drawable_height());
    mt_textureDescriptor_set_usage(depthTextureDescriptor, MTTextureUsageRenderTarget);
    mt_textureDescriptor_set_sampleCount(depthTextureDescriptor, engine->sampleCount);
    
    engine->depthTexture = mt_device_texture_new_texture_with_descriptor(engine->device, depthTextureDescriptor);
    
    mt_release(msaaTextureDescriptor);
    mt_release(depthTextureDescriptor);
}

void update_renderPass_descriptor(void) {
    MTRenderPassColorAttachmentDescriptor* colorAttachment = mt_renderpass_get_color_attachment_at_index(engine->colorAttachments, 0);
    mt_renderpass_color_attachment_set_texture(colorAttachment, engine->msaaRenderTargetTexture);
    mt_renderpass_color_attachment_set_resolve_texture(colorAttachment, platform_get_next_drawable_texture(engine->drawable));
    mt_renderpass_depth_attachment_set_texture(engine->depthAttachment, engine->depthTexture);
}

bool engine_on_application_quit(uint16_t code, void* sender, void* listener_inst, event_context data){
    return true;
}

bool engine_on_window_resized(uint16_t code, void* sender, void* listener_inst, event_context data) {
    
    printf("Window Resized!! drawable Width: %d \n", data.data.u16[0]);
    printf("Window Resized!! drawable Height: %d \n", data.data.u16[1]);
    
    if (engine->msaaRenderTargetTexture){
        mt_release(engine->msaaRenderTargetTexture);
    }
    
    if (engine->depthTexture){
        mt_release(engine->depthTexture);
    }
    
    create_depth_and_msaa_textures();
    engine->drawable = platform_get_next_drawable();
    update_renderPass_descriptor();
    return true;
}

//#include <sys/sysctl.h>
double osxGetCurrentTimeInSeconds(mach_timebase_info_data_t tb)
{
    uint64_t timeInNanoSecs =  mach_absolute_time() * tb.numer / tb.denom;
    return (double)timeInNanoSecs * 1.0E-9;
}

typedef struct Texture {
    MTTexture* texture;
    int width, height, channels;
    MTDevice* device;
}Texture;

Texture* create_texture(const char* path, MTDevice* device) {
    Texture* texture = malloc(sizeof(Texture));
    
    texture->device = device;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* image = stbi_load(path, &texture->width, &texture->height, &texture->channels, STBI_rgb_alpha);
    assert(image != NULL);
    
    MTTextureDescriptor* textureDescriptor = mt_textureDescriptor_new();
    mt_textureDescriptor_set_pixelFormat(textureDescriptor, MTPixelFormatRGBA8Unorm);
    mt_textureDescriptor_set_width(textureDescriptor, texture->width);
    mt_textureDescriptor_set_height(textureDescriptor, texture->height);
    
    texture->texture = mt_device_texture_new_texture_with_descriptor(device, textureDescriptor);
    
    uintptr_t bytesPerRow = 4 * texture->width;
    
    mt_texture_replaceRegion(texture->texture, mtRegionMake2D(0, 0, texture->width, texture->height), 0, image, bytesPerRow);
    
    mt_release(textureDescriptor);
    stbi_image_free(image);
    
    return texture;
}

typedef struct GameObject {
    VertexData* vertexData;
    MTBuffer* vertexBuffer;
    MTBuffer* transformationBuffer;
    Texture* texture;
}GameObject;

GameObject create_gameObject(VertexData* data, MTDevice* device);

GameObject create_gameObject(VertexData* data, MTDevice* device) {
    GameObject obj;
    
    obj.vertexData = data;
    
    obj.vertexBuffer = mt_device_buffer_new_buffer_with_bytes(device, data, sizeof(obj.vertexData), MTResourceStorageModeShared);
    
    obj.transformationBuffer = mt_device_buffer_new_buffer_with_length(device, sizeof(TransformationData), MTResourceStorageModeShared);
    
    obj.texture = malloc(sizeof(Texture));
    obj.texture = create_texture("mc_grass.jpeg", device);
    
    return obj;
}


int main(int argc, const char * argv[]) {
    
    engine = malloc(sizeof(Engine_State));
    engine->sampleCount = 4;
    
    Systems* systems = malloc(sizeof(Systems));
//    
    event_system_initialize(&systems->event_system_memory_requirement, 0);
    systems->event_system = malloc(systems->event_system_memory_requirement);
    if (!event_system_initialize(&systems->event_system_memory_requirement, systems->event_system)) {
        printf("Failed to initialize event system.");
        return false;
    }

    platform_system_config config = {
        .application_name = "Engine",
        .width = 1024,
        .height = 768,
        .flags = 0
    };
    
    if(!platform_system_startup(&config)){
        printf("Failed to startup platform.\n");
    }
    
    if(systems->event_system){
        event_register(EVENT_CODE_RESIZED, systems->event_system, engine_on_window_resized);
        event_register(EVENT_CODE_APPLICATION_QUIT, systems->event_system, engine_on_application_quit);
    }

    engine->device = mt_create_system_default_device();

    bool isRunning = true;
    
    MTBundle* bundle = mt_bundle_new();
    MTString* lib_path = mt_bundle_get_lib_path(bundle, mt_string_utf8String("default"), mt_string_utf8String("metallib"));
    MTURL* fileURL = mt_url_init_with_path(lib_path);
    
    MTError* error = NULL;
    MTLibrary* library = mt_library_new_library_withURL(engine->device, fileURL, &error);
    mt_release(fileURL);

    if(!library){
        printf("Failed to load library. Error %s\n", mt_error_get_localized_description(error));
    }
    
    MTFunction* vertFunction = mt_library_new_function(library, mt_string_utf8String("vertexShader"));
    MTFunction* fragFunction = mt_library_new_function(library, mt_string_utf8String("fragmentShader"));
    
    assert(vertFunction);
    assert(fragFunction);
    
    mt_release(library);
    
    // Cube for use in a right-handed coordinate system with triangle faces
    // specified with a Counter-Clockwise winding order.
    VertexData cubeVertices[] = {
        // Front face
        {{-0.5, -0.5, 0.5, 1.0}, {0.0, 0.0}},
        {{0.5, -0.5, 0.5, 1.0}, {1.0, 0.0}},
        {{0.5, 0.5, 0.5, 1.0}, {1.0, 1.0}},
        {{0.5, 0.5, 0.5, 1.0}, {1.0, 1.0}},
        {{-0.5, 0.5, 0.5, 1.0}, {0.0, 1.0}},
        {{-0.5, -0.5, 0.5, 1.0}, {0.0, 0.0}},
        
        // Back face
        {{0.5, -0.5, -0.5, 1.0}, {0.0, 0.0}},
        {{-0.5, -0.5, -0.5, 1.0}, {1.0, 0.0}},
        {{-0.5, 0.5, -0.5, 1.0}, {1.0, 1.0}},
        {{-0.5, 0.5, -0.5, 1.0}, {1.0, 1.0}},
        {{0.5, 0.5, -0.5, 1.0}, {0.0, 1.0}},
        {{0.5, -0.5, -0.5, 1.0}, {0.0, 0.0}},

        // Top face
        {{-0.5, 0.5, 0.5, 1.0}, {0.0, 0.0}},
        {{0.5, 0.5, 0.5, 1.0}, {1.0, 0.0}},
        {{0.5, 0.5, -0.5, 1.0}, {1.0, 1.0}},
        {{0.5, 0.5, -0.5, 1.0}, {1.0, 1.0}},
        {{-0.5, 0.5, -0.5, 1.0}, {0.0, 1.0}},
        {{-0.5, 0.5, 0.5, 1.0}, {0.0, 0.0}},

        // Bottom face
        {{-0.5, -0.5, -0.5, 1.0}, {0.0, 0.0}},
        {{0.5, -0.5, -0.5, 1.0}, {1.0, 0.0}},
        {{0.5, -0.5, 0.5, 1.0}, {1.0, 1.0}},
        {{0.5, -0.5, 0.5, 1.0}, {1.0, 1.0}},
        {{-0.5, -0.5, 0.5, 1.0}, {0.0, 1.0}},
        {{-0.5, -0.5, -0.5, 1.0}, {0.0, 0.0}},

        // Left face
        {{-0.5, -0.5, -0.5, 1.0}, {0.0, 0.0}},
        {{-0.5, -0.5, 0.5, 1.0}, {1.0, 0.0}},
        {{-0.5, 0.5, 0.5, 1.0}, {1.0, 1.0}},
        {{-0.5, 0.5, 0.5, 1.0}, {1.0, 1.0}},
        {{-0.5, 0.5, -0.5, 1.0}, {0.0, 1.0}},
        {{-0.5, -0.5, -0.5, 1.0}, {0.0, 0.0}},

        // Right face
        {{0.5, -0.5, 0.5, 1.0}, {0.0, 0.0}},
        {{0.5, -0.5, -0.5, 1.0}, {1.0, 0.0}},
        {{0.5, 0.5, -0.5, 1.0}, {1.0, 1.0}},
        {{0.5, 0.5, -0.5, 1.0}, {1.0, 1.0}},
        {{0.5, 0.5, 0.5, 1.0}, {0.0, 1.0}},
        {{0.5, -0.5, 0.5, 1.0}, {0.0, 0.0}},
    };
    
//    GameObject cube = create_gameObject(cubeVertices, device);
//    
    MTBuffer* cubeVertexBuffer = mt_device_buffer_new_buffer_with_bytes(engine->device, cubeVertices, sizeof(cubeVertices), MTResourceStorageModeShared);
    
    Texture* grassTexture = create_texture("mc_grass.jpeg", engine->device);
    
    MTBuffer* transformationBuffer = mt_device_buffer_new_buffer_with_length(engine->device, sizeof(TransformationData), MTResourceStorageModeShared);
    
    MTCommandQueue* cmd_queue = mt_device_commandQueue_new(engine->device);
    
    int sampleCount = 4;
    MTRenderPipelineDescriptor* renderPipelineDescriptor = mt_renderPipeline_descriptor_new();
    mt_renderPipeline_descriptor_set_vertex_function(renderPipelineDescriptor, vertFunction);
    mt_renderPipeline_descriptor_set_fragment_function(renderPipelineDescriptor, fragFunction);
    assert(renderPipelineDescriptor);
    MTPixelFormat pixelFormat = (MTPixelFormat)platform_get_drawable_pixelFormat();
    mt_renderPipeline_descriptor_set_color_attachments_pixel_format(renderPipelineDescriptor, 0, pixelFormat);
    mt_renderPipeline_descriptor_set_sample_count(renderPipelineDescriptor, sampleCount);
    mt_renderPipeline_descriptor_set_depth_attachment_pixel_format(renderPipelineDescriptor, MTPixelFormatDepth32Float);
    
    engine->renderPipelineState = mt_device_renderPipeline_state_new(engine->device, renderPipelineDescriptor, &error);
    
    if (!engine->renderPipelineState) {
        printf("Failed to create render pipeline state:: %s\n", mt_error_get_localized_description(error));
        return -1;
    }
    
    MTDepthStencilDescriptor* depthStencilDescriptor = mt_depth_stencil_descriptor_new();
    mt_depth_stencil_descriptor_set_depth_compare_function(depthStencilDescriptor, MTCompareFunctionLessEqual);
    mt_depth_stencil_descriptor_set_is_depth_write_enabled(depthStencilDescriptor, true);
    
    MTDepthStencilState* depthStencilState = mt_device_depth_stencil_sate_new(engine->device, depthStencilDescriptor);
    mt_release(depthStencilDescriptor);
    
    mt_release(renderPipelineDescriptor);
    mt_release(vertFunction);
    mt_release(fragFunction);
    
    create_depth_and_msaa_textures();

    engine->renderPassDescriptor = mt_renderpass_descriptor_new();
    
    engine->colorAttachments = mt_renderpass_color_attachment_get_color_attachments(engine->renderPassDescriptor);
    MTRenderPassColorAttachmentDescriptor* colorAttachment = mt_renderpass_get_color_attachment_at_index(engine->colorAttachments, 0);
    engine->depthAttachment = mt_renderpass_depth_attachment_get_depth_attachment(engine->renderPassDescriptor);
    
    engine->drawable = platform_get_next_drawable();
    
    mt_renderpass_color_attachment_set_texture(colorAttachment, engine->msaaRenderTargetTexture);
    mt_renderpass_color_attachment_set_resolve_texture(colorAttachment, platform_get_next_drawable_texture(engine->drawable));
    mt_renderpass_color_attachment_set_loadAction(colorAttachment, MTLoadActionClear);
    mt_renderpass_color_attachment_set_storeAction(colorAttachment, MTStoreActionMultisampleResolve);
    mt_renderpass_color_attachment_set_clearColor(colorAttachment, mt_clear_color_make(41.0f/255.0f, 42.0f/255.0f, 48.0f/255.0f, 1.0));
    
    mt_renderpass_depth_attachment_set_texture(engine->depthAttachment, engine->depthTexture);
    mt_renderpass_depth_attachment_set_loadAction(engine->depthAttachment, MTLoadActionClear);
    mt_renderpass_depth_attachment_set_storeAction(engine->depthAttachment, MTStoreActionDontCare);
    mt_renderpass_depth_attachment_set_clear_depth(engine->depthAttachment, 1.0);
    

    // Timing
   mach_timebase_info_data_t machTimebaseInfoData;
   mach_timebase_info(&machTimebaseInfoData);
   assert(machTimebaseInfoData.denom != 0);
   double currentTimeInSeconds = osxGetCurrentTimeInSeconds(machTimebaseInfoData);

    while (isRunning){
        
//        dispatch_semaphore_wait(uniformBufferSemaphore, DISPATCH_TIME_FOREVER);
        
        double previousTimeInSeconds = currentTimeInSeconds;
        currentTimeInSeconds = osxGetCurrentTimeInSeconds(machTimebaseInfoData);
        float dt = currentTimeInSeconds - previousTimeInSeconds;

        if(dt > (1.f / 60.f))
            dt = (1.f / 60.f);
        
        if(!platform_pump_messages()){
            isRunning = false;
        }
        
        // Modulate player's y-position
//        vfloat2 playerPos = {};
//        const float posCycleAmplitude = 0.5f;
//        const float posCyclePeriod = 3.f; // in seconds
//        const float posCycleFreq = 2 * M_PI / posCyclePeriod;
//        playerPos.y = posCycleAmplitude * sinf(posCycleFreq * currentTimeInSeconds);
//
//        // Cycle player color
//        vfloat4 playerColor;
//        const float colorCyclePeriod = 5.f; //in seconds
//        const float colorCycleFreq = 2 * M_PI / colorCyclePeriod;
//        playerColor.r = 0.5f * (sinf(colorCycleFreq * currentTimeInSeconds) + 1);
//        playerColor.g = 1 - playerColor.r;
//        playerColor.b = 0.f;
//        playerColor.a = 1.f;
//
//        // Update uniforms
//        Uniforms uniforms;
//        uniforms.pos = playerPos;
//        uniforms.color = playerColor;
//        memcpy(mt_buffer_get_contents(uniformBuffers[currentUniformBufferIndex]), &uniforms, sizeof(Uniforms));

        MTAutoreleasePool* pool =  mt_autoreleasepool_new();
        mt_autoreleasepool_init(pool);
        
        engine->drawable = platform_get_next_drawable();
        
        MTCommandBuffer* cmdBuffer = mt_commandBuffer_new(cmd_queue);
        
        update_renderPass_descriptor();
        
        MTRenderCommandEncoder* renderCommandEncoder = mt_renderCommand_encoder_new(cmdBuffer,  engine->renderPassDescriptor);
        
        mt_renderCommand_encoder_set_viewport(renderCommandEncoder, mt_viewport_make(0, 0,
                                                                           platform_get_drawable_width(),
                                                                           platform_get_drawable_height(),
                                                                           0, 1));
        
//        encodeRenderCommand(renderCommandEncoder);
        // Moves the Cube 1 unit down the negative Z-axis
        simd_float4x4 translationMatrix =  matrix4x4_translation(0, 0.0,-1.0);

    //    float angleInDegrees = glfwGetTime()/2.0 * 45;
        float angleInDegrees = (currentTimeInSeconds / 2.0f) * 45.0;
        float angleInRadians = angleInDegrees * M_PI / 180.0f;
        matrix_float4x4 rotationMatrix = matrix4x4_rotation(angleInRadians, 0.0, 1.0, 0.0);

        matrix_float4x4 modelMatrix = simd_mul(translationMatrix, rotationMatrix);

    //    float time = glfwGetTime();
        float time = currentTimeInSeconds;
        float oscillation = sin(time);  // oscillates between -1 and 1
        float zPosition = 1.5 + 1.5 * oscillation;  // maps oscillation to range [0, 3]

        simd_float3 R = {1, 0, 0}; // Unit-Right
        simd_float3 U = {0, 1, 0}; // Unit-Up
        simd_float3 F = {0, 0,-1}; // Unit-Forward
        simd_float3 P = {0, 0, 1}; // Camera Position in World Space

        matrix_float4x4 viewMatrix = matrix_make_rows(R.x, R.y, R.z, simd_dot(-R, P),
                                                      U.x, U.y, U.z, simd_dot(-U, P),
                                                     -F.x,-F.y,-F.z, simd_dot( F, P),
                                                      0, 0, 0, 1);

        float aspectRatio = (platform_get_drawable_width() / platform_get_drawable_height());
        float fov = 90 * (M_PI / 180.0f);
        float nearZ = 0.1f;
        float farZ = 100.0f;
        
        matrix_float4x4 perspectiveMatrix = matrix_perspective_right_hand(fov, aspectRatio, nearZ, farZ);
        TransformationData transformationData = { modelMatrix, viewMatrix, perspectiveMatrix };
        memcpy(mt_buffer_get_contents(transformationBuffer), &transformationData, sizeof(transformationData));
        
        mt_renderCommand_encoder_set_front_facing_winding(renderCommandEncoder, MTWindingCounterClockwise);
//        mt_renderCommand_encoder_set_cull_mode(renderCommandEncoder, MTCullModeBack);
        mt_renderCommand_encoder_set_pipeline_state(renderCommandEncoder, engine->renderPipelineState);
        mt_renderCommand_encoder_set_depth_stencil_state(renderCommandEncoder, depthStencilState);
        mt_renderCommand_encoder_set_vertex_buffer(renderCommandEncoder, cubeVertexBuffer, 0, 0);
        mt_renderCommand_encoder_set_vertex_buffer(renderCommandEncoder, transformationBuffer, 0, 1);
        mt_renderCommand_encoder_set_fragment_texture_at_index(renderCommandEncoder, grassTexture->texture, 0);
//        mt_renderCommand_encoder_set_triangle_fill_mode(renderCommandEncoder, MTTriangleFillModeLines);
        mt_renderCommand_encoder_draw_primitives(renderCommandEncoder, MTPrimitiveTypeTriangle, 0, sizeof(cubeVertices)/sizeof(cubeVertices[0]));
     
        mt_renderCommand_encoder_end_encoding(renderCommandEncoder);
        
        mt_commandBuffer_present_drawable(cmdBuffer, engine->drawable);
        
//        dispatch_semaphore_signal(uniformBufferSemaphore);
        
        mt_commandBuffer_commit(cmdBuffer);
        
        mt_commandBuffer_wait_until_completed(cmdBuffer);
        
        mt_autoreleasepool_release(pool);

//        currentUniformBufferIndex = (currentUniformBufferIndex + 1) % MAX_FRAMES_IN_FLIGHT;
    }
    
    mt_release(engine->renderPassDescriptor);
    mt_release(cmd_queue);
    mt_release(engine->renderPipelineState);
    free(grassTexture);
    
    free(systems->event_system);
    free(systems);
    
    platform_system_shutdown();
    event_system_shutdown(0);
    
    return 0;
}

/**
    DEBUG NOTE:
    To check for memory leaks using the terminal.
    cd into the executable directory and ENABLE MallocStackLogging by running:
    export MallocStackLogging=1
    Then RUN:
    leaks --atExit --list -- ./"Metal C"
    
    __This will list out any memory leaks in the terminal the moment you terminate the application.
 */
