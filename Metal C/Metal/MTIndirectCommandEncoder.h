//
//  MTIndirectCommandEncoder.h
//  Metal C
//
//  Created by Lungile Maseko on 2025/05/31.
//
#pragma once
#include "MTUtils.h"
#include "MTTypes.h"

typedef void* MTIndirectRenderCommand;
typedef void* MTIndirectComputeCommand;
typedef void* MTRenderPipelineState;
typedef void* MTBuffer;
typedef void* MTComputePipelineState;

MT_INLINE void mt_indirect_render_command_set_render_pipeline_state(MTIndirectRenderCommand command, MTRenderPipelineState pipeline_state) {
    MT_MSG_SEND_1(void, command, MT_SEL("setRenderPipelineState:"), id, pipeline_state);
}

MT_INLINE void mt_indirect_render_command_set_vertex_buffer(MTIndirectRenderCommand command, MTBuffer buffer, NSUInteger offset, NSUInteger index) {
    MT_MSG_SEND_3(void, command, MT_SEL("setVertexBuffer:offset:atIndex:"), id, buffer, NSUInteger, offset, NSUInteger, index);
}

MT_INLINE void mt_indirect_render_command_set_fragment_buffer(MTIndirectRenderCommand command, MTBuffer buffer, NSUInteger offset, NSUInteger index) {
    MT_MSG_SEND_3(void, command, MT_SEL("setFragmentBuffer:offset:atIndex:"), id, buffer, NSUInteger, offset, NSUInteger, index);
}

MT_INLINE void mt_indirect_render_command_set_vertex_buffer_with_stride(MTIndirectRenderCommand command, MTBuffer buffer, NSUInteger offset, NSUInteger stride, NSUInteger index) {
    MT_MSG_SEND_4(void, command, MT_SEL("setVertexBuffer:offset:attributeStride:atIndex:"), id, buffer, NSUInteger, offset, NSUInteger, stride, NSUInteger, index);
}

// High-arg functions - explicit casts needed
MT_INLINE void mt_indirect_render_command_draw_patches(MTIndirectRenderCommand command, NSUInteger control_points, NSUInteger patch_start, NSUInteger patch_count, MTBuffer patch_index_buffer, NSUInteger patch_index_offset, NSUInteger instance_count, NSUInteger base_instance, MTBuffer tess_factor_buffer, NSUInteger tess_offset, NSUInteger instance_stride) {
    ((void (*)(id, SEL, NSUInteger, NSUInteger, NSUInteger, id, NSUInteger, NSUInteger, NSUInteger, id, NSUInteger, NSUInteger))objc_msgSend)(
        (id)command, MT_SEL("drawPatches:patchStart:patchCount:patchIndexBuffer:patchIndexBufferOffset:instanceCount:baseInstance:tessellationFactorBuffer:tessellationFactorBufferOffset:tessellationFactorBufferInstanceStride:"),
        control_points, patch_start, patch_count, (id)patch_index_buffer, patch_index_offset, instance_count, base_instance, (id)tess_factor_buffer, tess_offset, instance_stride);
}

MT_INLINE void mt_indirect_render_command_draw_indexed_patches(MTIndirectRenderCommand command, NSUInteger control_points, NSUInteger patch_start, NSUInteger patch_count, MTBuffer patch_index_buffer, NSUInteger patch_index_offset, id control_index_buffer, NSUInteger control_index_offset, NSUInteger instance_count, NSUInteger base_instance, MTBuffer tess_factor_buffer, NSUInteger tess_offset, NSUInteger instance_stride) {
    ((void (*)(id, SEL, NSUInteger, NSUInteger, NSUInteger, id, NSUInteger, id, NSUInteger, NSUInteger, NSUInteger, id, NSUInteger, NSUInteger))objc_msgSend)(
        (id)command, MT_SEL("drawIndexedPatches:patchStart:patchCount:patchIndexBuffer:patchIndexBufferOffset:controlPointIndexBuffer:controlPointIndexBufferOffset:instanceCount:baseInstance:tessellationFactorBuffer:tessellationFactorBufferOffset:tessellationFactorBufferInstanceStride:"),
        control_points, patch_start, patch_count, (id)patch_index_buffer, patch_index_offset, control_index_buffer, control_index_offset, instance_count, base_instance, (id)tess_factor_buffer, tess_offset, instance_stride);
}

