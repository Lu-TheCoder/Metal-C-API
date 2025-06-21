//
//  MT4Archive.h
//  Metal C
//
//  Created by Lungile Maseko on 2025/06/21.
//
#pragma once

typedef void* MTError;
typedef void* MT4Archive;
typedef void* MT4BinaryFunction;
typedef void* MT4PipelineDescriptor;
typedef void* MT4BinaryFunctionDescriptor;
typedef void* MT4ComputePipelineDescriptor;
typedef void* MT4RenderPipelineDynamicLinkingDescriptor;
typedef void* MT4PipelineStageDynamicLinkingDescriptor;
typedef void* MTRenderPipelineState;
typedef void* MTComputePipelineState;

// Set label
MT_INLINE void mt4_archive_set_label(MT4Archive archive, const char* label) {
    if (!archive || !label) return;
    id nsLabel = ((id (*)(Class, SEL, const char*))objc_msgSend)(
        objc_getClass("NSString"),
        sel_getUid("stringWithUTF8String:"),
        label);
    ((void (*)(id, SEL, id))objc_msgSend)(archive, sel_getUid("setLabel:"), nsLabel);
}

// Create compute pipeline state with descriptor
MT_INLINE MTComputePipelineState mt4_archive_new_compute_pipeline_state_with_descriptor(
    MT4Archive archive,
    MT4ComputePipelineDescriptor descriptor,
    MTError *error)
{
    if (!archive || !descriptor) return nil;
    return ((MTComputePipelineState (*)(id, SEL, id, MTError*))objc_msgSend)(
        archive,
        sel_getUid("newComputePipelineStateWithDescriptor:error:"),
        descriptor,
        error
    );
}

// Create compute pipeline state with descriptor + linking
MT_INLINE MTComputePipelineState mt4_archive_new_compute_pipeline_state_with_descriptor_and_linking(
    MT4Archive archive,
    MT4ComputePipelineDescriptor descriptor,
    MT4PipelineStageDynamicLinkingDescriptor linking,
    MTError *error)
{
    if (!archive || !descriptor || !linking) return nil;
    return ((MTComputePipelineState (*)(id, SEL, id, id, MTError*))objc_msgSend)(
        archive,
        sel_getUid("newComputePipelineStateWithDescriptor:dynamicLinkingDescriptor:error:"),
        descriptor,
        linking,
        error
    );
}

// Create render pipeline state with descriptor
MT_INLINE MTRenderPipelineState mt4_archive_new_render_pipeline_state_with_descriptor(
    MT4Archive archive,
    MT4PipelineDescriptor descriptor,
    MTError *error)
{
    if (!archive || !descriptor) return nil;
    return ((MTRenderPipelineState (*)(id, SEL, id, MTError*))objc_msgSend)(
        archive,
        sel_getUid("newRenderPipelineStateWithDescriptor:error:"),
        descriptor,
        error
    );
}

// Create render pipeline state with descriptor + linking
MT_INLINE MTRenderPipelineState mt4_archive_new_render_pipeline_state_with_descriptor_and_linking(
    MT4Archive archive,
    MT4PipelineDescriptor descriptor,
    MT4RenderPipelineDynamicLinkingDescriptor linking,
    MTError *error)
{
    if (!archive || !descriptor || !linking) return nil;
    return ((MTRenderPipelineState (*)(id, SEL, id, id, MTError *))objc_msgSend)(
        archive,
        sel_getUid("newRenderPipelineStateWithDescriptor:dynamicLinkingDescriptor:error:"),
        descriptor,
        linking,
        error
    );
}

// Create binary function
MT_INLINE MT4BinaryFunction mt4_archive_new_binary_function_with_descriptor(
    MT4Archive archive,
    MT4BinaryFunctionDescriptor descriptor,
    MTError *error)
{
    if (!archive || !descriptor) return nil;
    return ((MT4BinaryFunction (*)(id, SEL, id, MTError*))objc_msgSend)(
        archive,
        sel_getUid("newBinaryFunctionWithDescriptor:error:"),
        descriptor,
        error
    );
}
