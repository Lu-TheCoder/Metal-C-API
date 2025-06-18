//
//  MTVertexDescriptor.h
//  Metal C
//
//  Created by Lungile Maseko on 2024/06/02.
//

#pragma once

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
}MTVertexFormat;

typedef enum MTVertexStepFunction {
    MTVertexStepFunctionConstant = 0,
    MTVertexStepFunctionPerVertex = 1,
    MTVertexStepFunctionPerInstance = 2,
    MTVertexStepFunctionPerPatch = 3,
    MTVertexStepFunctionPerPatchControlPoint = 4,
}MTVertexStepFunction;

typedef void* MTVertexBufferLayoutDescriptor;
typedef void* MTVertexBufferLayoutDescriptorArray;
typedef void* MTVertexAttributeDescriptor;
typedef void* MTVertexAttributeDescriptorArray;
typedef void* MTVertexDescriptor;

MT_INLINE MTVertexAttributeDescriptorArray mt_vertexAttribute_new_descriptorArray(void) {
    Class cls = objc_getClass("MTLVertexAttributeDescriptorArray");

    SEL allocSel = sel_registerName("alloc");
    id allocated = ((id (*)(Class, SEL))objc_msgSend)(cls, allocSel);

    SEL initSel = sel_registerName("init");
    return ((id (*)(id, SEL))objc_msgSend)(allocated, initSel);
}

// MARK: -----------------  MTLVertexBufferLayoutDescriptorArray Functions --------------------------

MT_INLINE MTVertexBufferLayoutDescriptor mt_vertex_layout_array_get(MTVertexBufferLayoutDescriptorArray array, NSUInteger index) {
    SEL sel = sel_registerName("objectAtIndexedSubscript:");
    typedef MTVertexBufferLayoutDescriptor (*Func)(void*, SEL, NSUInteger);
    return ((Func)objc_msgSend)(array, sel, index);
}

MT_INLINE void mt_vertex_layout_array_set(MTVertexBufferLayoutDescriptorArray array, NSUInteger index, MTVertexBufferLayoutDescriptor desc) {
    SEL sel = sel_registerName("setObject:atIndexedSubscript:");
    typedef void (*Func)(void*, SEL, MTVertexBufferLayoutDescriptor, NSUInteger);
    ((Func)objc_msgSend)(array, sel, desc, index);
}

// MARK: -----------------  MTLVertexAttributeDescriptorArray Functions --------------------------

MT_INLINE MTVertexAttributeDescriptor mt_vertex_attr_array_get(MTVertexAttributeDescriptorArray array, NSUInteger index) {
    SEL sel = sel_registerName("objectAtIndexedSubscript:");
    typedef MTVertexAttributeDescriptor (*Func)(void*, SEL, NSUInteger);
    return ((Func)objc_msgSend)(array, sel, index);
}

MT_INLINE void mt_vertex_attr_array_set(MTVertexAttributeDescriptorArray array, NSUInteger index, MTVertexAttributeDescriptor desc) {
    SEL sel = sel_registerName("setObject:atIndexedSubscript:");
    typedef void (*Func)(void*, SEL, MTVertexAttributeDescriptor, NSUInteger);
    ((Func)objc_msgSend)(array, sel, desc, index);
}

// MARK: ----------------- MTLVertexDescriptor Functions --------------------------

MT_INLINE MTVertexDescriptor mt_vertex_descriptor_create(void) {
    Class cls = objc_getClass("MTLVertexDescriptor");
    SEL sel = sel_registerName("vertexDescriptor");
    typedef id (*Func)(Class, SEL);
    return ((Func)objc_msgSend)(cls, sel);
}

MT_INLINE MTVertexBufferLayoutDescriptorArray mt_vertex_descriptor_get_layouts(MTVertexDescriptor desc) {
    SEL sel = sel_registerName("layouts");
    typedef MTVertexBufferLayoutDescriptorArray (*Func)(void*, SEL);
    return ((Func)objc_msgSend)(desc, sel);
}

MT_INLINE void mt_vertex_descriptor_set_vertex_layout_stride(MTVertexDescriptor desc, NSUInteger index, NSUInteger stride) {
    SEL layoutSel = sel_registerName("layouts");
    id layoutArray = ((id (*)(id, SEL))objc_msgSend)(desc, layoutSel);

    SEL getLayout = sel_registerName("objectAtIndexedSubscript:");
    id layout = ((id (*)(id, SEL, NSUInteger))objc_msgSend)(layoutArray, getLayout, index);

    SEL setStride = sel_registerName("setStride:");
    ((void (*)(id, SEL, NSUInteger))objc_msgSend)(layout, setStride, stride);
}

MT_INLINE void mt_vertex_descriptor_set_vertex_layout_step_rate(MTVertexDescriptor desc, NSUInteger index, NSUInteger stepRate) {
    SEL layoutSel = sel_registerName("layouts");
    id layoutArray = ((id (*)(id, SEL))objc_msgSend)(desc, layoutSel);

    SEL getLayout = sel_registerName("objectAtIndexedSubscript:");
    id layout = ((id (*)(id, SEL, NSUInteger))objc_msgSend)(layoutArray, getLayout, index);

    SEL setStepRate = sel_registerName("setStepRate:");
    ((void (*)(id, SEL, NSUInteger))objc_msgSend)(layout, setStepRate, stepRate);
}

