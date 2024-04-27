//
//  NSAutoreleasePool.h
//  Metal C
//
//  Created by Lungile Maseko on 2024/05/28.
//

#pragma once
#include <objc/runtime.h>
#include "../../ObjectiveCCore/Objectivec.h"

typedef void* MTAutoreleasePool;

void* (*_initPool)(void*, SEL) = (void* (*)(void*, SEL)) objc_msgSend;

MTAutoreleasePool* mt_autoreleasepool_new(void) {
    Class nsautoreleasepool = objc_getClass("NSAutoreleasePool");
    return (void*)class_createInstance(nsautoreleasepool, 0);
//    return (MTCommandQueue*)ms_send(device, sel_getUid("newCommandQueue"));
}

void mt_autoreleasepool_init(MTAutoreleasePool* pool){
    SEL initSel = sel_registerName("init");
    pool = _initPool(pool, initSel);
}

void mt_autoreleasepool_drain(MTAutoreleasePool* pool){
    SEL initSel = sel_registerName("drain");
    _initPool(pool, initSel);
}

void mt_autoreleasepool_release(MTAutoreleasePool* pool){
    SEL initSel = sel_registerName("release");
    _initPool(pool, initSel);
}


