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
}MTCommandBufferStatus;

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
}MTCommandBufferError;

typedef enum MTCommandBufferErrorOption {
    MTCommandBufferErrorOptionNone = 0,
    MTCommandBufferErrorOptionEncoderExecutionStatus = 1,
}MTCommandBufferErrorOption;

typedef enum MTCommandEncoderErrorState {
    MTCommandEncoderErrorStateUnknown = 0,
    MTCommandEncoderErrorStateCompleted = 1,
    MTCommandEncoderErrorStateAffected = 2,
    MTCommandEncoderErrorStatePending = 3,
    MTCommandEncoderErrorStateFaulted = 4,
}MTCommandEncoderErrorState;

MT_INLINE MTCommandBuffer mt_command_queue_create_commandBuffer(MTCommandQueue cmdQueue) {
    return ((id (*)(id, SEL))objc_msgSend)(cmdQueue, sel_getUid("commandBuffer"));
}

MT_INLINE MTBlitCommandEncoder mt_command_buffer_get_blit_encoder(MTCommandBuffer cmd_buf) {
    SEL sel = sel_getUid("blitCommandEncoder");
    return ((MTBlitCommandEncoder (*)(id, SEL))objc_msgSend)(cmd_buf, sel);
}

MT_INLINE MTBlitCommandEncoder mt_command_buffer_get_blit_encoder_with_descriptor(MTCommandBuffer cmd_buf, MTBlitPassDescriptor* desc) {
    SEL sel = sel_getUid("blitCommandEncoderWithDescriptor:");
    return ((MTBlitCommandEncoder (*)(id, SEL, MTBlitPassDescriptor*))objc_msgSend)(cmd_buf, sel, desc);
}

/**
 * @brief Creates a new MTLCommandBufferDescriptor class
 *
 * NOTE: Should be released using mtRelease().
 */
MT_INLINE MTCommandBufferDescriptor mt_commandBuffer_descriptor_new(void) {
    Class cmdBufDescClass = objc_getClass("MTLCommandBufferDescriptor");
    SEL allocSel = sel_getUid("alloc");
    SEL initSel = sel_getUid("init");

    // Allocate
    id obj = ((id (*)(Class, SEL))objc_msgSend)(cmdBufDescClass, allocSel);
    // Initialize
    obj = ((id (*)(id, SEL))objc_msgSend)(obj, initSel);

    return (MTCommandBufferDescriptor*)obj;
}

MT_INLINE void mt_commandBuffer_present_drawable(MTCommandBuffer cmdBuffer, MTDrawable* drawable) {
    void (*msgSend)(void*, SEL, void*) = (void (*)(void*, SEL, void*))objc_msgSend;
    SEL sel = sel_getUid("presentDrawable:");
    msgSend(cmdBuffer, sel, drawable);
}

MT_INLINE void mt_command_buffer_present_drawable_at_time(MTCommandBuffer cmd_buf, MTDrawable drawable, CFTimeInterval time) {
    SEL sel = sel_getUid("presentDrawable:atTime:");
    ((void (*)(id, SEL, id, CFTimeInterval))objc_msgSend)(cmd_buf, sel, drawable, time);
}

MT_INLINE void mt_commandBuffer_commit(MTCommandBuffer cmdBuffer) {
    void (*msgSend)(void*, SEL) = (void (*)(void*, SEL))objc_msgSend;
    SEL sel = sel_getUid("commit");
    msgSend(cmdBuffer, sel);
}

MT_INLINE void mt_commandBuffer_wait_until_completed(MTCommandBuffer cmdBuffer) {
    void (*msgSend)(void*, SEL) = (void (*)(void*, SEL))objc_msgSend;
    SEL sel = sel_getUid("waitUntilCompleted");
    msgSend(cmdBuffer, sel);
}

MT_INLINE void mt_command_buffer_push_debug_group(MTCommandBuffer cmd_buf, const char* name) {
    SEL sel = sel_getUid("pushDebugGroup:");
    id nsString = mt_nsstring_create(name);
    ((void (*)(id, SEL, id))objc_msgSend)(cmd_buf, sel, nsString);
    mt_nsstring_release(nsString);
}

MT_INLINE void mt_command_buffer_pop_debug_group(MTCommandBuffer cmd_buf) {
    SEL sel = sel_getUid("popDebugGroup");
    ((void (*)(id, SEL))objc_msgSend)(cmd_buf, sel);
}

MT_INLINE MTCommandBufferStatus mt_command_buffer_get_status(MTCommandBuffer cmd_buf) {
    SEL sel = sel_getUid("status");
    return ((MTCommandBufferStatus (*)(id, SEL))objc_msgSend)(cmd_buf, sel);
}

MT_INLINE MTError* mt_command_buffer_get_error(MTCommandBuffer cmd_buf) {
    SEL sel = sel_getUid("error");
    return ((MTError* (*)(id, SEL))objc_msgSend)(cmd_buf, sel);
}

MT_INLINE void mt_command_buffer_wait_until_scheduled(MTCommandBuffer cmd_buf) {
    SEL sel = sel_getUid("waitUntilScheduled");
    ((void (*)(id, SEL))objc_msgSend)(cmd_buf, sel);
}
