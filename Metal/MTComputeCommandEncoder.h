//
//  MTComputeCommandEncoder.h
//  Metal C
//
//  Created on 2026-05-30.
//

#pragma once
#include "MTUtils.h"
#include "MTTypes.h"
#include "MTResource.h"  // MTResourceUsage, MTBarrierScope

// ============================================================================
// MTLComputeCommandEncoder Functions
// ============================================================================

MT_INLINE void mt_compute_command_encoder_set_compute_pipeline_state(MTComputeCommandEncoder encoder, MTComputePipelineState state) {
    MT_MSG_SEND_1(void, encoder, MT_SEL("setComputePipelineState:"), id, state);
}

MT_INLINE void mt_compute_command_encoder_set_buffer(MTComputeCommandEncoder encoder, MTBuffer buffer, NSUInteger offset, NSUInteger index) {
    MT_MSG_SEND_3(void, encoder, MT_SEL("setBuffer:offset:atIndex:"), id, buffer, NSUInteger, offset, NSUInteger, index);
}

MT_INLINE void mt_compute_command_encoder_set_buffers(MTComputeCommandEncoder encoder, const MTBuffer* buffers, const NSUInteger* offsets, MTRange range) {
    // Explicit casts needed for C array of buffers
    ((void (*)(id, SEL, const id*, const NSUInteger*, MTRange))objc_msgSend)(
        (id)encoder,
        MT_SEL("setBuffers:offsets:withRange:"),
        (const id*)buffers,
        offsets,
        range
    );
}

MT_INLINE void mt_compute_command_encoder_set_buffer_offset(MTComputeCommandEncoder encoder, NSUInteger offset, NSUInteger index) {
    MT_MSG_SEND_2(void, encoder, MT_SEL("setBufferOffset:atIndex:"), NSUInteger, offset, NSUInteger, index);
}

MT_INLINE void mt_compute_command_encoder_set_bytes(MTComputeCommandEncoder encoder, const void* bytes, NSUInteger length, NSUInteger index) {
    MT_MSG_SEND_3(void, encoder, MT_SEL("setBytes:length:atIndex:"), const void*, bytes, NSUInteger, length, NSUInteger, index);
}

MT_INLINE void mt_compute_command_encoder_set_texture(MTComputeCommandEncoder encoder, MTTexture texture, NSUInteger index) {
    MT_MSG_SEND_2(void, encoder, MT_SEL("setTexture:atIndex:"), id, texture, NSUInteger, index);
}

MT_INLINE void mt_compute_command_encoder_set_textures(MTComputeCommandEncoder encoder, const MTTexture* textures, MTRange range) {
    ((void (*)(id, SEL, const id*, MTRange))objc_msgSend)(
        (id)encoder,
        MT_SEL("setTextures:withRange:"),
        (const id*)textures,
        range
    );
}

MT_INLINE void mt_compute_command_encoder_set_sampler_state(MTComputeCommandEncoder encoder, MTSamplerState sampler, NSUInteger index) {
    MT_MSG_SEND_2(void, encoder, MT_SEL("setSamplerState:atIndex:"), id, sampler, NSUInteger, index);
}

// Bind a ray-tracing acceleration structure to a buffer-argument slot. In MSL
// the matching parameter is e.g. `primitive_acceleration_structure a [[buffer(index)]]`.
// (MTLComputeCommandEncoder.h:157 setAccelerationStructure:atBufferIndex:)
MT_INLINE void mt_compute_command_encoder_set_acceleration_structure(MTComputeCommandEncoder encoder, MTAccelerationStructure accel, NSUInteger index) {
    MT_MSG_SEND_2(void, encoder, MT_SEL("setAccelerationStructure:atBufferIndex:"), id, accel, NSUInteger, index);
}

MT_INLINE void mt_compute_command_encoder_set_sampler_states(MTComputeCommandEncoder encoder, const MTSamplerState* samplers, MTRange range) {
    ((void (*)(id, SEL, const id*, MTRange))objc_msgSend)(
        (id)encoder,
        MT_SEL("setSamplerStates:withRange:"),
        (const id*)samplers,
        range
    );
}

