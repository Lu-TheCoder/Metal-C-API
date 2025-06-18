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
#include <stdio.h>

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

typedef enum MTTextureSwizzle : uint8_t {
    MTextureSwizzleZero  = 0,
    MTextureSwizzleOne   = 1,
    MTextureSwizzleRed   = 2,
    MTextureSwizzleGreen = 3,
    MTextureSwizzleBlue  = 4,
    MTextureSwizzleAlpha = 5
} MTTextureSwizzle;

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

typedef void* MTSharedTextureHandle;
typedef void* MTTextureDescriptor;

typedef void* MTTexture;

// MARK: MTSharedTexture Handle

MT_INLINE MTSharedTextureHandle mt_texture_new_shared_texture_handle(MTTexture texture) {
    SEL sel = sel_getUid("newSharedTextureHandle");
    typedef id (*NewSharedTextureHandleFunc)(id, SEL);
    NewSharedTextureHandleFunc func = (NewSharedTextureHandleFunc)objc_msgSend;
    return func((id)texture, sel);
}

MT_INLINE MTDevice* mt_sharedTextureHandle_get_device(MTSharedTextureHandle* handle) {
    SEL sel = sel_registerName("device");
    MTDevice* (*msgSend)(id, SEL) = (MTDevice* (*)(id, SEL))objc_msgSend;
    return msgSend((id)handle, sel);
}

// MARK: MTTexureDescriptor

MT_INLINE MTTextureDescriptor* mt_texture_descriptor_create(MTPixelFormat pixel_format, NSUInteger width, NSUInteger height, bool mipmapped) {
    Class descClass = objc_getClass("MTLTextureDescriptor");
    SEL sel = sel_getUid("texture2DDescriptorWithPixelFormat:width:height:mipmapped:");
    
    return ((MTTextureDescriptor* (*)(Class, SEL, MTPixelFormat, NSUInteger, NSUInteger, BOOL))objc_msgSend)(
        descClass, sel, pixel_format, width, height, mipmapped
    );
}

MT_INLINE MTTextureDescriptor mt_texture_cube_descriptor_create(MTPixelFormat pixel_format, NSUInteger size, bool mipmapped) {
    Class descClass = objc_getClass("MTLTextureDescriptor");
    SEL sel = sel_getUid("textureCubeDescriptorWithPixelFormat:size:mipmapped:");
    typedef id (*CubeDescFunc)(Class, SEL, NSUInteger, NSUInteger, BOOL);
    CubeDescFunc func = (CubeDescFunc)objc_msgSend;
    return func(descClass, sel, pixel_format, size, mipmapped);
}

MT_INLINE MTTextureDescriptor mt_texture_buffer_descriptor_create(
    MTPixelFormat pixel_format,
    NSUInteger width,
    MTResourceOptions resource_options,
    MTTextureUsage usage
) {
    Class descClass = objc_getClass("MTLTextureDescriptor");
    SEL sel = sel_getUid("textureBufferDescriptorWithPixelFormat:width:resourceOptions:usage:");
    typedef id (*BufferDescFunc)(Class, SEL, NSUInteger, NSUInteger, NSUInteger, NSUInteger);
    BufferDescFunc func = (BufferDescFunc)objc_msgSend;
    return func(descClass, sel, pixel_format, width, resource_options, usage);
}

MT_INLINE MTTexture mt_texture_new_texture_view_with_format(MTTexture texture, MTPixelFormat pixel_format) {
    typedef id (*NewTextureViewFunc)(id, SEL, MTPixelFormat);
    NewTextureViewFunc func = (NewTextureViewFunc)objc_msgSend;
    return (MTTexture)func((id)texture, sel_getUid("newTextureViewWithPixelFormat:"), pixel_format);
}

