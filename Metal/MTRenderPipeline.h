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
MT_INLINE MTRenderPipelineColorAttachmentDescriptor mt_color_attachment_create(void) {
    Class cls = MT_CLASS("MTLRenderPipelineColorAttachmentDescriptor");
    id obj = MT_MSG_SEND_CLASS(void*, cls, MT_SEL("alloc"));
    return MT_MSG_SEND(void*, obj, MT_SEL("init"));
}

// ============================================================================
// Color Attachment Properties - Swift-like API
// ============================================================================

// pixelFormat
MT_INLINE MTPixelFormat mt_color_attachment_get_pixel_format(MTRenderPipelineColorAttachmentDescriptor desc) {
    return MT_MSG_SEND(MTPixelFormat, desc, MT_SEL("pixelFormat"));
}

MT_INLINE void mt_color_attachment_set_pixel_format(MTRenderPipelineColorAttachmentDescriptor desc, MTPixelFormat format) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setPixelFormat:"), MTPixelFormat, format);
}

// blendingEnabled
MT_INLINE BOOL mt_color_attachment_is_blending_enabled(MTRenderPipelineColorAttachmentDescriptor desc) {
    return MT_MSG_SEND(BOOL, desc, MT_SEL("isBlendingEnabled"));
}

MT_INLINE void mt_color_attachment_set_blending(MTRenderPipelineColorAttachmentDescriptor desc, BOOL enabled) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setBlendingEnabled:"), BOOL, enabled);
}

// sourceRGBBlendFactor
MT_INLINE MTBlendFactor mt_color_attachment_get_src_rgb_blend(MTRenderPipelineColorAttachmentDescriptor desc) {
    return MT_MSG_SEND(MTBlendFactor, desc, MT_SEL("sourceRGBBlendFactor"));
}

MT_INLINE void mt_color_attachment_set_src_rgb_blend(MTRenderPipelineColorAttachmentDescriptor desc, MTBlendFactor factor) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setSourceRGBBlendFactor:"), MTBlendFactor, factor);
}

// destinationRGBBlendFactor
MT_INLINE MTBlendFactor mt_color_attachment_get_dst_rgb_blend(MTRenderPipelineColorAttachmentDescriptor desc) {
    return MT_MSG_SEND(MTBlendFactor, desc, MT_SEL("destinationRGBBlendFactor"));
}

MT_INLINE void mt_color_attachment_set_dst_rgb_blend(MTRenderPipelineColorAttachmentDescriptor desc, MTBlendFactor factor) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setDestinationRGBBlendFactor:"), MTBlendFactor, factor);
}

// rgbBlendOperation
MT_INLINE MTBlendOperation mt_color_attachment_get_rgb_blend_op(MTRenderPipelineColorAttachmentDescriptor desc) {
    return MT_MSG_SEND(MTBlendOperation, desc, MT_SEL("rgbBlendOperation"));
}

MT_INLINE void mt_color_attachment_set_rgb_blend_op(MTRenderPipelineColorAttachmentDescriptor desc, MTBlendOperation op) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setRgbBlendOperation:"), MTBlendOperation, op);
}

// sourceAlphaBlendFactor
MT_INLINE MTBlendFactor mt_color_attachment_get_src_alpha_blend(MTRenderPipelineColorAttachmentDescriptor desc) {
    return MT_MSG_SEND(MTBlendFactor, desc, MT_SEL("sourceAlphaBlendFactor"));
}

MT_INLINE void mt_color_attachment_set_src_alpha_blend(MTRenderPipelineColorAttachmentDescriptor desc, MTBlendFactor factor) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setSourceAlphaBlendFactor:"), MTBlendFactor, factor);
}

// destinationAlphaBlendFactor
MT_INLINE MTBlendFactor mt_color_attachment_get_dst_alpha_blend(MTRenderPipelineColorAttachmentDescriptor desc) {
    return MT_MSG_SEND(MTBlendFactor, desc, MT_SEL("destinationAlphaBlendFactor"));
}

