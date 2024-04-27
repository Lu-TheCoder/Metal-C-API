//
//  Objectivec.h
//  Metal C
//
//  Created by Lungile Maseko on 2024/04/29.
//
#pragma once
#include <objc/message.h>

union _Vector4
{
    struct { float x, y, z, w; };
    struct { float r, g, b, a; };
    struct { float s, t, p, q; };
    float v[4];
} __attribute__((aligned(16)));

typedef union _Vector4 Vector4;

/**
 * @brief uses obj_msgSend to communicate directly with objective c
 * eliminating the need for Objective-C files in the code base.
 *
 * https://indiestack.com/2019/10/casting-objective-c-message-sends/
 */

//------------------------------------------------------------------------------
// PRIVATE API
//------------------------------------------------------------------------------
void* (*_mtDeviceName)(void*, SEL) = (void* (*)(void*, SEL)) objc_msgSend;
const char* (*_toString)(void*, SEL) = (const char* (*)(void*, SEL)) objc_msgSend;

void* (*ms)(void*, SEL, const char *) = (void* (*)(void*, SEL, const char *)) objc_msgSend;

void* (*ms_send_sel)(void*, SEL) = (void* (*)(void*, SEL)) objc_msgSend;

void* (*ms_send)(void*, SEL, ...) = (void* (*)(void*, SEL, ...)) objc_msgSend;

void* (*ms_send_void)(void*, SEL, void*) = (void* (*)(void*, SEL, void*)) objc_msgSend;
void* (*ms_send_bool)(void*, SEL, bool) = (void* (*)(void*, SEL, bool)) objc_msgSend;
void* (*ms_send_uint)(void*, SEL, unsigned long) = (void* (*)(void*, SEL, unsigned long)) objc_msgSend;
void (*void_ms_send_ptr)(void*, SEL, void*) = (void (*)(void*, SEL, void*)) objc_msgSend;
void (*void_ms_send_bool)(void*, SEL, unsigned long) = (void (*)(void*, SEL, unsigned long)) objc_msgSend;
void (*void_ms_send_uint)(void*, SEL, unsigned long) = (void (*)(void*, SEL, unsigned long)) objc_msgSend;
void (*void_ms_send_float)(void*, SEL, float) = (void (*)(void*, SEL, float)) objc_msgSend;
void (*void_ms_send_float4)(void*, SEL, float, float, float, float) = (void (*)(void*, SEL, float, float, float, float)) objc_msgSend;
void (*void_ms_send_uint32)(void*, SEL, uint32_t) = (void (*)(void*, SEL, uint32_t)) objc_msgSend;
bool (*bool_ms_send)(void*, SEL) = (bool (*)(void*, SEL)) objc_msgSend;
uintptr_t (*ulong_ms_send)(void*, SEL) = (uintptr_t (*)(void*, SEL)) objc_msgSend;
uint32_t (*uint32_ms_send)(void*, SEL) = (uint32_t (*)(void*, SEL)) objc_msgSend;
void* (*ptr_ms_send)(void*, SEL) = (void* (*)(void*, SEL)) objc_msgSend;
void* (*ptr_ms_send_ptr)(void*, SEL, void*) = (void* (*)(void*, SEL, void*)) objc_msgSend;
void (*ms_send_v)(void*, SEL, void*) = (void (*)(void*, SEL, void*)) objc_msgSend;
void* (*ms_send2)(void*, SEL, uintptr_t, uintptr_t) = (void* (*)(void*, SEL, uintptr_t, uintptr_t)) objc_msgSend;

//------------------------------------------------------------------------------
// PUBLIC API
//------------------------------------------------------------------------------
const char* ns_toString(void* obj_ptr){
    return _toString(obj_ptr, sel_getUid("UTF8String"));
}



void* ns_mtDeviceName(void* obj_ptr){
    return _mtDeviceName(obj_ptr, sel_getUid("name"));
}
