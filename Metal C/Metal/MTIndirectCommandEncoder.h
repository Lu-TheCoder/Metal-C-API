//
//  MTIndirectCommandEncoder.h
//  Metal C
//
//  Created by Lungile Maseko on 2025/05/31.
//
#pragma once
#include "MTUtils.h"

typedef void* MTIndirectRenderCommand;
typedef void* MTRenderPipelineState;
typedef void* MTBuffer;
typedef void* MTComputePipelineState;

MT_INLINE void mt_indirect_render_command_set_render_pipeline_state(MTIndirectRenderCommand command, MTRenderPipelineState pipeline_state) {
    ((void (*)(id, SEL, id))objc_msgSend)(command, sel_getUid("setRenderPipelineState:"), pipeline_state);
}

MT_INLINE void mt_indirect_render_command_set_vertex_buffer(MTIndirectRenderCommand command, MTBuffer buffer, NSUInteger offset, NSUInteger index) {
    ((void (*)(id, SEL, id, NSUInteger, NSUInteger))objc_msgSend)(command, sel_getUid("setVertexBuffer:offset:atIndex:"), buffer, offset, index);
}

MT_INLINE void mt_indirect_render_command_set_fragment_buffer(MTIndirectRenderCommand command, MTBuffer buffer, NSUInteger offset, NSUInteger index) {
    ((void (*)(id, SEL, id, NSUInteger, NSUInteger))objc_msgSend)(command, sel_getUid("setFragmentBuffer:offset:atIndex:"), buffer, offset, index);
}

MT_INLINE void mt_indirect_render_command_set_vertex_buffer_with_stride(MTIndirectRenderCommand command, MTBuffer buffer, NSUInteger offset, NSUInteger stride, NSUInteger index) {
    ((void (*)(id, SEL, id, NSUInteger, NSUInteger, NSUInteger))objc_msgSend)(command, sel_getUid("setVertexBuffer:offset:attributeStride:atIndex:"), buffer, offset, stride, index);
}

MT_INLINE void mt_indirect_render_command_draw_patches(MTIndirectRenderCommand command, NSUInteger control_points, NSUInteger patch_start, NSUInteger patch_count, MTBuffer patch_index_buffer, NSUInteger patch_index_offset, NSUInteger instance_count, NSUInteger base_instance, MTBuffer tess_factor_buffer, NSUInteger tess_offset, NSUInteger instance_stride) {
    ((void (*)(id, SEL, NSUInteger, NSUInteger, NSUInteger, id, NSUInteger, NSUInteger, NSUInteger, id, NSUInteger, NSUInteger))objc_msgSend)(
        command, sel_getUid("drawPatches:patchStart:patchCount:patchIndexBuffer:patchIndexBufferOffset:instanceCount:baseInstance:tessellationFactorBuffer:tessellationFactorBufferOffset:tessellationFactorBufferInstanceStride:"),
        control_points, patch_start, patch_count, patch_index_buffer, patch_index_offset, instance_count, base_instance, tess_factor_buffer, tess_offset, instance_stride);
}

MT_INLINE void mt_indirect_render_command_draw_indexed_patches(MTIndirectRenderCommand command, NSUInteger control_points, NSUInteger patch_start, NSUInteger patch_count, MTBuffer patch_index_buffer, NSUInteger patch_index_offset, id control_index_buffer, NSUInteger control_index_offset, NSUInteger instance_count, NSUInteger base_instance, MTBuffer tess_factor_buffer, NSUInteger tess_offset, NSUInteger instance_stride) {
    ((void (*)(id, SEL, NSUInteger, NSUInteger, NSUInteger, id, NSUInteger, id, NSUInteger, NSUInteger, NSUInteger, id, NSUInteger, NSUInteger))objc_msgSend)(
        command, sel_getUid("drawIndexedPatches:patchStart:patchCount:patchIndexBuffer:patchIndexBufferOffset:controlPointIndexBuffer:controlPointIndexBufferOffset:instanceCount:baseInstance:tessellationFactorBuffer:tessellationFactorBufferOffset:tessellationFactorBufferInstanceStride:"),
        control_points, patch_start, patch_count, patch_index_buffer, patch_index_offset, control_index_buffer, control_index_offset, instance_count, base_instance, tess_factor_buffer, tess_offset, instance_stride);
}

