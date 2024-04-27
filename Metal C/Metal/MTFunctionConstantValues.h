//
//  MTFunctionConstantValues.h
//  Metal C
//
//  Created by Lungile Maseko on 2025/06/06.
//
#pragma once
#include "MTArgument.h"

typedef void* MTFunctionConstantValues;

MT_INLINE MTFunctionConstantValues mt_function_constant_values_create(void) {
    Class cls = objc_getClass("MTLFunctionConstantValues");
    return (MTFunctionConstantValues)((id (*)(Class, SEL))objc_msgSend)(cls, sel_getUid("new"));
}

MT_INLINE void mt_function_constant_values_set_value_at_index(
    MTFunctionConstantValues fcv,
    const void* value,
    MTDataType type,
    NSUInteger index
) {
    ((void (*)(id, SEL, const void*, MTDataType, NSUInteger))objc_msgSend)(
        (id)fcv, sel_getUid("setConstantValue:type:atIndex:"), value, type, index
    );
}

MT_INLINE void mt_function_constant_values_set_values_with_range(
    MTFunctionConstantValues fcv,
    const void* values,
    MTDataType type,
    MTRange range
) {
    ((void (*)(id, SEL, const void*, MTDataType, MTRange))objc_msgSend)(
        (id)fcv, sel_getUid("setConstantValues:type:withRange:"), values, type, range
    );
}

MT_INLINE void mt_function_constant_values_set_value_with_name(
    MTFunctionConstantValues fcv,
    const void* value,
    MTDataType type,
    MTString name // MTString is assumed to be typedef'd to void*
) {
    ((void (*)(id, SEL, const void*, MTDataType, id))objc_msgSend)(
        (id)fcv, sel_getUid("setConstantValue:type:withName:"), value, type, (id)name
    );
}

MT_INLINE void mt_function_constant_values_reset(MTFunctionConstantValues fcv) {
    ((void (*)(id, SEL))objc_msgSend)((id)fcv, sel_getUid("reset"));
}
