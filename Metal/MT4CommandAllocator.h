//
//  MT4CommandAllocator.h
//  Metal C
//
//  MTL4CommandAllocator — owns the backing memory a command buffer encodes
//  into. Reset it (once its command buffers have completed) to recycle the
//  memory for the next frame instead of allocating anew.
//

#pragma once
#include "MTFoundation/defines.h"
#include "MTFoundation/MTString.h"  // mt_object_set_label
#include <stdint.h>

// ---- Descriptor ----------------------------------------------------------

MT_INLINE MT4CommandAllocatorDescriptor mt4_command_allocator_descriptor_create(void) {
    return MT_ALLOC_INIT("MTL4CommandAllocatorDescriptor");
}

MT_INLINE void mt4_command_allocator_descriptor_set_label(MT4CommandAllocatorDescriptor desc, const char* label) {
    mt_object_set_label(desc, label);
}

// ---- Allocator (created via the device) ----------------------------------

MT_INLINE MT4CommandAllocator mt4_device_create_command_allocator(MTDevice device) {
    return MT_MSG_SEND(void*, device, MT_SEL("newCommandAllocator"));
}

MT_INLINE MT4CommandAllocator mt4_device_create_command_allocator_with_descriptor(MTDevice device, MT4CommandAllocatorDescriptor desc, MTError* outError) {
    return MT_MSG_SEND_2(void*, device, MT_SEL("newCommandAllocatorWithDescriptor:error:"), id, desc, MTError*, outError);
}

// Bytes currently backing this allocator.
MT_INLINE uint64_t mt4_command_allocator_get_allocated_size(MT4CommandAllocator allocator) {
    return MT_MSG_SEND(uint64_t, allocator, MT_SEL("allocatedSize"));
}

// Recycle the memory. Only call once all command buffers that used this
// allocator have completed execution.
MT_INLINE void mt4_command_allocator_reset(MT4CommandAllocator allocator) {
    MT_MSG_SEND(void, allocator, MT_SEL("reset"));
}
