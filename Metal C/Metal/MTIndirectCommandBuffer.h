//
//  MTIndirectCommandBuffer.h
//  Metal C
//
//  Created by Lungile Maseko on 2025/05/31.
//
#pragma once
#include "MTUtils.h"

typedef void* MTIndirectCommandBuffer;
typedef void* MTIndirectCommandBufferDescriptor;
typedef void* MTIndirectRenderCommand;
typedef void* MTIndirectComputeCommand;

typedef enum MTIndirectCommandType {
    MTLIndirectCommandTypeDraw                = (1 << 0),
    MTLIndirectCommandTypeDrawIndexed         = (1 << 1),
    MTLIndirectCommandTypeDrawPatches         = (1 << 2),
    MTLIndirectCommandTypeDrawIndexedPatches  = (1 << 3) ,

    MTLIndirectCommandTypeConcurrentDispatch  = (1 << 5), /* Dispatch threadgroups with concurrent execution */

    MTLIndirectCommandTypeConcurrentDispatchThreads = (1 << 6), /* Dispatch threads with concurrent execution */
    MTLIndirectCommandTypeDrawMeshThreadgroups= (1 << 7),
    MTLIndirectCommandTypeDrawMeshThreads = (1 << 8),
} MTIndirectCommandType;

typedef struct MTIndirectCommandBufferExecutionRange {
    uint32_t location;
    uint32_t length;
} MTIndirectCommandBufferExecutionRange;

MT_INLINE MTIndirectCommandBufferExecutionRange MTLIndirectCommandBufferExecutionRangeMake(uint32_t location, uint32_t length)
{
    MTIndirectCommandBufferExecutionRange icbRange = {location, length};
    return icbRange;
}

MT_INLINE MTIndirectCommandBufferDescriptor mt_indirect_command_buffer_descriptor_create(void) {
    Class descriptorClass = objc_getClass("MTLIndirectCommandBufferDescriptor");
    SEL allocSel = sel_registerName("alloc");
    SEL initSel = sel_registerName("init");

    id descriptor = ((id (*)(Class, SEL))objc_msgSend)(descriptorClass, allocSel);
    descriptor = ((id (*)(id, SEL))objc_msgSend)(descriptor, initSel);

    return (MTIndirectCommandBufferDescriptor)descriptor;
}

MT_INLINE MTIndirectRenderCommand mt_icb_get_render_command_at(MTIndirectCommandBuffer buffer, unsigned long index) {
    SEL sel = sel_registerName("indirectRenderCommandAtIndex:");
    return ((MTIndirectRenderCommand (*)(id, SEL, unsigned long))objc_msgSend)(buffer, sel, index);
}

MT_INLINE MTIndirectComputeCommand mt_icb_get_compute_command_at(MTIndirectCommandBuffer buffer, unsigned long index) {
    SEL sel = sel_registerName("indirectComputeCommandAtIndex:");
    return ((MTIndirectComputeCommand (*)(id, SEL, unsigned long))objc_msgSend)(buffer, sel, index);
}

MT_INLINE void mt_icb_descriptor_set_command_types(MTIndirectCommandBufferDescriptor desc, MTIndirectCommandType types) {
    ((void (*)(id, SEL, MTIndirectCommandType))objc_msgSend)(desc, sel_registerName("setCommandTypes:"), types);
}

MT_INLINE void mt_icb_descriptor_set_inherit_pipeline_state(MTIndirectCommandBufferDescriptor desc, bool inherit) {
    ((void (*)(id, SEL, BOOL))objc_msgSend)(desc, sel_registerName("setInheritPipelineState:"), inherit);
}

MT_INLINE void mt_icb_descriptor_set_inherit_buffers(MTIndirectCommandBufferDescriptor desc, bool inherit) {
    ((void (*)(id, SEL, BOOL))objc_msgSend)(desc, sel_registerName("setInheritBuffers:"), inherit);
}

MT_INLINE void mt_icb_descriptor_set_max_vertex_buffer_bind_count(MTIndirectCommandBufferDescriptor desc, uint32_t count) {
    ((void (*)(id, SEL, NSUInteger))objc_msgSend)(desc, sel_registerName("setMaxVertexBufferBindCount:"), count);
}

MT_INLINE void mt_icb_descriptor_set_max_fragment_buffer_bind_count(MTIndirectCommandBufferDescriptor desc, uint32_t count) {
    ((void (*)(id, SEL, NSUInteger))objc_msgSend)(desc, sel_registerName("setMaxFragmentBufferBindCount:"), count);
}

MT_INLINE void mt_icb_descriptor_set_max_kernel_buffer_bind_count(MTIndirectCommandBufferDescriptor desc, uint32_t count) {
    ((void (*)(id, SEL, NSUInteger))objc_msgSend)(desc, sel_registerName("setMaxKernelBufferBindCount:"), count);
}

MT_INLINE void mt_icb_descriptor_set_max_kernel_threadgroup_memory_bind_count(MTIndirectCommandBufferDescriptor desc, uint32_t count) {
    ((void (*)(id, SEL, NSUInteger))objc_msgSend)(desc, sel_registerName("setMaxKernelThreadgroupMemoryBindCount:"), count);
}

MT_INLINE void mt_icb_descriptor_set_max_object_buffer_bind_count(MTIndirectCommandBufferDescriptor desc, uint32_t count) {
    ((void (*)(id, SEL, NSUInteger))objc_msgSend)(desc, sel_registerName("setMaxObjectBufferBindCount:"), count);
}

