//
//  MTIOCommandQueue.h
//  Metal C
//
//  Created by Lungile Maseko on 2025/06/05.
//
#pragma once

typedef void* MTIOCommandBuffer;
typedef void* MTIOCommandQueue;
typedef void* MTIOFileHandle;
typedef void* MTString;

/* Used in MTLIOCommandQueueDescriptor to set the MTLIOQueue priority at creation time. */
typedef enum MTIOPriority {
    MTIOPriorityHigh = 0,
    MTIOPriorityNormal = 1,
    MTIOPriorityLow = 2,
} MTIOPriority;

/* Used in MTLIOCommandQueueDescriptor to set the MTLIOQueue type at creation time. */
typedef enum MTIOCommandQueueType {
    MTIOCommandQueueTypeConcurrent = 0,
    MTIOCommandQueueTypeSerial = 1,
} MTIOCommandQueueType;

extern const void* MTLIOErrorDomain;

/* Used by MTLIOFileHandle creation functions to indicate an error. */
typedef enum MTIOError {
    MTIOErrorURLInvalid       = 1,
    MTIOErrorInternal         = 2,
} MTIOError;

// ----------- Method: enqueueBarrier -----------
MT_INLINE void mt_io_command_queue_enqueue_barrier(MTIOCommandQueue queue) {
    SEL sel = sel_registerName("enqueueBarrier");
    typedef void (*FuncType)(void*, SEL);
    ((FuncType)objc_msgSend)(queue, sel);
}

// ----------- Method: commandBuffer -----------
MT_INLINE MTIOCommandBuffer mt_io_command_queue_command_buffer(MTIOCommandQueue queue) {
    SEL sel = sel_registerName("commandBuffer");
    typedef void* (*FuncType)(void*, SEL);
    return ((FuncType)objc_msgSend)(queue, sel);
}

// ----------- Method: commandBufferWithUnretainedReferences -----------
MT_INLINE MTIOCommandBuffer mt_io_command_queue_command_buffer_unretained(MTIOCommandQueue queue) {
    SEL sel = sel_registerName("commandBufferWithUnretainedReferences");
    typedef void* (*FuncType)(void*, SEL);
    return ((FuncType)objc_msgSend)(queue, sel);
}

// ----------- Property: label (getter) -----------
MT_INLINE MTString mt_io_command_queue_get_label(MTIOCommandQueue queue) {
    SEL sel = sel_registerName("label");
    typedef void* (*FuncType)(void*, SEL);
    return ((FuncType)objc_msgSend)(queue, sel);
}

// ----------- Property: label (setter) -----------
MT_INLINE void mt_io_command_queue_set_label(MTIOCommandQueue queue, MTString label) {
    SEL sel = sel_registerName("setLabel:");
    typedef void (*FuncType)(void*, SEL, void*);
    ((FuncType)objc_msgSend)(queue, sel, label);
}

//MARK: ----------- MTIOCommandQueueDescriptor -----------

MT_INLINE MTIOCommandQueueDescriptor mt_io_command_queue_descriptor_create(void) {
    Class descClass = objc_getClass("MTLIOCommandQueueDescriptor");
    SEL allocSel = sel_registerName("alloc");
    SEL initSel = sel_registerName("init");

    id obj = ((id (*)(Class, SEL))objc_msgSend)(descClass, allocSel);
    return ((id (*)(id, SEL))objc_msgSend)(obj, initSel);
}

MT_INLINE NSUInteger mt_io_command_queue_descriptor_get_max_command_buffer_count(MTIOCommandQueueDescriptor desc) {
    SEL sel = sel_registerName("maxCommandBufferCount");
    typedef NSUInteger (*FuncType)(void*, SEL);
    return ((FuncType)objc_msgSend)(desc, sel);
}

MT_INLINE void mt_io_command_queue_descriptor_set_max_command_buffer_count(MTIOCommandQueueDescriptor desc, NSUInteger count) {
    SEL sel = sel_registerName("setMaxCommandBufferCount:");
    typedef void (*FuncType)(void*, SEL, NSUInteger);
    ((FuncType)objc_msgSend)(desc, sel, count);
}

// ----------- priority -----------
MT_INLINE MTIOPriority mt_io_command_queue_descriptor_get_priority(MTIOCommandQueueDescriptor desc) {
    SEL sel = sel_registerName("priority");
    typedef MTIOPriority (*FuncType)(void*, SEL);
    return ((FuncType)objc_msgSend)(desc, sel);
}

MT_INLINE void mt_io_command_queue_descriptor_set_priority(MTIOCommandQueueDescriptor desc, MTIOPriority priority) {
    SEL sel = sel_registerName("setPriority:");
    typedef void (*FuncType)(void*, SEL, MTIOPriority);
    ((FuncType)objc_msgSend)(desc, sel, priority);
}

// ----------- type -----------
MT_INLINE MTIOCommandQueueType mt_io_command_queue_descriptor_get_type(MTIOCommandQueueDescriptor desc) {
    SEL sel = sel_registerName("type");
    typedef MTIOCommandQueueType (*FuncType)(void*, SEL);
    return ((FuncType)objc_msgSend)(desc, sel);
}

MT_INLINE void mt_io_command_queue_descriptor_set_type(MTIOCommandQueueDescriptor desc, MTIOCommandQueueType type) {
    SEL sel = sel_registerName("setType:");
    typedef void (*FuncType)(void*, SEL, MTIOCommandQueueType);
    ((FuncType)objc_msgSend)(desc, sel, type);
}

// ----------- maxCommandsInFlight -----------
MT_INLINE NSUInteger mt_io_command_queue_descriptor_get_max_commands_in_flight(MTIOCommandQueueDescriptor desc) {
    SEL sel = sel_registerName("maxCommandsInFlight");
    typedef NSUInteger (*FuncType)(void*, SEL);
    return ((FuncType)objc_msgSend)(desc, sel);
}

MT_INLINE void mt_io_command_queue_descriptor_set_max_commands_in_flight(MTIOCommandQueueDescriptor desc, NSUInteger maxCmds) {
    SEL sel = sel_registerName("setMaxCommandsInFlight:");
    typedef void (*FuncType)(void*, SEL, NSUInteger);
    ((FuncType)objc_msgSend)(desc, sel, maxCmds);
}

// ----------- Get label -----------
MT_INLINE MTString mt_io_file_handle_get_label(MTIOFileHandle handle) {
    SEL sel = sel_registerName("label");
    typedef MTString (*FuncType)(void*, SEL);
    return ((FuncType)objc_msgSend)(handle, sel);
}

// ----------- Set label -----------
MT_INLINE void mt_io_file_handle_set_label(MTIOFileHandle handle, MTString label) {
    SEL sel = sel_registerName("setLabel:");
    typedef void (*FuncType)(void*, SEL, MTString);
    ((FuncType)objc_msgSend)(handle, sel, label);
}
