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

typedef void* (*MsgSendInitFn)(void*, SEL);
typedef void  (*MsgSendVoidFn)(void*, SEL);

static MsgSendInitFn _msgSendInit = (MsgSendInitFn)objc_msgSend;
static MsgSendVoidFn _msgSendVoid = (MsgSendVoidFn)objc_msgSend;

MTAutoreleasePool mt_autoreleasepool_create(void) {
    Class nsAutoreleasePoolClass = objc_getClass("NSAutoreleasePool");
    void* pool = class_createInstance(nsAutoreleasePoolClass, 0);
    SEL initSel = sel_registerName("init");
    pool = _msgSendInit(pool, initSel);
    return pool;
}

void mt_autoreleasepool_drain(MTAutoreleasePool pool) {
    SEL drainSel = sel_registerName("drain");
    _msgSendVoid(pool, drainSel);
}

void mt_autoreleasepool_release(MTAutoreleasePool pool) {
    SEL releaseSel = sel_registerName("release");
    _msgSendVoid(pool, releaseSel);
}