MT_INLINE void mt_vertex_descriptor_set_vertex_layout_step_function(MTVertexDescriptor desc, NSUInteger index, MTVertexStepFunction stepFunction) {
    SEL layoutSel = sel_registerName("layouts");
    id layoutArray = ((id (*)(id, SEL))objc_msgSend)(desc, layoutSel);

    SEL getLayout = sel_registerName("objectAtIndexedSubscript:");
    id layout = ((id (*)(id, SEL, NSUInteger))objc_msgSend)(layoutArray, getLayout, index);

    SEL setStepFunction = sel_registerName("setStepFunction:");
    ((void (*)(id, SEL, NSUInteger))objc_msgSend)(layout, setStepFunction, stepFunction);
}

MT_INLINE MTVertexAttributeDescriptorArray mt_vertex_descriptor_get_attributes(MTVertexDescriptor desc) {
    SEL sel = sel_registerName("attributes");
    typedef MTVertexAttributeDescriptorArray (*Func)(void*, SEL);
    return ((Func)objc_msgSend)(desc, sel);
}

MT_INLINE void mt_vertex_descriptor_set_vertex_attribute_format(MTVertexDescriptor desc, NSUInteger index, MTVertexFormat format) {
    SEL attrSel = sel_registerName("attributes");
    id attrArray = ((id (*)(id, SEL))objc_msgSend)(desc, attrSel);

    SEL getAttr = sel_registerName("objectAtIndexedSubscript:");
    id attr = ((id (*)(id, SEL, NSUInteger))objc_msgSend)(attrArray, getAttr, index);

    SEL setFormat = sel_registerName("setFormat:");
    ((void (*)(id, SEL, NSUInteger))objc_msgSend)(attr, setFormat, format);
}

MT_INLINE void mt_vertex_descriptor_set_vertex_attribute_offset(MTVertexDescriptor desc, NSUInteger index, NSUInteger offset) {
    SEL attrSel = sel_registerName("attributes");
    id attrArray = ((id (*)(id, SEL))objc_msgSend)(desc, attrSel);

    SEL getAttr = sel_registerName("objectAtIndexedSubscript:");
    id attr = ((id (*)(id, SEL, NSUInteger))objc_msgSend)(attrArray, getAttr, index);

    SEL setOffset = sel_registerName("setOffset:");
    ((void (*)(id, SEL, NSUInteger))objc_msgSend)(attr, setOffset, offset);
}

MT_INLINE void mt_vertex_descriptor_set_vertex_attribute_buffer_index(MTVertexDescriptor desc, NSUInteger index, NSUInteger bufferIndex) {
    SEL attrSel = sel_registerName("attributes");
    id attrArray = ((id (*)(id, SEL))objc_msgSend)(desc, attrSel);

    SEL getAttr = sel_registerName("objectAtIndexedSubscript:");
    id attr = ((id (*)(id, SEL, NSUInteger))objc_msgSend)(attrArray, getAttr, index);

    SEL setBufferIndex = sel_registerName("setBufferIndex:");
    ((void (*)(id, SEL, NSUInteger))objc_msgSend)(attr, setBufferIndex, bufferIndex);
}

MT_INLINE void mt_vertex_descriptor_reset(MTVertexDescriptor desc) {
    SEL sel = sel_registerName("reset");
    typedef void (*Func)(void*, SEL);
    ((Func)objc_msgSend)(desc, sel);
}

// MARK: ----------------- MTLVertexAttributeDescriptor property Functions --------------------------

MT_INLINE MTVertexAttributeDescriptor mt_vertex_descriptor_get_attribute(MTVertexDescriptor desc, NSUInteger index) {
    SEL sel = sel_registerName("attributes");
    id attributes = ((id (*)(id, SEL))objc_msgSend)(desc, sel);

    SEL getAttrSel = sel_registerName("objectAtIndexedSubscript:");
    return ((id (*)(id, SEL, NSUInteger))objc_msgSend)(attributes, getAttrSel, index);
}

MT_INLINE void mt_vertex_attribute_set_format(MTVertexAttributeDescriptor attr, MTVertexFormat format) {
    SEL sel = sel_registerName("setFormat:");
    typedef void (*Func)(void*, SEL, NSUInteger);
    ((Func)objc_msgSend)(attr, sel, format);
}


MT_INLINE void mt_vertex_attribute_set_offset(MTVertexAttributeDescriptor attr, NSUInteger offset) {
    SEL sel = sel_registerName("setOffset:");
    typedef void (*Func)(void*, SEL, NSUInteger);
    ((Func)objc_msgSend)(attr, sel, offset);
}

