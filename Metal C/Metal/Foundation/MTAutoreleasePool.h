//
//  NSAutoreleasePool.h
//  Metal C
//
//  Created by Lungile Maseko on 2024/05/28.
//

#pragma once
#include <objc/runtime.h>
#include "defines.h"

typedef void* MTAutoreleasePool;

MT_INLINE MTAutoreleasePool mt_autoreleasepool_create(void) {
    Class NSAutoreleasePoolClass = objc_getClass("NSAutoreleasePool");

    SEL allocSel = sel_registerName("alloc");
    SEL initSel  = sel_registerName("init");

    id pool = ((id (*)(id, SEL))objc_msgSend)((id)NSAutoreleasePoolClass, allocSel);
    pool = ((id (*)(id, SEL))objc_msgSend)(pool, initSel);

    return (MTAutoreleasePool)pool;
}

MT_INLINE void mt_autoreleasepool_drain(MTAutoreleasePool pool) {
    SEL releaseSel = sel_registerName("release");
    ((void (*)(id, SEL))objc_msgSend)((id)pool, releaseSel);
}
