//
//  MTAccelerationStructure.h
//  Metal C
//
//  Hardware ray-tracing acceleration structures — the classic (Metal 3) path.
//  Header-only objc_msgSend shims in the wrapper's MT_INLINE style, bound
//  against the system SDK:
//    - MTLAccelerationStructure.h                (descriptors + device methods)
//    - MTLAccelerationStructureCommandEncoder.h  (build encoder)
//    - MTLComputeCommandEncoder.h                (setAccelerationStructure:)
//
//  Used by the offline lightmap baker. The runtime engine does NOT ray trace,
//  so this is only compiled into the baker tool. Opaque handles
//  MTAccelerationStructure / MTIntersectionFunctionTable are declared in
//  MTForwardDecls.h.
//
#pragma once
#include "MTUtils.h"
#include "MTTypes.h"
#include "MTResource.h"                 // MTResourceUsage
#include "MTStageInputOutputDescriptor.h"  // MTAttributeFormat, MTIndexType
#include "MTDevice.h"                   // MTAccelerationStructureSizes

MT_HANDLE(MTAccelerationStructureCommandEncoder);
MT_HANDLE(MTAccelerationStructureTriangleGeometryDescriptor);
MT_HANDLE(MTPrimitiveAccelerationStructureDescriptor);

// MTLAccelerationStructureUsage (MTLAccelerationStructure.h:44). The other
// types we need (MTAttributeFormat, MTIndexType, MTAccelerationStructureSizes)
// already exist in the wrapper and are reused via the includes above.
typedef enum MTAccelerationStructureUsage : NSUInteger {
    MTAccelerationStructureUsageNone                  = 0,
    MTAccelerationStructureUsageRefit                 = (1 << 0),
    MTAccelerationStructureUsagePreferFastBuild       = (1 << 1),
    MTAccelerationStructureUsageExtendedLimits        = (1 << 2),
    MTAccelerationStructureUsagePreferFastIntersection= (1 << 4),
} MTAccelerationStructureUsage;

// ---- NSArray helper (geometryDescriptors wants an NSArray) -----------------
MT_INLINE void* mt_array_with_objects(const void* const* objects, NSUInteger count) {
    return ((id (*)(Class, SEL, const void* const*, NSUInteger))objc_msgSend)(
        MT_CLASS("NSArray"), MT_SEL("arrayWithObjects:count:"), objects, count);
}

// ===========================================================================
// Triangle geometry descriptor
// (MTLAccelerationStructureTriangleGeometryDescriptor)
// ===========================================================================
MT_INLINE MTAccelerationStructureTriangleGeometryDescriptor
mt_as_triangle_geometry_descriptor_create(void) {
    return MT_MSG_SEND_CLASS(void*,
        MT_CLASS("MTLAccelerationStructureTriangleGeometryDescriptor"),
        MT_SEL("descriptor"));
}

MT_INLINE void mt_as_triangle_set_vertex_buffer(MTAccelerationStructureTriangleGeometryDescriptor d, MTBuffer buffer) {
    MT_MSG_SEND_1(void, d, MT_SEL("setVertexBuffer:"), id, buffer);
}
MT_INLINE void mt_as_triangle_set_vertex_buffer_offset(MTAccelerationStructureTriangleGeometryDescriptor d, NSUInteger offset) {
    MT_MSG_SEND_1(void, d, MT_SEL("setVertexBufferOffset:"), NSUInteger, offset);
}
MT_INLINE void mt_as_triangle_set_vertex_format(MTAccelerationStructureTriangleGeometryDescriptor d, MTAttributeFormat fmt) {
    MT_MSG_SEND_1(void, d, MT_SEL("setVertexFormat:"), NSUInteger, fmt);
}
MT_INLINE void mt_as_triangle_set_vertex_stride(MTAccelerationStructureTriangleGeometryDescriptor d, NSUInteger stride) {
    MT_MSG_SEND_1(void, d, MT_SEL("setVertexStride:"), NSUInteger, stride);
}
MT_INLINE void mt_as_triangle_set_index_buffer(MTAccelerationStructureTriangleGeometryDescriptor d, MTBuffer buffer) {
    MT_MSG_SEND_1(void, d, MT_SEL("setIndexBuffer:"), id, buffer);
}
MT_INLINE void mt_as_triangle_set_index_buffer_offset(MTAccelerationStructureTriangleGeometryDescriptor d, NSUInteger offset) {
    MT_MSG_SEND_1(void, d, MT_SEL("setIndexBufferOffset:"), NSUInteger, offset);
}
MT_INLINE void mt_as_triangle_set_index_type(MTAccelerationStructureTriangleGeometryDescriptor d, MTIndexType type) {
    MT_MSG_SEND_1(void, d, MT_SEL("setIndexType:"), NSUInteger, type);
}
MT_INLINE void mt_as_triangle_set_triangle_count(MTAccelerationStructureTriangleGeometryDescriptor d, NSUInteger count) {
    MT_MSG_SEND_1(void, d, MT_SEL("setTriangleCount:"), NSUInteger, count);
}
MT_INLINE void mt_as_geometry_set_opaque(MTAccelerationStructureTriangleGeometryDescriptor d, bool opaque) {
    MT_MSG_SEND_1(void, d, MT_SEL("setOpaque:"), BOOL, opaque);
}

