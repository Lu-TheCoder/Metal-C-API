//
//  MTResidencySet.h
//  Metal C
//
//  MTLResidencySet — explicit residency management (macOS 15+, and the
//  Metal 4 way of keeping resources resident). You add allocations (buffers,
//  textures, heaps) to a set, commit the changes, then either request
//  residency directly or attach the set to a command queue / command buffer.
//

#pragma once
#include "MTFoundation/defines.h"
#include "MTFoundation/MTString.h"  // mt_object_set_label
#include "MTTypes.h"   // NSUInteger
#include <stdint.h>

// ---- Descriptor ----------------------------------------------------------

MT_INLINE MTResidencySetDescriptor mt_residency_set_descriptor_create(void) {
    return MT_ALLOC_INIT("MTLResidencySetDescriptor");
}

MT_INLINE void mt_residency_set_descriptor_set_label(MTResidencySetDescriptor desc, const char* label) {
    mt_object_set_label(desc, label);
}

// Hint for how many allocations the set will hold (avoids reallocation).
MT_INLINE void mt_residency_set_descriptor_set_initial_capacity(MTResidencySetDescriptor desc, NSUInteger capacity) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setInitialCapacity:"), NSUInteger, capacity);
}

// ---- Residency set (created via mt_device_create_residency_set) ----------

MT_INLINE MTResidencySet mt_device_create_residency_set(MTDevice device, MTResidencySetDescriptor desc, MTError* outError) {
    return MT_MSG_SEND_2(void*, device, MT_SEL("newResidencySetWithDescriptor:error:"), id, desc, MTError*, outError);
}

// Any MTBuffer/MTTexture/MTHeap is an MTAllocation — cast it on the way in.
MT_INLINE void mt_residency_set_add_allocation(MTResidencySet set, MTAllocation allocation) {
    MT_MSG_SEND_1(void, set, MT_SEL("addAllocation:"), id, allocation);
}

MT_INLINE void mt_residency_set_add_allocations(MTResidencySet set, const MTAllocation* allocations, NSUInteger count) {
    ((void (*)(id, SEL, const id*, NSUInteger))objc_msgSend)(
        (id)set, MT_SEL("addAllocations:count:"), (const id*)allocations, count);
}

MT_INLINE void mt_residency_set_remove_allocation(MTResidencySet set, MTAllocation allocation) {
    MT_MSG_SEND_1(void, set, MT_SEL("removeAllocation:"), id, allocation);
}

MT_INLINE void mt_residency_set_remove_all_allocations(MTResidencySet set) {
    MT_MSG_SEND(void, set, MT_SEL("removeAllAllocations"));
}

MT_INLINE bool mt_residency_set_contains_allocation(MTResidencySet set, MTAllocation allocation) {
    return MT_MSG_SEND_1(bool, set, MT_SEL("containsAllocation:"), id, allocation);
}

MT_INLINE NSUInteger mt_residency_set_get_allocation_count(MTResidencySet set) {
    return MT_MSG_SEND(NSUInteger, set, MT_SEL("allocationCount"));
}

MT_INLINE uint64_t mt_residency_set_get_allocated_size(MTResidencySet set) {
    return MT_MSG_SEND(uint64_t, set, MT_SEL("allocatedSize"));
}

// Applies all pending add/remove operations.
MT_INLINE void mt_residency_set_commit(MTResidencySet set) {
    MT_MSG_SEND(void, set, MT_SEL("commit"));
}

// Make the committed contents resident / non-resident immediately.
MT_INLINE void mt_residency_set_request_residency(MTResidencySet set) {
    MT_MSG_SEND(void, set, MT_SEL("requestResidency"));
}

MT_INLINE void mt_residency_set_end_residency(MTResidencySet set) {
    MT_MSG_SEND(void, set, MT_SEL("endResidency"));
}