MT_INLINE void mt_vertex_attribute_set_buffer_index(MTVertexAttributeDescriptor attr, NSUInteger index) {
    SEL sel = sel_registerName("setBufferIndex:");
    typedef void (*Func)(void*, SEL, NSUInteger);
    ((Func)objc_msgSend)(attr, sel, index);
}

MT_INLINE void mt_vertex_attribute_array_set_format(MTVertexAttributeDescriptorArray arr, NSUInteger index, MTVertexFormat format) {
    SEL sel = sel_registerName("objectAtIndexedSubscript:");
    id attr = ((id (*)(id, SEL, NSUInteger))objc_msgSend)(arr, sel, index);

    SEL setFormat = sel_registerName("setFormat:");
    ((void (*)(id, SEL, NSUInteger))objc_msgSend)(attr, setFormat, format);
}

MT_INLINE void mt_vertex_attribute_array_set_offset(MTVertexAttributeDescriptorArray arr, NSUInteger index, NSUInteger offset) {
    SEL sel = sel_registerName("objectAtIndexedSubscript:");
    id attr = ((id (*)(id, SEL, NSUInteger))objc_msgSend)(arr, sel, index);

    SEL setOffset = sel_registerName("setOffset:");
    ((void (*)(id, SEL, NSUInteger))objc_msgSend)(attr, setOffset, offset);
}

MT_INLINE void mt_vertex_attribute_array_set_buffer_index(MTVertexAttributeDescriptorArray arr, NSUInteger index, NSUInteger bufferIndex) {
    SEL sel = sel_registerName("objectAtIndexedSubscript:");
    id attr = ((id (*)(id, SEL, NSUInteger))objc_msgSend)(arr, sel, index);

    SEL setBufferIndex = sel_registerName("setBufferIndex:");
    ((void (*)(id, SEL, NSUInteger))objc_msgSend)(attr, setBufferIndex, bufferIndex);
}


// MARK: ----------------- MTLVertexBufferLayoutDescriptor property Functions --------------------------

MT_INLINE MTVertexBufferLayoutDescriptor mt_vertex_descriptor_get_layout(MTVertexDescriptor desc, NSUInteger index) {
    SEL sel = sel_registerName("layouts");
    id layouts = ((id (*)(id, SEL))objc_msgSend)(desc, sel);

    SEL getLayoutSel = sel_registerName("objectAtIndexedSubscript:");
    return ((id (*)(id, SEL, NSUInteger))objc_msgSend)(layouts, getLayoutSel, index);
}

MT_INLINE void mt_vertex_layout_set_stride(MTVertexBufferLayoutDescriptor layout, NSUInteger stride) {
    SEL sel = sel_registerName("setStride:");
    typedef void (*Func)(void*, SEL, NSUInteger);
    ((Func)objc_msgSend)(layout, sel, stride);
}

MT_INLINE void mt_vertex_layout_set_step_function(MTVertexBufferLayoutDescriptor layout, MTVertexStepFunction stepFunction) {
    SEL sel = sel_registerName("setStepFunction:");
    typedef void (*Func)(void*, SEL, NSUInteger);
    ((Func)objc_msgSend)(layout, sel, stepFunction);
}

MT_INLINE void mt_vertex_layout_set_step_rate(MTVertexBufferLayoutDescriptor layout, NSUInteger stepRate) {
    SEL sel = sel_registerName("setStepRate:");
    typedef void (*Func)(void*, SEL, NSUInteger);
    ((Func)objc_msgSend)(layout, sel, stepRate);
}

MT_INLINE void mt_vertex_layout_array_set_stride(MTVertexBufferLayoutDescriptorArray arr, NSUInteger index, NSUInteger stride) {
    SEL sel = sel_registerName("objectAtIndexedSubscript:");
    id layout = ((id (*)(id, SEL, NSUInteger))objc_msgSend)(arr, sel, index);

    SEL setStride = sel_registerName("setStride:");
    ((void (*)(id, SEL, NSUInteger))objc_msgSend)(layout, setStride, stride);
}

MT_INLINE void mt_vertex_layout_array_set_step_rate(MTVertexBufferLayoutDescriptorArray arr, NSUInteger index, NSUInteger stepRate) {
    SEL sel = sel_registerName("objectAtIndexedSubscript:");
    id layout = ((id (*)(id, SEL, NSUInteger))objc_msgSend)(arr, sel, index);

    SEL setStepRate = sel_registerName("setStepRate:");
    ((void (*)(id, SEL, NSUInteger))objc_msgSend)(layout, setStepRate, stepRate);
}

MT_INLINE void mt_vertex_layout_array_set_step_function(MTVertexBufferLayoutDescriptorArray arr, NSUInteger index, MTVertexStepFunction stepFunction) {
    SEL sel = sel_registerName("objectAtIndexedSubscript:");
    id layout = ((id (*)(id, SEL, NSUInteger))objc_msgSend)(arr, sel, index);

    SEL setStepFunction = sel_registerName("setStepFunction:");
    ((void (*)(id, SEL, NSUInteger))objc_msgSend)(layout, setStepFunction, stepFunction);
}
