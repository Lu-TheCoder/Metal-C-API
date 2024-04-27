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
#include "../ObjectiveCCore/Objectivec.h"
#include "MTResource.h"
#include "MTRenderPipeline.h"
#include "MTTexture.h"
#include "MTSampler.h"
#include "MTDepthStencil.h"

typedef void MTDevice;

extern MTDevice* MTLCreateSystemDefaultDevice(void);

typedef enum MTCompressionMethod
{
    MTCompressionMethod_ZLib = 0,
    MTCompressionMethod_LZFSE = 1,
    MTCompressionMethod_LZ4 = 2,
    MTCompressionMethod_LZMA = 3,
    MTCompressionMethod_Bitmap = 4,
}MTCompressionMethod;

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
    uintptr_t accelerationStructureSize;
    uintptr_t buildScratchBufferSize;
    uintptr_t refitScratchBufferSize;
}MTAccelerationStructureSizes;

typedef enum MTCounterSamplingPoint {
    MTCounterSamplingPointAtStageBoundary = 0,
    MTCounterSamplingPointAtDrawBoundary = 1,
    MTCounterSamplingPointAtDispatchBoundary = 2,
    MTCounterSamplingPointAtTileDispatchBoundary = 3,
    MTCounterSamplingPointAtBlitBoundary = 4,
}MTCounterSamplingPoint;

typedef struct MTSizeAndAlign {
    uintptr_t size;
    uintptr_t align;
}MTSizeAndAlign;

//FIXME: Not Completed..
typedef struct MTArgumentDescriptor{
    void (*alloc)(void);
    void (*init)(void);

}MTArgumentDescriptor;

MTDevice* mt_create_system_default_device(void){
    return (MTDevice*) MTLCreateSystemDefaultDevice();
}

const char* mt_device_Name(MTDevice* device){
   return ns_toString(ns_mtDeviceName(device));
}

typedef void MTBuffer;

void* (*ms_send_buff_bytes)(void*, SEL, void*, uintptr_t, MTResourceOptions) = (void* (*)(void*, SEL, void*, uintptr_t, MTResourceOptions)) objc_msgSend;

MT_INLINE MTBuffer* mt_device_buffer_new_buffer_with_bytes(MTDevice* device, void* ptr, uintptr_t length, MTResourceOptions options){
    SEL sel = sel_registerName("newBufferWithBytes:length:options:");
    return ms_send_buff_bytes(device, sel, ptr, length, options);
}

void* (*ms_send_buff_length)(void*, SEL, uintptr_t, MTResourceOptions) = (void* (*)(void*, SEL, uintptr_t, MTResourceOptions)) objc_msgSend;

MT_INLINE MTBuffer* mt_device_buffer_new_buffer_with_length(MTDevice* device, uintptr_t length, MTResourceOptions options){
    SEL sel = sel_registerName("newBufferWithLength:options:");
    return ms_send_buff_length(device, sel, length, options);
}

void* (*ms_send_void2)(void*, SEL, MTRenderPipelineDescriptor*, MTError*) = (void* (*)(void*, SEL, MTRenderPipelineDescriptor*, MTError*)) objc_msgSend;

MT_INLINE MTRenderPipelineState* mt_device_renderPipeline_state_new(MTDevice* device, MTRenderPipelineDescriptor* render_desc, MTError** error){
    SEL sel = sel_registerName("newRenderPipelineStateWithDescriptor:error:");
    
    // Ensure the ms_send_void2 function pointer is cast to the correct type
    void* (*objc_msgSendTyped)(void*, SEL, MTRenderPipelineDescriptor*, MTError*) = (void* (*)(void*, SEL, MTRenderPipelineDescriptor*, MTError*))objc_msgSend;

    // Call the method
    return (void*)objc_msgSendTyped(device, sel, render_desc, error);
}

MT_INLINE MTTexture* mt_device_texture_new_texture_with_descriptor(MTDevice* device, MTTextureDescriptor* texture_desc) {
   return ms_send_void(device, sel_registerName("newTextureWithDescriptor:"), texture_desc);
}

MT_INLINE MTSamplerState* mt_device_sampler_state_new(MTDevice* device, MTSamplerDescriptor* sampler_desc) {
    return ms_send_void(device, sel_registerName("newSamplerStateWithDescriptor:"), sampler_desc);
}

MT_INLINE MTDepthStencilState* mt_device_depth_stencil_sate_new(MTDevice* device, MTDepthStencilDescriptor* desc) {
    return ptr_ms_send_ptr(device, sel_registerName("newDepthStencilStateWithDescriptor:"), desc);
}
