//
//  MT4CommandAllocator.h
//  Metal C
//
//  Created by Lungile Maseko on 2025/06/20.
//
#pragma once
#include "MTUtils.h"

typedef void* MT4CommandAllocatorDescriptor;
typedef void* MT4CommandAllocator;
typedef void* MTDevice;

MT_INLINE void mt4_command_allocator_descriptor_set_label(
    MT4CommandAllocatorDescriptor desc,
    const char* label
) {
    if (!desc || !label) return;

    SEL setSel = sel_getUid("setLabel:");
    id nsLabel = ((id (*)(Class, SEL, const char*))objc_msgSend)(
        objc_getClass("NSString"),
        sel_getUid("stringWithUTF8String:"),
        label
    );
    ((void (*)(id, SEL, id))objc_msgSend)(desc, setSel, nsLabel);
}

MT_INLINE MTDevice mt4_command_allocator_get_device(MT4CommandAllocator allocator) {
    if (!allocator) return NULL;

    SEL sel = sel_getUid("device");
    return ((MTDevice (*)(id, SEL))objc_msgSend)(allocator, sel);
}

MT_INLINE uint64_t mt4_command_allocator_get_allocated_size(MT4CommandAllocator allocator) {
    if (!allocator) return 0;

    SEL sel = sel_getUid("allocatedSize");
    return ((uint64_t (*)(id, SEL))objc_msgSend)(allocator, sel);
}

MT_INLINE void mt4_command_allocator_reset(MT4CommandAllocator allocator) {
    if (!allocator) return;

    SEL sel = sel_getUid("reset");
    ((void (*)(id, SEL))objc_msgSend)(allocator, sel);
}
