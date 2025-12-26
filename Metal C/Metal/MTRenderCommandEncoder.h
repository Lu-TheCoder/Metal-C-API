//
//  MTRenderCommandEncoder.h
//  Metal C
//
//  Created by Lungile Maseko on 2024/04/29.
//

#pragma once
#include <stdint.h>
#include "MTDepthStencil.h"
#include "MTRenderPass.h"
#include "MTRenderPipeline.h"
#include "MTCommandBuffer.h"
#include "MTStageInputOutputDescriptor.h"

typedef enum MTPrimitiveType {
    MTPrimitiveTypePoint = 0,
    MTPrimitiveTypeLine = 1,
    MTPrimitiveTypeLineStrip = 2,
    MTPrimitiveTypeTriangle = 3,
    MTPrimitiveTypeTriangleStrip = 4,
} MTPrimitiveType;

typedef enum MTVisibilityResultMode {
    MTVisibilityResultModeDisabled = 0,
    MTVisibilityResultModeBoolean = 1,
    MTVisibilityResultModeCounting = 2,
} MTVisibilityResultMode;

typedef struct MTScissorRect {
    unsigned long x;
    unsigned long y;
    unsigned long width;
    unsigned long height;
} MTScissorRect;

typedef struct MTViewport {
    double originX;
    double originY;
    double width;
    double height;
    double znear;
    double zfar;
} MTViewport;

typedef enum MTCullMode {
    MTCullModeNone = 0,
    MTCullModeFront = 1,
    MTCullModeBack = 2,
} MTCullMode;

typedef enum MTWinding {
    MTWindingClockwise = 0,
    MTWindingCounterClockwise = 1,
} MTWinding;

typedef enum MTDepthClipMode {
    MTDepthClipModeClip = 0,
    MTDepthClipModeClamp = 1,
} MTDepthClipMode;

typedef enum MTTriangleFillMode {
    MTTriangleFillModeFill = 0,
    MTTriangleFillModeLines = 1,
} MTTriangleFillMode;

typedef struct MTDrawPrimitivesIndirectArguments {
    uint32_t vertexCount;
    uint32_t instanceCount;
    uint32_t vertexStart;
    uint32_t baseInstance;
} MTDrawPrimitivesIndirectArguments;

typedef struct MTDrawIndexedPrimitivesIndirectArguments {
    uint32_t indexCount;
    uint32_t instanceCount;
    uint32_t indexStart;
    int32_t  baseVertex;
    uint32_t baseInstance;
} MTDrawIndexedPrimitivesIndirectArguments;

typedef struct MTVertexAmplificationViewMapping {
    uint32_t viewportArrayIndexOffset;
    uint32_t renderTargetArrayIndexOffset;
} MTVertexAmplificationViewMapping;

typedef struct MTDrawPatchIndirectArguments {
    uint32_t patchCount;
    uint32_t instanceCount;
    uint32_t patchStart;
    uint32_t baseInstance;
} MTDrawPatchIndirectArguments;

typedef struct MTQuadTessellationFactorsHalf {
    uint16_t edgeTessellationFactor[4];
    uint16_t insideTessellationFactor[2];
} MTQuadTessellationFactorsHalf;

typedef struct MTTriangleTessellationFactorsHalf {
    uint16_t edgeTessellationFactor[3];
    uint16_t insideTessellationFactor;
} MTTriangleTessellationFactorsHalf;

typedef enum MTRenderStages: unsigned long {
    MTLRenderStageVertex   = (1UL << 0),
    MTLRenderStageFragment = (1UL << 1),
    MTLRenderStageTile     = (1UL << 2),
    MTLRenderStageObject   = (1UL << 3),
    MTLRenderStageMesh     = (1UL << 4),
} MTRenderStages;

typedef void* MTRenderCommandEncoder;
typedef void* MTBuffer;
typedef void* MTVisibleFunctionTable;
typedef void* MTIntersectionFunctionTable;
typedef void* MTAccelerationStructure;

