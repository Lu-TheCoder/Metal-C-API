//
//  MTRenderPipeline.h
//  Metal C
//
//  Created by Lungile Maseko on 2024/05/29.
//

#pragma once
#include "MTLibrary.h"
#include "MTVertexDescriptor.h"
#include "MTPixelFormat.h"
#include "MTPipeline.h"

typedef void* MTRenderPipelineColorAttachmentDescriptor;
typedef void* MTRenderPipelineColorAttachmentDescriptorArray;
typedef void* MTRenderPipelineDescriptor;
typedef void* MTRenderPipelineState;

typedef enum MTBlendFactor {
    MTBlendFactorZero = 0,
    MTBlendFactorOne = 1,
    MTBlendFactorSourceColor = 2,
    MTBlendFactorOneMinusSourceColor = 3,
    MTBlendFactorSourceAlpha = 4,
    MTBlendFactorOneMinusSourceAlpha = 5,
    MTBlendFactorDestinationColor = 6,
    MTBlendFactorOneMinusDestinationColor = 7,
    MTBlendFactorDestinationAlpha = 8,
    MTBlendFactorOneMinusDestinationAlpha = 9,
    MTBlendFactorSourceAlphaSaturated = 10,
    MTBlendFactorBlendColor = 11,
    MTBlendFactorOneMinusBlendColor = 12,
    MTBlendFactorBlendAlpha = 13,
    MTBlendFactorOneMinusBlendAlpha = 14,
    MTBlendFactorSource1Color              API_AVAILABLE(macos(10.12), ios(10.11)) = 15,
    MTBlendFactorOneMinusSource1Color      API_AVAILABLE(macos(10.12), ios(10.11)) = 16,
    MTBlendFactorSource1Alpha              API_AVAILABLE(macos(10.12), ios(10.11)) = 17,
    MTBlendFactorOneMinusSource1Alpha      API_AVAILABLE(macos(10.12), ios(10.11)) = 18,
} MTBlendFactor;

typedef enum MTBlendOperation {
    MTBlendOperationAdd = 0,
    MTBlendOperationSubtract = 1,
    MTBlendOperationReverseSubtract = 2,
    MTBlendOperationMin = 3,
    MTBlendOperationMax = 4,
} MTBlendOperation;

typedef enum MTLColorWriteMask {
    MTColorWriteMaskNone  = 0,
    MTColorWriteMaskRed   = 0x1 << 3,
    MTColorWriteMaskGreen = 0x1 << 2,
    MTColorWriteMaskBlue  = 0x1 << 1,
    MTColorWriteMaskAlpha = 0x1 << 0,
    MTColorWriteMaskAll   = 0xf
} MTColorWriteMask;

typedef enum MTPrimitiveTopologyClass {
    MTPrimitiveTopologyClassUnspecified = 0,
    MTPrimitiveTopologyClassPoint = 1,
    MTPrimitiveTopologyClassLine = 2,
    MTPrimitiveTopologyClassTriangle = 3,
} MTPrimitiveTopologyClass;

typedef enum MTTessellationPartitionMode {
    MTTessellationPartitionModePow2 = 0,
    MTTessellationPartitionModeInteger = 1,
    MTTessellationPartitionModeFractionalOdd = 2,
    MTTessellationPartitionModeFractionalEven = 3,
} MTTessellationPartitionMode;

typedef enum MTLTessellationFactorStepFunction {
    MTTessellationFactorStepFunctionConstant = 0,
    MTTessellationFactorStepFunctionPerPatch = 1,
    MTTessellationFactorStepFunctionPerInstance = 2,
    MTTessellationFactorStepFunctionPerPatchAndPerInstance = 3,
} MTLTessellationFactorStepFunction;

typedef enum MTLTessellationFactorFormat {
    MTTessellationFactorFormatHalf = 0,
} MTLTessellationFactorFormat;

typedef enum MTTessellationControlPointIndexType {
    MTTessellationControlPointIndexTypeNone = 0,
    MTTessellationControlPointIndexTypeUInt16 = 1,
    MTTessellationControlPointIndexTypeUInt32 = 2,
} MTTessellationControlPointIndexType;

/**
 * @brief Creates a new MTLRenderPipelineColorAttachmentDescriptor class
 *
 * NOTE: Should be released using mtRelease();
 */
MT_INLINE MTRenderPipelineColorAttachmentDescriptor mt_renderPipeline_color_attachment_descriptor_new(void){
    Class renderPipeColorAttDesc = objc_getClass("MTLRenderPipelineColorAttachmentDescriptor");
    SEL allocSel = sel_getUid("alloc");
    
    void* attDesc = ms_send(renderPipeColorAttDesc, allocSel);
    SEL initSel = sel_getUid("init");
    ms_send(attDesc, initSel);
    return attDesc;
}

