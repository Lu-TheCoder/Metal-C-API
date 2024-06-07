//
//  MTTexture.h
//  Metal C
//
//  Created by Lungile Maseko on 2024/05/29.
//

#pragma once
#include <objc/message.h>
#include "MTTypes.h"
#include "MTUtils.h"
#include "MTHeap.h"

typedef enum MTTextureType{
    MTTextureType1D = 0,
    MTTextureType1DArray = 1,
    MTTextureType2D = 2,
    MTTextureType2DArray = 3,
    MTTextureType2DMultisample = 4,
    MTTextureTypeCube = 5,
    MTTextureTypeCubeArray = 6,
    MTTextureType3D = 7,
    MTTextureType2DMultisampleArray = 8,
    MTTextureTypeTextureBuffer = 9,
}MTTextureType;

typedef enum MTTextureSwizzle {
    MTTextureSwizzleZero = 0,
    MTTextureSwizzleOne = 1,
    MTTextureSwizzleRed = 2,
    MTTextureSwizzleGreen = 3,
    MTTextureSwizzleBlue = 4,
    MTTextureSwizzleAlpha = 5,
}MTTextureSwizzle;

typedef enum MTTextureUsage{
    MTTextureUsageUnknown = 0,
    MTTextureUsageShaderRead = 1,
    MTTextureUsageShaderWrite = 2,
    MTTextureUsageRenderTarget = 4,
    MTTextureUsagePixelFormatView = 16,
    MTTextureUsageShaderAtomic = 32,
}MTTextureUsage;

typedef enum MTTextureCompressionType {
    MTTextureCompressionTypeLossless = 0,
    MTTextureCompressionTypeLossy = 1,
}MTTextureCompressionType;

typedef struct MTLTextureSwizzleChannels {
    MTTextureSwizzle red;
    MTTextureSwizzle green;
    MTTextureSwizzle blue;
    MTTextureSwizzle alpha;
}MTLTextureSwizzleChannels;

typedef void MTSharedTextureHandle;
typedef void MTTextureDescriptor;

typedef void MTTexture;

// MARK: MTSharedTexture Handle

MT_INLINE MTSharedTextureHandle* mt_sharedTextureHandle_new(void) {
    return NSCLASS_ALLOC_INIT("MTLSharedTextureHandle");
}

MTDevice* mt_sharedTextureHandle_get_device(MTSharedTextureHandle* handle) {
    return ptr_ms_send(handle, sel_registerName("device"));
}

// MARK: MTTexureDescriptor

MT_INLINE MTTextureDescriptor* mt_textureDescriptor_new(void) {
    return NSCLASS_ALLOC_INIT("MTLTextureDescriptor");
}

void* (*ms_send_uint31bool)(void*, SEL, NSUInteger, NSUInteger, NSUInteger, bool) = (void* (*)(void*, SEL, NSUInteger, NSUInteger, NSUInteger, bool)) objc_msgSend;

MT_INLINE MTTextureDescriptor* mt_textureDescriptor_new_2D_descriptor(MTPixelFormat pixel_format, NSUInteger width, NSUInteger height, bool mipmapped) {
    SEL sel = sel_registerName("texture2DDescriptorWithPixelFormat:width:height:mipmapped:");
    return  ms_send_uint31bool(objc_getClass("MTLTextureDescriptor"), sel, pixel_format, width, height, mipmapped);
}

//MT_INLINE MTTextureDescriptor* mt_textureDescriptor_new_CubeDescriptor(MTPixelFormat pixel_format, NSUInteger width, NSUInteger height, bool mipmapped) {
//    SEL sel = sel_registerName("texture2DDescriptorWithPixelFormat:width:height:mipmapped:");
//    return  ms_send_uint31bool(objc_getClass("MTLTextureDescriptor"), sel, pixel_format, width, height, mipmapped);
//}
//
//MT_INLINE MTTextureDescriptor* mt_textureDescriptor_new_BufferDescriptor(MTPixelFormat pixel_format, NSUInteger width, NSUInteger height, bool mipmapped) {
//    SEL sel = sel_registerName("texture2DDescriptorWithPixelFormat:width:height:mipmapped:");
//    return  ms_send_uint31bool(objc_getClass("MTLTextureDescriptor"), sel, pixel_format, width, height, mipmapped);
//}