MT_INLINE void mt_icb_descriptor_set_max_mesh_buffer_bind_count(MTIndirectCommandBufferDescriptor desc, uint32_t count) {
    ((void (*)(id, SEL, NSUInteger))objc_msgSend)(desc, sel_registerName("setMaxMeshBufferBindCount:"), count);
}

MT_INLINE void mt_icb_descriptor_set_max_object_threadgroup_memory_bind_count(MTIndirectCommandBufferDescriptor desc, uint32_t count) {
    ((void (*)(id, SEL, NSUInteger))objc_msgSend)(desc, sel_registerName("setMaxObjectThreadgroupMemoryBindCount:"), count);
}

MT_INLINE void mt_icb_descriptor_set_support_ray_tracing(MTIndirectCommandBufferDescriptor desc, bool support) {
    ((void (*)(id, SEL, BOOL))objc_msgSend)(desc, sel_registerName("setSupportRayTracing:"), support);
}

MT_INLINE void mt_icb_descriptor_set_support_dynamic_attribute_stride(MTIndirectCommandBufferDescriptor desc, bool support) {
    ((void (*)(id, SEL, BOOL))objc_msgSend)(desc, sel_registerName("setSupportDynamicAttributeStride:"), support);
}

MT_INLINE MTIndirectCommandType mt_icb_descripter_get_command_types(MTIndirectCommandBufferDescriptor desc) {
    SEL sel = sel_getUid("commandTypes");
    return ((MTIndirectCommandType (*)(id, SEL))objc_msgSend)(desc, sel);
}

MT_INLINE bool mt_icb_descripter_get_inherit_pipeline_state(MTIndirectCommandBufferDescriptor desc) {
    SEL sel = sel_getUid("inheritPipelineState");
    return ((BOOL (*)(id, SEL))objc_msgSend)(desc, sel);
}

MT_INLINE bool mt_icb_descripter_get_inherit_buffers(MTIndirectCommandBufferDescriptor desc) {
    SEL sel = sel_getUid("inheritBuffers");
    return ((BOOL (*)(id, SEL))objc_msgSend)(desc, sel);
}

MT_INLINE NSUInteger mt_icb_descripter_get_max_vertex_buffer_bind_count(MTIndirectCommandBufferDescriptor desc) {
    SEL sel = sel_getUid("maxVertexBufferBindCount");
    return ((NSUInteger (*)(id, SEL))objc_msgSend)(desc, sel);
}

MT_INLINE NSUInteger mt_icb_descripter_get_max_fragment_buffer_bind_count(MTIndirectCommandBufferDescriptor desc) {
    SEL sel = sel_getUid("maxFragmentBufferBindCount");
    return ((NSUInteger (*)(id, SEL))objc_msgSend)(desc, sel);
}

MT_INLINE NSUInteger mt_icb_descripter_get_max_kernel_buffer_bind_count(MTIndirectCommandBufferDescriptor desc) {
    SEL sel = sel_getUid("maxKernelBufferBindCount");
    return ((NSUInteger (*)(id, SEL))objc_msgSend)(desc, sel);
}

MT_INLINE NSUInteger mt_icb_descripter_get_max_kernel_thread_group_memory_bind_count(MTIndirectCommandBufferDescriptor desc) {
    SEL sel = sel_getUid("maxKernelThreadgroupMemoryBindCount");
    return ((NSUInteger (*)(id, SEL))objc_msgSend)(desc, sel);
}

MT_INLINE NSUInteger mt_icb_descripter_get_max_object_buffer_bind_count(MTIndirectCommandBufferDescriptor desc) {
    SEL sel = sel_getUid("maxObjectBufferBindCount");
    return ((NSUInteger (*)(id, SEL))objc_msgSend)(desc, sel);
}

MT_INLINE NSUInteger mt_icb_descripter_get_max_mesh_buffer_bind_count(MTIndirectCommandBufferDescriptor desc) {
    SEL sel = sel_getUid("maxMeshBufferBindCount");
    return ((NSUInteger (*)(id, SEL))objc_msgSend)(desc, sel);
}

MT_INLINE NSUInteger mt_icb_descripter_get_max_object_thread_group_memory_bind_count(MTIndirectCommandBufferDescriptor desc) {
    SEL sel = sel_getUid("maxObjectThreadgroupMemoryBindCount");
    return ((NSUInteger (*)(id, SEL))objc_msgSend)(desc, sel);
}

MT_INLINE bool mt_icb_descripter_get_support_ray_tracing(MTIndirectCommandBufferDescriptor desc) {
    SEL sel = sel_getUid("supportRayTracing");
    return ((BOOL (*)(id, SEL))objc_msgSend)(desc, sel);
}

MT_INLINE bool mt_icb_descripter_get_support_dynamic_attribute_stride(MTIndirectCommandBufferDescriptor desc) {
    SEL sel = sel_getUid("supportDynamicAttributeStride");
    return ((BOOL (*)(id, SEL))objc_msgSend)(desc, sel);
}

MT_INLINE void mt_icb_reset_with_range(MTIndirectCommandBuffer buffer, MTRange range) {
    SEL sel = sel_registerName("resetWithRange:");
    ((void (*)(id, SEL, MTRange))objc_msgSend)(buffer, sel, range);
}

