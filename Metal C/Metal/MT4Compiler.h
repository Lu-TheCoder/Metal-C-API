//
//  MT4Compiler.h
//  Metal C
//
//  Created by Lungile Maseko on 2025/06/21.
//
#pragma once
#include "MT4CompilerTask.h"
#include "MTLibrary.h"

typedef void* MTDevice;
typedef void* MTURL;
typedef void* MTLibrary;
typedef void* MTRenderPipelineState;
typedef void* MTComputePipelineState;
typedef void* MTError;
typedef void* MT4Compiler;
typedef void* MT4LibraryDescriptor;
typedef void* MT4PipelineDataSetSerializer;
typedef void* MT4PipelineStageDynamicLinkingDescriptor;
typedef void* MT4MachineLearningPipelineDescriptor;
typedef void* MT4MachineLearningPipelineState;
typedef void* MT4CompilerTaskOptions;

// BLOCKS
typedef void (^MT4NewBinaryFunctionCompletionHandler)(MT4BinaryFunction function, MTError error);
typedef void (^MT4NewMachineLearningPipelineStateCompletionHandler)(MT4MachineLearningPipelineState mlPipelineState, MTError error);


MT_INLINE MT4PipelineDataSetSerializer mt4_compiler_get_pipeline_data_set_serializer(MT4Compiler compiler) {
    if (!compiler) return nil;
    return ((MT4PipelineDataSetSerializer (*)(void*, SEL))objc_msgSend)(
        compiler,
        sel_getUid("pipelineDataSetSerializer")
    );
}

// newLibraryWithDescriptor:error:
MT_INLINE MTLibrary mt4_compiler_new_library(MT4Compiler compiler, MT4LibraryDescriptor desc, MTError *error) {
    if (!compiler || !desc) return nil;
    return ((MTLibrary (*)(void*, SEL, void*, MTError*))objc_msgSend)(
        compiler,
        sel_getUid("newLibraryWithDescriptor:error:"),
        desc,
        error
    );
}

// newDynamicLibrary:error:
MT_INLINE MTDynamicLibrary mt4_compiler_new_dynamic_library(MT4Compiler compiler, MTLibrary lib, MTError *error) {
    if (!compiler || !lib) return nil;
    return ((MTDynamicLibrary (*)(void*, SEL, void*, MTError*))objc_msgSend)(
        compiler,
        sel_getUid("newDynamicLibrary:error:"),
        lib,
        error
    );
}

MT_INLINE MTDynamicLibrary mt4_compiler_new_dynamic_library_with_url(void* compiler, void* url, void** error) {
    if (!compiler || !url) return nil;
    return ((MTDynamicLibrary (*)(void*, SEL, void*, void**))objc_msgSend)(
        compiler,
        sel_getUid("newDynamicLibraryWithURL:error:"),
        url,
        error
    );
}

MT_INLINE MTComputePipelineState mt4_compiler_new_compute_pipeline_state(
    MT4Compiler compiler,
    MT4ComputePipelineDescriptor desc,
    MT4CompilerTaskOptions opts,
    MTError* error)
{
    if (!compiler || !desc) return nil;
    return ((MTComputePipelineState (*)(void*, SEL, void*, void*, void**))objc_msgSend)(
        compiler,
        sel_getUid("newComputePipelineStateWithDescriptor:compilerTaskOptions:error:"),
        desc,
        opts,
        error
    );
}

// newComputePipelineStateWithDescriptor:dynamicLinkingDescriptor:compilerTaskOptions:error:
MT_INLINE MTComputePipelineState mt4_compiler_new_compute_pipeline_state_linked(
    MT4Compiler compiler,
    MT4ComputePipelineDescriptor desc,
    MT4PipelineStageDynamicLinkingDescriptor linking,
    MT4CompilerTaskOptions opts,
    MTError *error)
{
    if (!compiler || !desc) return nil;
    return ((MTComputePipelineState (*)(void*, SEL, void*, void*, void*, MTError*))objc_msgSend)(
        compiler,
        sel_getUid("newComputePipelineStateWithDescriptor:dynamicLinkingDescriptor:compilerTaskOptions:error:"),
        desc,
        linking,
        opts,
        error
    );
}


// newRenderPipelineStateWithDescriptor:compilerTaskOptions:error:
MT_INLINE MTRenderPipelineState mt4_compiler_new_render_pipeline_state(MT4Compiler compiler, MT4PipelineDescriptor desc, MT4CompilerTaskOptions opts, MTError *error) {
    if (!compiler || !desc) return nil;
    return ((MTRenderPipelineState (*)(void*, SEL, void*, void*, MTError*))objc_msgSend)(
        compiler,
        sel_getUid("newRenderPipelineStateWithDescriptor:compilerTaskOptions:error:"),
        desc,
        opts,
        error
    );
}

