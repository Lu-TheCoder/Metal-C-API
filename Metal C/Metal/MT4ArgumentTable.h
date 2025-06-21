//
//  MT4ArgumentTable.h
//  Metal C
//
//  Created by Lungile Maseko on 2025/06/21.
//
#pragma once
#include "MTTypes.h"

typedef void *MT4ArgumentTableDescriptor;
typedef void *MT4ArgumentTable;

MT_INLINE MT4ArgumentTableDescriptor mt4_argument_table_descriptor_create(void) {
    // Get the class object
    Class cls = objc_getClass("MTL4ArgumentTableDescriptor");
    if (!cls) return NULL;

    // Allocate
    id obj = ((id (*)(Class, SEL))objc_msgSend)(cls, sel_getUid("alloc"));
    if (!obj) return NULL;

    // Initialize
    obj = ((id (*)(id, SEL))objc_msgSend)(obj, sel_getUid("init"));
    return obj;
}

MT_INLINE void mt4_argument_table_descriptor_set_max_buffer_bind_count(MT4ArgumentTableDescriptor desc, unsigned long count) {
    if (!desc) return;
    SEL sel = sel_getUid("setMaxBufferBindCount:");
    ((void (*)(id, SEL, unsigned long))objc_msgSend)(desc, sel, count);
}

MT_INLINE void mt4_argument_table_descriptor_set_max_texture_bind_count(MT4ArgumentTableDescriptor desc, unsigned long count) {
    if (!desc) return;
    SEL sel = sel_getUid("setMaxTextureBindCount:");
    ((void (*)(id, SEL, unsigned long))objc_msgSend)(desc, sel, count);
}

MT_INLINE void mt4_argument_table_descriptor_set_max_sampler_state_bind_count(MT4ArgumentTableDescriptor desc, unsigned long count) {
    if (!desc) return;
    SEL sel = sel_getUid("setMaxSamplerStateBindCount:");
    ((void (*)(id, SEL, unsigned long))objc_msgSend)(desc, sel, count);
}

MT_INLINE void mt4_argument_table_descriptor_set_initialize_bindings(MT4ArgumentTableDescriptor desc, bool value) {
    if (!desc) return;
    SEL sel = sel_getUid("setInitializeBindings:");
    ((void (*)(id, SEL, BOOL))objc_msgSend)(desc, sel, value);
}

MT_INLINE void mt4_argument_table_descriptor_set_support_attribute_strides(MT4ArgumentTableDescriptor desc, bool value) {
    if (!desc) return;
    SEL sel = sel_getUid("setSupportAttributeStrides:");
    ((void (*)(id, SEL, BOOL))objc_msgSend)(desc, sel, value);
}

MT_INLINE void mt4_argument_table_descriptor_set_label(MT4ArgumentTableDescriptor desc, const char *label) {
    if (!desc || !label) return;

    SEL setSel = sel_getUid("setLabel:");
    SEL strSel = sel_getUid("stringWithUTF8String:");
    Class nsStringClass = objc_getClass("NSString");

    id nsLabel = ((id (*)(Class, SEL, const char *))objc_msgSend)(
        nsStringClass,
        strSel,
        label
    );

    ((void (*)(id, SEL, id))objc_msgSend)(desc, setSel, nsLabel);
}

MT_INLINE void mt4_argument_table_set_address(MT4ArgumentTable table, uint64_t gpuAddress, unsigned long index) {
    if (!table) return;
    SEL sel = sel_getUid("setAddress:atIndex:");
    ((void (*)(id, SEL, uint64_t, unsigned long))objc_msgSend)(table, sel, gpuAddress, index);
}

MT_INLINE void mt4_argument_table_set_address_with_stride(MT4ArgumentTable table, uint64_t gpuAddress, unsigned long stride, unsigned long index) {
    if (!table) return;
    SEL sel = sel_getUid("setAddress:attributeStride:atIndex:");
    ((void (*)(id, SEL, uint64_t, unsigned long, unsigned long))objc_msgSend)(table, sel, gpuAddress, stride, index);
}

MT_INLINE void mt4_argument_table_set_resource(MT4ArgumentTable table, MTResourceID resourceID, unsigned long index) {
    if (!table) return;
    SEL sel = sel_getUid("setResource:atBufferIndex:");
    ((void (*)(id, SEL, MTResourceID, unsigned long))objc_msgSend)(table, sel, resourceID, index);
}

MT_INLINE void mt4_argument_table_set_texture(MT4ArgumentTable table, MTResourceID resourceID, unsigned long index) {
    if (!table) return;
    SEL sel = sel_getUid("setTexture:atIndex:");
    ((void (*)(id, SEL, MTResourceID, unsigned long))objc_msgSend)(table, sel, resourceID, index);
}

MT_INLINE void mt4_argument_table_set_sampler_state(MT4ArgumentTable table, MTResourceID resourceID, unsigned long index) {
    if (!table) return;
    SEL sel = sel_getUid("setSamplerState:atIndex:");
    ((void (*)(id, SEL, MTResourceID, unsigned long))objc_msgSend)(table, sel, resourceID, index);
}

MT_INLINE MTDevice mt4_argument_table_get_device(MT4ArgumentTable table) {
    if (!table) return NULL;

    SEL sel = sel_getUid("device");
    return ((MTDevice (*)(id, SEL))objc_msgSend)(table, sel);
}

MT_INLINE void mt4_argument_table_set_label(MT4ArgumentTable table, const char* label) {
    if (!table || !label) return;

    SEL setSel = sel_getUid("setLabel:");
    id nsLabel = ((id (*)(Class, SEL, const char*))objc_msgSend)(
        objc_getClass("NSString"),
        sel_getUid("stringWithUTF8String:"),
        label
    );
    ((void (*)(id, SEL, id))objc_msgSend)(table, setSel, nsLabel);
}
