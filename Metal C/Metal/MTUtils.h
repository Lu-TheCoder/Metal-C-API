//
//  MTUtils.h
//  Metal C
//
//  Created by Lungile Maseko on 2024/05/29.
//

#pragma once
#include "MTFoundation/defines.h"

#define MT_PACKED __attribute__((packed))

// Legacy macros (deprecated - use MT_ALLOC_INIT instead)
#define NSCLASS_NEW(name) MT_MSG_SEND_CLASS(id, MT_CLASS(name), MT_SEL("new"))
#define NSCLASS_ALLOC_INIT(name) MT_ALLOC_INIT(name)
#define NSCLASS_ALLOC(name) MT_MSG_SEND_CLASS(id, MT_CLASS(name), MT_SEL("alloc"))
#define NSCLASS(name) MT_CLASS(name)

MT_INLINE void mt_release(void* ptr) {
    MT_RELEASE(ptr);
}

MT_INLINE bool mt_is_retained_references(void* ptr) {
    return MT_MSG_SEND(BOOL, ptr, MT_SEL("retainedReferences"));
}

MT_INLINE void mt_set_retained_references(void* ptr) {
    MT_MSG_SEND_1(void, ptr, MT_SEL("setRetainedReferences:"), BOOL, YES);
}

MT_INLINE void* mt_retain(void* obj) {
    if (!obj) return NULL;
    return MT_RETAIN(obj);
}
