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

typedef void MTHeapDescriptor;
typedef void MTHeap;

// MARK: Setters

MT_INLINE MTHeapDescriptor* mt_new_heapDescriptor(void) {
    return NSCLASS_ALLOC_INIT("MTLHeapDescriptor");
}

MT_INLINE void mt_heapDescriptor_set_size(MTHeapDescriptor* desc, uintptr_t value) {
    void_ms_send_uint(desc, sel_registerName("setSize:"), value);
}

MT_INLINE void mt_heapDescriptor_set_storageMode(MTHeapDescriptor* desc, MTStorageMode mode) {
    void_ms_send_uint(desc, sel_registerName("setStorageMode:"), mode);
}

MT_INLINE void mt_heapDescriptor_set_cpu_cacheMode(MTHeapDescriptor* desc, MTCPUCacheMode mode) {
    void_ms_send_uint(desc, sel_registerName("setCpuCacheMode:"), mode);
}

MT_INLINE void mt_heapDescriptor_set_sparse_pageSize(MTHeapDescriptor* desc, MTSparsePageSize size) {
    void_ms_send_uint(desc, sel_registerName("setSparsePageSize:"), size);
}

MT_INLINE void mt_heapDescriptor_set_hazard_trackingMode(MTHeapDescriptor* desc, MTHazardTrackingMode mode) {
    void_ms_send_uint(desc, sel_registerName("setHazardTrackingMode:"), mode);
}

MT_INLINE void mt_heapDescriptor_set_resourceOptions(MTHeapDescriptor* desc, MTResourceOptions options) {
    void_ms_send_uint(desc, sel_registerName("setResourceOptions:"), options);
}

MT_INLINE void mt_heapDescriptor_set_heapType(MTHeapDescriptor* desc, MTHeapType type) {
    void_ms_send_uint(desc, sel_registerName("setType:"), type);
}

// MARK: Getters

MT_INLINE uintptr_t mt_heapDescriptor_get_size(MTHeapDescriptor* desc) {
    return ulong_ms_send(desc, sel_registerName("size"));
}

MT_INLINE MTStorageMode mt_heapDescriptor_get_storageMode(MTHeapDescriptor* desc) {
    return (MTStorageMode)ulong_ms_send(desc, sel_registerName("storageMode"));
}

MT_INLINE MTCPUCacheMode mt_heapDescriptor_get_cpu_cacheMode(MTHeapDescriptor* desc) {
    return (MTCPUCacheMode)ulong_ms_send(desc, sel_registerName("cpuCacheMode"));
}

MT_INLINE MTSparsePageSize mt_heapDescriptor_get_sparse_pageSize(MTHeapDescriptor* desc) {
    return (MTSparsePageSize)ulong_ms_send(desc, sel_registerName("sparsePageSize"));
}

MT_INLINE MTHazardTrackingMode mt_heapDescriptor_get_hazard_trackingMode(MTHeapDescriptor* desc) {
    return (MTHazardTrackingMode)ulong_ms_send(desc, sel_registerName("hazardTrackingMode"));
}

MT_INLINE MTResourceOptions mt_heapDescriptor_get_resourceOptions(MTHeapDescriptor* desc) {
    return (MTResourceOptions)ulong_ms_send(desc, sel_registerName("resourceOptions"));
}

MT_INLINE MTHeapType mt_heapDescriptor_get_heapType(MTHeapDescriptor* desc) {
    return (MTHeapType)ulong_ms_send(desc, sel_registerName("type"));
}
