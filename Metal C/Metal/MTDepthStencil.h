//
//  MTDepthStencil.h
//  Metal C
//
//  Created by Lungile Maseko on 2024/06/05.
//

#pragma once
#include "MTUtils.h"

typedef enum MTCompareFunction {
    MTCompareFunctionNever = 0,
    MTCompareFunctionLess = 1,
    MTCompareFunctionEqual = 2,
    MTCompareFunctionLessEqual = 3,
    MTCompareFunctionGreater = 4,
    MTCompareFunctionNotEqual = 5,
    MTCompareFunctionGreaterEqual = 6,
    MTCompareFunctionAlways = 7,
}MTCompareFunction;

typedef enum MTStencilOperation {
    MTStencilOperationKeep = 0,
    MTStencilOperationZero = 1,
    MTStencilOperationReplace = 2,
    MTStencilOperationIncrementClamp = 3,
    MTStencilOperationDecrementClamp = 4,
    MTStencilOperationInvert = 5,
    MTStencilOperationIncrementWrap = 6,
    MTStencilOperationDecrementWrap = 7,
}MTStencilOperation;

typedef void* MTDevice;
typedef void* MTStencilDescriptor;
typedef void* MTDepthStencilDescriptor;
typedef void* MTDepthStencilState;

// MARK: MTStencilDescriptor

MT_INLINE MTStencilDescriptor mt_stencil_descriptor_new(void) {
    Class cls = objc_getClass("MTLStencilDescriptor");
    id obj = ((id (*)(Class, SEL))objc_msgSend)(cls, sel_getUid("alloc"));
    return ((id (*)(id, SEL))objc_msgSend)(obj, sel_getUid("init"));
}

MT_INLINE void mt_stencil_descriptor_set_stencil_compare_function(MTStencilDescriptor desc, MTCompareFunction compare_func) {
    ((void (*)(id, SEL, NSUInteger))objc_msgSend)(desc, sel_getUid("setStencilCompareFunction:"), compare_func);
}

MT_INLINE MTCompareFunction mt_stencil_descriptor_get_stencil_compare_function(MTStencilDescriptor desc) {
    return ((MTCompareFunction (*)(id, SEL))objc_msgSend)(desc, sel_getUid("stencilCompareFunction"));
}

MT_INLINE void mt_stencil_descriptor_set_stencil_failure_operation(MTStencilDescriptor desc, MTStencilOperation operation) {
    ((void (*)(id, SEL, NSUInteger))objc_msgSend)(desc, sel_getUid("setStencilFailureOperation:"), operation);
}

MT_INLINE MTStencilOperation mt_stencil_descriptor_get_stencil_failure_operation(MTStencilDescriptor desc) {
    return ((MTStencilOperation (*)(id, SEL))objc_msgSend)(desc, sel_getUid("stencilFailureOperation"));
}

MT_INLINE void mt_stencil_descriptor_set_depth_failure_operation(MTStencilDescriptor desc, MTStencilOperation operation) {
    ((void (*)(id, SEL, NSUInteger))objc_msgSend)(desc, sel_getUid("setDepthFailureOperation:"), operation);
}

MT_INLINE MTStencilOperation mt_stencil_descriptor_get_depth_failure_operation(MTStencilDescriptor desc) {
    return ((MTStencilOperation (*)(id, SEL))objc_msgSend)(desc, sel_getUid("depthFailureOperation"));
}

MT_INLINE void mt_stencil_descriptor_set_depth_stencil_pass_operation(MTStencilDescriptor desc, MTStencilOperation operation) {
    ((void (*)(id, SEL, NSUInteger))objc_msgSend)(desc, sel_getUid("setDepthStencilPassOperation:"), operation);
}

MT_INLINE MTStencilOperation mt_stencil_descriptor_get_depth_stencil_pass_operation(MTStencilDescriptor desc) {
    return ((MTStencilOperation (*)(id, SEL))objc_msgSend)(desc, sel_getUid("depthStencilPassOperation"));
}

MT_INLINE void mt_stencil_descriptor_set_read_mask(MTStencilDescriptor desc, uint32_t value) {
    ((void (*)(id, SEL, uint32_t))objc_msgSend)(desc, sel_getUid("setReadMask:"), value);
}

