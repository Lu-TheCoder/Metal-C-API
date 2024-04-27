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
#include <Block.h>

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

typedef void* MTVertexAttribute;

typedef void* MTAttribute;

typedef void* MTLFunctionConstant;

typedef void* MTFunction;

typedef void* MTCompileOptions;

typedef void* MTLibrary;

MTCompileOptions mt_compile_options_new(void) {
    Class MTLCompileOptionsClass = objc_getClass("MTLCompileOptions");
    SEL allocSel = sel_registerName("alloc");
    SEL initSel = sel_registerName("init");

    id optsAlloc = ((id (*)(Class, SEL))objc_msgSend)(MTLCompileOptionsClass, allocSel);
    id opts = ((id (*)(id, SEL))objc_msgSend)(optsAlloc, initSel);
    return opts;
}

MT_INLINE MTLibrary mt_device_create_default_library(MTDevice* device) {
    typedef void* (*MsgSendFn)(void*, SEL);
    MsgSendFn msgSend = (MsgSendFn)objc_msgSend;
    SEL sel = sel_getUid("newDefaultLibrary");
    return (MTLibrary*)msgSend(device, sel);
}

MT_INLINE MTLibrary mt_device_create_library_withURL(MTDevice* device, MTURL* url, MTError** error) {
    typedef void* (*MsgSendFn)(void*, SEL, MTURL*, MTError**);
    MsgSendFn msgSend = (MsgSendFn)objc_msgSend;
    SEL sel = sel_getUid("newLibraryWithURL:error:");
    return (MTLibrary*)msgSend(device, sel, url, error);
}

MT_INLINE MTLibrary mt_device_create_library_with_data(MTDevice* device, dispatch_data_t data, MTError** error) {
    typedef void* (*MsgSendFn)(void*, SEL, dispatch_data_t, MTError**);
    MsgSendFn msgSend = (MsgSendFn)objc_msgSend;
    SEL sel = sel_getUid("newLibraryWithData:error:");
    return (MTLibrary*)msgSend(device, sel, data, error);
}

MT_INLINE MTLibrary mt_device_create_library_with_source(
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

typedef void (*mtl_library_callback_t)(void *userdata, MTLibrary lib, MTError *err);

MT_INLINE void mt_device_create_library_with_source_async(
    id device,
    MTString *source,
    MTCompileOptions *options,
    mtl_library_callback_t callback,
    void *userdata
) {
    SEL sel = sel_registerName("newLibraryWithSource:options:completionHandler:");
    typedef void (*MsgSendFn)(id, SEL, MTString *, MTCompileOptions *, void (^)(id, MTError *));

    // Create native Clang block that wraps your callback
    void (^handler)(id, MTError *) = ^(id lib, MTError *err) {
        callback(userdata, (MTLibrary)lib, (MTError *)err);
    };

    // Call Objective-C method with block
    MsgSendFn fn = (MsgSendFn)objc_msgSend;
    fn(device, sel, source, options, handler);

    // NOTE: No manual retain/release needed; ARC or block runtime handles it.
}

MT_INLINE MTFunction mt_library_create_function(MTLibrary* library, MTString* name) {
    typedef void* (*MsgSendFn)(void*, SEL, MTString*);
    MsgSendFn msgSend = (MsgSendFn)objc_msgSend;
    SEL sel = sel_getUid("newFunctionWithName:");
    return (MTFunction*)msgSend(library, sel, name);
}

MT_INLINE MTCompileOptions mt_compile_options_create(void) {
    Class cls = (Class)objc_getClass("MTLCompileOptions");
    SEL allocSel = sel_getUid("alloc");
    SEL initSel = sel_getUid("init");

    void* (*allocMsgSend)(Class, SEL) = (void* (*)(Class, SEL))objc_msgSend;
    void* (*initMsgSend)(void*, SEL) = (void* (*)(void*, SEL))objc_msgSend;

    void* obj = allocMsgSend(cls, allocSel);
    return (MTCompileOptions*)initMsgSend(obj, initSel);
}

// Set fastMathEnabled: YES or NO
MT_INLINE void mt_compile_options_set_fast_math_enabled(MTCompileOptions* opts, bool enabled) {
    SEL sel = sel_getUid("setFastMathEnabled:");
    void (*msgSend)(void*, SEL, bool) = (void (*)(void*, SEL, bool))objc_msgSend;
    msgSend(opts, sel, enabled);
}

// Set the Metal language version (e.g., MTLLanguageVersion2_4)
MT_INLINE void mt_compile_options_set_language_version(MTCompileOptions* opts, MTLanguageVersion version) {
    SEL sel = sel_getUid("setLanguageVersion:");
    void (*msgSend)(void*, SEL, MTLanguageVersion) = (void (*)(void*, SEL, MTLanguageVersion))objc_msgSend;
    msgSend(opts, sel, version);
}

MT_INLINE void mt_compile_options_set_preserve_invariance(MTCompileOptions opts, bool preserve) {
    SEL sel = sel_getUid("setPreserveInvariance:");
    ((void (*)(id, SEL, bool))objc_msgSend)(opts, sel, preserve);
}

MT_INLINE void mt_compile_options_set_optimization_level(MTCompileOptions opts, MTLibraryOptimizationLevel level) {
    SEL sel = sel_getUid("setOptimizationLevel:");
    ((void (*)(id, SEL, MTLibraryOptimizationLevel))objc_msgSend)(opts, sel, level);
}

MT_INLINE void mt_compile_options_set_compile_symbol_visibility(MTCompileOptions opts, MTCompileSymbolVisibility visibility) {
    SEL sel = sel_getUid("setCompileSymbolVisibility:");
    ((void (*)(id, SEL, MTCompileSymbolVisibility))objc_msgSend)(opts, sel, visibility);
}

MT_INLINE void mt_compile_options_set_allow_referencing_undefined_symbols(MTCompileOptions opts, bool allow) {
    SEL sel = sel_getUid("setAllowReferencingUndefinedSymbols:");
    ((void (*)(id, SEL, bool))objc_msgSend)(opts, sel, allow);
}

MT_INLINE void mt_compile_options_set_max_total_threads_per_threadgroup(MTCompileOptions opts, NSUInteger max_threads) {
    SEL sel = sel_getUid("setMaxTotalThreadsPerThreadgroup:");
    ((void (*)(id, SEL, NSUInteger))objc_msgSend)(opts, sel, max_threads);
}

MT_INLINE void mt_compile_options_set_enable_logging(MTCompileOptions opts, bool enable) {
    SEL sel = sel_getUid("setEnableLogging:");
    ((void (*)(id, SEL, bool))objc_msgSend)(opts, sel, enable);
}
