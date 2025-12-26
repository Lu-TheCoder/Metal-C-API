//
//  MTArgument.h
//  Metal C
//
//  Created by Lungile Maseko on 2025/06/06.
//
#pragma once
#include "MTUtils.h"
#include "MTTexture.h"

typedef enum MTDataType {
    MTDataTypeNone = 0,
    MTDataTypeStruct = 1,
    MTDataTypeArray  = 2,
    MTDataTypeFloat  = 3,
    MTDataTypeFloat2 = 4,
    MTDataTypeFloat3 = 5,
    MTDataTypeFloat4 = 6,
    MTDataTypeFloat2x2 = 7,
    MTDataTypeFloat2x3 = 8,
    MTDataTypeFloat2x4 = 9,
    MTDataTypeFloat3x2 = 10,
    MTDataTypeFloat3x3 = 11,
    MTDataTypeFloat3x4 = 12,
    MTDataTypeFloat4x2 = 13,
    MTDataTypeFloat4x3 = 14,
    MTDataTypeFloat4x4 = 15,
    MTDataTypeHalf  = 16,
    MTDataTypeHalf2 = 17,
    MTDataTypeHalf3 = 18,
    MTDataTypeHalf4 = 19,
    MTDataTypeHalf2x2 = 20,
    MTDataTypeHalf2x3 = 21,
    MTDataTypeHalf2x4 = 22,
    MTDataTypeHalf3x2 = 23,
    MTDataTypeHalf3x3 = 24,
    MTDataTypeHalf3x4 = 25,
    MTDataTypeHalf4x2 = 26,
    MTDataTypeHalf4x3 = 27,
    MTDataTypeHalf4x4 = 28,
    MTDataTypeInt  = 29,
    MTDataTypeInt2 = 30,
    MTDataTypeInt3 = 31,
    MTDataTypeInt4 = 32,
    MTDataTypeUInt  = 33,
    MTDataTypeUInt2 = 34,
    MTDataTypeUInt3 = 35,
    MTDataTypeUInt4 = 36,
    MTDataTypeShort  = 37,
    MTDataTypeShort2 = 38,
    MTDataTypeShort3 = 39,
    MTDataTypeShort4 = 40,
    MTDataTypeUShort = 41,
    MTDataTypeUShort2 = 42,
    MTDataTypeUShort3 = 43,
    MTDataTypeUShort4 = 44,
    MTDataTypeChar  = 45,
    MTDataTypeChar2 = 46,
    MTDataTypeChar3 = 47,
    MTDataTypeChar4 = 48,
    MTDataTypeUChar  = 49,
    MTDataTypeUChar2 = 50,
    MTDataTypeUChar3 = 51,
    MTDataTypeUChar4 = 52,
    MTDataTypeBool  = 53,
    MTDataTypeBool2 = 54,
    MTDataTypeBool3 = 55,
    MTDataTypeBool4 = 56,
    MTDataTypeTexture = 58,
    MTDataTypeSampler = 59,
    MTDataTypePointer = 60,
    MTDataTypeR8Unorm = 62,
    MTDataTypeR8Snorm = 63,
    MTDataTypeR16Unorm = 64,
    MTDataTypeR16Snorm = 65,
    MTDataTypeRG8Unorm = 66,
    MTDataTypeRG8Snorm = 67,
    MTDataTypeRG16Unorm = 68,
    MTDataTypeRG16Snorm = 69,
    MTDataTypeRGBA8Unorm = 70,
    MTDataTypeRGBA8Unorm_sRGB = 71,
    MTDataTypeRGBA8Snorm = 72,
    MTDataTypeRGBA16Unorm = 73,
    MTDataTypeRGBA16Snorm = 74,
    MTDataTypeRGB10A2Unorm = 75,
    MTDataTypeRG11B10Float = 76,
    MTDataTypeRGB9E5Float = 77,
    MTDataTypeRenderPipeline = 78,
    MTDataTypeComputePipeline = 79,
    MTDataTypeIndirectCommandBuffer = 80,
    MTDataTypeLong = 81,
    MTDataTypeLong2 = 82,
    MTDataTypeLong3 = 83,
    MTDataTypeLong4 = 84,
    MTDataTypeULong = 85,
    MTDataTypeULong2 = 86,
    MTDataTypeULong3 = 87,
    MTDataTypeULong4 = 88,
    MTDataTypeVisibleFunctionTable = 115,
    MTDataTypeIntersectionFunctionTable = 116,
    MTDataTypePrimitiveAccelerationStructure = 117,
    MTDataTypeInstanceAccelerationStructure = 118,
    MTDataTypeBFloat = 121,
    MTDataTypeBFloat2 = 122,
    MTDataTypeBFloat3 = 123,
    MTDataTypeBFloat4 = 124,
} MTDataType;

