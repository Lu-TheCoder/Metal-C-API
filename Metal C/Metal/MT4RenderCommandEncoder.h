//
//  MT4RenderCommandEncoder.h
//  Metal C
//
//  Created by Lungile Maseko on 2025/06/21.
//
#pragma once
#include "MTTypes.h"
#include "MTRenderCommandEncoder.h"
#include "MT4Counters.h"

typedef enum MT4RenderEncoderOptions {
    /// Declares that this render pass doesn't suspend nor resume.
    MT4RenderEncoderOptionNone       = 0,
    
    /// Configures the render pass as *suspending*.
    ///
    /// Pass this option to ``MTL4CommandBuffer/renderCommandEncoderWithDescriptor:options:`` to specify that Metal can
    /// stitch the work a render command encoder encodes with a subsequent "resuming" render command encoder.
    MT4RenderEncoderOptionSuspending = (1 << 0),
    
    /// Configures the render pass to as *resuming*.
    ///
    /// Pass this option to ``MTL4CommandBuffer/renderCommandEncoderWithDescriptor:options:`` to specify that Metal can
    /// stitch the work a render command encoder encodes with a prior "suspending" render command encoder.
    MT4RenderEncoderOptionResuming   = (1 << 1)
} MT4RenderEncoderOptions;

typedef void* MT4RenderCommandEncoder;
typedef void* MTLogicalToPhysicalColorAttachmentMap;
typedef void* MTRenderPipelineState;
typedef void* MT4ArgumentTable;

MT_INLINE NSUInteger mt4_render_command_encoder_get_tile_width(MT4RenderCommandEncoder encoder) {
    if (!encoder) return 0;
    return ((NSUInteger (*)(void*, SEL))objc_msgSend)(
        encoder,
        sel_getUid("tileWidth")
    );
}

MT_INLINE NSUInteger mt4_render_command_encoder_get_tile_height(MT4RenderCommandEncoder encoder) {
    if (!encoder) return 0;
    return ((NSUInteger (*)(void*, SEL))objc_msgSend)(
        encoder,
        sel_getUid("tileHeight")
    );
}

MT_INLINE void mt4_render_command_encoder_set_color_attachment_map(MT4RenderCommandEncoder encoder, MTLogicalToPhysicalColorAttachmentMap map) {
    if (!encoder || !map) return;
    ((void (*)(void*, SEL, void*))objc_msgSend)(
        encoder,
        sel_getUid("setColorAttachmentMap:"),
        map
    );
}

MT_INLINE void mt4_render_command_encoder_set_render_pipeline_state(MT4RenderCommandEncoder encoder, MTRenderPipelineState pipelineState) {
    if (!encoder || !pipelineState) return;
    ((void (*)(void*, SEL, void*))objc_msgSend)(
        encoder,
        sel_getUid("setRenderPipelineState:"),
        pipelineState
    );
}

MT_INLINE void mt4_render_command_encoder_set_viewport(MT4RenderCommandEncoder encoder, MTViewport viewport) {
    if (!encoder) return;
    ((void (*)(void*, SEL, MTViewport))objc_msgSend)(
        encoder,
        sel_getUid("setViewport:"),
        viewport
    );
}

MT_INLINE void mt4_render_command_encoder_set_viewports(MT4RenderCommandEncoder encoder, const MTViewport *viewports, NSUInteger count) {
    if (!encoder || !viewports || count == 0) return;
    ((void (*)(void*, SEL, const MTViewport *, NSUInteger))objc_msgSend)(
        encoder,
        sel_getUid("setViewports:count:"),
        viewports,
        count
    );
}

MT_INLINE void mt4_render_command_encoder_set_vertex_amplification_count(MT4RenderCommandEncoder encoder, NSUInteger count, const void* viewMappings) {
    if (!encoder) return;
    ((void (*)(void*, SEL, NSUInteger, const void*))objc_msgSend)(
        encoder,
        sel_getUid("setVertexAmplificationCount:viewMappings:"),
        count,
        viewMappings
    );
}

