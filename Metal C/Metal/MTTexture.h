//
//  MTTexture.h
//  Metal C
//
//  Created by Lungile Maseko on 2024/05/29.
//

#pragma once
#include "MTTypes.h"
#include "MTUtils.h"
#include "MTResource.h"
#include <stdio.h>

typedef enum MTTextureType {
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
} MTTextureType;

typedef enum MTTextureSwizzle : uint8_t {
    MTextureSwizzleZero  = 0,
    MTextureSwizzleOne   = 1,
    MTextureSwizzleRed   = 2,
    MTextureSwizzleGreen = 3,
    MTextureSwizzleBlue  = 4,
    MTextureSwizzleAlpha = 5
} MTTextureSwizzle;

typedef enum MTTextureUsage {
    MTTextureUsageUnknown = 0,
    MTTextureUsageShaderRead = 1,
    MTTextureUsageShaderWrite = 2,
    MTTextureUsageRenderTarget = 4,
    MTTextureUsagePixelFormatView = 16,
    MTTextureUsageShaderAtomic = 32,
} MTTextureUsage;

typedef enum MTTextureCompressionType {
    MTTextureCompressionTypeLossless = 0,
    MTTextureCompressionTypeLossy = 1,
} MTTextureCompressionType;

typedef struct MTLTextureSwizzleChannels {
    MTTextureSwizzle red;
    MTTextureSwizzle green;
    MTTextureSwizzle blue;
    MTTextureSwizzle alpha;
} MTLTextureSwizzleChannels;

typedef void* MTSharedTextureHandle;
typedef void* MTTextureDescriptor;
typedef void* MTTexture;
typedef void* MTHeap;
typedef void* MTDevice;

// MARK: MTSharedTexture Handle

MT_INLINE MTSharedTextureHandle mt_texture_new_shared_texture_handle(MTTexture texture) {
    return MT_MSG_SEND(id, texture, MT_SEL("newSharedTextureHandle"));
}

MT_INLINE MTDevice* mt_sharedTextureHandle_get_device(MTSharedTextureHandle* handle) {
    return MT_MSG_SEND(MTDevice*, handle, MT_SEL("device"));
}

// MARK: MTTextureDescriptor

MT_INLINE MTTextureDescriptor mt_texture_descriptor_create(MTPixelFormat pixel_format, NSUInteger width, NSUInteger height, bool mipmapped) {
    // 4-arg class method - needs explicit cast
    return ((id (*)(Class, SEL, MTPixelFormat, NSUInteger, NSUInteger, BOOL))objc_msgSend)(
        MT_CLASS("MTLTextureDescriptor"), MT_SEL("texture2DDescriptorWithPixelFormat:width:height:mipmapped:"),
        pixel_format, width, height, mipmapped);
}

MT_INLINE MTTextureDescriptor mt_texture_cube_descriptor_create(MTPixelFormat pixel_format, NSUInteger size, bool mipmapped) {
    return ((id (*)(Class, SEL, MTPixelFormat, NSUInteger, BOOL))objc_msgSend)(MT_CLASS("MTLTextureDescriptor"), MT_SEL("textureCubeDescriptorWithPixelFormat:size:mipmapped:"), pixel_format, size, mipmapped);
}

MT_INLINE MTTextureDescriptor mt_texture_buffer_descriptor_create(MTPixelFormat pixel_format, NSUInteger width, MTResourceOptions resource_options, MTTextureUsage usage) {
    return ((id (*)(Class, SEL, MTPixelFormat, NSUInteger, MTResourceOptions, MTTextureUsage))objc_msgSend)(MT_CLASS("MTLTextureDescriptor"), MT_SEL("textureBufferDescriptorWithPixelFormat:width:resourceOptions:usage:"), pixel_format, width, resource_options, usage);
}

MT_INLINE MTTexture mt_texture_new_texture_view_with_format(MTTexture texture, MTPixelFormat pixel_format) {
    return MT_MSG_SEND_1(id, texture, MT_SEL("newTextureViewWithPixelFormat:"), MTPixelFormat, pixel_format);
}

MT_INLINE MTTexture mt_texture_new_texture_view_with_full_desc(MTTexture texture, MTPixelFormat pixel_format, MTTextureType texture_type, MTRange levels, MTRange slices) {
    return ((id (*)(id, SEL, MTPixelFormat, MTTextureType, MTRange, MTRange))objc_msgSend)((id)texture, MT_SEL("newTextureViewWithPixelFormat:textureType:levels:slices:"), pixel_format, texture_type, levels, slices);
}