typedef enum MTBindingType {
    MTBindingTypeBuffer = 0,
    MTBindingTypeThreadgroupMemory = 1,
    MTBindingTypeTexture = 2,
    MTBindingTypeSampler = 3,
    MTBindingTypeImageblockData = 16,
    MTBindingTypeImageblock = 17,
    MTBindingTypeVisibleFunctionTable = 24,
    MTBindingTypePrimitiveAccelerationStructure = 25,
    MTBindingTypeInstanceAccelerationStructure = 26,
    MTBindingTypeIntersectionFunctionTable = 27,
    MTBindingTypeObjectPayload = 34,
} MTBindingType;

typedef enum MTBindingAccess {
    MTBindingAccessReadOnly   = 0,
    MTBindingAccessReadWrite  = 1,
    MTBindingAccessWriteOnly  = 2,
} MTBindingAccess;

typedef void* MTBinding;
typedef void* MTBufferBinding;
typedef void* MTThreadgroupBinding;
typedef void* MTTextureBinding;
typedef void* MTObjectPayloadBinding;
typedef void* MTType;
typedef void* MTStructMember;
typedef void* MTStructType;
typedef void* MTArrayType;
typedef void* MTArray;
typedef void* MTPointerType;
typedef void* MTTextureReferenceType;
typedef void* MTString;

// MARK: MTBinding

MT_INLINE MTString mt_binding_get_name(MTBinding binding) {
    return MT_MSG_SEND(id, binding, MT_SEL("name"));
}

MT_INLINE MTBindingType mt_binding_get_type(MTBinding binding) {
    return MT_MSG_SEND(MTBindingType, binding, MT_SEL("type"));
}

MT_INLINE MTBindingAccess mt_binding_get_access(MTBinding binding) {
    return MT_MSG_SEND(MTBindingAccess, binding, MT_SEL("access"));
}

MT_INLINE NSUInteger mt_binding_get_index(MTBinding binding) {
    return MT_MSG_SEND(NSUInteger, binding, MT_SEL("index"));
}

MT_INLINE bool mt_binding_is_used(MTBinding binding) {
    return MT_MSG_SEND(BOOL, binding, MT_SEL("isUsed"));
}

MT_INLINE bool mt_binding_is_argument(MTBinding binding) {
    return MT_MSG_SEND(BOOL, binding, MT_SEL("isArgument"));
}

// MARK: MTBufferBinding

MT_INLINE NSUInteger mt_buffer_binding_get_alignment(MTBufferBinding binding) {
    return MT_MSG_SEND(NSUInteger, binding, MT_SEL("bufferAlignment"));
}

MT_INLINE NSUInteger mt_buffer_binding_get_data_size(MTBufferBinding binding) {
    return MT_MSG_SEND(NSUInteger, binding, MT_SEL("bufferDataSize"));
}

MT_INLINE MTDataType mt_buffer_binding_get_data_type(MTBufferBinding binding) {
    return MT_MSG_SEND(MTDataType, binding, MT_SEL("bufferDataType"));
}

MT_INLINE void* mt_buffer_binding_get_struct_type(MTBufferBinding binding) {
    return MT_MSG_SEND(id, binding, MT_SEL("bufferStructType"));
}

MT_INLINE void* mt_buffer_binding_get_pointer_type(MTBufferBinding binding) {
    return MT_MSG_SEND(id, binding, MT_SEL("bufferPointerType"));
}