MT_INLINE void mt4_render_command_encoder_set_cull_mode(MT4RenderCommandEncoder encoder, MTCullMode cullMode) {
    if (!encoder) return;
    ((void (*)(void*, SEL, MTCullMode))objc_msgSend)(
        encoder,
        sel_getUid("setCullMode:"),
        cullMode
    );
}

typedef unsigned long MTLDepthClipMode;

MT_INLINE void mt4_render_command_encoder_set_depth_clip_mode(MT4RenderCommandEncoder encoder, MTLDepthClipMode mode) {
    if (!encoder) return;
    ((void (*)(void*, SEL, MTLDepthClipMode))objc_msgSend)(
        encoder,
        sel_getUid("setDepthClipMode:"),
        mode
    );
}

MT_INLINE void mt4_render_command_encoder_set_depth_bias(MT4RenderCommandEncoder encoder, float bias, float slopeScale, float clamp) {
    if (!encoder) return;
    ((void (*)(void*, SEL, float, float, float))objc_msgSend)(
        encoder,
        sel_getUid("setDepthBias:slopeScale:clamp:"),
        bias,
        slopeScale,
        clamp
    );
}

MT_INLINE void mt4_render_command_encoder_set_scissor_rect(MT4RenderCommandEncoder encoder, MTScissorRect rect) {
    if (!encoder) return;
    ((void (*)(void*, SEL, MTScissorRect))objc_msgSend)(
        encoder,
        sel_getUid("setScissorRect:"),
        rect
    );
}

MT_INLINE void mt4_render_command_encoder_set_scissor_rects(MT4RenderCommandEncoder encoder, const MTScissorRect* rects, NSUInteger count) {
    if (!encoder || !rects || count == 0) return;
    ((void (*)(void*, SEL, const MTScissorRect*, NSUInteger))objc_msgSend)(
        encoder,
        sel_getUid("setScissorRects:count:"),
        rects,
        count
    );
}

MT_INLINE void mt4_render_command_encoder_set_triangle_fill_mode(MT4RenderCommandEncoder encoder, MTTriangleFillMode mode) {
    if (!encoder) return;
    ((void (*)(void*, SEL, MTTriangleFillMode))objc_msgSend)(
        encoder,
        sel_getUid("setTriangleFillMode:"),
        mode
    );
}

MT_INLINE void mt4_render_command_encoder_set_blend_color(MT4RenderCommandEncoder encoder, float r, float g, float b, float a) {
    if (!encoder) return;
    ((void (*)(void*, SEL, float, float, float, float))objc_msgSend)(
        encoder,
        sel_getUid("setBlendColorRed:green:blue:alpha:"),
        r, g, b, a
    );
}

typedef void* MTDepthStencilState;

MT_INLINE void mt4_render_command_encoder_set_depth_stencil_state(MT4RenderCommandEncoder encoder, MTDepthStencilState state) {
    if (!encoder) return;
    ((void (*)(void*, SEL, void*))objc_msgSend)(
        encoder,
        sel_getUid("setDepthStencilState:"),
        state
    );
}

MT_INLINE void mt4_render_command_encoder_set_stencil_reference_value(MT4RenderCommandEncoder encoder, uint32_t value) {
    if (!encoder) return;
    ((void (*)(void*, SEL, uint32_t))objc_msgSend)(
        encoder,
        sel_getUid("setStencilReferenceValue:"),
        value
    );
}

MT_INLINE void mt4_render_command_encoder_set_stencil_front_back_reference_value(MT4RenderCommandEncoder encoder, uint32_t frontRef, uint32_t backRef) {
    if (!encoder) return;
    ((void (*)(void*, SEL, uint32_t, uint32_t))objc_msgSend)(
        encoder,
        sel_getUid("setStencilFrontReferenceValue:backReferenceValue:"),
        frontRef,
        backRef
    );
}

MT_INLINE void mt4_render_command_encoder_set_visibility_result_mode(MT4RenderCommandEncoder encoder, MTVisibilityResultMode mode, NSUInteger offset) {
    if (!encoder) return;
    ((void (*)(void*, SEL, MTVisibilityResultMode, NSUInteger))objc_msgSend)(
        encoder,
        sel_getUid("setVisibilityResultMode:offset:"),
        mode,
        offset
    );
}


