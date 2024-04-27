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

MT_INLINE MTCommandBuffer* mt_commandBuffer_new(MTCommandQueue* cmdQueue){
    return (void*) ms_send(cmdQueue, sel_getUid("commandBuffer"));
}

/**
 * @brief Creates a new MTLCommandBufferDescriptor class
 *
 * NOTE: Should be released using mtRelease().
 */
MT_INLINE MTCommandBufferDescriptor* mt_commandBuffer_descriptor_new(void){
    Class commandBufferDesc = objc_getClass("MTLCommandBufferDescriptor");
    SEL allocSel = sel_registerName("alloc");
    
    void* cmdBufDesc = ms_send(commandBufferDesc, allocSel);
    SEL initSel = sel_registerName("init");
    return ms_send(cmdBufDesc, initSel);
//    return NSCLASS_NEW("MTLCommandBufferDescriptor");
}

MT_INLINE void mt_commandBuffer_present_drawable(MTCommandBuffer* cmdBuffer, MTDrawable* drawable){
    ms_send_void(cmdBuffer, sel_registerName("presentDrawable:"), drawable);
}

MT_INLINE void mt_commandBuffer_commit(MTCommandBuffer* cmdBuffer){
    ms_send(cmdBuffer, sel_registerName("commit"));
}

MT_INLINE void mt_commandBuffer_wait_until_completed(MTCommandBuffer* cmdBuffer){
    ms_send(cmdBuffer, sel_registerName("waitUntilCompleted"));
}
