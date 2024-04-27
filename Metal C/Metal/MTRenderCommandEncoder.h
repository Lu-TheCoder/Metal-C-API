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
}MTPrimitiveType;

typedef enum MTVisibilityResultMode {
    MTVisibilityResultModeDisabled = 0,
    MTVisibilityResultModeBoolean = 1,
    MTVisibilityResultModeCounting = 2,
}MTVisibilityResultMode;

typedef struct MTScissorRect {
    unsigned long x;
    unsigned long y;
    unsigned long width;
    unsigned long height;
}MTScissorRect;

typedef struct MTViewport {
    double originX;
    double originY;
    double width;
    double height;
    double znear;
    double zfar;
}MTViewport;

typedef enum MTCullMode {
    MTCullModeNone = 0,
    MTCullModeFront = 1,
    MTCullModeBack = 2,
}MTCullMode;

typedef enum MTWinding {
    MTWindingClockwise = 0,
    MTWindingCounterClockwise = 1,
}MTWinding;

typedef enum MTDepthClipMode {
    MTDepthClipModeClip = 0,
    MTDepthClipModeClamp = 1,
}MTDepthClipMode;

typedef enum MTTriangleFillMode {
    MTTriangleFillModeFill = 0,
    MTTriangleFillModeLines = 1,
}MTTriangleFillMode;

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
    /* NOTE: edgeTessellationFactor and insideTessellationFactor are interpreted as half (16-bit floats) */
    uint16_t edgeTessellationFactor[4];
    uint16_t insideTessellationFactor[2];
} MTQuadTessellationFactorsHalf;

