//
//  CAMetalLayer.h
//  Metal C
//
//  Created by Lungile Maseko on 2025/06/04.
//
#pragma once
#include "../MTFoundation/defines.h"

// Typedefs

typedef struct {
    double width;
    double height;
} MT_CGSize;

// CAMetalLayer Functions

MT_INLINE MT_CAMetalLayer cametal_layer_create(void) {
    return MT_MSG_SEND_CLASS(void*, MT_CLASS("CAMetalLayer"), MT_SEL("new"));
}

MT_INLINE void cametal_layer_set_device(MT_CAMetalLayer layer, MTDevice device) {
    MT_MSG_SEND_1(void, layer, MT_SEL("setDevice:"), id, device);
}

MT_INLINE MTDevice cametal_layer_get_device(MT_CAMetalLayer layer) {
    return MT_MSG_SEND(void*, layer, MT_SEL("device"));
}

MT_INLINE MTDevice cametal_layer_get_preferred_device(MT_CAMetalLayer layer) {
    return MT_MSG_SEND(void*, layer, MT_SEL("preferredDevice"));
}

MT_INLINE void cametal_layer_set_pixel_format(MT_CAMetalLayer layer, int pixel_format) {
    MT_MSG_SEND_1(void, layer, MT_SEL("setPixelFormat:"), int, pixel_format);
}

MT_INLINE int cametal_layer_get_pixel_format(MT_CAMetalLayer layer) {
    return MT_MSG_SEND(int, layer, MT_SEL("pixelFormat"));
}

MT_INLINE void cametal_layer_set_framebuffer_only(MT_CAMetalLayer layer, bool framebuffer_only) {
    MT_MSG_SEND_1(void, layer, MT_SEL("setFramebufferOnly:"), bool, framebuffer_only);
}

MT_INLINE bool cametal_layer_get_framebuffer_only(MT_CAMetalLayer layer) {
    return MT_MSG_SEND(bool, layer, MT_SEL("framebufferOnly"));
}

// Struct args need explicit cast
MT_INLINE void cametal_layer_set_drawable_size(MT_CAMetalLayer layer, double width, double height) {
    MT_CGSize size = { width, height };
    ((void (*)(id, SEL, MT_CGSize))objc_msgSend)((id)layer, MT_SEL("setDrawableSize:"), size);
}

MT_INLINE void cametal_layer_get_drawable_size(MT_CAMetalLayer layer, double *width, double *height) {
    MT_CGSize size = ((MT_CGSize (*)(id, SEL))objc_msgSend)((id)layer, MT_SEL("drawableSize"));
    *width = size.width;
    *height = size.height;
}

MT_INLINE CAMetalDrawable cametal_layer_next_drawable(MT_CAMetalLayer layer) {
    return MT_MSG_SEND(void*, layer, MT_SEL("nextDrawable"));
}

MT_INLINE void cametal_layer_set_colorspace(MT_CAMetalLayer layer, CGColorSpace colorspace) {
    MT_MSG_SEND_1(void, layer, MT_SEL("setColorspace:"), CGColorSpace, colorspace);
}

MT_INLINE void cametal_layer_set_max_drawables(MT_CAMetalLayer layer, unsigned int count) {
    MT_MSG_SEND_1(void, layer, MT_SEL("setMaximumDrawableCount:"), NSUInteger, count);
}

MT_INLINE void cametal_layer_set_presents_with_transaction(MT_CAMetalLayer layer, bool enabled) {
    MT_MSG_SEND_1(void, layer, MT_SEL("setPresentsWithTransaction:"), bool, enabled);
}

MT_INLINE void cametal_layer_set_display_sync_enabled(MT_CAMetalLayer layer, bool enabled) {
    MT_MSG_SEND_1(void, layer, MT_SEL("setDisplaySyncEnabled:"), bool, enabled);
}

MT_INLINE void cametal_layer_set_allows_next_drawable_timeout(MT_CAMetalLayer layer, bool enabled) {
    MT_MSG_SEND_1(void, layer, MT_SEL("setAllowsNextDrawableTimeout:"), bool, enabled);
}

MT_INLINE void cametal_layer_set_developer_hud_properties(MT_CAMetalLayer layer, MTDictionary props) {
    MT_MSG_SEND_1(void, layer, MT_SEL("setDeveloperHUDProperties:"), id, props);
}

// The layer's residency set, which automatically tracks the current drawable.
// Use it with the Metal 4 path (mt4_command_buffer_use_residency_set) so the
// drawable is resident when you render to it. (macOS 26+)
MT_INLINE MTResidencySet cametal_layer_get_residency_set(MT_CAMetalLayer layer) {
    return MT_MSG_SEND(void*, layer, MT_SEL("residencySet"));
}

// CAMetalDrawable Functions

MT_INLINE MTTexture cametal_drawable_get_texture(CAMetalDrawable drawable) {
    return MT_MSG_SEND(void*, drawable, MT_SEL("texture"));
}

MT_INLINE MT_CAMetalLayer cametal_drawable_get_layer(CAMetalDrawable drawable) {
    return MT_MSG_SEND(void*, drawable, MT_SEL("layer"));
}
