//
//  MTRenderPipeline.h
//  Metal C
//
//  Created by Lungile Maseko on 2024/05/29.
//

#pragma once
#include "MTLibrary.h"
#include "MTVertexDescriptor.h"
#include "MTPixelFormat.h"

typedef void MTRenderPipelineColorAttachmentDescriptor;
typedef void MTRenderPipelineColorAttachmentDescriptorArray;
typedef void MTRenderPipelineDescriptor;
typedef void MTRenderPipelineState;

/**
 * @brief Creates a new MTLRenderPipelineColorAttachmentDescriptor class
 *
 * NOTE: Should be released using mtRelease();
 */
MT_INLINE MTRenderPipelineColorAttachmentDescriptor* mt_renderPipeline_color_attachment_descriptor_new(void){
    Class renderPipeColorAttDesc = objc_getClass("MTLRenderPipelineColorAttachmentDescriptor");
    SEL allocSel = sel_registerName("alloc");
    
    void* attDesc = ms_send(renderPipeColorAttDesc, allocSel);
    SEL initSel = sel_registerName("init");
    ms_send(attDesc, initSel);
    return attDesc;
}

/**
 * @brief Creates a new MTLRenderPipelineDescriptor class
 *
 * NOTE: Should be released using mtRelease();
 */
MT_INLINE MTRenderPipelineDescriptor* mt_renderPipeline_descriptor_new(void) {
    Class renderPipeDesc = objc_getClass("MTLRenderPipelineDescriptor");
    SEL allocSel = sel_registerName("alloc");
    
    void* renderDesc = ms_send(renderPipeDesc, allocSel);
    SEL initSel = sel_registerName("init");
    return ms_send(renderDesc, initSel);
}

MT_INLINE MTRenderPipelineColorAttachmentDescriptorArray* mt_renderPipeline_get_color_attachments(MTRenderPipelineDescriptor* render_pipeline_desc){
    SEL sel = sel_registerName("colorAttachments");
    return ms_send(render_pipeline_desc, sel);
}

MT_INLINE MTRenderPipelineColorAttachmentDescriptor* mt_renderPipeline_get_color_attachment_at_index(MTRenderPipelineColorAttachmentDescriptorArray* rpcada, unsigned long color_attach_index) {
    return ms_send_uint(rpcada, sel_registerName("objectAtIndexedSubscript:"), color_attach_index);
}

MT_INLINE void mt_renderPipeline_descriptor_set_vertex_function(MTRenderPipelineDescriptor* renderPipelineDesc, MTFunction* vertFunction) {
    ms_send_void(renderPipelineDesc, sel_registerName("setVertexFunction:"), vertFunction);
}

MT_INLINE void mt_renderPipeline_descriptor_set_fragment_function(MTRenderPipelineDescriptor* renderPipelineDesc, MTFunction* fragFunction) {
    ms_send_void(renderPipelineDesc, sel_registerName("setFragmentFunction:"), fragFunction);
}

MT_INLINE void mt_renderPipeline_descriptor_set_vertex_descriptor(MTRenderPipelineDescriptor* renderPipelineDesc, MTVertexDescriptor* vertDesc) {
    ms_send_void(renderPipelineDesc, sel_registerName("setVertexDescriptor:"), vertDesc);
}

MT_INLINE void mt_renderPipeline_descriptor_set_sample_count(MTRenderPipelineDescriptor* renderPipelineDesc, uintptr_t count) {
    void_ms_send_uint(renderPipelineDesc, sel_registerName("setSampleCount:"), count);
}

MT_INLINE void mt_renderPipeline_descriptor_set_raster_sample_count(MTRenderPipelineDescriptor* renderPipelineDesc, uintptr_t count) {
    void_ms_send_uint(renderPipelineDesc, sel_registerName("setRasterSampleCount:"), count);
}

MT_INLINE void mt_rendePipeline_descriptor_set_depth_attachment_pixel_format(MTRenderPipelineDescriptor* desc, MTPixelFormat format) {
    SEL sel = sel_registerName("setDepthAttachmentPixelFormat:");
//    MTRenderPipelineColorAttachmentDescriptor* color_attachments = mtRenderPipelineColorAttachments(renderPipelineDesc);
    void_ms_send_uint(desc, sel, format);
}

MT_INLINE void mt_rendePipeline_descriptor_set_stencil_attachment_pixel_format(MTRenderPipelineDescriptor* desc, MTPixelFormat format) {
    SEL sel = sel_registerName("setStencilAttachmentPixelFormat:");
//    MTRenderPipelineColorAttachmentDescriptor* color_attachments = mtRenderPipelineColorAttachments(renderPipelineDesc);
    void_ms_send_uint(desc, sel, format);
}


MT_INLINE void mt_renderPipeline_descriptor_set_color_attachments_pixel_format(MTRenderPipelineDescriptor* renderPipelineDesc, unsigned long color_attach_index, MTPixelFormat format) {
    MTRenderPipelineColorAttachmentDescriptor* color_attachments = mt_renderPipeline_get_color_attachments(renderPipelineDesc);
    ms_send_uint(mt_renderPipeline_get_color_attachment_at_index(color_attachments, color_attach_index), sel_registerName("setPixelFormat:"), format);
}

MT_INLINE void mt_rendePipeline_descriptor_set_color_attachment_pixel_format(MTRenderPipelineColorAttachmentDescriptor* color_attachment, MTPixelFormat format) {
    SEL sel = sel_registerName("setPixelFormat:");
//    MTRenderPipelineColorAttachmentDescriptor* color_attachments = mtRenderPipelineColorAttachments(renderPipelineDesc);
    ms_send_uint(color_attachment, sel, format);
}
