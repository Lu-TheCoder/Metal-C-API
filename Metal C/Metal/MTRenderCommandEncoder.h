//
//  MTRenderCommandEncoder.h
//  Metal C
//
//  Created by Lungile Maseko on 2024/04/29.
//

#pragma once
#include <stdint.h>
#include "MTDepthStencil.h"
#include "MTRenderPass.h"
#include "MTRenderPipeline.h"
#include "MTCommandBuffer.h"
#include "MTStageInputOutputDescriptor.h"

typedef enum MTPrimitiveType {
    MTPrimitiveTypePoint = 0,
    MTPrimitiveTypeLine = 1,
    MTPrimitiveTypeLineStrip = 2,
    MTPrimitiveTypeTriangle = 3,
    MTPrimitiveTypeTriangleStrip = 4,
}MTPrimitiveType;

typedef enum MTVisibilityResultMode {
    MTVisibilityResultModeDisabled = 0,
    MTVisibilityResultModeBoolean = 1,
    MTVisibilityResultModeCounting = 2,
}MTVisibilityResultMode;

typedef struct MTScissorRect {
    uintptr_t x;
    uintptr_t y;
    uintptr_t width;
    uintptr_t height;
}MTScissorRect;

typedef struct MTViewport {
    double originX;
    double originY;
    double width;
    double height;
    double znear;
    double zfar;
}MTViewport;

typedef enum MTCullMode {
    MTCullModeNone = 0,
    MTCullModeFront = 1,
    MTCullModeBack = 2,
}MTCullMode;

typedef enum MTWinding {
    MTWindingClockwise = 0,
    MTWindingCounterClockwise = 1,
}MTWinding;

typedef enum MTDepthClipMode {
    MTDepthClipModeClip = 0,
    MTDepthClipModeClamp = 1,
}MTDepthClipMode;

typedef enum MTTriangleFillMode {
    MTTriangleFillModeFill = 0,
    MTTriangleFillModeLines = 1,
}MTTriangleFillMode;

typedef struct MTDrawPrimitivesIndirectArguments {
    NSUInteger vertexCount;
    NSUInteger instanceCount;
    NSUInteger vertexStart;
    NSUInteger baseInstance;
}MTDrawPrimitivesIndirectArguments;

typedef void MTRenderCommandEncoder;

MTRenderCommandEncoder* mt_renderCommand_encoder_new(MTCommandBuffer* cmdBuf, MTRenderPassDescriptor* renderpassDesc){
    SEL selRCEWDescSel = sel_registerName("renderCommandEncoderWithDescriptor:");
    return ms_send_void(cmdBuf, selRCEWDescSel, renderpassDesc);
}

void mt_renderCommand_encoder_end_encoding(MTRenderCommandEncoder* renderCmdEncoder){
    SEL sel = sel_registerName("endEncoding");
     ms_send(renderCmdEncoder, sel);
}

void mt_renderCommand_encoder_set_pipeline_state(MTRenderCommandEncoder* render_cmd_enc, MTRenderPipelineState* pipeline_state){
    ms_send_void(render_cmd_enc, sel_registerName("setRenderPipelineState:"), pipeline_state);
}

MTViewport mt_viewport_make(double origin_x, double origin_y, double width, double height, double znear, double zfar)
{
    MTViewport viewport = {
        .originX = origin_x,
        .originY = origin_y,
        .width = width,
        .height = height,
        .znear = znear,
        .zfar = zfar,
    };
    
    return viewport;
}

void* (*ms_send_vertBuf)(void*, SEL, void*, NSUInteger, NSUInteger) = (void* (*)(void*, SEL, void*, NSUInteger, NSUInteger)) objc_msgSend;
void* (*ms_send_bytes)(void*, SEL, const void*, NSUInteger, NSUInteger) = (void* (*)(void*, SEL, const void*, NSUInteger, NSUInteger)) objc_msgSend;


