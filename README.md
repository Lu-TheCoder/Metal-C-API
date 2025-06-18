# Apple's Metal Graphics API For C.
This is the unofficial Metal Graphics API implementation for C. This API takes inspiration from the C++ Metal-CPP implementation which you can find at https://github.com/bkaradzic/metal-cpp .
This API is for developers seeking to integrate or simply use Metal in their game engines or graphics rendering projects without having to use Objective-c or Swift in their C codebase.

<img width="1277" alt="Screenshot 2025-06-18 at 19 15 47" src="https://github.com/user-attachments/assets/f8f5b292-07fe-4263-81a9-d434e660d52a" /> 
<img width="1277" alt="Screenshot 2025-06-18 at 19 18 23" src="https://github.com/user-attachments/assets/ddf4cd85-3578-4cf8-93aa-c703785391e0" />

![Screen Recording 2024-06-04 at 20 40 15](https://github.com/Lu-TheCoder/Metal-C-API/assets/90724319/e7e6b8ae-378e-4c07-90b9-de645c5ff0c2)

## Disclaimer
This API IS NOT PRODUCTION READY! and still in it's early development stage. Therefore use at your own risk!

# Basic Usage.

```c
// Load Metal C Header files:
#include "Metal/Metal.h"
#include "Metal/Foundation/Foundation.h"
#include "Metal/QuartzCore/CAMetalLayer.h"

int main() {

  // window initialization code goes here...
  ...

  MTDevice device = mt_create_system_default_device();
  if(!device){
    printf("Error: Failed to create device\n");
    return false;
  }

  MTCommandQueue command_queue = mt_device_create_command_queue(device);
  if(!command_queue){
    printf("Error: Failed to create command queue\n");
    return false;
  }
  
  // Retrieve your compiled metallib shader
  MTURL fileURL = mt_bundle_url_for_resource_(mt_string_from_utf8("default"), mt_string_from_utf8("metallib"));

  // Create your shader library
  MTError error = NULL;
  MTLibrary library = mt_device_create_library_withURL(state_ptr->device, fileURL, error);
  if(!library){
      printf("Failed to load library. Error %s\n", nsErrorLocalizedDescription(error));
  }
  
  MTFunction vertFunction = mt_library_create_function(state_ptr->library, mt_string_from_utf8("vert"));
  MTFunction fragFunction = mt_library_create_function(state_ptr->library, mt_string_from_utf8("frag"));

  // free library (no longer needed) 
  mt_release(library);

  float vertexData[] = {
      // x, y,
      -0.5f,  0.5f,
      -0.5f, -0.5f,
       0.5f, -0.5f,
      -0.5f,  0.5f,
       0.5f, -0.5f,
       0.5f,  0.5f
  };
  
  MTBuffer vertexBuffer = mt_device_create_buffer_with_bytes(device, vertexData, sizeof(vertexData), MTResourceCPUCacheModeDefaultCache);

  MTVertexDescriptor vertDesc = mt_vertex_descriptor_create();
  // Set your vertex attributes
  mt_vertex_descriptor_set_vertex_attribute_format(state_ptr->vertDesc, VertexAttributeIndex_Default_Position, MTVertexFormatFloat2);
  mt_vertex_descriptor_set_vertex_attribute_offset(vertDesc, VertexAttributeIndex_Default_Position, 0);
  mt_vertex_descriptor_set_vertex_attribute_buffer_index(vertDesc, VertexAttributeIndex_Default_Position, VertexBufferIndex_Attributes);
  // set your vertex layout
  mt_vertex_descriptor_set_vertex_layout_stride(vertDesc, VertexBufferIndex_Attributes, sizeof(Vertex3D));
  mt_vertex_descriptor_set_vertex_layout_step_rate(vertDesc, VertexBufferIndex_Attributes, 1);
  mt_vertex_descriptor_set_vertex_layout_step_function(vertDesc, VertexBufferIndex_Attributes, MTVertexStepFunctionPerVertex);

  // setup render pipeline descriptor
  MTRenderPipelineDescriptor renderPipelineDesc = mt_render_pipeline_descriptor_create();
  mt_render_pipeline_descriptor_set_label(renderPipelineDesc, "Default Render Pipeline");
  mt_render_pipeline_descriptor_set_vertex_function(renderPipelineDesc, vertFunction);
  mt_render_pipeline_descriptor_set_fragment_function(renderPipelineDesc, fragFunction);
  mt_render_pipeline_descriptor_set_vertex_descriptor(renderPipelineDesc, vertDesc);
  mt_render_pipeline_descriptor_set_color_attachments_pixel_format(renderPipelineDesc, 0, MTPixelFormatBGRA8Unorm);

  // create render pipeline state
  MTRenderPipelineState renderPipelineState = mt_device_create_render_pipeline_state(device, renderPipelineDesc, &error);
  
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

    CAMetalDrawable drawable = platform_get_next_drawable();
    
    MTRenderPassDescriptor renderPass = mt_renderpass_descriptor_new();
    MTCommandBuffer cmdBuffer = mt_command_queue_create_commandBuffer(queue);

    // Set color attachments
    mt_renderpass_color_attachments_set_texture(renderPass, 0, platform_get_next_drawable_texture(drawable));
    mt_renderpass_color_attachments_set_load_action(renderPass, 0, MTLoadActionClear);
    mt_renderpass_color_attachments_set_store_action(renderPass, 0, MTStoreActionMultisampleResolve);
    mt_renderpass_color_attachments_set_clear_color(renderPass, 0, mt_clear_color_create(42.0f/255.0f, 41.0f/255.0f, 43.0f/255.0f, 1.0f));

    MTRenderCommandEncoder renderCommandEncoder = mt_renderCommand_encoder_new(cmdBuffer, renderPass);
    mt_release(renderPass);

    mt_renderCommand_encoder_set_viewport(state_ptr->command_encoder, mt_viewport_make(
                                                                    0, 0,
                                                                    platform_get_drawable_width(state_ptr->current_window),
                                                                    platform_get_drawable_height(state_ptr->current_window),
                                                                    0, 1));  
    
    mt_renderCommand_encoder_set_pipeline_state(renderCommandEncoder, renderPipelineState);
    // bind vertex buffer
    mt_renderCommand_encoder_set_vertex_buffer(renderCommandEncoder, vertexBuffer, 0, VertexBufferIndex_Attributes);
    // draw geometry
    mt_renderCommand_encoder_draw_primitives(renderCommandEncoder, MTPrimitiveTypeTriangle, 0, 6);
    
    mt_renderCommand_encoder_end_encoding(renderCommandEncoder);
    mt_commandBuffer_present_drawable(cmdBuffer, drawable);
    mt_commandBuffer_commit(cmdBuffer);
    
    mt_commandBuffer_wait_until_completed(cmdBuffer);

    // release per frame resources
    mt_release(cmdBuffer);
    mt_release(renderCommandEncoder);
    mt_release(drawable);
  
  }

  // your shutdown/cleanup code goes here
  ...

  return 0;
}
```

# Contributions
If you want to help me build this API feel free to clone and create a PR. However please note no real C codebase standard has been set yet as everything is still in experimental stage.
Macros and function pointers are all over the place for now but in future releases will be properly utilised and any code repetition will be reduced. No inline functions have been added either, again they will soon follow once most of the API is working and thoroughly tested.