MT_INLINE void mt_color_attachment_set_dst_alpha_blend(MTRenderPipelineColorAttachmentDescriptor desc, MTBlendFactor factor) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setDestinationAlphaBlendFactor:"), MTBlendFactor, factor);
}

// alphaBlendOperation
MT_INLINE MTBlendOperation mt_color_attachment_get_alpha_blend_op(MTRenderPipelineColorAttachmentDescriptor desc) {
    return MT_MSG_SEND(MTBlendOperation, desc, MT_SEL("alphaBlendOperation"));
}

MT_INLINE void mt_color_attachment_set_alpha_blend_op(MTRenderPipelineColorAttachmentDescriptor desc, MTBlendOperation op) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setAlphaBlendOperation:"), MTBlendOperation, op);
}

// writeMask
MT_INLINE MTColorWriteMask mt_color_attachment_get_write_mask(MTRenderPipelineColorAttachmentDescriptor desc) {
    return MT_MSG_SEND(MTColorWriteMask, desc, MT_SEL("writeMask"));
}

MT_INLINE void mt_color_attachment_set_write_mask(MTRenderPipelineColorAttachmentDescriptor desc, MTColorWriteMask mask) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setWriteMask:"), MTColorWriteMask, mask);
}

// ============================================================================
// Deprecated aliases for backwards compatibility
// ============================================================================
#define mt_renderPipeline_color_attachment_descriptor_new mt_color_attachment_create
#define mt_render_pipeline_color_attachment_descriptor_get_pixel_format mt_color_attachment_get_pixel_format
#define mt_render_pipeline_color_attachment_descriptor_set_pixel_format mt_color_attachment_set_pixel_format
#define mt_render_pipeline_color_attachment_descriptor_is_blending_enabled mt_color_attachment_is_blending_enabled
#define mt_render_pipeline_color_attachment_descriptor_set_blending_enabled mt_color_attachment_set_blending
#define mt_render_pipeline_color_attachment_descriptor_get_source_rgb_blend_factor mt_color_attachment_get_src_rgb_blend
#define mt_render_pipeline_color_attachment_descriptor_set_source_rgb_blend_factor mt_color_attachment_set_src_rgb_blend
#define mt_render_pipeline_color_attachment_descriptor_get_destination_rgb_blend_factor mt_color_attachment_get_dst_rgb_blend
#define mt_render_pipeline_color_attachment_descriptor_set_destination_rgb_blend_factor mt_color_attachment_set_dst_rgb_blend
#define mt_render_pipeline_color_attachment_descriptor_get_rgb_blend_operation mt_color_attachment_get_rgb_blend_op
#define mt_render_pipeline_color_attachment_descriptor_set_rgb_blend_operation mt_color_attachment_set_rgb_blend_op
#define mt_render_pipeline_color_attachment_descriptor_get_source_alpha_blend_factor mt_color_attachment_get_src_alpha_blend
#define mt_render_pipeline_color_attachment_descriptor_set_source_alpha_blend_factor mt_color_attachment_set_src_alpha_blend
#define mt_render_pipeline_color_attachment_descriptor_get_destination_alpha_blend_factor mt_color_attachment_get_dst_alpha_blend
#define mt_render_pipeline_color_attachment_descriptor_set_destination_alpha_blend_factor mt_color_attachment_set_dst_alpha_blend
#define mt_render_pipeline_color_attachment_descriptor_get_alpha_blend_operation mt_color_attachment_get_alpha_blend_op
#define mt_render_pipeline_color_attachment_descriptor_set_alpha_blend_operation mt_color_attachment_set_alpha_blend_op
#define mt_render_pipeline_color_attachment_descriptor_get_write_mask mt_color_attachment_get_write_mask
#define mt_render_pipeline_color_attachment_descriptor_set_write_mask mt_color_attachment_set_write_mask

/**
 * @brief Creates a new MTLRenderPipelineDescriptor class
 *
 * NOTE: Should be released using mtRelease();
 */
// 1. Create a new MTLRenderPipelineDescriptor instance
MT_INLINE MTRenderPipelineDescriptor mt_render_pipeline_descriptor_create(void) {
    return MT_ALLOC_INIT("MTLRenderPipelineDescriptor");
}

