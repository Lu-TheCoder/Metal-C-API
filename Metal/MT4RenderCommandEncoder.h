//
//  MT4RenderCommandEncoder.h
//  Metal C
//
//  MTL4RenderCommandEncoder — encodes a render pass in the Metal 4 model.
//  Obtain one from mt4_command_buffer_get_render_encoder(cmd, passDescriptor).
//
//  Key difference from the classic encoder: resources are bound through an
//  MTL4ArgumentTable (see MT4ArgumentTable.h) rather than setVertexBuffer:
//  etc. Bind the table with mt4_render_command_encoder_set_argument_table,
//  then issue draws. The pipeline state is a classic MTRenderPipelineState
//  (produced by the MTL4 compiler in a later stage).
//
//  Shared encoder operations (barriers, fences, debug groups, end_encoding)
//  live in MT4CommandEncoder.h — cast this encoder to MT4CommandEncoder.
//

#pragma once
#include "MTFoundation/defines.h"
#include "MTTypes.h"                  // NSUInteger, MTGPUAddress
#include "MTRenderCommandEncoder.h"   // MTPrimitiveType, MTViewport, MTScissorRect, MTCullMode,
                                      // MTWinding, MTTriangleFillMode, MTDepthClipMode,
                                      // MTVisibilityResultMode, MTRenderStages, MTIndexType
#include "MT4ArgumentTable.h"
#include "MT4Counters.h"              // MT4CounterHeap, MT4TimestampGranularity

// Options for suspending/resuming (parallel) render passes
// (Metal's MTL4RenderEncoderOptions).
typedef enum MT4RenderEncoderOptions : unsigned long {
    MT4RenderEncoderOptionNone       = 0,
    MT4RenderEncoderOptionSuspending = 1 << 0,
    MT4RenderEncoderOptionResuming   = 1 << 1,
} MT4RenderEncoderOptions;

// ---- Pipeline + binding --------------------------------------------------

MT_INLINE void mt4_render_command_encoder_set_pipeline_state(MT4RenderCommandEncoder encoder, MTRenderPipelineState pipeline) {
    MT_MSG_SEND_1(void, encoder, MT_SEL("setRenderPipelineState:"), id, pipeline);
}

// Bind an argument table, making its contents visible to the given shader stages.
MT_INLINE void mt4_render_command_encoder_set_argument_table(MT4RenderCommandEncoder encoder, MT4ArgumentTable table, MTRenderStages stages) {
    MT_MSG_SEND_2(void, encoder, MT_SEL("setArgumentTable:atStages:"), id, table, MTRenderStages, stages);
}

// ---- Fixed-function state ------------------------------------------------

MT_INLINE void mt4_render_command_encoder_set_viewport(MT4RenderCommandEncoder encoder, MTViewport viewport) {
    ((void (*)(id, SEL, MTViewport))objc_msgSend)((id)encoder, MT_SEL("setViewport:"), viewport);
}

MT_INLINE void mt4_render_command_encoder_set_scissor_rect(MT4RenderCommandEncoder encoder, MTScissorRect rect) {
    ((void (*)(id, SEL, MTScissorRect))objc_msgSend)((id)encoder, MT_SEL("setScissorRect:"), rect);
}

MT_INLINE void mt4_render_command_encoder_set_cull_mode(MT4RenderCommandEncoder encoder, MTCullMode mode) {
    MT_MSG_SEND_1(void, encoder, MT_SEL("setCullMode:"), MTCullMode, mode);
}

MT_INLINE void mt4_render_command_encoder_set_front_facing_winding(MT4RenderCommandEncoder encoder, MTWinding winding) {
    MT_MSG_SEND_1(void, encoder, MT_SEL("setFrontFacingWinding:"), MTWinding, winding);
}

MT_INLINE void mt4_render_command_encoder_set_triangle_fill_mode(MT4RenderCommandEncoder encoder, MTTriangleFillMode mode) {
    MT_MSG_SEND_1(void, encoder, MT_SEL("setTriangleFillMode:"), MTTriangleFillMode, mode);
}

MT_INLINE void mt4_render_command_encoder_set_depth_clip_mode(MT4RenderCommandEncoder encoder, MTDepthClipMode mode) {
    MT_MSG_SEND_1(void, encoder, MT_SEL("setDepthClipMode:"), MTDepthClipMode, mode);
}

MT_INLINE void mt4_render_command_encoder_set_depth_bias(MT4RenderCommandEncoder encoder, float bias, float slope_scale, float clamp) {
    MT_MSG_SEND_3(void, encoder, MT_SEL("setDepthBias:slopeScale:clamp:"), float, bias, float, slope_scale, float, clamp);
}

MT_INLINE void mt4_render_command_encoder_set_depth_stencil_state(MT4RenderCommandEncoder encoder, MTDepthStencilState state) {
    MT_MSG_SEND_1(void, encoder, MT_SEL("setDepthStencilState:"), id, state);
}

MT_INLINE void mt4_render_command_encoder_set_stencil_reference_value(MT4RenderCommandEncoder encoder, uint32_t value) {
    MT_MSG_SEND_1(void, encoder, MT_SEL("setStencilReferenceValue:"), uint32_t, value);
}

