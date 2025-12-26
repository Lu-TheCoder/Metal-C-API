//
//  NSAutoreleasePool.h
//  Metal C
//
//  Created by Lungile Maseko on 2024/05/28.
//

#pragma once
#include "defines.h"

typedef void* MTAutoreleasePool;

MT_INLINE MTAutoreleasePool mt_autoreleasepool_create(void) {
    return MT_ALLOC_INIT("NSAutoreleasePool");
}

MT_INLINE void mt_autoreleasepool_drain(MTAutoreleasePool pool) {
    MT_RELEASE(pool);
}

// @autoreleasepool-style block macro for C
// Usage:
//   autoreleasepool {
//       // your code here
//   }
//
// This is equivalent to:
//   MTAutoreleasePool pool = mt_autoreleasepool_create();
//   // your code here
//   mt_autoreleasepool_drain(pool);

#define autoreleasepool \
    for (MTAutoreleasePool _pool_ = mt_autoreleasepool_create(), *_once_ = (void*)1; \
         _once_; \
         mt_autoreleasepool_drain(_pool_), _once_ = NULL)