MT_INLINE uint32_t mt_stencil_descriptor_get_read_mask(MTStencilDescriptor desc) {
    return ((uint32_t (*)(id, SEL))objc_msgSend)(desc, sel_getUid("readMask"));
}

MT_INLINE void mt_stencil_descriptor_set_write_mask(MTStencilDescriptor desc, uint32_t value) {
    ((void (*)(id, SEL, uint32_t))objc_msgSend)(desc, sel_getUid("setWriteMask:"), value);
}

MT_INLINE uint32_t mt_stencil_descriptor_get_write_mask(MTStencilDescriptor desc) {
    return ((uint32_t (*)(id, SEL))objc_msgSend)(desc, sel_getUid("writeMask"));
}

MT_INLINE MTDepthStencilDescriptor mt_depth_stencil_descriptor_new(void) {
    Class cls = objc_getClass("MTLDepthStencilDescriptor");
    id obj = ((id (*)(Class, SEL))objc_msgSend)(cls, sel_getUid("alloc"));
    return ((id (*)(id, SEL))objc_msgSend)(obj, sel_getUid("init"));
}

MT_INLINE void mt_depth_stencil_descriptor_set_depth_compare_function(MTDepthStencilDescriptor desc, MTCompareFunction compare_func) {
    ((void (*)(id, SEL, NSUInteger))objc_msgSend)(desc, sel_getUid("setDepthCompareFunction:"), compare_func);
}

MT_INLINE MTCompareFunction mt_depth_stencil_descriptor_get_depth_compare_function(MTDepthStencilDescriptor desc) {
    return ((MTCompareFunction (*)(id, SEL))objc_msgSend)(desc, sel_getUid("depthCompareFunction"));
}

MT_INLINE void mt_depth_stencil_descriptor_set_is_depth_write_enabled(MTDepthStencilDescriptor desc, bool is_write_enabled) {
    ((void (*)(id, SEL, BOOL))objc_msgSend)(desc, sel_getUid("setDepthWriteEnabled:"), is_write_enabled);
}

MT_INLINE bool mt_depth_stencil_descriptor_get_is_depth_write_enabled(MTDepthStencilDescriptor desc) {
    return ((BOOL (*)(id, SEL))objc_msgSend)(desc, sel_getUid("isDepthWriteEnabled"));
}

MT_INLINE void mt_depth_stencil_descriptor_set_front_face_stencil(MTDepthStencilDescriptor desc, MTStencilDescriptor front_face_stencil) {
    ((void (*)(id, SEL, id))objc_msgSend)(desc, sel_getUid("setFrontFaceStencil:"), front_face_stencil);
}

MT_INLINE MTStencilDescriptor mt_depth_stencil_descriptor_get_front_face_stencil(MTDepthStencilDescriptor desc) {
    return ((id (*)(id, SEL))objc_msgSend)(desc, sel_getUid("frontFaceStencil"));
}

MT_INLINE void mt_depth_stencil_descriptor_set_back_face_stencil(MTDepthStencilDescriptor desc, MTStencilDescriptor back_face_stencil) {
    ((void (*)(id, SEL, id))objc_msgSend)(desc, sel_getUid("setBackFaceStencil:"), back_face_stencil);
}

MT_INLINE MTStencilDescriptor mt_depth_stencil_descriptor_get_back_face_stencil(MTDepthStencilDescriptor desc) {
    return ((id (*)(id, SEL))objc_msgSend)(desc, sel_getUid("backFaceStencil"));
}

// MARK: MTDepthStencilState

MT_INLINE const char* mt_depth_stencil_state_get_label(MTDepthStencilState state) {
    SEL sel_label = sel_getUid("label");
    id nsLabel = ((id (*)(id, SEL))objc_msgSend)(state, sel_label);
    if (!nsLabel) return NULL;

    SEL sel_utf8 = sel_getUid("UTF8String");
    return ((const char* (*)(id, SEL))objc_msgSend)(nsLabel, sel_utf8);
}

MT_INLINE MTDevice mt_depth_stencil_state_get_device(MTDepthStencilState state) {
    SEL sel = sel_getUid("device");
    return ((MTDevice (*)(id, SEL))objc_msgSend)(state, sel);
}