MT_INLINE void mt4_render_command_encoder_set_color_store_action(MT4RenderCommandEncoder encoder, MTStoreAction action, NSUInteger index) {
    if (!encoder) return;
    ((void (*)(void*, SEL, MTStoreAction, NSUInteger))objc_msgSend)(
        encoder,
        sel_getUid("setColorStoreAction:atIndex:"),
        action,
        index
    );
}

MT_INLINE void mt4_render_command_encoder_set_depth_store_action(MT4RenderCommandEncoder encoder, MTStoreAction action) {
    if (!encoder) return;
    ((void (*)(void*, SEL, MTStoreAction))objc_msgSend)(
        encoder,
        sel_getUid("setDepthStoreAction:"),
        action
    );
}

MT_INLINE void mt4_render_command_encoder_set_stencil_store_action(MT4RenderCommandEncoder encoder, MTStoreAction action) {
    if (!encoder) return;
    ((void (*)(void*, SEL, MTStoreAction))objc_msgSend)(
        encoder,
        sel_getUid("setStencilStoreAction:"),
        action
    );
}

typedef unsigned long MTLPrimitiveType;

MT_INLINE void mt4_render_command_encoder_draw_primitives(MT4RenderCommandEncoder encoder, MTLPrimitiveType type, NSUInteger vertexStart, NSUInteger vertexCount) {
    if (!encoder) return;
    ((void (*)(void*, SEL, MTLPrimitiveType, NSUInteger, NSUInteger))objc_msgSend)(
        encoder,
        sel_getUid("drawPrimitives:vertexStart:vertexCount:"),
        type,
        vertexStart,
        vertexCount
    );
}

MT_INLINE void mt4_render_command_encoder_draw_primitives_instanced(MT4RenderCommandEncoder encoder, MTLPrimitiveType type, NSUInteger vertexStart, NSUInteger vertexCount, NSUInteger instanceCount) {
    if (!encoder) return;
    ((void (*)(void*, SEL, MTLPrimitiveType, NSUInteger, NSUInteger, NSUInteger))objc_msgSend)(
        encoder,
        sel_getUid("drawPrimitives:vertexStart:vertexCount:instanceCount:"),
        type,
        vertexStart,
        vertexCount,
        instanceCount
    );
}

MT_INLINE void mt4_render_command_encoder_draw_primitives_instanced_base(MT4RenderCommandEncoder encoder, MTLPrimitiveType type, NSUInteger vertexStart, NSUInteger vertexCount, NSUInteger instanceCount, NSUInteger baseInstance) {
    if (!encoder) return;
    ((void (*)(void*, SEL, MTLPrimitiveType, NSUInteger, NSUInteger, NSUInteger, NSUInteger))objc_msgSend)(
        encoder,
        sel_getUid("drawPrimitives:vertexStart:vertexCount:instanceCount:baseInstance:"),
        type,
        vertexStart,
        vertexCount,
        instanceCount,
        baseInstance
    );
}


MT_INLINE void mt4_render_command_encoder_draw_indexed_primitives(MT4RenderCommandEncoder encoder, MTPrimitiveType type, NSUInteger indexCount, MTIndexType indexType, uint64_t indexBuffer, NSUInteger indexBufferLength) {
    if (!encoder) return;
    ((void (*)(void*, SEL, MTLPrimitiveType, NSUInteger, MTIndexType, uint64_t, NSUInteger))objc_msgSend)(
        encoder,
        sel_getUid("drawIndexedPrimitives:indexCount:indexType:indexBuffer:indexBufferLength:"),
        type,
        indexCount,
        indexType,
        indexBuffer,
        indexBufferLength
    );
}

MT_INLINE void mt4_render_command_encoder_draw_indexed_primitives_instanced(
    MT4RenderCommandEncoder encoder,
    MTLPrimitiveType type,
    NSUInteger indexCount,
    MTIndexType indexType,
    uint64_t indexBuffer,
    NSUInteger indexBufferLength,
    NSUInteger instanceCount
) {
    if (!encoder) return;
    ((void (*)(void*, SEL, MTLPrimitiveType, NSUInteger, MTIndexType, uint64_t, NSUInteger, NSUInteger))objc_msgSend)(
        encoder,
        sel_getUid("drawIndexedPrimitives:indexCount:indexType:indexBuffer:indexBufferLength:instanceCount:"),
        type,
        indexCount,
        indexType,
        indexBuffer,
        indexBufferLength,
        instanceCount
    );
}

