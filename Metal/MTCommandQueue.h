//
//  MTCommandQueue.h
//  Metal C
//
//  Created by Lungile Maseko on 2024/04/29.
//

#pragma once
#include "MTDevice.h"

MT_INLINE MTCommandQueueDescriptor mt_command_queue_descriptor_create(void) {
    return MT_ALLOC_INIT("MTLCommandQueueDescriptor");
}

MT_INLINE MTCommandQueue mt_device_create_command_queue(MTDevice device) {
    return MT_MSG_SEND(void*, device, MT_SEL("newCommandQueue"));
}

MT_INLINE MTCommandQueue mt_device_create_command_queue_with_max_count(MTDevice device, NSUInteger max_count) {
    return MT_MSG_SEND_1(void*, device, MT_SEL("newCommandQueueWithMaxCommandBufferCount:"), NSUInteger, max_count);
}

MT_INLINE MTCommandQueue mt_device_create_command_queue_with_descriptor(MTDevice device, MTCommandQueueDescriptor descriptor) {
    return MT_MSG_SEND_1(void*, device, MT_SEL("newCommandQueueWithDescriptor:"), id, descriptor);
}
