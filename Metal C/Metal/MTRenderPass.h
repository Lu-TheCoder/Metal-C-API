//
//  MTRenderPass.h
//  Metal C
//
//  Created by Lungile Maseko on 2024/04/29.
//

#pragma once
#include "MTTexture.h"
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

typedef void* MTRenderPassAttachmentDescriptor;
typedef void* MTRenderPassColorAttachmentDescriptor;
typedef void* MTRenderPassDescriptor;
typedef void* MTRenderPassColorAttachmentDescriptorArray;

// ============================================================================
// MTClearColor helpers
// ============================================================================

MT_INLINE MTClearColor mt_clear_color(double r, double g, double b, double a) {
    return (MTClearColor){ r, g, b, a };
}

// ============================================================================
// MTRenderPassDescriptor
// ============================================================================

MT_INLINE MTRenderPassDescriptor mt_renderpass_new(void) {
    Class cls = MT_CLASS("MTLRenderPassDescriptor");
    id obj = MT_MSG_SEND_CLASS(id, cls, MT_SEL("alloc"));
    return MT_MSG_SEND(id, obj, MT_SEL("init"));
}

MT_INLINE void mt_renderpass_set_target_width(MTRenderPassDescriptor desc, NSUInteger width) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setRenderTargetWidth:"), NSUInteger, width);
}

MT_INLINE void mt_renderpass_set_target_height(MTRenderPassDescriptor desc, NSUInteger height) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setRenderTargetHeight:"), NSUInteger, height);
}

// ============================================================================
// Color Attachment - Single step access (combines array + index lookup)
// ============================================================================

MT_INLINE MTRenderPassColorAttachmentDescriptor mt_renderpass_color_attachment(MTRenderPassDescriptor desc, NSUInteger index) {
    id arr = MT_MSG_SEND(id, desc, MT_SEL("colorAttachments"));
    return MT_MSG_SEND_1(id, arr, MT_SEL("objectAtIndexedSubscript:"), NSUInteger, index);
}

// ============================================================================
// Color Attachment Properties
// ============================================================================

MT_INLINE void mt_renderpass_color_attachment_set_texture(MTRenderPassColorAttachmentDescriptor ca, MTTexture texture) {
    MT_MSG_SEND_1(void, ca, MT_SEL("setTexture:"), id, texture);
}

MT_INLINE void mt_renderpass_color_attachment_set_load_action(MTRenderPassColorAttachmentDescriptor ca, MTLoadAction action) {
    MT_MSG_SEND_1(void, ca, MT_SEL("setLoadAction:"), NSUInteger, action);
}

MT_INLINE void mt_renderpass_color_attachment_set_store_action(MTRenderPassColorAttachmentDescriptor ca, MTStoreAction action) {
    MT_MSG_SEND_1(void, ca, MT_SEL("setStoreAction:"), NSUInteger, action);
}

MT_INLINE void mt_renderpass_color_attachment_set_clear_color(MTRenderPassColorAttachmentDescriptor ca, MTClearColor color) {
    ((void (*)(id, SEL, MTClearColor))objc_msgSend)((id)ca, MT_SEL("setClearColor:"), color);
}

MT_INLINE MTClearColor mt_renderpass_color_attachment_get_clear_color(MTRenderPassColorAttachmentDescriptor ca) {
    return ((MTClearColor (*)(id, SEL))objc_msgSend)((id)ca, MT_SEL("clearColor"));
}

MT_INLINE void mt_renderpass_color_attachment_set_resolve_texture(MTRenderPassColorAttachmentDescriptor ca, MTTexture texture) {
    MT_MSG_SEND_1(void, ca, MT_SEL("setResolveTexture:"), id, texture);
}

// ============================================================================
// Depth Attachment
// ============================================================================

MT_INLINE void mt_renderpass_set_depth_texture(MTRenderPassDescriptor desc, MTTexture texture) {
    id depthAttachment = MT_MSG_SEND(id, desc, MT_SEL("depthAttachment"));
    MT_MSG_SEND_1(void, depthAttachment, MT_SEL("setTexture:"), id, texture);
}

MT_INLINE void mt_renderpass_set_depth_load_action(MTRenderPassDescriptor desc, MTLoadAction action) {
    id depthAttachment = MT_MSG_SEND(id, desc, MT_SEL("depthAttachment"));
    MT_MSG_SEND_1(void, depthAttachment, MT_SEL("setLoadAction:"), NSUInteger, action);
}

MT_INLINE void mt_renderpass_set_depth_store_action(MTRenderPassDescriptor desc, MTStoreAction action) {
    id depthAttachment = MT_MSG_SEND(id, desc, MT_SEL("depthAttachment"));
    MT_MSG_SEND_1(void, depthAttachment, MT_SEL("setStoreAction:"), NSUInteger, action);
}

MT_INLINE void mt_renderpass_set_depth_clear_value(MTRenderPassDescriptor desc, double clearValue) {
    id depthAttachment = MT_MSG_SEND(id, desc, MT_SEL("depthAttachment"));
    MT_MSG_SEND_1(void, depthAttachment, MT_SEL("setClearDepth:"), double, clearValue);
}

// ============================================================================
// Deprecated aliases for backwards compatibility
// ============================================================================
#define mt_renderpass_descriptor_new mt_renderpass_new
#define mt_clear_color_create mt_clear_color
#define mtRenderPassDescSetTargetWidth mt_renderpass_set_target_width
#define mtRenderPassDescSetTargetHeight mt_renderpass_set_target_height
#define mt_renderpass_color_attachment_get_color_attachments(desc) MT_MSG_SEND(id, desc, MT_SEL("colorAttachments"))
#define mt_renderpass_get_color_attachment_at_index(arr, idx) MT_MSG_SEND_1(id, arr, MT_SEL("objectAtIndexedSubscript:"), NSUInteger, idx)
#define mt_renderpass_color_attachment_set_loadAction mt_renderpass_color_attachment_set_load_action
#define mt_renderpass_color_attachment_set_storeAction mt_renderpass_color_attachment_set_store_action
#define mt_renderpass_color_attachment_set_clearColor mt_renderpass_color_attachment_set_clear_color
#define mt_renderpass_color_attachments_set_texture(desc, idx, tex) mt_renderpass_color_attachment_set_texture(mt_renderpass_color_attachment(desc, idx), tex)
#define mt_renderpass_color_attachments_set_load_action(desc, idx, act) mt_renderpass_color_attachment_set_load_action(mt_renderpass_color_attachment(desc, idx), act)
#define mt_renderpass_color_attachments_set_store_action(desc, idx, act) mt_renderpass_color_attachment_set_store_action(mt_renderpass_color_attachment(desc, idx), act)
#define mt_renderpass_color_attachments_set_clear_color(desc, idx, clr) mt_renderpass_color_attachment_set_clear_color(mt_renderpass_color_attachment(desc, idx), clr)
#define mtSetClearColor(ptr, r, g, b, a) (*(ptr) = mt_clear_color(r, g, b, a))
#define mt_renderPass_color_attachment_get_clear_color mt_renderpass_color_attachment_get_clear_color
#define mtSetRenderPassColorAttachmentDescriptorClearColor(desc, ptr) mt_renderpass_color_attachment_set_clear_color(desc, *(ptr))