MT_INLINE void mt_compute_command_encoder_set_threadgroup_memory_length(MTComputeCommandEncoder encoder, NSUInteger length, NSUInteger index) {
    MT_MSG_SEND_2(void, encoder, MT_SEL("setThreadgroupMemoryLength:atIndex:"), NSUInteger, length, NSUInteger, index);
}

MT_INLINE void mt_compute_command_encoder_dispatch_threadgroups(MTComputeCommandEncoder encoder, MTSize threadgroupsPerGrid, MTSize threadsPerThreadgroup) {
    ((void (*)(id, SEL, MTSize, MTSize))objc_msgSend)(
        (id)encoder,
        MT_SEL("dispatchThreadgroups:threadsPerThreadgroup:"),
        threadgroupsPerGrid,
        threadsPerThreadgroup
    );
}

MT_INLINE void mt_compute_command_encoder_dispatch_threads(MTComputeCommandEncoder encoder, MTSize threadsPerGrid, MTSize threadsPerThreadgroup) {
    ((void (*)(id, SEL, MTSize, MTSize))objc_msgSend)(
        (id)encoder,
        MT_SEL("dispatchThreads:threadsPerThreadgroup:"),
        threadsPerGrid,
        threadsPerThreadgroup
    );
}

// MARK: - Resource Residency (required for heap / argument-buffer resources)

MT_INLINE void mt_compute_command_encoder_use_resource(MTComputeCommandEncoder encoder, MTResource resource, MTResourceUsage usage) {
    MT_MSG_SEND_2(void, encoder, MT_SEL("useResource:usage:"), id, resource, MTResourceUsage, usage);
}

MT_INLINE void mt_compute_command_encoder_use_resources(MTComputeCommandEncoder encoder, const MTResource* resources, NSUInteger count, MTResourceUsage usage) {
    ((void (*)(id, SEL, const id*, NSUInteger, MTResourceUsage))objc_msgSend)(
        (id)encoder, MT_SEL("useResources:count:usage:"), (const id*)resources, count, usage);
}

MT_INLINE void mt_compute_command_encoder_use_heap(MTComputeCommandEncoder encoder, MTHeap heap) {
    MT_MSG_SEND_1(void, encoder, MT_SEL("useHeap:"), id, heap);
}

MT_INLINE void mt_compute_command_encoder_use_heaps(MTComputeCommandEncoder encoder, const MTHeap* heaps, NSUInteger count) {
    ((void (*)(id, SEL, const id*, NSUInteger))objc_msgSend)(
        (id)encoder, MT_SEL("useHeaps:count:"), (const id*)heaps, count);
}

// MARK: - Memory Barriers

MT_INLINE void mt_compute_command_encoder_memory_barrier_with_scope(MTComputeCommandEncoder encoder, MTBarrierScope scope) {
    MT_MSG_SEND_1(void, encoder, MT_SEL("memoryBarrierWithScope:"), MTBarrierScope, scope);
}

MT_INLINE void mt_compute_command_encoder_memory_barrier_with_resources(MTComputeCommandEncoder encoder, const MTResource* resources, NSUInteger count) {
    ((void (*)(id, SEL, const id*, NSUInteger))objc_msgSend)(
        (id)encoder, MT_SEL("memoryBarrierWithResources:count:"), (const id*)resources, count);
}

// MARK: - Fences

MT_INLINE void mt_compute_command_encoder_update_fence(MTComputeCommandEncoder encoder, MTFence fence) {
    MT_MSG_SEND_1(void, encoder, MT_SEL("updateFence:"), id, fence);
}

MT_INLINE void mt_compute_command_encoder_wait_for_fence(MTComputeCommandEncoder encoder, MTFence fence) {
    MT_MSG_SEND_1(void, encoder, MT_SEL("waitForFence:"), id, fence);
}

MT_INLINE void mt_compute_command_encoder_end_encoding(MTComputeCommandEncoder encoder) {
    MT_MSG_SEND(void, encoder, MT_SEL("endEncoding"));
}
