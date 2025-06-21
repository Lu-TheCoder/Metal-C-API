//
//  MT4CommandBuffer.h
//  Metal C
//
//  Created by Lungile Maseko on 2025/06/20.
//
#pragma once
#include "MTUtils.h"
#include "MTTypes.h"
#include "MT4RenderCommandEncoder.h"

typedef void* MT4CommandBufferOptions;
typedef void* MT4MachineLearningCommandEncoder;
typedef void* MT4ComputeCommandEncoder;
typedef void* MT4RenderCommandEncoder;
typedef void* MT4RenderPassDescriptor;
typedef void* MT4CounterHeap;
typedef void* MT4CommandBuffer;
typedef void* MTLogState;
typedef void* MTFence;

MT_INLINE void mt4_command_buffer_options_set_log_state(MT4CommandBufferOptions options, MTLogState logState) {
    if (!options) return;
    SEL sel = sel_getUid("setLogState:");
    ((void (*)(id, SEL, id))objc_msgSend)(options, sel, logState);
}

MT_INLINE MTLogState mt4_command_buffer_options_get_log_state(MT4CommandBufferOptions options) {
    if (!options) return NULL;
    SEL sel = sel_getUid("logState");
    return ((MTLogState (*)(id, SEL))objc_msgSend)(options, sel);
}

MT_INLINE MTDevice mt4_command_buffer_get_device(MT4CommandBuffer cmd) {
    if (!cmd) return NULL;
    SEL sel = sel_getUid("device");
    return ((MTDevice (*)(id, SEL))objc_msgSend)(cmd, sel);
}

MT_INLINE void mt4_command_buffer_set_label(MT4CommandBuffer cmd, const char* label) {
    if (!cmd || !label) return;
    id nsLabel = ((id (*)(Class, SEL, const char*))objc_msgSend)(objc_getClass("NSString"),
        sel_getUid("stringWithUTF8String:"), label);
    SEL sel = sel_getUid("setLabel:");
    ((void (*)(id, SEL, id))objc_msgSend)(cmd, sel, nsLabel);
}

MT_INLINE void mt4_command_buffer_begin_with_allocator(MT4CommandBuffer cmd, MT4CommandAllocator allocator) {
    if (!cmd || !allocator) return;
    SEL sel = sel_getUid("beginCommandBufferWithAllocator:");
    ((void (*)(id, SEL, id))objc_msgSend)(cmd, sel, allocator);
}

MT_INLINE void mt4_command_buffer_begin_with_allocator_options(MT4CommandBuffer cmd, MT4CommandAllocator allocator, MT4CommandBufferOptions options) {
    if (!cmd || !allocator || !options) return;
    SEL sel = sel_getUid("beginCommandBufferWithAllocator:options:");
    ((void (*)(id, SEL, id, id))objc_msgSend)(cmd, sel, allocator, options);
}

MT_INLINE void mt4_command_buffer_end(MT4CommandBuffer cmd) {
    if (!cmd) return;
    SEL sel = sel_getUid("endCommandBuffer");
    ((void (*)(id, SEL))objc_msgSend)(cmd, sel);
}

MT_INLINE MT4RenderCommandEncoder mt4_command_buffer_render_encoder_create(MT4CommandBuffer cmd, MT4RenderPassDescriptor desc) {
    if (!cmd || !desc) return NULL;
    SEL sel = sel_getUid("renderCommandEncoderWithDescriptor:");
    return ((MT4RenderCommandEncoder (*)(id, SEL, id))objc_msgSend)(cmd, sel, desc);
}

MT_INLINE MT4RenderCommandEncoder mt4_command_buffer_render_encoder_create_with_options(
    MT4CommandBuffer cmd, MT4RenderPassDescriptor desc, MT4RenderEncoderOptions opts) {
    if (!cmd || !desc) return NULL;
    SEL sel = sel_getUid("renderCommandEncoderWithDescriptor:options:");
    return ((MT4RenderCommandEncoder (*)(id, SEL, id, MT4RenderEncoderOptions))objc_msgSend)(cmd, sel, desc, opts);
}

MT_INLINE MT4ComputeCommandEncoder mt4_command_buffer_compute_encoder_create(MT4CommandBuffer cmd) {
    if (!cmd) return NULL;
    SEL sel = sel_getUid("computeCommandEncoder");
    return ((MT4ComputeCommandEncoder (*)(id, SEL))objc_msgSend)(cmd, sel);
}

MT_INLINE MT4MachineLearningCommandEncoder mt4_command_buffer_ml_encoder(MT4CommandBuffer cmd) {
    if (!cmd) return NULL;
    SEL sel = sel_getUid("machineLearningCommandEncoder");
    return ((MT4MachineLearningCommandEncoder (*)(id, SEL))objc_msgSend)(cmd, sel);
}

MT_INLINE void mt4_command_buffer_use_residency_set(MT4CommandBuffer cmd, MTResidencySet set) {
    if (!cmd || !set) return;
    SEL sel = sel_getUid("useResidencySet:");
    ((void (*)(id, SEL, id))objc_msgSend)(cmd, sel, set);
}

MT_INLINE void mt4_command_buffer_use_residency_sets(MT4CommandBuffer cmd, const MTResidencySet* sets, unsigned long count) {
    if (!cmd || !sets || !count) return;
    SEL sel = sel_getUid("useResidencySets:count:");
    ((void (*)(id, SEL, const id*, unsigned long))objc_msgSend)(cmd, sel, sets, count);
}

MT_INLINE void mt4_command_buffer_push_debug_group(MT4CommandBuffer cmd, const char* str) {
    if (!cmd || !str) return;
    id nsStr = ((id (*)(Class, SEL, const char*))objc_msgSend)(objc_getClass("NSString"),
        sel_getUid("stringWithUTF8String:"), str);
    SEL sel = sel_getUid("pushDebugGroup:");
    ((void (*)(id, SEL, id))objc_msgSend)(cmd, sel, nsStr);
}

MT_INLINE void mt4_command_buffer_pop_debug_group(MT4CommandBuffer cmd) {
    if (!cmd) return;
    SEL sel = sel_getUid("popDebugGroup");
    ((void (*)(id, SEL))objc_msgSend)(cmd, sel);
}

MT_INLINE void mt4_command_buffer_write_timestamp_into_heap(MT4CommandBuffer cmd, MT4CounterHeap heap, unsigned long index) {
    if (!cmd || !heap) return;
    SEL sel = sel_getUid("writeTimestampIntoHeap:atIndex:");
    ((void (*)(id, SEL, id, unsigned long ))objc_msgSend)(cmd, sel, heap, index);
}

MT_INLINE void mt4_command_buffer_resolve_counter_heap(
    MT4CommandBuffer cmd, MT4CounterHeap heap, MTRange range,
    MTBuffer buffer, unsigned long  offset, MTFence fenceWait, MTFence fenceUpdate
) {
    if (!cmd || !heap || !buffer) return;
    SEL sel = sel_getUid("resolveCounterHeap:withRange:intoBuffer:atOffset:waitFence:updateFence:");
    ((void (*)(id, SEL, id, MTRange, id, unsigned long , id, id))objc_msgSend)(
        cmd, sel, heap, range, buffer, offset, fenceWait, fenceUpdate
    );
}
