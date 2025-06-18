//
//  MTSampler.h
//  Metal C
//
//  Created by Lungile Maseko on 2024/06/03.
//

#pragma once
#include <objc/message.h>
#include "MTTypes.h"
#include "MTDepthStencil.h"

typedef enum MTSamplerMinMagFilter {
    MTSamplerMinMagFilterNearest = 0,
    MTSamplerMinMagFilterLinear = 1,
}MTSamplerMinMagFilter;

typedef enum MTSamplerMipFilter {
    MTSamplerMipFilterNotMipmapped = 0,
    MTSamplerMipFilterNearest = 1,
    MTSamplerMipFilterLinear = 2,
}MTSamplerMipFilter;

typedef enum MTSamplerAddressMode {
    MTSamplerAddressModeClampToEdge = 0,
    MTSamplerAddressModeMirrorClampToEdge = 1,
    MTSamplerAddressModeRepeat = 2,
    MTSamplerAddressModeMirrorRepeat = 3,
    MTSamplerAddressModeClampToZero = 4,
    MTSamplerAddressModeClampToBorderColor = 5,
}MTSamplerAddressMode;

typedef enum MTSamplerBorderColor {
    MTSamplerBorderColorTransparentBlack = 0,
    MTSamplerBorderColorOpaqueBlack = 1,
    MTSamplerBorderColorOpaqueWhite = 2,
}MTSamplerBorderColor;

typedef void* MTSamplerDescriptor;
typedef void* MTSamplerState;

// Create a new MTSamplerDescriptor
MT_INLINE MTSamplerDescriptor mt_sampler_descriptor_new(void) {
    Class cls = objc_getClass("MTLSamplerDescriptor");
    SEL allocSel = sel_registerName("alloc");
    id obj = ((id (*)(Class, SEL))objc_msgSend)(cls, allocSel);

    SEL initSel = sel_registerName("init");
    return ((id (*)(id, SEL))objc_msgSend)(obj, initSel);
}

// Setters
MT_INLINE void mt_sampler_descriptor_set_min_filter(MTSamplerDescriptor desc, NSUInteger min_filter) {
    SEL sel = sel_registerName("setMinFilter:");
    ((void (*)(id, SEL, NSUInteger))objc_msgSend)(desc, sel, min_filter);
}

MT_INLINE void mt_sampler_descriptor_set_mag_filter(MTSamplerDescriptor desc, NSUInteger mag_filter) {
    SEL sel = sel_registerName("setMagFilter:");
    ((void (*)(id, SEL, NSUInteger))objc_msgSend)(desc, sel, mag_filter);
}

MT_INLINE void mt_samplerDescriptor_set_mip_filter(MTSamplerDescriptor desc, NSUInteger mip_filter) {
    SEL sel = sel_registerName("setMipFilter:");
    ((void (*)(id, SEL, NSUInteger))objc_msgSend)(desc, sel, mip_filter);
}

MT_INLINE void mt_sampler_descriptor_set_max_anisotropy(MTSamplerDescriptor desc, NSUInteger max_anisotropy) {
    SEL sel = sel_registerName("setMaxAnisotropy:");
    ((void (*)(id, SEL, NSUInteger))objc_msgSend)(desc, sel, max_anisotropy);
}

MT_INLINE void mt_sampler_descriptor_set_s_address_mode(MTSamplerDescriptor desc, NSUInteger mode) {
    SEL sel = sel_registerName("setSAddressMode:");
    ((void (*)(id, SEL, NSUInteger))objc_msgSend)(desc, sel, mode);
}

MT_INLINE void mt_sampler_descriptor_set_t_address_mode(MTSamplerDescriptor desc, NSUInteger mode) {
    SEL sel = sel_registerName("setTAddressMode:");
    ((void (*)(id, SEL, NSUInteger))objc_msgSend)(desc, sel, mode);
}

MT_INLINE void mt_sampler_descriptor_set_r_address_mode(MTSamplerDescriptor desc, NSUInteger mode) {
    SEL sel = sel_registerName("setRAddressMode:");
    ((void (*)(id, SEL, NSUInteger))objc_msgSend)(desc, sel, mode);
}

MT_INLINE void mt_sampler_descriptor_set_border_color(MTSamplerDescriptor desc, NSUInteger color) {
    SEL sel = sel_registerName("setBorderColor:");
    ((void (*)(id, SEL, NSUInteger))objc_msgSend)(desc, sel, color);
}

MT_INLINE void mt_sampler_descriptor_set_is_normalized_coordinates(MTSamplerDescriptor desc, bool is_normalized) {
    SEL sel = sel_registerName("setNormalizedCoordinates:");
    ((void (*)(id, SEL, BOOL))objc_msgSend)(desc, sel, (BOOL)is_normalized);
}

MT_INLINE void mt_sampler_set_lod_min_clamp(MTSamplerDescriptor desc, float min) {
    SEL sel = sel_registerName("setLodMinClamp:");
    ((void (*)(id, SEL, float))objc_msgSend)(desc, sel, min);
}

MT_INLINE void mt_sampler_set_lod_max_clamp(MTSamplerDescriptor desc, float max) {
    SEL sel = sel_registerName("setLodMaxClamp:");
    ((void (*)(id, SEL, float))objc_msgSend)(desc, sel, max);
}

MT_INLINE void mt_sampler_set_lod_average(MTSamplerDescriptor desc, BOOL average) {
    SEL sel = sel_registerName("setLodAverage:");
    ((void (*)(id, SEL, BOOL))objc_msgSend)(desc, sel, average);
}

MT_INLINE void mt_sampler_set_compare_function(MTSamplerDescriptor desc, MTCompareFunction func) {
    SEL sel = sel_registerName("setCompareFunction:");
    ((void (*)(id, SEL, NSUInteger))objc_msgSend)(desc, sel, func);
}

MT_INLINE void mt_sampler_set_support_argument_buffers(MTSamplerDescriptor desc, BOOL support) {
    SEL sel = sel_registerName("setSupportArgumentBuffers:");
    ((void (*)(id, SEL, BOOL))objc_msgSend)(desc, sel, support);
}

MT_INLINE void mt_sampler_set_label(MTSamplerDescriptor desc, const char* label) {
    SEL sel = sel_getUid("setLabel:");
    id str = ((id (*)(Class, SEL, const char*))objc_msgSend)(
        objc_getClass("NSString"),
        sel_getUid("stringWithUTF8String:"),
        label
    );
    ((void (*)(id, SEL, id))objc_msgSend)(desc, sel, str);
}

// MARK: --------------------- MTSamplerState ---------------------------------

MT_INLINE const char* mt_sampler_state_get_label(MTSamplerState samplerState) {
    SEL sel_label = sel_getUid("label");
    id nsLabel = ((id (*)(id, SEL))objc_msgSend)(samplerState, sel_label);

    if (!nsLabel) return NULL;

    SEL sel_utf8 = sel_getUid("UTF8String");
    return ((const char* (*)(id, SEL))objc_msgSend)(nsLabel, sel_utf8);
}

MT_INLINE MTDevice mt_sampler_state_get_device(MTSamplerState samplerState) {
    SEL sel = sel_getUid("device");
    return (MTDevice)((id (*)(id, SEL))objc_msgSend)(samplerState, sel);
}

MT_INLINE MTResourceID mt_sampler_state_get_gpu_resource_id(MTSamplerState samplerState) {
    SEL sel = sel_getUid("gpuResourceID");
    return ((MTResourceID (*)(id, SEL))objc_msgSend)(samplerState, sel);
}
