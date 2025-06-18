//
//  NSString.h
//  Metal C
//
//  Created by Lungile Maseko on 2024/06/02.
//

#pragma once
#include "defines.h"

typedef enum MTStringEncoding {
    MTASCIIStringEncoding = 1,
    MTNEXTSTEPStringEncoding = 2,
    MTJapaneseEUCStringEncoding = 3,
    MTUTF8StringEncoding = 4,
    MTISOLatin1StringEncoding = 5,
    MTSymbolStringEncoding = 6,
    MTNonLossyASCIIStringEncoding = 7,
    MTShiftJISStringEncoding = 8,
    MTISOLatin2StringEncoding = 9,
    MTUnicodeStringEncoding = 10,
    MTWindowsCP1251StringEncoding = 11,
    MTWindowsCP1252StringEncoding = 12,
    MTWindowsCP1253StringEncoding = 13,
    MTWindowsCP1254StringEncoding = 14,
    MTWindowsCP1250StringEncoding = 15,
    MTISO2022JPStringEncoding = 21,
    MTMacOSRomanStringEncoding = 30,

    MTUTF16StringEncoding = MTUnicodeStringEncoding,

    MTUTF16BigEndianStringEncoding = 0x90000100,
    MTUTF16LittleEndianStringEncoding = 0x94000100,

    MTUTF32StringEncoding = 0x8c000100,
    MTUTF32BigEndianStringEncoding = 0x98000100,
    MTUTF32LittleEndianStringEncoding = 0x9c000100
}MTStringEncoding;

//typedef enum NSStringCompareOptions {
//    
//}NSStringCompareOptions;

typedef void* MTString;

/// Converts a C string (UTF-8) to an NSString*
MT_INLINE MTString mt_string_from_utf8(const char *utf8) {
    Class nsStringClass = objc_getClass("NSString");
    SEL sel = sel_registerName("stringWithUTF8String:");
    typedef id (*MsgSendFn)(id, SEL, const char *);
    return ((MsgSendFn)objc_msgSend)((id)nsStringClass, sel, utf8);
}

/// Converts NSString* to UTF-8 C string
MT_INLINE const char* mt_string_to_utf8(MTString str) {
    SEL sel = sel_registerName("UTF8String");
    typedef const char* (*MsgSendFn)(id, SEL);
    return ((MsgSendFn)objc_msgSend)(str, sel);
}

MT_INLINE id mt_nsstring_create(const char* cstr) {
    Class nsStringClass = objc_getClass("NSString");
    SEL initWithUTF8Sel = sel_getUid("initWithUTF8String:");
    id nsStringAlloc = ((id (*)(id, SEL))objc_msgSend)((id)nsStringClass, sel_getUid("alloc"));
    id nsString = ((id (*)(id, SEL, const char*))objc_msgSend)(nsStringAlloc, initWithUTF8Sel, cstr);
    return nsString;
}

MT_INLINE void mt_nsstring_release(id nsString) {
    SEL releaseSel = sel_getUid("release");
    ((void (*)(id, SEL))objc_msgSend)(nsString, releaseSel);
}


// TODO: REMOVE THIS AND PLACE IT ELSEWHERE
MT_INLINE void mt_object_set_label(void* metal_object, const char* label) {
    if (!metal_object || !label) return;

    SEL setLabelSel = sel_getUid("setLabel:");
    id nsLabel = mt_nsstring_create(label);

    ((void (*)(id, SEL, id))objc_msgSend)((id)metal_object, setLabelSel, nsLabel);

    mt_nsstring_release(nsLabel);
}
