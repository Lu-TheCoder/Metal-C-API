//
//  MT4RenderPipeline.h
//  Metal C
//
//  MTL4RenderPipelineDescriptor — input to mt4_compiler_create_render_pipeline_state.
//
//  Differences from the classic descriptor:
//   - Functions are set as *descriptors* (MT4LibraryFunctionDescriptor, created
//     via MT4Compiler.h), not MTFunction objects. Pass them where an
//     MT4FunctionDescriptor is expected (the library descriptor is a subtype —
//     cast it: (MT4FunctionDescriptor)libFnDesc).
//   - Color-attachment blending is expressed with MT4BlendState (enabled/
//     disabled) on a dedicated MT4RenderPipelineColorAttachmentDescriptor.
//

#pragma once
#include "MTFoundation/defines.h"
#include "MTFoundation/MTString.h"  // mt_object_set_label
#include "MTTypes.h"                // NSUInteger
#include "MTRenderPipeline.h"       // MTBlendFactor, MTBlendOperation, MTColorWriteMask, MTPrimitiveTopologyClass
#include "MTPixelFormat.h"          // MTPixelFormat

// ---- MTL4 pipeline enums -------------------------------------------------

typedef enum MT4BlendState : long {
    MT4BlendStateDisabled = 0,
    MT4BlendStateEnabled  = 1,
} MT4BlendState;

typedef enum MT4AlphaToCoverageState : long {
    MT4AlphaToCoverageStateDisabled = 0,
    MT4AlphaToCoverageStateEnabled  = 1,
} MT4AlphaToCoverageState;

typedef enum MT4AlphaToOneState : long {
    MT4AlphaToOneStateDisabled = 0,
    MT4AlphaToOneStateEnabled  = 1,
} MT4AlphaToOneState;

typedef enum MT4IndirectCommandBufferSupportState : long {
    MT4IndirectCommandBufferSupportStateDisabled = 0,
    MT4IndirectCommandBufferSupportStateEnabled  = 1,
} MT4IndirectCommandBufferSupportState;

// ---- Color attachment ----------------------------------------------------

MT_INLINE MT4RenderPipelineColorAttachmentDescriptor mt4_render_pipeline_descriptor_get_color_attachment(MT4RenderPipelineDescriptor desc, NSUInteger index) {
    id arr = MT_MSG_SEND(void*, desc, MT_SEL("colorAttachments"));
    return MT_MSG_SEND_1(void*, arr, MT_SEL("objectAtIndexedSubscript:"), NSUInteger, index);
}

MT_INLINE void mt4_color_attachment_set_pixel_format(MT4RenderPipelineColorAttachmentDescriptor ca, MTPixelFormat format) {
    MT_MSG_SEND_1(void, ca, MT_SEL("setPixelFormat:"), MTPixelFormat, format);
}

MT_INLINE void mt4_color_attachment_set_blending_state(MT4RenderPipelineColorAttachmentDescriptor ca, MT4BlendState state) {
    MT_MSG_SEND_1(void, ca, MT_SEL("setBlendingState:"), MT4BlendState, state);
}

MT_INLINE void mt4_color_attachment_set_source_rgb_blend_factor(MT4RenderPipelineColorAttachmentDescriptor ca, MTBlendFactor factor) {
    MT_MSG_SEND_1(void, ca, MT_SEL("setSourceRGBBlendFactor:"), MTBlendFactor, factor);
}

MT_INLINE void mt4_color_attachment_set_destination_rgb_blend_factor(MT4RenderPipelineColorAttachmentDescriptor ca, MTBlendFactor factor) {
    MT_MSG_SEND_1(void, ca, MT_SEL("setDestinationRGBBlendFactor:"), MTBlendFactor, factor);
}

MT_INLINE void mt4_color_attachment_set_rgb_blend_operation(MT4RenderPipelineColorAttachmentDescriptor ca, MTBlendOperation op) {
    MT_MSG_SEND_1(void, ca, MT_SEL("setRgbBlendOperation:"), MTBlendOperation, op);
}

MT_INLINE void mt4_color_attachment_set_source_alpha_blend_factor(MT4RenderPipelineColorAttachmentDescriptor ca, MTBlendFactor factor) {
    MT_MSG_SEND_1(void, ca, MT_SEL("setSourceAlphaBlendFactor:"), MTBlendFactor, factor);
}

