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
} MTPurgeableState;

typedef enum MTCPUCacheMode {
    MTCPUCacheModeDefaultCache = 0,
    MTCPUCacheModeWriteCombined = 1,
} MTCPUCacheMode;

typedef enum MTStorageMode {
    MTStorageModeShared = 0,
    MTStorageModeManaged = 1,
    MTStorageModePrivate = 2,
    MTStorageModeMemoryless = 3,
} MTStorageMode;

typedef enum MTHazardTrackingMode {
    MTHazardTrackingModeDefault = 0,
    MTHazardTrackingModeUntracked = 1,
    MTHazardTrackingModeTracked = 2,
} MTHazardTrackingMode;

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
} MTResourceOptions;

MT_INLINE MTDevice mt_resource_get_device(MTResource resource) {
    return MT_MSG_SEND(void*, resource, MT_SEL("device"));
}

MT_INLINE MTCPUCacheMode mt_resource_get_cpu_cache_mode(MTResource resource) {
    return MT_MSG_SEND(MTCPUCacheMode, resource, MT_SEL("cpuCacheMode"));
}

MT_INLINE MTStorageMode mt_resource_get_storage_mode(MTResource resource) {
    return MT_MSG_SEND(MTStorageMode, resource, MT_SEL("storageMode"));
}

MT_INLINE MTHazardTrackingMode mt_resource_get_hazard_tracking_mode(MTResource resource) {
    return MT_MSG_SEND(MTHazardTrackingMode, resource, MT_SEL("hazardTrackingMode"));
}

MT_INLINE MTResourceOptions mt_resource_get_resource_options(MTResource resource) {
    return MT_MSG_SEND(MTResourceOptions, resource, MT_SEL("resourceOptions"));
}

MT_INLINE MTHeap mt_resource_get_heap(MTResource resource) {
    return MT_MSG_SEND(void*, resource, MT_SEL("heap"));
}

MT_INLINE unsigned long mt_resource_get_heap_offset(MTResource resource) {
    return MT_MSG_SEND(unsigned long, resource, MT_SEL("heapOffset"));
}

MT_INLINE unsigned long mt_resource_get_allocated_size(MTResource resource) {
    return MT_MSG_SEND(unsigned long, resource, MT_SEL("allocatedSize"));
}

// How a resource is accessed by the GPU — used by encoder useResource: calls
// to make heap / argument-buffer resources resident.
typedef enum MTResourceUsage : unsigned long {
    MTResourceUsageRead   = 1 << 0,
    MTResourceUsageWrite  = 1 << 1,
    MTResourceUsageSample = 1 << 2, // deprecated by Metal; Read covers sampling
} MTResourceUsage;

// Scope for memoryBarrier calls.
typedef enum MTBarrierScope : unsigned long {
    MTBarrierScopeBuffers       = 1 << 0,
    MTBarrierScopeTextures      = 1 << 1,
    MTBarrierScopeRenderTargets = 1 << 2,
} MTBarrierScope;