// MARK: - Encoder Creation/Lifecycle

MT_INLINE MTRenderCommandEncoder mt_renderCommand_encoder_new(MTCommandBuffer cmdBuf, MTRenderPassDescriptor renderpassDesc) {
    return MT_MSG_SEND_1(id, cmdBuf, MT_SEL("renderCommandEncoderWithDescriptor:"), id, renderpassDesc);
}

MT_INLINE void mt_renderCommand_encoder_end_encoding(MTRenderCommandEncoder encoder) {
    MT_MSG_SEND(void, encoder, MT_SEL("endEncoding"));
}

MT_INLINE void mt_renderCommand_encoder_set_pipeline_state(MTRenderCommandEncoder encoder, MTRenderPipelineState pipelineState) {
    MT_MSG_SEND_1(void, encoder, MT_SEL("setRenderPipelineState:"), id, pipelineState);
}

// MARK: - Viewport Helpers

MT_INLINE MTViewport mt_viewport_make(double origin_x, double origin_y, double width, double height, double znear, double zfar) {
    MTViewport viewport = {
        .originX = origin_x,
        .originY = origin_y,
        .width = width,
        .height = height,
        .znear = znear,
        .zfar = zfar,
    };
    return viewport;
}

// MARK: - Vertex Buffer Functions

MT_INLINE void mt_renderCommand_encoder_set_vertex_buffer(MTRenderCommandEncoder render_cmd_enc, MTBuffer buffer, unsigned long offset, unsigned long at_index) {
    MT_MSG_SEND_3(void, render_cmd_enc, MT_SEL("setVertexBuffer:offset:atIndex:"), id, buffer, unsigned long, offset, unsigned long, at_index);
}

MT_INLINE void mt_renderCommand_encoder_set_vertex_bytes(MTRenderCommandEncoder render_cmd_enc, const void* bytes, unsigned long length, unsigned long at_index) {
    MT_MSG_SEND_3(void, render_cmd_enc, MT_SEL("setVertexBytes:length:atIndex:"), const void*, bytes, unsigned long, length, unsigned long, at_index);
}

MT_INLINE void mt_renderCommand_encoder_set_vertex_buffer_offset(MTRenderCommandEncoder render_cmd_enc, unsigned long offset, unsigned long index) {
    MT_MSG_SEND_2(void, render_cmd_enc, MT_SEL("setVertexBufferOffset:atIndex:"), unsigned long, offset, unsigned long, index);
}

// Struct arg - explicit cast
MT_INLINE void mt_renderCommand_encoder_set_vertex_buffers(MTRenderCommandEncoder render_cmd_enc, MTBuffer const* buffers, const unsigned long* offsets, MTRange range) {
    ((void (*)(id, SEL, const void*, const unsigned long*, MTRange))objc_msgSend)(
        (id)render_cmd_enc, MT_SEL("setVertexBuffers:offsets:withRange:"), buffers, offsets, range);
}

MT_INLINE void mt_renderCommand_encoder_set_vertex_buffer_stride(MTRenderCommandEncoder render_cmd_enc, MTBuffer buffer, unsigned long offset, unsigned long stride, unsigned long index) {
    MT_MSG_SEND_4(void, render_cmd_enc, MT_SEL("setVertexBuffer:offset:attributeStride:atIndex:"), id, buffer, unsigned long, offset, unsigned long, stride, unsigned long, index);
}

// Struct arg - explicit cast
MT_INLINE void mt_renderCommand_encoder_set_vertex_buffers_stride(MTRenderCommandEncoder render_cmd_enc, void* const* buffers, const unsigned long* offsets, const unsigned long* strides, MTRange range) {
    ((void (*)(id, SEL, void* const*, const unsigned long*, const unsigned long*, MTRange))objc_msgSend)(
        (id)render_cmd_enc, MT_SEL("setVertexBuffers:offsets:attributeStrides:withRange:"), buffers, offsets, strides, range);
}

