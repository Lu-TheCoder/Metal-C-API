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
    TextureType1D = 0,
    TextureType1DArray = 1,
    TextureType2D = 2,
    TextureType2DArray = 3,
    TextureType2DMultisample = 4,
    TextureTypeCube = 5,
    TextureTypeCubeArray = 6,
    TextureType3D = 7,
    TextureType2DMultisampleArray = 8,
    TextureTypeTextureBuffer = 9,
}MTTextureType;

typedef enum MTTextureSwizzle : uint8_t {
    TextureSwizzleZero  = 0,
    TextureSwizzleOne   = 1,
    TextureSwizzleRed   = 2,
    TextureSwizzleGreen = 3,
    TextureSwizzleBlue  = 4,
    TextureSwizzleAlpha = 5
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

MTDevice* mt_sharedTextureHandle_get_device(MTSharedTextureHandle* handle) {
    return ptr_ms_send(handle, sel_getUid("device"));
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

MT_INLINE void mt_textureDescriptor_set_textureType(MTTextureDescriptor* desc, MTTextureType type) {
    void_ms_send_uint(desc, sel_getUid("setTextureType:"), type);
}

MT_INLINE void mt_textureDescriptor_set_pixelFormat(MTTextureDescriptor* desc, MTPixelFormat type) {
    void_ms_send_uint(desc, sel_getUid("setPixelFormat:"), type);
}

MT_INLINE void mt_textureDescriptor_set_width(MTTextureDescriptor* desc, uintptr_t width) {
    void_ms_send_uint(desc, sel_getUid("setWidth:"), width);
}

MT_INLINE void mt_textureDescriptor_set_height(MTTextureDescriptor* desc, uintptr_t height) {
    void_ms_send_uint(desc, sel_getUid("setHeight:"), height);
}

MT_INLINE void mt_textureDescriptor_set_depth(MTTextureDescriptor* desc, uintptr_t depth) {
    void_ms_send_uint(desc, sel_getUid("setDepth:"), depth);
}

MT_INLINE void mt_textureDescriptor_set_mipmap_levelCount(MTTextureDescriptor* desc, uintptr_t count) {
    void_ms_send_uint(desc, sel_getUid("setMipmapLevelCount:"), count);
}

MT_INLINE void mt_textureDescriptor_set_sampleCount(MTTextureDescriptor* desc, uintptr_t count) {
    void_ms_send_uint(desc, sel_getUid("setSampleCount:"), count);
}

MT_INLINE void mt_textureDescriptor_set_arrayLength(MTTextureDescriptor* desc, uintptr_t length) {
    void_ms_send_uint(desc, sel_getUid("setArrayLength:"), length);
}

MT_INLINE void mt_textureDescriptor_set_resourceOptions(MTTextureDescriptor* desc, MTResourceOptions options) {
    void_ms_send_uint(desc, sel_getUid("setResourceOptions:"), options);
}

MT_INLINE void mt_textureDescriptor_set_cpu_cacheMode(MTTextureDescriptor* desc, MTCPUCacheMode mode) {
    void_ms_send_uint(desc, sel_getUid("setCpuCacheMode:"), mode);
}

MT_INLINE void mt_textureDescriptor_set_storageMode(MTTextureDescriptor* desc, MTStorageMode mode) {
    void_ms_send_uint(desc, sel_getUid("setStorageMode:"), mode);
}

MT_INLINE void mt_textureDescriptor_set_hazard_trackingMode(MTTextureDescriptor* desc, MTHazardTrackingMode mode) {
    void_ms_send_uint(desc, sel_getUid("setHazardTrackingMode:"), mode);
}

MT_INLINE void mt_textureDescriptor_set_usage(MTTextureDescriptor* desc, MTTextureUsage usage) {
    void_ms_send_uint(desc, sel_getUid("setUsage:"), usage);
}

MT_INLINE void mt_textureDescriptor_set_allow_gpu_optimisedContents(MTTextureDescriptor* desc, bool is_allowed) {
    void_ms_send_uint(desc, sel_getUid("setAllowGPUOptimizedContents:"), is_allowed);
}

MT_INLINE void mt_textureDescriptor_set_compressionType(MTTextureDescriptor* desc, MTTextureCompressionType type) {
    void_ms_send_uint(desc, sel_getUid("setCompressionType:"), type);
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

// MARK: MTTexture Getters

MT_INLINE uintptr_t mt_texture_get_width(MTTexture* texture){
    return ulong_ms_send(texture, sel_getUid("width"));
}

MT_INLINE uintptr_t mt_texture_get_height(MTTexture* texture){
    return ulong_ms_send(texture, sel_getUid("height"));
}

MT_INLINE uintptr_t mt_texture_get_depth(MTTexture* texture){
    return ulong_ms_send(texture, sel_getUid("depth"));
}

MT_INLINE uintptr_t mt_texture_get_mipmap_level_count(MTTexture* texture){
    return ulong_ms_send(texture, sel_getUid("mipmapLevelCount"));
}

MT_INLINE uintptr_t mt_texture_get_sample_count(MTTexture* texture){
    return ulong_ms_send(texture, sel_getUid("sampleCount"));
}

MT_INLINE uintptr_t mt_texture_get_array_length(MTTexture* texture){
    return ulong_ms_send(texture, sel_getUid("arrayLength"));
}

MT_INLINE MTTextureUsage mt_texture_get_usage(MTTexture* texture){
    return (MTTextureUsage)ulong_ms_send(texture, sel_getUid("usage"));
}

MT_INLINE bool mt_texture_is_shareable(MTTexture* texture){
    return bool_ms_send(texture, sel_getUid("isShareable"));
}

MT_INLINE bool mt_texture_is_frame_buffer_only(MTTexture* texture){
    return bool_ms_send(texture, sel_getUid("isFramebufferOnly"));
}

MT_INLINE bool mt_texture_is_sparse(MTTexture* texture){
    return bool_ms_send(texture, sel_getUid("isSparse"));
}

MT_INLINE bool mt_texture_is_aliasable(MTTexture* texture) {
    return bool_ms_send(texture, sel_getUid("isAliasable"));
}

MT_INLINE bool mt_texture_allows_gpu_optimised_contents(MTTexture* texture) {
    return bool_ms_send(texture, sel_getUid("allowGPUOptimizedContents"));
}

MT_INLINE MTTextureCompressionType mt_texture_get_compression_type(MTTexture* texture) {
    return (MTTextureCompressionType)ulong_ms_send(texture, sel_getUid("compressionType"));
}

MT_INLINE MTResourceID mt_texture_get_gpu_resource_id(MTTexture texture) {
    typedef MTResourceID (*ResourceIDGetterFunc)(id, SEL);
    ResourceIDGetterFunc getter = (ResourceIDGetterFunc)objc_msgSend;
    return getter(texture, sel_getUid("gpuResourceID"));
}

MT_INLINE MTTexture* mt_texture_get_remote_storage_texture(MTTexture* texture) {
    return ptr_ms_send(texture, sel_getUid("remoteStorageTexture"));
}

MT_INLINE MTLTextureSwizzleChannels mt_texture_get_swizzle_channels(MTTexture texture) {
    typedef MTLTextureSwizzleChannels (*SwizzleGetterFunc)(id, SEL);
    SwizzleGetterFunc getter = (SwizzleGetterFunc)objc_msgSend;
    return getter((id)texture, sel_getUid("swizzle"));
}

MT_INLINE MTDevice* mt_texture_get_device(MTTexture* texture) {
    return ptr_ms_send(texture, sel_getUid("device"));
}

MT_INLINE MTCPUCacheMode mt_texture_get_cpu_cache_mode(MTTexture* texture) {
    return (MTCPUCacheMode)ulong_ms_send(texture, sel_getUid("cpuCacheMode"));
}

MT_INLINE MTStorageMode mt_texture_get_storage_mode(MTTexture* texture) {
    return (MTStorageMode)ulong_ms_send(texture, sel_getUid("storageMode"));
}

MT_INLINE MTHazardTrackingMode mt_texture_get_hazard_tracking_mode(MTTexture* texture) {
    return (MTHazardTrackingMode)ulong_ms_send(texture, sel_getUid("hazardTrackingMode"));
}

MT_INLINE MTResourceOptions mt_texture_get_resourceOptions(MTTexture* texture) {
    return (MTResourceOptions)ulong_ms_send(texture, sel_getUid("resourceOptions"));
}

MT_INLINE MTHeap* mt_texture_get_heap(MTTexture texture) {
    typedef MTHeap* (*HeapGetterFunc)(id, SEL);
    HeapGetterFunc getter = (HeapGetterFunc)objc_msgSend;
    return getter(texture, sel_getUid("heap"));
}

MT_INLINE uintptr_t mt_texture_get_heapOffset(MTTexture* texture) {
    return ulong_ms_send(texture, sel_getUid("heapOffset"));
}

MT_INLINE uintptr_t mt_texture_get_allocatedSize(MTTexture* texture) {
    return ulong_ms_send(texture, sel_getUid("allocatedSize"));
}

MT_INLINE uintptr_t mt_texture_get_buffer_bytes_per_row(MTTexture* texture) {
    return ulong_ms_send(texture, sel_getUid("bufferBytesPerRow"));
}

MT_INLINE uintptr_t mt_texture_get_buffer_offset(MTTexture* texture) {
    return ulong_ms_send(texture, sel_getUid("bufferOffset"));
}
// TODO incomplete
