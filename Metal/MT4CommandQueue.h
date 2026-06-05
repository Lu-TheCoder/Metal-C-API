//
//  MT4CommandQueue.h
//  Metal C
//
//  MTL4CommandQueue — submits MTL4 command buffers, and handles GPU/CPU and
//  presentation synchronization (events + drawables) and residency-set
//  attachment for the Metal 4 model.
//

#pragma once
#include "MTFoundation/defines.h"
#include "MTFoundation/MTString.h"  // mt_object_set_label
#include "MTTypes.h"                // NSUInteger
#include <stdint.h>
#include <dispatch/dispatch.h>

// ---- Commit options ------------------------------------------------------

MT_INLINE MT4CommitOptions mt4_commit_options_create(void) {
    return MT_ALLOC_INIT("MTL4CommitOptions");
}

// ---- Queue descriptor ----------------------------------------------------

MT_INLINE MT4CommandQueueDescriptor mt4_command_queue_descriptor_create(void) {
    return MT_ALLOC_INIT("MTL4CommandQueueDescriptor");
}

MT_INLINE void mt4_command_queue_descriptor_set_label(MT4CommandQueueDescriptor desc, const char* label) {
    mt_object_set_label(desc, label);
}

// The dispatch queue on which commit-feedback handlers are invoked.
MT_INLINE void mt4_command_queue_descriptor_set_feedback_queue(MT4CommandQueueDescriptor desc, dispatch_queue_t queue) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setFeedbackQueue:"), dispatch_queue_t, queue);
}

// ---- Queue (created via the device) --------------------------------------

MT_INLINE MT4CommandQueue mt4_device_create_command_queue(MTDevice device) {
    return MT_MSG_SEND(void*, device, MT_SEL("newMTL4CommandQueue"));
}

MT_INLINE MT4CommandQueue mt4_device_create_command_queue_with_descriptor(MTDevice device, MT4CommandQueueDescriptor desc, MTError* outError) {
    return MT_MSG_SEND_2(void*, device, MT_SEL("newMTL4CommandQueueWithDescriptor:error:"), id, desc, MTError*, outError);
}

// ---- Submission ----------------------------------------------------------

MT_INLINE void mt4_command_queue_commit(MT4CommandQueue queue, const MT4CommandBuffer* command_buffers, NSUInteger count) {
    ((void (*)(id, SEL, const id*, NSUInteger))objc_msgSend)(
        (id)queue, MT_SEL("commit:count:"), (const id*)command_buffers, count);
}

MT_INLINE void mt4_command_queue_commit_with_options(MT4CommandQueue queue, const MT4CommandBuffer* command_buffers, NSUInteger count, MT4CommitOptions options) {
    ((void (*)(id, SEL, const id*, NSUInteger, id))objc_msgSend)(
        (id)queue, MT_SEL("commit:count:options:"), (const id*)command_buffers, count, (id)options);
}

// ---- Event synchronization (MTEvent / MTSharedEvent) ---------------------

MT_INLINE void mt4_command_queue_signal_event(MT4CommandQueue queue, MTEvent event, uint64_t value) {
    MT_MSG_SEND_2(void, queue, MT_SEL("signalEvent:value:"), id, event, uint64_t, value);
}

MT_INLINE void mt4_command_queue_wait_for_event(MT4CommandQueue queue, MTEvent event, uint64_t value) {
    MT_MSG_SEND_2(void, queue, MT_SEL("waitForEvent:value:"), id, event, uint64_t, value);
}

// ---- Drawable (presentation) synchronization -----------------------------

MT_INLINE void mt4_command_queue_signal_drawable(MT4CommandQueue queue, MTDrawable drawable) {
    MT_MSG_SEND_1(void, queue, MT_SEL("signalDrawable:"), id, drawable);
}

MT_INLINE void mt4_command_queue_wait_for_drawable(MT4CommandQueue queue, MTDrawable drawable) {
    MT_MSG_SEND_1(void, queue, MT_SEL("waitForDrawable:"), id, drawable);
}

// ---- Residency sets ------------------------------------------------------

MT_INLINE void mt4_command_queue_add_residency_set(MT4CommandQueue queue, MTResidencySet set) {
    MT_MSG_SEND_1(void, queue, MT_SEL("addResidencySet:"), id, set);
}

MT_INLINE void mt4_command_queue_add_residency_sets(MT4CommandQueue queue, const MTResidencySet* sets, NSUInteger count) {
    ((void (*)(id, SEL, const id*, NSUInteger))objc_msgSend)(
        (id)queue, MT_SEL("addResidencySets:count:"), (const id*)sets, count);
}

MT_INLINE void mt4_command_queue_remove_residency_set(MT4CommandQueue queue, MTResidencySet set) {
    MT_MSG_SEND_1(void, queue, MT_SEL("removeResidencySet:"), id, set);
}