MT_INLINE void mt_renderCommand_encoder_set_vertex_buffer_offset_stride(MTRenderCommandEncoder render_cmd_enc, unsigned long offset, unsigned long stride, unsigned long index) {
    MT_MSG_SEND_3(void, render_cmd_enc, MT_SEL("setVertexBufferOffset:attributeStride:atIndex:"), unsigned long, offset, unsigned long, stride, unsigned long, index);
}

MT_INLINE void mt_renderCommand_encoder_set_vertex_bytes_stride(MTRenderCommandEncoder render_cmd_enc, const void* bytes, unsigned long length, unsigned long stride, unsigned long index) {
    MT_MSG_SEND_4(void, render_cmd_enc, MT_SEL("setVertexBytes:length:attributeStride:atIndex:"), const void*, bytes, unsigned long, length, unsigned long, stride, unsigned long, index);
}

// MARK: - Draw Primitives

MT_INLINE void mt_renderCommand_encoder_draw_primitives(MTRenderCommandEncoder render_cmd_enc, MTPrimitiveType type, unsigned long vertex_start, unsigned long vertex_count) {
    MT_MSG_SEND_3(void, render_cmd_enc, MT_SEL("drawPrimitives:vertexStart:vertexCount:"), MTPrimitiveType, type, unsigned long, vertex_start, unsigned long, vertex_count);
}

MT_INLINE void mt_renderCommand_encoder_draw_indexed_primitives(MTRenderCommandEncoder render_cmd_enc, MTPrimitiveType primitive_type, unsigned long index_count, MTIndexType index_type, const MTBuffer index_buffer, uintptr_t index_buffer_offset) {
    MT_MSG_SEND_5(void, render_cmd_enc, MT_SEL("drawIndexedPrimitives:indexCount:indexType:indexBuffer:indexBufferOffset:"), MTPrimitiveType, primitive_type, unsigned long, index_count, MTIndexType, index_type, id, index_buffer, uintptr_t, index_buffer_offset);
}

MT_INLINE void mt_renderCommand_encoder_draw_indexed_primitives_with_instance_count(MTRenderCommandEncoder render_cmd_enc, MTPrimitiveType primitive_type, unsigned long index_count, MTIndexType index_type, const MTBuffer index_buffer, uintptr_t index_buffer_offset, uintptr_t instance_count) {
    MT_MSG_SEND_6(void, render_cmd_enc, MT_SEL("drawIndexedPrimitives:indexCount:indexType:indexBuffer:indexBufferOffset:instanceCount:"), MTPrimitiveType, primitive_type, unsigned long, index_count, MTIndexType, index_type, id, index_buffer, uintptr_t, index_buffer_offset, uintptr_t, instance_count);
}

// MARK: - Vertex Textures

MT_INLINE void mt_renderCommand_encoder_set_vertex_texture(MTRenderCommandEncoder render_cmd_enc, MTTexture texture, NSUInteger index) {
    MT_MSG_SEND_2(void, render_cmd_enc, MT_SEL("setVertexTexture:atIndex:"), id, texture, NSUInteger, index);
}

// Struct arg - explicit cast
MT_INLINE void mt_renderCommand_encoder_set_vertex_textures(MTRenderCommandEncoder render_cmd_enc, MTTexture const* textures, MTRange range) {
    ((void (*)(id, SEL, const void*, MTRange))objc_msgSend)((id)render_cmd_enc, MT_SEL("setVertexTextures:withRange:"), textures, range);
}

// MARK: - Vertex Samplers

MT_INLINE void mt_renderCommand_encoder_set_vertex_sampler_state(MTRenderCommandEncoder render_cmd_enc, MTSamplerState sampler, NSUInteger index) {
    MT_MSG_SEND_2(void, render_cmd_enc, MT_SEL("setVertexSamplerState:atIndex:"), id, sampler, NSUInteger, index);
}

