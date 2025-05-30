//
//  MTPipeline.h
//  Metal C
//
//  Created by Lungile Maseko on 2025/05/30.
//
#pragma once
#include "MTUtils.h"

typedef enum MTMutability
{
    MTLMutabilityDefault   = 0,
    MTLMutabilityMutable   = 1,
    MTLMutabilityImmutable = 2,
}MTMutability;


typedef enum MTShaderValidation
{
    MTLShaderValidationDefault = 0,
    MTLShaderValidationEnabled = 1,
    MTLShaderValidationDisabled = 2,
}MTShaderValidation;

typedef void* MTPipelineBufferDescriptor;

MT_INLINE MTPipelineBufferDescriptor mt_pipeline_buffer_descriptor_create(void) {
    Class cls = objc_getClass("MTLPipelineBufferDescriptor");
    return (MTPipelineBufferDescriptor)((id (*)(Class, SEL))objc_msgSend)(cls, sel_getUid("new"));
}

MT_INLINE void mt_pipeline_buffer_descriptor_set_mutability(MTPipelineBufferDescriptor desc, MTMutability mutability) {
    ((void (*)(id, SEL, MTMutability))objc_msgSend)((id)desc, sel_getUid("setMutability:"), mutability);
}

MT_INLINE MTMutability mt_pipeline_buffer_descriptor_get_mutability(MTPipelineBufferDescriptor desc) {
    return ((MTMutability (*)(id, SEL))objc_msgSend)((id)desc, sel_getUid("mutability"));
}
