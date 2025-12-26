//
//  MTFunctionDescriptor.h
//  Metal C
//
//  Created by Lungile Maseko on 2025/06/06.
//
#pragma once
#include "MTUtils.h"

typedef void* MTBinaryArchive;
typedef void* MTFunctionDescriptor;
typedef void* MTIntersectionFunctionDescriptor;
typedef void* MTFunctionConstantValues;

typedef enum MTFunctionOptions {
    MTFunctionOptionNone = 0,
    MTFunctionOptionCompileToBinary = 1 << 0,
    MTFunctionOptionStoreFunctionInMetalPipelinesScript = 1 << 1,
    MTFunctionOptionFailOnBinaryArchiveMiss = 1 << 2,
} MTFunctionOptions;

MT_INLINE MTFunctionDescriptor mt_function_descriptor_create(void) {
    return MT_MSG_SEND_CLASS(id, MT_CLASS("MTLFunctionDescriptor"), MT_SEL("functionDescriptor"));
}

MT_INLINE void mt_function_descriptor_set_name(MTFunctionDescriptor desc, const char* name) {
    id str = MT_MSG_SEND_CLASS_1(id, MT_CLASS("NSString"), MT_SEL("stringWithUTF8String:"), const char*, name);
    MT_MSG_SEND_1(void, desc, MT_SEL("setName:"), id, str);
}

MT_INLINE const char* mt_function_descriptor_get_name(MTFunctionDescriptor desc) {
    id ns_str = MT_MSG_SEND(id, desc, MT_SEL("name"));
    if (!ns_str) return NULL;
    return MT_MSG_SEND(const char*, ns_str, MT_SEL("UTF8String"));
}

MT_INLINE void mt_function_descriptor_set_specialized_name(MTFunctionDescriptor desc, const char* name) {
    id str = MT_MSG_SEND_CLASS_1(id, MT_CLASS("NSString"), MT_SEL("stringWithUTF8String:"), const char*, name);
    MT_MSG_SEND_1(void, desc, MT_SEL("setSpecializedName:"), id, str);
}

MT_INLINE const char* mt_function_descriptor_get_specialized_name(MTFunctionDescriptor desc) {
    id ns_str = MT_MSG_SEND(id, desc, MT_SEL("specializedName"));
    if (!ns_str) return NULL;
    return MT_MSG_SEND(const char*, ns_str, MT_SEL("UTF8String"));
}

MT_INLINE void mt_function_descriptor_set_constant_values(MTFunctionDescriptor desc, MTFunctionConstantValues values) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setConstantValues:"), id, values);
}

MT_INLINE MTFunctionConstantValues mt_function_descriptor_get_constant_values(MTFunctionDescriptor desc) {
    return MT_MSG_SEND(id, desc, MT_SEL("constantValues"));
}

MT_INLINE void mt_function_descriptor_set_options(MTFunctionDescriptor desc, MTFunctionOptions options) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setOptions:"), MTFunctionOptions, options);
}

MT_INLINE MTFunctionOptions mt_function_descriptor_get_options(MTFunctionDescriptor desc) {
    return MT_MSG_SEND(MTFunctionOptions, desc, MT_SEL("options"));
}

MT_INLINE void mt_function_descriptor_set_binary_archives(MTFunctionDescriptor desc, MTBinaryArchive archives_array) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setBinaryArchives:"), id, archives_array);
}

MT_INLINE id mt_function_descriptor_get_binary_archives(MTFunctionDescriptor desc) {
    return MT_MSG_SEND(id, desc, MT_SEL("binaryArchives"));
}

MT_INLINE MTIntersectionFunctionDescriptor mt_intersection_function_descriptor_create(void) {
    return MT_MSG_SEND_CLASS(id, MT_CLASS("MTLIntersectionFunctionDescriptor"), MT_SEL("functionDescriptor"));
}

// MARK: Helper Functions

MT_INLINE id mt_nsarray_from_binary_archives(MTBinaryArchive* archives, NSUInteger count) {
    return MT_MSG_SEND_CLASS_2(id, MT_CLASS("NSArray"), MT_SEL("arrayWithObjects:count:"), const id*, (const id*)archives, NSUInteger, count);
}