// Struct arg - explicit cast
MT_INLINE void mt_renderCommand_encoder_set_vertex_sampler_states(MTRenderCommandEncoder render_cmd_enc, MTSamplerState const* samplers, MTRange range) {
    ((void (*)(id, SEL, const void*, MTRange))objc_msgSend)((id)render_cmd_enc, MT_SEL("setVertexSamplerStates:withRange:"), samplers, range);
}

MT_INLINE void mt_renderCommand_encoder_set_vertex_sampler_state_lod(MTRenderCommandEncoder render_cmd_enc, MTSamplerState sampler, float lod_min, float lod_max, NSUInteger index) {
    MT_MSG_SEND_4(void, render_cmd_enc, MT_SEL("setVertexSamplerState:lodMinClamp:lodMaxClamp:atIndex:"), id, sampler, float, lod_min, float, lod_max, NSUInteger, index);
}

// Struct arg - explicit cast
MT_INLINE void mt_renderCommand_encoder_set_vertex_sampler_states_lod(MTRenderCommandEncoder render_cmd_enc, MTSamplerState const* samplers, const float* lod_min_clamps, const float* lod_max_clamps, MTRange range) {
    ((void (*)(id, SEL, const void*, const float*, const float*, MTRange))objc_msgSend)(
        (id)render_cmd_enc, MT_SEL("setVertexSamplerStates:lodMinClamps:lodMaxClamps:withRange:"), samplers, lod_min_clamps, lod_max_clamps, range);
}

// MARK: - Vertex Function Tables

MT_INLINE void mt_renderCommand_encoder_set_vertex_visible_function_table(MTRenderCommandEncoder render_cmd_enc, MTVisibleFunctionTable function_table, NSUInteger buffer_index) {
    MT_MSG_SEND_2(void, render_cmd_enc, MT_SEL("setVertexVisibleFunctionTable:atBufferIndex:"), id, function_table, NSUInteger, buffer_index);
}

// Struct arg - explicit cast
MT_INLINE void mt_renderCommand_encoder_set_vertex_visible_function_tables(MTRenderCommandEncoder render_cmd_enc, MTVisibleFunctionTable const* tables, MTRange range) {
    ((void (*)(id, SEL, const void*, MTRange))objc_msgSend)((id)render_cmd_enc, MT_SEL("setVertexVisibleFunctionTables:withBufferRange:"), tables, range);
}

MT_INLINE void mt_renderCommand_encoder_set_vertex_intersection_function_table(MTRenderCommandEncoder render_cmd_enc, MTIntersectionFunctionTable table, NSUInteger buffer_index) {
    MT_MSG_SEND_2(void, render_cmd_enc, MT_SEL("setVertexIntersectionFunctionTable:atBufferIndex:"), id, table, NSUInteger, buffer_index);
}

// Struct arg - explicit cast
MT_INLINE void mt_renderCommand_encoder_set_vertex_intersection_function_tables(MTRenderCommandEncoder render_cmd_enc, MTIntersectionFunctionTable const* tables, MTRange range) {
    ((void (*)(id, SEL, const void*, MTRange))objc_msgSend)((id)render_cmd_enc, MT_SEL("setVertexIntersectionFunctionTables:withBufferRange:"), tables, range);
}

MT_INLINE void mt_renderCommand_encoder_set_vertex_acceleration_structure(MTRenderCommandEncoder render_cmd_enc, MTAccelerationStructure accel_struct, NSUInteger buffer_index) {
    MT_MSG_SEND_2(void, render_cmd_enc, MT_SEL("setVertexAccelerationStructure:atBufferIndex:"), id, accel_struct, NSUInteger, buffer_index);
}

// MARK: - Viewport & Rasterization State

// Struct arg - explicit cast
MT_INLINE void mt_renderCommand_encoder_set_viewport(MTRenderCommandEncoder render_cmd_enc, MTViewport viewport) {
    ((void (*)(id, SEL, MTViewport))objc_msgSend)((id)render_cmd_enc, MT_SEL("setViewport:"), viewport);
}

