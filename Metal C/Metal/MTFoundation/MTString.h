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
} MTStringEncoding;

typedef void* MTString;

/// Converts a C string (UTF-8) to an NSString*
MT_INLINE MTString mt_string_from_utf8(const char *utf8) {
    return MT_MSG_SEND_CLASS_1(id, MT_CLASS("NSString"), MT_SEL("stringWithUTF8String:"), const char*, utf8);
}

/// Converts NSString* to UTF-8 C string
MT_INLINE const char* mt_string_to_utf8(MTString str) {
    return MT_MSG_SEND(const char*, str, MT_SEL("UTF8String"));
}

MT_INLINE id mt_nsstring_create(const char* cstr) {
    id alloc = MT_MSG_SEND_CLASS(id, MT_CLASS("NSString"), MT_SEL("alloc"));
    return MT_MSG_SEND_1(id, alloc, MT_SEL("initWithUTF8String:"), const char*, cstr);
}

MT_INLINE void mt_nsstring_release(id nsString) {
    MT_RELEASE(nsString);
}

// TODO: REMOVE THIS AND PLACE IT ELSEWHERE
MT_INLINE void mt_object_set_label(void* metal_object, const char* label) {
    if (!metal_object || !label) return;
    id nsLabel = mt_nsstring_create(label);
    MT_MSG_SEND_1(void, metal_object, MT_SEL("setLabel:"), id, nsLabel);
    mt_nsstring_release(nsLabel);
}
