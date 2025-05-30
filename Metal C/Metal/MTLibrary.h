//
//  MTLibrary.h
//  Metal C
//
//  Created by Lungile Maseko on 2024/06/02.
//

#pragma once
#include "MTDevice.h"
#include "Foundation/MTError.h"
#include "Foundation/MTURL.h"
#include "Foundation/MTString.h"
#include <dispatch/dispatch.h>

typedef void* MTDevice;

typedef enum MTPatchType {
    MTPatchTypeNone = 0,
    MTPatchTypeTriangle = 1,
    MTPatchTypeQuad = 2,
}MTPatchType;

typedef enum MTFunctionType {
    MTFunctionTypeVertex = 1,
    MTFunctionTypeFragment = 2,
    MTFunctionTypeKernel = 3,
    MTFunctionTypeVisible = 5,
    MTFunctionTypeIntersection = 6,
    MTFunctionTypeMesh = 7,
    MTFunctionTypeObject = 8,
}MTFunctionType;

typedef enum MTLanguageVersion {
    MTLanguageVersion1_0 = 65536,
    MTLanguageVersion1_1 = 65537,
    MTLanguageVersion1_2 = 65538,
    MTLanguageVersion2_0 = 131072,
    MTLanguageVersion2_1 = 131073,
    MTLanguageVersion2_2 = 131074,
    MTLanguageVersion2_3 = 131075,
    MTLanguageVersion2_4 = 131076,
    MTLanguageVersion3_0 = 196608,
    MTLanguageVersion3_1 = 196609,
}MTLanguageVersion;

typedef enum MTLibraryType {
    MTLibraryTypeExecutable = 0,
    MTLibraryTypeDynamic = 1,
}MTLibraryType;

typedef enum MTLibraryOptimizationLevel {
    MTLibraryOptimizationLevelDefault = 0,
    MTLibraryOptimizationLevelSize = 1,
}MTLibraryOptimizationLevel;

typedef enum MTCompileSymbolVisibility {
    MTCompileSymbolVisibilityDefault = 0,
    MTCompileSymbolVisibilityHidden = 1,
}MTCompileSymbolVisibility;

typedef enum MTLibraryError {
    MTLibraryErrorUnsupported = 1,
    MTLibraryErrorInternal = 2,
    MTLibraryErrorCompileFailure = 3,
    MTLibraryErrorCompileWarning = 4,
    MTLibraryErrorFunctionNotFound = 5,
    MTLibraryErrorFileNotFound = 6,
}MTLibraryError;

typedef void MTVertexAttribute;

typedef void MTAttribute;

typedef void MTLFunctionConstant;

typedef void MTFunction;

typedef void MTCompileOptions;

typedef void MTLibrary;

MT_INLINE MTLibrary* mt_device_create_default_library(MTDevice* device) {
    typedef void* (*MsgSendFn)(void*, SEL);
    MsgSendFn msgSend = (MsgSendFn)objc_msgSend;
    SEL sel = sel_getUid("newDefaultLibrary");
    return (MTLibrary*)msgSend(device, sel);
}

MT_INLINE MTLibrary* mt_device_create_library_withURL(MTDevice* device, MTURL* url, MTError** error) {
    typedef void* (*MsgSendFn)(void*, SEL, MTURL*, MTError**);
    MsgSendFn msgSend = (MsgSendFn)objc_msgSend;
    SEL sel = sel_getUid("newLibraryWithURL:error:");
    return (MTLibrary*)msgSend(device, sel, url, error);
}

MT_INLINE MTLibrary* mt_device_create_library_with_data(MTDevice* device, dispatch_data_t data, MTError** error) {
    typedef void* (*MsgSendFn)(void*, SEL, dispatch_data_t, MTError**);
    MsgSendFn msgSend = (MsgSendFn)objc_msgSend;
    SEL sel = sel_getUid("newLibraryWithData:error:");
    return (MTLibrary*)msgSend(device, sel, data, error);
}

MT_INLINE MTLibrary* mt_device_create_library_with_source(
    MTDevice* device,
    MTString* source,
    MTCompileOptions* options,
    MTError** error
) {
    typedef void* (*MsgSendFn)(void*, SEL, MTString*, MTCompileOptions*, MTError**);
    MsgSendFn msgSend = (MsgSendFn)objc_msgSend;
    SEL sel = sel_getUid("newLibraryWithSource:options:error:");
    return (MTLibrary*)msgSend(device, sel, source, options, error);
}

MT_INLINE MTFunction* mt_library_create_function(MTLibrary* library, MTString* name) {
    typedef void* (*MsgSendFn)(void*, SEL, MTString*);
    MsgSendFn msgSend = (MsgSendFn)objc_msgSend;
    SEL sel = sel_getUid("newFunctionWithName:");
    return (MTFunction*)msgSend(library, sel, name);
}

MT_INLINE MTCompileOptions* mt_compile_options_create(void) {
    Class cls = (Class)objc_getClass("MTLCompileOptions");
    SEL allocSel = sel_registerName("alloc");
    SEL initSel = sel_registerName("init");

    void* (*allocMsgSend)(Class, SEL) = (void* (*)(Class, SEL))objc_msgSend;
    void* (*initMsgSend)(void*, SEL) = (void* (*)(void*, SEL))objc_msgSend;

    void* obj = allocMsgSend(cls, allocSel);
    return (MTCompileOptions*)initMsgSend(obj, initSel);
}

// Set fastMathEnabled: YES or NO
MT_INLINE void mt_compile_options_set_fast_math_enabled(MTCompileOptions* opts, bool enabled) {
    SEL sel = sel_registerName("setFastMathEnabled:");
    void (*msgSend)(void*, SEL, bool) = (void (*)(void*, SEL, bool))objc_msgSend;
    msgSend(opts, sel, enabled);
}

// Set the Metal language version (e.g., MTLLanguageVersion2_4)
MT_INLINE void mt_compile_options_set_language_version(MTCompileOptions* opts, MTLanguageVersion version) {
    SEL sel = sel_registerName("setLanguageVersion:");
    void (*msgSend)(void*, SEL, MTLanguageVersion) = (void (*)(void*, SEL, MTLanguageVersion))objc_msgSend;
    msgSend(opts, sel, version);
}