MT_INLINE void mt_renderCommand_encoder_set_viewports(MTRenderCommandEncoder render_cmd_enc, const MTViewport* viewports, NSUInteger count) {
    MT_MSG_SEND_2(void, render_cmd_enc, MT_SEL("setViewports:count:"), const MTViewport*, viewports, NSUInteger, count);
}

MT_INLINE void mt_renderCommand_encoder_set_front_facing_winding(MTRenderCommandEncoder render_cmd_enc, MTWinding winding) {
    MT_MSG_SEND_1(void, render_cmd_enc, MT_SEL("setFrontFacingWinding:"), MTWinding, winding);
}

MT_INLINE void mt_renderCommand_encoder_set_vertex_amplification_count(MTRenderCommandEncoder render_cmd_enc, NSUInteger count, const MTVertexAmplificationViewMapping* view_mappings) {
    MT_MSG_SEND_2(void, render_cmd_enc, MT_SEL("setVertexAmplificationCount:viewMappings:"), NSUInteger, count, const MTVertexAmplificationViewMapping*, view_mappings);
}

MT_INLINE void mt_renderCommand_encoder_set_cull_mode(MTRenderCommandEncoder render_cmd_enc, MTCullMode cull_mode) {
    MT_MSG_SEND_1(void, render_cmd_enc, MT_SEL("setCullMode:"), MTCullMode, cull_mode);
}

MT_INLINE void mt_renderCommand_encoder_set_depth_clip_mode(MTRenderCommandEncoder render_cmd_enc, MTDepthClipMode clip_mode) {
    MT_MSG_SEND_1(void, render_cmd_enc, MT_SEL("setDepthClipMode:"), MTDepthClipMode, clip_mode);
}

MT_INLINE void mt_renderCommand_encoder_set_depth_bias(MTRenderCommandEncoder render_cmd_enc, float depth_bias, float slope_scale, float clamp) {
    MT_MSG_SEND_3(void, render_cmd_enc, MT_SEL("setDepthBias:slopeScale:clamp:"), float, depth_bias, float, slope_scale, float, clamp);
}

// Struct arg - explicit cast
MT_INLINE void mt_renderCommand_encoder_set_scissor_rect(MTRenderCommandEncoder render_cmd_enc, MTScissorRect rect) {
    ((void (*)(id, SEL, MTScissorRect))objc_msgSend)((id)render_cmd_enc, MT_SEL("setScissorRect:"), rect);
}

MT_INLINE void mt_renderCommand_encoder_set_scissor_rects(MTRenderCommandEncoder render_cmd_enc, const MTScissorRect* scissor_rects, NSUInteger count) {
    MT_MSG_SEND_2(void, render_cmd_enc, MT_SEL("setScissorRects:count:"), const MTScissorRect*, scissor_rects, NSUInteger, count);
}

MT_INLINE void mt_renderCommand_encoder_set_triangle_fill_mode(MTRenderCommandEncoder render_cmd_enc, MTTriangleFillMode fill_mode) {
    MT_MSG_SEND_1(void, render_cmd_enc, MT_SEL("setTriangleFillMode:"), MTTriangleFillMode, fill_mode);
}

// MARK: - Fragment Buffer Functions

MT_INLINE void mt_renderCommand_encoder_set_fragment_bytes(MTRenderCommandEncoder render_cmd_enc, const void* bytes, NSUInteger length, NSUInteger index) {
    MT_MSG_SEND_3(void, render_cmd_enc, MT_SEL("setFragmentBytes:length:atIndex:"), const void*, bytes, NSUInteger, length, NSUInteger, index);
}

MT_INLINE void mt_renderCommand_encoder_set_fragment_buffer(MTRenderCommandEncoder render_cmd_enc, MTBuffer buffer, NSUInteger offset, NSUInteger index) {
    MT_MSG_SEND_3(void, render_cmd_enc, MT_SEL("setFragmentBuffer:offset:atIndex:"), id, buffer, NSUInteger, offset, NSUInteger, index);
}

