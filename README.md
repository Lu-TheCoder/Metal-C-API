# Apple's Metal Graphics API For C.
This is the unofficial Metal Graphics API implementation for C. This API takes inspiration from the C++ Metal-CPP implementation which you can find at https://github.com/bkaradzic/metal-cpp .
This API is for developers seeking to integrate or simply use Metal in their game engines or graphics rendering projects.


![Screen Recording 2024-06-04 at 20 40 15](https://github.com/Lu-TheCoder/Metal-C-API/assets/90724319/e7e6b8ae-378e-4c07-90b9-de645c5ff0c2)

## Disclaimer
This API IS NOT PRODUCTION READY! and still in it's early development stage. Therefore use at your own risk!

# Basic Usage.

```c
#include "Metal/Metal.h"

int main() {

  // window initialization code goes here...
  ...

  MTDevice* device = mt_create_system_default_device();

  // Automatically find the path of compiled shader
  // -> Useful if project is not in Xcode. 
  MTBundle* bundle = mt_bundle_new();
  MTString* lib_path = mt_bundle_get_lib_path(bundle, mt_string_utf8String("default"), mt_string_utf8String("metallib"));
  MTURL* fileURL = mt_url_init_with_path(lib_path);
  
  MTError* error = NULL;
  MTLibrary* library = mt_library_new_library_withURL(device, fileURL, &error);

  if(!library){
      printf("Failed to load library. Error %s\n", nsErrorLocalizedDescription(error));
  }
  
  MTFunction* vertFunction = mt_library_new_function(library, nsUtf8String("vert"));
  MTFunction* fragFunction = mt_library_new_function(library, nsUtf8String("frag"));
    
  mtRelease(library);

  float vertexData[] = {
      // x, y,
      -0.5f,  0.5f,
      -0.5f, -0.5f,
       0.5f, -0.5f,
      -0.5f,  0.5f,
       0.5f, -0.5f,
       0.5f,  0.5f
  };
  
  MTBuffer* vertexBuffer = mt_buffer_new_bufferWithBytes(device, vertexData, sizeof(vertexData), MTResourceCPUCacheModeDefaultCache);

  MTVertexDescriptor* vertDesc = mt_vertexDescriptor_new();
  MTVertexAttributeDescriptorArray* attributes = mt_vertexDescriptor_get_attributes(vertDesc);
  MTVertexBufferLayoutDescriptorArray* layouts = mt_vertexDescriptor_get_layouts(vertDesc);

  // Attributes
  mt_vertexAttribute_set_format(attributes, VertexAttributeIndex_Position, MTVertexFormatFloat2);
  mt_vertexAttribute_set_offset(attributes, VertexAttributeIndex_Position, 0);
  mt_vertexAttribute_set_buffer_index(attributes, VertexAttributeIndex_Position, VertexBufferIndex_Attributes);
  // Layout
  mt_vertexBufferLayout_set_stride(layouts, VertexBufferIndex_Attributes, 2 * sizeof(float));
  mt_vertexBufferLayout_set_stepRate(layouts, VertexBufferIndex_Attributes, 1);
  mt_vertexBufferLayout_set_stepFunction(layouts, VertexBufferIndex_Attributes, MTVertexStepFunctionPerVertex);
  
  MTRenderPipelineDescriptor* renderPipelineDesc = mt_renderPipeline_descriptor_new();
  mt_renderPipeline_descriptor_set_vertex_function(renderPipelineDesc, vertFunction);
  mt_renderPipeline_descriptor_set_fragment_function(renderPipelineDesc, fragFunction);
  mt_renderPipeline_descriptor_set_vertex_descriptor(renderPipelineDesc, vertDesc);
  mt_renderPipeline_descriptor_set_color_attachments_pixel_format(renderPipelineDesc, 0, (MTPixelFormat)platform_get_drawable_pixelFormat());
  
  MTRenderPipelineState* renderPipelineState = mt_renderPipelineState_new(device, renderPipelineDesc, &error);
  
  if (!renderPipelineState) {
      printf("Failed to create pipeline state. Error: %s\n", nsErrorLocalizedDescription(error));
      return(1);
  }

  mt_release(vertFunction);
  mt_release(fragFunction);
  mt_release(vertDesc);
  mt_release(renderPipelineDesc);

  // Game/Window loop
  while (isRunning) {

    // Start of Autoreleasepool
    NSAutoreleasePool* pool =  mtlNewAutoreleasepool();
    mtAutoreleasePoolInit(pool);

    void* drawable = platform_get_next_drawable();
    
    MTRenderPassDescriptor* renderPass = mt_renderpass_descriptor_new();
    MTCommandBuffer* cmdBuffer = mt_commandBuffer_new(queue);
    
    MTRenderPassColorAttachmentDescriptorArray* colorAttachments = mt_renderpass_color_attachment_get_color_attachments(renderPass);
    MTRenderPassColorAttachmentDescriptor* colorAttachment = mt_renderpass_get_color_attachment_at_index(colorAttachments, 0);
    mt_renderpass_color_attachment_set_texture(colorAttachment, platform_get_next_drawable_texture(drawable));
    mt_renderpass_color_attachment_set_loadAction(colorAttachment, MTLoadActionClear);
    mt_renderpass_color_attachment_set_storeAction(colorAttachment, MTStoreActionStore);
    mt_renderpass_color_attachment_set_clearColor(colorAttachment, mt_clear_color_make(0.1, 0.1, 0.1, 1.0));
    
    MTRenderCommandEncoder* renderCommandEncoder = mt_renderCommand_encoder_new(cmdBuffer, renderPass);
    mt_release(renderPass);
    
   mt_renderCommand_encoder_set_viewport(renderCommandEncoder, mt_viewport_make(0, 0,
                                                                       platform_get_drawable_width(),
                                                                       platform_get_drawable_height(),
                                                                       0, 1));
    
    mt_renderCommand_encoder_set_pipeline_state(renderCommandEncoder, renderPipelineState);
    mt_renderCommand_encoder_set_vertex_buffer(renderCommandEncoder, vertexBuffer, 0, VertexBufferIndex_Attributes);
    mt_renderCommand_encoder_set_draw_primitives(renderCommandEncoder, MTPrimitiveTypeTriangle, 0, 6);
    
    mt_renderCommand_encoder_end_encoding(renderCommandEncoder);
    
    mt_commandBuffer_present_drawable(cmdBuffer, drawable);
    
    mt_commandBuffer_commit(cmdBuffer);
    
    mt_commandBuffer_wait_until_completed(cmdBuffer);

    // end of Autoreleasepool.
    mtAutoreleasePoolRelease(pool);
  
  }

  // your shutdown/cleanup code goes here
  ...

  return 0;
}
```

# Contributions
If you want to help me build this API feel free to clone and create a PR. However please note no real C codebase standard has been set yet as everything is still in experimental stage.
Macros and function pointers are all over the place for now but in future releases will be properly utilised and any code repetition will be reduced. No inline functions have been added either, again they will soon follow once most of the API is working and thoroughly tested.

