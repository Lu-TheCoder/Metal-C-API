//
//  MTBuffer.h
//  Metal C
//
//  Created by Lungile Maseko on 2024/04/29.
//

#pragma once
#include "MTDevice.h"
#include "../ObjectiveCCore/Objectivec.h"
#include "MTResource.h"

typedef void* MTBuffer;

MT_INLINE void* mt_buffer_get_contents(MTBuffer* buffer) {
    return ms_send_sel(buffer, sel_getUid("contents"));
}

MT_INLINE void mt_buffer_add_debug_marker(MTBuffer buffer, const char* marker, MTRange range) {
    id nsMarker = mt_nsstring_create(marker);
    SEL sel = sel_getUid("addDebugMarker:range:");
    typedef void (*MsgSendFunc)(id, SEL, id, MTRange);
    MsgSendFunc func = (MsgSendFunc)objc_msgSend;
    func((id)buffer, sel, nsMarker, range);
    // Release nsMarker if using manual ref counting, otherwise ARC handles it
    mt_nsstring_release(nsMarker);
}

MT_INLINE void mt_buffer_remove_all_debug_markers(MTBuffer buffer) {
    SEL sel = sel_getUid("removeAllDebugMarkers");
    typedef void (*MsgSendFunc)(id, SEL);
    MsgSendFunc func = (MsgSendFunc)objc_msgSend;
    func((id)buffer, sel);
}
