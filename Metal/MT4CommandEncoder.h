//
//  MT4CommandEncoder.h
//  Metal C
//
//  Shared base of every Metal 4 encoder (render / compute / ML). The MTL4
//  encoders all conform to the MTL4CommandEncoder protocol, so these functions
//  take the base MT4CommandEncoder handle — pass any concrete encoder with an
//  explicit cast, e.g.:
//      mt4_command_encoder_end_encoding((MT4CommandEncoder)render_encoder);
//
//  These replace the classic memory-barrier / fence model: MTL4 barriers are
//  expressed in terms of MTStages (pipeline stages) with explicit cache-
//  visibility options.
//

#pragma once
#include "MTFoundation/defines.h"
#include "MTFoundation/MTString.h"  // mt_object_set_label / mt_string_*

// Pipeline stages a barrier / fence applies to (Metal's MTLStages).
typedef enum MTStages : unsigned long {
    MTStageVertex                = 1 << 0,
    MTStageFragment              = 1 << 1,
    MTStageTile                  = 1 << 2,
    MTStageObject                = 1 << 3,
    MTStageMesh                  = 1 << 4,
    MTStageResourceState         = 1 << 26,
    MTStageDispatch              = 1 << 27,
    MTStageBlit                  = 1 << 28,
    MTStageAccelerationStructure = 1 << 29,
    MTStageMachineLearning       = 1 << 30,
} MTStages;

// Cache-flush behaviour for MTL4 barriers (Metal's MTL4VisibilityOptions).
typedef enum MT4VisibilityOptions : unsigned long {
    MT4VisibilityOptionNone          = 0,
    MT4VisibilityOptionDevice        = 1 << 0,
    MT4VisibilityOptionResourceAlias = 1 << 1,
} MT4VisibilityOptions;

// ---- Debug + lifecycle ---------------------------------------------------

MT_INLINE void mt4_command_encoder_set_label(MT4CommandEncoder encoder, const char* label) {
    mt_object_set_label(encoder, label);
}

MT_INLINE void mt4_command_encoder_insert_debug_signpost(MT4CommandEncoder encoder, const char* str) {
    id ns = mt_string_create(str);
    MT_MSG_SEND_1(void, encoder, MT_SEL("insertDebugSignpost:"), id, ns);
    mt_string_release(ns);
}

MT_INLINE void mt4_command_encoder_push_debug_group(MT4CommandEncoder encoder, const char* name) {
    id ns = mt_string_create(name);
    MT_MSG_SEND_1(void, encoder, MT_SEL("pushDebugGroup:"), id, ns);
    mt_string_release(ns);
}

MT_INLINE void mt4_command_encoder_pop_debug_group(MT4CommandEncoder encoder) {
    MT_MSG_SEND(void, encoder, MT_SEL("popDebugGroup"));
}

MT_INLINE void mt4_command_encoder_end_encoding(MT4CommandEncoder encoder) {
    MT_MSG_SEND(void, encoder, MT_SEL("endEncoding"));
}

// ---- Barriers ------------------------------------------------------------

// Consumer barrier: work in this encoder for `before_stages` waits on prior
// command-queue work for `after_queue_stages`.
MT_INLINE void mt4_command_encoder_barrier_after_queue_stages(MT4CommandEncoder encoder, MTStages after_queue_stages, MTStages before_stages, MT4VisibilityOptions options) {
    MT_MSG_SEND_3(void, encoder, MT_SEL("barrierAfterQueueStages:beforeStages:visibilityOptions:"), MTStages, after_queue_stages, MTStages, before_stages, MT4VisibilityOptions, options);
}

// Producer barrier: subsequent encoders' `before_queue_stages` wait on this
// encoder's `after_stages`.
MT_INLINE void mt4_command_encoder_barrier_after_stages(MT4CommandEncoder encoder, MTStages after_stages, MTStages before_queue_stages, MT4VisibilityOptions options) {
    MT_MSG_SEND_3(void, encoder, MT_SEL("barrierAfterStages:beforeQueueStages:visibilityOptions:"), MTStages, after_stages, MTStages, before_queue_stages, MT4VisibilityOptions, options);
}

// Intra-pass barrier within this single encoder.
MT_INLINE void mt4_command_encoder_barrier_after_encoder_stages(MT4CommandEncoder encoder, MTStages after_encoder_stages, MTStages before_encoder_stages, MT4VisibilityOptions options) {
    MT_MSG_SEND_3(void, encoder, MT_SEL("barrierAfterEncoderStages:beforeEncoderStages:visibilityOptions:"), MTStages, after_encoder_stages, MTStages, before_encoder_stages, MT4VisibilityOptions, options);
}

// ---- Fences --------------------------------------------------------------

MT_INLINE void mt4_command_encoder_update_fence(MT4CommandEncoder encoder, MTFence fence, MTStages after_encoder_stages) {
    MT_MSG_SEND_2(void, encoder, MT_SEL("updateFence:afterEncoderStages:"), id, fence, MTStages, after_encoder_stages);
}

MT_INLINE void mt4_command_encoder_wait_for_fence(MT4CommandEncoder encoder, MTFence fence, MTStages before_encoder_stages) {
    MT_MSG_SEND_2(void, encoder, MT_SEL("waitForFence:beforeEncoderStages:"), id, fence, MTStages, before_encoder_stages);
}
