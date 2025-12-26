//
//  MTDevice.h
//  Metal C
//
//  Created by Lungile Maseko on 2024/04/29.
//
#pragma once

#include <stdint.h>
#include "MTUtils.h"
#include "MTHeap.h"
#include "MTResource.h"
#include "MTRenderPipeline.h"
#include "MTTexture.h"
#include "MTSampler.h"
#include "MTDepthStencil.h"

typedef void* MTDevice;

extern MTDevice* MTLCreateSystemDefaultDevice(void);

typedef enum MTIOCompressionMethod {
    MTIOCompressionMethod_ZLib = 0,
    MTIOCompressionMethod_LZFSE = 1,
    MTIOCompressionMethod_LZ4 = 2,
    MTIOCompressionMethod_LZMA = 3,
    MTIOCompressionMethod_Bitmap = 4,
} MTIOCompressionMethod;

typedef enum MTFeatureSet {
    MTFeatureSet_iOS_GPUFamily1_v1 = 0,
    MTFeatureSet_iOS_GPUFamily2_v1 = 1,
    MTFeatureSet_iOS_GPUFamily1_v2 = 2,
    MTFeatureSet_iOS_GPUFamily2_v2 = 3,
    MTFeatureSet_iOS_GPUFamily3_v1 = 4,
    MTFeatureSet_iOS_GPUFamily1_v3 = 5,
    MTFeatureSet_iOS_GPUFamily2_v3 = 6,
    MTFeatureSet_iOS_GPUFamily3_v2 = 7,
    MTFeatureSet_iOS_GPUFamily1_v4 = 8,
    MTFeatureSet_iOS_GPUFamily2_v4 = 9,
    MTFeatureSet_iOS_GPUFamily3_v3 = 10,
    MTFeatureSet_iOS_GPUFamily4_v1 = 11,
    MTFeatureSet_iOS_GPUFamily1_v5 = 12,
    MTFeatureSet_iOS_GPUFamily2_v5 = 13,
    MTFeatureSet_iOS_GPUFamily3_v4 = 14,
    MTFeatureSet_iOS_GPUFamily4_v2 = 15,
    MTFeatureSet_iOS_GPUFamily5_v1 = 16,
    MTFeatureSet_macOS_GPUFamily1_v1 = 10000,
    MTFeatureSet_OSX_GPUFamily1_v1 = 10000,
    MTFeatureSet_macOS_GPUFamily1_v2 = 10001,
    MTFeatureSet_OSX_GPUFamily1_v2 = 10001,
    MTFeatureSet_macOS_ReadWriteTextureTier2 = 10002,
    MTFeatureSet_OSX_ReadWriteTextureTier2 = 10002,
    MTFeatureSet_macOS_GPUFamily1_v3 = 10003,
    MTFeatureSet_macOS_GPUFamily1_v4 = 10004,
    MTFeatureSet_macOS_GPUFamily2_v1 = 10005,
    MTFeatureSet_watchOS_GPUFamily1_v1 = 20000,
    MTFeatureSet_WatchOS_GPUFamily1_v1 = 20000,
    MTFeatureSet_watchOS_GPUFamily2_v1 = 20001,
    MTFeatureSet_WatchOS_GPUFamily2_v1 = 20001,
    MTFeatureSet_tvOS_GPUFamily1_v1 = 30000,
    MTFeatureSet_TVOS_GPUFamily1_v1 = 30000,
    MTFeatureSet_tvOS_GPUFamily1_v2 = 30001,
    MTFeatureSet_tvOS_GPUFamily1_v3 = 30002,
    MTFeatureSet_tvOS_GPUFamily2_v1 = 30003,
    MTFeatureSet_tvOS_GPUFamily1_v4 = 30004,
    MTFeatureSet_tvOS_GPUFamily2_v2 = 30005,
} MTFeatureSet;

typedef enum MTGPUFamily {
    MTGPUFamilyApple1 = 1001,
    MTGPUFamilyApple2 = 1002,
    MTGPUFamilyApple3 = 1003,
    MTGPUFamilyApple4 = 1004,
    MTGPUFamilyApple5 = 1005,
    MTGPUFamilyApple6 = 1006,
    MTGPUFamilyApple7 = 1007,
    MTGPUFamilyApple8 = 1008,
    MTGPUFamilyApple9 = 1009,
    MTGPUFamilyMac1 = 2001,
    MTGPUFamilyMac2 = 2002,
    MTGPUFamilyCommon1 = 3001,
    MTGPUFamilyCommon2 = 3002,
    MTGPUFamilyCommon3 = 3003,
    MTGPUFamilyMacCatalyst1 = 4001,
    MTGPUFamilyMacCatalyst2 = 4002,
    MTGPUFamilyMetal3 = 5001,
} MTGPUFamily;

