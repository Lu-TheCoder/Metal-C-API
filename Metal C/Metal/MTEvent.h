//
//  MTEvent.h
//  Metal C
//
//  Created by Lungile Maseko on 2025/06/20.
//
#pragma once
#include "MTUtils.h"

typedef void* MTEvent;
typedef void* MTSharedEvent;
typedef void* MTSharedEventListener;
typedef void* MTSharedEventHandle;
typedef void* MTDevice;
typedef void* MTString;
typedef void* MTDispatchQueue;

MT_INLINE MTSharedEventListener mt_shared_event_listener_new(void) {
    typedef MTSharedEventListener (*MTSharedEventListenerInitMsgSend)(void*, SEL);
    MTSharedEventListenerInitMsgSend msgSend = (MTSharedEventListenerInitMsgSend)objc_msgSend;

    Class cls = objc_getClass("MTLSharedEventListener");
    SEL sel = sel_getUid("init");

    id obj = ((id (*)(id, SEL))objc_msgSend)((id)cls, sel_getUid("alloc"));
    return msgSend(obj, sel);
}

MT_INLINE MTSharedEventListener mt_shared_event_listener_new_with_dispatch_queue(MTDispatchQueue queue) {
    typedef MTSharedEventListener (*MTSharedEventListenerInitWithQueueMsgSend)(void*, SEL, MTDispatchQueue);
    MTSharedEventListenerInitWithQueueMsgSend msgSend = (MTSharedEventListenerInitWithQueueMsgSend)objc_msgSend;

    Class cls = objc_getClass("MTLSharedEventListener");
    SEL sel = sel_getUid("initWithDispatchQueue:");

    id obj = ((id (*)(id, SEL))objc_msgSend)((id)cls, sel_getUid("alloc"));
    return msgSend(obj, sel, queue);
}

MT_INLINE MTSharedEventListener mt_shared_event_listener_shared(void) {
    typedef MTSharedEventListener (*MTSharedEventListenerSharedMsgSend)(Class, SEL);
    MTSharedEventListenerSharedMsgSend msgSend = (MTSharedEventListenerSharedMsgSend)objc_msgSend;

    Class cls = objc_getClass("MTLSharedEventListener");
    SEL sel = sel_getUid("sharedListener");
    return msgSend(cls, sel);
}

MT_INLINE MTDispatchQueue mt_shared_event_listener_get_dispatch_queue(MTSharedEventListener listener) {
    typedef MTDispatchQueue (*MTGetDispatchQueueMsgSend)(void*, SEL);
    MTGetDispatchQueueMsgSend msgSend = (MTGetDispatchQueueMsgSend)objc_msgSend;

    SEL sel = sel_getUid("dispatchQueue");
    return msgSend(listener, sel);
}

typedef void (^MTSharedEventNotificationBlock)(MTSharedEvent event, uint64_t value);

MT_INLINE void mt_shared_event_notify_listener(
    MTSharedEvent event,
    MTSharedEventListener listener,
    uint64_t value,
    MTSharedEventNotificationBlock block
) {
    typedef void (*MTNotifyListenerMsgSend)(void*, SEL, MTSharedEventListener, uint64_t, MTSharedEventNotificationBlock);
    MTNotifyListenerMsgSend msgSend = (MTNotifyListenerMsgSend)objc_msgSend;

    SEL sel = sel_getUid("notifyListener:atValue:block:");
    msgSend(event, sel, listener, value, block);
}

MT_INLINE MTSharedEventHandle mt_shared_event_new_shared_handle(MTSharedEvent event) {
    typedef MTSharedEventHandle (*MTNewSharedHandleMsgSend)(void*, SEL);
    MTNewSharedHandleMsgSend msgSend = (MTNewSharedHandleMsgSend)objc_msgSend;

    SEL sel = sel_getUid("newSharedEventHandle");
    return msgSend(event, sel);
}

MT_INLINE bool mt_shared_event_wait_until_signaled(MTSharedEvent event, uint64_t value, uint64_t timeout_ms) {
    typedef bool (*MTWaitMsgSend)(void*, SEL, uint64_t, uint64_t);
    MTWaitMsgSend msgSend = (MTWaitMsgSend)objc_msgSend;

    SEL sel = sel_getUid("waitUntilSignaledValue:timeoutMS:");
    return msgSend(event, sel, value, timeout_ms);
}

MT_INLINE uint64_t mt_shared_event_get_signaled_value(MTSharedEvent event) {
    typedef uint64_t (*MTGetSignaledValueMsgSend)(void*, SEL);
    MTGetSignaledValueMsgSend msgSend = (MTGetSignaledValueMsgSend)objc_msgSend;

    SEL sel = sel_getUid("signaledValue");
    return msgSend(event, sel);
}

MT_INLINE void mt_shared_event_set_signaled_value(MTSharedEvent event, uint64_t value) {
    typedef void (*MTSetSignaledValueMsgSend)(void*, SEL, uint64_t);
    MTSetSignaledValueMsgSend msgSend = (MTSetSignaledValueMsgSend)objc_msgSend;

    SEL sel = sel_getUid("setSignaledValue:");
    msgSend(event, sel, value);
}

MT_INLINE MTDevice mt_event_get_device(MTEvent event) {
    typedef MTDevice (*MTGetDeviceMsgSend)(void*, SEL);
    MTGetDeviceMsgSend msgSend = (MTGetDeviceMsgSend)objc_msgSend;

    SEL sel = sel_getUid("device");
    return msgSend(event, sel);
}

MT_INLINE MTString mt_event_get_label(MTEvent event) {
    typedef MTString (*MTGetLabelMsgSend)(void*, SEL);
    MTGetLabelMsgSend msgSend = (MTGetLabelMsgSend)objc_msgSend;

    SEL sel = sel_getUid("label");
    return msgSend(event, sel);
}

MT_INLINE void mt_event_set_label(MTEvent event, MTString label) {
    SEL sel = sel_getUid("setLabel:");
    id str = ((id (*)(Class, SEL, const char*))objc_msgSend)(
           objc_getClass("NSString"),
           sel_getUid("stringWithUTF8String:"),
           label);
    ((void (*)(id, SEL, id))objc_msgSend)((id)event, sel, str);
}

MT_INLINE MTString mt_shared_event_handle_get_label(MTSharedEventHandle handle) {
    SEL sel = sel_registerName("label");
    return ((MTString (*)(id, SEL))objc_msgSend)((id)handle, sel);
}
