//
//  CAMetalLayer.h
//  Metal C
//
//  Created by Lungile Maseko on 2025/06/04.
//
#pragma once

#include <objc/message.h>
#include <objc/runtime.h>

// Typedefs
typedef void* MTDevice;
typedef void* MTTexture;
typedef void* MTDrawable;
typedef void* MT_CAMetalLayer;
typedef void* MT_CAMetalDrawable;
typedef void* MTDictionary;
typedef void* CGColorSpace;

typedef struct {
    double width;
    double height;
} MT_CGSize;

// CAMetalLayer Functions

MT_INLINE MT_CAMetalLayer cametal_layer_create(void) {
    Class cls = objc_getClass("CAMetalLayer");
    return ((id (*)(Class, SEL))objc_msgSend)(cls, sel_registerName("new"));
}

MT_INLINE void cametal_layer_set_device(MT_CAMetalLayer layer, MTDevice device) {
    ((void (*)(id, SEL, id))objc_msgSend)(layer, sel_registerName("setDevice:"), device);
}

MT_INLINE MTDevice cametal_layer_get_device(MT_CAMetalLayer layer) {
    return ((id (*)(id, SEL))objc_msgSend)(layer, sel_registerName("device"));
}

MT_INLINE MTDevice cametal_layer_get_preferred_device(MT_CAMetalLayer layer) {
    return ((id (*)(id, SEL))objc_msgSend)(layer, sel_registerName("preferredDevice"));
}

MT_INLINE void cametal_layer_set_pixel_format(MT_CAMetalLayer layer, int pixel_format) {
    ((void (*)(id, SEL, int))objc_msgSend)(layer, sel_registerName("setPixelFormat:"), pixel_format);
}

MT_INLINE int cametal_layer_get_pixel_format(MT_CAMetalLayer layer) {
    return ((int (*)(id, SEL))objc_msgSend)(layer, sel_registerName("pixelFormat"));
}

MT_INLINE void cametal_layer_set_framebuffer_only(MT_CAMetalLayer layer, bool framebuffer_only) {
    ((void (*)(id, SEL, bool))objc_msgSend)(layer, sel_registerName("setFramebufferOnly:"), framebuffer_only);
}

MT_INLINE bool cametal_layer_get_framebuffer_only(MT_CAMetalLayer layer) {
    return ((bool (*)(id, SEL))objc_msgSend)(layer, sel_registerName("framebufferOnly"));
}

MT_INLINE void cametal_layer_set_drawable_size(MT_CAMetalLayer layer, double width, double height) {
    MT_CGSize size = { width, height };
    ((void (*)(id, SEL, MT_CGSize))objc_msgSend)(layer, sel_registerName("setDrawableSize:"), size);
}

MT_INLINE void cametal_layer_get_drawable_size(MT_CAMetalLayer layer, double *width, double *height) {
    MT_CGSize size = ((MT_CGSize (*)(id, SEL))objc_msgSend)(layer, sel_registerName("drawableSize"));
    *width = size.width;
    *height = size.height;
}

MT_INLINE CAMetalDrawable cametal_layer_next_drawable(MT_CAMetalLayer layer) {
    return ((id (*)(id, SEL))objc_msgSend)(layer, sel_registerName("nextDrawable"));
}

MT_INLINE void cametal_layer_set_colorspace(MT_CAMetalLayer layer, CGColorSpace colorspace) {
    ((void (*)(id, SEL, CGColorSpace))objc_msgSend)(layer, sel_registerName("setColorspace:"), colorspace);
}

MT_INLINE void cametal_layer_set_max_drawables(MT_CAMetalLayer layer, unsigned int count) {
    ((void (*)(id, SEL, NSUInteger))objc_msgSend)(layer, sel_registerName("setMaximumDrawableCount:"), count);
}

MT_INLINE void cametal_layer_set_presents_with_transaction(MT_CAMetalLayer layer, bool enabled) {
    ((void (*)(id, SEL, bool))objc_msgSend)(layer, sel_registerName("setPresentsWithTransaction:"), enabled);
}

MT_INLINE void cametal_layer_set_display_sync_enabled(MT_CAMetalLayer layer, bool enabled) {
    ((void (*)(id, SEL, bool))objc_msgSend)(layer, sel_registerName("setDisplaySyncEnabled:"), enabled);
}

MT_INLINE void cametal_layer_set_allows_next_drawable_timeout(MT_CAMetalLayer layer, bool enabled) {
    ((void (*)(id, SEL, bool))objc_msgSend)(layer, sel_registerName("setAllowsNextDrawableTimeout:"), enabled);
}

MT_INLINE void cametal_layer_set_developer_hud_properties(MT_CAMetalLayer layer, MTDictionary props) {
    ((void (*)(id, SEL, MTDictionary))objc_msgSend)(layer, sel_registerName("setDeveloperHUDProperties:"), props);
}

// CAMetalDrawable Functions

MT_INLINE MTTexture cametal_drawable_get_texture(CAMetalDrawable drawable) {
    return ((id (*)(id, SEL))objc_msgSend)(drawable, sel_registerName("texture"));
}

MT_INLINE MT_CAMetalLayer cametal_drawable_get_layer(CAMetalDrawable drawable) {
    return ((id (*)(id, SEL))objc_msgSend)(drawable, sel_registerName("layer"));
}