// ===========================================================================
// Primitive acceleration-structure descriptor
// (MTLPrimitiveAccelerationStructureDescriptor)
// ===========================================================================
MT_INLINE MTPrimitiveAccelerationStructureDescriptor
mt_primitive_acceleration_structure_descriptor_create(void) {
    return MT_MSG_SEND_CLASS(void*,
        MT_CLASS("MTLPrimitiveAccelerationStructureDescriptor"),
        MT_SEL("descriptor"));
}
// geometries: C array of MTAccelerationStructureTriangleGeometryDescriptor handles.
MT_INLINE void mt_primitive_as_descriptor_set_geometry_descriptors(
        MTPrimitiveAccelerationStructureDescriptor desc,
        const void* const* geometries, NSUInteger count) {
    void* arr = mt_array_with_objects(geometries, count);
    MT_MSG_SEND_1(void, desc, MT_SEL("setGeometryDescriptors:"), id, arr);
}
// usage lives on the base MTLAccelerationStructureDescriptor.
MT_INLINE void mt_acceleration_structure_descriptor_set_usage(
        MTPrimitiveAccelerationStructureDescriptor desc, MTAccelerationStructureUsage usage) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setUsage:"), NSUInteger, usage);
}

// ===========================================================================
// Device methods
// ===========================================================================
// NOTE: struct-by-value return — only call with a valid (non-NULL) device.
MT_INLINE MTAccelerationStructureSizes
mt_device_acceleration_structure_sizes(MTDevice device, MTPrimitiveAccelerationStructureDescriptor desc) {
    return ((MTAccelerationStructureSizes (*)(id, SEL, id))objc_msgSend)(
        (id)device, MT_SEL("accelerationStructureSizesWithDescriptor:"), (id)desc);
}
MT_INLINE MTAccelerationStructure
mt_device_create_acceleration_structure_with_size(MTDevice device, NSUInteger size) {
    return MT_MSG_SEND_1(void*, device, MT_SEL("newAccelerationStructureWithSize:"), NSUInteger, size);
}

// ===========================================================================
// Command buffer -> acceleration-structure command encoder (classic)
// ===========================================================================
MT_INLINE MTAccelerationStructureCommandEncoder
mt_command_buffer_acceleration_structure_command_encoder(MTCommandBuffer cmd) {
    return MT_MSG_SEND(void*, cmd, MT_SEL("accelerationStructureCommandEncoder"));
}

MT_INLINE void mt_as_command_encoder_build(
        MTAccelerationStructureCommandEncoder enc,
        MTAccelerationStructure accel,
        MTPrimitiveAccelerationStructureDescriptor desc,
        MTBuffer scratch, NSUInteger scratchOffset) {
    MT_MSG_SEND_4(void, enc,
        MT_SEL("buildAccelerationStructure:descriptor:scratchBuffer:scratchBufferOffset:"),
        id, accel, id, desc, id, scratch, NSUInteger, scratchOffset);
}
MT_INLINE void mt_as_command_encoder_use_resource(
        MTAccelerationStructureCommandEncoder enc, MTResource resource, MTResourceUsage usage) {
    MT_MSG_SEND_2(void, enc, MT_SEL("useResource:usage:"), id, resource, MTResourceUsage, usage);
}
MT_INLINE void mt_as_command_encoder_end_encoding(MTAccelerationStructureCommandEncoder enc) {
    MT_MSG_SEND(void, enc, MT_SEL("endEncoding"));
}
