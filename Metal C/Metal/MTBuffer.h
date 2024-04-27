//
//  MTBuffer.h
//  Metal C
//
//  Created by Lungile Maseko on 2024/04/29.
//

#pragma once

#include <objc/message.h>
#include <objc/objc.h>
#include "MTTypes.h"

typedef void* MTDevice;
typedef void* MTTexture;
typedef void* MTTextureDescriptor;
typedef void* MTBuffer;
typedef void* MTString;

// ----------- Getter: length -----------
MT_INLINE unsigned long mt_buffer_get_length(MTBuffer buffer) {
    SEL sel = sel_getUid("length");
    typedef NSUInteger (*FuncType)(void*, SEL);
    return ((FuncType)objc_msgSend)(buffer, sel);
}

// ----------- Getter: contents -----------
MT_INLINE void* mt_buffer_get_contents(MTBuffer buffer) {
    SEL sel = sel_getUid("contents");
    typedef void* (*FuncType)(void*, SEL);
    return ((FuncType)objc_msgSend)(buffer, sel);
}

// ----------- Method: didModifyRange -----------
MT_INLINE void mt_buffer_did_modify_range(MTBuffer buffer, MTRange range) {
    SEL sel = sel_getUid("didModifyRange:");
    typedef void (*FuncType)(void*, SEL, MTRange);
    ((FuncType)objc_msgSend)(buffer, sel, range);
}

// ----------- Method: newTextureWithDescriptor:offset:bytesPerRow -----------
MT_INLINE MTTexture mt_buffer_new_texture(MTBuffer buffer, MTTextureDescriptor descriptor, NSUInteger offset, NSUInteger bytesPerRow) {
    SEL sel = sel_getUid("newTextureWithDescriptor:offset:bytesPerRow:");
    typedef MTTexture (*FuncType)(void*, SEL, MTTextureDescriptor, NSUInteger, NSUInteger);
    return ((FuncType)objc_msgSend)(buffer, sel, descriptor, offset, bytesPerRow);
}

// ----------- Method: addDebugMarker:range: -----------
MT_INLINE void mt_buffer_add_debug_marker(MTBuffer buffer, MTString marker, MTRange range) {
    SEL sel = sel_getUid("addDebugMarker:range:");
    typedef void (*FuncType)(void*, SEL, MTString, MTRange);
    ((FuncType)objc_msgSend)(buffer, sel, marker, range);
}

// ----------- Method: removeAllDebugMarkers -----------
MT_INLINE void mt_buffer_remove_all_debug_markers(MTBuffer buffer) {
    SEL sel = sel_getUid("removeAllDebugMarkers");
    typedef void (*FuncType)(void*, SEL);
    ((FuncType)objc_msgSend)(buffer, sel);
}

// ----------- Getter: remoteStorageBuffer -----------
MT_INLINE MTBuffer mt_buffer_get_remote_storage_buffer(MTBuffer buffer) {
    SEL sel = sel_getUid("remoteStorageBuffer");
    typedef MTBuffer (*FuncType)(void*, SEL);
    return ((FuncType)objc_msgSend)(buffer, sel);
}

// ----------- Method: newRemoteBufferViewForDevice -----------
MT_INLINE MTBuffer mt_buffer_new_remote_buffer_view(MTBuffer buffer, MTDevice device) {
    SEL sel = sel_getUid("newRemoteBufferViewForDevice:");
    typedef MTBuffer (*FuncType)(void*, SEL, MTDevice);
    return ((FuncType)objc_msgSend)(buffer, sel, device);
}

// ----------- Getter: gpuAddress -----------
MT_INLINE uint64_t mt_buffer_get_gpu_address(MTBuffer buffer) {
    SEL sel = sel_getUid("gpuAddress");
    typedef uint64_t (*FuncType)(void*, SEL);
    return ((FuncType)objc_msgSend)(buffer, sel);
}