//TODO: NOT TESTED
MT_INLINE MTTexture mt_texture_new_texture_view_with_full_desc(
    MTTexture texture,
    MTPixelFormat pixel_format,
    MTTextureType texture_type,
    MTRange levels,
    MTRange slices
) {
    typedef id (*NewTextureViewFullFunc)(id, SEL, MTPixelFormat, MTTextureType, MTRange, MTRange);
    NewTextureViewFullFunc func = (NewTextureViewFullFunc)objc_msgSend;
    return (MTTexture)func((id)texture, sel_getUid("newTextureViewWithPixelFormat:textureType:levels:slices:"), pixel_format, texture_type, levels, slices);
}

MT_INLINE void mt_texture_descriptor_set_texture_type(MTTextureDescriptor desc, MTTextureType type) {
    ((void (*)(id, SEL, NSUInteger))objc_msgSend)(desc, sel_getUid("setTextureType:"), type);
}

MT_INLINE void mt_texture_descriptor_set_pixel_format(MTTextureDescriptor desc, MTPixelFormat type) {
    ((void (*)(id, SEL, NSUInteger))objc_msgSend)(desc, sel_getUid("setPixelFormat:"), type);
}

MT_INLINE void mt_texture_descriptor_set_width(MTTextureDescriptor desc, uintptr_t width) {
    ((void (*)(id, SEL, NSUInteger))objc_msgSend)(desc, sel_getUid("setWidth:"), width);
}

MT_INLINE void mt_texture_descriptor_set_height(MTTextureDescriptor desc, uintptr_t height) {
    ((void (*)(id, SEL, NSUInteger))objc_msgSend)(desc, sel_getUid("setHeight:"), height);
}

MT_INLINE void mt_texture_descriptor_set_depth(MTTextureDescriptor desc, uintptr_t depth) {
    ((void (*)(id, SEL, NSUInteger))objc_msgSend)(desc, sel_getUid("setDepth:"), depth);
}

MT_INLINE void mt_texture_descriptor_set_mipmap_level_count(MTTextureDescriptor desc, uintptr_t count) {
    ((void (*)(id, SEL, NSUInteger))objc_msgSend)(desc, sel_getUid("setMipmapLevelCount:"), count);
}

MT_INLINE void mt_texture_descriptor_set_sample_count(MTTextureDescriptor desc, uintptr_t count) {
    ((void (*)(id, SEL, NSUInteger))objc_msgSend)(desc, sel_getUid("setSampleCount:"), count);
}

MT_INLINE void mt_texture_descriptor_set_array_length(MTTextureDescriptor desc, uintptr_t length) {
    ((void (*)(id, SEL, NSUInteger))objc_msgSend)(desc, sel_getUid("setArrayLength:"), length);
}

MT_INLINE void mt_texture_descriptor_set_resource_options(MTTextureDescriptor desc, MTResourceOptions options) {
    ((void (*)(id, SEL, NSUInteger))objc_msgSend)(desc, sel_getUid("setResourceOptions:"), options);
}

MT_INLINE void mt_texture_descriptor_set_cpu_cache_mode(MTTextureDescriptor desc, MTCPUCacheMode mode) {
    ((void (*)(id, SEL, NSUInteger))objc_msgSend)(desc, sel_getUid("setCpuCacheMode:"), mode);
}

MT_INLINE void mt_texture_descriptor_set_storage_mode(MTTextureDescriptor desc, MTStorageMode mode) {
    ((void (*)(id, SEL, NSUInteger))objc_msgSend)(desc, sel_getUid("setStorageMode:"), mode);
}

MT_INLINE void mt_texture_descriptor_set_hazard_tracking_mode(MTTextureDescriptor desc, MTHazardTrackingMode mode) {
    ((void (*)(id, SEL, NSUInteger))objc_msgSend)(desc, sel_getUid("setHazardTrackingMode:"), mode);
}

MT_INLINE void mt_texture_descriptor_set_usage(MTTextureDescriptor desc, MTTextureUsage usage) {
    ((void (*)(id, SEL, NSUInteger))objc_msgSend)(desc, sel_getUid("setUsage:"), usage);
}

MT_INLINE void mt_texture_descriptor_set_allow_gpu_optimised_contents(MTTextureDescriptor desc, bool is_allowed) {
    ((void (*)(id, SEL, BOOL))objc_msgSend)(desc, sel_getUid("setAllowGPUOptimizedContents:"), is_allowed);
}

