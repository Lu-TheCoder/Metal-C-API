//
//  NSError.h
//  Metal C
//
//  Created by Lungile Maseko on 2024/06/02.
//

#pragma once

typedef void* MTError;

// Code: - (NSInteger)code
long mt_error_get_code(MTError error) {
    SEL sel = sel_registerName("code");
    typedef long (*MsgSendFn)(id, SEL);
    return ((MsgSendFn)objc_msgSend)(error, sel);
}

// Description: - (NSString *)localizedDescription
const char* mt_error_get_localized_description(MTError error) {
    SEL sel = sel_registerName("localizedDescription");
    typedef id (*MsgSendFn)(id, SEL);
    id nsStr = ((MsgSendFn)objc_msgSend)(error, sel);
    return ns_toString(nsStr); // Assumes ns_toString handles NSString* to UTF-8
}

// Recovery suggestion: - (NSString *)localizedRecoverySuggestion
const char* mt_error_get_localized_recovery_suggestion(MTError error) {
    SEL sel = sel_registerName("localizedRecoverySuggestion");
    typedef id (*MsgSendFn)(id, SEL);
    id nsStr = ((MsgSendFn)objc_msgSend)(error, sel);
    return ns_toString(nsStr);
}

// Failure reason: - (NSString *)localizedFailureReason
const char* mt_error_get_localized_failure_reason(MTError error) {
    SEL sel = sel_registerName("localizedFailureReason");
    typedef id (*MsgSendFn)(id, SEL);
    id nsStr = ((MsgSendFn)objc_msgSend)(error, sel);
    return ns_toString(nsStr);
}
