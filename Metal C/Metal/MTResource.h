//
//  MTResource.h
//  Metal C
//
//  Created by Lungile Maseko on 2024/04/29.
//

#pragma once

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

typedef enum MTResourceOptions {
    MTResourceCPUCacheModeDefaultCache = 0,
    MTResourceCPUCacheModeWriteCombined = 1,
    MTResourceStorageModeShared = 0,
    MTResourceStorageModeManaged = 16,
    MTResourceStorageModePrivate = 32,
    MTResourceStorageModeMemoryless = 48,
    MTResourceHazardTrackingModeDefault = 0,
    MTResourceHazardTrackingModeUntracked = 256,
    MTResourceHazardTrackingModeTracked = 512,
    MTResourceOptionCPUCacheModeDefault = 0,
    MTResourceOptionCPUCacheModeWriteCombined = 1,
}MTResourceOptions;
