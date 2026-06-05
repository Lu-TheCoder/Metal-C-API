//
//  MT4RenderPass.h
//  Metal C
//
//  MTL4RenderPassDescriptor — describes the attachments for an MTL4 render
//  encoder. The color/depth/stencil attachments are the SAME classic objects
//  used by the Metal 3 render pass, so the color-attachment setters from
//  MTRenderPass.h (mt_render_pass_color_attachment_set_*) work on the
//  descriptor returned by mt4_render_pass_descriptor_get_color_attachment.
//

#pragma once
#include "MTFoundation/defines.h"
#include "MTTypes.h"        // NSUInteger
#include "MTRenderPass.h"   // MTClearColor, MTLoadAction/MTStoreAction, color-attachment setters
#include <stdint.h>

// Whether the render pass resets or accumulates visibility results
// (Metal's MTLVisibilityResultType).
typedef enum MTVisibilityResultType : long {
    MTVisibilityResultTypeReset      = 0,
    MTVisibilityResultTypeAccumulate = 1,
} MTVisibilityResultType;

// ---- Descriptor ----------------------------------------------------------

MT_INLINE MT4RenderPassDescriptor mt4_render_pass_descriptor_create(void) {
    return MT_ALLOC_INIT("MTL4RenderPassDescriptor");
}

// Returns the color attachment descriptor at `index`. Configure it with the
// existing mt_render_pass_color_attachment_set_* functions from MTRenderPass.h.
MT_INLINE MTRenderPassColorAttachmentDescriptor mt4_render_pass_descriptor_get_color_attachment(MT4RenderPassDescriptor desc, NSUInteger index) {
    id arr = MT_MSG_SEND(void*, desc, MT_SEL("colorAttachments"));
    return MT_MSG_SEND_1(void*, arr, MT_SEL("objectAtIndexedSubscript:"), NSUInteger, index);
}

// ---- Depth attachment ----------------------------------------------------

MT_INLINE void mt4_render_pass_descriptor_set_depth_texture(MT4RenderPassDescriptor desc, MTTexture texture) {
    id att = MT_MSG_SEND(void*, desc, MT_SEL("depthAttachment"));
    MT_MSG_SEND_1(void, att, MT_SEL("setTexture:"), id, texture);
}

MT_INLINE void mt4_render_pass_descriptor_set_depth_load_action(MT4RenderPassDescriptor desc, MTLoadAction action) {
    id att = MT_MSG_SEND(void*, desc, MT_SEL("depthAttachment"));
    MT_MSG_SEND_1(void, att, MT_SEL("setLoadAction:"), NSUInteger, action);
}

MT_INLINE void mt4_render_pass_descriptor_set_depth_store_action(MT4RenderPassDescriptor desc, MTStoreAction action) {
    id att = MT_MSG_SEND(void*, desc, MT_SEL("depthAttachment"));
    MT_MSG_SEND_1(void, att, MT_SEL("setStoreAction:"), NSUInteger, action);
}

MT_INLINE void mt4_render_pass_descriptor_set_depth_clear_value(MT4RenderPassDescriptor desc, double clear_value) {
    id att = MT_MSG_SEND(void*, desc, MT_SEL("depthAttachment"));
    MT_MSG_SEND_1(void, att, MT_SEL("setClearDepth:"), double, clear_value);
}

// ---- Stencil attachment --------------------------------------------------

MT_INLINE void mt4_render_pass_descriptor_set_stencil_texture(MT4RenderPassDescriptor desc, MTTexture texture) {
    id att = MT_MSG_SEND(void*, desc, MT_SEL("stencilAttachment"));
    MT_MSG_SEND_1(void, att, MT_SEL("setTexture:"), id, texture);
}

MT_INLINE void mt4_render_pass_descriptor_set_stencil_load_action(MT4RenderPassDescriptor desc, MTLoadAction action) {
    id att = MT_MSG_SEND(void*, desc, MT_SEL("stencilAttachment"));
    MT_MSG_SEND_1(void, att, MT_SEL("setLoadAction:"), NSUInteger, action);
}

MT_INLINE void mt4_render_pass_descriptor_set_stencil_store_action(MT4RenderPassDescriptor desc, MTStoreAction action) {
    id att = MT_MSG_SEND(void*, desc, MT_SEL("stencilAttachment"));
    MT_MSG_SEND_1(void, att, MT_SEL("setStoreAction:"), NSUInteger, action);
}

MT_INLINE void mt4_render_pass_descriptor_set_stencil_clear_value(MT4RenderPassDescriptor desc, uint32_t clear_value) {
    id att = MT_MSG_SEND(void*, desc, MT_SEL("stencilAttachment"));
    MT_MSG_SEND_1(void, att, MT_SEL("setClearStencil:"), uint32_t, clear_value);
}

// ---- Render-target / tile properties -------------------------------------

MT_INLINE void mt4_render_pass_descriptor_set_render_target_width(MT4RenderPassDescriptor desc, NSUInteger width) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setRenderTargetWidth:"), NSUInteger, width);
}

MT_INLINE void mt4_render_pass_descriptor_set_render_target_height(MT4RenderPassDescriptor desc, NSUInteger height) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setRenderTargetHeight:"), NSUInteger, height);
}

MT_INLINE void mt4_render_pass_descriptor_set_render_target_array_length(MT4RenderPassDescriptor desc, NSUInteger length) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setRenderTargetArrayLength:"), NSUInteger, length);
}

MT_INLINE void mt4_render_pass_descriptor_set_default_raster_sample_count(MT4RenderPassDescriptor desc, NSUInteger count) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setDefaultRasterSampleCount:"), NSUInteger, count);
}

MT_INLINE void mt4_render_pass_descriptor_set_tile_width(MT4RenderPassDescriptor desc, NSUInteger width) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setTileWidth:"), NSUInteger, width);
}

MT_INLINE void mt4_render_pass_descriptor_set_tile_height(MT4RenderPassDescriptor desc, NSUInteger height) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setTileHeight:"), NSUInteger, height);
}

// ---- Visibility results --------------------------------------------------

MT_INLINE void mt4_render_pass_descriptor_set_visibility_result_buffer(MT4RenderPassDescriptor desc, MTBuffer buffer) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setVisibilityResultBuffer:"), id, buffer);
}

MT_INLINE void mt4_render_pass_descriptor_set_visibility_result_type(MT4RenderPassDescriptor desc, MTVisibilityResultType type) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setVisibilityResultType:"), MTVisibilityResultType, type);
}
