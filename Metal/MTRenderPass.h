//
//  MTRenderPass.h
//  Metal C
//
//  Created by Lungile Maseko on 2024/04/29.
//

#pragma once
#include "MTTexture.h"
#include "MTPixelFormat.h"
#include "MTFoundation/defines.h"

typedef struct {
    double red;
    double green;
    double blue;
    double alpha;
} MTClearColor;

typedef enum MTLoadAction {
   MTLoadActionDontCare = 0,
   MTLoadActionLoad = 1,
   MTLoadActionClear = 2,
} MTLoadAction;

typedef enum MTStoreAction {
    MTStoreActionDontCare = 0,
    MTStoreActionStore = 1,
    MTStoreActionMultisampleResolve = 2,
    MTStoreActionStoreAndMultisampleResolve = 3,
    MTStoreActionUnknown = 4,
    MTStoreActionCustomSampleDepthStore = 5,
} MTStoreAction;

typedef enum MTStoreActionOptions {
    StoreActionOptionNone = 0,
    StoreActionOptionCustomSamplePositions = 1,
    StoreActionOptionValidMask = 1,
} MTStoreActionOptions;

// ============================================================================
// MTClearColor helpers
// ============================================================================

MT_INLINE MTClearColor mt_clear_color(double r, double g, double b, double a) {
    return (MTClearColor){ r, g, b, a };
}

// ============================================================================
// MTRenderPassDescriptor
// ============================================================================

MT_INLINE MTRenderPassDescriptor mt_render_pass_create(void) {
    Class cls = MT_CLASS("MTLRenderPassDescriptor");
    id obj = MT_MSG_SEND_CLASS(void*, cls, MT_SEL("alloc"));
    return MT_MSG_SEND(void*, obj, MT_SEL("init"));
}

MT_INLINE void mt_render_pass_set_target_width(MTRenderPassDescriptor desc, NSUInteger width) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setRenderTargetWidth:"), NSUInteger, width);
}

MT_INLINE void mt_render_pass_set_target_height(MTRenderPassDescriptor desc, NSUInteger height) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setRenderTargetHeight:"), NSUInteger, height);
}

// ============================================================================
// Color Attachment - Single step access (combines array + index lookup)
// ============================================================================

MT_INLINE MTRenderPassColorAttachmentDescriptor mt_render_pass_color_attachment(MTRenderPassDescriptor desc, NSUInteger index) {
    id arr = MT_MSG_SEND(void*, desc, MT_SEL("colorAttachments"));
    return MT_MSG_SEND_1(void*, arr, MT_SEL("objectAtIndexedSubscript:"), NSUInteger, index);
}

// ============================================================================
// Color Attachment Properties
// ============================================================================

MT_INLINE void mt_render_pass_color_attachment_set_texture(MTRenderPassColorAttachmentDescriptor ca, MTTexture texture) {
    MT_MSG_SEND_1(void, ca, MT_SEL("setTexture:"), id, texture);
}

MT_INLINE void mt_render_pass_color_attachment_set_load_action(MTRenderPassColorAttachmentDescriptor ca, MTLoadAction action) {
    MT_MSG_SEND_1(void, ca, MT_SEL("setLoadAction:"), NSUInteger, action);
}

MT_INLINE void mt_render_pass_color_attachment_set_store_action(MTRenderPassColorAttachmentDescriptor ca, MTStoreAction action) {
    MT_MSG_SEND_1(void, ca, MT_SEL("setStoreAction:"), NSUInteger, action);
}

MT_INLINE void mt_render_pass_color_attachment_set_clear_color(MTRenderPassColorAttachmentDescriptor ca, MTClearColor color) {
    ((void (*)(id, SEL, MTClearColor))objc_msgSend)((id)ca, MT_SEL("setClearColor:"), color);
}

MT_INLINE MTClearColor mt_render_pass_color_attachment_get_clear_color(MTRenderPassColorAttachmentDescriptor ca) {
    return ((MTClearColor (*)(id, SEL))objc_msgSend)((id)ca, MT_SEL("clearColor"));
}

MT_INLINE void mt_render_pass_color_attachment_set_resolve_texture(MTRenderPassColorAttachmentDescriptor ca, MTTexture texture) {
    MT_MSG_SEND_1(void, ca, MT_SEL("setResolveTexture:"), id, texture);
}

// ============================================================================
// Depth Attachment
// ============================================================================

MT_INLINE void mt_render_pass_set_depth_texture(MTRenderPassDescriptor desc, MTTexture texture) {
    id depthAttachment = MT_MSG_SEND(void*, desc, MT_SEL("depthAttachment"));
    MT_MSG_SEND_1(void, depthAttachment, MT_SEL("setTexture:"), id, texture);
}

MT_INLINE void mt_render_pass_set_depth_load_action(MTRenderPassDescriptor desc, MTLoadAction action) {
    id depthAttachment = MT_MSG_SEND(void*, desc, MT_SEL("depthAttachment"));
    MT_MSG_SEND_1(void, depthAttachment, MT_SEL("setLoadAction:"), NSUInteger, action);
}

MT_INLINE void mt_render_pass_set_depth_store_action(MTRenderPassDescriptor desc, MTStoreAction action) {
    id depthAttachment = MT_MSG_SEND(void*, desc, MT_SEL("depthAttachment"));
    MT_MSG_SEND_1(void, depthAttachment, MT_SEL("setStoreAction:"), NSUInteger, action);
}

MT_INLINE void mt_render_pass_set_depth_clear_value(MTRenderPassDescriptor desc, double clearValue) {
    id depthAttachment = MT_MSG_SEND(void*, desc, MT_SEL("depthAttachment"));
    MT_MSG_SEND_1(void, depthAttachment, MT_SEL("setClearDepth:"), double, clearValue);
}

