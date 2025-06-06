//
//  MTResource.h
//  Metal C
//
//  Created by Lungile Maseko on 2024/04/29.
//

#pragma once
#include "MTUtils.h"

typedef enum MTPurgeableState {
    MTPurgeableStateKeepCurrent = 1,
    MTPurgeableStateNonVolatile = 2,
    MTPurgeableStateVolatile = 3,
    MTPurgeableStateEmpty = 4,
}MTPurgeableState;

typedef enum MTCPUCacheMode {
    MTCPUCacheModeDefaultCache = 0,
    MTCPUCacheModeWriteCombined = 1,
}MTCPUCacheMode;

typedef enum MTStorageMode {
    MTStorageModeShared = 0,
    MTStorageModeManaged = 1,
    MTStorageModePrivate = 2,
    MTStorageModeMemoryless = 3,
}MTStorageMode;

typedef enum MTHazardTrackingMode {
    MTHazardTrackingModeDefault = 0,
    MTHazardTrackingModeUntracked = 1,
    MTHazardTrackingModeTracked = 2,
}MTHazardTrackingMode;

typedef enum MTResourceOptions : unsigned long {
    MTResourceCPUCacheModeDefaultCache = 0,
    MTResourceCPUCacheModeWriteCombined = 1,
    MTResourceStorageModeShared = 0,
    MTResourceStorageModeManaged = 16,
    MTResourceStorageModePrivate = 32,
    MTResourceStorageModeMemoryless = 48,
    MTResourceHazardTrackingModeDefault = 0,
    MTResourceHazardTrackingModeUntracked = 256,
    MTResourceHazardTrackingModeTracked = 512,
    MTResourceOptionCPUCacheModeDefault = 0, //Deprecated
    MTResourceOptionCPUCacheModeWriteCombined = 1, //Deprecated
}MTResourceOptions;

typedef void* MTResource;
typedef void* MTHeap;
typedef void* MTDevice;

MT_INLINE MTDevice mt_resource_get_device(MTResource resource) {
    return ((id (*)(id, SEL))objc_msgSend)(resource, sel_getUid("device"));
}

MT_INLINE MTCPUCacheMode mt_resource_get_cpu_cache_mode(MTResource resource) {
    return ((MTCPUCacheMode (*)(id, SEL))objc_msgSend)(resource, sel_getUid("cpuCacheMode"));
}

MT_INLINE MTStorageMode mt_resource_get_storage_mode(MTResource resource) {
    return ((MTStorageMode (*)(id, SEL))objc_msgSend)(resource, sel_getUid("storageMode"));
}

MT_INLINE MTHazardTrackingMode mt_resource_get_hazard_tracking_mode(MTResource resource) {
    return ((MTHazardTrackingMode (*)(id, SEL))objc_msgSend)(resource, sel_getUid("hazardTrackingMode"));
}

MT_INLINE MTResourceOptions mt_resource_get_resource_options(MTResource resource) {
    return ((MTResourceOptions (*)(id, SEL))objc_msgSend)(resource, sel_getUid("resourceOptions"));
}

MT_INLINE MTHeap mt_resource_get_heap(MTResource resource) {
    return ((id (*)(id, SEL))objc_msgSend)(resource, sel_getUid("heap"));
}

MT_INLINE unsigned long mt_resource_get_heap_offset(MTResource resource) {
    return ((unsigned long (*)(id, SEL))objc_msgSend)(resource, sel_getUid("heapOffset"));
}

MT_INLINE unsigned long mt_resource_get_allocated_size(MTResource resource) {
    return ((unsigned long (*)(id, SEL))objc_msgSend)(resource, sel_getUid("allocatedSize"));
}
