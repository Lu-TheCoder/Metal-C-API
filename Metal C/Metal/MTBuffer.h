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

typedef void MTBuffer;

MT_INLINE void* mt_buffer_get_contents(MTBuffer* buffer) {
    return ms_send_sel(buffer, sel_registerName("contents"));
}