typedef enum MTDeviceLocation {
    MTDeviceLocationBuiltIn = 0,
    MTDeviceLocationSlot = 1,
    MTDeviceLocationExternal = 2,
    MTDeviceLocationUnspecified = UINTPTR_MAX,
} MTDeviceLocation;

typedef enum MTPipelineOption {
    MTPipelineOptionNone = 0,
    MTPipelineOptionArgumentInfo = 1,
    MTPipelineOptionBufferTypeInfo = 2,
    MTPipelineOptionFailOnBinaryArchiveMiss = 4,
} MTPipelineOption;

typedef enum MTReadWriteTextureTier {
    MTReadWriteTextureTierNone = 0,
    MTReadWriteTextureTier1 = 1,
    MTReadWriteTextureTier2 = 2,
} MTReadWriteTextureTier;

typedef enum MTArgumentBuffersTier {
    MTArgumentBuffersTier1 = 0,
    MTArgumentBuffersTier2 = 1,
} MTArgumentBuffersTier;

typedef enum MTSparseTextureRegionAlignmentMode {
    MTSparseTextureRegionAlignmentModeOutward = 0,
    MTSparseTextureRegionAlignmentModeInward = 1,
} MTSparseTextureRegionAlignmentMode;

typedef struct MTAccelerationStructureSizes {
    unsigned long accelerationStructureSize;
    unsigned long buildScratchBufferSize;
    unsigned long refitScratchBufferSize;
} MTAccelerationStructureSizes;

typedef enum MTCounterSamplingPoint {
    MTCounterSamplingPointAtStageBoundary = 0,
    MTCounterSamplingPointAtDrawBoundary = 1,
    MTCounterSamplingPointAtDispatchBoundary = 2,
    MTCounterSamplingPointAtTileDispatchBoundary = 3,
    MTCounterSamplingPointAtBlitBoundary = 4,
} MTCounterSamplingPoint;

typedef struct MTSizeAndAlign {
    unsigned long size;
    unsigned long align;
} MTSizeAndAlign;

MT_INLINE MTDevice* mt_create_system_default_device(void) {
    return (MTDevice*)MTLCreateSystemDefaultDevice();
}

MT_INLINE const char* mt_device_get_name(MTDevice device) {
    if (!device) return NULL;
    id nsStr = MT_MSG_SEND(id, device, MT_SEL("name"));
    if (!nsStr) return NULL;
    return MT_MSG_SEND(const char*, nsStr, MT_SEL("UTF8String"));
}

typedef void* MTBuffer;
typedef void* MTIndirectCommandBuffer;
typedef void* MTIndirectCommandBufferDescriptor;
typedef void* MTRenderPipelineReflection;
typedef void* MTIOFileHandle;
typedef void* MTIOCommandQueue;
typedef void* MTIOCommandQueueDescriptor;
typedef void* MTBinaryArchiveDescriptor;
typedef void* MTBinaryArchive;

typedef void (*render_pipeline_callback_t)(void *userdata, MTRenderPipelineState pipeline, MTError *error);
typedef void (*render_pipeline_with_reflection_callback_t)(void *userdata, MTRenderPipelineState pipeline, MTRenderPipelineReflection *reflection, MTError *error);
typedef void (*MTNewRenderPipelineStateCallback)(void *userdata, MTRenderPipelineState pipelineState, MTError error);

// ============================================================================
// Buffer Creation
// ============================================================================

MT_INLINE MTBuffer mt_device_create_buffer_with_bytes(MTDevice device, void* ptr, uintptr_t length, MTResourceOptions options) {
    return MT_MSG_SEND_3(id, device, MT_SEL("newBufferWithBytes:length:options:"), void*, ptr, uintptr_t, length, MTResourceOptions, options);
}

MT_INLINE MTBuffer mt_device_create_buffer_with_length(MTDevice device, uintptr_t length, MTResourceOptions options) {
    return MT_MSG_SEND_2(id, device, MT_SEL("newBufferWithLength:options:"), uintptr_t, length, MTResourceOptions, options);
}

MT_INLINE MTIndirectCommandBuffer mt_device_new_indirect_command_buffer(MTDevice device, MTIndirectCommandBufferDescriptor descriptor, unsigned long maxCommandCount, MTResourceOptions options) {
    return MT_MSG_SEND_3(id, device, MT_SEL("newIndirectCommandBufferWithDescriptor:maxCommandCount:options:"), id, descriptor, unsigned long, maxCommandCount, MTResourceOptions, options);
}