// pixelFormat property
MT_INLINE MTPixelFormat mt_render_pipeline_color_attachment_descriptor_get_pixel_format(MTRenderPipelineColorAttachmentDescriptor desc) {
    SEL sel = sel_getUid("pixelFormat");
    return ((MTPixelFormat (*)(id, SEL))objc_msgSend)(desc, sel);
}

MT_INLINE void mt_render_pipeline_color_attachment_descriptor_set_pixel_format(MTRenderPipelineColorAttachmentDescriptor desc, MTPixelFormat format) {
    SEL sel = sel_getUid("setPixelFormat:");
    ((void (*)(id, SEL, MTPixelFormat))objc_msgSend)(desc, sel, format);
}

// blendingEnabled property (note the custom getter 'isBlendingEnabled')
MT_INLINE BOOL mt_render_pipeline_color_attachment_descriptor_is_blending_enabled(MTRenderPipelineColorAttachmentDescriptor desc) {
    SEL sel = sel_getUid("isBlendingEnabled");
    return ((BOOL (*)(id, SEL))objc_msgSend)(desc, sel);
}

MT_INLINE void mt_render_pipeline_color_attachment_descriptor_set_blending_enabled(MTRenderPipelineColorAttachmentDescriptor desc, BOOL enabled) {
    SEL sel = sel_getUid("setBlendingEnabled:");
    ((void (*)(id, SEL, BOOL))objc_msgSend)(desc, sel, enabled);
}

// sourceRGBBlendFactor property
MT_INLINE MTBlendFactor mt_render_pipeline_color_attachment_descriptor_get_source_rgb_blend_factor(MTRenderPipelineColorAttachmentDescriptor desc) {
    SEL sel = sel_getUid("sourceRGBBlendFactor");
    return ((MTBlendFactor (*)(id, SEL))objc_msgSend)(desc, sel);
}

MT_INLINE void mt_render_pipeline_color_attachment_descriptor_set_source_rgb_blend_factor(MTRenderPipelineColorAttachmentDescriptor desc, MTBlendFactor factor) {
    SEL sel = sel_getUid("setSourceRGBBlendFactor:");
    ((void (*)(id, SEL, MTBlendFactor))objc_msgSend)(desc, sel, factor);
}

// destinationRGBBlendFactor property
MT_INLINE MTBlendFactor mt_render_pipeline_color_attachment_descriptor_get_destination_rgb_blend_factor(MTRenderPipelineColorAttachmentDescriptor desc) {
    SEL sel = sel_getUid("destinationRGBBlendFactor");
    return ((MTBlendFactor (*)(id, SEL))objc_msgSend)(desc, sel);
}

MT_INLINE void mt_render_pipeline_color_attachment_descriptor_set_destination_rgb_blend_factor(MTRenderPipelineColorAttachmentDescriptor desc, MTBlendFactor factor) {
    SEL sel = sel_getUid("setDestinationRGBBlendFactor:");
    ((void (*)(id, SEL, MTBlendFactor))objc_msgSend)(desc, sel, factor);
}

// rgbBlendOperation property
MT_INLINE MTBlendOperation mt_render_pipeline_color_attachment_descriptor_get_rgb_blend_operation(MTRenderPipelineColorAttachmentDescriptor desc) {
    SEL sel = sel_getUid("rgbBlendOperation");
    return ((MTBlendOperation (*)(id, SEL))objc_msgSend)(desc, sel);
}

MT_INLINE void mt_render_pipeline_color_attachment_descriptor_set_rgb_blend_operation(MTRenderPipelineColorAttachmentDescriptor desc, MTBlendOperation operation) {
    SEL sel = sel_getUid("setRgbBlendOperation:");
    ((void (*)(id, SEL, MTBlendOperation))objc_msgSend)(desc, sel, operation);
}

// sourceAlphaBlendFactor property
MT_INLINE MTBlendFactor mt_render_pipeline_color_attachment_descriptor_get_source_alpha_blend_factor(MTRenderPipelineColorAttachmentDescriptor desc) {
    SEL sel = sel_getUid("sourceAlphaBlendFactor");
    return ((MTBlendFactor (*)(id, SEL))objc_msgSend)(desc, sel);
}

MT_INLINE void mt_render_pipeline_color_attachment_descriptor_set_source_alpha_blend_factor(MTRenderPipelineColorAttachmentDescriptor desc, MTBlendFactor factor) {
    SEL sel = sel_getUid("setSourceAlphaBlendFactor:");
    ((void (*)(id, SEL, MTBlendFactor))objc_msgSend)(desc, sel, factor);
}

// destinationAlphaBlendFactor property
MT_INLINE MTBlendFactor mt_render_pipeline_color_attachment_descriptor_get_destination_alpha_blend_factor(MTRenderPipelineColorAttachmentDescriptor desc) {
    SEL sel = sel_getUid("destinationAlphaBlendFactor");
    return ((MTBlendFactor (*)(id, SEL))objc_msgSend)(desc, sel);
}

