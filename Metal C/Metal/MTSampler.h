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

void* (*ms_send_textRegion2)(void*, SEL, MTRegion, NSUInteger, void*, NSUInteger) = (void* (*)(void*, SEL, MTRegion, NSUInteger, void*, NSUInteger)) objc_msgSend;

MT_INLINE MTSamplerDescriptor* mt_samplerDescriptor_new(void){
    return NSCLASS_NEW("MTLSamplerDescriptor");
}

MT_INLINE void mt_samplerDescriptor_set_minFilter(MTSamplerDescriptor sampler_desc, MTSamplerMinMagFilter min_filter) {
    ms_send_uint(sampler_desc, sel_getUid("setMinFilter:"), min_filter);
}

MT_INLINE void mt_samplerDescriptor_set_magFilter(MTSamplerDescriptor sampler_desc, MTSamplerMinMagFilter mag_filter) {
    ms_send_uint(sampler_desc, sel_getUid("setMagFilter:"), mag_filter);
}

MT_INLINE void mt_samplerDescriptor_set_mipFilter(MTSamplerDescriptor sampler_desc, MTSamplerMipFilter mip_filter) {
    ms_send_uint(sampler_desc, sel_getUid("setMipFilter:"), mip_filter);
}

MT_INLINE void mt_samplerDescriptor_set_maxAnisotropy(MTSamplerDescriptor sampler_desc, NSUInteger max_anisotropy) {
    ms_send_uint(sampler_desc, sel_getUid("setMaxAnisotropy:"), max_anisotropy);
}

MT_INLINE void mt_samplerDescriptor_set_sAddressMode(MTSamplerDescriptor sampler_desc, MTSamplerAddressMode addr_mode) {
    ms_send_uint(sampler_desc, sel_getUid("setSAddressMode:"), addr_mode);
}

MT_INLINE void mt_samplerDescriptor_set_tAddressMode(MTSamplerDescriptor sampler_desc, MTSamplerAddressMode addr_mode) {
    ms_send_uint(sampler_desc, sel_getUid("setTAddressMode:"), addr_mode);
}

MT_INLINE void mt_samplerDescriptor_set_rAddressMode(MTSamplerDescriptor sampler_desc, MTSamplerAddressMode addr_mode) {
    ms_send_uint(sampler_desc, sel_getUid("setRAddressMode:"), addr_mode);
}

MT_INLINE void mt_samplerDescriptor_set_borderColor(MTSamplerDescriptor sampler_desc, MTSamplerBorderColor border_color) {
    ms_send_uint(sampler_desc, sel_getUid("setBorderColor:"), border_color);
}

MT_INLINE void mt_samplerDescriptor_set_isNormalizedCoordinates(MTSamplerDescriptor sampler_desc, bool is_normalized) {
    ms_send_uint(sampler_desc, sel_getUid("setNormalizedCoordinates:"), is_normalized);
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