MT_INLINE void mt_texture_descriptor_set_texture_type(MTTextureDescriptor desc, MTTextureType type) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setTextureType:"), NSUInteger, type);
}

MT_INLINE void mt_texture_descriptor_set_pixel_format(MTTextureDescriptor desc, MTPixelFormat type) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setPixelFormat:"), NSUInteger, type);
}

MT_INLINE void mt_texture_descriptor_set_width(MTTextureDescriptor desc, uintptr_t width) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setWidth:"), NSUInteger, width);
}

MT_INLINE void mt_texture_descriptor_set_height(MTTextureDescriptor desc, uintptr_t height) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setHeight:"), NSUInteger, height);
}

MT_INLINE void mt_texture_descriptor_set_depth(MTTextureDescriptor desc, uintptr_t depth) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setDepth:"), NSUInteger, depth);
}

MT_INLINE void mt_texture_descriptor_set_mipmap_level_count(MTTextureDescriptor desc, uintptr_t count) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setMipmapLevelCount:"), NSUInteger, count);
}

MT_INLINE void mt_texture_descriptor_set_sample_count(MTTextureDescriptor desc, uintptr_t count) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setSampleCount:"), NSUInteger, count);
}

MT_INLINE void mt_texture_descriptor_set_array_length(MTTextureDescriptor desc, uintptr_t length) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setArrayLength:"), NSUInteger, length);
}

MT_INLINE void mt_texture_descriptor_set_resource_options(MTTextureDescriptor desc, MTResourceOptions options) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setResourceOptions:"), NSUInteger, options);
}

MT_INLINE void mt_texture_descriptor_set_cpu_cache_mode(MTTextureDescriptor desc, MTCPUCacheMode mode) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setCpuCacheMode:"), NSUInteger, mode);
}

MT_INLINE void mt_texture_descriptor_set_storage_mode(MTTextureDescriptor desc, MTStorageMode mode) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setStorageMode:"), NSUInteger, mode);
}

MT_INLINE void mt_texture_descriptor_set_hazard_tracking_mode(MTTextureDescriptor desc, MTHazardTrackingMode mode) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setHazardTrackingMode:"), NSUInteger, mode);
}

MT_INLINE void mt_texture_descriptor_set_usage(MTTextureDescriptor desc, MTTextureUsage usage) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setUsage:"), NSUInteger, usage);
}

MT_INLINE void mt_texture_descriptor_set_allow_gpu_optimised_contents(MTTextureDescriptor desc, bool is_allowed) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setAllowGPUOptimizedContents:"), BOOL, is_allowed);
}

MT_INLINE void mt_texture_descriptor_set_compression_type(MTTextureDescriptor desc, MTTextureCompressionType type) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setCompressionType:"), NSUInteger, type);
}

// MARK: MTTexture Operations

// Struct args need explicit casts
MT_INLINE void mt_texture_replace_region(void* texture, MTRegion region, uintptr_t mipmap_level, const void* bytes, uintptr_t bytes_per_row) {
    ((void (*)(id, SEL, MTRegion, uintptr_t, const void*, uintptr_t))objc_msgSend)(
        (id)texture, MT_SEL("replaceRegion:mipmapLevel:withBytes:bytesPerRow:"), region, mipmap_level, bytes, bytes_per_row
    );
}

MT_INLINE void mt_texture_replace_region_with_bytes_and_slice(MTTexture texture, MTRegion region, uintptr_t mipmap_level, uintptr_t slice, const void* bytes, uintptr_t bytes_per_row) {
    ((void (*)(id, SEL, MTRegion, uintptr_t, uintptr_t, const void*, uintptr_t, uintptr_t))objc_msgSend)(
        (id)texture, MT_SEL("replaceRegion:mipmapLevel:slice:withBytes:bytesPerRow:bytesPerImage:"), region, mipmap_level, slice, bytes, bytes_per_row, 0
    );
}

// MARK: MTTexture Getters

MT_INLINE uintptr_t mt_texture_get_width(MTTexture texture) {
    return MT_MSG_SEND(uintptr_t, texture, MT_SEL("width"));
}

MT_INLINE uintptr_t mt_texture_get_height(MTTexture texture) {
    return MT_MSG_SEND(uintptr_t, texture, MT_SEL("height"));
}

MT_INLINE uintptr_t mt_texture_get_depth(MTTexture texture) {
    return MT_MSG_SEND(uintptr_t, texture, MT_SEL("depth"));
}

MT_INLINE uintptr_t mt_texture_get_mipmap_level_count(MTTexture texture) {
    return MT_MSG_SEND(uintptr_t, texture, MT_SEL("mipmapLevelCount"));
}