MT_INLINE void mt_render_pipeline_color_attachment_descriptor_set_destination_alpha_blend_factor(MTRenderPipelineColorAttachmentDescriptor desc, MTBlendFactor factor) {
    SEL sel = sel_getUid("setDestinationAlphaBlendFactor:");
    ((void (*)(id, SEL, MTBlendFactor))objc_msgSend)(desc, sel, factor);
}

// alphaBlendOperation property
MT_INLINE MTBlendOperation mt_render_pipeline_color_attachment_descriptor_get_alpha_blend_operation(MTRenderPipelineColorAttachmentDescriptor desc) {
    SEL sel = sel_getUid("alphaBlendOperation");
    return ((MTBlendOperation (*)(id, SEL))objc_msgSend)(desc, sel);
}

MT_INLINE void mt_render_pipeline_color_attachment_descriptor_set_alpha_blend_operation(MTRenderPipelineColorAttachmentDescriptor desc, MTBlendOperation operation) {
    SEL sel = sel_getUid("setAlphaBlendOperation:");
    ((void (*)(id, SEL, MTBlendOperation))objc_msgSend)(desc, sel, operation);
}

// writeMask property
MT_INLINE MTColorWriteMask mt_render_pipeline_color_attachment_descriptor_get_write_mask(MTRenderPipelineColorAttachmentDescriptor desc) {
    SEL sel = sel_getUid("writeMask");
    return ((MTColorWriteMask (*)(id, SEL))objc_msgSend)(desc, sel);
}

MT_INLINE void mt_render_pipeline_color_attachment_descriptor_set_write_mask(MTRenderPipelineColorAttachmentDescriptor desc, MTColorWriteMask mask) {
    SEL sel = sel_getUid("setWriteMask:");
    ((void (*)(id, SEL, MTColorWriteMask))objc_msgSend)(desc, sel, mask);
}

/**
 * @brief Creates a new MTLRenderPipelineDescriptor class
 *
 * NOTE: Should be released using mtRelease();
 */
MT_INLINE MTRenderPipelineDescriptor mt_render_pipeline_descriptor_new(void) {
    Class renderPipeDesc = objc_getClass("MTLRenderPipelineDescriptor");
    SEL allocSel = sel_getUid("alloc");
    
    void* renderDesc = ms_send(renderPipeDesc, allocSel);
    SEL initSel = sel_getUid("init");
    return ms_send(renderDesc, initSel);
}

MT_INLINE MTRenderPipelineColorAttachmentDescriptorArray mt_render_pipeline_get_color_attachments(MTRenderPipelineDescriptor* render_pipeline_desc){
    SEL sel = sel_getUid("colorAttachments");
    return ms_send(render_pipeline_desc, sel);
}

MT_INLINE MTRenderPipelineColorAttachmentDescriptor mt_render_pipeline_get_color_attachment_at_index(MTRenderPipelineColorAttachmentDescriptorArray rpcada, unsigned long color_attach_index) {
    return ms_send_uint(rpcada, sel_getUid("objectAtIndexedSubscript:"), color_attach_index);
}

MT_INLINE MTRenderPipelineColorAttachmentDescriptor
mt_render_pipeline_descriptor_get_color_attachment_at_index(MTRenderPipelineDescriptor render_pipeline_desc, unsigned long index) {
    SEL sel_colorAttachments = sel_getUid("colorAttachments");
    SEL sel_objectAtIndex = sel_getUid("objectAtIndexedSubscript:");

    // Get the colorAttachments array
    id colorAttachmentsArray = ((id (*)(id, SEL))objc_msgSend)(render_pipeline_desc, sel_colorAttachments);

    // Get the color attachment at the given index
    return ((id (*)(id, SEL, unsigned long))objc_msgSend)(colorAttachmentsArray, sel_objectAtIndex, index);
}

MT_INLINE void mt_render_pipeline_descriptor_set_label(MTRenderPipelineDescriptor desc, const char* label) {
    SEL sel = sel_getUid("setLabel:");
    id str = ((id (*)(Class, SEL, const char*))objc_msgSend)(
        objc_getClass("NSString"),
        sel_getUid("stringWithUTF8String:"),
        label
    );
    ((void (*)(id, SEL, id))objc_msgSend)(desc, sel, str);
}

MT_INLINE void mt_render_pipeline_descriptor_set_vertex_function(MTRenderPipelineDescriptor renderPipelineDesc, MTFunction* vertFunction) {
    ms_send_void(renderPipelineDesc, sel_getUid("setVertexFunction:"), vertFunction);
}

