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

/// Create an NSURL object with a file path
MT_INLINE MTURL mt_url_init_with_path(MTString path) {
    id alloc = MT_MSG_SEND_CLASS(id, MT_CLASS("NSURL"), MT_SEL("alloc"));
    return MT_MSG_SEND_1(id, alloc, MT_SEL("initFileURLWithPath:"), id, path);
}

MT_INLINE MTURL mt_url_init_with_string(MTString urlString) {
    return MT_MSG_SEND_CLASS_1(id, MT_CLASS("NSURL"), MT_SEL("URLWithString:"), id, urlString);
}

/// Get absoluteString from NSURL
MT_INLINE const char* mt_url_get_absolute_string(MTURL url) {
    MTString str = MT_MSG_SEND(id, url, MT_SEL("absoluteString"));
    return mt_string_to_utf8(str);
}

/// Get path from NSURL
MT_INLINE const char* mt_url_get_path(MTURL url) {
    MTString pathStr = MT_MSG_SEND(id, url, MT_SEL("path"));
    return mt_string_to_utf8(pathStr);
}

/// Check if NSURL is a file URL
MT_INLINE bool mt_url_is_file_url(MTURL url) {
    return MT_MSG_SEND(BOOL, url, MT_SEL("isFileURL"));
}
