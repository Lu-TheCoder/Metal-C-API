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

// -------------------
// Setters
// -------------------

MT_INLINE void mt_heap_descriptor_set_size(MTHeapDescriptor desc, uintptr_t value) {
    SEL sel = sel_registerName("setSize:");
    void (*msgSendVoidUInt)(id, SEL, uintptr_t) = (void (*)(id, SEL, uintptr_t))objc_msgSend;
    msgSendVoidUInt((id)desc, sel, value);
}

MT_INLINE void mt_heap_descriptor_set_storageMode(MTHeapDescriptor desc, MTStorageMode mode) {
    SEL sel = sel_registerName("setStorageMode:");
    void (*msgSendVoidUInt)(id, SEL, MTStorageMode) = (void (*)(id, SEL, MTStorageMode))objc_msgSend;
    msgSendVoidUInt((id)desc, sel, mode);
}

MT_INLINE void mt_heap_descriptor_set_cpu_cacheMode(MTHeapDescriptor desc, MTCPUCacheMode mode) {
    SEL sel = sel_registerName("setCpuCacheMode:");
    void (*msgSendVoidUInt)(id, SEL, MTCPUCacheMode) = (void (*)(id, SEL, MTCPUCacheMode))objc_msgSend;
    msgSendVoidUInt((id)desc, sel, mode);
}

MT_INLINE void mt_heap_descriptor_set_sparse_pageSize(MTHeapDescriptor desc, MTSparsePageSize size) {
    SEL sel = sel_registerName("setSparsePageSize:");
    void (*msgSendVoidUInt)(id, SEL, MTSparsePageSize) = (void (*)(id, SEL, MTSparsePageSize))objc_msgSend;
    msgSendVoidUInt((id)desc, sel, size);
}

MT_INLINE void mt_heap_descriptor_set_hazard_trackingMode(MTHeapDescriptor desc, MTHazardTrackingMode mode) {
    SEL sel = sel_registerName("setHazardTrackingMode:");
    void (*msgSendVoidUInt)(id, SEL, MTHazardTrackingMode) = (void (*)(id, SEL, MTHazardTrackingMode))objc_msgSend;
    msgSendVoidUInt((id)desc, sel, mode);
}

MT_INLINE void mt_heap_descriptor_set_resourceOptions(MTHeapDescriptor desc, MTResourceOptions options) {
    SEL sel = sel_registerName("setResourceOptions:");
    void (*msgSendVoidUInt)(id, SEL, MTResourceOptions) = (void (*)(id, SEL, MTResourceOptions))objc_msgSend;
    msgSendVoidUInt((id)desc, sel, options);
}

MT_INLINE void mt_heap_descriptor_set_heapType(MTHeapDescriptor desc, MTHeapType type) {
    SEL sel = sel_registerName("setType:");
    void (*msgSendVoidUInt)(id, SEL, MTHeapType) = (void (*)(id, SEL, MTHeapType))objc_msgSend;
    msgSendVoidUInt((id)desc, sel, type);
}

// -------------------
// Getters
// -------------------

MT_INLINE uintptr_t mt_heap_descriptor_get_size(MTHeapDescriptor desc) {
    SEL sel = sel_registerName("size");
    uintptr_t (*msgSendUInt)(id, SEL) = (uintptr_t (*)(id, SEL))objc_msgSend;
    return msgSendUInt((id)desc, sel);
}

MT_INLINE MTStorageMode mt_heap_descriptor_get_storageMode(MTHeapDescriptor desc) {
    SEL sel = sel_registerName("storageMode");
    MTStorageMode (*msgSendUInt)(id, SEL) = (MTStorageMode (*)(id, SEL))objc_msgSend;
    return msgSendUInt((id)desc, sel);
}

MT_INLINE MTCPUCacheMode mt_heap_descriptor_get_cpu_cacheMode(MTHeapDescriptor desc) {
    SEL sel = sel_registerName("cpuCacheMode");
    MTCPUCacheMode (*msgSendUInt)(id, SEL) = (MTCPUCacheMode (*)(id, SEL))objc_msgSend;
    return msgSendUInt((id)desc, sel);
}

MT_INLINE MTSparsePageSize mt_heap_descriptor_get_sparse_pageSize(MTHeapDescriptor desc) {
    SEL sel = sel_registerName("sparsePageSize");
    MTSparsePageSize (*msgSendUInt)(id, SEL) = (MTSparsePageSize (*)(id, SEL))objc_msgSend;
    return msgSendUInt((id)desc, sel);
}

MT_INLINE MTHazardTrackingMode mt_heap_descriptor_get_hazard_trackingMode(MTHeapDescriptor desc) {
    SEL sel = sel_registerName("hazardTrackingMode");
    MTHazardTrackingMode (*msgSendUInt)(id, SEL) = (MTHazardTrackingMode (*)(id, SEL))objc_msgSend;
    return msgSendUInt((id)desc, sel);
}

MT_INLINE MTResourceOptions mt_heap_descriptor_get_resourceOptions(MTHeapDescriptor desc) {
    SEL sel = sel_registerName("resourceOptions");
    MTResourceOptions (*msgSendUInt)(id, SEL) = (MTResourceOptions (*)(id, SEL))objc_msgSend;
    return msgSendUInt((id)desc, sel);
}

MT_INLINE MTHeapType mt_heapDescriptor_get_heapType(MTHeapDescriptor desc) {
    SEL sel = sel_registerName("type");
    MTHeapType (*msgSendUInt)(id, SEL) = (MTHeapType (*)(id, SEL))objc_msgSend;
    return msgSendUInt((id)desc, sel);
}
