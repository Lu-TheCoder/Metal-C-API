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

typedef void* MTCommandBuffer;
typedef void* MTCommandBufferDescriptor;
typedef void* MTBlitCommandEncoder;
typedef void* MTBlitPassDescriptor;

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

MT_INLINE MTCommandBuffer mt_command_queue_create_commandBuffer(MTCommandQueue cmdQueue) {
    return MT_MSG_SEND(id, cmdQueue, MT_SEL("commandBuffer"));
}

MT_INLINE MTBlitCommandEncoder mt_command_buffer_get_blit_encoder(MTCommandBuffer cmd_buf) {
    return MT_MSG_SEND(id, cmd_buf, MT_SEL("blitCommandEncoder"));
}

MT_INLINE MTBlitCommandEncoder mt_command_buffer_get_blit_encoder_with_descriptor(MTCommandBuffer cmd_buf, MTBlitPassDescriptor* desc) {
    return MT_MSG_SEND_1(id, cmd_buf, MT_SEL("blitCommandEncoderWithDescriptor:"), MTBlitPassDescriptor*, desc);
}

MT_INLINE MTCommandBufferDescriptor mt_commandBuffer_descriptor_new(void) {
    return MT_ALLOC_INIT("MTLCommandBufferDescriptor");
}

MT_INLINE void mt_commandBuffer_present_drawable(MTCommandBuffer cmdBuffer, MTDrawable* drawable) {
    MT_MSG_SEND_1(void, cmdBuffer, MT_SEL("presentDrawable:"), id, drawable);
}

MT_INLINE void mt_command_buffer_present_drawable_at_time(MTCommandBuffer cmd_buf, MTDrawable drawable, CFTimeInterval time) {
    MT_MSG_SEND_2(void, cmd_buf, MT_SEL("presentDrawable:atTime:"), id, drawable, CFTimeInterval, time);
}

MT_INLINE void mt_commandBuffer_commit(MTCommandBuffer cmdBuffer) {
    MT_MSG_SEND(void, cmdBuffer, MT_SEL("commit"));
}

MT_INLINE void mt_commandBuffer_wait_until_completed(MTCommandBuffer cmdBuffer) {
    MT_MSG_SEND(void, cmdBuffer, MT_SEL("waitUntilCompleted"));
}

MT_INLINE void mt_command_buffer_push_debug_group(MTCommandBuffer cmd_buf, const char* name) {
    id nsString = mt_nsstring_create(name);
    MT_MSG_SEND_1(void, cmd_buf, MT_SEL("pushDebugGroup:"), id, nsString);
    mt_nsstring_release(nsString);
}

MT_INLINE void mt_command_buffer_pop_debug_group(MTCommandBuffer cmd_buf) {
    MT_MSG_SEND(void, cmd_buf, MT_SEL("popDebugGroup"));
}

MT_INLINE MTCommandBufferStatus mt_command_buffer_get_status(MTCommandBuffer cmd_buf) {
    return MT_MSG_SEND(MTCommandBufferStatus, cmd_buf, MT_SEL("status"));
}

MT_INLINE MTError* mt_command_buffer_get_error(MTCommandBuffer cmd_buf) {
    return MT_MSG_SEND(MTError*, cmd_buf, MT_SEL("error"));
}

MT_INLINE void mt_command_buffer_wait_until_scheduled(MTCommandBuffer cmd_buf) {
    MT_MSG_SEND(void, cmd_buf, MT_SEL("waitUntilScheduled"));
}