MT_INLINE void mt_indirect_render_command_draw_primitives(MTIndirectRenderCommand command, NSUInteger primitive_type, NSUInteger vertex_start, NSUInteger vertex_count, NSUInteger instance_count, NSUInteger base_instance) {
    ((void (*)(id, SEL, NSUInteger, NSUInteger, NSUInteger, NSUInteger, NSUInteger))objc_msgSend)(command, sel_getUid("drawPrimitives:vertexStart:vertexCount:instanceCount:baseInstance:"), primitive_type, vertex_start, vertex_count, instance_count, base_instance);
}

MT_INLINE void mt_indirect_render_command_draw_indexed_primitives(MTIndirectRenderCommand command, NSUInteger primitive_type, NSUInteger index_count, NSUInteger index_type, MTBuffer index_buffer, NSUInteger index_buffer_offset, NSUInteger instance_count, long base_vertex, NSUInteger base_instance) {
    ((void (*)(id, SEL, NSUInteger, NSUInteger, NSUInteger, id, NSUInteger, NSUInteger, long, NSUInteger))objc_msgSend)(command, sel_getUid("drawIndexedPrimitives:indexCount:indexType:indexBuffer:indexBufferOffset:instanceCount:baseVertex:baseInstance:"), primitive_type, index_count, index_type, index_buffer, index_buffer_offset, instance_count, base_vertex, base_instance);
}

MT_INLINE void mt_indirect_render_command_set_object_threadgroup_memory_length(MTIndirectRenderCommand command, NSUInteger length, NSUInteger index) {
    ((void (*)(id, SEL, NSUInteger, NSUInteger))objc_msgSend)(command, sel_getUid("setObjectThreadgroupMemoryLength:atIndex:"), length, index);
}

MT_INLINE void mt_indirect_render_command_set_object_buffer(MTIndirectRenderCommand command, MTBuffer buffer, NSUInteger offset, NSUInteger index) {
    ((void (*)(id, SEL, id, NSUInteger, NSUInteger))objc_msgSend)(command, sel_getUid("setObjectBuffer:offset:atIndex:"), buffer, offset, index);
}

MT_INLINE void mt_indirect_render_command_set_mesh_buffer(MTIndirectRenderCommand command, MTBuffer buffer, NSUInteger offset, NSUInteger index) {
    ((void (*)(id, SEL, id, NSUInteger, NSUInteger))objc_msgSend)(command, sel_getUid("setMeshBuffer:offset:atIndex:"), buffer, offset, index);
}

MT_INLINE void mt_indirect_render_command_draw_mesh_threadgroups(MTIndirectRenderCommand command, MTSize tg_grid, MTSize tg_object, MTSize tg_mesh) {
    ((void (*)(id, SEL, MTSize, MTSize, MTSize))objc_msgSend)(command, sel_getUid("drawMeshThreadgroups:threadsPerObjectThreadgroup:threadsPerMeshThreadgroup:"), tg_grid, tg_object, tg_mesh);
}

MT_INLINE void mt_indirect_render_command_draw_mesh_threads(MTIndirectRenderCommand command, MTSize threads, MTSize tg_object, MTSize tg_mesh) {
    ((void (*)(id, SEL, MTSize, MTSize, MTSize))objc_msgSend)(command, sel_getUid("drawMeshThreads:threadsPerObjectThreadgroup:threadsPerMeshThreadgroup:"), threads, tg_object, tg_mesh);
}

MT_INLINE void mt_indirect_render_command_set_barrier(MTIndirectRenderCommand command) {
    ((void (*)(id, SEL))objc_msgSend)(command, sel_getUid("setBarrier"));
}

