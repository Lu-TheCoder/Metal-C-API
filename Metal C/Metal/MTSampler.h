//
//  MTSampler.h
//  Metal C
//
//  Created by Lungile Maseko on 2024/06/03.
//

#pragma once
#include <objc/message.h>

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

typedef void MTSamplerDescriptor;
typedef void MTSamplerState;

void* (*ms_send_textRegion2)(void*, SEL, MTRegion, NSUInteger, void*, NSUInteger) = (void* (*)(void*, SEL, MTRegion, NSUInteger, void*, NSUInteger)) objc_msgSend;


MT_INLINE MTSamplerDescriptor* mt_samplerDescriptor_new(void){
    return NSCLASS_NEW("MTLSamplerDescriptor");
}

MT_INLINE void mt_samplerDescriptor_set_minFilter(MTSamplerDescriptor* sampler_desc, MTSamplerMinMagFilter min_filter) {
    ms_send_uint(sampler_desc, sel_registerName("setMinFilter:"), min_filter);
}

MT_INLINE void mt_samplerDescriptor_set_magFilter(MTSamplerDescriptor* sampler_desc, MTSamplerMinMagFilter mag_filter) {
    ms_send_uint(sampler_desc, sel_registerName("setMagFilter:"), mag_filter);
}

MT_INLINE void mt_samplerDescriptor_set_mipFilter(MTSamplerDescriptor* sampler_desc, MTSamplerMipFilter mip_filter) {
    ms_send_uint(sampler_desc, sel_registerName("setMipFilter:"), mip_filter);
}

MT_INLINE void mt_samplerDescriptor_set_maxAnisotropy(MTSamplerDescriptor* sampler_desc, NSUInteger max_anisotropy) {
    ms_send_uint(sampler_desc, sel_registerName("setMaxAnisotropy:"), max_anisotropy);
}

MT_INLINE void mt_samplerDescriptor_set_sAddressMode(MTSamplerDescriptor* sampler_desc, MTSamplerAddressMode addr_mode) {
    ms_send_uint(sampler_desc, sel_registerName("setSAddressMode:"), addr_mode);
}

MT_INLINE void mt_samplerDescriptor_set_tAddressMode(MTSamplerDescriptor* sampler_desc, MTSamplerAddressMode addr_mode) {
    ms_send_uint(sampler_desc, sel_registerName("setTAddressMode:"), addr_mode);
}

MT_INLINE void mt_samplerDescriptor_set_rAddressMode(MTSamplerDescriptor* sampler_desc, MTSamplerAddressMode addr_mode) {
    ms_send_uint(sampler_desc, sel_registerName("setRAddressMode:"), addr_mode);
}

MT_INLINE void mt_samplerDescriptor_set_borderColor(MTSamplerDescriptor* sampler_desc, MTSamplerBorderColor border_color) {
    ms_send_uint(sampler_desc, sel_registerName("setBorderColor:"), border_color);
}

MT_INLINE void mt_samplerDescriptor_set_isNormalizedCoordinates(MTSamplerDescriptor* sampler_desc, bool is_normalized) {
    ms_send_uint(sampler_desc, sel_registerName("setNormalizedCoordinates:"), is_normalized);
}

// TODO: incomplete...
