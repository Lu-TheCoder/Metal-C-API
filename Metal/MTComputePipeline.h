//
//  MTComputePipeline.h
//  Metal C
//
//  Created on 2026-05-30.
//

#pragma once
#include "MTLibrary.h"

// ============================================================================
// MTLComputePipelineDescriptor Functions
// ============================================================================

MT_INLINE MTComputePipelineDescriptor mt_compute_pipeline_descriptor_create(void) {
    return MT_ALLOC_INIT("MTLComputePipelineDescriptor");
}

MT_INLINE void mt_compute_pipeline_descriptor_set_label(MTComputePipelineDescriptor desc, const char* label) {
    id str = mt_string_create(label);
    MT_MSG_SEND_1(void, desc, MT_SEL("setLabel:"), id, str);
    mt_string_release(str);
}

MT_INLINE const char* mt_compute_pipeline_descriptor_get_label(MTComputePipelineDescriptor desc) {
    id nsStr = MT_MSG_SEND(void*, desc, MT_SEL("label"));
    if (!nsStr) return NULL;
    return MT_MSG_SEND(const char*, nsStr, MT_SEL("UTF8String"));
}

MT_INLINE void mt_compute_pipeline_descriptor_set_compute_function(MTComputePipelineDescriptor desc, MTFunction function) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setComputeFunction:"), id, function);
}

MT_INLINE MTFunction mt_compute_pipeline_descriptor_get_compute_function(MTComputePipelineDescriptor desc) {
    return MT_MSG_SEND(void*, desc, MT_SEL("computeFunction"));
}

MT_INLINE void mt_compute_pipeline_descriptor_set_thread_group_size_is_multiple_of_thread_execution_width(MTComputePipelineDescriptor desc, bool value) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setThreadGroupSizeIsMultipleOfThreadExecutionWidth:"), BOOL, value);
}

MT_INLINE bool mt_compute_pipeline_descriptor_get_thread_group_size_is_multiple_of_thread_execution_width(MTComputePipelineDescriptor desc) {
    return MT_MSG_SEND(BOOL, desc, MT_SEL("threadGroupSizeIsMultipleOfThreadExecutionWidth"));
}

MT_INLINE void mt_compute_pipeline_descriptor_set_max_total_threads_per_threadgroup(MTComputePipelineDescriptor desc, NSUInteger count) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setMaxTotalThreadsPerThreadgroup:"), NSUInteger, count);
}

MT_INLINE NSUInteger mt_compute_pipeline_descriptor_get_max_total_threads_per_threadgroup(MTComputePipelineDescriptor desc) {
    return MT_MSG_SEND(NSUInteger, desc, MT_SEL("maxTotalThreadsPerThreadgroup"));
}

// ============================================================================
// MTLComputePipelineState Functions
// ============================================================================

MT_INLINE MTDevice mt_compute_pipeline_state_get_device(MTComputePipelineState pipeline) {
    return MT_MSG_SEND(void*, pipeline, MT_SEL("device"));
}

MT_INLINE const char* mt_compute_pipeline_state_get_label(MTComputePipelineState pipeline) {
    id nsStr = MT_MSG_SEND(void*, pipeline, MT_SEL("label"));
    if (!nsStr) return NULL;
    return MT_MSG_SEND(const char*, nsStr, MT_SEL("UTF8String"));
}

MT_INLINE NSUInteger mt_compute_pipeline_state_get_max_total_threads_per_threadgroup(MTComputePipelineState pipeline) {
    return MT_MSG_SEND(NSUInteger, pipeline, MT_SEL("maxTotalThreadsPerThreadgroup"));
}

MT_INLINE NSUInteger mt_compute_pipeline_state_get_thread_execution_width(MTComputePipelineState pipeline) {
    return MT_MSG_SEND(NSUInteger, pipeline, MT_SEL("threadExecutionWidth"));
}

MT_INLINE NSUInteger mt_compute_pipeline_state_get_static_threadgroup_memory_length(MTComputePipelineState pipeline) {
    return MT_MSG_SEND(NSUInteger, pipeline, MT_SEL("staticThreadgroupMemoryLength"));
}

// Shader reflection (macOS 26+). Non-NULL only if the pipeline was built with
// reflection requested (classic: MTPipelineOptionBindingInfo; Metal 4:
// MT4ShaderReflectionBindingInfo on the pipeline options). Enumerate the
// returned bindings with mt_array_get_count + mt_array_get_binding_at_index,
// then inspect each MTBinding via the accessors in MTArgument.h.
MT_INLINE MTComputePipelineReflection mt_compute_pipeline_state_get_reflection(MTComputePipelineState pipeline) {
    return MT_MSG_SEND(void*, pipeline, MT_SEL("reflection"));
}

MT_INLINE MTArray mt_compute_pipeline_reflection_get_bindings(MTComputePipelineReflection reflection) {
    return MT_MSG_SEND(void*, reflection, MT_SEL("bindings"));
}
