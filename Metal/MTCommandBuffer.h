//
//  MTCommandBuffer.h
//  Metal C
//
//  Created by Lungile Maseko on 2024/04/29.
//

#pragma once
#include "MTCommandQueue.h"
#include "MTDrawable.h"
#include "MTUtils.h"

typedef enum MTCommandBufferStatus {
    MTCommandBufferStatusNotEnqueued = 0,
    MTCommandBufferStatusEnqueued = 1,
    MTCommandBufferStatusCommitted = 2,
    MTCommandBufferStatusScheduled = 3,
    MTCommandBufferStatusCompleted = 4,
    MTCommandBufferStatusError = 5,
} MTCommandBufferStatus;

typedef enum MTCommandBufferError {
    MTCommandBufferErrorNone = 0,
    MTCommandBufferErrorInternal = 1,
    MTCommandBufferErrorTimeout = 2,
    MTCommandBufferErrorPageFault = 3,
    MTCommandBufferErrorBlacklisted = 4,
    MTCommandBufferErrorAccessRevoked = 4,
    MTCommandBufferErrorNotPermitted = 7,
    MTCommandBufferErrorOutOfMemory = 8,
    MTCommandBufferErrorInvalidResource = 9,
    MTCommandBufferErrorMemoryless = 10,
    MTCommandBufferErrorDeviceRemoved = 11,
    MTCommandBufferErrorStackOverflow = 12,
} MTCommandBufferError;

typedef enum MTCommandBufferErrorOption {
    MTCommandBufferErrorOptionNone = 0,
    MTCommandBufferErrorOptionEncoderExecutionStatus = 1,
} MTCommandBufferErrorOption;

typedef enum MTCommandEncoderErrorState {
    MTCommandEncoderErrorStateUnknown = 0,
    MTCommandEncoderErrorStateCompleted = 1,
    MTCommandEncoderErrorStateAffected = 2,
    MTCommandEncoderErrorStatePending = 3,
    MTCommandEncoderErrorStateFaulted = 4,
} MTCommandEncoderErrorState;

MT_INLINE MTCommandBuffer mt_command_queue_get_command_buffer(MTCommandQueue cmdQueue) {
    return MT_MSG_SEND(void*, cmdQueue, MT_SEL("commandBuffer"));
}

MT_INLINE MTBlitCommandEncoder mt_command_buffer_get_blit_encoder(MTCommandBuffer cmd_buf) {
    return MT_MSG_SEND(void*, cmd_buf, MT_SEL("blitCommandEncoder"));
}

MT_INLINE MTBlitCommandEncoder mt_command_buffer_get_blit_encoder_with_descriptor(MTCommandBuffer cmd_buf, MTBlitPassDescriptor desc) {
    return MT_MSG_SEND_1(void*, cmd_buf, MT_SEL("blitCommandEncoderWithDescriptor:"), id, desc);
}

MT_INLINE MTCommandBufferDescriptor mt_command_buffer_descriptor_create(void) {
    return MT_ALLOC_INIT("MTLCommandBufferDescriptor");
}

MT_INLINE void mt_command_buffer_present_drawable(MTCommandBuffer cmdBuffer, MTDrawable drawable) {
    MT_MSG_SEND_1(void, cmdBuffer, MT_SEL("presentDrawable:"), id, drawable);
}

MT_INLINE void mt_command_buffer_present_drawable_at_time(MTCommandBuffer cmd_buf, MTDrawable drawable, CFTimeInterval time) {
    MT_MSG_SEND_2(void, cmd_buf, MT_SEL("presentDrawable:atTime:"), id, drawable, CFTimeInterval, time);
}

MT_INLINE void mt_command_buffer_commit(MTCommandBuffer cmdBuffer) {
    MT_MSG_SEND(void, cmdBuffer, MT_SEL("commit"));
}

MT_INLINE void mt_command_buffer_wait_until_completed(MTCommandBuffer cmdBuffer) {
    MT_MSG_SEND(void, cmdBuffer, MT_SEL("waitUntilCompleted"));
}

MT_INLINE void mt_command_buffer_push_debug_group(MTCommandBuffer cmd_buf, const char* name) {
    id nsString = mt_string_create(name);
    MT_MSG_SEND_1(void, cmd_buf, MT_SEL("pushDebugGroup:"), id, nsString);
    mt_string_release(nsString);
}

MT_INLINE void mt_command_buffer_pop_debug_group(MTCommandBuffer cmd_buf) {
    MT_MSG_SEND(void, cmd_buf, MT_SEL("popDebugGroup"));
}

MT_INLINE MTCommandBufferStatus mt_command_buffer_get_status(MTCommandBuffer cmd_buf) {
    return MT_MSG_SEND(MTCommandBufferStatus, cmd_buf, MT_SEL("status"));
}

MT_INLINE MTError mt_command_buffer_get_error(MTCommandBuffer cmd_buf) {
    return MT_MSG_SEND(void*, cmd_buf, MT_SEL("error"));
}

MT_INLINE void mt_command_buffer_wait_until_scheduled(MTCommandBuffer cmd_buf) {
    MT_MSG_SEND(void, cmd_buf, MT_SEL("waitUntilScheduled"));
}

// ============================================================================
// Command Buffer Handlers
// ============================================================================

/// Registers a block to be called when the command buffer has completed execution.
/// The block receives the completed command buffer as its argument.
/// This is the proper way to synchronize CPU/GPU work (e.g., signaling a
/// semaphore for triple-buffered uniform updates) without stalling the CPU.
MT_INLINE void mt_command_buffer_add_completed_handler(MTCommandBuffer cmd_buf, void (^handler)(MTCommandBuffer)) {
    MT_MSG_SEND_1(void, cmd_buf, MT_SEL("addCompletedHandler:"), void (^)(id), handler);
}

/// Registers a block to be called when the command buffer has been scheduled for execution.
MT_INLINE void mt_command_buffer_add_scheduled_handler(MTCommandBuffer cmd_buf, void (^handler)(MTCommandBuffer)) {
    MT_MSG_SEND_1(void, cmd_buf, MT_SEL("addScheduledHandler:"), void (^)(id), handler);
}

MT_INLINE MTComputeCommandEncoder mt_command_buffer_get_compute_encoder(MTCommandBuffer cmd_buf) {
    return MT_MSG_SEND(void*, cmd_buf, MT_SEL("computeCommandEncoder"));
}

// ============================================================================
// Event synchronization
//
// Queues a GPU-side wait/signal on this command buffer. Accepts an MTEvent or
// an MTSharedEvent (cast the shared event to MTEvent). Must be called before
// the command buffer is committed.
// ============================================================================

MT_INLINE void mt_command_buffer_encode_wait_for_event(MTCommandBuffer cmd_buf, MTEvent event, uint64_t value) {
    MT_MSG_SEND_2(void, cmd_buf, MT_SEL("encodeWaitForEvent:value:"), id, event, uint64_t, value);
}

MT_INLINE void mt_command_buffer_encode_signal_event(MTCommandBuffer cmd_buf, MTEvent event, uint64_t value) {
    MT_MSG_SEND_2(void, cmd_buf, MT_SEL("encodeSignalEvent:value:"), id, event, uint64_t, value);
}
