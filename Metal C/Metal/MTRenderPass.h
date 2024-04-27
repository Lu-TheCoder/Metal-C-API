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


typedef void MTRenderPassAttachmentDescriptor;

typedef void MTRenderPassColorAttachmentDescriptor;

typedef void MTRenderPassDescriptor;

typedef void MTRenderPassColorAttachmentDescriptorArray;

void mtSetClearColor(MTClearColor* clearColor, double red, double green, double blue, double alpha){
    clearColor->red = red;
    clearColor->green = green;
    clearColor->blue = blue;
    clearColor->alpha = alpha;
};

MTClearColor mtNewClearColor(double r, double g, double b, double a){
    MTClearColor color;
    color.red = r;
    color.green = g;
    color.blue = b;
    color.alpha = a;
    
    return color;
}

/**
 * @brief Creates a new MTLRenderPassAttachmentDescriptor class
 *
 * NOTE: Should be released using mtRelease();
 */
MT_INLINE MTRenderPassAttachmentDescriptor* mtNewRenderPassAttachmentDescriptor(void){
    Class renderpassAttDesc = objc_getClass("MTLRenderPassAttachmentDescriptor");
    SEL allocSel = sel_registerName("alloc");
    
    void* pass = ms_send(renderpassAttDesc, allocSel);
    SEL initSel = sel_registerName("init");
    return ms_send(pass, initSel);
}

/**
 * @brief Creates a new MTLRenderPassColorAttachmentDescriptor class
 *
 * NOTE: Should be released using mtRelease();
 */
MT_INLINE MTRenderPassColorAttachmentDescriptor* mtNewRenderPassColorAttachmentDescriptor(void){
    Class AttDesc = objc_getClass("MTLRenderPassColorAttachmentDescriptor");
    SEL allocSel = sel_registerName("alloc");
    
    void* att = ms_send(AttDesc, allocSel);
    SEL initSel = sel_registerName("init");
    ms_send(att, initSel);
    return att;
}

/**
 * @brief Creates a new MTLRenderPassDescriptor class
 *
 * NOTE: Should be released using mtRelease();
 */
MT_INLINE MTRenderPassDescriptor* mt_renderpass_descriptor_new(void) {
    Class renderpassDesc = objc_getClass("MTLRenderPassDescriptor");
    SEL allocSel = sel_registerName("alloc");
    
    void* pass = ms_send(renderpassDesc, allocSel);
    SEL initSel = sel_registerName("init");
    return ms_send(pass, initSel);
}

MT_INLINE void mtRenderPassDescSetSampleCount(MTRenderPassDescriptor* ptr, NSUInteger width){
    SEL sel = sel_registerName("setRenderTargetWidth:");
    ms_send_uint(ptr, sel, width);
}

MT_INLINE void mtRenderPassDescSetTargetWidth(MTRenderPassDescriptor* ptr, NSUInteger width){
    SEL sel = sel_registerName("setRenderTargetWidth:");
    ms_send_uint(ptr, sel, width);
}

MT_INLINE void mtRenderPassDescSetTargetHeight(MTRenderPassDescriptor* ptr, NSUInteger height){
    SEL sel = sel_registerName("setRenderTargetHeight:");
    ms_send_uint(ptr, sel, height);
}

MT_INLINE MTRenderPassColorAttachmentDescriptorArray* mt_renderpass_color_attachment_get_color_attachments(MTRenderPassDescriptor* renderpass){
    SEL attchSel = sel_registerName("colorAttachments");
    return ms_send(renderpass, attchSel);
}

MT_INLINE void mt_renderpass_color_attachment_set_loadAction(void* ptr, MTLoadAction action) {
    ms_send_uint(ptr, sel_registerName("setLoadAction:"), action);
}

MT_INLINE void mt_renderpass_color_attachment_set_storeAction(void* ptr, MTStoreAction action) {
    ms_send_uint(ptr, sel_registerName("setStoreAction:"), action);
}

MT_INLINE MTClearColor mt_clear_color_make(double red, double green, double blue, double alpha)
{
    MTClearColor result;
    result.red = red;
    result.green = green;
    result.blue = blue;
    result.alpha = alpha;
    return result;
}

void* (*ms_send_color)(void*, SEL, MTClearColor) = (void* (*)(void*, SEL, MTClearColor)) objc_msgSend;

MT_INLINE void mt_renderpass_color_attachment_set_clearColor(MTRenderPassColorAttachmentDescriptor* colorDesc, MTClearColor color){
    ms_send_color(colorDesc, sel_registerName("setClearColor:"), color);
}

MT_INLINE void mt_renderpass_color_attachment_set_texture(void* ptr, void* texture){
    ms_send_void(ptr, sel_registerName("setTexture:"), texture);
}

MT_INLINE MTRenderPassColorAttachmentDescriptor* mt_renderpass_get_color_attachment_at_index(MTRenderPassColorAttachmentDescriptorArray* rcadA, NSUInteger attachment_index){
    SEL selIndex = sel_registerName("objectAtIndexedSubscript:");
    return  ms_send_uint(rcadA, selIndex, attachment_index);
}

//FIXME: Not Returning a populated ClearColor struct.
MTClearColor* mtGetRenderPassColorAttachmentDescriptorClearColor(MTRenderPassColorAttachmentDescriptor* rpColorAttachDescriptor){
    return (MTClearColor*) ms_send(rpColorAttachDescriptor, sel_getUid("clearColor"));
}

MT_INLINE void mtSetRenderPassColorAttachmentDescriptorClearColor(MTRenderPassColorAttachmentDescriptor* rpColorAttachDescriptor, MTClearColor* color){
    ms_send_v(rpColorAttachDescriptor, sel_registerName("setClearColor:"), color);
}