// 2. Get colorAttachments property
MT_INLINE MTRenderPipelineColorAttachmentDescriptorArray mt_render_pipeline_get_color_attachments(MTRenderPipelineDescriptor render_pipeline_desc) {
    return MT_MSG_SEND(void*, render_pipeline_desc, MT_SEL("colorAttachments"));
}

// 3. Get color attachment at a specific index using subscripting
MT_INLINE MTRenderPipelineColorAttachmentDescriptor mt_render_pipeline_get_color_attachment_at_index(MTRenderPipelineColorAttachmentDescriptorArray array, unsigned long color_attach_index) {
    return MT_MSG_SEND_1(void*, array, MT_SEL("objectAtIndexedSubscript:"), NSUInteger, color_attach_index);
}

MT_INLINE MTRenderPipelineColorAttachmentDescriptor
mt_render_pipeline_descriptor_get_color_attachment_at_index(MTRenderPipelineDescriptor render_pipeline_desc, unsigned long index) {
    id colorAttachmentsArray = MT_MSG_SEND(void*, render_pipeline_desc, MT_SEL("colorAttachments"));
    return MT_MSG_SEND_1(void*, colorAttachmentsArray, MT_SEL("objectAtIndexedSubscript:"), NSUInteger, index);
}

MT_INLINE void mt_render_pipeline_descriptor_set_label(MTRenderPipelineDescriptor desc, const char* label) {
    id str = mt_string_create(label);
    MT_MSG_SEND_1(void, desc, MT_SEL("setLabel:"), id, str);
    mt_string_release(str);
}

// -------------------
// Setters
// -------------------

MT_INLINE void mt_render_pipeline_descriptor_set_vertex_function(MTRenderPipelineDescriptor renderPipelineDesc, MTFunction vertFunction) {
    MT_MSG_SEND_1(void, renderPipelineDesc, MT_SEL("setVertexFunction:"), id, vertFunction);
}

MT_INLINE void mt_render_pipeline_descriptor_set_fragment_function(MTRenderPipelineDescriptor renderPipelineDesc, MTFunction fragFunction) {
    MT_MSG_SEND_1(void, renderPipelineDesc, MT_SEL("setFragmentFunction:"), id, fragFunction);
}

MT_INLINE void mt_render_pipeline_descriptor_set_vertex_descriptor(MTRenderPipelineDescriptor renderPipelineDesc, MTVertexDescriptor vertDesc) {
    MT_MSG_SEND_1(void, renderPipelineDesc, MT_SEL("setVertexDescriptor:"), id, vertDesc);
}

MT_INLINE void mt_render_pipeline_descriptor_set_raster_sample_count(MTRenderPipelineDescriptor renderPipelineDesc, uintptr_t count) {
    MT_MSG_SEND_1(void, renderPipelineDesc, MT_SEL("setRasterSampleCount:"), NSUInteger, count);
}

MT_INLINE void mt_render_pipeline_descriptor_set_depth_attachment_pixel_format(MTRenderPipelineDescriptor desc, MTPixelFormat format) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setDepthAttachmentPixelFormat:"), MTPixelFormat, format);
}

MT_INLINE void mt_render_pipeline_descriptor_set_stencil_attachment_pixel_format(MTRenderPipelineDescriptor desc, MTPixelFormat format) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setStencilAttachmentPixelFormat:"), MTPixelFormat, format);
}

MT_INLINE void mt_render_pipeline_descriptor_set_color_attachments_pixel_format(MTRenderPipelineDescriptor renderPipelineDesc, unsigned long color_attach_index, MTPixelFormat format) {
    id attachments = MT_MSG_SEND(void*, renderPipelineDesc, MT_SEL("colorAttachments"));
    id attachment = MT_MSG_SEND_1(void*, attachments, MT_SEL("objectAtIndexedSubscript:"), NSUInteger, color_attach_index);
    MT_MSG_SEND_1(void, attachment, MT_SEL("setPixelFormat:"), MTPixelFormat, format);
}

