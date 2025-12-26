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