MT_INLINE void mt4_color_attachment_set_destination_alpha_blend_factor(MT4RenderPipelineColorAttachmentDescriptor ca, MTBlendFactor factor) {
    MT_MSG_SEND_1(void, ca, MT_SEL("setDestinationAlphaBlendFactor:"), MTBlendFactor, factor);
}

MT_INLINE void mt4_color_attachment_set_alpha_blend_operation(MT4RenderPipelineColorAttachmentDescriptor ca, MTBlendOperation op) {
    MT_MSG_SEND_1(void, ca, MT_SEL("setAlphaBlendOperation:"), MTBlendOperation, op);
}

MT_INLINE void mt4_color_attachment_set_write_mask(MT4RenderPipelineColorAttachmentDescriptor ca, MTColorWriteMask mask) {
    MT_MSG_SEND_1(void, ca, MT_SEL("setWriteMask:"), MTColorWriteMask, mask);
}

// ---- Render pipeline descriptor ------------------------------------------

MT_INLINE MT4RenderPipelineDescriptor mt4_render_pipeline_descriptor_create(void) {
    return MT_ALLOC_INIT("MTL4RenderPipelineDescriptor");
}

MT_INLINE void mt4_render_pipeline_descriptor_set_label(MT4RenderPipelineDescriptor desc, const char* label) {
    mt_object_set_label(desc, label);
}

MT_INLINE void mt4_render_pipeline_descriptor_set_vertex_function_descriptor(MT4RenderPipelineDescriptor desc, MT4FunctionDescriptor fn) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setVertexFunctionDescriptor:"), id, fn);
}

MT_INLINE void mt4_render_pipeline_descriptor_set_fragment_function_descriptor(MT4RenderPipelineDescriptor desc, MT4FunctionDescriptor fn) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setFragmentFunctionDescriptor:"), id, fn);
}

MT_INLINE void mt4_render_pipeline_descriptor_set_vertex_descriptor(MT4RenderPipelineDescriptor desc, MTVertexDescriptor vertex_desc) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setVertexDescriptor:"), id, vertex_desc);
}

MT_INLINE void mt4_render_pipeline_descriptor_set_raster_sample_count(MT4RenderPipelineDescriptor desc, NSUInteger count) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setRasterSampleCount:"), NSUInteger, count);
}

MT_INLINE void mt4_render_pipeline_descriptor_set_rasterization_enabled(MT4RenderPipelineDescriptor desc, bool enabled) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setRasterizationEnabled:"), BOOL, enabled);
}

MT_INLINE void mt4_render_pipeline_descriptor_set_max_vertex_amplification_count(MT4RenderPipelineDescriptor desc, NSUInteger count) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setMaxVertexAmplificationCount:"), NSUInteger, count);
}

MT_INLINE void mt4_render_pipeline_descriptor_set_input_primitive_topology(MT4RenderPipelineDescriptor desc, MTPrimitiveTopologyClass topology) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setInputPrimitiveTopology:"), MTPrimitiveTopologyClass, topology);
}

MT_INLINE void mt4_render_pipeline_descriptor_set_alpha_to_coverage_state(MT4RenderPipelineDescriptor desc, MT4AlphaToCoverageState state) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setAlphaToCoverageState:"), MT4AlphaToCoverageState, state);
}

MT_INLINE void mt4_render_pipeline_descriptor_set_alpha_to_one_state(MT4RenderPipelineDescriptor desc, MT4AlphaToOneState state) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setAlphaToOneState:"), MT4AlphaToOneState, state);
}

MT_INLINE void mt4_render_pipeline_descriptor_set_support_indirect_command_buffers(MT4RenderPipelineDescriptor desc, MT4IndirectCommandBufferSupportState state) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setSupportIndirectCommandBuffers:"), MT4IndirectCommandBufferSupportState, state);
}

MT_INLINE void mt4_render_pipeline_descriptor_reset(MT4RenderPipelineDescriptor desc) {
    MT_MSG_SEND(void, desc, MT_SEL("reset"));
}

// Attach compile-time options (e.g. to request reflection). See MT4PipelineState.h.
MT_INLINE void mt4_render_pipeline_descriptor_set_options(MT4RenderPipelineDescriptor desc, MT4PipelineOptions options) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setOptions:"), id, options);
}