MT_INLINE MTRenderPipelineState mt4_compiler_new_render_pipeline_state_linked(
    MT4Compiler compiler,
    MT4PipelineDescriptor desc,
    MT4RenderPipelineDynamicLinkingDescriptor linking_desc,
    MT4CompilerTaskOptions opts,
    MTError *error)
{
    if (!compiler || !desc) return nil;
    return ((MTRenderPipelineState (*)(void*, SEL, void*, void*, void*, MTError*))objc_msgSend)(
        compiler,
        sel_getUid("newRenderPipelineStateWithDescriptor:dynamicLinkingDescriptor:compilerTaskOptions:error:"),
        desc,
        linking_desc,
        opts,
        error
    );
}


MT_INLINE MTRenderPipelineState mt4_compiler_new_render_pipeline_state_by_specialization(
    MT4Compiler compiler,
    MT4PipelineDescriptor desc,
    MTRenderPipelineState pipeline,
    MTError *error)
{
    if (!compiler || !desc || !pipeline) return nil;
    return ((MTRenderPipelineState (*)(void*, SEL, void*, void*, MTError*))objc_msgSend)(
        compiler,
        sel_getUid("newRenderPipelineStateBySpecializationWithDescriptor:pipeline:error:"),
        desc,
        pipeline,
        error
    );
}

MT_INLINE MT4BinaryFunction mt4_compiler_new_binary_function(
    MT4Compiler compiler,
    MT4BinaryFunctionDescriptor desc,
    MT4CompilerTaskOptions opts,
    MTError *error
) {
    if (!compiler || !desc || !error) return nil;
    return ((MT4BinaryFunction (*)(void*, SEL, void*, void*, MTError*))objc_msgSend)(
        compiler,
        sel_getUid("newBinaryFunctionWithDescriptor:compilerTaskOptions:error:"),
        desc,
        opts,
        error
    );
}

MT_INLINE MT4CompilerTask mt4_compiler_new_library_async(
    MT4Compiler compiler,
    MT4LibraryDescriptor desc,
    MTNewLibraryCompletionHandler handler
) {
    if (!compiler || !desc || !handler) return nil;
    return ((MT4CompilerTask (*)(void*, SEL, void*, MTNewLibraryCompletionHandler))objc_msgSend)(
        compiler,
        sel_getUid("newLibraryWithDescriptor:completionHandler:"),
        desc,
        handler
    );
}

MT_INLINE MT4CompilerTask mt4_compiler_new_dynamic_library_async(
    MT4Compiler compiler,
    MTLibrary library,
    MTNewLibraryCompletionHandler handler
) {
    if (!compiler || !library || !handler) return nil;
    return ((MT4CompilerTask (*)(void*, SEL, void*, MTNewLibraryCompletionHandler))objc_msgSend)(
        compiler,
        sel_getUid("newDynamicLibrary:completionHandler:"),
        library,
        handler
    );
}

MT_INLINE MT4CompilerTask mt4_compiler_new_dynamic_library_with_url_async(
    MT4Compiler compiler,
    MTURL url,
    MTNewDynamicLibraryCompletionHandler handler
) {
    if (!compiler || !url || !handler) return nil;
    return ((MT4CompilerTask (*)(void*, SEL, void*, MTNewDynamicLibraryCompletionHandler))objc_msgSend)(
        compiler,
        sel_getUid("newDynamicLibraryWithURL:error:"),
        url,
        handler
    );
}

MT_INLINE MT4CompilerTask mt4_compiler_new_compute_pipeline_state_async(
    MT4Compiler compiler,
    MT4ComputePipelineDescriptor desc,
    MT4CompilerTaskOptions opts,
    MTNewComputePipelineStateCompletionHandler handler
) {
    if (!compiler || !desc || !handler) return nil;
    return ((MT4CompilerTask (*)(void*, SEL, void*, void*, MTNewComputePipelineStateCompletionHandler))objc_msgSend)(
        compiler,
        sel_getUid("newComputePipelineStateWithDescriptor:compilerTaskOptions:completionHandler:"),
        desc,
        opts,
        handler
    );
}

MT_INLINE MT4CompilerTask mt4_compiler_new_compute_pipeline_state_linked_async(
    MT4Compiler compiler,
    MT4ComputePipelineDescriptor desc,
    MT4PipelineStageDynamicLinkingDescriptor linking_desc,
    MT4CompilerTaskOptions opts,
    MTNewComputePipelineStateCompletionHandler handler
) {
    if (!compiler || !desc || !handler) return nil;
    return ((MT4CompilerTask (*)(void*, SEL, void*, void*, void*, MTNewComputePipelineStateCompletionHandler))objc_msgSend)(
        compiler,
        sel_getUid("newComputePipelineStateWithDescriptor:dynamicLinkingDescriptor:compilerTaskOptions:completionHandler:"),
        desc,
        linking_desc,
        opts,
        handler
    );
}