MT_INLINE void mt_render_pipeline_descriptor_set_fragment_function(MTRenderPipelineDescriptor renderPipelineDesc, MTFunction* fragFunction) {
    ms_send_void(renderPipelineDesc, sel_getUid("setFragmentFunction:"), fragFunction);
}

MT_INLINE void mt_render_pipeline_descriptor_set_vertex_descriptor(MTRenderPipelineDescriptor renderPipelineDesc, MTVertexDescriptor* vertDesc) {
    ms_send_void(renderPipelineDesc, sel_getUid("setVertexDescriptor:"), vertDesc);
}

MT_INLINE void mt_render_pipeline_descriptor_set_raster_sample_count(MTRenderPipelineDescriptor renderPipelineDesc, uintptr_t count) {
    void_ms_send_uint(renderPipelineDesc, sel_getUid("setRasterSampleCount:"), count);
}

MT_INLINE void mt_render_pipeline_descriptor_set_depth_attachment_pixel_format(MTRenderPipelineDescriptor desc, MTPixelFormat format) {
    SEL sel = sel_getUid("setDepthAttachmentPixelFormat:");
    void_ms_send_uint(desc, sel, format);
}

MT_INLINE void mt_render_pipeline_descriptor_set_stencil_attachment_pixel_format(MTRenderPipelineDescriptor desc, MTPixelFormat format) {
    SEL sel = sel_getUid("setStencilAttachmentPixelFormat:");
    void_ms_send_uint(desc, sel, format);
}

MT_INLINE void mt_render_pipeline_descriptor_set_color_attachments_pixel_format(MTRenderPipelineDescriptor renderPipelineDesc, unsigned long color_attach_index, MTPixelFormat format) {
    MTRenderPipelineColorAttachmentDescriptor* color_attachments = mt_render_pipeline_get_color_attachments(renderPipelineDesc);
    ms_send_uint(mt_render_pipeline_get_color_attachment_at_index(color_attachments, color_attach_index), sel_getUid("setPixelFormat:"), format);
}

MT_INLINE void mt_render_pipeline_descriptor_reset(MTRenderPipelineDescriptor desc) {
    SEL sel = sel_getUid("reset");
    ms_send(desc, sel);
}

MT_INLINE MTShaderValidation mt_render_pipeline_descriptor_get_shader_validation(MTRenderPipelineDescriptor desc) {
    SEL sel = sel_getUid("shaderValidation");
    return ((MTShaderValidation (*)(id, SEL))objc_msgSend)(desc, sel);
}

MT_INLINE void mt_render_pipeline_descriptor_set_shader_validation(MTRenderPipelineDescriptor desc, MTShaderValidation validation) {
    SEL sel = sel_getUid("setShaderValidation:");
    ((void (*)(id, SEL, MTShaderValidation))objc_msgSend)(desc, sel, validation);
}

// alphaToCoverageEnabled property
MT_INLINE BOOL mt_render_pipeline_descriptor_is_alpha_to_coverage_enabled(MTRenderPipelineDescriptor desc) {
    SEL sel = sel_getUid("isAlphaToCoverageEnabled");
    return ((BOOL (*)(id, SEL))objc_msgSend)(desc, sel);
}

MT_INLINE void mt_render_pipeline_descriptor_set_alpha_to_coverage_enabled(MTRenderPipelineDescriptor desc, BOOL enabled) {
    SEL sel = sel_getUid("setAlphaToCoverageEnabled:");
    ((void (*)(id, SEL, BOOL))objc_msgSend)(desc, sel, enabled);
}

// alphaToOneEnabled property
MT_INLINE BOOL mt_render_pipeline_descriptor_is_alpha_to_one_enabled(MTRenderPipelineDescriptor desc) {
    SEL sel = sel_getUid("isAlphaToOneEnabled");
    return ((BOOL (*)(id, SEL))objc_msgSend)(desc, sel);
}

MT_INLINE void mt_render_pipeline_descriptor_set_alpha_to_one_enabled(MTRenderPipelineDescriptor desc, BOOL enabled) {
    SEL sel = sel_getUid("setAlphaToOneEnabled:");
    ((void (*)(id, SEL, BOOL))objc_msgSend)(desc, sel, enabled);
}

// rasterizationEnabled property
MT_INLINE BOOL mt_render_pipeline_descriptor_is_rasterization_enabled(MTRenderPipelineDescriptor desc) {
    SEL sel = sel_getUid("isRasterizationEnabled");
    return ((BOOL (*)(id, SEL))objc_msgSend)(desc, sel);
}

MT_INLINE void mt_render_pipeline_descriptor_set_rasterization_enabled(MTRenderPipelineDescriptor desc, BOOL enabled) {
    SEL sel = sel_getUid("setRasterizationEnabled:");
    ((void (*)(id, SEL, BOOL))objc_msgSend)(desc, sel, enabled);
}
