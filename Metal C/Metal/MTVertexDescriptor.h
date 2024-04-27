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

typedef void MTVertexBufferLayoutDescriptor;
typedef void MTVertexBufferLayoutDescriptorArray;
typedef void MTVertexAttributeDescriptor;
typedef void MTVertexAttributeDescriptorArray;
typedef void MTVertexDescriptor;

MT_INLINE MTVertexAttributeDescriptorArray* mt_vertexAttribute_new_descriptorArray(void) {
    Class vertDesc = objc_getClass("MTLVertexAttributeDescriptorArray");
    SEL allocSel = sel_registerName("alloc");
    
    void* desc = ms_send(vertDesc, allocSel);
    SEL initSel = sel_registerName("init");
    return ms_send(desc, initSel);
}

MT_INLINE MTVertexAttributeDescriptor* mt_vertexAttribute_at_index(MTVertexAttributeDescriptorArray* vaa, unsigned long attrib_index) {
    SEL selIndex = sel_registerName("objectAtIndexedSubscript:");
    return  ms_send_uint(vaa, selIndex, attrib_index);
}

MT_INLINE void mt_vertexAttribute_set_format(MTVertexAttributeDescriptorArray** attributes_array, unsigned long index, MTVertexFormat format) {
    SEL sel = sel_registerName("setFormat:");
    ms_send_uint(mt_vertexAttribute_at_index(attributes_array, index), sel, format);
}

MT_INLINE void mt_vertexAttribute_set_offset(MTVertexAttributeDescriptorArray** attributes_array, unsigned long index, unsigned long offset) {
    SEL sel = sel_registerName("setOffset:");
    ms_send_uint(mt_vertexAttribute_at_index(attributes_array, index), sel, offset);
}

MT_INLINE void mt_vertexAttribute_set_buffer_index(MTVertexAttributeDescriptorArray** attributes_array, unsigned long index, unsigned long buffer_index) {
    SEL sel = sel_registerName("setBufferIndex:");
    ms_send_uint(mt_vertexAttribute_at_index(attributes_array, index), sel, buffer_index);
}

MT_INLINE MTVertexDescriptor* mt_vertexDescriptor_new(void){
    Class vertDesc = objc_getClass("MTLVertexDescriptor");
    SEL allocSel = sel_registerName("alloc");
    
    void* desc = ms_send(vertDesc, allocSel);
    SEL initSel = sel_registerName("init");
    return ms_send(desc, initSel);
}

MT_INLINE MTVertexBufferLayoutDescriptorArray* mt_vertexDescriptor_get_layouts(MTVertexDescriptor* vertex_desc){
    SEL sel = sel_registerName("layouts");
    return ms_send(vertex_desc, sel);
}

MT_INLINE MTVertexBufferLayoutDescriptor* mt_vertexBufferLayout_at_index(MTVertexBufferLayoutDescriptorArray* vbla, unsigned long attrib_index) {
    SEL selIndex = sel_registerName("objectAtIndexedSubscript:");
    return  ms_send_uint(vbla, selIndex, attrib_index);
}

MT_INLINE void mt_vertexBufferLayout_set_stride(MTVertexAttributeDescriptorArray** attributes_array, unsigned long index, unsigned long stride) {
    SEL sel = sel_registerName("setStride:");
    ms_send_uint(mt_vertexAttribute_at_index(attributes_array, index), sel, stride);
}

MT_INLINE void mt_vertexBufferLayout_set_stepFunction(MTVertexAttributeDescriptorArray** attributes_array, unsigned long index, MTVertexStepFunction step_func) {
    SEL sel = sel_registerName("setStepFunction:");
    ms_send_uint(mt_vertexAttribute_at_index(attributes_array, index), sel, step_func);
}

MT_INLINE void mt_vertexBufferLayout_set_stepRate(MTVertexAttributeDescriptorArray** attributes_array, unsigned long index, unsigned long step_rate) {
    SEL sel = sel_registerName("setStepRate:");
    ms_send_uint(mt_vertexAttribute_at_index(attributes_array, index), sel, step_rate);
}


MT_INLINE MTVertexAttributeDescriptorArray* mt_vertexDescriptor_get_attributes(MTVertexDescriptor* vertex_desc){
    SEL sel = sel_registerName("attributes");
    return ms_send(vertex_desc, sel);
}

MT_INLINE void mt_vertexDescriptor_reset(MTVertexDescriptor* vertex_desc) {
    SEL sel = sel_registerName("reset");
    ms_send(vertex_desc, sel);
}