MT_INLINE void mt_renderCommand_encoder_set_fragment_buffer_offset(MTRenderCommandEncoder render_cmd_enc, NSUInteger offset, NSUInteger index) {
    MT_MSG_SEND_2(void, render_cmd_enc, MT_SEL("setFragmentBufferOffset:atIndex:"), NSUInteger, offset, NSUInteger, index);
}

// Struct arg - explicit cast
MT_INLINE void mt_renderCommand_encoder_set_fragment_buffers(MTRenderCommandEncoder render_cmd_enc, const MTBuffer* buffers, const NSUInteger* offsets, MTRange range) {
    ((void (*)(id, SEL, const void*, const NSUInteger*, MTRange))objc_msgSend)(
        (id)render_cmd_enc, MT_SEL("setFragmentBuffers:offsets:withRange:"), buffers, offsets, range);
}

// MARK: - Fragment Textures

MT_INLINE void mt_renderCommand_encoder_set_fragment_texture(MTRenderCommandEncoder render_cmd_enc, MTTexture texture, NSUInteger index) {
    MT_MSG_SEND_2(void, render_cmd_enc, MT_SEL("setFragmentTexture:atIndex:"), id, texture, NSUInteger, index);
}

// Struct arg - explicit cast
MT_INLINE void mt_renderCommand_encoder_set_fragment_textures(MTRenderCommandEncoder render_cmd_enc, const MTTexture* textures, MTRange range) {
    ((void (*)(id, SEL, const void*, MTRange))objc_msgSend)((id)render_cmd_enc, MT_SEL("setFragmentTextures:withRange:"), textures, range);
}

// MARK: - Fragment Samplers

MT_INLINE void mt_renderCommand_encoder_set_fragment_sampler_state(MTRenderCommandEncoder render_cmd_enc, MTSamplerState sampler, NSUInteger index) {
    MT_MSG_SEND_2(void, render_cmd_enc, MT_SEL("setFragmentSamplerState:atIndex:"), id, sampler, NSUInteger, index);
}

// Struct arg - explicit cast
MT_INLINE void mt_renderCommand_encoder_set_fragment_sampler_states(MTRenderCommandEncoder render_cmd_enc, const MTSamplerState* samplers, MTRange range) {
    ((void (*)(id, SEL, const void*, MTRange))objc_msgSend)((id)render_cmd_enc, MT_SEL("setFragmentSamplerStates:withRange:"), samplers, range);
}

MT_INLINE void mt_renderCommand_encoder_set_fragment_sampler_state_lod(MTRenderCommandEncoder render_cmd_enc, MTSamplerState sampler, float lod_min, float lod_max, NSUInteger index) {
    MT_MSG_SEND_4(void, render_cmd_enc, MT_SEL("setFragmentSamplerState:lodMinClamp:lodMaxClamp:atIndex:"), id, sampler, float, lod_min, float, lod_max, NSUInteger, index);
}

// Struct arg - explicit cast
MT_INLINE void mt_renderCommand_encoder_set_fragment_sampler_states_lod(MTRenderCommandEncoder render_cmd_enc, const MTSamplerState* samplers, const float* lod_min_clamps, const float* lod_max_clamps, MTRange range) {
    ((void (*)(id, SEL, const void*, const float*, const float*, MTRange))objc_msgSend)(
        (id)render_cmd_enc, MT_SEL("setFragmentSamplerStates:lodMinClamps:lodMaxClamps:withRange:"), samplers, lod_min_clamps, lod_max_clamps, range);
}

// MARK: - Fragment Function Tables

MT_INLINE void mt_renderCommand_encoder_set_fragment_visible_function_table(MTRenderCommandEncoder render_cmd_enc, MTVisibleFunctionTable table, NSUInteger index) {
    MT_MSG_SEND_2(void, render_cmd_enc, MT_SEL("setFragmentVisibleFunctionTable:atBufferIndex:"), id, table, NSUInteger, index);
}