MT_INLINE void mt4_render_command_encoder_draw_indexed_primitives_instanced_base(
    MT4RenderCommandEncoder encoder,
    MTLPrimitiveType type,
    NSUInteger indexCount,
    MTIndexType indexType,
    uint64_t indexBuffer,
    NSUInteger indexBufferLength,
    NSUInteger instanceCount,
    long baseVertex,
    NSUInteger baseInstance
) {
    if (!encoder) return;
    ((void (*)(void*, SEL, MTLPrimitiveType, NSUInteger, MTIndexType, uint64_t, NSUInteger, NSUInteger, long, NSUInteger))objc_msgSend)(
        encoder,
        sel_getUid("drawIndexedPrimitives:indexCount:indexType:indexBuffer:indexBufferLength:instanceCount:baseVertex:baseInstance:"),
        type,
        indexCount,
        indexType,
        indexBuffer,
        indexBufferLength,
        instanceCount,
        baseVertex,
        baseInstance
    );
}

MT_INLINE void mt4_render_command_encoder_draw_primitives_indirect(
    MT4RenderCommandEncoder encoder,
    MTLPrimitiveType type,
    uint64_t indirectBuffer
) {
    if (!encoder) return;
    ((void (*)(void*, SEL, MTLPrimitiveType, uint64_t))objc_msgSend)(
        encoder,
        sel_getUid("drawPrimitives:indirectBuffer:"),
        type,
        indirectBuffer
    );
}

MT_INLINE void mt4_render_command_encoder_draw_indexed_primitives_indirect(
    MT4RenderCommandEncoder encoder,
    MTLPrimitiveType type,
    MTIndexType indexType,
    uint64_t indexBuffer,
    NSUInteger indexBufferLength,
    uint64_t indirectBuffer
) {
    if (!encoder) return;
    ((void (*)(void*, SEL, MTLPrimitiveType, MTIndexType, uint64_t, NSUInteger, uint64_t))objc_msgSend)(
        encoder,
        sel_getUid("drawIndexedPrimitives:indexType:indexBuffer:indexBufferLength:indirectBuffer:"),
        type,
        indexType,
        indexBuffer,
        indexBufferLength,
        indirectBuffer
    );
}

MT_INLINE void mt4_render_command_encoder_execute_commands_in_buffer_with_range(
    MT4RenderCommandEncoder encoder,
    MTIndirectCommandBuffer indirectBuffer,
    MTRange range
) {
    if (!encoder || !indirectBuffer) return;
    ((void (*)(void*, SEL, void*, MTRange))objc_msgSend)(
        encoder,
        sel_getUid("executeCommandsInBuffer:withRange:"),
        indirectBuffer,
        range
    );
}

MT_INLINE void mt4_render_command_encoder_execute_commands_in_buffer_indirect(
    MT4RenderCommandEncoder encoder,
    MTIndirectCommandBuffer indirectBuffer,
    uint64_t indirectRangeBuffer
) {
    if (!encoder || !indirectBuffer) return;
    ((void (*)(void*, SEL, void*, uint64_t))objc_msgSend)(
        encoder,
        sel_getUid("executeCommandsInBuffer:indirectBuffer:"),
        indirectBuffer,
        indirectRangeBuffer
    );
}

MT_INLINE void mt4_render_command_encoder_set_object_threadgroup_memory_length(
    MT4RenderCommandEncoder encoder,
    NSUInteger length,
    NSUInteger index
) {
    if (!encoder) return;
    ((void (*)(void*, SEL, NSUInteger, NSUInteger))objc_msgSend)(
        encoder,
        sel_getUid("setObjectThreadgroupMemoryLength:atIndex:"),
        length,
        index
    );
}

