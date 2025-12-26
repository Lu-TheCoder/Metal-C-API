//
//  MTVertexDescriptor.h
//  Metal C
//
//  Created by Lungile Maseko on 2024/06/02.
//

#pragma once
#include "MTUtils.h"

typedef enum MTVertexFormat {
    MTVertexFormatInvalid = 0,
    MTVertexFormatUChar2 = 1,
    MTVertexFormatUChar3 = 2,
    MTVertexFormatUChar4 = 3,
    MTVertexFormatChar2 = 4,
    MTVertexFormatChar3 = 5,
    MTVertexFormatChar4 = 6,
    MTVertexFormatUChar2Normalized = 7,
    MTVertexFormatUChar3Normalized = 8,
    MTVertexFormatUChar4Normalized = 9,
    MTVertexFormatChar2Normalized = 10,
    MTVertexFormatChar3Normalized = 11,
    MTVertexFormatChar4Normalized = 12,
    MTVertexFormatUShort2 = 13,
    MTVertexFormatUShort3 = 14,
    MTVertexFormatUShort4 = 15,
    MTVertexFormatShort2 = 16,
    MTVertexFormatShort3 = 17,
    MTVertexFormatShort4 = 18,
    MTVertexFormatUShort2Normalized = 19,
    MTVertexFormatUShort3Normalized = 20,
    MTVertexFormatUShort4Normalized = 21,
    MTVertexFormatShort2Normalized = 22,
    MTVertexFormatShort3Normalized = 23,
    MTVertexFormatShort4Normalized = 24,
    MTVertexFormatHalf2 = 25,
    MTVertexFormatHalf3 = 26,
    MTVertexFormatHalf4 = 27,
    MTVertexFormatFloat = 28,
    MTVertexFormatFloat2 = 29,
    MTVertexFormatFloat3 = 30,
    MTVertexFormatFloat4 = 31,
    MTVertexFormatInt = 32,
    MTVertexFormatInt2 = 33,
    MTVertexFormatInt3 = 34,
    MTVertexFormatInt4 = 35,
    MTVertexFormatUInt = 36,
    MTVertexFormatUInt2 = 37,
    MTVertexFormatUInt3 = 38,
    MTVertexFormatUInt4 = 39,
    MTVertexFormatInt1010102Normalized = 40,
    MTVertexFormatUInt1010102Normalized = 41,
    MTVertexFormatUChar4Normalized_BGRA = 42,
    MTVertexFormatUChar = 45,
    MTVertexFormatChar = 46,
    MTVertexFormatUCharNormalized = 47,
    MTVertexFormatCharNormalized = 48,
    MTVertexFormatUShort = 49,
    MTVertexFormatShort = 50,
    MTVertexFormatUShortNormalized = 51,
    MTVertexFormatShortNormalized = 52,
    MTVertexFormatHalf = 53,
    MTVertexFormatFloatRG11B10 = 54,
    MTVertexFormatFloatRGB9E5 = 55,
} MTVertexFormat;

typedef enum MTVertexStepFunction {
    MTVertexStepFunctionConstant = 0,
    MTVertexStepFunctionPerVertex = 1,
    MTVertexStepFunctionPerInstance = 2,
    MTVertexStepFunctionPerPatch = 3,
    MTVertexStepFunctionPerPatchControlPoint = 4,
} MTVertexStepFunction;

typedef void* MTVertexBufferLayoutDescriptor;
typedef void* MTVertexBufferLayoutDescriptorArray;
typedef void* MTVertexAttributeDescriptor;
typedef void* MTVertexAttributeDescriptorArray;
typedef void* MTVertexDescriptor;

MT_INLINE MTVertexAttributeDescriptorArray mt_vertexAttribute_new_descriptorArray(void) {
    return MT_ALLOC_INIT("MTLVertexAttributeDescriptorArray");
}

// MARK: MTLVertexBufferLayoutDescriptorArray Functions

MT_INLINE MTVertexBufferLayoutDescriptor mt_vertex_layout_array_get(MTVertexBufferLayoutDescriptorArray array, NSUInteger index) {
    return MT_MSG_SEND_1(id, array, MT_SEL("objectAtIndexedSubscript:"), NSUInteger, index);
}

MT_INLINE void mt_vertex_layout_array_set(MTVertexBufferLayoutDescriptorArray array, NSUInteger index, MTVertexBufferLayoutDescriptor desc) {
    MT_MSG_SEND_2(void, array, MT_SEL("setObject:atIndexedSubscript:"), id, desc, NSUInteger, index);
}

// MARK: MTLVertexAttributeDescriptorArray Functions

MT_INLINE MTVertexAttributeDescriptor mt_vertex_attr_array_get(MTVertexAttributeDescriptorArray array, NSUInteger index) {
    return MT_MSG_SEND_1(id, array, MT_SEL("objectAtIndexedSubscript:"), NSUInteger, index);
}

