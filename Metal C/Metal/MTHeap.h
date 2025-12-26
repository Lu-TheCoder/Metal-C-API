//
//  MTHeap.h
//  Metal C
//
//  Created by Lungile Maseko on 2024/06/05.
//

#pragma once
#include "MTUtils.h"
#include "MTResource.h"

typedef void* MTTextureDescriptor;
typedef void* MTTexture;
typedef void* MTBuffer;

typedef enum MTSparsePageSize {
    MTSparsePageSize16 = 101,
    MTSparsePageSize64 = 102,
    MTSparsePageSize256 = 103,
} MTSparsePageSize;

typedef enum MTHeapType {
    MTHeapTypeAutomatic = 0,
    MTHeapTypePlacement = 1,
    MTHeapTypeSparse = 2,
} MTHeapType;

typedef void* MTHeapDescriptor;
typedef void* MTHeap;

// MARK: Creation

MT_INLINE MTHeapDescriptor mt_heap_descriptor_create(void) {
    return MT_ALLOC_INIT("MTLHeapDescriptor");
}

MT_INLINE MTTexture mt_heap_create_texture_with_descriptor(MTHeap heap, MTTextureDescriptor desc) {
    return MT_MSG_SEND_1(id, heap, MT_SEL("newTextureWithDescriptor:"), id, desc);
}

MT_INLINE MTTexture mt_heap_create_texture_at_offset(MTHeap heap, MTTextureDescriptor desc, uintptr_t offset) {
    return MT_MSG_SEND_2(id, heap, MT_SEL("newTextureWithDescriptor:offset:"), id, desc, uintptr_t, offset);
}

MT_INLINE MTBuffer mt_heap_create_buffer(MTHeap heap, uintptr_t length, MTResourceOptions options) {
    return MT_MSG_SEND_2(id, heap, MT_SEL("newBufferWithLength:options:"), uintptr_t, length, MTResourceOptions, options);
}

MT_INLINE MTBuffer mt_heap_create_buffer_at_offset(MTHeap heap, uintptr_t length, MTResourceOptions options, uintptr_t offset) {
    return MT_MSG_SEND_3(id, heap, MT_SEL("newBufferWithLength:options:offset:"), uintptr_t, length, MTResourceOptions, options, uintptr_t, offset);
}

// MARK: Setters

MT_INLINE void mt_heap_descriptor_set_size(MTHeapDescriptor desc, uintptr_t value) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setSize:"), uintptr_t, value);
}

MT_INLINE void mt_heap_descriptor_set_storageMode(MTHeapDescriptor desc, MTStorageMode mode) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setStorageMode:"), MTStorageMode, mode);
}

MT_INLINE void mt_heap_descriptor_set_cpu_cacheMode(MTHeapDescriptor desc, MTCPUCacheMode mode) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setCpuCacheMode:"), MTCPUCacheMode, mode);
}

MT_INLINE void mt_heap_descriptor_set_sparse_pageSize(MTHeapDescriptor desc, MTSparsePageSize size) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setSparsePageSize:"), MTSparsePageSize, size);
}

MT_INLINE void mt_heap_descriptor_set_hazard_trackingMode(MTHeapDescriptor desc, MTHazardTrackingMode mode) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setHazardTrackingMode:"), MTHazardTrackingMode, mode);
}

MT_INLINE void mt_heap_descriptor_set_resourceOptions(MTHeapDescriptor desc, MTResourceOptions options) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setResourceOptions:"), MTResourceOptions, options);
}

MT_INLINE void mt_heap_descriptor_set_heapType(MTHeapDescriptor desc, MTHeapType type) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setType:"), MTHeapType, type);
}

// MARK: Getters

MT_INLINE uintptr_t mt_heap_descriptor_get_size(MTHeapDescriptor desc) {
    return MT_MSG_SEND(uintptr_t, desc, MT_SEL("size"));
}

MT_INLINE MTStorageMode mt_heap_descriptor_get_storageMode(MTHeapDescriptor desc) {
    return MT_MSG_SEND(MTStorageMode, desc, MT_SEL("storageMode"));
}

MT_INLINE MTCPUCacheMode mt_heap_descriptor_get_cpu_cacheMode(MTHeapDescriptor desc) {
    return MT_MSG_SEND(MTCPUCacheMode, desc, MT_SEL("cpuCacheMode"));
}

MT_INLINE MTSparsePageSize mt_heap_descriptor_get_sparse_pageSize(MTHeapDescriptor desc) {
    return MT_MSG_SEND(MTSparsePageSize, desc, MT_SEL("sparsePageSize"));
}

MT_INLINE MTHazardTrackingMode mt_heap_descriptor_get_hazard_trackingMode(MTHeapDescriptor desc) {
    return MT_MSG_SEND(MTHazardTrackingMode, desc, MT_SEL("hazardTrackingMode"));
}

MT_INLINE MTResourceOptions mt_heap_descriptor_get_resourceOptions(MTHeapDescriptor desc) {
    return MT_MSG_SEND(MTResourceOptions, desc, MT_SEL("resourceOptions"));
}

MT_INLINE MTHeapType mt_heapDescriptor_get_heapType(MTHeapDescriptor desc) {
    return MT_MSG_SEND(MTHeapType, desc, MT_SEL("type"));
}
