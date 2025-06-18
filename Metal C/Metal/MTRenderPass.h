//
//  MTRenderPass.h
//  Metal C
//
//  Created by Lungile Maseko on 2024/04/29.
//

#pragma once
#include "MTTexture.h"

typedef struct
{
    double red;
    double green;
    double blue;
    double alpha;
} MTClearColor;

typedef enum MTLoadAction{
   MTLoadActionDontCare = 0,
   MTLoadActionLoad = 1,
   MTLoadActionClear = 2,
}MTLoadAction;

typedef enum MTStoreAction{
    MTStoreActionDontCare = 0,
    MTStoreActionStore = 1,
    MTStoreActionMultisampleResolve = 2,
    MTStoreActionStoreAndMultisampleResolve = 3,
    MTStoreActionUnknown = 4,
    MTStoreActionCustomSampleDepthStore = 5,
}MTStoreAction;

typedef enum MTStoreActionOptions{
    StoreActionOptionNone = 0,
    StoreActionOptionCustomSamplePositions = 1,
    StoreActionOptionValidMask = 1,
}MTStoreActionOptions;


typedef void* MTRenderPassAttachmentDescriptor;

typedef void* MTRenderPassColorAttachmentDescriptor;

typedef void* MTRenderPassDescriptor;

typedef void* MTRenderPassColorAttachmentDescriptorArray;

MT_INLINE void mtSetClearColor(MTClearColor* clearColor, double red, double green, double blue, double alpha){
    clearColor->red = red;
    clearColor->green = green;
    clearColor->blue = blue;
    clearColor->alpha = alpha;
};

/**
 * @brief Creates a new MTLRenderPassDescriptor class
 *
 * NOTE: Should be released using mtRelease();
 */
// Create a new MTLRenderPassDescriptor
MT_INLINE MTRenderPassDescriptor mt_renderpass_descriptor_new(void) {
    Class cls = objc_getClass("MTLRenderPassDescriptor");
    SEL allocSel = sel_registerName("alloc");
    id obj = ((id (*)(Class, SEL))objc_msgSend)(cls, allocSel);

    SEL initSel = sel_registerName("init");
    return ((id (*)(id, SEL))objc_msgSend)(obj, initSel);
}

// Set render target width (same method used by two wrappers)
MT_INLINE void mtRenderPassDescSetSampleCount(MTRenderPassDescriptor desc, NSUInteger count) {
    SEL sel = sel_registerName("setRenderTargetWidth:");
    ((void (*)(id, SEL, NSUInteger))objc_msgSend)(desc, sel, count);
}

MT_INLINE void mtRenderPassDescSetTargetWidth(MTRenderPassDescriptor desc, NSUInteger width) {
    SEL sel = sel_registerName("setRenderTargetWidth:");
    ((void (*)(id, SEL, NSUInteger))objc_msgSend)(desc, sel, width);
}

MT_INLINE void mtRenderPassDescSetTargetHeight(MTRenderPassDescriptor desc, NSUInteger height) {
    SEL sel = sel_registerName("setRenderTargetHeight:");
    ((void (*)(id, SEL, NSUInteger))objc_msgSend)(desc, sel, height);
}

// Get color attachments array from render pass descriptor
MT_INLINE MTRenderPassColorAttachmentDescriptorArray mt_renderpass_color_attachment_get_color_attachments(MTRenderPassDescriptor desc) {
    SEL sel = sel_registerName("colorAttachments");
    return ((id (*)(id, SEL))objc_msgSend)(desc, sel);
}

// Set load/store actions on color attachment descriptor
MT_INLINE void mt_renderpass_color_attachment_set_loadAction(void* attachment, MTLoadAction action) {
    SEL sel = sel_registerName("setLoadAction:");
    ((void (*)(id, SEL, NSUInteger))objc_msgSend)(attachment, sel, action);
}

MT_INLINE void mt_renderpass_color_attachment_set_storeAction(void* attachment, MTStoreAction action) {
    SEL sel = sel_registerName("setStoreAction:");
    ((void (*)(id, SEL, NSUInteger))objc_msgSend)(attachment, sel, action);
}

MT_INLINE MTClearColor mt_clear_color_create(double red, double green, double blue, double alpha)
{
    MTClearColor result;
    result.red = red;
    result.green = green;
    result.blue = blue;
    result.alpha = alpha;
    return result;
}

MT_INLINE void mt_renderpass_color_attachment_set_clearColor(
    MTRenderPassColorAttachmentDescriptor rpColorAttachDescriptor,
    MTClearColor color
) {
    typedef void (*MsgSendFunc)(void*, SEL, MTClearColor);
    ((MsgSendFunc)objc_msgSend)(rpColorAttachDescriptor, sel_getUid("setClearColor:"), color);
}

// Set the texture of a color attachment descriptor
MT_INLINE void mt_renderpass_color_attachment_set_texture(MTRenderPassColorAttachmentDescriptor colorDesc, void* texture) {
    SEL sel = sel_registerName("setTexture:");
    ((void (*)(id, SEL, id))objc_msgSend)(colorDesc, sel, texture);
}

// Get color attachment descriptor at given index from array
MT_INLINE MTRenderPassColorAttachmentDescriptor mt_renderpass_get_color_attachment_at_index(MTRenderPassColorAttachmentDescriptorArray array, NSUInteger index) {
    SEL sel = sel_registerName("objectAtIndexedSubscript:");
    return ((id (*)(id, SEL, NSUInteger))objc_msgSend)(array, sel, index);
}