void mt_renderCommand_encoder_set_vertex_buffer(MTRenderCommandEncoder* render_cmd_enc, MTBuffer* buffer, NSUInteger offset, NSUInteger at_index){
    ms_send_vertBuf(render_cmd_enc, sel_registerName("setVertexBuffer:offset:atIndex:"), buffer, offset, at_index);
}

void mt_renderCommand_encoder_set_vertex_bytes(MTRenderCommandEncoder* render_cmd_enc, const void* bytes, NSUInteger length, NSUInteger at_index){
    ms_send_bytes(render_cmd_enc, sel_registerName("setVertexBytes:length:atIndex:"), bytes, length, at_index);
}

void mt_renderCommand_encoder_set_fragment_buffer(MTRenderCommandEncoder* render_cmd_enc, MTBuffer* buffer, NSUInteger offset, NSUInteger at_index){
    ms_send_vertBuf(render_cmd_enc, sel_registerName("setFragmentBuffer:offset:atIndex:"), buffer, offset, at_index);
}

void mt_renderCommand_encoder_set_fragment_bytes(MTRenderCommandEncoder* render_cmd_enc, const void* bytes, NSUInteger length, NSUInteger at_index){
    ms_send_bytes(render_cmd_enc, sel_registerName("setFragmentBytes:length:atIndex:"), bytes, length, at_index);
}

void* (*ms_send_viewport)(void*, SEL, MTViewport) = (void* (*)(void*, SEL, MTViewport)) objc_msgSend;

void mt_renderCommand_encoder_set_viewport(MTRenderCommandEncoder* render_cmd_enc, MTViewport viewport) {
    ms_send_viewport(render_cmd_enc, sel_registerName("setViewport:"), viewport);
}

void* (*ms_send_drawPrim)(void*, SEL, NSUInteger, NSUInteger, NSUInteger) = (void* (*)(void*, SEL, NSUInteger, NSUInteger, NSUInteger)) objc_msgSend;

void* (*ms_send_drawIndxPrim)(void*, SEL, NSUInteger, NSUInteger, NSUInteger, const MTBuffer*, NSUInteger) = (void* (*)(void*, SEL, NSUInteger, NSUInteger, NSUInteger, const MTBuffer*, NSUInteger)) objc_msgSend;

void* (*ms_send_drawIndxPrimInst)(void*, SEL, NSUInteger, NSUInteger, NSUInteger, const MTBuffer*, NSUInteger, NSUInteger) = (void* (*)(void*, SEL, NSUInteger, NSUInteger, NSUInteger, const MTBuffer*, NSUInteger, NSUInteger)) objc_msgSend;


void mt_renderCommand_encoder_draw_primitives(MTRenderCommandEncoder* render_cmd_enc, MTPrimitiveType type, NSUInteger vertex_start, NSUInteger vertex_count){
    ms_send_drawPrim(render_cmd_enc, sel_registerName("drawPrimitives:vertexStart:vertexCount:"), type, vertex_start, vertex_count);
}

void mt_renderCommand_encoder_draw_indexed_primitives_with_instance_count(MTRenderCommandEncoder* render_cmd_enc,
                                                          MTPrimitiveType primitive_type,
                                                          NSUInteger index_count,
                                                          MTIndexType index_type,
                                                          const MTBuffer* index_buffer,
                                                          uintptr_t index_buffer_offset,
                                                          uintptr_t instance_count) {
    ms_send_drawIndxPrimInst(render_cmd_enc,
                     sel_registerName("drawIndexedPrimitives:indexCount:indexType:indexBuffer:indexBufferOffset:"),
                     primitive_type, index_count, index_type, index_buffer, index_buffer_offset, instance_count);
}

void mt_renderCommand_encoder_draw_indexed_primitives(MTRenderCommandEncoder* render_cmd_enc,
                                                          MTPrimitiveType primitive_type,
                                                          NSUInteger index_count,
                                                          MTIndexType index_type,
                                                          const MTBuffer* index_buffer,
                                                          uintptr_t index_buffer_offset) {
    ms_send_drawIndxPrim(render_cmd_enc,
                     sel_registerName("drawIndexedPrimitives:indexCount:indexType:indexBuffer:indexBufferOffset:"),
                     primitive_type, index_count, index_type, index_buffer, index_buffer_offset);
}