void mt_textureDescriptor_set_textureType(MTTextureDescriptor* desc, MTTextureType type) {
    void_ms_send_uint(desc, sel_registerName("setTextureType:"), type);
}

void mt_textureDescriptor_set_pixelFormat(MTTextureDescriptor* desc, MTPixelFormat type) {
    void_ms_send_uint(desc, sel_registerName("setPixelFormat:"), type);
}

void mt_textureDescriptor_set_width(MTTextureDescriptor* desc, uintptr_t width) {
    void_ms_send_uint(desc, sel_registerName("setWidth:"), width);
}

void mt_textureDescriptor_set_height(MTTextureDescriptor* desc, uintptr_t height) {
    void_ms_send_uint(desc, sel_registerName("setHeight:"), height);
}

void mt_textureDescriptor_set_depth(MTTextureDescriptor* desc, uintptr_t depth) {
    void_ms_send_uint(desc, sel_registerName("setDepth:"), depth);
}

void mt_textureDescriptor_set_mipmap_levelCount(MTTextureDescriptor* desc, uintptr_t count) {
    void_ms_send_uint(desc, sel_registerName("setMipmapLevelCount:"), count);
}

void mt_textureDescriptor_set_sampleCount(MTTextureDescriptor* desc, uintptr_t count) {
    void_ms_send_uint(desc, sel_registerName("setSampleCount:"), count);
}

void mt_textureDescriptor_set_arrayLength(MTTextureDescriptor* desc, uintptr_t length) {
    void_ms_send_uint(desc, sel_registerName("setArrayLength:"), length);
}

void mt_textureDescriptor_set_resourceOptions(MTTextureDescriptor* desc, MTResourceOptions options) {
    void_ms_send_uint(desc, sel_registerName("setResourceOptions:"), options);
}

void mt_textureDescriptor_set_cpu_cacheMode(MTTextureDescriptor* desc, MTCPUCacheMode mode) {
    void_ms_send_uint(desc, sel_registerName("setCpuCacheMode:"), mode);
}

void mt_textureDescriptor_set_storageMode(MTTextureDescriptor* desc, MTStorageMode mode) {
    void_ms_send_uint(desc, sel_registerName("setStorageMode:"), mode);
}

void mt_textureDescriptor_set_hazard_trackingMode(MTTextureDescriptor* desc, MTHazardTrackingMode mode) {
    void_ms_send_uint(desc, sel_registerName("setHazardTrackingMode:"), mode);
}

void mt_textureDescriptor_set_usage(MTTextureDescriptor* desc, MTTextureUsage usage) {
    void_ms_send_uint(desc, sel_registerName("setUsage:"), usage);
}

void mt_textureDescriptor_set_allow_gpu_optimisedContents(MTTextureDescriptor* desc, bool is_allowed) {
    void_ms_send_uint(desc, sel_registerName("setAllowGPUOptimizedContents:"), is_allowed);
}

void mt_textureDescriptor_set_compressionType(MTTextureDescriptor* desc, MTTextureCompressionType type) {
    void_ms_send_uint(desc, sel_registerName("setCompressionType:"), type);
}

// TODO: incomplete


// MARK: MTTextureDescriptor Setters

//MT_INLINE void mt_texture_set_storage_mode(MTTexture* texture, MTStorageMode mode){
//    void_ms_send_uint(texture, sel_registerName(""), mode);
//}
//
//MT_INLINE void mt_texture_set_usage(MTTexture* texture, MTTextureUsage mode){
//    void_ms_send_uint(texture, sel_registerName(""), mode);
//}

// MARK: MTTexture

void* (*ms_send_textRegion)(void*, SEL, MTRegion, NSUInteger, void*, NSUInteger) = (void* (*)(void*, SEL, MTRegion, NSUInteger, void*, NSUInteger)) objc_msgSend;

MT_INLINE void mt_texture_replaceRegion(MTTexture* texture, MTRegion region, NSUInteger mipmap_level, void* withBytes, NSUInteger bytes_per_row) {
    SEL sel = sel_registerName("replaceRegion:mipmapLevel:withBytes:bytesPerRow:");
    ms_send_textRegion(texture, sel, region, mipmap_level, withBytes, bytes_per_row);
}

// MARK: MTTexture Getters

MT_INLINE uintptr_t mt_texture_get_width(MTTexture* texture){
    return ulong_ms_send(texture, sel_registerName("width"));
}

