//
//  MTBuffer.h
//  Metal C
//
//  Created by Lungile Maseko on 2024/04/29.
//

#pragma once
#include "MTFoundation/defines.h"
#include "MTTypes.h"

typedef void* MTDevice;
typedef void* MTTexture;
typedef void* MTTextureDescriptor;
typedef void* MTBuffer;
typedef void* MTString;

// ----------- Getter: length -----------
MT_INLINE unsigned long mt_buffer_get_length(MTBuffer buffer) {
    return MT_MSG_SEND(NSUInteger, buffer, MT_SEL("length"));
}

// ----------- Getter: contents -----------
MT_INLINE void* mt_buffer_get_contents(MTBuffer buffer) {
    return MT_MSG_SEND(void*, buffer, MT_SEL("contents"));
}

// ----------- Method: didModifyRange -----------
MT_INLINE void mt_buffer_did_modify_range(MTBuffer buffer, MTRange range) {
    ((void (*)(id, SEL, MTRange))objc_msgSend)((id)buffer, MT_SEL("didModifyRange:"), range);
}

// ----------- Method: newTextureWithDescriptor:offset:bytesPerRow -----------
MT_INLINE MTTexture mt_buffer_new_texture(MTBuffer buffer, MTTextureDescriptor descriptor, NSUInteger offset, NSUInteger bytesPerRow) {
    return MT_MSG_SEND_3(id, buffer, MT_SEL("newTextureWithDescriptor:offset:bytesPerRow:"), id, descriptor, NSUInteger, offset, NSUInteger, bytesPerRow);
}

// ----------- Method: addDebugMarker:range: -----------
MT_INLINE void mt_buffer_add_debug_marker(MTBuffer buffer, MTString marker, MTRange range) {
    ((void (*)(id, SEL, id, MTRange))objc_msgSend)((id)buffer, MT_SEL("addDebugMarker:range:"), (id)marker, range);
}

// ----------- Method: removeAllDebugMarkers -----------
MT_INLINE void mt_buffer_remove_all_debug_markers(MTBuffer buffer) {
    MT_MSG_SEND(void, buffer, MT_SEL("removeAllDebugMarkers"));
}

// ----------- Getter: remoteStorageBuffer -----------
MT_INLINE MTBuffer mt_buffer_get_remote_storage_buffer(MTBuffer buffer) {
    return MT_MSG_SEND(id, buffer, MT_SEL("remoteStorageBuffer"));
}

// ----------- Method: newRemoteBufferViewForDevice -----------
MT_INLINE MTBuffer mt_buffer_new_remote_buffer_view(MTBuffer buffer, MTDevice device) {
    return MT_MSG_SEND_1(id, buffer, MT_SEL("newRemoteBufferViewForDevice:"), id, device);
}

// ----------- Getter: gpuAddress -----------
MT_INLINE uint64_t mt_buffer_get_gpu_address(MTBuffer buffer) {
    return MT_MSG_SEND(uint64_t, buffer, MT_SEL("gpuAddress"));
}
