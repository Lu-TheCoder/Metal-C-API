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
MT_INLINE MTRenderPipelineColorAttachmentDescriptor mt_renderPipeline_color_attachment_descriptor_new(void) {
    Class cls = objc_getClass("MTLRenderPipelineColorAttachmentDescriptor");

    // [MTLRenderPipelineColorAttachmentDescriptor alloc]
    SEL allocSel = sel_registerName("alloc");
    id (*allocFn)(Class, SEL) = (id (*)(Class, SEL))objc_msgSend;
    id obj = allocFn(cls, allocSel);

    // [[... alloc] init]
    SEL initSel = sel_registerName("init");
    id (*initFn)(id, SEL) = (id (*)(id, SEL))objc_msgSend;
    obj = initFn(obj, initSel);

    return obj;
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
// 1. Create a new MTLRenderPipelineDescriptor instance
MT_INLINE MTRenderPipelineDescriptor mt_render_pipeline_descriptor_new(void) {
    Class renderPipeDesc = objc_getClass("MTLRenderPipelineDescriptor");

    // [MTLRenderPipelineDescriptor alloc]
    SEL allocSel = sel_registerName("alloc");
    id (*allocFn)(Class, SEL) = (id (*)(Class, SEL))objc_msgSend;
    id allocInstance = allocFn(renderPipeDesc, allocSel);

    // [[MTLRenderPipelineDescriptor alloc] init]
    SEL initSel = sel_registerName("init");
    id (*initFn)(id, SEL) = (id (*)(id, SEL))objc_msgSend;
    return initFn(allocInstance, initSel);
}

// 2. Get colorAttachments property
MT_INLINE MTRenderPipelineColorAttachmentDescriptorArray mt_render_pipeline_get_color_attachments(MTRenderPipelineDescriptor render_pipeline_desc) {
    SEL sel = sel_registerName("colorAttachments");
    MTRenderPipelineColorAttachmentDescriptorArray (*getter)(id, SEL) =
        (MTRenderPipelineColorAttachmentDescriptorArray (*)(id, SEL))objc_msgSend;
    return getter((id)render_pipeline_desc, sel);
}

// 3. Get color attachment at a specific index using subscripting
MT_INLINE MTRenderPipelineColorAttachmentDescriptor mt_render_pipeline_get_color_attachment_at_index(MTRenderPipelineColorAttachmentDescriptorArray array, unsigned long color_attach_index) {
    SEL sel = sel_registerName("objectAtIndexedSubscript:");
    MTRenderPipelineColorAttachmentDescriptor (*getAtIndex)(id, SEL, NSUInteger) =
        (MTRenderPipelineColorAttachmentDescriptor (*)(id, SEL, NSUInteger))objc_msgSend;
    return getAtIndex((id)array, sel, color_attach_index);
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

// -------------------
// Setters
// -------------------

MT_INLINE void mt_render_pipeline_descriptor_set_vertex_function(MTRenderPipelineDescriptor renderPipelineDesc, MTFunction* vertFunction) {
    SEL sel = sel_registerName("setVertexFunction:");
    void (*msgSendVoidId)(id, SEL, id) = (void (*)(id, SEL, id))objc_msgSend;
    msgSendVoidId((id)renderPipelineDesc, sel, (id)vertFunction);
}

MT_INLINE void mt_render_pipeline_descriptor_set_fragment_function(MTRenderPipelineDescriptor renderPipelineDesc, MTFunction* fragFunction) {
    SEL sel = sel_registerName("setFragmentFunction:");
    void (*msgSendVoidId)(id, SEL, id) = (void (*)(id, SEL, id))objc_msgSend;
    msgSendVoidId((id)renderPipelineDesc, sel, (id)fragFunction);
}

MT_INLINE void mt_render_pipeline_descriptor_set_vertex_descriptor(MTRenderPipelineDescriptor renderPipelineDesc, MTVertexDescriptor* vertDesc) {
    SEL sel = sel_registerName("setVertexDescriptor:");
    void (*msgSendVoidId)(id, SEL, id) = (void (*)(id, SEL, id))objc_msgSend;
    msgSendVoidId((id)renderPipelineDesc, sel, (id)vertDesc);
}

MT_INLINE void mt_render_pipeline_descriptor_set_raster_sample_count(MTRenderPipelineDescriptor renderPipelineDesc, uintptr_t count) {
    SEL sel = sel_registerName("setRasterSampleCount:");
    void (*msgSendVoidUInt)(id, SEL, uintptr_t) = (void (*)(id, SEL, uintptr_t))objc_msgSend;
    msgSendVoidUInt((id)renderPipelineDesc, sel, count);
}

MT_INLINE void mt_render_pipeline_descriptor_set_depth_attachment_pixel_format(MTRenderPipelineDescriptor desc, MTPixelFormat format) {
    SEL sel = sel_registerName("setDepthAttachmentPixelFormat:");
    void (*msgSendVoidUInt)(id, SEL, MTPixelFormat) = (void (*)(id, SEL, MTPixelFormat))objc_msgSend;
    msgSendVoidUInt((id)desc, sel, format);
}

MT_INLINE void mt_render_pipeline_descriptor_set_stencil_attachment_pixel_format(MTRenderPipelineDescriptor desc, MTPixelFormat format) {
    SEL sel = sel_registerName("setStencilAttachmentPixelFormat:");
    void (*msgSendVoidUInt)(id, SEL, MTPixelFormat) = (void (*)(id, SEL, MTPixelFormat))objc_msgSend;
    msgSendVoidUInt((id)desc, sel, format);
}

MT_INLINE void mt_render_pipeline_descriptor_set_color_attachments_pixel_format(MTRenderPipelineDescriptor renderPipelineDesc, unsigned long color_attach_index, MTPixelFormat format) {
    // Get colorAttachments: [renderPipelineDesc colorAttachments]
    SEL sel_colorAttachments = sel_registerName("colorAttachments");
    MTRenderPipelineColorAttachmentDescriptorArray (*msgSendColorAttachments)(id, SEL) =
        (MTRenderPipelineColorAttachmentDescriptorArray (*)(id, SEL))objc_msgSend;
    MTRenderPipelineColorAttachmentDescriptorArray attachments = msgSendColorAttachments((id)renderPipelineDesc, sel_colorAttachments);

    // Get colorAttachment at index: [attachments objectAtIndexedSubscript:index]
    SEL sel_atIndex = sel_registerName("objectAtIndexedSubscript:");
    MTRenderPipelineColorAttachmentDescriptor (*msgSendAtIndex)(id, SEL, NSUInteger) =
        (MTRenderPipelineColorAttachmentDescriptor (*)(id, SEL, NSUInteger))objc_msgSend;
    MTRenderPipelineColorAttachmentDescriptor attachment = msgSendAtIndex((id)attachments, sel_atIndex, color_attach_index);

    // Set pixel format: [attachment setPixelFormat:format]
    SEL sel_setPixelFormat = sel_registerName("setPixelFormat:");
    void (*msgSendSetPixelFormat)(id, SEL, MTPixelFormat) =
        (void (*)(id, SEL, MTPixelFormat))objc_msgSend;
    msgSendSetPixelFormat((id)attachment, sel_setPixelFormat, format);
}

MT_INLINE void mt_render_pipeline_descriptor_reset(MTRenderPipelineDescriptor desc) {
    SEL sel_reset = sel_registerName("reset");
    void (*msgSendReset)(id, SEL) = (void (*)(id, SEL))objc_msgSend;
    msgSendReset((id)desc, sel_reset);
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
