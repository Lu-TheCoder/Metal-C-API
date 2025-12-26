//
//  MTIOCommandBuffer.h
//  Metal C
//
//  Created by Lungile Maseko on 2025/06/05.
//
#pragma once
#include "MTTypes.h"
#include "MTUtils.h"

typedef void* MTIOCommandBuffer;
typedef void* MTIOFileHandle;
typedef void* MTBuffer;
typedef void* MTTexture;
typedef void* MTError;
typedef void* MTSharedEvent;
typedef void* MTString;

typedef enum MTIOStatus {
    MTLIOStatusPending = 0,
    MTLIOStatusCancelled = 1,
    MTLIOStatusError = 2,
    MTLIOStatusComplete = 3,
} MTIOStatus;

typedef void (*MTIOCommandCallback)(void* userData);

// Block-based callback - needs explicit block handling
MT_INLINE void mt_io_command_buffer_add_completed_handler(MTIOCommandBuffer cmdBuf, MTIOCommandCallback callback, void* userData) {
    SEL sel = sel_registerName("addCompletedHandler:");
    void (^handlerBlock)(void* buffer) = ^(void* buffer) {
        callback(userData);
    };
    ((void (*)(id, SEL, void*))objc_msgSend)((id)cmdBuf, sel, handlerBlock);
}

MT_INLINE void mt_io_command_buffer_load_bytes(MTIOCommandBuffer cmdBuf, void* pointer, unsigned long size, MTIOFileHandle handle, unsigned long handleOffset) {
    MT_MSG_SEND_4(void, cmdBuf, MT_SEL("loadBytes:size:sourceHandle:sourceHandleOffset:"), void*, pointer, unsigned long, size, id, handle, unsigned long, handleOffset);
}

MT_INLINE void mt_io_command_buffer_load_buffer(MTIOCommandBuffer cmdBuf, MTBuffer buffer, unsigned long offset, unsigned long size, MTIOFileHandle handle, unsigned long handleOffset) {
    MT_MSG_SEND_5(void, cmdBuf, MT_SEL("loadBuffer:offset:size:sourceHandle:sourceHandleOffset:"), id, buffer, unsigned long, offset, unsigned long, size, id, handle, unsigned long, handleOffset);
}

// 9-arg function - explicit cast needed
MT_INLINE void mt_io_command_buffer_load_texture(MTIOCommandBuffer cmdBuf, MTTexture texture, unsigned slice, unsigned level, MTSize size, unsigned sourceBytesPerRow, unsigned sourceBytesPerImage, MTOrigin destinationOrigin, MTIOFileHandle sourceHandle, unsigned long long sourceHandleOffset) {
    SEL sel = MT_SEL("loadTexture:slice:level:size:sourceBytesPerRow:sourceBytesPerImage:destinationOrigin:sourceHandle:sourceHandleOffset:");
    ((void (*)(id, SEL, id, unsigned, unsigned, MTSize, unsigned, unsigned, MTOrigin, id, unsigned long long))objc_msgSend)((id)cmdBuf, sel, (id)texture, slice, level, size, sourceBytesPerRow, sourceBytesPerImage, destinationOrigin, (id)sourceHandle, sourceHandleOffset);
}

MT_INLINE void mt_io_command_buffer_copy_status_to_buffer(MTIOCommandBuffer cmdBuf, MTBuffer buffer, unsigned offset) {
    MT_MSG_SEND_2(void, cmdBuf, MT_SEL("copyStatusToBuffer:offset:"), id, buffer, unsigned, offset);
}

MT_INLINE void mt_io_command_buffer_commit(MTIOCommandBuffer cmdBuf) {
    MT_MSG_SEND(void, cmdBuf, MT_SEL("commit"));
}

MT_INLINE void mt_io_command_buffer_wait_until_completed(MTIOCommandBuffer cmdBuf) {
    MT_MSG_SEND(void, cmdBuf, MT_SEL("waitUntilCompleted"));
}

MT_INLINE void mt_io_command_buffer_try_cancel(MTIOCommandBuffer cmdBuf) {
    MT_MSG_SEND(void, cmdBuf, MT_SEL("tryCancel"));
}

MT_INLINE void mt_io_command_buffer_add_barrier(MTIOCommandBuffer cmdBuf) {
    MT_MSG_SEND(void, cmdBuf, MT_SEL("addBarrier"));
}

MT_INLINE void mt_io_command_buffer_push_debug_group(MTIOCommandBuffer cmdBuf, MTString label) {
    MT_MSG_SEND_1(void, cmdBuf, MT_SEL("pushDebugGroup:"), id, label);
}

MT_INLINE void mt_io_command_buffer_pop_debug_group(MTIOCommandBuffer cmdBuf) {
    MT_MSG_SEND(void, cmdBuf, MT_SEL("popDebugGroup"));
}

MT_INLINE void mt_io_command_buffer_enqueue(MTIOCommandBuffer cmdBuf) {
    MT_MSG_SEND(void, cmdBuf, MT_SEL("enqueue"));
}

MT_INLINE void mt_io_command_buffer_wait_for_event(MTIOCommandBuffer cmdBuf, MTSharedEvent event, uint64_t value) {
    MT_MSG_SEND_2(void, cmdBuf, MT_SEL("waitForEvent:value:"), id, event, uint64_t, value);
}

MT_INLINE void mt_io_command_buffer_signal_event(MTIOCommandBuffer cmdBuf, MTSharedEvent event, uint64_t value) {
    MT_MSG_SEND_2(void, cmdBuf, MT_SEL("signalEvent:value:"), id, event, uint64_t, value);
}

MT_INLINE void mt_io_command_buffer_set_label(MTIOCommandBuffer cmdBuf, MTString label) {
    MT_MSG_SEND_1(void, cmdBuf, MT_SEL("setLabel:"), id, label);
}

MT_INLINE MTString mt_io_command_buffer_get_label(MTIOCommandBuffer cmdBuf) {
    return MT_MSG_SEND(id, cmdBuf, MT_SEL("label"));
}

MT_INLINE MTIOStatus mt_io_command_buffer_get_status(MTIOCommandBuffer cmdBuf) {
    return MT_MSG_SEND(MTIOStatus, cmdBuf, MT_SEL("status"));
}

MT_INLINE MTError mt_io_command_buffer_get_error(MTIOCommandBuffer cmdBuf) {
    return MT_MSG_SEND(id, cmdBuf, MT_SEL("error"));
}
