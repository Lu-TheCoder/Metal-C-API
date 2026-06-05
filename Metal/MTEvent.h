//
//  MTEvent.h
//  Metal C
//
//  MTEvent / MTSharedEvent accessors.
//
//  Create events via the device:
//    MTEvent       e  = mt_device_create_event(device);        // GPU-only
//    MTSharedEvent se = mt_device_create_shared_event(device);  // CPU + GPU
//  Queue GPU waits/signals with mt_command_buffer_encode_wait_for_event /
//  _signal_event (see MTCommandBuffer.h). The functions below let the CPU
//  observe and drive an MTSharedEvent's value directly.
//

#pragma once
#include "MTFoundation/defines.h"
#include <stdint.h>

// Current value of a shared event (the highest value signalled so far).
MT_INLINE uint64_t mt_shared_event_get_signaled_value(MTSharedEvent event) {
    return MT_MSG_SEND(uint64_t, event, MT_SEL("signaledValue"));
}

// Set the value from the CPU. Setting it can release GPU waiters blocked on
// a value <= this one.
MT_INLINE void mt_shared_event_set_signaled_value(MTSharedEvent event, uint64_t value) {
    MT_MSG_SEND_1(void, event, MT_SEL("setSignaledValue:"), uint64_t, value);
}

// Block the CPU until the event's signaledValue >= `value`, or `timeout_ms`
// elapses. Returns true if the value was reached, false on timeout.
MT_INLINE bool mt_shared_event_wait_until_signaled_value(MTSharedEvent event, uint64_t value, uint64_t timeout_ms) {
    return MT_MSG_SEND_2(bool, event, MT_SEL("waitUntilSignaledValue:timeoutMS:"), uint64_t, value, uint64_t, timeout_ms);
}

// The device that created the event.
MT_INLINE MTDevice mt_event_get_device(MTEvent event) {
    return MT_MSG_SEND(void*, event, MT_SEL("device"));
}