void* (*ms_send_fragTex)(void*, SEL, void*, unsigned long) = (void* (*)(void*, SEL, void*, unsigned long)) objc_msgSend;

void mt_renderCommand_encoder_set_fragment_texture_at_index(MTRenderCommandEncoder* render_cmd_enc, MTTexture* texture, NSUInteger index) {
    ms_send_fragTex(render_cmd_enc, sel_registerName("setFragmentTexture:atIndex:"), texture, index);
}

void mt_renderCommand_encoder_set_fragment_sampler_state_at_index(MTRenderCommandEncoder* render_cmd_enc, MTSamplerState* sampler_state, NSUInteger index) {
    ms_send_fragTex(render_cmd_enc, sel_registerName("setFragmentSamplerState:atIndex:"), sampler_state, index);
}

void mt_renderCommand_encoder_set_depth_stencil_state(MTRenderCommandEncoder* render_cmd_enc, MTDepthStencilState* depth_state) {
    void_ms_send_ptr(render_cmd_enc, sel_registerName("setDepthStencilState:"), depth_state);
}

void mt_renderCommand_encoder_set_cull_mode(MTRenderCommandEncoder* render_cmd_enc, MTCullMode mode) {
    void_ms_send_uint(render_cmd_enc, sel_registerName("setCullMode:"), mode);
}

void mt_renderCommand_encoder_set_triangle_fill_mode(MTRenderCommandEncoder* render_cmd_enc, MTTriangleFillMode mode) {
    void_ms_send_uint(render_cmd_enc, sel_registerName("setTriangleFillMode:"), mode);
}

void mt_renderCommand_encoder_set_depth_clip_mode(MTRenderCommandEncoder* render_cmd_enc, MTDepthClipMode mode) {
    void_ms_send_uint(render_cmd_enc, sel_registerName("setDepthClipMode:"), mode);
}

void mt_renderCommand_encoder_set_front_facing_winding(MTRenderCommandEncoder* render_cmd_enc, MTWinding winding) {
    void_ms_send_uint(render_cmd_enc, sel_registerName("setFrontFacingWinding:"), winding);
}

void mt_renderCommand_encoder_set_depth_store_action(MTRenderCommandEncoder* render_cmd_enc, MTStoreAction store_action) {
    void_ms_send_uint(render_cmd_enc, sel_registerName("setDepthStoreAction:"), store_action);
}

void mt_renderCommand_encoder_set_stencil_store_action(MTRenderCommandEncoder* render_cmd_enc, MTStoreAction store_action) {
    void_ms_send_uint(render_cmd_enc, sel_registerName("setStencilStoreAction:"), store_action);
}

void mt_renderCommand_encoder_set_depth_store_action_options(MTRenderCommandEncoder* render_cmd_enc, MTStoreActionOptions options) {
    void_ms_send_uint(render_cmd_enc, sel_registerName("setDepthStoreActionOptions:"), options);
}

void mt_renderCommand_encoder_set_stencil_store_action_options(MTRenderCommandEncoder* render_cmd_enc, MTStoreActionOptions options) {
    void_ms_send_uint(render_cmd_enc, sel_registerName("setStencilStoreActionOptions:"), options);
}

void mt_renderCommand_encoder_set_tessellation_factor_scale(MTRenderCommandEncoder* render_cmd_enc, float scale) {
    void_ms_send_float(render_cmd_enc, sel_registerName("setTessellationFactorScale:"), scale);
}

void mt_renderCommand_encoder_set_blend_color(MTRenderCommandEncoder* render_cmd_enc, float r, float g, float b, float a) {
    void_ms_send_float4(render_cmd_enc, sel_registerName("setBlendColorRed:green:blue:alpha:"), r, g, b, a);
}
