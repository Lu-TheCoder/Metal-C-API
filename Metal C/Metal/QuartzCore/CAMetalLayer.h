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
typedef void* CAMetalLayer;
typedef void* CAMetalDrawable;
typedef void* NSDictionary;
typedef void* CGColorSpace;

typedef struct {
    double width;
    double height;
} CGSize;

// CAMetalLayer Functions

CAMetalLayer cametal_layer_create(void) {
    Class cls = objc_getClass("CAMetalLayer");
    return ((id (*)(Class, SEL))objc_msgSend)(cls, sel_registerName("new"));
}

void cametal_layer_set_device(CAMetalLayer layer, MTDevice device) {
    ((void (*)(id, SEL, id))objc_msgSend)(layer, sel_registerName("setDevice:"), device);
}

MTDevice cametal_layer_get_device(CAMetalLayer layer) {
    return ((id (*)(id, SEL))objc_msgSend)(layer, sel_registerName("device"));
}

MTDevice cametal_layer_get_preferred_device(CAMetalLayer layer) {
    return ((id (*)(id, SEL))objc_msgSend)(layer, sel_registerName("preferredDevice"));
}

void cametal_layer_set_pixel_format(CAMetalLayer layer, int pixel_format) {
    ((void (*)(id, SEL, int))objc_msgSend)(layer, sel_registerName("setPixelFormat:"), pixel_format);
}

int cametal_layer_get_pixel_format(CAMetalLayer layer) {
    return ((int (*)(id, SEL))objc_msgSend)(layer, sel_registerName("pixelFormat"));
}

void cametal_layer_set_framebuffer_only(CAMetalLayer layer, bool framebuffer_only) {
    ((void (*)(id, SEL, bool))objc_msgSend)(layer, sel_registerName("setFramebufferOnly:"), framebuffer_only);
}

bool cametal_layer_get_framebuffer_only(CAMetalLayer layer) {
    return ((bool (*)(id, SEL))objc_msgSend)(layer, sel_registerName("framebufferOnly"));
}

void cametal_layer_set_drawable_size(CAMetalLayer layer, double width, double height) {
    CGSize size = { width, height };
    ((void (*)(id, SEL, CGSize))objc_msgSend)(layer, sel_registerName("setDrawableSize:"), size);
}

void cametal_layer_get_drawable_size(CAMetalLayer layer, double *width, double *height) {
    CGSize size = ((CGSize (*)(id, SEL))objc_msgSend)(layer, sel_registerName("drawableSize"));
    *width = size.width;
    *height = size.height;
}

CAMetalDrawable cametal_layer_next_drawable(CAMetalLayer layer) {
    return ((id (*)(id, SEL))objc_msgSend)(layer, sel_registerName("nextDrawable"));
}

void cametal_layer_set_colorspace(CAMetalLayer layer, CGColorSpace colorspace) {
    ((void (*)(id, SEL, CGColorSpace))objc_msgSend)(layer, sel_registerName("setColorspace:"), colorspace);
}

void cametal_layer_set_max_drawables(CAMetalLayer layer, unsigned int count) {
    ((void (*)(id, SEL, NSUInteger))objc_msgSend)(layer, sel_registerName("setMaximumDrawableCount:"), count);
}

void cametal_layer_set_presents_with_transaction(CAMetalLayer layer, bool enabled) {
    ((void (*)(id, SEL, bool))objc_msgSend)(layer, sel_registerName("setPresentsWithTransaction:"), enabled);
}

void cametal_layer_set_display_sync_enabled(CAMetalLayer layer, bool enabled) {
    ((void (*)(id, SEL, bool))objc_msgSend)(layer, sel_registerName("setDisplaySyncEnabled:"), enabled);
}

void cametal_layer_set_allows_next_drawable_timeout(CAMetalLayer layer, bool enabled) {
    ((void (*)(id, SEL, bool))objc_msgSend)(layer, sel_registerName("setAllowsNextDrawableTimeout:"), enabled);
}

void cametal_layer_set_developer_hud_properties(CAMetalLayer layer, NSDictionary props) {
    ((void (*)(id, SEL, NSDictionary))objc_msgSend)(layer, sel_registerName("setDeveloperHUDProperties:"), props);
}

// CAMetalDrawable Functions

MTTexture cametal_drawable_get_texture(CAMetalDrawable drawable) {
    return ((id (*)(id, SEL))objc_msgSend)(drawable, sel_registerName("texture"));
}

CAMetalLayer cametal_drawable_get_layer(CAMetalDrawable drawable) {
    return ((id (*)(id, SEL))objc_msgSend)(drawable, sel_registerName("layer"));
}

