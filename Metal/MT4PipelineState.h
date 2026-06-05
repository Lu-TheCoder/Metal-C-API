//
//  MT4PipelineState.h
//  Metal C
//
//  MTL4PipelineOptions — compile-time options you attach to a Metal 4 pipeline
//  descriptor (via mt4_*_pipeline_descriptor_set_options) to request shader
//  reflection and/or shader validation.
//
//  To read reflection afterwards: enable MT4ShaderReflectionBindingInfo here,
//  build the pipeline with the MTL4 compiler, then call
//  mt_render_pipeline_state_get_reflection / mt_compute_pipeline_state_get_reflection
//  on the resulting state (the MTL4 compiler returns classic state objects,
//  whose `reflection` property is populated on macOS 26+).
//

#pragma once
#include "MTFoundation/defines.h"
#include "MTPipeline.h"  // MTShaderValidation (MTLShaderValidationDefault/Enabled/Disabled)

// Metal's MTL4ShaderReflection (option mask).
typedef enum MT4ShaderReflection : unsigned long {
    MT4ShaderReflectionNone           = 0,
    MT4ShaderReflectionBindingInfo    = 1 << 0,
    MT4ShaderReflectionBufferTypeInfo = 1 << 1,
} MT4ShaderReflection;

MT_INLINE MT4PipelineOptions mt4_pipeline_options_create(void) {
    return MT_ALLOC_INIT("MTL4PipelineOptions");
}

MT_INLINE void mt4_pipeline_options_set_shader_reflection(MT4PipelineOptions options, MT4ShaderReflection reflection) {
    MT_MSG_SEND_1(void, options, MT_SEL("setShaderReflection:"), MT4ShaderReflection, reflection);
}

MT_INLINE void mt4_pipeline_options_set_shader_validation(MT4PipelineOptions options, MTShaderValidation validation) {
    MT_MSG_SEND_1(void, options, MT_SEL("setShaderValidation:"), MTShaderValidation, validation);
}
