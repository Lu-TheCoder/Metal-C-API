//
//  MT4ArgumentTable.h
//  Metal C
//
//  MTL4ArgumentTable — the Metal 4 binding model. Instead of binding resources
//  slot-by-slot on the encoder (setVertexBuffer:atIndex: etc.), you fill an
//  argument table with GPU addresses / MTResourceIDs and bind the whole table
//  to the encoder for a set of shader stages (see mt4_render_command_encoder_set_argument_table).
//
//  Get the values to bind via:
//    MTGPUAddress  addr = mt_buffer_get_gpu_address(buffer);
//    MTResourceID  rid  = mt_texture_get_gpu_resource_id(texture);
//

#pragma once
#include "MTFoundation/defines.h"
#include "MTFoundation/MTString.h"  // mt_object_set_label
#include "MTTypes.h"                // NSUInteger, MTGPUAddress, MTResourceID

// ---- Descriptor ----------------------------------------------------------

MT_INLINE MT4ArgumentTableDescriptor mt4_argument_table_descriptor_create(void) {
    return MT_ALLOC_INIT("MTL4ArgumentTableDescriptor");
}

// Number of buffer binding slots (max 31).
MT_INLINE void mt4_argument_table_descriptor_set_max_buffer_bind_count(MT4ArgumentTableDescriptor desc, NSUInteger count) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setMaxBufferBindCount:"), NSUInteger, count);
}

// Number of texture binding slots (max 128).
MT_INLINE void mt4_argument_table_descriptor_set_max_texture_bind_count(MT4ArgumentTableDescriptor desc, NSUInteger count) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setMaxTextureBindCount:"), NSUInteger, count);
}

// Number of sampler-state binding slots (max 16).
MT_INLINE void mt4_argument_table_descriptor_set_max_sampler_state_bind_count(MT4ArgumentTableDescriptor desc, NSUInteger count) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setMaxSamplerStateBindCount:"), NSUInteger, count);
}

// Initialize all bindings to nil on creation.
MT_INLINE void mt4_argument_table_descriptor_set_initialize_bindings(MT4ArgumentTableDescriptor desc, bool initialize) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setInitializeBindings:"), BOOL, initialize);
}

// Reserve room for dynamic per-binding attribute strides (needed if you use
// mt4_argument_table_set_address_with_stride).
MT_INLINE void mt4_argument_table_descriptor_set_support_attribute_strides(MT4ArgumentTableDescriptor desc, bool support) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setSupportAttributeStrides:"), BOOL, support);
}

MT_INLINE void mt4_argument_table_descriptor_set_label(MT4ArgumentTableDescriptor desc, const char* label) {
    mt_object_set_label(desc, label);
}

// ---- Argument table (created via the device) -----------------------------

MT_INLINE MT4ArgumentTable mt4_device_create_argument_table(MTDevice device, MT4ArgumentTableDescriptor desc, MTError* outError) {
    return MT_MSG_SEND_2(void*, device, MT_SEL("newArgumentTableWithDescriptor:error:"), id, desc, MTError*, outError);
}

// ---- Bindings ------------------------------------------------------------

// Bind a buffer by GPU address to a buffer slot.
MT_INLINE void mt4_argument_table_set_address(MT4ArgumentTable table, MTGPUAddress gpu_address, NSUInteger index) {
    MT_MSG_SEND_2(void, table, MT_SEL("setAddress:atIndex:"), MTGPUAddress, gpu_address, NSUInteger, index);
}

// Bind a vertex buffer by GPU address with a dynamic attribute stride.
// (Descriptor must have supportAttributeStrides set.)
MT_INLINE void mt4_argument_table_set_address_with_stride(MT4ArgumentTable table, MTGPUAddress gpu_address, NSUInteger stride, NSUInteger index) {
    MT_MSG_SEND_3(void, table, MT_SEL("setAddress:attributeStride:atIndex:"), MTGPUAddress, gpu_address, NSUInteger, stride, NSUInteger, index);
}

// Bind a resource (by MTResourceID) to a buffer slot.
MT_INLINE void mt4_argument_table_set_resource(MT4ArgumentTable table, MTResourceID resource_id, NSUInteger index) {
    ((void (*)(id, SEL, MTResourceID, NSUInteger))objc_msgSend)(
        (id)table, MT_SEL("setResource:atBufferIndex:"), resource_id, index);
}

// Bind a texture (by MTResourceID) to a texture slot.
MT_INLINE void mt4_argument_table_set_texture(MT4ArgumentTable table, MTResourceID resource_id, NSUInteger index) {
    ((void (*)(id, SEL, MTResourceID, NSUInteger))objc_msgSend)(
        (id)table, MT_SEL("setTexture:atIndex:"), resource_id, index);
}

// Bind a sampler state (by MTResourceID) to a sampler slot.
MT_INLINE void mt4_argument_table_set_sampler_state(MT4ArgumentTable table, MTResourceID resource_id, NSUInteger index) {
    ((void (*)(id, SEL, MTResourceID, NSUInteger))objc_msgSend)(
        (id)table, MT_SEL("setSamplerState:atIndex:"), resource_id, index);
}
