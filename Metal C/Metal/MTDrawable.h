//
//  MTDrawable.h
//  Metal C
//
//  Created by Lungile Maseko on 2024/04/29.
//

#pragma once
#include "MTFoundation/defines.h"

typedef double CFTimeInterval;

typedef void* MTDrawable;
typedef void* CAMetalDrawable;

MT_INLINE void mt_drawable_present(MTDrawable drawable) {
    MT_MSG_SEND(void, drawable, MT_SEL("present"));
}

MT_INLINE void mt_drawable_present_at_time(MTDrawable drawable, CFTimeInterval time) {
    MT_MSG_SEND_1(void, drawable, MT_SEL("presentAtTime:"), CFTimeInterval, time);
}

MT_INLINE void mt_drawable_present_after_min_duration(MTDrawable drawable, CFTimeInterval duration) {
    MT_MSG_SEND_1(void, drawable, MT_SEL("presentAfterMinimumDuration:"), CFTimeInterval, duration);
}

MT_INLINE CFTimeInterval mt_drawable_get_presented_time(MTDrawable drawable) {
    return MT_MSG_SEND(CFTimeInterval, drawable, MT_SEL("presentedTime"));
}

MT_INLINE unsigned long mt_drawable_get_id(MTDrawable drawable) {
    return MT_MSG_SEND(unsigned long, drawable, MT_SEL("drawableID"));
}
