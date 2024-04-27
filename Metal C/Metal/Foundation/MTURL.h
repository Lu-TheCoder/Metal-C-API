//
//  NSURL.h
//  Metal C
//
//  Created by Lungile Maseko on 2024/06/02.
//

#pragma once
#include "MTString.h"

typedef void MTURL;

MTURL* mt_url_new(void){
    Class nsUrlClass = objc_getClass("NSURL");
    SEL allocSel = sel_registerName("alloc");
    
    void* url = ms_send(nsUrlClass, allocSel);
    SEL initSel = sel_registerName("init");
    ms_send(url, initSel);
    return url;
}

void* (*ms_send_path)(void*, SEL, MTString*) = (void* (*)(void*, SEL, MTString*)) objc_msgSend;

MTURL* mt_url_init_with_path(MTString* path){
    Class nsUrlClass = objc_getClass("NSURL");
    SEL allocSel = sel_registerName("alloc");
    
    void* _class = ms_send(nsUrlClass, allocSel);
    
    SEL initSel2 = sel_registerName("initFileURLWithPath:");
    
    return (MTURL*)ms_send_path(_class, initSel2, path);
}
