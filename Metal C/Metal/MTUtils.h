//
//  MTUtils.h
//  Metal C
//
//  Created by Lungile Maseko on 2024/05/29.
//

#pragma once
#include <objc/message.h>

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

typedef void* MTArray;

MT_INLINE void mt_release(void* ptr) {
    SEL releaseSel = sel_registerName("release");
    void (*msgSend)(id, SEL) = (void (*)(id, SEL))objc_msgSend;
    msgSend((id)ptr, releaseSel);
}

MT_INLINE bool mt_is_retained_references(void* ptr) {
    SEL sel = sel_registerName("retainedReferences");
    BOOL (*msgSend)(id, SEL) = (BOOL (*)(id, SEL))objc_msgSend;
    return msgSend((id)ptr, sel);
}

MT_INLINE void mt_set_retained_references(void* ptr) {
    SEL sel = sel_registerName("setRetainedReferences:");
    void (*msgSend)(id, SEL, BOOL) = (void (*)(id, SEL, BOOL))objc_msgSend;
    msgSend((id)ptr, sel, YES);
}

MT_INLINE void* mt_retain(void* obj) {
    if (!obj) return NULL;
    return ((void* (*)(void*, SEL))objc_msgSend)(obj, sel_registerName("retain"));
}

MT_INLINE MTArray mt_array_with_objects(const id* objects, unsigned long count) {
    return ((MTArray (*)(Class, SEL, const id*, unsigned long))objc_msgSend)(
        objc_getClass("NSArray"),
        sel_getUid("arrayWithObjects:count:"),
        objects,
        count
    );
}
