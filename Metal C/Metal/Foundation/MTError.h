//
//  NSError.h
//  Metal C
//
//  Created by Lungile Maseko on 2024/06/02.
//

#pragma once

typedef void MTError;

MTError* mt_error_new(void){
    Class nsErrorClass = objc_getClass("NSError");
    return nsErrorClass;
}

long mt_error_get_code(MTError* error) {
    SEL sel = sel_registerName("code");
    return (long)ms_send(error, sel);
}

const char* mt_error_get_localized_description(MTError* error) {
    SEL sel = sel_registerName("localizedDescription");
    void* s = ms_send(error, sel);
    return ns_toString(s);
}

const char* mt_error_get_localized_recovery_suggestion(MTError* error) {
    SEL sel = sel_registerName("localizedRecoverySuggestion");
    return (const char*)ns_toString(ms_send(error, sel));
}

const char* mt_error_get_localized_failure_reason(MTError* error) {
    SEL sel = sel_registerName("localizedFailureReason");
    return (const char*)ns_toString(ms_send(error, sel));
}
