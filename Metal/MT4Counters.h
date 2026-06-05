//
//  MT4Counters.h
//  Metal C
//
//  MTL4CounterHeap — GPU timestamp sampling for profiling. Create a heap, write
//  timestamps into it from encoders / the command buffer, then resolve the
//  range back to CPU-readable bytes after the work completes.
//

#pragma once
#include "MTFoundation/defines.h"
#include "MTFoundation/MTString.h"  // mt_object_set_label
#include "MTTypes.h"                // NSUInteger, MTRange
#include <stdint.h>

// What a counter heap stores (Metal's MTL4CounterHeapType).
typedef enum MT4CounterHeapType : long {
    MT4CounterHeapTypeInvalid   = 0,
    MT4CounterHeapTypeTimestamp = 1,
} MT4CounterHeapType;

// Accuracy hint for timestamp writes (Metal's MTL4TimestampGranularity).
typedef enum MT4TimestampGranularity : long {
    MT4TimestampGranularityRelaxed = 0,
    MT4TimestampGranularityPrecise = 1,
} MT4TimestampGranularity;

// ---- Descriptor ----------------------------------------------------------

MT_INLINE MT4CounterHeapDescriptor mt4_counter_heap_descriptor_create(void) {
    return MT_ALLOC_INIT("MTL4CounterHeapDescriptor");
}

MT_INLINE void mt4_counter_heap_descriptor_set_type(MT4CounterHeapDescriptor desc, MT4CounterHeapType type) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setType:"), MT4CounterHeapType, type);
}

MT_INLINE void mt4_counter_heap_descriptor_set_count(MT4CounterHeapDescriptor desc, NSUInteger count) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setCount:"), NSUInteger, count);
}

// ---- Counter heap (created via the device) -------------------------------

MT_INLINE MT4CounterHeap mt4_device_create_counter_heap(MTDevice device, MT4CounterHeapDescriptor desc, MTError* outError) {
    return MT_MSG_SEND_2(void*, device, MT_SEL("newCounterHeapWithDescriptor:error:"), id, desc, MTError*, outError);
}

MT_INLINE void mt4_counter_heap_set_label(MT4CounterHeap heap, const char* label) {
    mt_object_set_label(heap, label);
}

MT_INLINE NSUInteger mt4_counter_heap_get_count(MT4CounterHeap heap) {
    return MT_MSG_SEND(NSUInteger, heap, MT_SEL("count"));
}

MT_INLINE MT4CounterHeapType mt4_counter_heap_get_type(MT4CounterHeap heap) {
    return MT_MSG_SEND(MT4CounterHeapType, heap, MT_SEL("type"));
}

// Resolve a range of entries to CPU-readable bytes. Returns an NSData object
// (opaque); read it with the helpers below. Call after the GPU work completes.
// `range` follows NSRange layout (location, length), matching MTRange.
MT_INLINE void* mt4_counter_heap_resolve_counter_range(MT4CounterHeap heap, MTRange range) {
    return ((void* (*)(id, SEL, MTRange))objc_msgSend)((id)heap, MT_SEL("resolveCounterRange:"), range);
}

MT_INLINE void mt4_counter_heap_invalidate_counter_range(MT4CounterHeap heap, MTRange range) {
    ((void (*)(id, SEL, MTRange))objc_msgSend)((id)heap, MT_SEL("invalidateCounterRange:"), range);
}

// Read the bytes/length of the NSData returned by resolve_counter_range.
MT_INLINE const void* mt4_counter_data_get_bytes(void* counter_data) {
    return MT_MSG_SEND(const void*, counter_data, MT_SEL("bytes"));
}

MT_INLINE NSUInteger mt4_counter_data_get_length(void* counter_data) {
    return MT_MSG_SEND(NSUInteger, counter_data, MT_SEL("length"));
}

// ---- Timestamp writes ----------------------------------------------------
// (The render-encoder variant, which takes MTRenderStages, lives in
//  MT4RenderCommandEncoder.h.)

MT_INLINE void mt4_command_buffer_write_timestamp(MT4CommandBuffer cmd_buf, MT4CounterHeap heap, NSUInteger index) {
    MT_MSG_SEND_2(void, cmd_buf, MT_SEL("writeTimestampIntoHeap:atIndex:"), id, heap, NSUInteger, index);
}

MT_INLINE void mt4_compute_command_encoder_write_timestamp(MT4ComputeCommandEncoder encoder, MT4TimestampGranularity granularity, MT4CounterHeap heap, NSUInteger index) {
    MT_MSG_SEND_3(void, encoder, MT_SEL("writeTimestampWithGranularity:intoHeap:atIndex:"), MT4TimestampGranularity, granularity, id, heap, NSUInteger, index);
}
