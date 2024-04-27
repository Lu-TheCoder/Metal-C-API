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

void mtSetClearColor(MTClearColor* clearColor, double red, double green, double blue, double alpha){
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
MT_INLINE MTRenderPassDescriptor mt_renderpass_descriptor_new(void) {
    Class renderpassDesc = objc_getClass("MTLRenderPassDescriptor");
    SEL allocSel = sel_getUid("alloc");
    
    void* pass = ms_send(renderpassDesc, allocSel);
    SEL initSel = sel_getUid("init");
    return ms_send(pass, initSel);
}

MT_INLINE void mtRenderPassDescSetSampleCount(MTRenderPassDescriptor ptr, NSUInteger width){
    SEL sel = sel_getUid("setRenderTargetWidth:");
    ms_send_uint(ptr, sel, width);
}

MT_INLINE void mtRenderPassDescSetTargetWidth(MTRenderPassDescriptor ptr, NSUInteger width){
    SEL sel = sel_getUid("setRenderTargetWidth:");
    ms_send_uint(ptr, sel, width);
}

MT_INLINE void mtRenderPassDescSetTargetHeight(MTRenderPassDescriptor ptr, NSUInteger height){
    SEL sel = sel_getUid("setRenderTargetHeight:");
    ms_send_uint(ptr, sel, height);
}

MT_INLINE MTRenderPassColorAttachmentDescriptorArray mt_renderpass_color_attachment_get_color_attachments(MTRenderPassDescriptor renderpass){
    SEL attchSel = sel_getUid("colorAttachments");
    return ms_send(renderpass, attchSel);
}

MT_INLINE void mt_renderpass_color_attachment_set_loadAction(void* ptr, MTLoadAction action) {
    ms_send_uint(ptr, sel_getUid("setLoadAction:"), action);
}

MT_INLINE void mt_renderpass_color_attachment_set_storeAction(void* ptr, MTStoreAction action) {
    ms_send_uint(ptr, sel_getUid("setStoreAction:"), action);
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

MT_INLINE void mt_renderpass_color_attachment_set_texture(MTRenderPassColorAttachmentDescriptor colorDesc, void* texture){
    ms_send_void(colorDesc, sel_getUid("setTexture:"), texture);
}

MT_INLINE MTRenderPassColorAttachmentDescriptor* mt_renderpass_get_color_attachment_at_index(MTRenderPassColorAttachmentDescriptorArray rcadA, NSUInteger attachment_index){
    SEL selIndex = sel_getUid("objectAtIndexedSubscript:");
    return  ms_send_uint(rcadA, selIndex, attachment_index);
}

MT_INLINE MTClearColor mt_renderPass_color_attachment_get_clear_color(MTRenderPassColorAttachmentDescriptor rpColorAttachDescriptor) {
    typedef MTClearColor (*MsgSendFunc)(void*, SEL);
    return ((MsgSendFunc)objc_msgSend)(rpColorAttachDescriptor, sel_getUid("clearColor"));
}

MT_INLINE void mtSetRenderPassColorAttachmentDescriptorClearColor(MTRenderPassColorAttachmentDescriptor rpColorAttachDescriptor, MTClearColor* color){
    ms_send_v(rpColorAttachDescriptor, sel_getUid("setClearColor:"), color);
}


