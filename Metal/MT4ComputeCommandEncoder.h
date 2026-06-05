//
//  MT4ComputeCommandEncoder.h
//  Metal C
//
//  MTL4ComputeCommandEncoder — encodes compute dispatches in the Metal 4 model,
//  and also serves as the home for blit-style operations (Metal 4 has no
//  separate blit encoder). Obtain one from mt4_command_buffer_get_compute_encoder.
//
//  Resources are bound through an MTL4ArgumentTable (see MT4ArgumentTable.h);
//  unlike the render encoder, the compute setArgumentTable takes no stages.
//  Shared ops (barriers, fences, debug, end_encoding) are in MT4CommandEncoder.h
//  — cast this encoder to MT4CommandEncoder.
//
//  Note: the many region-based texture-copy overloads and acceleration-
//  structure build/refit commands this encoder also supports are deferred to a
//  later stage; the common blit conveniences are included below.
//

#pragma once
#include "MTFoundation/defines.h"
#include "MTTypes.h"            // NSUInteger, MTSize, MTRange, MTGPUAddress
#include "MT4CommandEncoder.h"  // MTStages
#include "MT4ArgumentTable.h"

// ---- Pipeline + binding --------------------------------------------------

MT_INLINE void mt4_compute_command_encoder_set_pipeline_state(MT4ComputeCommandEncoder encoder, MTComputePipelineState state) {
    MT_MSG_SEND_1(void, encoder, MT_SEL("setComputePipelineState:"), id, state);
}

MT_INLINE void mt4_compute_command_encoder_set_argument_table(MT4ComputeCommandEncoder encoder, MT4ArgumentTable table) {
    MT_MSG_SEND_1(void, encoder, MT_SEL("setArgumentTable:"), id, table);
}

// Stages for which this encoder can encode work (e.g. Dispatch | Blit).
MT_INLINE MTStages mt4_compute_command_encoder_get_stages(MT4ComputeCommandEncoder encoder) {
    return MT_MSG_SEND(MTStages, encoder, MT_SEL("stages"));
}

// ---- Threadgroup / imageblock memory -------------------------------------

MT_INLINE void mt4_compute_command_encoder_set_threadgroup_memory_length(MT4ComputeCommandEncoder encoder, NSUInteger length, NSUInteger index) {
    MT_MSG_SEND_2(void, encoder, MT_SEL("setThreadgroupMemoryLength:atIndex:"), NSUInteger, length, NSUInteger, index);
}

MT_INLINE void mt4_compute_command_encoder_set_imageblock_size(MT4ComputeCommandEncoder encoder, NSUInteger width, NSUInteger height) {
    MT_MSG_SEND_2(void, encoder, MT_SEL("setImageblockWidth:height:"), NSUInteger, width, NSUInteger, height);
}

// ---- Dispatch ------------------------------------------------------------

MT_INLINE void mt4_compute_command_encoder_dispatch_threads(MT4ComputeCommandEncoder encoder, MTSize threads_per_grid, MTSize threads_per_threadgroup) {
    ((void (*)(id, SEL, MTSize, MTSize))objc_msgSend)(
        (id)encoder, MT_SEL("dispatchThreads:threadsPerThreadgroup:"), threads_per_grid, threads_per_threadgroup);
}

MT_INLINE void mt4_compute_command_encoder_dispatch_threadgroups(MT4ComputeCommandEncoder encoder, MTSize threadgroups_per_grid, MTSize threads_per_threadgroup) {
    ((void (*)(id, SEL, MTSize, MTSize))objc_msgSend)(
        (id)encoder, MT_SEL("dispatchThreadgroups:threadsPerThreadgroup:"), threadgroups_per_grid, threads_per_threadgroup);
}

// Indirect dispatch — args read from a buffer at the given GPU address.
MT_INLINE void mt4_compute_command_encoder_dispatch_threadgroups_indirect(MT4ComputeCommandEncoder encoder, MTGPUAddress indirect_buffer, MTSize threads_per_threadgroup) {
    ((void (*)(id, SEL, MTGPUAddress, MTSize))objc_msgSend)(
        (id)encoder, MT_SEL("dispatchThreadgroupsWithIndirectBuffer:threadsPerThreadgroup:"), indirect_buffer, threads_per_threadgroup);
}

// Args (including threadsPerThreadgroup) are laid out in the indirect buffer.
MT_INLINE void mt4_compute_command_encoder_dispatch_threads_indirect(MT4ComputeCommandEncoder encoder, MTGPUAddress indirect_buffer) {
    MT_MSG_SEND_1(void, encoder, MT_SEL("dispatchThreadsWithIndirectBuffer:"), MTGPUAddress, indirect_buffer);
}

// ---- Blit-style operations (Metal 4 folds these into the compute encoder) -

MT_INLINE void mt4_compute_command_encoder_copy_from_buffer_to_buffer(MT4ComputeCommandEncoder encoder, MTBuffer source, NSUInteger source_offset, MTBuffer dest, NSUInteger dest_offset, NSUInteger size) {
    MT_MSG_SEND_5(void, encoder, MT_SEL("copyFromBuffer:sourceOffset:toBuffer:destinationOffset:size:"), id, source, NSUInteger, source_offset, id, dest, NSUInteger, dest_offset, NSUInteger, size);
}

// `range` follows NSRange layout (location, length), matching MTRange.
MT_INLINE void mt4_compute_command_encoder_fill_buffer(MT4ComputeCommandEncoder encoder, MTBuffer buffer, MTRange range, uint8_t value) {
    ((void (*)(id, SEL, id, MTRange, uint8_t))objc_msgSend)(
        (id)encoder, MT_SEL("fillBuffer:range:value:"), (id)buffer, range, value);
}

MT_INLINE void mt4_compute_command_encoder_generate_mipmaps(MT4ComputeCommandEncoder encoder, MTTexture texture) {
    MT_MSG_SEND_1(void, encoder, MT_SEL("generateMipmapsForTexture:"), id, texture);
}

MT_INLINE void mt4_compute_command_encoder_optimize_contents_for_gpu_access(MT4ComputeCommandEncoder encoder, MTTexture texture) {
    MT_MSG_SEND_1(void, encoder, MT_SEL("optimizeContentsForGPUAccess:"), id, texture);
}

MT_INLINE void mt4_compute_command_encoder_optimize_contents_for_cpu_access(MT4ComputeCommandEncoder encoder, MTTexture texture) {
    MT_MSG_SEND_1(void, encoder, MT_SEL("optimizeContentsForCPUAccess:"), id, texture);
}
