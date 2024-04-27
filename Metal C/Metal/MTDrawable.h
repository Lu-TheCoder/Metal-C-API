//
//  MTDrawable.h
//  Metal C
//
//  Created by Lungile Maseko on 2024/04/29.
//

#pragma once

typedef double CFTimeInterval;

typedef void* MTDrawable;
typedef void* CAMetalDrawable;

MT_INLINE void mt_drawable_present(MTDrawable drawable) {
    SEL sel = sel_getUid("present");
    ((void (*)(id, SEL))objc_msgSend)(drawable, sel);
}

MT_INLINE void mt_drawable_present_at_time(MTDrawable drawable, CFTimeInterval time) {
    SEL sel = sel_getUid("presentAtTime:");
    ((void (*)(id, SEL, CFTimeInterval))objc_msgSend)(drawable, sel, time);
}

MT_INLINE void mt_drawable_present_after_min_duration(MTDrawable drawable, CFTimeInterval duration) {
    SEL sel = sel_getUid("presentAfterMinimumDuration:");
    ((void (*)(id, SEL, CFTimeInterval))objc_msgSend)(drawable, sel, duration);
}

MT_INLINE CFTimeInterval mt_drawable_get_presented_time(MTDrawable drawable) {
    SEL sel = sel_getUid("presentedTime");
    return ((CFTimeInterval (*)(id, SEL))objc_msgSend)(drawable, sel);
}

MT_INLINE unsigned long mt_drawable_get_id(MTDrawable drawable) {
    SEL sel = sel_getUid("drawableID");
    return ((unsigned long (*)(id, SEL))objc_msgSend)(drawable, sel);
}
