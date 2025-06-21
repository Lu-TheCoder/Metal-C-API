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
typedef void* MTSharedEvent;
typedef void* MTSharedEventHandle;
typedef void* MTEvent;

extern MTDevice* MTLCreateSystemDefaultDevice(void);

typedef enum MTIOCompressionMethod
{
    MTIOCompressionMethod_ZLib = 0,
    MTIOCompressionMethod_LZFSE = 1,
    MTIOCompressionMethod_LZ4 = 2,
    MTIOCompressionMethod_LZMA = 3,
    MTIOCompressionMethod_Bitmap = 4,
}MTIOCompressionMethod;

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
}MTFeatureSet;

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
}MTGPUFamily;

typedef enum MTDeviceLocation {
    MTDeviceLocationBuiltIn = 0,
    MTDeviceLocationSlot = 1,
    MTDeviceLocationExternal = 2,
    MTDeviceLocationUnspecified = UINTPTR_MAX,
}MTDeviceLocation;

typedef enum MTPipelineOption {
    MTPipelineOptionNone = 0,
    MTPipelineOptionArgumentInfo = 1,
    MTPipelineOptionBufferTypeInfo = 2,
    MTPipelineOptionFailOnBinaryArchiveMiss = 4,
}MTPipelineOption;

typedef enum MTReadWriteTextureTier {
    MTReadWriteTextureTierNone = 0,
    MTReadWriteTextureTier1 = 1,
    MTReadWriteTextureTier2 = 2,
}MTReadWriteTextureTier;

typedef enum MTArgumentBuffersTier {
    MTArgumentBuffersTier1 = 0,
    MTArgumentBuffersTier2 = 1,
}MTArgumentBuffersTier;

typedef enum MTSparseTextureRegionAlignmentMode {
    MTSparseTextureRegionAlignmentModeOutward = 0,
    MTSparseTextureRegionAlignmentModeInward = 1,
}MTSparseTextureRegionAlignmentMode;

typedef struct MTAccelerationStructureSizes{
    unsigned long accelerationStructureSize;
    unsigned long buildScratchBufferSize;
    unsigned long refitScratchBufferSize;
}MTAccelerationStructureSizes;

typedef enum MTCounterSamplingPoint {
    MTCounterSamplingPointAtStageBoundary = 0,
    MTCounterSamplingPointAtDrawBoundary = 1,
    MTCounterSamplingPointAtDispatchBoundary = 2,
    MTCounterSamplingPointAtTileDispatchBoundary = 3,
    MTCounterSamplingPointAtBlitBoundary = 4,
}MTCounterSamplingPoint;

typedef struct MTSizeAndAlign {
    unsigned long size;
    unsigned long align;
}MTSizeAndAlign;

MT_INLINE MTDevice* mt_create_system_default_device(void){
    return (MTDevice*) MTLCreateSystemDefaultDevice();
}

MT_INLINE const char* mt_device_get_name(MTDevice device) {
    if (!device) return NULL;

    // Call: [device name]
    SEL nameSel = sel_registerName("name");
    id (*msgSendObj)(id, SEL) = (id (*)(id, SEL))objc_msgSend;
    id nsStr = msgSendObj((id)device, nameSel);
    if (!nsStr) return NULL;

    // Call: [name UTF8String]
    SEL utf8Sel = sel_registerName("UTF8String");
    const char* (*msgSendUTF8)(id, SEL) = (const char* (*)(id, SEL))objc_msgSend;
    return msgSendUTF8(nsStr, utf8Sel);
}

typedef void* MTURL;
typedef void* MTBuffer;
typedef void* MTIndirectCommandBuffer;
typedef void* MTIndirectCommandBufferDescriptor;
typedef void* MTRenderPipelineReflection;

typedef void* MTTextureDescriptor;
typedef void* MTHeapDescriptor;

typedef void* MTIOFileHandle;
typedef void* MTIOCommandQueue;
typedef void* MTIOCommandQueueDescriptor;

typedef void* MTBinaryArchiveDescriptor;
typedef void* MTBinaryArchive;


