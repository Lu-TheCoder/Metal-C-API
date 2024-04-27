//
//  NSBundle.h
//  Metal C
//
//  Created by Lungile Maseko on 2024/06/02.
//

#pragma once
#include "MTURL.h"
#include "MTString.h"

typedef void MTBundle;

MTBundle* mt_bundle_new(void){
    Class bundleClass = objc_getClass("NSBundle");
    
    SEL sel = sel_registerName("mainBundle");
    return ms_send(bundleClass, sel);
}

void* (*ms_send_string2)(void*, SEL, id, id) = (void* (*)(void*, SEL, id, id)) objc_msgSend;

MTString* mt_bundle_get_lib_path(MTBundle* bundle, MTString* file_name, MTString* file_extension){
    SEL sel = sel_registerName("pathForResource:ofType:");
    return ms_send_string2(bundle, sel, file_name, file_extension);
}

//NSBundle* nsMainBundle(NSBundle* bundle){
//    SEL sel = sel_registerName("mainBundle");
//    return ms_send(bundle, sel);
//}