// MARK: MTThreadgroupBinding

MT_INLINE NSUInteger mt_threadgroup_binding_get_alignment(MTThreadgroupBinding binding) {
    return MT_MSG_SEND(NSUInteger, binding, MT_SEL("threadgroupMemoryAlignment"));
}

MT_INLINE NSUInteger mt_threadgroup_binding_get_data_size(MTThreadgroupBinding binding) {
    return MT_MSG_SEND(NSUInteger, binding, MT_SEL("threadgroupMemoryDataSize"));
}

// MARK: MTTextureBinding

MT_INLINE MTTextureType mt_texture_binding_get_texture_type(MTTextureBinding binding) {
    return MT_MSG_SEND(MTTextureType, binding, MT_SEL("textureType"));
}

MT_INLINE MTDataType mt_texture_binding_get_data_type(MTTextureBinding binding) {
    return MT_MSG_SEND(MTDataType, binding, MT_SEL("textureDataType"));
}

MT_INLINE bool mt_texture_binding_is_depth(MTTextureBinding binding) {
    return MT_MSG_SEND(BOOL, binding, MT_SEL("isDepthTexture"));
}

MT_INLINE NSUInteger mt_texture_binding_get_array_length(MTTextureBinding binding) {
    return MT_MSG_SEND(NSUInteger, binding, MT_SEL("arrayLength"));
}

// MARK: MTObjectPayloadBinding

MT_INLINE NSUInteger mt_object_payload_binding_get_alignment(MTObjectPayloadBinding binding) {
    return MT_MSG_SEND(NSUInteger, binding, MT_SEL("objectPayloadAlignment"));
}

MT_INLINE NSUInteger mt_object_payload_binding_get_data_size(MTObjectPayloadBinding binding) {
    return MT_MSG_SEND(NSUInteger, binding, MT_SEL("objectPayloadDataSize"));
}

// MARK: MTType

MT_INLINE MTDataType mt_type_get_data_type(MTType type) {
    return MT_MSG_SEND(MTDataType, type, MT_SEL("dataType"));
}

// MARK: MTStructMember

MT_INLINE MTString mt_struct_member_get_name(MTStructMember member) {
    return MT_MSG_SEND(id, member, MT_SEL("name"));
}

MT_INLINE NSUInteger mt_struct_member_get_offset(MTStructMember member) {
    return MT_MSG_SEND(NSUInteger, member, MT_SEL("offset"));
}

MT_INLINE MTDataType mt_struct_member_get_data_type(MTStructMember member) {
    return MT_MSG_SEND(MTDataType, member, MT_SEL("dataType"));
}

MT_INLINE MTStructType mt_struct_member_get_struct_type(MTStructMember member) {
    return MT_MSG_SEND(id, member, MT_SEL("structType"));
}

MT_INLINE MTArrayType mt_struct_member_get_array_type(MTStructMember member) {
    return MT_MSG_SEND(id, member, MT_SEL("arrayType"));
}

MT_INLINE MTTextureReferenceType mt_struct_member_get_texture_reference_type(MTStructMember member) {
    return MT_MSG_SEND(id, member, MT_SEL("textureReferenceType"));
}

MT_INLINE MTPointerType mt_struct_member_get_pointer_type(MTStructMember member) {
    return MT_MSG_SEND(id, member, MT_SEL("pointerType"));
}

MT_INLINE NSUInteger mt_struct_member_get_argument_index(MTStructMember member) {
    return MT_MSG_SEND(NSUInteger, member, MT_SEL("argumentIndex"));
}

// MARK: MTStructType

MT_INLINE MTArray mt_struct_type_get_members(MTStructType type) {
    return MT_MSG_SEND(id, type, MT_SEL("members"));
}

MT_INLINE MTStructMember mt_struct_type_get_member_by_name(MTStructType type, MTString name) {
    return MT_MSG_SEND_1(id, type, MT_SEL("memberByName:"), id, name);
}

// MARK: MTArrayType

MT_INLINE MTDataType mt_array_type_get_element_type(MTArrayType type) {
    return MT_MSG_SEND(MTDataType, type, MT_SEL("elementType"));
}

