//
//  MTIndirectCommandBuffer.h
//  Metal C
//
//  Created by Lungile Maseko on 2025/05/31.
//
#pragma once
#include "MTUtils.h"
#include "MTTypes.h"

typedef void* MTIndirectCommandBuffer;
typedef void* MTIndirectCommandBufferDescriptor;
typedef void* MTIndirectRenderCommand;
typedef void* MTIndirectComputeCommand;

typedef enum MTIndirectCommandType {
    MTLIndirectCommandTypeDraw                = (1 << 0),
    MTLIndirectCommandTypeDrawIndexed         = (1 << 1),
    MTLIndirectCommandTypeDrawPatches         = (1 << 2),
    MTLIndirectCommandTypeDrawIndexedPatches  = (1 << 3),
    MTLIndirectCommandTypeConcurrentDispatch  = (1 << 5),
    MTLIndirectCommandTypeConcurrentDispatchThreads = (1 << 6),
    MTLIndirectCommandTypeDrawMeshThreadgroups= (1 << 7),
    MTLIndirectCommandTypeDrawMeshThreads = (1 << 8),
} MTIndirectCommandType;

typedef struct MTIndirectCommandBufferExecutionRange {
    uint32_t location;
    uint32_t length;
} MTIndirectCommandBufferExecutionRange;

MT_INLINE MTIndirectCommandBufferExecutionRange MTLIndirectCommandBufferExecutionRangeMake(uint32_t location, uint32_t length) {
    MTIndirectCommandBufferExecutionRange icbRange = {location, length};
    return icbRange;
}

MT_INLINE MTIndirectCommandBufferDescriptor mt_indirect_command_buffer_descriptor_create(void) {
    return MT_ALLOC_INIT("MTLIndirectCommandBufferDescriptor");
}

MT_INLINE MTIndirectRenderCommand mt_icb_get_render_command_at(MTIndirectCommandBuffer buffer, unsigned long index) {
    return MT_MSG_SEND_1(id, buffer, MT_SEL("indirectRenderCommandAtIndex:"), unsigned long, index);
}

MT_INLINE MTIndirectComputeCommand mt_icb_get_compute_command_at(MTIndirectCommandBuffer buffer, unsigned long index) {
    return MT_MSG_SEND_1(id, buffer, MT_SEL("indirectComputeCommandAtIndex:"), unsigned long, index);
}

MT_INLINE void mt_icb_descriptor_set_command_types(MTIndirectCommandBufferDescriptor desc, MTIndirectCommandType types) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setCommandTypes:"), MTIndirectCommandType, types);
}

MT_INLINE void mt_icb_descriptor_set_inherit_pipeline_state(MTIndirectCommandBufferDescriptor desc, bool inherit) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setInheritPipelineState:"), BOOL, inherit);
}

MT_INLINE void mt_icb_descriptor_set_inherit_buffers(MTIndirectCommandBufferDescriptor desc, bool inherit) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setInheritBuffers:"), BOOL, inherit);
}

MT_INLINE void mt_icb_descriptor_set_max_vertex_buffer_bind_count(MTIndirectCommandBufferDescriptor desc, uint32_t count) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setMaxVertexBufferBindCount:"), NSUInteger, count);
}

MT_INLINE void mt_icb_descriptor_set_max_fragment_buffer_bind_count(MTIndirectCommandBufferDescriptor desc, uint32_t count) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setMaxFragmentBufferBindCount:"), NSUInteger, count);
}

MT_INLINE void mt_icb_descriptor_set_max_kernel_buffer_bind_count(MTIndirectCommandBufferDescriptor desc, uint32_t count) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setMaxKernelBufferBindCount:"), NSUInteger, count);
}

MT_INLINE void mt_icb_descriptor_set_max_kernel_threadgroup_memory_bind_count(MTIndirectCommandBufferDescriptor desc, uint32_t count) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setMaxKernelThreadgroupMemoryBindCount:"), NSUInteger, count);
}

MT_INLINE void mt_icb_descriptor_set_max_object_buffer_bind_count(MTIndirectCommandBufferDescriptor desc, uint32_t count) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setMaxObjectBufferBindCount:"), NSUInteger, count);
}

