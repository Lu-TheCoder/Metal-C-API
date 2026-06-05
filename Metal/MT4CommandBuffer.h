//
//  MT4CommandBuffer.h
//  Metal C
//
//  MTL4CommandBuffer — the Metal 4 command buffer. Unlike the classic
//  MTCommandBuffer (obtained from a queue, single-use, auto-managed), an
//  MTL4CommandBuffer is created once from the device and reused: each frame you
//  call begin (binding a command allocator), encode work, call end, then submit
//  it via mt4_command_queue_commit.
//
//  Typical frame:
//    mt4_command_buffer_begin(cmd, allocator);
//    MT4RenderCommandEncoder enc = mt4_command_buffer_get_render_encoder(cmd, pass);
//    ... encode ...
//    mt4_command_buffer_end(cmd);
//    mt4_command_queue_commit(queue, &cmd, 1);
//

#pragma once
#include "MTFoundation/defines.h"
#include "MTFoundation/MTString.h"  // mt_object_set_label
#include "MTTypes.h"                // NSUInteger

// ---- Command buffer options ----------------------------------------------

MT_INLINE MT4CommandBufferOptions mt4_command_buffer_options_create(void) {
    return MT_ALLOC_INIT("MTL4CommandBufferOptions");
}

MT_INLINE void mt4_command_buffer_options_set_label(MT4CommandBufferOptions options, const char* label) {
    mt_object_set_label(options, label);
}

// ---- Command buffer (created via the device) -----------------------------

MT_INLINE MT4CommandBuffer mt4_device_create_command_buffer(MTDevice device) {
    return MT_MSG_SEND(void*, device, MT_SEL("newCommandBuffer"));
}

MT_INLINE void mt4_command_buffer_set_label(MT4CommandBuffer cmd_buf, const char* label) {
    mt_object_set_label(cmd_buf, label);
}

// ---- Recording lifecycle -------------------------------------------------

// Bind a command allocator and begin recording. Any previous useResidencySet
// calls on this command buffer are cleared — set residency again after begin.
MT_INLINE void mt4_command_buffer_begin(MT4CommandBuffer cmd_buf, MT4CommandAllocator allocator) {
    MT_MSG_SEND_1(void, cmd_buf, MT_SEL("beginCommandBufferWithAllocator:"), id, allocator);
}

MT_INLINE void mt4_command_buffer_begin_with_options(MT4CommandBuffer cmd_buf, MT4CommandAllocator allocator, MT4CommandBufferOptions options) {
    MT_MSG_SEND_2(void, cmd_buf, MT_SEL("beginCommandBufferWithAllocator:options:"), id, allocator, id, options);
}

MT_INLINE void mt4_command_buffer_end(MT4CommandBuffer cmd_buf) {
    MT_MSG_SEND(void, cmd_buf, MT_SEL("endCommandBuffer"));
}

// ---- Encoders (transient — owned by the command buffer, do not release) --

MT_INLINE MT4RenderCommandEncoder mt4_command_buffer_get_render_encoder(MT4CommandBuffer cmd_buf, MT4RenderPassDescriptor descriptor) {
    return MT_MSG_SEND_1(void*, cmd_buf, MT_SEL("renderCommandEncoderWithDescriptor:"), id, descriptor);
}

MT_INLINE MT4ComputeCommandEncoder mt4_command_buffer_get_compute_encoder(MT4CommandBuffer cmd_buf) {
    return MT_MSG_SEND(void*, cmd_buf, MT_SEL("computeCommandEncoder"));
}

MT_INLINE MT4MachineLearningCommandEncoder mt4_command_buffer_get_machine_learning_encoder(MT4CommandBuffer cmd_buf) {
    return MT_MSG_SEND(void*, cmd_buf, MT_SEL("machineLearningCommandEncoder"));
}

// ---- Residency -----------------------------------------------------------

MT_INLINE void mt4_command_buffer_use_residency_set(MT4CommandBuffer cmd_buf, MTResidencySet set) {
    MT_MSG_SEND_1(void, cmd_buf, MT_SEL("useResidencySet:"), id, set);
}

MT_INLINE void mt4_command_buffer_use_residency_sets(MT4CommandBuffer cmd_buf, const MTResidencySet* sets, NSUInteger count) {
    ((void (*)(id, SEL, const id*, NSUInteger))objc_msgSend)(
        (id)cmd_buf, MT_SEL("useResidencySets:count:"), (const id*)sets, count);
}

// ---- Debug groups --------------------------------------------------------

MT_INLINE void mt4_command_buffer_push_debug_group(MT4CommandBuffer cmd_buf, const char* name) {
    id ns = mt_string_create(name);
    MT_MSG_SEND_1(void, cmd_buf, MT_SEL("pushDebugGroup:"), id, ns);
    mt_string_release(ns);
}

MT_INLINE void mt4_command_buffer_pop_debug_group(MT4CommandBuffer cmd_buf) {
    MT_MSG_SEND(void, cmd_buf, MT_SEL("popDebugGroup"));
}
