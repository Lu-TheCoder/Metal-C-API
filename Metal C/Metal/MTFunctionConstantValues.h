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
    return MT_MSG_SEND_CLASS(id, MT_CLASS("MTLFunctionConstantValues"), MT_SEL("new"));
}

MT_INLINE void mt_function_constant_values_set_value_at_index(MTFunctionConstantValues fcv, const void* value, MTDataType type, NSUInteger index) {
    MT_MSG_SEND_3(void, fcv, MT_SEL("setConstantValue:type:atIndex:"), const void*, value, MTDataType, type, NSUInteger, index);
}

// Struct arg - explicit cast needed
MT_INLINE void mt_function_constant_values_set_values_with_range(MTFunctionConstantValues fcv, const void* values, MTDataType type, MTRange range) {
    ((void (*)(id, SEL, const void*, MTDataType, MTRange))objc_msgSend)((id)fcv, MT_SEL("setConstantValues:type:withRange:"), values, type, range);
}

MT_INLINE void mt_function_constant_values_set_value_with_name(MTFunctionConstantValues fcv, const void* value, MTDataType type, MTString name) {
    MT_MSG_SEND_3(void, fcv, MT_SEL("setConstantValue:type:withName:"), const void*, value, MTDataType, type, id, name);
}

MT_INLINE void mt_function_constant_values_reset(MTFunctionConstantValues fcv) {
    MT_MSG_SEND(void, fcv, MT_SEL("reset"));
}
