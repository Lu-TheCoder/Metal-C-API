//
//  MTTypes.h
//  Metal C
//
//  Created by Lungile Maseko on 2024/06/03.
//

#pragma once
#include <stdint.h>
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


MT_INLINE MTRegion mtRegionMake2D(NSUInteger x, NSUInteger y, NSUInteger width, NSUInteger height){
    MTRegion region;
    region.origin.x = x; region.origin.y = y; region.origin.z = 0;
    region.size.width = width; region.size.height = height; region.size.depth = 1;
    return region;
}
