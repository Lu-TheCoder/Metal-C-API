//
//  MTPipeline.h
//  Metal C
//
//  Created by Lungile Maseko on 2025/05/30.
//
#pragma once
#include "MTUtils.h"

typedef enum MTMutability {
    MTLMutabilityDefault   = 0,
    MTLMutabilityMutable   = 1,
    MTLMutabilityImmutable = 2,
} MTMutability;

typedef enum MTShaderValidation {
    MTLShaderValidationDefault = 0,
    MTLShaderValidationEnabled = 1,
    MTLShaderValidationDisabled = 2,
} MTShaderValidation;

typedef void* MTPipelineBufferDescriptor;

MT_INLINE MTPipelineBufferDescriptor mt_pipeline_buffer_descriptor_create(void) {
    return MT_MSG_SEND_CLASS(id, MT_CLASS("MTLPipelineBufferDescriptor"), MT_SEL("new"));
}

MT_INLINE void mt_pipeline_buffer_descriptor_set_mutability(MTPipelineBufferDescriptor desc, MTMutability mutability) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setMutability:"), MTMutability, mutability);
}

MT_INLINE MTMutability mt_pipeline_buffer_descriptor_get_mutability(MTPipelineBufferDescriptor desc) {
    return MT_MSG_SEND(MTMutability, desc, MT_SEL("mutability"));
}