typedef void (*render_pipeline_callback_t)(
    void *userdata,
    MTRenderPipelineState pipeline,
    MTError *error);

typedef void (*render_pipeline_with_reflection_callback_t)(
    void *userdata,
    MTRenderPipelineState pipeline,
    MTRenderPipelineReflection *reflection,
    MTError *error
);

typedef void (*MTNewRenderPipelineStateCallback)(
    void *userdata,
    MTRenderPipelineState pipelineState,
    MTError error
);

MT_INLINE MTBuffer mt_device_create_buffer_with_bytes(MTDevice device, void* ptr, uintptr_t length, MTResourceOptions options) {
    typedef void* (*MTNewBufferWithBytesMsgSend)(void*, SEL, void*, uintptr_t, MTResourceOptions);
    MTNewBufferWithBytesMsgSend msgSend = (MTNewBufferWithBytesMsgSend)objc_msgSend;
    
    SEL sel = sel_getUid("newBufferWithBytes:length:options:");
    return msgSend(device, sel, ptr, length, options);
}

MT_INLINE MTBuffer mt_device_create_buffer_with_length(
    MTDevice device,
    uintptr_t length,
    MTResourceOptions options
) {
    typedef void* (*MTNewBufferMsgSend)(void*, SEL, uintptr_t, MTResourceOptions);
    MTNewBufferMsgSend msgSend = (MTNewBufferMsgSend)objc_msgSend;
    
    SEL sel = sel_getUid("newBufferWithLength:options:");
    return msgSend(device, sel, length, options);
}

MT_INLINE MTIndirectCommandBuffer mt_device_new_indirect_command_buffer(
    MTDevice device,
    MTIndirectCommandBufferDescriptor descriptor,
    unsigned long maxCommandCount,
    MTResourceOptions options
) {
    SEL sel = sel_getUid("newIndirectCommandBufferWithDescriptor:maxCommandCount:options:");
    return ((MTIndirectCommandBuffer(*)(id, SEL, MTIndirectCommandBufferDescriptor, unsigned long, MTResourceOptions))
            objc_msgSend)(device, sel, descriptor, maxCommandCount, options);
}

MT_INLINE MTRenderPipelineState mt_device_create_render_pipeline_state(
    MTDevice device,
    MTRenderPipelineDescriptor render_desc,
    MTError** error
) {
    typedef void* (*MTNewRenderPipelineStateMsgSend)(
        void*, SEL, MTRenderPipelineDescriptor*, MTError**
    );

    MTNewRenderPipelineStateMsgSend msgSend = (MTNewRenderPipelineStateMsgSend)objc_msgSend;

    SEL sel = sel_getUid("newRenderPipelineStateWithDescriptor:error:");
    return (MTRenderPipelineState*)msgSend(device, sel, render_desc, error);
}

MT_INLINE void mt_device_new_render_pipeline_state_async(
    id device,
    MTRenderPipelineDescriptor descriptor,
    MTNewRenderPipelineStateCallback callback,
    void *userdata
) {
    SEL sel = sel_registerName("newRenderPipelineStateWithDescriptor:completionHandler:");
    typedef void (*MsgSendFn)(id, SEL, MTRenderPipelineDescriptor *, void *);

    // Define the handler block using Clang's block extension
    void (^handler)(MTRenderPipelineState, MTError *) = ^(MTRenderPipelineState pipelineState, MTError *err) {
        callback(userdata, pipelineState, err);
    };

    MsgSendFn fn = (MsgSendFn)objc_msgSend;
    fn(device, sel, descriptor, handler);
}

MT_INLINE id mt_new_render_pipeline_state_with_reflection(
    id device,
    MTRenderPipelineDescriptor desc,
    MTPipelineOption options,
    MTRenderPipelineReflection **out_reflection,
    MTError **out_error
) {
    SEL sel = sel_registerName("newRenderPipelineStateWithDescriptor:options:reflection:error:");
    typedef id (*MsgSendFn)(id, SEL, MTRenderPipelineDescriptor *, MTPipelineOption, MTRenderPipelineReflection **, MTError **);

    MsgSendFn fn = (MsgSendFn)objc_msgSend;
    return fn(device, sel, desc, options, out_reflection, out_error);
}