MT_INLINE void mt_indirect_render_command_draw_primitives(MTIndirectRenderCommand command, NSUInteger primitive_type, NSUInteger vertex_start, NSUInteger vertex_count, NSUInteger instance_count, NSUInteger base_instance) {
    MT_MSG_SEND_5(void, command, MT_SEL("drawPrimitives:vertexStart:vertexCount:instanceCount:baseInstance:"), NSUInteger, primitive_type, NSUInteger, vertex_start, NSUInteger, vertex_count, NSUInteger, instance_count, NSUInteger, base_instance);
}

MT_INLINE void mt_indirect_render_command_draw_indexed_primitives(MTIndirectRenderCommand command, NSUInteger primitive_type, NSUInteger index_count, NSUInteger index_type, MTBuffer index_buffer, NSUInteger index_buffer_offset, NSUInteger instance_count, long base_vertex, NSUInteger base_instance) {
    ((void (*)(id, SEL, NSUInteger, NSUInteger, NSUInteger, id, NSUInteger, NSUInteger, long, NSUInteger))objc_msgSend)(
        (id)command, MT_SEL("drawIndexedPrimitives:indexCount:indexType:indexBuffer:indexBufferOffset:instanceCount:baseVertex:baseInstance:"),
        primitive_type, index_count, index_type, (id)index_buffer, index_buffer_offset, instance_count, base_vertex, base_instance);
}

MT_INLINE void mt_indirect_render_command_set_object_threadgroup_memory_length(MTIndirectRenderCommand command, NSUInteger length, NSUInteger index) {
    MT_MSG_SEND_2(void, command, MT_SEL("setObjectThreadgroupMemoryLength:atIndex:"), NSUInteger, length, NSUInteger, index);
}

MT_INLINE void mt_indirect_render_command_set_object_buffer(MTIndirectRenderCommand command, MTBuffer buffer, NSUInteger offset, NSUInteger index) {
    MT_MSG_SEND_3(void, command, MT_SEL("setObjectBuffer:offset:atIndex:"), id, buffer, NSUInteger, offset, NSUInteger, index);
}

MT_INLINE void mt_indirect_render_command_set_mesh_buffer(MTIndirectRenderCommand command, MTBuffer buffer, NSUInteger offset, NSUInteger index) {
    MT_MSG_SEND_3(void, command, MT_SEL("setMeshBuffer:offset:atIndex:"), id, buffer, NSUInteger, offset, NSUInteger, index);
}

// Struct args - explicit casts needed
MT_INLINE void mt_indirect_render_command_draw_mesh_threadgroups(MTIndirectRenderCommand command, MTSize tg_grid, MTSize tg_object, MTSize tg_mesh) {
    ((void (*)(id, SEL, MTSize, MTSize, MTSize))objc_msgSend)((id)command, MT_SEL("drawMeshThreadgroups:threadsPerObjectThreadgroup:threadsPerMeshThreadgroup:"), tg_grid, tg_object, tg_mesh);
}

MT_INLINE void mt_indirect_render_command_draw_mesh_threads(MTIndirectRenderCommand command, MTSize threads, MTSize tg_object, MTSize tg_mesh) {
    ((void (*)(id, SEL, MTSize, MTSize, MTSize))objc_msgSend)((id)command, MT_SEL("drawMeshThreads:threadsPerObjectThreadgroup:threadsPerMeshThreadgroup:"), threads, tg_object, tg_mesh);
}

MT_INLINE void mt_indirect_render_command_set_barrier(MTIndirectRenderCommand command) {
    MT_MSG_SEND(void, command, MT_SEL("setBarrier"));
}

