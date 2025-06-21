//
//  MT4ResidencySet.h
//  Metal C
//
//  Created by Lungile Maseko on 2025/06/21.
//
#pragma once

typedef void* MTResidencySetDescriptor;
typedef void* MTResidencySet;
typedef void* MTAllocation;
typedef void* MTDevice;

MT_INLINE MTResidencySetDescriptor mt_residency_set_descriptor_new(void) {
    Class cls = objc_getClass("MTLResidencySetDescriptor");
    return (MTResidencySetDescriptor)((id (*)(id, SEL))objc_msgSend)(cls, sel_getUid("new"));
}

MT_INLINE MTDevice mt_residency_set_get_device(MTResidencySet set) {
    if (!set) return NULL;
    SEL sel = sel_getUid("device");
    return (MTDevice)((id (*)(id, SEL))objc_msgSend)(set, sel);
}

MT_INLINE void mt_residency_set_descriptor_set_label(MTResidencySetDescriptor desc, const char *label) {
    if (!desc) return;
    SEL sel = sel_getUid("setLabel:");
    id str = label ? ((id (*)(Class, SEL, const char *))objc_msgSend)(objc_getClass("NSString"), sel_getUid("stringWithUTF8String:"), label) : nil;
    ((void (*)(id, SEL, id))objc_msgSend)(desc, sel, str);
}

MT_INLINE void mt_residency_set_descriptor_set_initial_capacity(MTResidencySetDescriptor desc, unsigned long capacity) {
    if (!desc) return;
    SEL sel = sel_getUid("setInitialCapacity:");
    ((void (*)(id, SEL, unsigned long))objc_msgSend)(desc, sel, capacity);
}

MT_INLINE void mt_residency_set_request_residency(MTResidencySet set) {
    if (!set) return;
    SEL sel = sel_getUid("requestResidency");
    ((void (*)(id, SEL))objc_msgSend)(set, sel);
}

MT_INLINE void mt_residency_set_end_residency(MTResidencySet set) {
    if (!set) return;
    SEL sel = sel_getUid("endResidency");
    ((void (*)(id, SEL))objc_msgSend)(set, sel);
}

MT_INLINE void mt_residency_set_add_allocation(MTResidencySet set, MTAllocation alloc) {
    if (!set || !alloc) return;
    SEL sel = sel_getUid("addAllocation:");
    ((void (*)(id, SEL, id))objc_msgSend)(set, sel, alloc);
}

MT_INLINE void mt_residency_set_add_allocations(MTResidencySet set, const id *allocs, unsigned long count) {
    if (!set || !allocs || !count) return;
    SEL sel = sel_getUid("addAllocations:count:");
    ((void (*)(id, SEL, const id *, unsigned long))objc_msgSend)(set, sel, allocs, count);
}

MT_INLINE void mt_residency_set_remove_allocation(MTResidencySet set, MTAllocation alloc) {
    if (!set || !alloc) return;
    SEL sel = sel_getUid("removeAllocation:");
    ((void (*)(id, SEL, id))objc_msgSend)(set, sel, alloc);
}

MT_INLINE void mt_residency_set_remove_allocations(MTResidencySet set, const id *allocs, unsigned long count) {
    if (!set || !allocs || !count) return;
    SEL sel = sel_getUid("removeAllocations:count:");
    ((void (*)(id, SEL, const id *, unsigned long))objc_msgSend)(set, sel, allocs, count);
}

MT_INLINE void mt_residency_set_remove_all_allocations(MTResidencySet set) {
    if (!set) return;
    SEL sel = sel_getUid("removeAllAllocations");
    ((void (*)(id, SEL))objc_msgSend)(set, sel);
}

MT_INLINE BOOL mt_residency_set_contains_allocation(MTResidencySet set, MTAllocation alloc) {
    if (!set || !alloc) return NO;
    SEL sel = sel_getUid("containsAllocation:");
    return ((BOOL (*)(id, SEL, id))objc_msgSend)(set, sel, alloc);
}

MT_INLINE unsigned long mt_residency_set_get_allocation_count(MTResidencySet set) {
    if (!set) return 0;
    SEL sel = sel_getUid("allocationCount");
    return ((unsigned long (*)(id, SEL))objc_msgSend)(set, sel);
}

MT_INLINE uint64_t mt_residency_set_get_allocated_size(MTResidencySet set) {
    if (!set) return 0;
    SEL sel = sel_getUid("allocatedSize");
    return ((uint64_t (*)(id, SEL))objc_msgSend)(set, sel);
}

MT_INLINE void mt_residency_set_commit(MTResidencySet set) {
    if (!set) return;
    SEL sel = sel_getUid("commit");
    ((void (*)(id, SEL))objc_msgSend)(set, sel);
}

// TODO: I'm holding off from implementing this till I figure out how to handle this approprately...
// @property (readonly, copy, nonnull) NSArray<id<MTLAllocation>> *allAllocations;