MT_INLINE MT4CompilerTask mt4_compiler_new_render_pipeline_state_async(
    MT4Compiler compiler,
    MT4PipelineDescriptor desc,
    MT4CompilerTaskOptions opts,
    MTNewRenderPipelineStateCompletionHandler handler
) {
    if (!compiler || !desc || !handler) return nil;
    return ((MT4CompilerTask (*)(void*, SEL, void*, void*, MTNewRenderPipelineStateCompletionHandler))objc_msgSend)(
        compiler,
        sel_getUid("newRenderPipelineStateWithDescriptor:compilerTaskOptions:completionHandler:"),
        desc,
        opts,
        handler
    );
}

MT_INLINE MT4CompilerTask mt4_compiler_new_render_pipeline_state_linked_async(
    MT4Compiler compiler,
    MT4PipelineDescriptor desc,
    MT4RenderPipelineDynamicLinkingDescriptor linking_desc,
    MT4CompilerTaskOptions opts,
    MTNewRenderPipelineStateCompletionHandler handler
) {
    if (!compiler || !desc || !handler) return nil;
    return ((MT4CompilerTask (*)(void*, SEL, void*, void*, void*, MTNewRenderPipelineStateCompletionHandler))objc_msgSend)(
        compiler,
        sel_getUid("newRenderPipelineStateWithDescriptor:dynamicLinkingDescriptor:compilerTaskOptions:completionHandler:"),
        desc,
        linking_desc,
        opts,
        handler
    );
}

MT_INLINE MT4CompilerTask mt4_compiler_new_render_pipeline_state_by_specialization_async(
    MT4Compiler compiler,
    MT4PipelineDescriptor desc,
    MTRenderPipelineState pipeline,
    MTNewRenderPipelineStateCompletionHandler handler
) {
    if (!compiler || !desc || !pipeline || !handler) return nil;
    return ((MT4CompilerTask (*)(void*, SEL, void*, void*, MTNewRenderPipelineStateCompletionHandler))objc_msgSend)(
        compiler,
        sel_getUid("newRenderPipelineStateBySpecializationWithDescriptor:pipeline:completionHandler:"),
        desc,
        pipeline,
        handler
    );
}

MT_INLINE MT4BinaryFunction mt4_compiler_new_binary_function_async(
    MT4Compiler compiler,
    MT4BinaryFunctionDescriptor desc,
    MT4CompilerTaskOptions opts,
    MT4NewBinaryFunctionCompletionHandler handler
) {
    if (!compiler || !desc || !handler) return nil;
    return ((MT4BinaryFunction (*)(void*, SEL, void*, void*, MT4NewBinaryFunctionCompletionHandler))objc_msgSend)(
        compiler,
        sel_getUid("newBinaryFunctionWithDescriptor:compilerTaskOptions:completionHandler:"),
        desc,
        opts,
        handler
    );
}

MT_INLINE MT4MachineLearningPipelineState mt4_compiler_new_ml_pipeline_state(
    MT4Compiler compiler,
    MT4MachineLearningPipelineDescriptor desc,
    MTError error
) {
    if (!compiler || !desc || !error) return nil;
    return ((MT4MachineLearningPipelineState (*)(void*, SEL, void*, MTError*))objc_msgSend)(
        compiler,
        sel_getUid("newMachineLearningPipelineStateWithDescriptor:error:"),
        desc,
        error
    );
}

MT_INLINE MT4CompilerTask mt4_compiler_new_ml_pipeline_state_async(
    MT4Compiler compiler,
    MT4MachineLearningPipelineDescriptor desc,
    MT4NewMachineLearningPipelineStateCompletionHandler handler
) {
    if (!compiler || !desc || !handler) return nil;
    return ((MT4CompilerTask (*)(void*, SEL, void*, MT4NewMachineLearningPipelineStateCompletionHandler))objc_msgSend)(
        compiler,
        sel_getUid("newMachineLearningPipelineStateWithDescriptor:completionHandler:"),
        desc,
        handler
    );
}

// cancel
MT_INLINE void mt4_compiler_cancel(MT4Compiler compiler) {
    if (!compiler) return;
    ((void (*)(void*, SEL))objc_msgSend)(compiler, sel_getUid("cancel"));
}

// device (property getter)
MT_INLINE MTDevice mt4_compiler_get_device(MT4Compiler compiler) {
    if (!compiler) return nil;
    return ((MTDevice (*)(void*, SEL))objc_msgSend)(compiler, sel_getUid("device"));
}