typedef struct MTTriangleTessellationFactorsHalf{
    /* NOTE: edgeTessellationFactor and insideTessellationFactor are interpreted as half (16-bit floats) */
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

MTRenderCommandEncoder mt_renderCommand_encoder_new(MTCommandBuffer cmdBuf, MTRenderPassDescriptor* renderpassDesc){
    SEL selRCEWDescSel = sel_getUid("renderCommandEncoderWithDescriptor:");
    return ms_send_void(cmdBuf, selRCEWDescSel, renderpassDesc);
}

void mt_renderCommand_encoder_end_encoding(MTRenderCommandEncoder renderCmdEncoder){
    SEL sel = sel_getUid("endEncoding");
     ms_send(renderCmdEncoder, sel);
}

void mt_renderCommand_encoder_set_pipeline_state(MTRenderCommandEncoder render_cmd_enc, MTRenderPipelineState pipeline_state){
    ms_send_void(render_cmd_enc, sel_getUid("setRenderPipelineState:"), pipeline_state);
}

MTViewport mt_viewport_make(double origin_x, double origin_y, double width, double height, double znear, double zfar)
{
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

MT_INLINE void mt_renderCommand_encoder_set_vertex_buffer(
    MTRenderCommandEncoder render_cmd_enc,
    MTBuffer* buffer,
    unsigned long offset,
    unsigned long at_index
) {
    typedef void (*SetVertexBufferFunc)(id, SEL, id, unsigned long, unsigned long);
    ((SetVertexBufferFunc)objc_msgSend)(
        (id)render_cmd_enc,
        sel_getUid("setVertexBuffer:offset:atIndex:"),
        (id)buffer,
        offset,
        at_index
    );
}

MT_INLINE void mt_renderCommand_encoder_set_vertex_bytes(
    MTRenderCommandEncoder render_cmd_enc,
    const void* bytes,
    unsigned long length,
    unsigned long at_index
) {
    typedef void (*SetVertexBytesFunc)(id, SEL, const void*, unsigned long, unsigned long);
    ((SetVertexBytesFunc)objc_msgSend)(
        (id)render_cmd_enc,
        sel_getUid("setVertexBytes:length:atIndex:"),
        bytes,
        length,
        at_index
    );
}

MT_INLINE void mt_renderCommand_encoder_set_vertex_buffer_offset(
    MTRenderCommandEncoder render_cmd_enc,
    unsigned long offset,
    unsigned long index
) {
    typedef void (*FuncType)(id, SEL, unsigned long, unsigned long);
    ((FuncType)objc_msgSend)(
        (id)render_cmd_enc,
        sel_getUid("setVertexBufferOffset:atIndex:"),
        offset,
        index
    );
}

MT_INLINE void mt_renderCommand_encoder_set_vertex_buffers(
    MTRenderCommandEncoder render_cmd_enc,
    MTBuffer const* buffers,
    const unsigned long* offsets,
    MTRange range
) {
    typedef void (*FuncType)(id, SEL, void* const*, const unsigned long*, MTRange);
    ((FuncType)objc_msgSend)(
        (id)render_cmd_enc,
        sel_getUid("setVertexBuffers:offsets:withRange:"),
        buffers,
        offsets,
        range
    );
}

MT_INLINE void mt_renderCommand_encoder_set_vertex_buffer_stride(
    MTRenderCommandEncoder render_cmd_enc,
    MTBuffer buffer,
    unsigned long offset,
    unsigned long stride,
    unsigned long index
) {
    typedef void (*FuncType)(id, SEL, id, unsigned long, unsigned long, unsigned long);
    ((FuncType)objc_msgSend)(
        (id)render_cmd_enc,
        sel_getUid("setVertexBuffer:offset:attributeStride:atIndex:"),
        (id)buffer,
        offset,
        stride,
        index
    );
}

MT_INLINE void mt_renderCommand_encoder_set_vertex_buffers_stride(
    MTRenderCommandEncoder render_cmd_enc,
    void* const* buffers,
    const unsigned long* offsets,
    const unsigned long* strides,
    MTRange range
) {
    typedef void (*FuncType)(id, SEL, void* const*, const unsigned long*, const unsigned long*, MTRange);
    ((FuncType)objc_msgSend)(
        (id)render_cmd_enc,
        sel_getUid("setVertexBuffers:offsets:attributeStrides:withRange:"),
        buffers,
        offsets,
        strides,
        range
    );
}

MT_INLINE void mt_renderCommand_encoder_set_vertex_buffer_offset_stride(
    MTRenderCommandEncoder render_cmd_enc,
    unsigned long offset,
    unsigned long stride,
    unsigned long index
) {
    typedef void (*FuncType)(id, SEL, unsigned long, unsigned long, unsigned long);
    ((FuncType)objc_msgSend)(
        (id)render_cmd_enc,
        sel_getUid("setVertexBufferOffset:attributeStride:atIndex:"),
        offset,
        stride,
        index
    );
}

MT_INLINE void mt_renderCommand_encoder_set_vertex_bytes_stride(
    MTRenderCommandEncoder render_cmd_enc,
    const void* bytes,
    unsigned long length,
    unsigned long stride,
    unsigned long index
) {
    typedef void (*FuncType)(id, SEL, const void*, unsigned long, unsigned long, unsigned long);
    ((FuncType)objc_msgSend)(
        (id)render_cmd_enc,
        sel_getUid("setVertexBytes:length:attributeStride:atIndex:"),
        bytes,
        length,
        stride,
        index
    );
}

MT_INLINE void mt_renderCommand_encoder_draw_primitives(
    MTRenderCommandEncoder render_cmd_enc,
    MTPrimitiveType type,
    unsigned long vertex_start,
    unsigned long vertex_count
) {
    typedef void (*DrawPrimitivesFunc)(
        id, SEL, MTPrimitiveType, unsigned long, unsigned long
    );
    DrawPrimitivesFunc func = (DrawPrimitivesFunc)objc_msgSend;
    func((id)render_cmd_enc,
         sel_getUid("drawPrimitives:vertexStart:vertexCount:"),
         type,
         vertex_start,
         vertex_count);
}

MT_INLINE void mt_renderCommand_encoder_draw_indexed_primitives(
    MTRenderCommandEncoder render_cmd_enc,
    MTPrimitiveType primitive_type,
    unsigned long index_count,
    MTIndexType index_type,
    const MTBuffer index_buffer,
    uintptr_t index_buffer_offset
) {
    typedef void (*DrawIndexedPrimitivesFunc)(
        id, SEL, MTPrimitiveType, unsigned long, MTIndexType, const MTBuffer, unsigned long
    );
    DrawIndexedPrimitivesFunc func = (DrawIndexedPrimitivesFunc)objc_msgSend;
    func((id)render_cmd_enc,
         sel_getUid("drawIndexedPrimitives:indexCount:indexType:indexBuffer:indexBufferOffset:"),
         primitive_type,
         index_count,
         index_type,
         index_buffer,
         index_buffer_offset);
}

MT_INLINE void mt_renderCommand_encoder_draw_indexed_primitives_with_instance_count(
    MTRenderCommandEncoder render_cmd_enc,
    MTPrimitiveType primitive_type,
    unsigned long index_count,
    MTIndexType index_type,
    const MTBuffer index_buffer,
    uintptr_t index_buffer_offset,
    uintptr_t instance_count
) {
    typedef void (*DrawIndexedPrimitivesInstancedFunc)(
        id, SEL, MTPrimitiveType, unsigned long, MTIndexType, const MTBuffer, unsigned long, unsigned long
    );
    DrawIndexedPrimitivesInstancedFunc func = (DrawIndexedPrimitivesInstancedFunc)objc_msgSend;
    func((id)render_cmd_enc,
         sel_getUid("drawIndexedPrimitives:indexCount:indexType:indexBuffer:indexBufferOffset:instanceCount:"),
         primitive_type,
         index_count,
         index_type,
         index_buffer,
         index_buffer_offset,
         instance_count);
}

MT_INLINE void mt_renderCommand_encoder_set_vertex_texture(
    MTRenderCommandEncoder render_cmd_enc,
    MTTexture texture,
    NSUInteger index
) {
    typedef void (*FuncType)(id, SEL, MTTexture, NSUInteger);
    ((FuncType)objc_msgSend)(
        (id)render_cmd_enc,
        sel_getUid("setVertexTexture:atIndex:"),
        texture,
        index
    );
}

MT_INLINE void mt_renderCommand_encoder_set_vertex_textures(
    MTRenderCommandEncoder render_cmd_enc,
    MTTexture const* textures,
    MTRange range
) {
    typedef void (*FuncType)(id, SEL, MTTexture const*, MTRange);
    ((FuncType)objc_msgSend)(
        (id)render_cmd_enc,
        sel_getUid("setVertexTextures:withRange:"),
        textures,
        range
    );
}

MT_INLINE void mt_renderCommand_encoder_set_vertex_sampler_state(
    MTRenderCommandEncoder render_cmd_enc,
    MTSamplerState sampler,
    NSUInteger index
) {
    typedef void (*FuncType)(id, SEL, MTSamplerState, NSUInteger);
    ((FuncType)objc_msgSend)(
        (id)render_cmd_enc,
        sel_getUid("setVertexSamplerState:atIndex:"),
        sampler,
        index
    );
}

MT_INLINE void mt_renderCommand_encoder_set_vertex_sampler_states(
    MTRenderCommandEncoder render_cmd_enc,
    MTSamplerState const* samplers,
    MTRange range
) {
    typedef void (*FuncType)(id, SEL, MTSamplerState const*, MTRange);
    ((FuncType)objc_msgSend)(
        (id)render_cmd_enc,
        sel_getUid("setVertexSamplerStates:withRange:"),
        samplers,
        range
    );
}

MT_INLINE void mt_renderCommand_encoder_set_vertex_sampler_state_lod(
    MTRenderCommandEncoder render_cmd_enc,
    MTSamplerState sampler,
    float lod_min,
    float lod_max,
    NSUInteger index
) {
    typedef void (*FuncType)(id, SEL, MTSamplerState, float, float, NSUInteger);
    ((FuncType)objc_msgSend)(
        (id)render_cmd_enc,
        sel_getUid("setVertexSamplerState:lodMinClamp:lodMaxClamp:atIndex:"),
        sampler,
        lod_min,
        lod_max,
        index
    );
}

MT_INLINE void mt_renderCommand_encoder_set_vertex_sampler_states_lod(
    MTRenderCommandEncoder render_cmd_enc,
    MTSamplerState const* samplers,
    const float* lod_min_clamps,
    const float* lod_max_clamps,
    MTRange range
) {
    typedef void (*FuncType)(id, SEL, MTSamplerState const*, const float*, const float*, MTRange);
    ((FuncType)objc_msgSend)(
        (id)render_cmd_enc,
        sel_getUid("setVertexSamplerStates:lodMinClamps:lodMaxClamps:withRange:"),
        samplers,
        lod_min_clamps,
        lod_max_clamps,
        range
    );
}

MT_INLINE void mt_renderCommand_encoder_set_vertex_visible_function_table(
    MTRenderCommandEncoder render_cmd_enc,
    MTVisibleFunctionTable function_table,
    NSUInteger buffer_index
) {
    typedef void (*FuncType)(id, SEL, MTVisibleFunctionTable, NSUInteger);
    ((FuncType)objc_msgSend)(
        (id)render_cmd_enc,
        sel_getUid("setVertexVisibleFunctionTable:atBufferIndex:"),
        function_table,
        buffer_index
    );
}

MT_INLINE void mt_renderCommand_encoder_set_vertex_visible_function_tables(
    MTRenderCommandEncoder render_cmd_enc,
    MTVisibleFunctionTable const* tables,
    MTRange range
) {
    typedef void (*FuncType)(id, SEL, MTVisibleFunctionTable const*, MTRange);
    ((FuncType)objc_msgSend)(
        (id)render_cmd_enc,
        sel_getUid("setVertexVisibleFunctionTables:withBufferRange:"),
        tables,
        range
    );
}

MT_INLINE void mt_renderCommand_encoder_set_vertex_intersection_function_table(
    MTRenderCommandEncoder render_cmd_enc,
    MTIntersectionFunctionTable table,
    NSUInteger buffer_index
) {
    typedef void (*FuncType)(id, SEL, MTIntersectionFunctionTable, NSUInteger);
    ((FuncType)objc_msgSend)(
        (id)render_cmd_enc,
        sel_getUid("setVertexIntersectionFunctionTable:atBufferIndex:"),
        table,
        buffer_index
    );
}

MT_INLINE void mt_renderCommand_encoder_set_vertex_intersection_function_tables(
    MTRenderCommandEncoder render_cmd_enc,
    MTIntersectionFunctionTable const* tables,
    MTRange range
) {
    typedef void (*FuncType)(id, SEL, MTIntersectionFunctionTable const*, MTRange);
    ((FuncType)objc_msgSend)(
        (id)render_cmd_enc,
        sel_getUid("setVertexIntersectionFunctionTables:withBufferRange:"),
        tables,
        range
    );
}

MT_INLINE void mt_renderCommand_encoder_set_vertex_acceleration_structure(
    MTRenderCommandEncoder render_cmd_enc,
    MTAccelerationStructure accel_struct,
    NSUInteger buffer_index
) {
    typedef void (*FuncType)(id, SEL, MTAccelerationStructure, NSUInteger);
    ((FuncType)objc_msgSend)(
        (id)render_cmd_enc,
        sel_getUid("setVertexAccelerationStructure:atBufferIndex:"),
        accel_struct,
        buffer_index
    );
}

MT_INLINE void mt_renderCommand_encoder_set_viewport(
    MTRenderCommandEncoder render_cmd_enc,
    MTViewport viewport
) {
    typedef void (*SetViewportFunc)(id, SEL, MTViewport);
    ((SetViewportFunc)objc_msgSend)(
        (id)render_cmd_enc,
        sel_getUid("setViewport:"),
        viewport
    );
}

MT_INLINE void mt_renderCommand_encoder_set_viewports(
    MTRenderCommandEncoder render_cmd_enc,
    const MTViewport* viewports,
    NSUInteger count
) {
    typedef void (*SetViewportsFunc)(id, SEL, const MTViewport*, NSUInteger);
    ((SetViewportsFunc)objc_msgSend)(
        (id)render_cmd_enc,
        sel_getUid("setViewports:count:"),
        viewports,
        count
    );
}

MT_INLINE void mt_renderCommand_encoder_set_front_facing_winding(
    MTRenderCommandEncoder render_cmd_enc,
    MTWinding winding
) {
    typedef void (*SetFrontFacingWindingFunc)(id, SEL, MTWinding);
    ((SetFrontFacingWindingFunc)objc_msgSend)(
        (id)render_cmd_enc,
        sel_getUid("setFrontFacingWinding:"),
        winding
    );
}

MT_INLINE void mt_renderCommand_encoder_set_vertex_amplification_count(
    MTRenderCommandEncoder render_cmd_enc,
    NSUInteger count,
    const MTVertexAmplificationViewMapping* view_mappings
) {
    typedef void (*SetVertexAmplificationCountFunc)(id, SEL, NSUInteger, const MTVertexAmplificationViewMapping*);
    ((SetVertexAmplificationCountFunc)objc_msgSend)(
        (id)render_cmd_enc,
        sel_getUid("setVertexAmplificationCount:viewMappings:"),
        count,
        view_mappings
    );
}

MT_INLINE void mt_renderCommand_encoder_set_cull_mode(
    MTRenderCommandEncoder render_cmd_enc,
    MTCullMode cull_mode
) {
    typedef void (*SetCullModeFunc)(id, SEL, MTCullMode);
    ((SetCullModeFunc)objc_msgSend)(
        (id)render_cmd_enc,
        sel_getUid("setCullMode:"),
        cull_mode
    );
}

MT_INLINE void mt_renderCommand_encoder_set_depth_clip_mode(
    MTRenderCommandEncoder render_cmd_enc,
    MTDepthClipMode clip_mode
) {
    typedef void (*SetDepthClipModeFunc)(id, SEL, MTDepthClipMode);
    ((SetDepthClipModeFunc)objc_msgSend)(
        (id)render_cmd_enc,
        sel_getUid("setDepthClipMode:"),
        clip_mode
    );
}

MT_INLINE void mt_renderCommand_encoder_set_depth_bias(
    MTRenderCommandEncoder render_cmd_enc,
    float depth_bias,
    float slope_scale,
    float clamp
) {
    typedef void (*SetDepthBiasFunc)(id, SEL, float, float, float);
    ((SetDepthBiasFunc)objc_msgSend)(
        (id)render_cmd_enc,
        sel_getUid("setDepthBias:slopeScale:clamp:"),
        depth_bias,
        slope_scale,
        clamp
    );
}

MT_INLINE void mt_renderCommand_encoder_set_scissor_rect(
    MTRenderCommandEncoder render_cmd_enc,
    MTScissorRect rect
) {
    typedef void (*SetScissorRectFunc)(id, SEL, MTScissorRect);
    ((SetScissorRectFunc)objc_msgSend)(
        (id)render_cmd_enc,
        sel_getUid("setScissorRect:"),
        rect
    );
}

MT_INLINE void mt_renderCommand_encoder_set_scissor_rects(
    MTRenderCommandEncoder render_cmd_enc,
    const MTScissorRect* scissor_rects,
    NSUInteger count
) {
    typedef void (*SetScissorRectsFunc)(id, SEL, const MTScissorRect*, NSUInteger);
    ((SetScissorRectsFunc)objc_msgSend)(
        (id)render_cmd_enc,
        sel_getUid("setScissorRects:count:"),
        scissor_rects,
        count
    );
}

MT_INLINE void mt_renderCommand_encoder_set_triangle_fill_mode(
    MTRenderCommandEncoder render_cmd_enc,
    MTTriangleFillMode fill_mode
) {
    typedef void (*SetTriangleFillModeFunc)(id, SEL, MTTriangleFillMode);
    ((SetTriangleFillModeFunc)objc_msgSend)(
        (id)render_cmd_enc,
        sel_getUid("setTriangleFillMode:"),
        fill_mode
    );
}

MT_INLINE void mt_renderCommand_encoder_set_fragment_bytes(
    MTRenderCommandEncoder render_cmd_enc,
    const void* bytes,
    NSUInteger length,
    NSUInteger index
) {
    typedef void (*SetFragmentBytesFunc)(id, SEL, const void*, NSUInteger, NSUInteger);
    ((SetFragmentBytesFunc)objc_msgSend)(
        (id)render_cmd_enc,
        sel_getUid("setFragmentBytes:length:atIndex:"),
        bytes,
        length,
        index
    );
}


MT_INLINE void mt_renderCommand_encoder_set_fragment_buffer(
    MTRenderCommandEncoder render_cmd_enc,
    MTBuffer buffer,
    NSUInteger offset,
    NSUInteger index
) {
    typedef void (*SetFragmentBufferFunc)(id, SEL, id, NSUInteger, NSUInteger);
    ((SetFragmentBufferFunc)objc_msgSend)(
        (id)render_cmd_enc,
        sel_getUid("setFragmentBuffer:offset:atIndex:"),
        (id)buffer,
        offset,
        index
    );
}

MT_INLINE void mt_renderCommand_encoder_set_fragment_buffer_offset(
    MTRenderCommandEncoder render_cmd_enc,
    NSUInteger offset,
    NSUInteger index
) {
    typedef void (*SetFragmentBufferOffsetFunc)(id, SEL, NSUInteger, NSUInteger);
    ((SetFragmentBufferOffsetFunc)objc_msgSend)(
        (id)render_cmd_enc,
        sel_getUid("setFragmentBufferOffset:atIndex:"),
        offset,
        index
    );
}

MT_INLINE void mt_renderCommand_encoder_set_fragment_buffers(
    MTRenderCommandEncoder render_cmd_enc,
    const MTBuffer* buffers,
    const NSUInteger* offsets,
    MTRange range
) {
    typedef void (*SetFragmentBuffersFunc)(id, SEL, const id*, const NSUInteger*, MTRange);
    ((SetFragmentBuffersFunc)objc_msgSend)(
        (id)render_cmd_enc,
        sel_getUid("setFragmentBuffers:offsets:withRange:"),
        (const id*)buffers,
        offsets,
        range
    );
}

MT_INLINE void mt_renderCommand_encoder_set_fragment_texture(
    MTRenderCommandEncoder render_cmd_enc,
    MTTexture texture,
    NSUInteger index
) {
    typedef void (*SetFragmentTextureFunc)(id, SEL, id, NSUInteger);
    ((SetFragmentTextureFunc)objc_msgSend)(
        (id)render_cmd_enc,
        sel_getUid("setFragmentTexture:atIndex:"),
        (id)texture,
        index
    );
}

MT_INLINE void mt_renderCommand_encoder_set_fragment_textures(
    MTRenderCommandEncoder render_cmd_enc,
    const MTTexture* textures,
    MTRange range
) {
    typedef void (*SetFragmentTexturesFunc)(id, SEL, const id*, MTRange);
    ((SetFragmentTexturesFunc)objc_msgSend)(
        (id)render_cmd_enc,
        sel_getUid("setFragmentTextures:withRange:"),
        (const id*)textures,
        range
    );
}

MT_INLINE void mt_renderCommand_encoder_set_fragment_sampler_state(
    MTRenderCommandEncoder render_cmd_enc,
    MTSamplerState sampler,
    NSUInteger index
) {
    typedef void (*SetFragmentSamplerStateFunc)(id, SEL, id, NSUInteger);
    ((SetFragmentSamplerStateFunc)objc_msgSend)(
        (id)render_cmd_enc,
        sel_getUid("setFragmentSamplerState:atIndex:"),
        (id)sampler,
        index
    );
}

MT_INLINE void mt_renderCommand_encoder_set_fragment_sampler_states(
    MTRenderCommandEncoder render_cmd_enc,
    const MTSamplerState* samplers,
    MTRange range
) {
    typedef void (*SetFragmentSamplerStatesFunc)(id, SEL, const id*, MTRange);
    ((SetFragmentSamplerStatesFunc)objc_msgSend)(
        (id)render_cmd_enc,
        sel_getUid("setFragmentSamplerStates:withRange:"),
        (const id*)samplers,
        range
    );
}

MT_INLINE void mt_renderCommand_encoder_set_fragment_sampler_state_lod(
    MTRenderCommandEncoder render_cmd_enc,
    MTSamplerState sampler,
    float lod_min,
    float lod_max,
    NSUInteger index
) {
    typedef void (*SetFragmentSamplerStateLODFunc)(id, SEL, id, float, float, NSUInteger);
    ((SetFragmentSamplerStateLODFunc)objc_msgSend)(
        (id)render_cmd_enc,
        sel_getUid("setFragmentSamplerState:lodMinClamp:lodMaxClamp:atIndex:"),
        (id)sampler,
        lod_min,
        lod_max,
        index
    );
}

MT_INLINE void mt_renderCommand_encoder_set_fragment_sampler_states_lod(
    MTRenderCommandEncoder render_cmd_enc,
    const MTSamplerState* samplers,
    const float* lod_min_clamps,
    const float* lod_max_clamps,
    MTRange range
) {
    typedef void (*SetFragmentSamplerStatesLODArrayFunc)(id, SEL, const id*, const float*, const float*, MTRange);
    ((SetFragmentSamplerStatesLODArrayFunc)objc_msgSend)(
        (id)render_cmd_enc,
        sel_getUid("setFragmentSamplerStates:lodMinClamps:lodMaxClamps:withRange:"),
        (const id*)samplers,
        lod_min_clamps,
        lod_max_clamps,
        range
    );
}

MT_INLINE void mt_renderCommand_encoder_set_fragment_visible_function_table(
    MTRenderCommandEncoder render_cmd_enc,
    MTVisibleFunctionTable table,
    NSUInteger index
) {
    typedef void (*SetFragmentVisibleFunctionTableFunc)(id, SEL, id, NSUInteger);
    ((SetFragmentVisibleFunctionTableFunc)objc_msgSend)(
        (id)render_cmd_enc,
        sel_getUid("setFragmentVisibleFunctionTable:atBufferIndex:"),
        (id)table,
        index
    );
}

MT_INLINE void mt_renderCommand_encoder_set_fragment_visible_function_tables(
    MTRenderCommandEncoder render_cmd_enc,
    const MTVisibleFunctionTable* tables,
    MTRange range
) {
    typedef void (*SetFragmentVisibleFunctionTablesFunc)(id, SEL, const id*, MTRange);
    ((SetFragmentVisibleFunctionTablesFunc)objc_msgSend)(
        (id)render_cmd_enc,
        sel_getUid("setFragmentVisibleFunctionTables:withBufferRange:"),
        (const id*)tables,
        range
    );
}

MT_INLINE void mt_renderCommand_encoder_set_fragment_intersection_function_table(
    MTRenderCommandEncoder render_cmd_enc,
    MTIntersectionFunctionTable table,
    NSUInteger index
) {
    typedef void (*SetFragmentIntersectionFunctionTableFunc)(id, SEL, id, NSUInteger);
    ((SetFragmentIntersectionFunctionTableFunc)objc_msgSend)(
        (id)render_cmd_enc,
        sel_getUid("setFragmentIntersectionFunctionTable:atBufferIndex:"),
        (id)table,
        index
    );
}

MT_INLINE void mt_renderCommand_encoder_set_fragment_intersection_function_tables(
    MTRenderCommandEncoder render_cmd_enc,
    const MTIntersectionFunctionTable* tables,
    MTRange range
) {
    typedef void (*SetFragmentIntersectionFunctionTablesFunc)(id, SEL, const id*, MTRange);
    ((SetFragmentIntersectionFunctionTablesFunc)objc_msgSend)(
        (id)render_cmd_enc,
        sel_getUid("setFragmentIntersectionFunctionTables:withBufferRange:"),
        (const id*)tables,
        range
    );
}

MT_INLINE void mt_renderCommand_encoder_set_fragment_acceleration_structure(
    MTRenderCommandEncoder render_cmd_enc,
    MTAccelerationStructure accel_struct,
    NSUInteger index
) {
    typedef void (*SetFragmentAccelerationStructureFunc)(id, SEL, id, NSUInteger);
    ((SetFragmentAccelerationStructureFunc)objc_msgSend)(
        (id)render_cmd_enc,
        sel_getUid("setFragmentAccelerationStructure:atBufferIndex:"),
        (id)accel_struct,
        index
    );
}

MT_INLINE void mt_renderCommand_encoder_set_blend_color(
    MTRenderCommandEncoder render_cmd_enc,
    float red,
    float green,
    float blue,
    float alpha
) {
    typedef void (*SetBlendColorFunc)(id, SEL, float, float, float, float);
    ((SetBlendColorFunc)objc_msgSend)(
        (id)render_cmd_enc,
        sel_getUid("setBlendColorRed:green:blue:alpha:"),
        red, green, blue, alpha
    );
}

MT_INLINE void mt_renderCommand_encoder_set_depth_stencil_state(
    MTRenderCommandEncoder render_cmd_enc,
    MTDepthStencilState state
) {
    typedef void (*SetDepthStencilStateFunc)(id, SEL, id);
    ((SetDepthStencilStateFunc)objc_msgSend)(
        (id)render_cmd_enc,
        sel_getUid("setDepthStencilState:"),
        (id)state
    );
}

MT_INLINE void mt_renderCommand_encoder_set_stencil_reference_value(
    MTRenderCommandEncoder render_cmd_enc,
    uint32_t ref_value
) {
    typedef void (*SetStencilReferenceValueFunc)(id, SEL, uint32_t);
    ((SetStencilReferenceValueFunc)objc_msgSend)(
        (id)render_cmd_enc,
        sel_getUid("setStencilReferenceValue:"),
        ref_value
    );
}

MT_INLINE void mt_renderCommand_encoder_set_stencil_reference_values(
    MTRenderCommandEncoder render_cmd_enc,
    uint32_t front,
    uint32_t back
) {
    typedef void (*SetStencilReferenceValuesFunc)(id, SEL, uint32_t, uint32_t);
    ((SetStencilReferenceValuesFunc)objc_msgSend)(
        (id)render_cmd_enc,
        sel_getUid("setStencilFrontReferenceValue:backReferenceValue:"),
        front, back
    );
}

MT_INLINE void mt_renderCommand_encoder_set_visibility_result_mode(
    MTRenderCommandEncoder render_cmd_enc,
    MTVisibilityResultMode mode,
    NSUInteger offset
) {
    typedef void (*SetVisibilityResultModeFunc)(id, SEL, MTVisibilityResultMode, NSUInteger);
    ((SetVisibilityResultModeFunc)objc_msgSend)(
        (id)render_cmd_enc,
        sel_getUid("setVisibilityResultMode:offset:"),
        mode, offset
    );
}

MT_INLINE void mt_renderCommand_encoder_set_color_store_action(
    MTRenderCommandEncoder render_cmd_enc,
    MTStoreAction store_action,
    NSUInteger color_attachment_index
) {
    typedef void (*SetColorStoreActionFunc)(id, SEL, MTStoreAction, NSUInteger);
    ((SetColorStoreActionFunc)objc_msgSend)(
        (id)render_cmd_enc,
        sel_getUid("setColorStoreAction:atIndex:"),
        store_action, color_attachment_index
    );
}

MT_INLINE void mt_renderCommand_encoder_set_depth_store_action(
    MTRenderCommandEncoder render_cmd_enc,
    MTStoreAction store_action
) {
    typedef void (*SetDepthStoreActionFunc)(id, SEL, MTStoreAction);
    ((SetDepthStoreActionFunc)objc_msgSend)(
        (id)render_cmd_enc,
        sel_getUid("setDepthStoreAction:"),
        store_action
    );
}

MT_INLINE void mt_renderCommand_encoder_set_stencil_store_action(
    MTRenderCommandEncoder render_cmd_enc,
    MTStoreAction store_action
) {
    typedef void (*SetStencilStoreActionFunc)(id, SEL, MTStoreAction);
    ((SetStencilStoreActionFunc)objc_msgSend)(
        (id)render_cmd_enc,
        sel_getUid("setStencilStoreAction:"),
        store_action
    );
}

MT_INLINE void mt_renderCommand_encoder_set_color_store_action_options(
    MTRenderCommandEncoder render_cmd_enc,
    MTStoreActionOptions options,
    NSUInteger color_attachment_index
) {
    typedef void (*SetColorStoreActionOptionsFunc)(id, SEL, MTStoreActionOptions, NSUInteger);
    ((SetColorStoreActionOptionsFunc)objc_msgSend)(
        (id)render_cmd_enc,
        sel_getUid("setColorStoreActionOptions:atIndex:"),
        options, color_attachment_index
    );
}

MT_INLINE void mt_renderCommand_encoder_set_depth_store_action_options(
    MTRenderCommandEncoder render_cmd_enc,
    MTStoreActionOptions options
) {
    typedef void (*SetDepthStoreActionOptionsFunc)(id, SEL, MTStoreActionOptions);
    ((SetDepthStoreActionOptionsFunc)objc_msgSend)(
        (id)render_cmd_enc,
        sel_getUid("setDepthStoreActionOptions:"),
        options
    );
}

MT_INLINE void mt_renderCommand_encoder_set_stencil_store_action_options(
    MTRenderCommandEncoder render_cmd_enc,
    MTStoreActionOptions options
) {
    typedef void (*SetStencilStoreActionOptionsFunc)(id, SEL, MTStoreActionOptions);
    ((SetStencilStoreActionOptionsFunc)objc_msgSend)(
        (id)render_cmd_enc,
        sel_getUid("setStencilStoreActionOptions:"),
        options
    );
}

MT_INLINE void mt_renderCommand_encoder_set_object_bytes(
    MTRenderCommandEncoder render_cmd_enc,
    const void *bytes,
    NSUInteger length,
    NSUInteger index
) {
    typedef void (*SetObjectBytesFunc)(id, SEL, const void *, NSUInteger, NSUInteger);
    ((SetObjectBytesFunc)objc_msgSend)(
        (id)render_cmd_enc,
        sel_getUid("setObjectBytes:length:atIndex:"),
        bytes, length, index
    );
}

MT_INLINE void mt_renderCommand_encoder_set_object_buffer(
    MTRenderCommandEncoder render_cmd_enc,
    MTBuffer buffer,
    NSUInteger offset,
    NSUInteger index
) {
    typedef void (*SetObjectBufferFunc)(id, SEL, id, NSUInteger, NSUInteger);
    ((SetObjectBufferFunc)objc_msgSend)(
        (id)render_cmd_enc,
        sel_getUid("setObjectBuffer:offset:atIndex:"),
        (id)buffer, offset, index
    );
}

MT_INLINE void mt_renderCommand_encoder_set_object_buffer_offset(
    MTRenderCommandEncoder render_cmd_enc,
    NSUInteger offset,
    NSUInteger index
) {
    typedef void (*SetObjectBufferOffsetFunc)(id, SEL, NSUInteger, NSUInteger);
    ((SetObjectBufferOffsetFunc)objc_msgSend)(
        (id)render_cmd_enc,
        sel_getUid("setObjectBufferOffset:atIndex:"),
        offset, index
    );
}

//MT_INLINE void mt_renderCommand_encoder_set_object_buffers(
//    MTRenderCommandEncoder render_cmd_enc,
//    MTBuffer* _Nullable buffers,
//    const NSUInteger* offsets,
//    NSUInteger range_location,
//    NSUInteger range_length
//) {
//    typedef void (*SetObjectBuffersFunc)(id, SEL, id*, NSUInteger*, struct MTRange);
//    SetObjectBuffersFunc func = (SetObjectBuffersFunc)objc_msgSend;
//    MTRange range = { range_location, range_length };
//    func((id)render_cmd_enc,
//         sel_getUid("setObjectBuffers:offsets:withRange:"),
//         buffers, (NSUInteger*)offsets, range);
//}

MT_INLINE void mt_renderCommand_encoder_set_object_texture(
    MTRenderCommandEncoder render_cmd_enc,
    MTTexture texture,
    NSUInteger index
) {
    typedef void (*SetObjectTextureFunc)(id, SEL, id, NSUInteger);
    ((SetObjectTextureFunc)objc_msgSend)(
        (id)render_cmd_enc,
        sel_getUid("setObjectTexture:atIndex:"),
        (id)texture, index
    );
}
//
//MT_INLINE void mt_renderCommand_encoder_set_object_textures(
//    MTRenderCommandEncoder render_cmd_enc,
//    const MTTexture _Nullable *textures,
//    MTRange range
//) {
//    typedef void (*SetObjectTexturesFunc)(id, SEL, const id[], MTRange);
//    ((SetObjectTexturesFunc)objc_msgSend)(
//        (id)render_cmd_enc,
//        sel_getUid("setObjectTextures:withRange:"),
//        (const id[])textures, range
//    );
//}

MT_INLINE void mt_renderCommand_encoder_set_object_sampler_state(
    MTRenderCommandEncoder render_cmd_enc,
    MTSamplerState sampler,
    NSUInteger index
) {
    typedef void (*SetObjectSamplerStateFunc)(id, SEL, id, NSUInteger);
    ((SetObjectSamplerStateFunc)objc_msgSend)(
        (id)render_cmd_enc,
        sel_getUid("setObjectSamplerState:atIndex:"),
        (id)sampler, index
    );
}

void mt_renderCommand_encoder_set_tessellation_factor_scale(MTRenderCommandEncoder render_cmd_enc, float scale) {
    void_ms_send_float(render_cmd_enc, sel_getUid("setTessellationFactorScale:"), scale);
}