MT_INLINE void mt4_render_command_encoder_set_stencil_front_back_reference_value(MT4RenderCommandEncoder encoder, uint32_t front, uint32_t back) {
    MT_MSG_SEND_2(void, encoder, MT_SEL("setStencilFrontReferenceValue:backReferenceValue:"), uint32_t, front, uint32_t, back);
}

MT_INLINE void mt4_render_command_encoder_set_blend_color(MT4RenderCommandEncoder encoder, float red, float green, float blue, float alpha) {
    MT_MSG_SEND_4(void, encoder, MT_SEL("setBlendColorRed:green:blue:alpha:"), float, red, float, green, float, blue, float, alpha);
}

MT_INLINE void mt4_render_command_encoder_set_visibility_result_mode(MT4RenderCommandEncoder encoder, MTVisibilityResultMode mode, NSUInteger offset) {
    MT_MSG_SEND_2(void, encoder, MT_SEL("setVisibilityResultMode:offset:"), MTVisibilityResultMode, mode, NSUInteger, offset);
}

// ---- Store actions (override the render pass) ----------------------------

MT_INLINE void mt4_render_command_encoder_set_color_store_action(MT4RenderCommandEncoder encoder, MTStoreAction action, NSUInteger color_attachment_index) {
    MT_MSG_SEND_2(void, encoder, MT_SEL("setColorStoreAction:atIndex:"), MTStoreAction, action, NSUInteger, color_attachment_index);
}

MT_INLINE void mt4_render_command_encoder_set_depth_store_action(MT4RenderCommandEncoder encoder, MTStoreAction action) {
    MT_MSG_SEND_1(void, encoder, MT_SEL("setDepthStoreAction:"), MTStoreAction, action);
}

MT_INLINE void mt4_render_command_encoder_set_stencil_store_action(MT4RenderCommandEncoder encoder, MTStoreAction action) {
    MT_MSG_SEND_1(void, encoder, MT_SEL("setStencilStoreAction:"), MTStoreAction, action);
}

// ---- Draws ---------------------------------------------------------------

MT_INLINE void mt4_render_command_encoder_draw_primitives(MT4RenderCommandEncoder encoder, MTPrimitiveType type, NSUInteger vertex_start, NSUInteger vertex_count) {
    MT_MSG_SEND_3(void, encoder, MT_SEL("drawPrimitives:vertexStart:vertexCount:"), MTPrimitiveType, type, NSUInteger, vertex_start, NSUInteger, vertex_count);
}

MT_INLINE void mt4_render_command_encoder_draw_primitives_instanced(MT4RenderCommandEncoder encoder, MTPrimitiveType type, NSUInteger vertex_start, NSUInteger vertex_count, NSUInteger instance_count) {
    MT_MSG_SEND_4(void, encoder, MT_SEL("drawPrimitives:vertexStart:vertexCount:instanceCount:"), MTPrimitiveType, type, NSUInteger, vertex_start, NSUInteger, vertex_count, NSUInteger, instance_count);
}

MT_INLINE void mt4_render_command_encoder_draw_primitives_instanced_base(MT4RenderCommandEncoder encoder, MTPrimitiveType type, NSUInteger vertex_start, NSUInteger vertex_count, NSUInteger instance_count, NSUInteger base_instance) {
    MT_MSG_SEND_5(void, encoder, MT_SEL("drawPrimitives:vertexStart:vertexCount:instanceCount:baseInstance:"), MTPrimitiveType, type, NSUInteger, vertex_start, NSUInteger, vertex_count, NSUInteger, instance_count, NSUInteger, base_instance);
}

// Indexed draws — the index buffer is given by GPU address (Metal 4 change).
MT_INLINE void mt4_render_command_encoder_draw_indexed_primitives(MT4RenderCommandEncoder encoder, MTPrimitiveType type, NSUInteger index_count, MTIndexType index_type, MTGPUAddress index_buffer, NSUInteger index_buffer_length) {
    MT_MSG_SEND_5(void, encoder, MT_SEL("drawIndexedPrimitives:indexCount:indexType:indexBuffer:indexBufferLength:"), MTPrimitiveType, type, NSUInteger, index_count, MTIndexType, index_type, MTGPUAddress, index_buffer, NSUInteger, index_buffer_length);
}

MT_INLINE void mt4_render_command_encoder_draw_indexed_primitives_instanced(MT4RenderCommandEncoder encoder, MTPrimitiveType type, NSUInteger index_count, MTIndexType index_type, MTGPUAddress index_buffer, NSUInteger index_buffer_length, NSUInteger instance_count) {
    MT_MSG_SEND_6(void, encoder, MT_SEL("drawIndexedPrimitives:indexCount:indexType:indexBuffer:indexBufferLength:instanceCount:"), MTPrimitiveType, type, NSUInteger, index_count, MTIndexType, index_type, MTGPUAddress, index_buffer, NSUInteger, index_buffer_length, NSUInteger, instance_count);
}

// ---- Timestamp -----------------------------------------------------------

MT_INLINE void mt4_render_command_encoder_write_timestamp(MT4RenderCommandEncoder encoder, MT4TimestampGranularity granularity, MTRenderStages after_stage, MT4CounterHeap heap, NSUInteger index) {
    MT_MSG_SEND_4(void, encoder, MT_SEL("writeTimestampWithGranularity:afterStage:intoHeap:atIndex:"), MT4TimestampGranularity, granularity, MTRenderStages, after_stage, id, heap, NSUInteger, index);
}
