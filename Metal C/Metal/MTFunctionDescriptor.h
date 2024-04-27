//
//  MTFunctionDescriptor.h
//  Metal C
//
//  Created by Lungile Maseko on 2025/06/06.
//
#pragma once

typedef void* MTBinaryArchive;
typedef void* MTFunctionDescriptor;
typedef void* MTIntersectionFunctionDescriptor;

typedef enum MTFunctionOptions {
    /**
     * @brief Default usage
     */
    MTFunctionOptionNone = 0,
    MTFunctionOptionCompileToBinary = 1 << 0,
    MTFunctionOptionStoreFunctionInMetalPipelinesScript = 1 << 1,
    MTFunctionOptionFailOnBinaryArchiveMiss = 1 << 2,
} MTFunctionOptions;

MT_INLINE MTFunctionDescriptor mt_function_descriptor_create(void) {
    Class cls = objc_getClass("MTLFunctionDescriptor");
    SEL sel = sel_getUid("functionDescriptor");
    return ((id (*)(Class, SEL))objc_msgSend)(cls, sel);
}

MT_INLINE void mt_function_descriptor_set_name(MTFunctionDescriptor desc, const char* name) {
    SEL sel = sel_getUid("setName:");
    id str = ((id (*)(Class, SEL, const char*))objc_msgSend)(
        objc_getClass("NSString"),
        sel_getUid("stringWithUTF8String:"),
        name
    );
    ((void (*)(id, SEL, id))objc_msgSend)((id)desc, sel, str);
}

MT_INLINE const char* mt_function_descriptor_get_name(MTFunctionDescriptor desc) {
    SEL sel_name = sel_getUid("name");
    id ns_str = ((id (*)(id, SEL))objc_msgSend)((id)desc, sel_name);
    if (!ns_str) return NULL;

    SEL sel_utf8 = sel_getUid("UTF8String");
    const char* cstr = ((const char* (*)(id, SEL))objc_msgSend)(ns_str, sel_utf8);
    return cstr;
}

MT_INLINE void mt_function_descriptor_set_specialized_name(MTFunctionDescriptor desc, const char* name) {
    SEL sel = sel_getUid("setSpecializedName:");
    id str = ((id (*)(Class, SEL, const char*))objc_msgSend)(
        objc_getClass("NSString"),
        sel_getUid("stringWithUTF8String:"),
        name
    );
    ((void (*)(id, SEL, id))objc_msgSend)((id)desc, sel, str);
}

MT_INLINE const char* mt_function_descriptor_get_specialized_name(MTFunctionDescriptor desc) {
    SEL sel_spec_name = sel_getUid("specializedName");
    id ns_str = ((id (*)(id, SEL))objc_msgSend)((id)desc, sel_spec_name);
    if (!ns_str) return NULL;

    SEL sel_utf8 = sel_getUid("UTF8String");
    const char* cstr = ((const char* (*)(id, SEL))objc_msgSend)(ns_str, sel_utf8);
    return cstr;
}

MT_INLINE void mt_function_descriptor_set_constant_values(MTFunctionDescriptor desc, MTFunctionConstantValues values) {
    SEL sel = sel_getUid("setConstantValues:");
    ((void (*)(id, SEL, id))objc_msgSend)((id)desc, sel, (id)values);
}

MT_INLINE MTFunctionConstantValues mt_function_descriptor_get_constant_values(MTFunctionDescriptor desc) {
    SEL sel = sel_getUid("constantValues");
    return (MTFunctionConstantValues)((id (*)(id, SEL))objc_msgSend)((id)desc, sel);
}

MT_INLINE void mt_function_descriptor_set_options(MTFunctionDescriptor desc, MTFunctionOptions options) {
    SEL sel = sel_getUid("setOptions:");
    ((void (*)(id, SEL, MTFunctionOptions))objc_msgSend)((id)desc, sel, options);
}

MT_INLINE MTFunctionOptions mt_function_descriptor_get_options(MTFunctionDescriptor desc) {
    SEL sel = sel_getUid("options");
    return ((MTFunctionOptions (*)(id, SEL))objc_msgSend)((id)desc, sel);
}

MT_INLINE void mt_function_descriptor_set_binary_archives(MTFunctionDescriptor desc, MTBinaryArchive archives_array) {
    SEL sel = sel_getUid("setBinaryArchives:");
    ((void (*)(id, SEL, id))objc_msgSend)((id)desc, sel, archives_array);
}

MT_INLINE id mt_function_descriptor_get_binary_archives(MTFunctionDescriptor desc) {
    SEL sel = sel_getUid("binaryArchives");
    return ((id (*)(id, SEL))objc_msgSend)((id)desc, sel);
}

MT_INLINE MTIntersectionFunctionDescriptor mt_intersection_function_descriptor_create(void) {
    Class cls = objc_getClass("MTLIntersectionFunctionDescriptor");
    SEL sel = sel_getUid("functionDescriptor");
    return ((id (*)(Class, SEL))objc_msgSend)(cls, sel);
}

// MARK: Helper FUnctions
// FIXME:
// Needs refactoring or be placed elsewhere? or maybe build NSArray Wrapper?

MT_INLINE id mt_nsarray_from_binary_archives(MTBinaryArchive* archives, NSUInteger count) {
    Class NSArrayClass = objc_getClass("NSArray");
    SEL selWithObjects = sel_getUid("arrayWithObjects:count:");

    return ((id (*)(Class, SEL, const id*, NSUInteger))objc_msgSend)(
        NSArrayClass, selWithObjects, (const id*)archives, count
    );
}