MT_INLINE NSUInteger mt_array_type_get_array_length(MTArrayType type) {
    return MT_MSG_SEND(NSUInteger, type, MT_SEL("arrayLength"));
}

MT_INLINE NSUInteger mt_array_type_get_stride(MTArrayType type) {
    return MT_MSG_SEND(NSUInteger, type, MT_SEL("stride"));
}

MT_INLINE NSUInteger mt_array_type_get_argument_index_stride(MTArrayType type) {
    return MT_MSG_SEND(NSUInteger, type, MT_SEL("argumentIndexStride"));
}
    
MT_INLINE MTStructType mt_array_type_get_element_struct_type(MTArrayType type) {
    return MT_MSG_SEND(id, type, MT_SEL("elementStructType"));
}

MT_INLINE MTArrayType mt_array_type_get_element_array_type(MTArrayType type) {
    return MT_MSG_SEND(id, type, MT_SEL("elementArrayType"));
}

MT_INLINE MTTextureReferenceType mt_array_type_get_element_texture_reference_type(MTArrayType type) {
    return MT_MSG_SEND(id, type, MT_SEL("elementTextureReferenceType"));
}

MT_INLINE MTPointerType mt_array_type_get_element_pointer_type(MTArrayType type) {
    return MT_MSG_SEND(id, type, MT_SEL("elementPointerType"));
}

// MARK: MTPointerType Functions

MT_INLINE MTDataType mt_pointer_type_get_element_type(MTPointerType type) {
    return MT_MSG_SEND(MTDataType, type, MT_SEL("elementType"));
}

MT_INLINE MTBindingAccess mt_pointer_type_get_access(MTPointerType type) {
    return MT_MSG_SEND(MTBindingAccess, type, MT_SEL("access"));
}

MT_INLINE NSUInteger mt_pointer_type_get_alignment(MTPointerType type) {
    return MT_MSG_SEND(NSUInteger, type, MT_SEL("alignment"));
}

MT_INLINE NSUInteger mt_pointer_type_get_data_size(MTPointerType type) {
    return MT_MSG_SEND(NSUInteger, type, MT_SEL("dataSize"));
}

MT_INLINE BOOL mt_pointer_type_element_is_argument_buffer(MTPointerType type) {
    return MT_MSG_SEND(BOOL, type, MT_SEL("elementIsArgumentBuffer"));
}
    
MT_INLINE MTStructType mt_pointer_type_get_element_struct_type(MTPointerType type) {
    return MT_MSG_SEND(id, type, MT_SEL("elementStructType"));
}

MT_INLINE MTArrayType mt_pointer_type_get_element_array_type(MTPointerType type) {
    return MT_MSG_SEND(id, type, MT_SEL("elementArrayType"));
}

// MARK: MTTextureReferenceType Functions

MT_INLINE MTDataType mt_texture_reference_type_get_texture_data_type(MTTextureReferenceType type) {
    return MT_MSG_SEND(MTDataType, type, MT_SEL("textureDataType"));
}

MT_INLINE MTTextureType mt_texture_reference_type_get_texture_type(MTTextureReferenceType type) {
    return MT_MSG_SEND(MTTextureType, type, MT_SEL("textureType"));
}

MT_INLINE MTBindingAccess mt_texture_reference_type_get_access(MTTextureReferenceType type) {
    return MT_MSG_SEND(MTBindingAccess, type, MT_SEL("access"));
}

MT_INLINE BOOL mt_texture_reference_type_is_depth_texture(MTTextureReferenceType type) {
    return MT_MSG_SEND(BOOL, type, MT_SEL("isDepthTexture"));
}

// MARK: MTArray Helper Functions

MT_INLINE NSUInteger mt_array_get_count(MTArray array) {
    return MT_MSG_SEND(NSUInteger, array, MT_SEL("count"));
}

MT_INLINE MTStructMember mt_array_get_object_at_index(MTArray array, NSUInteger index) {
    return MT_MSG_SEND_1(id, array, MT_SEL("objectAtIndex:"), NSUInteger, index);
}
