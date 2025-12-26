//
//  defines.h
//  Metal C
//
//  Created by Lungile Maseko on 2025/06/07.
//
#pragma once

#include <objc/objc.h>
#include <objc/runtime.h>
#include <objc/message.h>
#include <objc/NSObjCRuntime.h>
#include <stdbool.h>

// BOOL compatibility
#ifndef BOOL
#define BOOL bool
#endif

#define MT_INLINE __attribute__((always_inline)) inline

// ============================================================================
// Type-safe objc_msgSend helpers for ARM64 compatibility
// Apple Silicon requires explicit function pointer casts for objc_msgSend
// ============================================================================

// Selector and Class helpers
#define MT_SEL(name) sel_getUid(name)
#define MT_CLASS(name) objc_getClass(name)

// No-arg: id result = MT_MSG_SEND(id, obj, sel);
#define MT_MSG_SEND(RetType, obj, sel) \
    ((RetType (*)(id, SEL))objc_msgSend)((id)(obj), (sel))

// 1-arg: MT_MSG_SEND_1(void, obj, sel, ArgType, arg);
// Note: Arguments are cast to their declared types to handle void* -> id conversions
#define MT_MSG_SEND_1(RetType, obj, sel, T1, a1) \
    ((RetType (*)(id, SEL, T1))objc_msgSend)((id)(obj), (sel), (T1)(a1))

// 2-arg
#define MT_MSG_SEND_2(RetType, obj, sel, T1, a1, T2, a2) \
    ((RetType (*)(id, SEL, T1, T2))objc_msgSend)((id)(obj), (sel), (T1)(a1), (T2)(a2))

// 3-arg
#define MT_MSG_SEND_3(RetType, obj, sel, T1, a1, T2, a2, T3, a3) \
    ((RetType (*)(id, SEL, T1, T2, T3))objc_msgSend)((id)(obj), (sel), (T1)(a1), (T2)(a2), (T3)(a3))

// 4-arg
#define MT_MSG_SEND_4(RetType, obj, sel, T1, a1, T2, a2, T3, a3, T4, a4) \
    ((RetType (*)(id, SEL, T1, T2, T3, T4))objc_msgSend)((id)(obj), (sel), (T1)(a1), (T2)(a2), (T3)(a3), (T4)(a4))

// 5-arg
#define MT_MSG_SEND_5(RetType, obj, sel, T1, a1, T2, a2, T3, a3, T4, a4, T5, a5) \
    ((RetType (*)(id, SEL, T1, T2, T3, T4, T5))objc_msgSend)((id)(obj), (sel), (T1)(a1), (T2)(a2), (T3)(a3), (T4)(a4), (T5)(a5))

// 6-arg
#define MT_MSG_SEND_6(RetType, obj, sel, T1, a1, T2, a2, T3, a3, T4, a4, T5, a5, T6, a6) \
    ((RetType (*)(id, SEL, T1, T2, T3, T4, T5, T6))objc_msgSend)((id)(obj), (sel), (T1)(a1), (T2)(a2), (T3)(a3), (T4)(a4), (T5)(a5), (T6)(a6))

// ============================================================================
// Class method helpers
// ============================================================================

#define MT_MSG_SEND_CLASS(RetType, cls, sel) \
    ((RetType (*)(Class, SEL))objc_msgSend)((cls), (sel))

#define MT_MSG_SEND_CLASS_1(RetType, cls, sel, T1, a1) \
    ((RetType (*)(Class, SEL, T1))objc_msgSend)((cls), (sel), (T1)(a1))

#define MT_MSG_SEND_CLASS_2(RetType, cls, sel, T1, a1, T2, a2) \
    ((RetType (*)(Class, SEL, T1, T2))objc_msgSend)((cls), (sel), (T1)(a1), (T2)(a2))

// ============================================================================
// Common patterns
// ============================================================================

// Alloc + Init pattern: id obj = MT_ALLOC_INIT("NSObject");
#define MT_ALLOC_INIT(className) \
    MT_MSG_SEND(id, MT_MSG_SEND_CLASS(id, MT_CLASS(className), MT_SEL("alloc")), MT_SEL("init"))

// Release
#define MT_RELEASE(obj) MT_MSG_SEND(void, obj, MT_SEL("release"))

// Retain
#define MT_RETAIN(obj) MT_MSG_SEND(id, obj, MT_SEL("retain"))
