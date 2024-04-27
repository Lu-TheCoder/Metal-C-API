//
//  MTUtils.h
//  Metal C
//
//  Created by Lungile Maseko on 2024/05/29.
//

#pragma once
#include <objc/message.h>
#include "../ObjectiveCCore/Objectivec.h"

#define MT_INLINE __attribute__((always_inline)) inline
#define MT_PACKED __attribute__((packed))

// Possibly use these MACROS or stick with inline functions for now (Better for Debugging..)
#define NSCLASS_NEW(name) \
({Class cls = objc_getClass(name); \
SEL allocSel = sel_registerName("new"); \
ms_send(cls, allocSel);})

#define NSCLASS_ALLOC_INIT(name) \
({Class cls = objc_getClass(name); \
SEL allocSel = sel_registerName("alloc"); \
void* c = ms_send(cls, allocSel); \
SEL initSel = sel_registerName("init");\
ms_send(c, initSel);})

#define NSCLASS_ALLOC(name) \
({Class cls = objc_getClass(name); \
SEL allocSel = sel_registerName("alloc"); \
ms_send(cls, allocSel);})

#define NSCLASS(name) \
({objc_getClass(name);})

MT_INLINE void mt_release(void* ptr){
    SEL releaseSel = sel_getUid("release");
    ms_send(ptr, releaseSel);
}

MT_INLINE bool mt_is_retained_references(void* ptr){
    SEL retRefSel = sel_getUid("retainedReferences");
    return ms_send(ptr, retRefSel);
}

MT_INLINE void mt_set_retained_references(void* ptr){
    SEL retRefSel = sel_getUid("setRetainedReferences:");
    ms_send_bool(ptr, retRefSel, true);
}

