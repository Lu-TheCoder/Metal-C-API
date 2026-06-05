//
//  MT4ComputePipeline.h
//  Metal C
//
//  MTL4ComputePipelineDescriptor — input to mt4_compiler_create_compute_pipeline_state.
//  The compute function is set as a descriptor (MT4LibraryFunctionDescriptor,
//  created via MT4Compiler.h), not an MTFunction.
//

#pragma once
#include "MTFoundation/defines.h"
#include "MTFoundation/MTString.h"  // mt_object_set_label
#include "MTTypes.h"                // NSUInteger, MTSize
#include "MT4RenderPipeline.h"      // MT4IndirectCommandBufferSupportState

MT_INLINE MT4ComputePipelineDescriptor mt4_compute_pipeline_descriptor_create(void) {
    return MT_ALLOC_INIT("MTL4ComputePipelineDescriptor");
}

MT_INLINE void mt4_compute_pipeline_descriptor_set_label(MT4ComputePipelineDescriptor desc, const char* label) {
    mt_object_set_label(desc, label);
}

// Pass a MT4LibraryFunctionDescriptor (cast to MT4FunctionDescriptor).
MT_INLINE void mt4_compute_pipeline_descriptor_set_compute_function_descriptor(MT4ComputePipelineDescriptor desc, MT4FunctionDescriptor fn) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setComputeFunctionDescriptor:"), id, fn);
}

MT_INLINE void mt4_compute_pipeline_descriptor_set_threadgroup_size_is_multiple_of_thread_execution_width(MT4ComputePipelineDescriptor desc, bool value) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setThreadGroupSizeIsMultipleOfThreadExecutionWidth:"), BOOL, value);
}

MT_INLINE void mt4_compute_pipeline_descriptor_set_max_total_threads_per_threadgroup(MT4ComputePipelineDescriptor desc, NSUInteger value) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setMaxTotalThreadsPerThreadgroup:"), NSUInteger, value);
}

MT_INLINE void mt4_compute_pipeline_descriptor_set_required_threads_per_threadgroup(MT4ComputePipelineDescriptor desc, MTSize size) {
    ((void (*)(id, SEL, MTSize))objc_msgSend)((id)desc, MT_SEL("setRequiredThreadsPerThreadgroup:"), size);
}

MT_INLINE void mt4_compute_pipeline_descriptor_set_support_indirect_command_buffers(MT4ComputePipelineDescriptor desc, MT4IndirectCommandBufferSupportState state) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setSupportIndirectCommandBuffers:"), MT4IndirectCommandBufferSupportState, state);
}

MT_INLINE void mt4_compute_pipeline_descriptor_reset(MT4ComputePipelineDescriptor desc) {
    MT_MSG_SEND(void, desc, MT_SEL("reset"));
}

// Attach compile-time options (e.g. to request reflection). See MT4PipelineState.h.
MT_INLINE void mt4_compute_pipeline_descriptor_set_options(MT4ComputePipelineDescriptor desc, MT4PipelineOptions options) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setOptions:"), id, options);
}
