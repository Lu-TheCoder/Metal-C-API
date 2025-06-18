//
//  MTCommandQueue.h
//  Metal C
//
//  Created by Lungile Maseko on 2024/04/29.
//

#pragma once

#include "MTDevice.h"

typedef void* MTCommandQueue;
typedef void* MTCommandQueueDescriptor;

MT_INLINE MTCommandQueueDescriptor mt_command_queue_descriptor_new(void) {
    Class descClass = objc_getClass("MTLCommandQueueDescriptor");
    SEL sel = sel_getUid("alloc");
    id obj = ((id (*)(Class, SEL))objc_msgSend)(descClass, sel);
    
    sel = sel_getUid("init");
    return ((id (*)(id, SEL))objc_msgSend)(obj, sel);
}

MT_INLINE MTCommandQueue mt_device_create_command_queue(MTDevice device) {
        return (MTCommandQueue*)((id (*)(id, SEL))objc_msgSend)(device, sel_getUid("newCommandQueue"));
}

MT_INLINE MTCommandQueue mt_device_create_command_queue_with_max_count(MTDevice device, NSUInteger max_count) {
    typedef id (*NewCommandQueueMaxFunc)(id, SEL, NSUInteger);
    NewCommandQueueMaxFunc func = (NewCommandQueueMaxFunc)objc_msgSend;
    return (MTCommandQueue*)func(device, sel_getUid("newCommandQueueWithMaxCommandBufferCount:"), max_count);
}

MT_INLINE MTCommandQueue mt_device_create_command_queue_with_descriptor(MTDevice device, MTCommandQueueDescriptor* descriptor) {
    typedef id (*NewCommandQueueDescFunc)(id, SEL, MTCommandQueueDescriptor*);
    NewCommandQueueDescFunc func = (NewCommandQueueDescFunc)objc_msgSend;
    return (MTCommandQueue*)func(device, sel_getUid("newCommandQueueWithDescriptor:"), descriptor);
}

//FIXME: Crashes
//MTCommandQueue* mtNewCommandQueueWithMaxCommandBufferCount(MTDevice* device, uintptr_t count){
//    return (MTCommandQueue*)ms_send(device, sel_getUid("newCommandQueueWithMaxCommandBufferCount:"), count);
//}
