//
//  MT4LibraryFunctionDescriptor.h
//  Metal C
//
//  Created by Lungile Maseko on 2025/06/21.
//
#pragma once

typedef void* MT4LibraryFunctionDescriptor;
typedef void* MTLibrary;

MT_INLINE MT4LibraryFunctionDescriptor mt4_library_function_descriptor_create(void) {
    // Get the class
    Class cls = objc_getClass("MTL4LibraryFunctionDescriptor");
    if (!cls) return NULL;

    // Allocate the object
    id obj = ((id (*)(Class, SEL))objc_msgSend)(cls, sel_getUid("alloc"));
    if (!obj) return NULL;

    // Initialize the object
    obj = ((id (*)(id, SEL))objc_msgSend)(obj, sel_getUid("init"));
    return obj;
}

/// Get name (returns NSString*, caller handles cast if needed)
MT_INLINE const char* mt4_library_function_descriptor_get_name(MT4LibraryFunctionDescriptor desc) {
    if (!desc) return NULL;

    // Get NSString* via objc_msgSend
    id nsName = ((id (*)(void*, SEL))objc_msgSend)(
        desc,
        sel_getUid("name")
    );

    if (!nsName) return NULL;

    // Get UTF8String (const char*) via objc_msgSend
    const char* cstr = ((const char* (*)(id, SEL))objc_msgSend)(
        nsName,
        sel_getUid("UTF8String")
    );

    return cstr;
}

/// Set name from const char*
MT_INLINE void mt4_library_function_descriptor_set_name(MT4LibraryFunctionDescriptor desc, const char* name) {
    if (!desc || !name) return;

    // Convert const char* to NSString* manually without @"" or [NSString ...]
    id nsName = ((id (*)(Class, SEL, const char*))objc_msgSend)(
        (Class)objc_getClass("NSString"),
        sel_getUid("stringWithUTF8String:"),
        name
    );

    ((void (*)(void*, SEL, id))objc_msgSend)(
        desc,
        sel_getUid("setName:"),
        nsName
    );
}

/// Get library
MT_INLINE MTLibrary mt4_library_function_descriptor_get_library(MT4LibraryFunctionDescriptor desc) {
    if (!desc) return nil;
    return ((MTLibrary (*)(void*, SEL))objc_msgSend)(
        desc,
        sel_getUid("library")
    );
}

/// Set library
MT_INLINE void mt4_library_function_descriptor_set_library(MT4LibraryFunctionDescriptor desc, MTLibrary lib) {
    if (!desc) return;
    ((void (*)(void*, SEL, MTLibrary))objc_msgSend)(
        desc,
        sel_getUid("setLibrary:"),
        lib
    );
}