MT_INLINE uintptr_t mt_texture_get_sample_count(MTTexture texture) {
    return MT_MSG_SEND(uintptr_t, texture, MT_SEL("sampleCount"));
}

MT_INLINE uintptr_t mt_texture_get_array_length(MTTexture texture) {
    return MT_MSG_SEND(uintptr_t, texture, MT_SEL("arrayLength"));
}

MT_INLINE MTTextureUsage mt_texture_get_usage(MTTexture texture) {
    return MT_MSG_SEND(MTTextureUsage, texture, MT_SEL("usage"));
}

MT_INLINE bool mt_texture_is_shareable(MTTexture texture) {
    return MT_MSG_SEND(bool, texture, MT_SEL("isShareable"));
}

MT_INLINE bool mt_texture_is_frame_buffer_only(MTTexture texture) {
    return MT_MSG_SEND(bool, texture, MT_SEL("isFramebufferOnly"));
}

MT_INLINE bool mt_texture_is_sparse(MTTexture texture) {
    return MT_MSG_SEND(bool, texture, MT_SEL("isSparse"));
}

MT_INLINE bool mt_texture_is_aliasable(MTTexture texture) {
    return MT_MSG_SEND(bool, texture, MT_SEL("isAliasable"));
}

MT_INLINE bool mt_texture_allows_gpu_optimised_contents(MTTexture texture) {
    return MT_MSG_SEND(bool, texture, MT_SEL("allowGPUOptimizedContents"));
}

MT_INLINE MTTextureCompressionType mt_texture_get_compression_type(MTTexture texture) {
    return MT_MSG_SEND(MTTextureCompressionType, texture, MT_SEL("compressionType"));
}

// Struct returns need explicit casts
MT_INLINE MTResourceID mt_texture_get_gpu_resource_id(MTTexture texture) {
    return ((MTResourceID (*)(id, SEL))objc_msgSend)((id)texture, MT_SEL("gpuResourceID"));
}

MT_INLINE MTTexture* mt_texture_get_remote_storage_texture(MTTexture* texture) {
    return MT_MSG_SEND(MTTexture*, texture, MT_SEL("remoteStorageTexture"));
}

MT_INLINE MTLTextureSwizzleChannels mt_texture_get_swizzle_channels(MTTexture texture) {
    return ((MTLTextureSwizzleChannels (*)(id, SEL))objc_msgSend)((id)texture, MT_SEL("swizzle"));
}

MT_INLINE MTDevice* mt_texture_get_device(MTTexture* texture) {
    return MT_MSG_SEND(MTDevice*, texture, MT_SEL("device"));
}

MT_INLINE MTCPUCacheMode mt_texture_get_cpu_cache_mode(MTTexture texture) {
    return MT_MSG_SEND(MTCPUCacheMode, texture, MT_SEL("cpuCacheMode"));
}

MT_INLINE MTStorageMode mt_texture_get_storage_mode(MTTexture texture) {
    return MT_MSG_SEND(MTStorageMode, texture, MT_SEL("storageMode"));
}

MT_INLINE MTHazardTrackingMode mt_texture_get_hazard_tracking_mode(MTTexture texture) {
    return MT_MSG_SEND(MTHazardTrackingMode, texture, MT_SEL("hazardTrackingMode"));
}

MT_INLINE MTResourceOptions mt_texture_get_resourceOptions(MTTexture texture) {
    return MT_MSG_SEND(MTResourceOptions, texture, MT_SEL("resourceOptions"));
}

MT_INLINE MTHeap* mt_texture_get_heap(MTTexture texture) {
    return MT_MSG_SEND(MTHeap*, texture, MT_SEL("heap"));
}

MT_INLINE uintptr_t mt_texture_get_heapOffset(MTTexture texture) {
    return MT_MSG_SEND(uintptr_t, texture, MT_SEL("heapOffset"));
}

MT_INLINE uintptr_t mt_texture_get_allocatedSize(MTTexture texture) {
    return MT_MSG_SEND(uintptr_t, texture, MT_SEL("allocatedSize"));
}

MT_INLINE uintptr_t mt_texture_get_buffer_bytes_per_row(MTTexture texture) {
    return MT_MSG_SEND(uintptr_t, texture, MT_SEL("bufferBytesPerRow"));
}

MT_INLINE uintptr_t mt_texture_get_buffer_offset(MTTexture texture) {
    return MT_MSG_SEND(uintptr_t, texture, MT_SEL("bufferOffset"));
}
