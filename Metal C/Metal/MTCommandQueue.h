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


MTCommandQueue* mt_device_commandQueue_new(MTDevice* device){
    return (MTCommandQueue*)ms_send(device, sel_getUid("newCommandQueue"));
}



//FIXME: Crashes
//MTCommandQueue* mtNewCommandQueueWithMaxCommandBufferCount(MTDevice* device, uintptr_t count){
//    return (MTCommandQueue*)ms_send(device, sel_getUid("newCommandQueueWithMaxCommandBufferCount:"), count);
//}