MT_INLINE void mt_icb_descriptor_set_max_mesh_buffer_bind_count(MTIndirectCommandBufferDescriptor desc, uint32_t count) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setMaxMeshBufferBindCount:"), NSUInteger, count);
}

MT_INLINE void mt_icb_descriptor_set_max_object_threadgroup_memory_bind_count(MTIndirectCommandBufferDescriptor desc, uint32_t count) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setMaxObjectThreadgroupMemoryBindCount:"), NSUInteger, count);
}

MT_INLINE void mt_icb_descriptor_set_support_ray_tracing(MTIndirectCommandBufferDescriptor desc, bool support) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setSupportRayTracing:"), BOOL, support);
}

MT_INLINE void mt_icb_descriptor_set_support_dynamic_attribute_stride(MTIndirectCommandBufferDescriptor desc, bool support) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setSupportDynamicAttributeStride:"), BOOL, support);
}

MT_INLINE MTIndirectCommandType mt_icb_descripter_get_command_types(MTIndirectCommandBufferDescriptor desc) {
    return MT_MSG_SEND(MTIndirectCommandType, desc, MT_SEL("commandTypes"));
}

MT_INLINE bool mt_icb_descripter_get_inherit_pipeline_state(MTIndirectCommandBufferDescriptor desc) {
    return MT_MSG_SEND(BOOL, desc, MT_SEL("inheritPipelineState"));
}

MT_INLINE bool mt_icb_descripter_get_inherit_buffers(MTIndirectCommandBufferDescriptor desc) {
    return MT_MSG_SEND(BOOL, desc, MT_SEL("inheritBuffers"));
}

MT_INLINE NSUInteger mt_icb_descripter_get_max_vertex_buffer_bind_count(MTIndirectCommandBufferDescriptor desc) {
    return MT_MSG_SEND(NSUInteger, desc, MT_SEL("maxVertexBufferBindCount"));
}

MT_INLINE NSUInteger mt_icb_descripter_get_max_fragment_buffer_bind_count(MTIndirectCommandBufferDescriptor desc) {
    return MT_MSG_SEND(NSUInteger, desc, MT_SEL("maxFragmentBufferBindCount"));
}

MT_INLINE NSUInteger mt_icb_descripter_get_max_kernel_buffer_bind_count(MTIndirectCommandBufferDescriptor desc) {
    return MT_MSG_SEND(NSUInteger, desc, MT_SEL("maxKernelBufferBindCount"));
}

MT_INLINE NSUInteger mt_icb_descripter_get_max_kernel_thread_group_memory_bind_count(MTIndirectCommandBufferDescriptor desc) {
    return MT_MSG_SEND(NSUInteger, desc, MT_SEL("maxKernelThreadgroupMemoryBindCount"));
}

MT_INLINE NSUInteger mt_icb_descripter_get_max_object_buffer_bind_count(MTIndirectCommandBufferDescriptor desc) {
    return MT_MSG_SEND(NSUInteger, desc, MT_SEL("maxObjectBufferBindCount"));
}

MT_INLINE NSUInteger mt_icb_descripter_get_max_mesh_buffer_bind_count(MTIndirectCommandBufferDescriptor desc) {
    return MT_MSG_SEND(NSUInteger, desc, MT_SEL("maxMeshBufferBindCount"));
}

MT_INLINE NSUInteger mt_icb_descripter_get_max_object_thread_group_memory_bind_count(MTIndirectCommandBufferDescriptor desc) {
    return MT_MSG_SEND(NSUInteger, desc, MT_SEL("maxObjectThreadgroupMemoryBindCount"));
}

MT_INLINE bool mt_icb_descripter_get_support_ray_tracing(MTIndirectCommandBufferDescriptor desc) {
    return MT_MSG_SEND(BOOL, desc, MT_SEL("supportRayTracing"));
}

MT_INLINE bool mt_icb_descripter_get_support_dynamic_attribute_stride(MTIndirectCommandBufferDescriptor desc) {
    return MT_MSG_SEND(BOOL, desc, MT_SEL("supportDynamicAttributeStride"));
}

// Struct arg - explicit cast needed
MT_INLINE void mt_icb_reset_with_range(MTIndirectCommandBuffer buffer, MTRange range) {
    ((void (*)(id, SEL, MTRange))objc_msgSend)((id)buffer, MT_SEL("resetWithRange:"), range);
}
