//
//  NSError.h
//  Metal C
//
//  Created by Lungile Maseko on 2024/06/02.
//

#pragma once
#include "defines.h"

typedef void* MTError;

// Code: - (NSInteger)code
MT_INLINE long mt_error_get_code(MTError error) {
    SEL sel = sel_registerName("code");
    typedef long (*MsgSendFn)(id, SEL);
    return ((MsgSendFn)objc_msgSend)(error, sel);
}

MT_INLINE const char* mt_error_get_localized_description(MTError error) {
    SEL sel = sel_registerName("localizedDescription");
    id (*msgSendObj)(id, SEL) = (id (*)(id, SEL))objc_msgSend;
    id nsStr = msgSendObj((id)error, sel);

    if (!nsStr) return NULL;

    SEL utf8Sel = sel_registerName("UTF8String");
    const char* (*msgSendUTF8)(id, SEL) = (const char* (*)(id, SEL))objc_msgSend;
    return msgSendUTF8(nsStr, utf8Sel);
}

MT_INLINE const char* mt_error_get_localized_recovery_suggestion(MTError error) {
    SEL sel = sel_registerName("localizedRecoverySuggestion");
    id (*msgSendObj)(id, SEL) = (id (*)(id, SEL))objc_msgSend;
    id nsStr = msgSendObj((id)error, sel);

    if (!nsStr) return NULL;

    SEL utf8Sel = sel_registerName("UTF8String");
    const char* (*msgSendUTF8)(id, SEL) = (const char* (*)(id, SEL))objc_msgSend;
    return msgSendUTF8(nsStr, utf8Sel);
}

MT_INLINE const char* mt_error_get_localized_failure_reason(MTError error) {
    SEL sel = sel_registerName("localizedFailureReason");
    id (*msgSendObj)(id, SEL) = (id (*)(id, SEL))objc_msgSend;
    id nsStr = msgSendObj((id)error, sel);

    if (!nsStr) return NULL;

    SEL utf8Sel = sel_registerName("UTF8String");
    const char* (*msgSendUTF8)(id, SEL) = (const char* (*)(id, SEL))objc_msgSend;
    return msgSendUTF8(nsStr, utf8Sel);
}