MT_INLINE void mt_new_render_pipeline_state_with_reflection_async(
    id device,
    MTRenderPipelineDescriptor desc,
    MTPipelineOption options,
    render_pipeline_with_reflection_callback_t callback,
    void *userdata
) {
    SEL sel = sel_registerName("newRenderPipelineStateWithDescriptor:options:completionHandler:");
    typedef void (*MsgSendFn)(
            id,
            SEL,
            MTRenderPipelineDescriptor *,
            MTPipelineOption,
            void (^)(MTRenderPipelineState, MTRenderPipelineReflection, MTError *)
        );

    void (^handler)(MTRenderPipelineState, MTRenderPipelineReflection, MTError *) =
           ^(MTRenderPipelineState pipelineState, MTRenderPipelineReflection pipelineReflection, MTError *error) {
               callback(userdata, pipelineState, pipelineReflection, error);
           };

    MsgSendFn fn = (MsgSendFn)objc_msgSend;
    fn(device, sel, desc, options, handler);
}

MT_INLINE MTTexture mt_device_create_texture_with_descriptor(
    MTDevice device,
    MTTextureDescriptor texture_desc
) {
    typedef void* (*MsgSendFn)(void*, SEL, MTTextureDescriptor*);
    MsgSendFn msgSend = (MsgSendFn)objc_msgSend;
    SEL sel = sel_getUid("newTextureWithDescriptor:");
    return (MTTexture*)msgSend(device, sel, texture_desc);
}

MT_INLINE MTTexture mt_device_create_shared_texture_with_descriptor(
    MTDevice device,
    MTTextureDescriptor texture_desc
) {
    typedef void* (*MsgSendFn)(void*, SEL, MTTextureDescriptor*);
    MsgSendFn msgSend = (MsgSendFn)objc_msgSend;
    SEL sel = sel_getUid("newSharedTextureWithDescriptor:");
    return (MTTexture*)msgSend(device, sel, texture_desc);
}

MT_INLINE MTSamplerState mt_device_create_sampler_state(
    MTDevice device,
    MTSamplerDescriptor sampler_desc
) {
    typedef void* (*MsgSendFn)(void*, SEL, MTSamplerDescriptor*);
    MsgSendFn msgSend = (MsgSendFn)objc_msgSend;
    SEL sel = sel_getUid("newSamplerStateWithDescriptor:");
    return (MTSamplerState*)msgSend(device, sel, sampler_desc);
}

MT_INLINE MTDepthStencilState mt_device_create_depth_stencil_state(
    MTDevice device,
    MTDepthStencilDescriptor desc
) {
    typedef void* (*MsgSendFn)(void*, SEL, MTDepthStencilDescriptor*);
    MsgSendFn msgSend = (MsgSendFn)objc_msgSend;
    SEL sel = sel_getUid("newDepthStencilStateWithDescriptor:");
    return (MTDepthStencilState*)msgSend(device, sel, desc);
}

MT_INLINE MTSizeAndAlign mt_device_heap_texture_size_and_align(MTDevice device, MTTextureDescriptor* desc) {
    typedef MTSizeAndAlign (*HeapTextureSizeAlignFunc)(void*, SEL, void*);
    HeapTextureSizeAlignFunc func = (HeapTextureSizeAlignFunc)objc_msgSend;
    return func(device, sel_getUid("heapTextureSizeAndAlignWithDescriptor:"), desc);
}

MT_INLINE MTSizeAndAlign mt_device_heap_buffer_size_and_align(MTDevice device, NSUInteger length, MTResourceOptions options) {
    typedef MTSizeAndAlign (*HeapBufferSizeAlignFunc)(void*, SEL, NSUInteger, MTResourceOptions);
    HeapBufferSizeAlignFunc func = (HeapBufferSizeAlignFunc)objc_msgSend;
    return func(device, sel_getUid("heapBufferSizeAndAlignWithLength:options:"), length, options);
}

