//
//  MTSampler.h
//  Metal C
//
//  Created by Lungile Maseko on 2024/06/03.
//

#pragma once
#include "MTTypes.h"
#include "MTUtils.h"
#include "MTDepthStencil.h"

typedef enum MTSamplerMinMagFilter {
    MTSamplerMinMagFilterNearest = 0,
    MTSamplerMinMagFilterLinear = 1,
} MTSamplerMinMagFilter;

typedef enum MTSamplerMipFilter {
    MTSamplerMipFilterNotMipmapped = 0,
    MTSamplerMipFilterNearest = 1,
    MTSamplerMipFilterLinear = 2,
} MTSamplerMipFilter;

typedef enum MTSamplerAddressMode {
    MTSamplerAddressModeClampToEdge = 0,
    MTSamplerAddressModeMirrorClampToEdge = 1,
    MTSamplerAddressModeRepeat = 2,
    MTSamplerAddressModeMirrorRepeat = 3,
    MTSamplerAddressModeClampToZero = 4,
    MTSamplerAddressModeClampToBorderColor = 5,
} MTSamplerAddressMode;

typedef enum MTSamplerBorderColor {
    MTSamplerBorderColorTransparentBlack = 0,
    MTSamplerBorderColorOpaqueBlack = 1,
    MTSamplerBorderColorOpaqueWhite = 2,
} MTSamplerBorderColor;

typedef void* MTSamplerDescriptor;
typedef void* MTSamplerState;

MT_INLINE MTSamplerDescriptor mt_sampler_descriptor_new(void) {
    return MT_ALLOC_INIT("MTLSamplerDescriptor");
}

// Setters
MT_INLINE void mt_sampler_descriptor_set_min_filter(MTSamplerDescriptor desc, NSUInteger min_filter) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setMinFilter:"), NSUInteger, min_filter);
}

MT_INLINE void mt_sampler_descriptor_set_mag_filter(MTSamplerDescriptor desc, NSUInteger mag_filter) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setMagFilter:"), NSUInteger, mag_filter);
}

MT_INLINE void mt_samplerDescriptor_set_mip_filter(MTSamplerDescriptor desc, NSUInteger mip_filter) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setMipFilter:"), NSUInteger, mip_filter);
}

MT_INLINE void mt_sampler_descriptor_set_max_anisotropy(MTSamplerDescriptor desc, NSUInteger max_anisotropy) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setMaxAnisotropy:"), NSUInteger, max_anisotropy);
}

MT_INLINE void mt_sampler_descriptor_set_s_address_mode(MTSamplerDescriptor desc, NSUInteger mode) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setSAddressMode:"), NSUInteger, mode);
}

MT_INLINE void mt_sampler_descriptor_set_t_address_mode(MTSamplerDescriptor desc, NSUInteger mode) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setTAddressMode:"), NSUInteger, mode);
}

MT_INLINE void mt_sampler_descriptor_set_r_address_mode(MTSamplerDescriptor desc, NSUInteger mode) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setRAddressMode:"), NSUInteger, mode);
}

MT_INLINE void mt_sampler_descriptor_set_border_color(MTSamplerDescriptor desc, NSUInteger color) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setBorderColor:"), NSUInteger, color);
}

MT_INLINE void mt_sampler_descriptor_set_is_normalized_coordinates(MTSamplerDescriptor desc, bool is_normalized) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setNormalizedCoordinates:"), BOOL, is_normalized);
}

MT_INLINE void mt_sampler_set_lod_min_clamp(MTSamplerDescriptor desc, float min) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setLodMinClamp:"), float, min);
}

MT_INLINE void mt_sampler_set_lod_max_clamp(MTSamplerDescriptor desc, float max) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setLodMaxClamp:"), float, max);
}

MT_INLINE void mt_sampler_set_lod_average(MTSamplerDescriptor desc, BOOL average) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setLodAverage:"), BOOL, average);
}

MT_INLINE void mt_sampler_set_compare_function(MTSamplerDescriptor desc, MTCompareFunction func) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setCompareFunction:"), NSUInteger, func);
}

MT_INLINE void mt_sampler_set_support_argument_buffers(MTSamplerDescriptor desc, BOOL support) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setSupportArgumentBuffers:"), BOOL, support);
}

MT_INLINE void mt_sampler_set_label(MTSamplerDescriptor desc, const char* label) {
    id str = MT_MSG_SEND_CLASS_1(id, MT_CLASS("NSString"), MT_SEL("stringWithUTF8String:"), const char*, label);
    MT_MSG_SEND_1(void, desc, MT_SEL("setLabel:"), id, str);
}

// MARK: MTSamplerState

MT_INLINE const char* mt_sampler_state_get_label(MTSamplerState samplerState) {
    id nsLabel = MT_MSG_SEND(id, samplerState, MT_SEL("label"));
    if (!nsLabel) return NULL;
    return MT_MSG_SEND(const char*, nsLabel, MT_SEL("UTF8String"));
}

MT_INLINE MTDevice mt_sampler_state_get_device(MTSamplerState samplerState) {
    return MT_MSG_SEND(id, samplerState, MT_SEL("device"));
}

// Struct return - explicit cast needed
MT_INLINE MTResourceID mt_sampler_state_get_gpu_resource_id(MTSamplerState samplerState) {
    return ((MTResourceID (*)(id, SEL))objc_msgSend)((id)samplerState, MT_SEL("gpuResourceID"));
}