MT_INLINE void mt_indirect_render_command_clear_barrier(MTIndirectRenderCommand command) {
    ((void (*)(id, SEL))objc_msgSend)(command, sel_getUid("clearBarrier"));
}

MT_INLINE void mt_indirect_render_command_reset(MTIndirectRenderCommand command) {
    ((void (*)(id, SEL))objc_msgSend)(command, sel_getUid("reset"));
}

// MARK: MT Indirect Compute

MT_INLINE void mt_indirect_compute_command_set_pipeline_state(MTIndirectComputeCommand cmd, MTComputePipelineState pipeline) {
    ((void (*)(id, SEL, id))objc_msgSend)(cmd, sel_getUid("setComputePipelineState:"), pipeline);
}

MT_INLINE void mt_indirect_compute_command_set_kernel_buffer(MTIndirectComputeCommand cmd, MTBuffer buffer, NSUInteger offset, NSUInteger index) {
    ((void (*)(id, SEL, id, NSUInteger, NSUInteger))objc_msgSend)(
        cmd, sel_getUid("setKernelBuffer:offset:atIndex:"), buffer, offset, index);
}

MT_INLINE void mt_indirect_compute_command_set_kernel_buffer_stride(MTIndirectComputeCommand cmd, MTBuffer buffer, NSUInteger offset, NSUInteger stride, NSUInteger index) {
    ((void (*)(id, SEL, id, NSUInteger, NSUInteger, NSUInteger))objc_msgSend)(
        cmd, sel_getUid("setKernelBuffer:offset:attributeStride:atIndex:"), buffer, offset, stride, index);
}

MT_INLINE void mt_indirect_compute_command_concurrent_dispatch_threadgroups(MTIndirectComputeCommand cmd, MTSize threadgroups, MTSize threads_per_threadgroup) {
    ((void (*)(id, SEL, MTSize, MTSize))objc_msgSend)(
        cmd, sel_getUid("concurrentDispatchThreadgroups:threadsPerThreadgroup:"), threadgroups, threads_per_threadgroup);
}

MT_INLINE void mt_indirect_compute_command_concurrent_dispatch_threads(MTIndirectComputeCommand cmd, MTSize threads, MTSize threads_per_threadgroup) {
    ((void (*)(id, SEL, MTSize, MTSize))objc_msgSend)(
        cmd, sel_getUid("concurrentDispatchThreads:threadsPerThreadgroup:"), threads, threads_per_threadgroup);
}

MT_INLINE void mt_indirect_compute_command_set_barrier(MTIndirectComputeCommand cmd) {
    ((void (*)(id, SEL))objc_msgSend)(cmd, sel_getUid("setBarrier"));
}

MT_INLINE void mt_indirect_compute_command_clear_barrier(MTIndirectComputeCommand cmd) {
    ((void (*)(id, SEL))objc_msgSend)(cmd, sel_getUid("clearBarrier"));
}

MT_INLINE void mt_indirect_compute_command_set_imageblock_size(MTIndirectComputeCommand cmd, NSUInteger width, NSUInteger height) {
    ((void (*)(id, SEL, NSUInteger, NSUInteger))objc_msgSend)(
        cmd, sel_getUid("setImageblockWidth:height:"), width, height);
}

MT_INLINE void mt_indirect_compute_command_reset(MTIndirectComputeCommand cmd) {
    ((void (*)(id, SEL))objc_msgSend)(cmd, sel_getUid("reset"));
}

MT_INLINE void mt_indirect_compute_command_set_threadgroup_memory(MTIndirectComputeCommand cmd, NSUInteger length, NSUInteger index) {
    ((void (*)(id, SEL, NSUInteger, NSUInteger))objc_msgSend)(
        cmd, sel_getUid("setThreadgroupMemoryLength:atIndex:"), length, index);
}

MT_INLINE void mt_indirect_compute_command_set_stage_in_region(MTIndirectComputeCommand cmd, MTRegion region) {
    ((void (*)(id, SEL, MTRegion))objc_msgSend)(
        cmd, sel_getUid("setStageInRegion:"), region);
}
