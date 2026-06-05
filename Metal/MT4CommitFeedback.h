//
//  MT4CommitFeedback.h
//  Metal C
//
//  MTL4CommitFeedback — post-execution feedback for a committed set of MTL4
//  command buffers: any error, plus GPU start/end timestamps. Register a
//  callback on an MT4CommitOptions, then pass those options to
//  mt4_command_queue_commit_with_options.
//

#pragma once
#include "MTFoundation/defines.h"

// ---- Feedback accessors (valid inside your feedback callback) ------------

// nil/NULL if the commit succeeded.
MT_INLINE MTError mt4_commit_feedback_get_error(MT4CommitFeedback feedback) {
    return MT_MSG_SEND(void*, feedback, MT_SEL("error"));
}

// GPU execution start/end, in seconds (CFTimeInterval).
MT_INLINE double mt4_commit_feedback_get_gpu_start_time(MT4CommitFeedback feedback) {
    return MT_MSG_SEND(double, feedback, MT_SEL("GPUStartTime"));
}

MT_INLINE double mt4_commit_feedback_get_gpu_end_time(MT4CommitFeedback feedback) {
    return MT_MSG_SEND(double, feedback, MT_SEL("GPUEndTime"));
}

// ---- Registering a feedback handler on commit options --------------------

typedef void (*mt4_commit_feedback_callback_t)(void* userdata, MT4CommitFeedback feedback);

MT_INLINE void mt4_commit_options_add_feedback_handler(MT4CommitOptions options, mt4_commit_feedback_callback_t callback, void* userdata) {
    void (^handler)(id) = ^(id feedback) { callback(userdata, (MT4CommitFeedback)feedback); };
    MT_MSG_SEND_1(void, options, MT_SEL("addFeedbackHandler:"), void (^)(id), handler);
}
