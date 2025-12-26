//
//  MTIOCommandQueue.h
//  Metal C
//
//  Created by Lungile Maseko on 2025/06/05.
//
#pragma once
#include "MTUtils.h"

typedef void* MTIOCommandBuffer;
typedef void* MTIOCommandQueue;
typedef void* MTIOCommandQueueDescriptor;
typedef void* MTIOFileHandle;
typedef void* MTString;

typedef enum MTIOPriority {
    MTIOPriorityHigh = 0,
    MTIOPriorityNormal = 1,
    MTIOPriorityLow = 2,
} MTIOPriority;

typedef enum MTIOCommandQueueType {
    MTIOCommandQueueTypeConcurrent = 0,
    MTIOCommandQueueTypeSerial = 1,
} MTIOCommandQueueType;

extern const void* MTLIOErrorDomain;

typedef enum MTIOError {
    MTIOErrorURLInvalid = 1,
    MTIOErrorInternal = 2,
} MTIOError;

// MTIOCommandQueue methods
MT_INLINE void mt_io_command_queue_enqueue_barrier(MTIOCommandQueue queue) {
    MT_MSG_SEND(void, queue, MT_SEL("enqueueBarrier"));
}

MT_INLINE MTIOCommandBuffer mt_io_command_queue_command_buffer(MTIOCommandQueue queue) {
    return MT_MSG_SEND(id, queue, MT_SEL("commandBuffer"));
}

MT_INLINE MTIOCommandBuffer mt_io_command_queue_command_buffer_unretained(MTIOCommandQueue queue) {
    return MT_MSG_SEND(id, queue, MT_SEL("commandBufferWithUnretainedReferences"));
}

MT_INLINE MTString mt_io_command_queue_get_label(MTIOCommandQueue queue) {
    return MT_MSG_SEND(id, queue, MT_SEL("label"));
}

MT_INLINE void mt_io_command_queue_set_label(MTIOCommandQueue queue, MTString label) {
    MT_MSG_SEND_1(void, queue, MT_SEL("setLabel:"), id, label);
}

// MTIOCommandQueueDescriptor
MT_INLINE MTIOCommandQueueDescriptor mt_io_command_queue_descriptor_create(void) {
    return MT_ALLOC_INIT("MTLIOCommandQueueDescriptor");
}

MT_INLINE NSUInteger mt_io_command_queue_descriptor_get_max_command_buffer_count(MTIOCommandQueueDescriptor desc) {
    return MT_MSG_SEND(NSUInteger, desc, MT_SEL("maxCommandBufferCount"));
}

MT_INLINE void mt_io_command_queue_descriptor_set_max_command_buffer_count(MTIOCommandQueueDescriptor desc, NSUInteger count) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setMaxCommandBufferCount:"), NSUInteger, count);
}

MT_INLINE MTIOPriority mt_io_command_queue_descriptor_get_priority(MTIOCommandQueueDescriptor desc) {
    return MT_MSG_SEND(MTIOPriority, desc, MT_SEL("priority"));
}

MT_INLINE void mt_io_command_queue_descriptor_set_priority(MTIOCommandQueueDescriptor desc, MTIOPriority priority) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setPriority:"), MTIOPriority, priority);
}

MT_INLINE MTIOCommandQueueType mt_io_command_queue_descriptor_get_type(MTIOCommandQueueDescriptor desc) {
    return MT_MSG_SEND(MTIOCommandQueueType, desc, MT_SEL("type"));
}

MT_INLINE void mt_io_command_queue_descriptor_set_type(MTIOCommandQueueDescriptor desc, MTIOCommandQueueType type) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setType:"), MTIOCommandQueueType, type);
}

MT_INLINE NSUInteger mt_io_command_queue_descriptor_get_max_commands_in_flight(MTIOCommandQueueDescriptor desc) {
    return MT_MSG_SEND(NSUInteger, desc, MT_SEL("maxCommandsInFlight"));
}

MT_INLINE void mt_io_command_queue_descriptor_set_max_commands_in_flight(MTIOCommandQueueDescriptor desc, NSUInteger maxCmds) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setMaxCommandsInFlight:"), NSUInteger, maxCmds);
}

// MTIOFileHandle
MT_INLINE MTString mt_io_file_handle_get_label(MTIOFileHandle handle) {
    return MT_MSG_SEND(id, handle, MT_SEL("label"));
}

MT_INLINE void mt_io_file_handle_set_label(MTIOFileHandle handle, MTString label) {
    MT_MSG_SEND_1(void, handle, MT_SEL("setLabel:"), id, label);
}