MT_INLINE void mt_vertex_attr_array_set(MTVertexAttributeDescriptorArray array, NSUInteger index, MTVertexAttributeDescriptor desc) {
    MT_MSG_SEND_2(void, array, MT_SEL("setObject:atIndexedSubscript:"), id, desc, NSUInteger, index);
}

// MARK: MTLVertexDescriptor Functions

MT_INLINE MTVertexDescriptor mt_vertex_descriptor_create(void) {
    return MT_MSG_SEND_CLASS(id, MT_CLASS("MTLVertexDescriptor"), MT_SEL("vertexDescriptor"));
}

MT_INLINE MTVertexBufferLayoutDescriptorArray mt_vertex_descriptor_get_layouts(MTVertexDescriptor desc) {
    return MT_MSG_SEND(id, desc, MT_SEL("layouts"));
}

MT_INLINE void mt_vertex_descriptor_set_vertex_layout_stride(MTVertexDescriptor desc, NSUInteger index, NSUInteger stride) {
    id layoutArray = MT_MSG_SEND(id, desc, MT_SEL("layouts"));
    id layout = MT_MSG_SEND_1(id, layoutArray, MT_SEL("objectAtIndexedSubscript:"), NSUInteger, index);
    MT_MSG_SEND_1(void, layout, MT_SEL("setStride:"), NSUInteger, stride);
}

MT_INLINE void mt_vertex_descriptor_set_vertex_layout_step_rate(MTVertexDescriptor desc, NSUInteger index, NSUInteger stepRate) {
    id layoutArray = MT_MSG_SEND(id, desc, MT_SEL("layouts"));
    id layout = MT_MSG_SEND_1(id, layoutArray, MT_SEL("objectAtIndexedSubscript:"), NSUInteger, index);
    MT_MSG_SEND_1(void, layout, MT_SEL("setStepRate:"), NSUInteger, stepRate);
}

MT_INLINE void mt_vertex_descriptor_set_vertex_layout_step_function(MTVertexDescriptor desc, NSUInteger index, MTVertexStepFunction stepFunction) {
    id layoutArray = MT_MSG_SEND(id, desc, MT_SEL("layouts"));
    id layout = MT_MSG_SEND_1(id, layoutArray, MT_SEL("objectAtIndexedSubscript:"), NSUInteger, index);
    MT_MSG_SEND_1(void, layout, MT_SEL("setStepFunction:"), NSUInteger, stepFunction);
}

MT_INLINE MTVertexAttributeDescriptorArray mt_vertex_descriptor_get_attributes(MTVertexDescriptor desc) {
    return MT_MSG_SEND(id, desc, MT_SEL("attributes"));
}

MT_INLINE void mt_vertex_descriptor_set_vertex_attribute_format(MTVertexDescriptor desc, NSUInteger index, MTVertexFormat format) {
    id attrArray = MT_MSG_SEND(id, desc, MT_SEL("attributes"));
    id attr = MT_MSG_SEND_1(id, attrArray, MT_SEL("objectAtIndexedSubscript:"), NSUInteger, index);
    MT_MSG_SEND_1(void, attr, MT_SEL("setFormat:"), NSUInteger, format);
}

MT_INLINE void mt_vertex_descriptor_set_vertex_attribute_offset(MTVertexDescriptor desc, NSUInteger index, NSUInteger offset) {
    id attrArray = MT_MSG_SEND(id, desc, MT_SEL("attributes"));
    id attr = MT_MSG_SEND_1(id, attrArray, MT_SEL("objectAtIndexedSubscript:"), NSUInteger, index);
    MT_MSG_SEND_1(void, attr, MT_SEL("setOffset:"), NSUInteger, offset);
}

MT_INLINE void mt_vertex_descriptor_set_vertex_attribute_buffer_index(MTVertexDescriptor desc, NSUInteger index, NSUInteger bufferIndex) {
    id attrArray = MT_MSG_SEND(id, desc, MT_SEL("attributes"));
    id attr = MT_MSG_SEND_1(id, attrArray, MT_SEL("objectAtIndexedSubscript:"), NSUInteger, index);
    MT_MSG_SEND_1(void, attr, MT_SEL("setBufferIndex:"), NSUInteger, bufferIndex);
}

MT_INLINE void mt_vertex_descriptor_reset(MTVertexDescriptor desc) {
    MT_MSG_SEND(void, desc, MT_SEL("reset"));
}

// MARK: MTLVertexAttributeDescriptor property Functions

MT_INLINE MTVertexAttributeDescriptor mt_vertex_descriptor_get_attribute(MTVertexDescriptor desc, NSUInteger index) {
    id attributes = MT_MSG_SEND(id, desc, MT_SEL("attributes"));
    return MT_MSG_SEND_1(id, attributes, MT_SEL("objectAtIndexedSubscript:"), NSUInteger, index);
}

