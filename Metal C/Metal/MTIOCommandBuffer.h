//
//  MTIOCommandBuffer.h
//  Metal C
//
//  Created by Lungile Maseko on 2025/06/05.
//
#pragma once
#include "MTTypes.h"

typedef void* MTIOCommandBuffer;
typedef void* MTIOFileHandle;
typedef void* MTBuffer;
typedef void* MTTexture;
typedef void* MTError;
typedef void* MTSharedEvent;

/* Used by MTIOCommandBuffer to indicate completion status. */
typedef enum MTIOStatus {
    MTLIOStatusPending = 0,
    MTLIOStatusCancelled = 1,
    MTLIOStatusError = 2,
    MTLIOStatusComplete = 3,
} MTIOStatus;

typedef void (*MTIOCommandCallback)(void* userData);

void mt_io_command_buffer_add_completed_handler(MTIOCommandBuffer cmdBuf, MTIOCommandCallback callback, void* userData) {
    SEL sel = sel_registerName("addCompletedHandler:");

    // Wrap C function and userData in a block
    void (^handlerBlock)(void* buffer) = ^(void* buffer){
        callback(userData);
    };

    typedef void (*FuncType)(void*, SEL, void*);
    ((FuncType)objc_msgSend)(cmdBuf, sel, handlerBlock);
}

void mt_io_command_buffer_load_bytes(MTIOCommandBuffer cmdBuf, void* pointer, unsigned long size, MTIOFileHandle handle, unsigned long handleOffset) {
    SEL sel = sel_registerName("loadBytes:size:sourceHandle:sourceHandleOffset:");
    typedef void (*FuncType)(void*, SEL, void*, unsigned long, void*, unsigned long);
    ((FuncType)objc_msgSend)(cmdBuf, sel, pointer, size, handle, handleOffset);
}

void mt_io_command_buffer_load_buffer(MTIOCommandBuffer cmdBuf, MTBuffer buffer, unsigned long offset, unsigned long size, MTIOFileHandle handle, unsigned long handleOffset) {
    SEL sel = sel_registerName("loadBuffer:offset:size:sourceHandle:sourceHandleOffset:");
    typedef void (*FuncType)(void*, SEL, void*, unsigned long, unsigned long, void*, unsigned long);
    ((FuncType)objc_msgSend)(cmdBuf, sel, buffer, offset, size, handle, handleOffset);
}

void mt_io_command_buffer_load_texture(MTIOCommandBuffer cmdBuf, MTTexture texture, unsigned slice, unsigned level, MTSize size, unsigned sourceBytesPerRow, unsigned sourceBytesPerImage, MTOrigin destinationOrigin, MTIOFileHandle sourceHandle, unsigned long long sourceHandleOffset) {
    SEL sel = sel_registerName("loadTexture:slice:level:size:sourceBytesPerRow:sourceBytesPerImage:destinationOrigin:sourceHandle:sourceHandleOffset:");
    typedef void (*FuncType)(void*, SEL, void*, unsigned, unsigned, MTSize, unsigned, unsigned, MTOrigin, void*, unsigned long long);
    ((FuncType)objc_msgSend)(cmdBuf, sel, texture, slice, level, size, sourceBytesPerRow, sourceBytesPerImage, destinationOrigin, sourceHandle, sourceHandleOffset);
}

void mt_io_command_buffer_copy_status_to_buffer(MTIOCommandBuffer cmdBuf, MTBuffer buffer, unsigned offset) {
    SEL sel = sel_registerName("copyStatusToBuffer:offset:");
    typedef void (*FuncType)(void*, SEL, void*, unsigned);
    ((FuncType)objc_msgSend)(cmdBuf, sel, buffer, offset);
}

void mt_io_command_buffer_commit(MTIOCommandBuffer cmdBuf) {
    SEL sel = sel_registerName("commit");
    ((void (*)(void*, SEL))objc_msgSend)(cmdBuf, sel);
}

void mt_io_command_buffer_wait_until_completed(MTIOCommandBuffer cmdBuf) {
    SEL sel = sel_registerName("waitUntilCompleted");
    ((void (*)(void*, SEL))objc_msgSend)(cmdBuf, sel);
}

void mt_io_command_buffer_try_cancel(MTIOCommandBuffer cmdBuf) {
    SEL sel = sel_registerName("tryCancel");
    ((void (*)(void*, SEL))objc_msgSend)(cmdBuf, sel);
}

void mt_io_command_buffer_add_barrier(MTIOCommandBuffer cmdBuf) {
    SEL sel = sel_registerName("addBarrier");
    ((void (*)(void*, SEL))objc_msgSend)(cmdBuf, sel);
}

void mt_io_command_buffer_push_debug_group(MTIOCommandBuffer cmdBuf, MTString label) {
    SEL sel = sel_registerName("pushDebugGroup:");
    ((void (*)(void*, SEL, void*))objc_msgSend)(cmdBuf, sel, label);
}

void mt_io_command_buffer_pop_debug_group(MTIOCommandBuffer cmdBuf) {
    SEL sel = sel_registerName("popDebugGroup");
    ((void (*)(void*, SEL))objc_msgSend)(cmdBuf, sel);
}

void mt_io_command_buffer_enqueue(MTIOCommandBuffer cmdBuf) {
    SEL sel = sel_registerName("enqueue");
    ((void (*)(void*, SEL))objc_msgSend)(cmdBuf, sel);
}

void mt_io_command_buffer_wait_for_event(MTIOCommandBuffer cmdBuf, MTSharedEvent event, uint64_t value) {
    SEL sel = sel_registerName("waitForEvent:value:");
    ((void (*)(void*, SEL, void*, uint64_t))objc_msgSend)(cmdBuf, sel, event, value);
}

void mt_io_command_buffer_signal_event(MTIOCommandBuffer cmdBuf, MTSharedEvent event, uint64_t value) {
    SEL sel = sel_registerName("signalEvent:value:");
    ((void (*)(void*, SEL, void*, uint64_t))objc_msgSend)(cmdBuf, sel, event, value);
}

void mt_io_command_buffer_set_label(MTIOCommandBuffer cmdBuf, MTString label) {
    SEL sel = sel_registerName("setLabel:");
    ((void (*)(void*, SEL, void*))objc_msgSend)(cmdBuf, sel, label);
}

MTString mt_io_command_buffer_get_label(MTIOCommandBuffer cmdBuf) {
    SEL sel = sel_registerName("label");
    return ((MTString (*)(void*, SEL))objc_msgSend)(cmdBuf, sel);
}

MTIOStatus mt_io_command_buffer_get_status(MTIOCommandBuffer cmdBuf) {
    SEL sel = sel_registerName("status");
    return ((MTIOStatus (*)(void*, SEL))objc_msgSend)(cmdBuf, sel);
}

MTError mt_io_command_buffer_get_error(MTIOCommandBuffer cmdBuf) {
    SEL sel = sel_registerName("error");
    return ((MTError (*)(void*, SEL))objc_msgSend)(cmdBuf, sel);
}