// ============================================================================
// Pipeline State Creation
// ============================================================================

MT_INLINE MTRenderPipelineState mt_device_create_render_pipeline_state(MTDevice device, MTRenderPipelineDescriptor render_desc, MTError** error) {
    return MT_MSG_SEND_2(id, device, MT_SEL("newRenderPipelineStateWithDescriptor:error:"), id, render_desc, MTError**, error);
}

MT_INLINE void mt_device_new_render_pipeline_state_async(id device, MTRenderPipelineDescriptor descriptor, MTNewRenderPipelineStateCallback callback, void *userdata) {
    SEL sel = sel_registerName("newRenderPipelineStateWithDescriptor:completionHandler:");
    typedef void (*MsgSendFn)(id, SEL, id, void *);
    void (^handler)(MTRenderPipelineState, MTError *) = ^(MTRenderPipelineState pipelineState, MTError *err) {
        callback(userdata, pipelineState, err);
    };
    MsgSendFn fn = (MsgSendFn)objc_msgSend;
    fn(device, sel, (id)descriptor, handler);
}

MT_INLINE id mt_new_render_pipeline_state_with_reflection(id device, MTRenderPipelineDescriptor desc, MTPipelineOption options, MTRenderPipelineReflection **out_reflection, MTError **out_error) {
    return MT_MSG_SEND_4(id, device, MT_SEL("newRenderPipelineStateWithDescriptor:options:reflection:error:"), id, desc, MTPipelineOption, options, MTRenderPipelineReflection**, out_reflection, MTError**, out_error);
}

MT_INLINE void mt_new_render_pipeline_state_with_reflection_async(id device, MTRenderPipelineDescriptor desc, MTPipelineOption options, render_pipeline_with_reflection_callback_t callback, void *userdata) {
    SEL sel = sel_registerName("newRenderPipelineStateWithDescriptor:options:completionHandler:");
    typedef void (*MsgSendFn)(id, SEL, id, MTPipelineOption, void (^)(MTRenderPipelineState, MTRenderPipelineReflection, MTError *));
    void (^handler)(MTRenderPipelineState, MTRenderPipelineReflection, MTError *) = ^(MTRenderPipelineState pipelineState, MTRenderPipelineReflection pipelineReflection, MTError *error) {
        callback(userdata, pipelineState, pipelineReflection, error);
    };
    MsgSendFn fn = (MsgSendFn)objc_msgSend;
    fn(device, sel, (id)desc, options, handler);
}

// ============================================================================
// Resource Creation
// ============================================================================

MT_INLINE MTTexture mt_device_create_texture_with_descriptor(MTDevice device, MTTextureDescriptor texture_desc) {
    return MT_MSG_SEND_1(id, device, MT_SEL("newTextureWithDescriptor:"), id, texture_desc);
}

MT_INLINE MTTexture mt_device_create_shared_texture_with_descriptor(MTDevice device, MTTextureDescriptor texture_desc) {
    return MT_MSG_SEND_1(id, device, MT_SEL("newSharedTextureWithDescriptor:"), id, texture_desc);
}

MT_INLINE MTSamplerState mt_device_create_sampler_state(MTDevice device, MTSamplerDescriptor sampler_desc) {
    return MT_MSG_SEND_1(id, device, MT_SEL("newSamplerStateWithDescriptor:"), id, sampler_desc);
}

MT_INLINE MTDepthStencilState mt_device_create_depth_stencil_state(MTDevice device, MTDepthStencilDescriptor desc) {
    return MT_MSG_SEND_1(id, device, MT_SEL("newDepthStencilStateWithDescriptor:"), id, desc);
}

// Struct returns need explicit casts (can't use macros cleanly)
MT_INLINE MTSizeAndAlign mt_device_heap_texture_size_and_align(MTDevice device, MTTextureDescriptor* desc) {
    typedef MTSizeAndAlign (*HeapTextureSizeAlignFunc)(id, SEL, id);
    return ((HeapTextureSizeAlignFunc)objc_msgSend)((id)device, MT_SEL("heapTextureSizeAndAlignWithDescriptor:"), (id)desc);
}

MT_INLINE MTSizeAndAlign mt_device_heap_buffer_size_and_align(MTDevice device, NSUInteger length, MTResourceOptions options) {
    typedef MTSizeAndAlign (*HeapBufferSizeAlignFunc)(id, SEL, NSUInteger, MTResourceOptions);
    return ((HeapBufferSizeAlignFunc)objc_msgSend)((id)device, MT_SEL("heapBufferSizeAndAlignWithLength:options:"), length, options);
}

