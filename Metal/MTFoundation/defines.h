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
#include <os/availability.h>  // API_AVAILABLE / API_UNAVAILABLE used in enum declarations
#include <stdbool.h>
#include "../MTForwardDecls.h"  // opaque handle typedefs (MTBuffer, MTTexture, ...)

// BOOL compatibility
#ifndef BOOL
#define BOOL bool
#endif

#define MT_INLINE static __attribute__((always_inline)) inline

// ============================================================================
// Null-handle contract
// ============================================================================
//
// Like Metal (and Vulkan) themselves, this wrapper does NOT validate handles —
// passing an invalid/NULL handle is the caller's responsibility. The rules:
//
//   * Functions returning a handle, scalar, or pointer are SAFE to call with a
//     NULL handle: objc messaging to nil returns 0 / nil, so you get NULL / 0
//     back. (A handful of helpers also null-check explicitly.)
//
//   * Functions that return a C STRUCT by value (e.g. MTSizeAndAlign,
//     MTResourceID, MTClearColor) are NOT safe on a NULL handle — messaging nil
//     for a struct return is UNDEFINED on ARM64 (you get garbage, not zero).
//     Only call these with a valid handle.
//
//   * void / setter functions on a NULL handle are a no-op (message to nil),
//     but treat that as a bug, not a feature.
//
// In short: don't pass NULL handles. Check the result of creation functions
// (most take an MTError* out-param) before using what they return.
// ============================================================================

// ============================================================================
// Type-safe objc_msgSend helpers for ARM64 compatibility
// Apple Silicon requires explicit function pointer casts for objc_msgSend
// ============================================================================

// Selector and Class helpers using static caching for performance
#define MT_SEL(name) ({ \
    static SEL _sel = NULL; \
    if (__builtin_expect(!_sel, 0)) _sel = sel_getUid(name); \
    _sel; \
})
#define MT_CLASS(name) ({ \
    static Class _cls = NULL; \
    if (__builtin_expect(!_cls, 0)) _cls = objc_getClass(name); \
    _cls; \
})

// No-arg: id result = MT_MSG_SEND(void*, obj, sel);
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
    MT_MSG_SEND(void*, MT_MSG_SEND_CLASS(void*, MT_CLASS(className), MT_SEL("alloc")), MT_SEL("init"))

// Release
#define MT_RELEASE(obj) MT_MSG_SEND(void, obj, MT_SEL("release"))

// Retain
#define MT_RETAIN(obj) MT_MSG_SEND(void*, obj, MT_SEL("retain"))
