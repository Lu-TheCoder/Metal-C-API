//
//  MTCommandQueue.h
//  Metal C
//
//  Created by Lungile Maseko on 2024/04/29.
//

#pragma once

#include "MTDevice.h"
#include "../ObjectiveCCore/Objectivec.h"

typedef void MTCommandQueue;

MT_INLINE MTCommandQueue* mt_device_create_command_queue(MTDevice* device) {
    typedef void* (*MTNewCommandQueueMsgSend)(void*, SEL);
    MTNewCommandQueueMsgSend msgSend = (MTNewCommandQueueMsgSend)objc_msgSend;

    SEL sel = sel_getUid("newCommandQueue");
    return (MTCommandQueue*)msgSend(device, sel);
}

//FIXME: Crashes
//MTCommandQueue* mtNewCommandQueueWithMaxCommandBufferCount(MTDevice* device, uintptr_t count){
//    return (MTCommandQueue*)ms_send(device, sel_getUid("newCommandQueueWithMaxCommandBufferCount:"), count);
//}
