//
//  NSString.h
//  Metal C
//
//  Created by Lungile Maseko on 2024/06/02.
//

#pragma once

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

typedef void MTString;

MTString* mt_string_new(void){
    Class _class = objc_getClass("NSString");
    SEL allocSel = sel_registerName("alloc");
    
    void* _nsString = ms_send(_class, allocSel);
    SEL initSel = sel_registerName("init");
    return ms_send(_nsString, initSel);
}

void* (*ms_send_string_encoding)(void*, SEL, const char*, unsigned long) = (void* (*)(void*, SEL, const char*, unsigned long)) objc_msgSend;

MTString* mt_string_utf8String(const char* string){
    Class _class = objc_getClass("NSString");
    SEL allocSel = sel_registerName("alloc");
    
    void* _nsString = ms_send(_class, allocSel);
    SEL initSel = sel_registerName("stringWithCString:encoding:");
    
    return ms_send_string_encoding(_class, initSel, string, MTUTF8StringEncoding);
}