MT_INLINE void mt_texture_descriptor_set_compression_type(MTTextureDescriptor desc, MTTextureCompressionType type) {
    ((void (*)(id, SEL, NSUInteger))objc_msgSend)(desc, sel_getUid("setCompressionType:"), type);
}
// TODO: incomplete


// MARK: MTTexture

MT_INLINE void mt_texture_replace_region(
    void* texture,
    MTRegion region,
    uintptr_t mipmap_level,
    const void* bytes,
    uintptr_t bytes_per_row
) {
    SEL sel = sel_getUid("replaceRegion:mipmapLevel:withBytes:bytesPerRow:");
    ((void (*)(id, SEL, MTRegion, uintptr_t, const void*, uintptr_t))objc_msgSend)(
        texture, sel, region, mipmap_level, bytes, bytes_per_row
    );
}

MT_INLINE void mt_texture_replace_region_with_bytes_and_slice(
    MTTexture texture,
    MTRegion region,
    uintptr_t mipmap_level,
    uintptr_t slice,
    const void* bytes,
    uintptr_t bytes_per_row
) {
    SEL sel = sel_getUid("replaceRegion:mipmapLevel:slice:withBytes:bytesPerRow:bytesPerImage:");
    ((void (*)(id, SEL, MTRegion, uintptr_t, uintptr_t, const void*, uintptr_t, uintptr_t))objc_msgSend)(
        texture, sel, region, mipmap_level, slice, bytes, bytes_per_row, 0
    );
}

// MARK: MTTexture Getters

MT_INLINE uintptr_t mt_texture_get_width(MTTexture texture) {
    return ((uintptr_t (*)(id, SEL))objc_msgSend)(texture, sel_getUid("width"));
}

MT_INLINE uintptr_t mt_texture_get_height(MTTexture texture) {
    return ((uintptr_t (*)(id, SEL))objc_msgSend)(texture, sel_getUid("height"));
}

MT_INLINE uintptr_t mt_texture_get_depth(MTTexture texture) {
    return ((uintptr_t (*)(id, SEL))objc_msgSend)(texture, sel_getUid("depth"));
}

MT_INLINE uintptr_t mt_texture_get_mipmap_level_count(MTTexture texture) {
    return ((uintptr_t (*)(id, SEL))objc_msgSend)(texture, sel_getUid("mipmapLevelCount"));
}

MT_INLINE uintptr_t mt_texture_get_sample_count(MTTexture texture) {
    return ((uintptr_t (*)(id, SEL))objc_msgSend)(texture, sel_getUid("sampleCount"));
}

MT_INLINE uintptr_t mt_texture_get_array_length(MTTexture texture) {
    return ((uintptr_t (*)(id, SEL))objc_msgSend)(texture, sel_getUid("arrayLength"));
}

MT_INLINE MTTextureUsage mt_texture_get_usage(MTTexture texture) {
    return (MTTextureUsage)((uintptr_t (*)(id, SEL))objc_msgSend)(texture, sel_getUid("usage"));
}

MT_INLINE bool mt_texture_is_shareable(MTTexture texture) {
    return ((bool (*)(id, SEL))objc_msgSend)(texture, sel_getUid("isShareable"));
}

MT_INLINE bool mt_texture_is_frame_buffer_only(MTTexture texture) {
    return ((bool (*)(id, SEL))objc_msgSend)(texture, sel_getUid("isFramebufferOnly"));
}

MT_INLINE bool mt_texture_is_sparse(MTTexture texture) {
    return ((bool (*)(id, SEL))objc_msgSend)(texture, sel_getUid("isSparse"));
}

MT_INLINE bool mt_texture_is_aliasable(MTTexture texture) {
    return ((bool (*)(id, SEL))objc_msgSend)(texture, sel_getUid("isAliasable"));
}