MT_INLINE MTHeap mt_device_create_heap_with_descriptor(MTDevice device, MTHeapDescriptor descriptor) {
    typedef id (*NewHeapFunc)(id, SEL, MTHeapDescriptor);
    NewHeapFunc func = (NewHeapFunc)objc_msgSend;
    return (MTHeap)func((id)device, sel_getUid("newHeapWithDescriptor:"), descriptor);
}

MT_INLINE bool mt_device_supports_family(
    MTDevice device,
    MTGPUFamily gpu_family
) {
    typedef bool (*MsgSendFn)(void*, SEL, MTGPUFamily);
    MsgSendFn msgSend = (MsgSendFn)objc_msgSend;
    SEL sel = sel_getUid("supportsFamily:");
    return msgSend(device, sel, gpu_family);
}

MT_INLINE bool mt_device_supports_texture_sample_count(
    MTDevice device,
    uintptr_t count
) {
    typedef bool (*MsgSendFn)(void*, SEL, uintptr_t);
    MsgSendFn msgSend = (MsgSendFn)objc_msgSend;
    SEL sel = sel_getUid("supportsTextureSampleCount:");
    return msgSend(device, sel, count);
}

MT_INLINE uintptr_t mt_device_max_buffer_length(
    MTDevice device
) {
    typedef uintptr_t (*MsgSendFn)(void*, SEL);
    MsgSendFn msgSend = (MsgSendFn)objc_msgSend;
    SEL sel = sel_getUid("maxBufferLength");
    return msgSend(device, sel);
}

MT_INLINE bool mt_device_supports_counter_sampling(
    MTDevice device,
    MTCounterSamplingPoint sampling_point
) {
    typedef bool (*MsgSendFn)(void*, SEL, MTCounterSamplingPoint);
    MsgSendFn msgSend = (MsgSendFn)objc_msgSend;
    SEL sel = sel_getUid("supportsCounterSampling:");
    return msgSend(device, sel, sampling_point);
}

MT_INLINE bool mt_device_supports_vertex_amplification_count(
    MTDevice device,
    uintptr_t count
) {
    typedef bool (*MsgSendFn)(void*, SEL, uintptr_t);
    MsgSendFn msgSend = (MsgSendFn)objc_msgSend;
    SEL sel = sel_getUid("supportsVertexAmplificationCount:");
    return msgSend(device, sel, count);
}

MT_INLINE bool mt_device_supports_dynamic_libraries(
    MTDevice device
) {
    typedef bool (*MsgSendFn)(void*, SEL);
    MsgSendFn msgSend = (MsgSendFn)objc_msgSend;
    SEL sel = sel_getUid("supportsDynamicLibraries");
    return msgSend(device, sel);
}

MT_INLINE bool mt_device_supports_render_dynamic_libraries(
    MTDevice device
) {
    typedef bool (*MsgSendFn)(void*, SEL);
    MsgSendFn msgSend = (MsgSendFn)objc_msgSend;
    SEL sel = sel_getUid("supportsRenderDynamicLibraries");
    return msgSend(device, sel);
}

MT_INLINE bool mt_device_supports_ray_tracing(
    MTDevice device
) {
    typedef bool (*MsgSendFn)(void*, SEL);
    MsgSendFn msgSend = (MsgSendFn)objc_msgSend;
    SEL sel = sel_getUid("supportsRaytracing");
    return msgSend(device, sel);
}

MT_INLINE bool mt_device_supports_ray_tracing_from_render(
    MTDevice device
) {
    typedef bool (*MsgSendFn)(void*, SEL);
    MsgSendFn msgSend = (MsgSendFn)objc_msgSend;
    SEL sel = sel_getUid("supportsRaytracingFromRender");
    return msgSend(device, sel);
}