MT_INLINE void mt_indirect_render_command_clear_barrier(MTIndirectRenderCommand command) {
    MT_MSG_SEND(void, command, MT_SEL("clearBarrier"));
}

MT_INLINE void mt_indirect_render_command_reset(MTIndirectRenderCommand command) {
    MT_MSG_SEND(void, command, MT_SEL("reset"));
}

// MARK: MTIndirectComputeCommand

MT_INLINE void mt_indirect_compute_command_set_pipeline_state(MTIndirectComputeCommand cmd, MTComputePipelineState pipeline) {
    MT_MSG_SEND_1(void, cmd, MT_SEL("setComputePipelineState:"), id, pipeline);
}

MT_INLINE void mt_indirect_compute_command_set_kernel_buffer(MTIndirectComputeCommand cmd, MTBuffer buffer, NSUInteger offset, NSUInteger index) {
    MT_MSG_SEND_3(void, cmd, MT_SEL("setKernelBuffer:offset:atIndex:"), id, buffer, NSUInteger, offset, NSUInteger, index);
}

MT_INLINE void mt_indirect_compute_command_set_kernel_buffer_stride(MTIndirectComputeCommand cmd, MTBuffer buffer, NSUInteger offset, NSUInteger stride, NSUInteger index) {
    MT_MSG_SEND_4(void, cmd, MT_SEL("setKernelBuffer:offset:attributeStride:atIndex:"), id, buffer, NSUInteger, offset, NSUInteger, stride, NSUInteger, index);
}

// Struct args - explicit casts needed
MT_INLINE void mt_indirect_compute_command_concurrent_dispatch_threadgroups(MTIndirectComputeCommand cmd, MTSize threadgroups, MTSize threads_per_threadgroup) {
    ((void (*)(id, SEL, MTSize, MTSize))objc_msgSend)((id)cmd, MT_SEL("concurrentDispatchThreadgroups:threadsPerThreadgroup:"), threadgroups, threads_per_threadgroup);
}

MT_INLINE void mt_indirect_compute_command_concurrent_dispatch_threads(MTIndirectComputeCommand cmd, MTSize threads, MTSize threads_per_threadgroup) {
    ((void (*)(id, SEL, MTSize, MTSize))objc_msgSend)((id)cmd, MT_SEL("concurrentDispatchThreads:threadsPerThreadgroup:"), threads, threads_per_threadgroup);
}

MT_INLINE void mt_indirect_compute_command_set_barrier(MTIndirectComputeCommand cmd) {
    MT_MSG_SEND(void, cmd, MT_SEL("setBarrier"));
}

MT_INLINE void mt_indirect_compute_command_clear_barrier(MTIndirectComputeCommand cmd) {
    MT_MSG_SEND(void, cmd, MT_SEL("clearBarrier"));
}

MT_INLINE void mt_indirect_compute_command_set_imageblock_size(MTIndirectComputeCommand cmd, NSUInteger width, NSUInteger height) {
    MT_MSG_SEND_2(void, cmd, MT_SEL("setImageblockWidth:height:"), NSUInteger, width, NSUInteger, height);
}

MT_INLINE void mt_indirect_compute_command_reset(MTIndirectComputeCommand cmd) {
    MT_MSG_SEND(void, cmd, MT_SEL("reset"));
}

MT_INLINE void mt_indirect_compute_command_set_threadgroup_memory(MTIndirectComputeCommand cmd, NSUInteger length, NSUInteger index) {
    MT_MSG_SEND_2(void, cmd, MT_SEL("setThreadgroupMemoryLength:atIndex:"), NSUInteger, length, NSUInteger, index);
}

// Struct arg - explicit cast needed
MT_INLINE void mt_indirect_compute_command_set_stage_in_region(MTIndirectComputeCommand cmd, MTRegion region) {
    ((void (*)(id, SEL, MTRegion))objc_msgSend)((id)cmd, MT_SEL("setStageInRegion:"), region);
}