MT_INLINE void mt4_render_command_encoder_draw_mesh_threadgroups(
    MT4RenderCommandEncoder encoder,
    MTSize threadgroupsPerGrid,
    MTSize threadsPerObjectThreadgroup,
    MTSize threadsPerMeshThreadgroup
) {
    if (!encoder) return;
    ((void (*)(void*, SEL, MTSize, MTSize, MTSize))objc_msgSend)(
        encoder,
        sel_getUid("drawMeshThreadgroups:threadsPerObjectThreadgroup:threadsPerMeshThreadgroup:"),
        threadgroupsPerGrid,
        threadsPerObjectThreadgroup,
        threadsPerMeshThreadgroup
    );
}

MT_INLINE void mt4_render_command_encoder_draw_mesh_threads(
    MT4RenderCommandEncoder encoder,
    MTSize threadsPerGrid,
    MTSize threadsPerObjectThreadgroup,
    MTSize threadsPerMeshThreadgroup
) {
    if (!encoder) return;
    ((void (*)(void*, SEL, MTSize, MTSize, MTSize))objc_msgSend)(
        encoder,
        sel_getUid("drawMeshThreads:threadsPerObjectThreadgroup:threadsPerMeshThreadgroup:"),
        threadsPerGrid,
        threadsPerObjectThreadgroup,
        threadsPerMeshThreadgroup
    );
}

MT_INLINE void mt4_render_command_encoder_draw_mesh_threadgroups_indirect(
    MT4RenderCommandEncoder encoder,
    uint64_t indirectBuffer,
    MTSize threadsPerObjectThreadgroup,
    MTSize threadsPerMeshThreadgroup
) {
    if (!encoder) return;
    ((void (*)(void*, SEL, uint64_t, MTSize, MTSize))objc_msgSend)(
        encoder,
        sel_getUid("drawMeshThreadgroupsWithIndirectBuffer:threadsPerObjectThreadgroup:threadsPerMeshThreadgroup:"),
        indirectBuffer,
        threadsPerObjectThreadgroup,
        threadsPerMeshThreadgroup
    );
}

MT_INLINE void mt4_render_command_encoder_dispatch_threads_per_tile(
    MT4RenderCommandEncoder encoder,
    MTSize threadsPerTile
) {
    if (!encoder) return;
    ((void (*)(void*, SEL, MTSize))objc_msgSend)(
        encoder,
        sel_getUid("dispatchThreadsPerTile:"),
        threadsPerTile
    );
}

MT_INLINE void mt4_render_command_encoder_set_threadgroup_memory_length(
    MT4RenderCommandEncoder encoder,
    NSUInteger length,
    NSUInteger offset,
    NSUInteger index
) {
    if (!encoder) return;
    ((void (*)(void*, SEL, NSUInteger, NSUInteger, NSUInteger))objc_msgSend)(
        encoder,
        sel_getUid("setThreadgroupMemoryLength:offset:atIndex:"),
        length,
        offset,
        index
    );
}

MT_INLINE void mt4_render_command_encoder_set_argument_table(
    MT4RenderCommandEncoder encoder,
    MT4ArgumentTable table,
    MTRenderStages stages
) {
    if (!encoder || !table) return;
    ((void (*)(void*, SEL, void*, MTRenderStages))objc_msgSend)(
        encoder,
        sel_getUid("setArgumentTable:atStages:"),
        table,
        stages
    );
}

MT_INLINE void mt4_render_command_encoder_set_front_facing_winding(
    MT4RenderCommandEncoder encoder,
    MTWinding winding
) {
    if (!encoder) return;
    ((void (*)(void*, SEL, MTWinding))objc_msgSend)(
        encoder,
        sel_getUid("setFrontFacingWinding:"),
        winding
    );
}

MT_INLINE void mt4_render_command_encoder_write_timestamp(
    MT4RenderCommandEncoder encoder,
    MT4TimestampGranularity granularity,
    MTRenderStages stage,
    MT4CounterHeap heap,
    NSUInteger index
) {
    if (!encoder || !heap) return;
    ((void (*)(void*, SEL, MT4TimestampGranularity, MTRenderStages, void*, NSUInteger))objc_msgSend)(
        encoder,
        sel_getUid("writeTimestampWithGranularity:afterStage:intoHeap:atIndex:"),
        granularity,
        stage,
        heap,
        index
    );
}
