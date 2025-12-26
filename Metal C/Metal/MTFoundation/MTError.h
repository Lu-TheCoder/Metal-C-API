//
//  NSError.h
//  Metal C
//
//  Created by Lungile Maseko on 2024/06/02.
//

#pragma once
#include "defines.h"

typedef void* MTError;

// Code: - (NSInteger)code
MT_INLINE long mt_error_get_code(MTError error) {
    return MT_MSG_SEND(long, error, MT_SEL("code"));
}

MT_INLINE const char* mt_error_get_localized_description(MTError error) {
    id nsStr = MT_MSG_SEND(id, error, MT_SEL("localizedDescription"));
    if (!nsStr) return NULL;
    return MT_MSG_SEND(const char*, nsStr, MT_SEL("UTF8String"));
}

MT_INLINE const char* mt_error_get_localized_recovery_suggestion(MTError error) {
    id nsStr = MT_MSG_SEND(id, error, MT_SEL("localizedRecoverySuggestion"));
    if (!nsStr) return NULL;
    return MT_MSG_SEND(const char*, nsStr, MT_SEL("UTF8String"));
}

MT_INLINE const char* mt_error_get_localized_failure_reason(MTError error) {
    id nsStr = MT_MSG_SEND(id, error, MT_SEL("localizedFailureReason"));
    if (!nsStr) return NULL;
    return MT_MSG_SEND(const char*, nsStr, MT_SEL("UTF8String"));
}