MT_INLINE uintptr_t mt_texture_get_height(MTTexture* texture){
    return ulong_ms_send(texture, sel_registerName("height"));
}

MT_INLINE uintptr_t mt_texture_get_depth(MTTexture* texture){
    return ulong_ms_send(texture, sel_registerName("depth"));
}

MT_INLINE uintptr_t mt_texture_get_mipmap_levelCount(MTTexture* texture){
    return ulong_ms_send(texture, sel_registerName("mipmapLevelCount"));
}

MT_INLINE uintptr_t mt_texture_get_sample_count(MTTexture* texture){
    return ulong_ms_send(texture, sel_registerName("sampleCount"));
}

MT_INLINE uintptr_t mt_texture_get_array_length(MTTexture* texture){
    return ulong_ms_send(texture, sel_registerName("arrayLength"));
}

MT_INLINE MTTextureUsage mt_texture_get_usage(MTTexture* texture){
    return (MTTextureUsage)ulong_ms_send(texture, sel_registerName("usage"));
}

MT_INLINE bool mt_texture_is_shareable(MTTexture* texture){
    return bool_ms_send(texture, sel_registerName("isShareable"));
}

MT_INLINE bool mt_texture_is_framebufferOnly(MTTexture* texture){
    return bool_ms_send(texture, sel_registerName("isFramebufferOnly"));
}

MT_INLINE bool mt_texture_is_sparse(MTTexture* texture){
    return bool_ms_send(texture, sel_registerName("isSparse"));
}

MT_INLINE bool mt_texture_is_aliasable(MTTexture* texture) {
    return bool_ms_send(texture, sel_registerName("isAliasable"));
}

MT_INLINE bool mt_texture_allows_gpu_optimisedContents(MTTexture* texture) {
    return bool_ms_send(texture, sel_registerName("allowGPUOptimizedContents"));
}

MT_INLINE MTTextureCompressionType mt_texture_get_compressionType(MTTexture* texture) {
    return (MTTextureCompressionType)ulong_ms_send(texture, sel_registerName("compressionType"));
}

// TODO: refine and test (its a truct not void ptr)
MT_INLINE MTResourceID* mt_texture_get_gpu_resourceID(MTTexture* texture) {
    return ptr_ms_send(texture, sel_registerName("gpuResourceID"));
}

MT_INLINE MTTexture* mt_texture_get_remote_storage_texture(MTTexture* texture) {
    return ptr_ms_send(texture, sel_registerName("remoteStorageTexture"));
}

// TODO: refine and test (its a truct not void ptr)
MT_INLINE MTLTextureSwizzleChannels* mt_texture_get_swizzleChannels(MTTexture* texture) {
    return ptr_ms_send(texture, sel_registerName("swizzle"));
}

MT_INLINE MTDevice* mt_texture_get_device(MTTexture* texture) {
    return ptr_ms_send(texture, sel_registerName("device"));
}

MT_INLINE MTCPUCacheMode mt_texture_get_cpu_cacheMode(MTTexture* texture) {
    return (MTCPUCacheMode)ulong_ms_send(texture, sel_registerName("cpuCacheMode"));
}

MT_INLINE MTStorageMode mt_texture_get_storageMode(MTTexture* texture) {
    return (MTStorageMode)ulong_ms_send(texture, sel_registerName("storageMode"));
}

MT_INLINE MTHazardTrackingMode mt_texture_get_hazardTrackingMode(MTTexture* texture) {
    return (MTHazardTrackingMode)ulong_ms_send(texture, sel_registerName("hazardTrackingMode"));
}

MT_INLINE MTResourceOptions mt_texture_get_resourceOptions(MTTexture* texture) {
    return (MTResourceOptions)ulong_ms_send(texture, sel_registerName("resourceOptions"));
}

MT_INLINE MTHeap* mt_texture_get_heap(MTTexture* texture) {
    return ptr_ms_send(texture, sel_registerName("heap"));
}

MT_INLINE uintptr_t mt_texture_get_heapOffset(MTTexture* texture) {
    return ulong_ms_send(texture, sel_registerName("heapOffset"));
}

MT_INLINE uintptr_t mt_texture_get_allocatedSize(MTTexture* texture) {
    return ulong_ms_send(texture, sel_registerName("allocatedSize"));
}

// TODO incomplete
