//
//  MTHeap.h
//  Metal C
//
//  Created by Lungile Maseko on 2024/06/05.
//

#pragma once
#include "MTUtils.h"
#include "MTDevice.h"
#include "MTResource.h"

typedef void* MTTextureDescriptor;
typedef void* MTTexture;
typedef void* MTBuffer;

typedef enum MTSparsePageSize {
    MTSparsePageSize16 = 101,
    MTSparsePageSize64 = 102,
    MTSparsePageSize256 = 103,
}MTSparsePageSize;

typedef enum MTHeapType {
    MTHeapTypeAutomatic = 0,
    MTHeapTypePlacement = 1,
    MTHeapTypeSparse = 2,
}MTHeapType;

typedef void* MTHeapDescriptor;
typedef void* MTHeap;

// MARK: Setters


MT_INLINE MTHeapDescriptor mt_heap_descriptor_create(void) {
    Class descClass = objc_getClass("MTLHeapDescriptor");
    SEL allocSel = sel_getUid("alloc");
    SEL initSel = sel_getUid("init");

    typedef id (*AllocFunc)(Class, SEL);
    typedef id (*InitFunc)(id, SEL);

    AllocFunc allocFunc = (AllocFunc)objc_msgSend;
    InitFunc initFunc = (InitFunc)objc_msgSend;

    id descriptor = allocFunc(descClass, allocSel);
    descriptor = initFunc(descriptor, initSel);

    return (MTHeapDescriptor)descriptor;
}

MT_INLINE MTTexture mt_heap_create_texture_with_descriptor(MTHeap heap, MTTextureDescriptor desc) {
    typedef id (*NewTextureFromHeapFunc)(id, SEL, id);
    NewTextureFromHeapFunc func = (NewTextureFromHeapFunc)objc_msgSend;
    return (MTTexture)func((id)heap, sel_getUid("newTextureWithDescriptor:"), desc);
}

MT_INLINE MTTexture mt_heap_create_texture_at_offset(MTHeap heap, MTTextureDescriptor* desc, uintptr_t offset) {
    SEL sel = sel_getUid("newTextureWithDescriptor:offset:");
    typedef id (*MsgSendFunc)(id, SEL, MTTextureDescriptor*, uintptr_t);
    MsgSendFunc func = (MsgSendFunc)objc_msgSend;
    return (MTTexture)func((id)heap, sel, desc, offset);
}

MT_INLINE MTBuffer mt_heap_create_buffer(MTHeap heap, uintptr_t length, MTResourceOptions options) {
    SEL sel = sel_getUid("newBufferWithLength:options:");
    typedef id (*MsgSendFunc)(id, SEL, uintptr_t, MTResourceOptions);
    MsgSendFunc func = (MsgSendFunc)objc_msgSend;
    return (MTBuffer)func((id)heap, sel, length, options);
}

MT_INLINE MTBuffer mt_heap_create_buffer_at_offset(MTHeap heap, uintptr_t length, MTResourceOptions options, uintptr_t offset) {
    SEL sel = sel_getUid("newBufferWithLength:options:offset:");
    typedef id (*MsgSendFunc)(id, SEL, uintptr_t, MTResourceOptions, uintptr_t);
    MsgSendFunc func = (MsgSendFunc)objc_msgSend;
    return (MTBuffer)func((id)heap, sel, length, options, offset);
}

MT_INLINE void mt_heap_descriptor_set_size(MTHeapDescriptor* desc, uintptr_t value) {
    void_ms_send_uint(desc, sel_getUid("setSize:"), value);
}

MT_INLINE void mt_heap_descriptor_set_storageMode(MTHeapDescriptor* desc, MTStorageMode mode) {
    void_ms_send_uint(desc, sel_getUid("setStorageMode:"), mode);
}

MT_INLINE void mt_heap_descriptor_set_cpu_cacheMode(MTHeapDescriptor* desc, MTCPUCacheMode mode) {
    void_ms_send_uint(desc, sel_getUid("setCpuCacheMode:"), mode);
}

MT_INLINE void mt_heap_descriptor_set_sparse_pageSize(MTHeapDescriptor* desc, MTSparsePageSize size) {
    void_ms_send_uint(desc, sel_getUid("setSparsePageSize:"), size);
}

MT_INLINE void mt_heap_descriptor_set_hazard_trackingMode(MTHeapDescriptor* desc, MTHazardTrackingMode mode) {
    void_ms_send_uint(desc, sel_getUid("setHazardTrackingMode:"), mode);
}

MT_INLINE void mt_heap_descriptor_set_resourceOptions(MTHeapDescriptor* desc, MTResourceOptions options) {
    void_ms_send_uint(desc, sel_getUid("setResourceOptions:"), options);
}

MT_INLINE void mt_heap_descriptor_set_heapType(MTHeapDescriptor* desc, MTHeapType type) {
    void_ms_send_uint(desc, sel_getUid("setType:"), type);
}

// MARK: Getters

MT_INLINE uintptr_t mt_heap_descriptor_get_size(MTHeapDescriptor* desc) {
    return ulong_ms_send(desc, sel_getUid("size"));
}

MT_INLINE MTStorageMode mt_heap_descriptor_get_storageMode(MTHeapDescriptor* desc) {
    return (MTStorageMode)ulong_ms_send(desc, sel_getUid("storageMode"));
}

MT_INLINE MTCPUCacheMode mt_heap_descriptor_get_cpu_cacheMode(MTHeapDescriptor* desc) {
    return (MTCPUCacheMode)ulong_ms_send(desc, sel_getUid("cpuCacheMode"));
}

MT_INLINE MTSparsePageSize mt_heap_descriptor_get_sparse_pageSize(MTHeapDescriptor* desc) {
    return (MTSparsePageSize)ulong_ms_send(desc, sel_getUid("sparsePageSize"));
}

MT_INLINE MTHazardTrackingMode mt_heap_descriptor_get_hazard_trackingMode(MTHeapDescriptor* desc) {
    return (MTHazardTrackingMode)ulong_ms_send(desc, sel_getUid("hazardTrackingMode"));
}

MT_INLINE MTResourceOptions mt_heap_descriptor_get_resourceOptions(MTHeapDescriptor* desc) {
    return (MTResourceOptions)ulong_ms_send(desc, sel_getUid("resourceOptions"));
}

MT_INLINE MTHeapType mt_heapDescriptor_get_heapType(MTHeapDescriptor* desc) {
    return (MTHeapType)ulong_ms_send(desc, sel_getUid("type"));
}