MT_INLINE bool mt_texture_allows_gpu_optimised_contents(MTTexture texture) {
    return ((bool (*)(id, SEL))objc_msgSend)(texture, sel_getUid("allowGPUOptimizedContents"));
}

MT_INLINE MTTextureCompressionType mt_texture_get_compression_type(MTTexture texture) {
    return (MTTextureCompressionType)((uintptr_t (*)(id, SEL))objc_msgSend)(texture, sel_getUid("compressionType"));
}

MT_INLINE MTResourceID mt_texture_get_gpu_resource_id(MTTexture texture) {
    typedef MTResourceID (*ResourceIDGetterFunc)(id, SEL);
    ResourceIDGetterFunc getter = (ResourceIDGetterFunc)objc_msgSend;
    return getter(texture, sel_getUid("gpuResourceID"));
}

MT_INLINE MTTexture* mt_texture_get_remote_storage_texture(MTTexture* texture) {
    SEL sel = sel_registerName("remoteStorageTexture");
    MTTexture* (*msgSend)(id, SEL) = (MTTexture* (*)(id, SEL))objc_msgSend;
    return msgSend((id)texture, sel);
}

MT_INLINE MTLTextureSwizzleChannels mt_texture_get_swizzle_channels(MTTexture texture) {
    typedef MTLTextureSwizzleChannels (*SwizzleGetterFunc)(id, SEL);
    SwizzleGetterFunc getter = (SwizzleGetterFunc)objc_msgSend;
    return getter((id)texture, sel_getUid("swizzle"));
}

MT_INLINE MTDevice* mt_texture_get_device(MTTexture* texture) {
    SEL sel = sel_registerName("device");
    MTDevice* (*msgSend)(id, SEL) = (MTDevice* (*)(id, SEL))objc_msgSend;
    return msgSend((id)texture, sel);
}

MT_INLINE MTCPUCacheMode mt_texture_get_cpu_cache_mode(MTTexture texture) {
    return (MTCPUCacheMode)((uintptr_t (*)(id, SEL))objc_msgSend)(texture, sel_getUid("cpuCacheMode"));
}

MT_INLINE MTStorageMode mt_texture_get_storage_mode(MTTexture texture) {
    return (MTStorageMode)((uintptr_t (*)(id, SEL))objc_msgSend)(texture, sel_getUid("storageMode"));
}

MT_INLINE MTHazardTrackingMode mt_texture_get_hazard_tracking_mode(MTTexture texture) {
    return (MTHazardTrackingMode)((uintptr_t (*)(id, SEL))objc_msgSend)(texture, sel_getUid("hazardTrackingMode"));
}

MT_INLINE MTResourceOptions mt_texture_get_resourceOptions(MTTexture texture) {
    return (MTResourceOptions)((uintptr_t (*)(id, SEL))objc_msgSend)(texture, sel_getUid("resourceOptions"));
}

MT_INLINE MTHeap* mt_texture_get_heap(MTTexture texture) {
    typedef MTHeap* (*HeapGetterFunc)(id, SEL);
    HeapGetterFunc getter = (HeapGetterFunc)objc_msgSend;
    return getter(texture, sel_getUid("heap"));
}

MT_INLINE uintptr_t mt_texture_get_heapOffset(MTTexture texture) {
    return ((uintptr_t (*)(id, SEL))objc_msgSend)(texture, sel_getUid("heapOffset"));
}

MT_INLINE uintptr_t mt_texture_get_allocatedSize(MTTexture texture) {
    return ((uintptr_t (*)(id, SEL))objc_msgSend)(texture, sel_getUid("allocatedSize"));
}

MT_INLINE uintptr_t mt_texture_get_buffer_bytes_per_row(MTTexture texture) {
    return ((uintptr_t (*)(id, SEL))objc_msgSend)(texture, sel_getUid("bufferBytesPerRow"));
}

MT_INLINE uintptr_t mt_texture_get_buffer_offset(MTTexture texture) {
    return ((uintptr_t (*)(id, SEL))objc_msgSend)(texture, sel_getUid("bufferOffset"));
}
// TODO incomplete
