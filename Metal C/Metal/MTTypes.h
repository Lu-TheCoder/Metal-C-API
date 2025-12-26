//
//  MTTypes.h
//  Metal C
//
//  Created by Lungile Maseko on 2024/06/03.
//

#pragma once
#include <stdint.h>
#include "MTFoundation/defines.h"

typedef unsigned long NSUInteger;

typedef struct MTOrigin {
    NSUInteger x;
    NSUInteger y;
    NSUInteger z;
}MTOrigin;

typedef struct MTSize {
    NSUInteger width;
    NSUInteger height;
    NSUInteger depth;
}MTSize;

typedef struct MTRegion {
    MTOrigin origin;
    MTSize size;
}MTRegion;

typedef struct MTSamplePosition {
    float x;
    float y;
}MTSamplePosition;

typedef struct MTResourceID {
    uint64_t _impl;
}MTResourceID;

typedef struct {
    uintptr_t location;
    uintptr_t length;
} MTRange;

typedef MTSamplePosition MTCoordinate2D;

MT_INLINE MTOrigin mt_create_origin(uintptr_t x, uintptr_t y, uintptr_t z)
{
    MTOrigin origin = {x, y, z};
    return origin;
}

MT_INLINE MTSize mt_create_size(NSUInteger width, NSUInteger height, NSUInteger depth)
{
    MTSize size = {width, height, depth};
    return size;
}

MT_INLINE MTRegion mt_region_create_1D(uintptr_t x, uintptr_t width) {
    MTRegion region;
    region.origin.x = x; region.origin.y = 0; region.origin.z = 0;
    region.size.width = width; region.size.height = 1; region.size.depth = 1;
    return region;
}

MT_INLINE MTRegion mt_create_2D_region(uintptr_t x, uintptr_t y, uintptr_t width, uintptr_t height){
    MTRegion region;
    region.origin.x = x; region.origin.y = y; region.origin.z = 0;
    region.size.width = width; region.size.height = height; region.size.depth = 1;
    return region;
}

MT_INLINE MTRegion mt_create_3D_region(uintptr_t x, uintptr_t y, uintptr_t z, uintptr_t width, uintptr_t height, uintptr_t depth){
    MTRegion region;
    region.origin.x = x; region.origin.y = y; region.origin.z = z;
    region.size.width = width; region.size.height = height; region.size.depth = depth;
    return region;
}

MT_INLINE MTSamplePosition mt_create_sample_position(float x, float y) {
    MTSamplePosition position = {x, y};
    return position;
}

MT_INLINE MTCoordinate2D mt_create_2D_coordinate(float x, float y)
{
    MTCoordinate2D result = {x, y};
    return result;
}