MT_INLINE bool mt_device_supports_function_pointers(
    MTDevice device
) {
    typedef bool (*MsgSendFn)(void*, SEL);
    MsgSendFn msgSend = (MsgSendFn)objc_msgSend;
    SEL sel = sel_getUid("supportsFunctionPointers");
    return msgSend(device, sel);
}

MT_INLINE bool mt_device_supports_function_pointers_from_render(
    MTDevice device
) {
    typedef bool (*MsgSendFn)(void*, SEL);
    MsgSendFn msgSend = (MsgSendFn)objc_msgSend;
    SEL sel = sel_getUid("supportsFunctionPointersFromRender");
    return msgSend(device, sel);
}

MT_INLINE bool mt_device_supports_primitive_motion_blur(
    MTDevice device
) {
    typedef bool (*MsgSendFn)(void*, SEL);
    MsgSendFn msgSend = (MsgSendFn)objc_msgSend;
    SEL sel = sel_getUid("supportsPrimitiveMotionBlur");
    return msgSend(device, sel);
}

MT_INLINE uintptr_t mt_device_maximum_concurrent_compilation_task_count(
    MTDevice device
) {
    typedef uintptr_t (*MsgSendFn)(void*, SEL);
    MsgSendFn msgSend = (MsgSendFn)objc_msgSend;
    SEL sel = sel_getUid("maximumConcurrentCompilationTaskCount");
    return msgSend(device, sel);
}

// -- MARK: IO

MT_INLINE MTIOFileHandle mt_device_new_io_file_handle(MTDevice device, MTURL url, MTError* outError) {
    SEL sel = sel_registerName("newIOFileHandleWithURL:error:");
    typedef MTIOFileHandle (*MsgSendType)(id, SEL, MTURL, MTError*);
    return ((MsgSendType)objc_msgSend)(device, sel, url, outError);
}

MT_INLINE MTIOFileHandle mt_device_new_io_file_handle_with_compression(MTDevice device, MTURL url, MTIOCompressionMethod compression, MTError* outError) {
    SEL sel = sel_registerName("newIOFileHandleWithURL:compressionMethod:error:");
    typedef MTIOFileHandle (*MsgSendType)(id, SEL, MTURL, unsigned long, MTError*);
    return ((MsgSendType)objc_msgSend)(device, sel, url, compression, outError);
}

MT_INLINE MTIOCommandQueue mt_device_new_io_command_queue(MTDevice device, MTIOCommandQueueDescriptor desc, MTError* outError) {
    SEL sel = sel_registerName("newIOCommandQueueWithDescriptor:error:");
    typedef MTIOCommandQueue (*MsgSendType)(id, SEL, MTIOCommandQueueDescriptor, MTError*);
    return ((MsgSendType)objc_msgSend)(device, sel, desc, outError);
}

// -- MARK: BinaryArchive
MT_INLINE MTBinaryArchive mt_device_new_binary_archive(MTDevice device, MTBinaryArchiveDescriptor desc, MTError* error_out) {
    SEL sel = sel_getUid("newBinaryArchiveWithDescriptor:error:");
    return (MTBinaryArchive)((id (*)(id, SEL, id, MTError**))objc_msgSend)((id)device, sel, (id)desc, (MTError**)error_out);
}

MT_INLINE MTEvent mt_device_new_event(MTDevice device) {
    if (!device) return NULL;

    SEL sel = sel_getUid("newEvent");
    return ((MTEvent (*)(id, SEL))objc_msgSend)((id)device, sel);
}

MT_INLINE MTSharedEvent mt_device_new_shared_event(MTDevice device) {
    if (!device) return NULL;

    SEL sel = sel_getUid("newSharedEvent");
    return ((MTSharedEvent (*)(id, SEL))objc_msgSend)((id)device, sel);
}

MT_INLINE MTSharedEvent mt_device_new_shared_event_with_handle(MTDevice device, MTSharedEventHandle handle) {
    if (!device || !handle) return NULL;

    SEL sel = sel_getUid("newSharedEventWithHandle:");
    return ((MTSharedEvent (*)(id, SEL, MTSharedEventHandle))objc_msgSend)((id)device, sel, handle);
}