// Struct arg - explicit cast
MT_INLINE void mt_renderCommand_encoder_set_fragment_visible_function_tables(MTRenderCommandEncoder render_cmd_enc, const MTVisibleFunctionTable* tables, MTRange range) {
    ((void (*)(id, SEL, const void*, MTRange))objc_msgSend)((id)render_cmd_enc, MT_SEL("setFragmentVisibleFunctionTables:withBufferRange:"), tables, range);
}

MT_INLINE void mt_renderCommand_encoder_set_fragment_intersection_function_table(MTRenderCommandEncoder render_cmd_enc, MTIntersectionFunctionTable table, NSUInteger index) {
    MT_MSG_SEND_2(void, render_cmd_enc, MT_SEL("setFragmentIntersectionFunctionTable:atBufferIndex:"), id, table, NSUInteger, index);
}

// Struct arg - explicit cast
MT_INLINE void mt_renderCommand_encoder_set_fragment_intersection_function_tables(MTRenderCommandEncoder render_cmd_enc, const MTIntersectionFunctionTable* tables, MTRange range) {
    ((void (*)(id, SEL, const void*, MTRange))objc_msgSend)((id)render_cmd_enc, MT_SEL("setFragmentIntersectionFunctionTables:withBufferRange:"), tables, range);
}

MT_INLINE void mt_renderCommand_encoder_set_fragment_acceleration_structure(MTRenderCommandEncoder render_cmd_enc, MTAccelerationStructure accel_struct, NSUInteger index) {
    MT_MSG_SEND_2(void, render_cmd_enc, MT_SEL("setFragmentAccelerationStructure:atBufferIndex:"), id, accel_struct, NSUInteger, index);
}

// MARK: - Blending & Depth/Stencil State

MT_INLINE void mt_renderCommand_encoder_set_blend_color(MTRenderCommandEncoder render_cmd_enc, float red, float green, float blue, float alpha) {
    MT_MSG_SEND_4(void, render_cmd_enc, MT_SEL("setBlendColorRed:green:blue:alpha:"), float, red, float, green, float, blue, float, alpha);
}

MT_INLINE void mt_renderCommand_encoder_set_depth_stencil_state(MTRenderCommandEncoder render_cmd_enc, MTDepthStencilState state) {
    MT_MSG_SEND_1(void, render_cmd_enc, MT_SEL("setDepthStencilState:"), id, state);
}

MT_INLINE void mt_renderCommand_encoder_set_stencil_reference_value(MTRenderCommandEncoder render_cmd_enc, uint32_t ref_value) {
    MT_MSG_SEND_1(void, render_cmd_enc, MT_SEL("setStencilReferenceValue:"), uint32_t, ref_value);
}

MT_INLINE void mt_renderCommand_encoder_set_stencil_reference_values(MTRenderCommandEncoder render_cmd_enc, uint32_t front, uint32_t back) {
    MT_MSG_SEND_2(void, render_cmd_enc, MT_SEL("setStencilFrontReferenceValue:backReferenceValue:"), uint32_t, front, uint32_t, back);
}

// MARK: - Visibility Result

MT_INLINE void mt_renderCommand_encoder_set_visibility_result_mode(MTRenderCommandEncoder render_cmd_enc, MTVisibilityResultMode mode, NSUInteger offset) {
    MT_MSG_SEND_2(void, render_cmd_enc, MT_SEL("setVisibilityResultMode:offset:"), MTVisibilityResultMode, mode, NSUInteger, offset);
}

// MARK: - Store Actions

MT_INLINE void mt_renderCommand_encoder_set_color_store_action(MTRenderCommandEncoder render_cmd_enc, MTStoreAction store_action, NSUInteger color_attachment_index) {
    MT_MSG_SEND_2(void, render_cmd_enc, MT_SEL("setColorStoreAction:atIndex:"), MTStoreAction, store_action, NSUInteger, color_attachment_index);
}

