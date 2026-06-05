//
//  MT4MachineLearningPipeline.h
//  Metal C
//
//  MTL4MachineLearningPipelineDescriptor / state — for the ML command encoder
//  (see MT4MachineLearningCommandEncoder.h). Describe the network with a
//  machine-learning function descriptor, compile it via the MTL4 compiler, then
//  size the intermediates heap from the resulting state's intermediatesHeapSize.
//
//  Note: per-input tensor dimension configuration (MTLTensorExtents) is not yet
//  wrapped and is deferred.
//

#pragma once
#include "MTFoundation/defines.h"
#include "MTFoundation/MTString.h"  // mt_object_set_label
#include "MTTypes.h"                // NSUInteger

// ---- Descriptor ----------------------------------------------------------

MT_INLINE MT4MachineLearningPipelineDescriptor mt4_machine_learning_pipeline_descriptor_create(void) {
    return MT_ALLOC_INIT("MTL4MachineLearningPipelineDescriptor");
}

MT_INLINE void mt4_machine_learning_pipeline_descriptor_set_label(MT4MachineLearningPipelineDescriptor desc, const char* label) {
    mt_object_set_label(desc, label);
}

// Pass a MT4LibraryFunctionDescriptor (cast to MT4FunctionDescriptor).
MT_INLINE void mt4_machine_learning_pipeline_descriptor_set_function_descriptor(MT4MachineLearningPipelineDescriptor desc, MT4FunctionDescriptor fn) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setMachineLearningFunctionDescriptor:"), id, fn);
}

MT_INLINE void mt4_machine_learning_pipeline_descriptor_reset(MT4MachineLearningPipelineDescriptor desc) {
    MT_MSG_SEND(void, desc, MT_SEL("reset"));
}

// Attach compile-time options (e.g. to request reflection). See MT4PipelineState.h.
MT_INLINE void mt4_machine_learning_pipeline_descriptor_set_options(MT4MachineLearningPipelineDescriptor desc, MT4PipelineOptions options) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setOptions:"), id, options);
}

// ---- Compile (via the MTL4 compiler, from MT4Compiler.h) -----------------

MT_INLINE MT4MachineLearningPipelineState mt4_compiler_create_machine_learning_pipeline_state(MT4Compiler compiler, MT4MachineLearningPipelineDescriptor desc, MTError* outError) {
    return MT_MSG_SEND_2(void*, compiler, MT_SEL("newMachineLearningPipelineStateWithDescriptor:error:"), id, desc, MTError*, outError);
}

// ---- Pipeline state ------------------------------------------------------

// Minimum heap size (bytes) for the intermediate tensors this network needs.
// Pass a heap of at least this size to mt4_machine_learning_command_encoder_dispatch_network.
MT_INLINE NSUInteger mt4_machine_learning_pipeline_state_get_intermediates_heap_size(MT4MachineLearningPipelineState state) {
    return MT_MSG_SEND(NSUInteger, state, MT_SEL("intermediatesHeapSize"));
}

// Shader reflection. Non-NULL only if built with MT4ShaderReflectionBindingInfo.
// Enumerate bindings via mt4_machine_learning_pipeline_reflection_get_bindings.
MT_INLINE MT4MachineLearningPipelineReflection mt4_machine_learning_pipeline_state_get_reflection(MT4MachineLearningPipelineState state) {
    return MT_MSG_SEND(void*, state, MT_SEL("reflection"));
}

// Returns an MTArray of MTBinding (use MTArgument.h accessors).
MT_INLINE MTArray mt4_machine_learning_pipeline_reflection_get_bindings(MT4MachineLearningPipelineReflection reflection) {
    return MT_MSG_SEND(void*, reflection, MT_SEL("bindings"));
}