MT_INLINE MTHeap mt_device_create_heap_with_descriptor(MTDevice device, MTHeapDescriptor descriptor) {
    return MT_MSG_SEND_1(id, device, MT_SEL("newHeapWithDescriptor:"), id, descriptor);
}

// ============================================================================
// Device Capabilities
// ============================================================================

MT_INLINE bool mt_device_supports_family(MTDevice device, MTGPUFamily gpu_family) {
    return MT_MSG_SEND_1(bool, device, MT_SEL("supportsFamily:"), MTGPUFamily, gpu_family);
}

MT_INLINE bool mt_device_supports_texture_sample_count(MTDevice device, uintptr_t count) {
    return MT_MSG_SEND_1(bool, device, MT_SEL("supportsTextureSampleCount:"), uintptr_t, count);
}

MT_INLINE uintptr_t mt_device_max_buffer_length(MTDevice device) {
    return MT_MSG_SEND(uintptr_t, device, MT_SEL("maxBufferLength"));
}

MT_INLINE bool mt_device_supports_counter_sampling(MTDevice device, MTCounterSamplingPoint sampling_point) {
    return MT_MSG_SEND_1(bool, device, MT_SEL("supportsCounterSampling:"), MTCounterSamplingPoint, sampling_point);
}

MT_INLINE bool mt_device_supports_vertex_amplification_count(MTDevice device, uintptr_t count) {
    return MT_MSG_SEND_1(bool, device, MT_SEL("supportsVertexAmplificationCount:"), uintptr_t, count);
}

MT_INLINE bool mt_device_supports_dynamic_libraries(MTDevice device) {
    return MT_MSG_SEND(bool, device, MT_SEL("supportsDynamicLibraries"));
}

MT_INLINE bool mt_device_supports_render_dynamic_libraries(MTDevice device) {
    return MT_MSG_SEND(bool, device, MT_SEL("supportsRenderDynamicLibraries"));
}

MT_INLINE bool mt_device_supports_ray_tracing(MTDevice device) {
    return MT_MSG_SEND(bool, device, MT_SEL("supportsRaytracing"));
}

MT_INLINE bool mt_device_supports_ray_tracing_from_render(MTDevice device) {
    return MT_MSG_SEND(bool, device, MT_SEL("supportsRaytracingFromRender"));
}

MT_INLINE bool mt_device_supports_function_pointers(MTDevice device) {
    return MT_MSG_SEND(bool, device, MT_SEL("supportsFunctionPointers"));
}

MT_INLINE bool mt_device_supports_function_pointers_from_render(MTDevice device) {
    return MT_MSG_SEND(bool, device, MT_SEL("supportsFunctionPointersFromRender"));
}

MT_INLINE bool mt_device_supports_primitive_motion_blur(MTDevice device) {
    return MT_MSG_SEND(bool, device, MT_SEL("supportsPrimitiveMotionBlur"));
}

MT_INLINE uintptr_t mt_device_maximum_concurrent_compilation_task_count(MTDevice device) {
    return MT_MSG_SEND(uintptr_t, device, MT_SEL("maximumConcurrentCompilationTaskCount"));
}

// ============================================================================
// IO
// ============================================================================

MT_INLINE MTIOFileHandle mt_device_new_io_file_handle(MTDevice device, MTURL url, MTError** outError) {
    return MT_MSG_SEND_2(id, device, MT_SEL("newIOFileHandleWithURL:error:"), id, url, MTError**, outError);
}

MT_INLINE MTIOFileHandle mt_device_new_io_file_handle_with_compression(MTDevice device, MTURL url, MTIOCompressionMethod compression, MTError** outError) {
    return MT_MSG_SEND_3(id, device, MT_SEL("newIOFileHandleWithURL:compressionMethod:error:"), id, url, unsigned long, compression, MTError**, outError);
}

MT_INLINE MTIOCommandQueue mt_device_new_io_command_queue(MTDevice device, MTIOCommandQueueDescriptor desc, MTError** outError) {
    return MT_MSG_SEND_2(id, device, MT_SEL("newIOCommandQueueWithDescriptor:error:"), id, desc, MTError**, outError);
}

// ============================================================================
// Binary Archive
// ============================================================================

MT_INLINE MTBinaryArchive mt_device_new_binary_archive(MTDevice device, MTBinaryArchiveDescriptor desc, MTError** outError) {
    return MT_MSG_SEND_2(id, device, MT_SEL("newBinaryArchiveWithDescriptor:error:"), id, desc, MTError**, outError);
}
