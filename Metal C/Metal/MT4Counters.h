//
//  MT4Counters.h
//  Metal C
//
//  Created by Lungile Maseko on 2025/06/21.
//
#pragma once
#include "MTTypes.h"

/// Represents a timestamp data entry in a counter heap of type `MTL4CounterHeapTypeTimestamp`.
typedef struct
{
    uint64_t timestamp;
} MT4TimestampHeapEntry;

/// Defines the type of a ``MTL4CounterHeap`` and the contents of its entries.
typedef enum MT4CounterHeapType {
    /// Specifies that ``MTL4CounterHeap`` entries contain invalid data.
    MT4CounterHeapTypeInvalid,
    
    /// Specifies that ``MTL4CounterHeap`` entries contain GPU timestamp data.
    MT4CounterHeapTypeTimestamp,
} MT4CounterHeapType;

typedef enum MT4TimestampGranularity {
    /// A minimally-invasive timestamp which may be less precise.
    ///
    /// Using this granularity incurs in the lowest overhead, at the cost of precision. For example, it may sample at
    /// command encoder boundaries.
    MT4TimestampGranularityRelaxed = 0,
    
    /// A timestamp as precise as possible.
    ///
    /// Using this granularity may incur in a performance penalty, for example, it may cause splitting of command encoders.
    MT4TimestampGranularityPrecise = 1,
} MT4TimestampGranularity;

typedef void* MT4CounterHeapDescriptor;
typedef void* MT4CounterHeap;
typedef void* MTData;

MT_INLINE void mt4_counter_heap_descriptor_set_type(MT4CounterHeapDescriptor desc, MT4CounterHeapType type) {
    if (!desc) return;
    ((void (*)(void*, SEL, MT4CounterHeapType))objc_msgSend)(
        desc,
        sel_getUid("setType:"),
        type
    );
}

MT_INLINE MT4CounterHeapType mt4_counter_heap_descriptor_get_type(MT4CounterHeapDescriptor desc) {
    if (!desc) return 0;
    return ((MT4CounterHeapType (*)(void*, SEL))objc_msgSend)(
        desc,
        sel_getUid("type")
    );
}

MT_INLINE void mt4_counter_heap_descriptor_set_entry_count(MT4CounterHeapDescriptor desc, NSUInteger count) {
    if (!desc) return;
    ((void (*)(void*, SEL, NSUInteger))objc_msgSend)(
        desc,
        sel_getUid("setEntryCount:"),
        count
    );
}

MT_INLINE NSUInteger mt4_counter_heap_descriptor_get_entry_count(MT4CounterHeapDescriptor desc) {
    if (!desc) return 0;
    return ((NSUInteger (*)(void*, SEL))objc_msgSend)(
        desc,
        sel_getUid("entryCount")
    );
}

MT_INLINE NSUInteger mt4_counter_heap_get_count(MT4CounterHeap heap) {
    if (!heap) return 0;
    return ((NSUInteger (*)(void*, SEL))objc_msgSend)(
        heap,
        sel_getUid("count")
    );
}

MT_INLINE MT4CounterHeapType mt4_counter_heap_get_type(MT4CounterHeap heap) {
    if (!heap) return 0;
    return ((MT4CounterHeapType (*)(void*, SEL))objc_msgSend)(
        heap,
        sel_getUid("type")
    );
}

MT_INLINE MTData mt4_counter_heap_resolve_counter_range(MT4CounterHeap heap, MTRange range) {
    if (!heap) return nil;
    return ((MTData (*)(void*, SEL, MTRange))objc_msgSend)(
        heap,
        sel_getUid("resolveCounterRange:"),
        range
    );
}

MT_INLINE void mt4_counter_heap_invalidate_counter_range(MT4CounterHeap heap, MTRange range) {
    if (!heap) return;
    ((void (*)(void*, SEL, MTRange))objc_msgSend)(
        heap,
        sel_getUid("invalidateCounterRange:"),
        range
    );
}

MT_INLINE void mt4_counter_heap_set_label(MT4CounterHeap heap, const char* label) {
    if (!heap || !label) return;

    SEL sel = sel_getUid("setLabel:");
    id nsLabel = ((id (*)(Class, SEL, const char*))objc_msgSend)(
        objc_getClass("NSString"),
        sel_getUid("stringWithUTF8String:"),
        label
    );

    ((void (*)(id, SEL, id))objc_msgSend)(heap, sel, nsLabel);
}