MT_INLINE void mt_renderCommand_encoder_set_depth_store_action(MTRenderCommandEncoder render_cmd_enc, MTStoreAction store_action) {
    MT_MSG_SEND_1(void, render_cmd_enc, MT_SEL("setDepthStoreAction:"), MTStoreAction, store_action);
}

MT_INLINE void mt_renderCommand_encoder_set_stencil_store_action(MTRenderCommandEncoder render_cmd_enc, MTStoreAction store_action) {
    MT_MSG_SEND_1(void, render_cmd_enc, MT_SEL("setStencilStoreAction:"), MTStoreAction, store_action);
}

MT_INLINE void mt_renderCommand_encoder_set_color_store_action_options(MTRenderCommandEncoder render_cmd_enc, MTStoreActionOptions options, NSUInteger color_attachment_index) {
    MT_MSG_SEND_2(void, render_cmd_enc, MT_SEL("setColorStoreActionOptions:atIndex:"), MTStoreActionOptions, options, NSUInteger, color_attachment_index);
}

MT_INLINE void mt_renderCommand_encoder_set_depth_store_action_options(MTRenderCommandEncoder render_cmd_enc, MTStoreActionOptions options) {
    MT_MSG_SEND_1(void, render_cmd_enc, MT_SEL("setDepthStoreActionOptions:"), MTStoreActionOptions, options);
}

MT_INLINE void mt_renderCommand_encoder_set_stencil_store_action_options(MTRenderCommandEncoder render_cmd_enc, MTStoreActionOptions options) {
    MT_MSG_SEND_1(void, render_cmd_enc, MT_SEL("setStencilStoreActionOptions:"), MTStoreActionOptions, options);
}

// MARK: - Object Stage Functions

MT_INLINE void mt_renderCommand_encoder_set_object_bytes(MTRenderCommandEncoder render_cmd_enc, const void *bytes, NSUInteger length, NSUInteger index) {
    MT_MSG_SEND_3(void, render_cmd_enc, MT_SEL("setObjectBytes:length:atIndex:"), const void*, bytes, NSUInteger, length, NSUInteger, index);
}

MT_INLINE void mt_renderCommand_encoder_set_object_buffer(MTRenderCommandEncoder render_cmd_enc, MTBuffer buffer, NSUInteger offset, NSUInteger index) {
    MT_MSG_SEND_3(void, render_cmd_enc, MT_SEL("setObjectBuffer:offset:atIndex:"), id, buffer, NSUInteger, offset, NSUInteger, index);
}

MT_INLINE void mt_renderCommand_encoder_set_object_buffer_offset(MTRenderCommandEncoder render_cmd_enc, NSUInteger offset, NSUInteger index) {
    MT_MSG_SEND_2(void, render_cmd_enc, MT_SEL("setObjectBufferOffset:atIndex:"), NSUInteger, offset, NSUInteger, index);
}

MT_INLINE void mt_renderCommand_encoder_set_object_texture(MTRenderCommandEncoder render_cmd_enc, MTTexture texture, NSUInteger index) {
    MT_MSG_SEND_2(void, render_cmd_enc, MT_SEL("setObjectTexture:atIndex:"), id, texture, NSUInteger, index);
}

MT_INLINE void mt_renderCommand_encoder_set_object_sampler_state(MTRenderCommandEncoder render_cmd_enc, MTSamplerState sampler, NSUInteger index) {
    MT_MSG_SEND_2(void, render_cmd_enc, MT_SEL("setObjectSamplerState:atIndex:"), id, sampler, NSUInteger, index);
}

// MARK: - Tessellation

MT_INLINE void mt_renderCommand_encoder_set_tessellation_factor_scale(MTRenderCommandEncoder encoder, float scale) {
    MT_MSG_SEND_1(void, encoder, MT_SEL("setTessellationFactorScale:"), float, scale);
}