MT_INLINE void mt_vertex_attribute_set_format(MTVertexAttributeDescriptor attr, MTVertexFormat format) {
    MT_MSG_SEND_1(void, attr, MT_SEL("setFormat:"), NSUInteger, format);
}

MT_INLINE void mt_vertex_attribute_set_offset(MTVertexAttributeDescriptor attr, NSUInteger offset) {
    MT_MSG_SEND_1(void, attr, MT_SEL("setOffset:"), NSUInteger, offset);
}

MT_INLINE void mt_vertex_attribute_set_buffer_index(MTVertexAttributeDescriptor attr, NSUInteger index) {
    MT_MSG_SEND_1(void, attr, MT_SEL("setBufferIndex:"), NSUInteger, index);
}

MT_INLINE void mt_vertex_attribute_array_set_format(MTVertexAttributeDescriptorArray arr, NSUInteger index, MTVertexFormat format) {
    id attr = MT_MSG_SEND_1(id, arr, MT_SEL("objectAtIndexedSubscript:"), NSUInteger, index);
    MT_MSG_SEND_1(void, attr, MT_SEL("setFormat:"), NSUInteger, format);
}

MT_INLINE void mt_vertex_attribute_array_set_offset(MTVertexAttributeDescriptorArray arr, NSUInteger index, NSUInteger offset) {
    id attr = MT_MSG_SEND_1(id, arr, MT_SEL("objectAtIndexedSubscript:"), NSUInteger, index);
    MT_MSG_SEND_1(void, attr, MT_SEL("setOffset:"), NSUInteger, offset);
}

MT_INLINE void mt_vertex_attribute_array_set_buffer_index(MTVertexAttributeDescriptorArray arr, NSUInteger index, NSUInteger bufferIndex) {
    id attr = MT_MSG_SEND_1(id, arr, MT_SEL("objectAtIndexedSubscript:"), NSUInteger, index);
    MT_MSG_SEND_1(void, attr, MT_SEL("setBufferIndex:"), NSUInteger, bufferIndex);
}

// MARK: MTLVertexBufferLayoutDescriptor property Functions

MT_INLINE MTVertexBufferLayoutDescriptor mt_vertex_descriptor_get_layout(MTVertexDescriptor desc, NSUInteger index) {
    id layouts = MT_MSG_SEND(id, desc, MT_SEL("layouts"));
    return MT_MSG_SEND_1(id, layouts, MT_SEL("objectAtIndexedSubscript:"), NSUInteger, index);
}

MT_INLINE void mt_vertex_layout_set_stride(MTVertexBufferLayoutDescriptor layout, NSUInteger stride) {
    MT_MSG_SEND_1(void, layout, MT_SEL("setStride:"), NSUInteger, stride);
}

MT_INLINE void mt_vertex_layout_set_step_function(MTVertexBufferLayoutDescriptor layout, MTVertexStepFunction stepFunction) {
    MT_MSG_SEND_1(void, layout, MT_SEL("setStepFunction:"), NSUInteger, stepFunction);
}

MT_INLINE void mt_vertex_layout_set_step_rate(MTVertexBufferLayoutDescriptor layout, NSUInteger stepRate) {
    MT_MSG_SEND_1(void, layout, MT_SEL("setStepRate:"), NSUInteger, stepRate);
}

MT_INLINE void mt_vertex_layout_array_set_stride(MTVertexBufferLayoutDescriptorArray arr, NSUInteger index, NSUInteger stride) {
    id layout = MT_MSG_SEND_1(id, arr, MT_SEL("objectAtIndexedSubscript:"), NSUInteger, index);
    MT_MSG_SEND_1(void, layout, MT_SEL("setStride:"), NSUInteger, stride);
}

MT_INLINE void mt_vertex_layout_array_set_step_rate(MTVertexBufferLayoutDescriptorArray arr, NSUInteger index, NSUInteger stepRate) {
    id layout = MT_MSG_SEND_1(id, arr, MT_SEL("objectAtIndexedSubscript:"), NSUInteger, index);
    MT_MSG_SEND_1(void, layout, MT_SEL("setStepRate:"), NSUInteger, stepRate);
}

MT_INLINE void mt_vertex_layout_array_set_step_function(MTVertexBufferLayoutDescriptorArray arr, NSUInteger index, MTVertexStepFunction stepFunction) {
    id layout = MT_MSG_SEND_1(id, arr, MT_SEL("objectAtIndexedSubscript:"), NSUInteger, index);
    MT_MSG_SEND_1(void, layout, MT_SEL("setStepFunction:"), NSUInteger, stepFunction);
}