MT_INLINE void mt_render_pipeline_descriptor_reset(MTRenderPipelineDescriptor desc) {
    MT_MSG_SEND(void, desc, MT_SEL("reset"));
}

MT_INLINE MTShaderValidation mt_render_pipeline_descriptor_get_shader_validation(MTRenderPipelineDescriptor desc) {
    return MT_MSG_SEND(MTShaderValidation, desc, MT_SEL("shaderValidation"));
}

MT_INLINE void mt_render_pipeline_descriptor_set_shader_validation(MTRenderPipelineDescriptor desc, MTShaderValidation validation) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setShaderValidation:"), MTShaderValidation, validation);
}

// alphaToCoverageEnabled property
MT_INLINE BOOL mt_render_pipeline_descriptor_is_alpha_to_coverage_enabled(MTRenderPipelineDescriptor desc) {
    return MT_MSG_SEND(BOOL, desc, MT_SEL("isAlphaToCoverageEnabled"));
}

MT_INLINE void mt_render_pipeline_descriptor_set_alpha_to_coverage_enabled(MTRenderPipelineDescriptor desc, BOOL enabled) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setAlphaToCoverageEnabled:"), BOOL, enabled);
}

// alphaToOneEnabled property
MT_INLINE BOOL mt_render_pipeline_descriptor_is_alpha_to_one_enabled(MTRenderPipelineDescriptor desc) {
    return MT_MSG_SEND(BOOL, desc, MT_SEL("isAlphaToOneEnabled"));
}

MT_INLINE void mt_render_pipeline_descriptor_set_alpha_to_one_enabled(MTRenderPipelineDescriptor desc, BOOL enabled) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setAlphaToOneEnabled:"), BOOL, enabled);
}

// rasterizationEnabled property
MT_INLINE BOOL mt_render_pipeline_descriptor_is_rasterization_enabled(MTRenderPipelineDescriptor desc) {
    return MT_MSG_SEND(BOOL, desc, MT_SEL("isRasterizationEnabled"));
}

MT_INLINE void mt_render_pipeline_descriptor_set_rasterization_enabled(MTRenderPipelineDescriptor desc, BOOL enabled) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setRasterizationEnabled:"), BOOL, enabled);
}

// ============================================================================
// Shader reflection (macOS 26+)
//
// state.reflection is non-NULL only if the pipeline was built with reflection
// requested (classic: MTPipelineOptionBindingInfo; Metal 4:
// MT4ShaderReflectionBindingInfo on the pipeline options). Each per-stage
// getter returns an MTArray of MTBinding — enumerate with mt_array_get_count +
// mt_array_get_binding_at_index, then inspect via the accessors in MTArgument.h.
// ============================================================================

MT_INLINE MTRenderPipelineReflection mt_render_pipeline_state_get_reflection(MTRenderPipelineState pipeline) {
    return MT_MSG_SEND(void*, pipeline, MT_SEL("reflection"));
}

MT_INLINE MTArray mt_render_pipeline_reflection_get_vertex_bindings(MTRenderPipelineReflection reflection) {
    return MT_MSG_SEND(void*, reflection, MT_SEL("vertexBindings"));
}

MT_INLINE MTArray mt_render_pipeline_reflection_get_fragment_bindings(MTRenderPipelineReflection reflection) {
    return MT_MSG_SEND(void*, reflection, MT_SEL("fragmentBindings"));
}

MT_INLINE MTArray mt_render_pipeline_reflection_get_tile_bindings(MTRenderPipelineReflection reflection) {
    return MT_MSG_SEND(void*, reflection, MT_SEL("tileBindings"));
}

MT_INLINE MTArray mt_render_pipeline_reflection_get_object_bindings(MTRenderPipelineReflection reflection) {
    return MT_MSG_SEND(void*, reflection, MT_SEL("objectBindings"));
}

MT_INLINE MTArray mt_render_pipeline_reflection_get_mesh_bindings(MTRenderPipelineReflection reflection) {
    return MT_MSG_SEND(void*, reflection, MT_SEL("meshBindings"));
}
