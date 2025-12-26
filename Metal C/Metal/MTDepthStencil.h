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
} MTCompareFunction;

typedef enum MTStencilOperation {
    MTStencilOperationKeep = 0,
    MTStencilOperationZero = 1,
    MTStencilOperationReplace = 2,
    MTStencilOperationIncrementClamp = 3,
    MTStencilOperationDecrementClamp = 4,
    MTStencilOperationInvert = 5,
    MTStencilOperationIncrementWrap = 6,
    MTStencilOperationDecrementWrap = 7,
} MTStencilOperation;

typedef void* MTDevice;
typedef void* MTStencilDescriptor;
typedef void* MTDepthStencilDescriptor;
typedef void* MTDepthStencilState;

// MARK: MTStencilDescriptor

MT_INLINE MTStencilDescriptor mt_stencil_descriptor_new(void) {
    return MT_ALLOC_INIT("MTLStencilDescriptor");
}

MT_INLINE void mt_stencil_descriptor_set_stencil_compare_function(MTStencilDescriptor desc, MTCompareFunction compare_func) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setStencilCompareFunction:"), NSUInteger, compare_func);
}

MT_INLINE MTCompareFunction mt_stencil_descriptor_get_stencil_compare_function(MTStencilDescriptor desc) {
    return MT_MSG_SEND(MTCompareFunction, desc, MT_SEL("stencilCompareFunction"));
}

MT_INLINE void mt_stencil_descriptor_set_stencil_failure_operation(MTStencilDescriptor desc, MTStencilOperation operation) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setStencilFailureOperation:"), NSUInteger, operation);
}

MT_INLINE MTStencilOperation mt_stencil_descriptor_get_stencil_failure_operation(MTStencilDescriptor desc) {
    return MT_MSG_SEND(MTStencilOperation, desc, MT_SEL("stencilFailureOperation"));
}

MT_INLINE void mt_stencil_descriptor_set_depth_failure_operation(MTStencilDescriptor desc, MTStencilOperation operation) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setDepthFailureOperation:"), NSUInteger, operation);
}

MT_INLINE MTStencilOperation mt_stencil_descriptor_get_depth_failure_operation(MTStencilDescriptor desc) {
    return MT_MSG_SEND(MTStencilOperation, desc, MT_SEL("depthFailureOperation"));
}

MT_INLINE void mt_stencil_descriptor_set_depth_stencil_pass_operation(MTStencilDescriptor desc, MTStencilOperation operation) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setDepthStencilPassOperation:"), NSUInteger, operation);
}

MT_INLINE MTStencilOperation mt_stencil_descriptor_get_depth_stencil_pass_operation(MTStencilDescriptor desc) {
    return MT_MSG_SEND(MTStencilOperation, desc, MT_SEL("depthStencilPassOperation"));
}

MT_INLINE void mt_stencil_descriptor_set_read_mask(MTStencilDescriptor desc, uint32_t value) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setReadMask:"), uint32_t, value);
}

MT_INLINE uint32_t mt_stencil_descriptor_get_read_mask(MTStencilDescriptor desc) {
    return MT_MSG_SEND(uint32_t, desc, MT_SEL("readMask"));
}

MT_INLINE void mt_stencil_descriptor_set_write_mask(MTStencilDescriptor desc, uint32_t value) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setWriteMask:"), uint32_t, value);
}

MT_INLINE uint32_t mt_stencil_descriptor_get_write_mask(MTStencilDescriptor desc) {
    return MT_MSG_SEND(uint32_t, desc, MT_SEL("writeMask"));
}

// MARK: MTDepthStencilDescriptor

MT_INLINE MTDepthStencilDescriptor mt_depth_stencil_descriptor_new(void) {
    return MT_ALLOC_INIT("MTLDepthStencilDescriptor");
}

MT_INLINE void mt_depth_stencil_descriptor_set_depth_compare_function(MTDepthStencilDescriptor desc, MTCompareFunction compare_func) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setDepthCompareFunction:"), NSUInteger, compare_func);
}

MT_INLINE MTCompareFunction mt_depth_stencil_descriptor_get_depth_compare_function(MTDepthStencilDescriptor desc) {
    return MT_MSG_SEND(MTCompareFunction, desc, MT_SEL("depthCompareFunction"));
}

MT_INLINE void mt_depth_stencil_descriptor_set_is_depth_write_enabled(MTDepthStencilDescriptor desc, bool is_write_enabled) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setDepthWriteEnabled:"), BOOL, is_write_enabled);
}

MT_INLINE bool mt_depth_stencil_descriptor_get_is_depth_write_enabled(MTDepthStencilDescriptor desc) {
    return MT_MSG_SEND(BOOL, desc, MT_SEL("isDepthWriteEnabled"));
}

MT_INLINE void mt_depth_stencil_descriptor_set_front_face_stencil(MTDepthStencilDescriptor desc, MTStencilDescriptor front_face_stencil) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setFrontFaceStencil:"), id, front_face_stencil);
}

MT_INLINE MTStencilDescriptor mt_depth_stencil_descriptor_get_front_face_stencil(MTDepthStencilDescriptor desc) {
    return MT_MSG_SEND(id, desc, MT_SEL("frontFaceStencil"));
}

MT_INLINE void mt_depth_stencil_descriptor_set_back_face_stencil(MTDepthStencilDescriptor desc, MTStencilDescriptor back_face_stencil) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setBackFaceStencil:"), id, back_face_stencil);
}

MT_INLINE MTStencilDescriptor mt_depth_stencil_descriptor_get_back_face_stencil(MTDepthStencilDescriptor desc) {
    return MT_MSG_SEND(id, desc, MT_SEL("backFaceStencil"));
}

// MARK: MTDepthStencilState

MT_INLINE const char* mt_depth_stencil_state_get_label(MTDepthStencilState state) {
    id nsLabel = MT_MSG_SEND(id, state, MT_SEL("label"));
    if (!nsLabel) return NULL;
    return MT_MSG_SEND(const char*, nsLabel, MT_SEL("UTF8String"));
}

MT_INLINE MTDevice mt_depth_stencil_state_get_device(MTDepthStencilState state) {
    return MT_MSG_SEND(id, state, MT_SEL("device"));
}
