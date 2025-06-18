//
//  NSURL.h
//  Metal C
//
//  Created by Lungile Maseko on 2024/06/02.
//

#pragma once
#include "MTString.h"
#include "defines.h"

typedef void* MTURL;
typedef void* MTString; // Assume MTString is a wrapper for NSString*

/// Create an NSURL object with a file path
MT_INLINE MTURL mt_url_init_with_path(MTString path) {
    Class nsUrlClass = objc_getClass("NSURL");
    SEL allocSel = sel_registerName("alloc");
    SEL initFileSel = sel_registerName("initFileURLWithPath:");

    typedef id (*AllocFn)(id, SEL);
    typedef id (*InitFn)(id, SEL, id);

    id allocInstance = ((AllocFn)objc_msgSend)((id)nsUrlClass, allocSel);
    return ((InitFn)objc_msgSend)(allocInstance, initFileSel, path);
}

MT_INLINE MTURL mt_url_init_with_string(MTString urlString) {
    Class nsUrlClass = objc_getClass("NSURL");
    SEL sel = sel_registerName("URLWithString:");
    typedef id (*MsgSendFn)(id, SEL, id);
    return ((MsgSendFn)objc_msgSend)((id)nsUrlClass, sel, urlString);
}

/// Get absoluteString from NSURL
MT_INLINE const char* mt_url_get_absolute_string(MTURL url) {
    SEL sel = sel_registerName("absoluteString");
    typedef id (*MsgSendFn)(id, SEL);
    MTString str = ((MsgSendFn)objc_msgSend)(url, sel);
    return mt_string_to_utf8(str);
}

/// Get path from NSURL
MT_INLINE const char* mt_url_get_path(MTURL url) {
    SEL sel = sel_registerName("path");
    typedef id (*MsgSendFn)(id, SEL);
    MTString pathStr = ((MsgSendFn)objc_msgSend)(url, sel);
    return mt_string_to_utf8(pathStr);
}

/// Check if NSURL is a file URL
MT_INLINE bool mt_url_is_file_url(MTURL url) {
    SEL sel = sel_registerName("isFileURL");
    typedef BOOL (*MsgSendFn)(id, SEL);
    return ((MsgSendFn)objc_msgSend)(url, sel);
}