// Get clearColor from a color attachment descriptor
MT_INLINE MTClearColor mt_renderPass_color_attachment_get_clear_color(MTRenderPassColorAttachmentDescriptor desc) {
    SEL sel = sel_registerName("clearColor");
    return ((MTClearColor (*)(id, SEL))objc_msgSend)(desc, sel);
}

// Set clearColor on a color attachment descriptor
MT_INLINE void mtSetRenderPassColorAttachmentDescriptorClearColor(MTRenderPassColorAttachmentDescriptor desc, MTClearColor* color) {
    SEL sel = sel_registerName("setClearColor:");
    ((void (*)(id, SEL, MTClearColor))objc_msgSend)(desc, sel, *color);
}



MT_INLINE void mt_renderpass_color_attachments_set_texture(MTRenderPassDescriptor desc, NSUInteger index, MTTexture texture) {
    MTRenderPassColorAttachmentDescriptorArray arr = ((id (*)(id, SEL))objc_msgSend)(desc, sel_getUid("colorAttachments"));
    id attachment = ((id (*)(id, SEL, NSUInteger))objc_msgSend)(arr, sel_getUid("objectAtIndexedSubscript:"), index);
    ((void (*)(id, SEL, id))objc_msgSend)(attachment, sel_getUid("setTexture:"), texture);
}

MT_INLINE void mt_renderpass_color_attachments_set_resolve_texture(MTRenderPassDescriptor desc, NSUInteger index, MTTexture resolve_texture) {
    MTRenderPassColorAttachmentDescriptorArray arr = ((id (*)(id, SEL))objc_msgSend)(desc, sel_getUid("colorAttachments"));
    id attachment = ((id (*)(id, SEL, NSUInteger))objc_msgSend)(arr, sel_getUid("objectAtIndexedSubscript:"), index);
    ((void (*)(id, SEL, id))objc_msgSend)(attachment, sel_getUid("setResolveTexture:"), resolve_texture);
}

MT_INLINE void mt_renderpass_color_attachments_set_load_action(MTRenderPassDescriptor desc, NSUInteger index, MTLoadAction action) {
    MTRenderPassColorAttachmentDescriptorArray arr = ((id (*)(id, SEL))objc_msgSend)(desc, sel_getUid("colorAttachments"));
    id attachment = ((id (*)(id, SEL, NSUInteger))objc_msgSend)(arr, sel_getUid("objectAtIndexedSubscript:"), index);
    ((void (*)(id, SEL, NSUInteger))objc_msgSend)(attachment, sel_getUid("setLoadAction:"), action);
}

MT_INLINE void mt_renderpass_color_attachments_set_store_action(MTRenderPassDescriptor desc, NSUInteger index, MTStoreAction action) {
    MTRenderPassColorAttachmentDescriptorArray arr = ((id (*)(id, SEL))objc_msgSend)(desc, sel_getUid("colorAttachments"));
    id attachment = ((id (*)(id, SEL, NSUInteger))objc_msgSend)(arr, sel_getUid("objectAtIndexedSubscript:"), index);
    ((void (*)(id, SEL, NSUInteger))objc_msgSend)(attachment, sel_getUid("setStoreAction:"), action);
}

MT_INLINE void mt_renderpass_color_attachments_set_clear_color(MTRenderPassDescriptor desc, NSUInteger index, MTClearColor color) {
    MTRenderPassColorAttachmentDescriptorArray arr = ((id (*)(id, SEL))objc_msgSend)(desc, sel_getUid("colorAttachments"));
    id attachment = ((id (*)(id, SEL, NSUInteger))objc_msgSend)(arr, sel_getUid("objectAtIndexedSubscript:"), index);
    ((void (*)(id, SEL, MTClearColor))objc_msgSend)(attachment, sel_getUid("setClearColor:"), color);
}

MT_INLINE void mt_renderpass_set_depth_texture(MTRenderPassDescriptor desc, MTTexture texture) {
    id depthAttachment = ((id (*)(id, SEL))objc_msgSend)(desc, sel_getUid("depthAttachment"));
    ((void (*)(id, SEL, id))objc_msgSend)(depthAttachment, sel_getUid("setTexture:"), texture);
}

MT_INLINE void mt_renderpass_set_depth_load_action(MTRenderPassDescriptor desc, MTLoadAction action) {
    id depthAttachment = ((id (*)(id, SEL))objc_msgSend)(desc, sel_getUid("depthAttachment"));
    ((void (*)(id, SEL, NSUInteger))objc_msgSend)(depthAttachment, sel_getUid("setLoadAction:"), action);
}

MT_INLINE void mt_renderpass_set_depth_store_action(MTRenderPassDescriptor desc, MTStoreAction action) {
    id depthAttachment = ((id (*)(id, SEL))objc_msgSend)(desc, sel_getUid("depthAttachment"));
    ((void (*)(id, SEL, NSUInteger))objc_msgSend)(depthAttachment, sel_getUid("setStoreAction:"), action);
}

MT_INLINE void mt_renderpass_set_depth_clear_value(MTRenderPassDescriptor desc, double clearValue) {
    id depthAttachment = ((id (*)(id, SEL))objc_msgSend)(desc, sel_getUid("depthAttachment"));
    ((void (*)(id, SEL, double))objc_msgSend)(depthAttachment, sel_getUid("setClearDepth:"), clearValue);
}
