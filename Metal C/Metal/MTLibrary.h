//
//  MTLibrary.h
//  Metal C
//
//  Created by Lungile Maseko on 2024/06/02.
//

#pragma once
#include "MTDevice.h"
#include "MTFoundation/MTError.h"
#include "MTFoundation/MTURL.h"
#include "MTFoundation/MTString.h"
#include <dispatch/dispatch.h>
#include <Block.h>

typedef void* MTDevice;

typedef enum MTPatchType {
    MTPatchTypeNone = 0,
    MTPatchTypeTriangle = 1,
    MTPatchTypeQuad = 2,
} MTPatchType;

typedef enum MTFunctionType {
    MTFunctionTypeVertex = 1,
    MTFunctionTypeFragment = 2,
    MTFunctionTypeKernel = 3,
    MTFunctionTypeVisible = 5,
    MTFunctionTypeIntersection = 6,
    MTFunctionTypeMesh = 7,
    MTFunctionTypeObject = 8,
} MTFunctionType;

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
} MTLanguageVersion;

typedef enum MTLibraryType {
    MTLibraryTypeExecutable = 0,
    MTLibraryTypeDynamic = 1,
} MTLibraryType;

typedef enum MTLibraryOptimizationLevel {
    MTLibraryOptimizationLevelDefault = 0,
    MTLibraryOptimizationLevelSize = 1,
} MTLibraryOptimizationLevel;

typedef enum MTCompileSymbolVisibility {
    MTCompileSymbolVisibilityDefault = 0,
    MTCompileSymbolVisibilityHidden = 1,
} MTCompileSymbolVisibility;

typedef enum MTLibraryError {
    MTLibraryErrorUnsupported = 1,
    MTLibraryErrorInternal = 2,
    MTLibraryErrorCompileFailure = 3,
    MTLibraryErrorCompileWarning = 4,
    MTLibraryErrorFunctionNotFound = 5,
    MTLibraryErrorFileNotFound = 6,
} MTLibraryError;

typedef void* MTVertexAttribute;
typedef void* MTAttribute;
typedef void* MTLFunctionConstant;
typedef void* MTFunction;
typedef void* MTCompileOptions;
typedef void* MTLibrary;

MT_INLINE MTCompileOptions mt_compile_options_new(void) {
    return MT_ALLOC_INIT("MTLCompileOptions");
}

MT_INLINE MTLibrary mt_device_create_default_library(MTDevice* device) {
    return MT_MSG_SEND(id, device, MT_SEL("newDefaultLibrary"));
}

MT_INLINE MTLibrary mt_device_create_library_withURL(MTDevice device, MTURL url, MTError** error) {
    return MT_MSG_SEND_2(id, device, MT_SEL("newLibraryWithURL:error:"), id, url, MTError**, error);
}

MT_INLINE MTLibrary mt_device_create_library_with_data(MTDevice* device, dispatch_data_t data, MTError** error) {
    return MT_MSG_SEND_2(id, device, MT_SEL("newLibraryWithData:error:"), dispatch_data_t, data, MTError**, error);
}

MT_INLINE MTLibrary mt_device_create_library_with_source(
    MTDevice* device,
    MTString* source,
    MTCompileOptions* options,
    MTError** error
) {
    return MT_MSG_SEND_3(id, device, MT_SEL("newLibraryWithSource:options:error:"), id, source, id, options, MTError**, error);
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

    void (^handler)(id, MTError *) = ^(id lib, MTError *err) {
        callback(userdata, (MTLibrary)lib, (MTError *)err);
    };

    MsgSendFn fn = (MsgSendFn)objc_msgSend;
    fn(device, sel, source, options, handler);
}

MT_INLINE MTFunction mt_library_create_function(MTLibrary* library, MTString* name) {
    return MT_MSG_SEND_1(id, library, MT_SEL("newFunctionWithName:"), id, name);
}

MT_INLINE MTCompileOptions mt_compile_options_create(void) {
    return MT_ALLOC_INIT("MTLCompileOptions");
}

MT_INLINE void mt_compile_options_set_fast_math_enabled(MTCompileOptions* opts, bool enabled) {
    MT_MSG_SEND_1(void, opts, MT_SEL("setFastMathEnabled:"), bool, enabled);
}

MT_INLINE void mt_compile_options_set_language_version(MTCompileOptions* opts, MTLanguageVersion version) {
    MT_MSG_SEND_1(void, opts, MT_SEL("setLanguageVersion:"), MTLanguageVersion, version);
}

MT_INLINE void mt_compile_options_set_preserve_invariance(MTCompileOptions opts, bool preserve) {
    MT_MSG_SEND_1(void, opts, MT_SEL("setPreserveInvariance:"), bool, preserve);
}

MT_INLINE void mt_compile_options_set_optimization_level(MTCompileOptions opts, MTLibraryOptimizationLevel level) {
    MT_MSG_SEND_1(void, opts, MT_SEL("setOptimizationLevel:"), MTLibraryOptimizationLevel, level);
}

MT_INLINE void mt_compile_options_set_compile_symbol_visibility(MTCompileOptions opts, MTCompileSymbolVisibility visibility) {
    MT_MSG_SEND_1(void, opts, MT_SEL("setCompileSymbolVisibility:"), MTCompileSymbolVisibility, visibility);
}

MT_INLINE void mt_compile_options_set_allow_referencing_undefined_symbols(MTCompileOptions opts, bool allow) {
    MT_MSG_SEND_1(void, opts, MT_SEL("setAllowReferencingUndefinedSymbols:"), bool, allow);
}

MT_INLINE void mt_compile_options_set_max_total_threads_per_threadgroup(MTCompileOptions opts, NSUInteger max_threads) {
    MT_MSG_SEND_1(void, opts, MT_SEL("setMaxTotalThreadsPerThreadgroup:"), NSUInteger, max_threads);
}

MT_INLINE void mt_compile_options_set_enable_logging(MTCompileOptions opts, bool enable) {
    MT_MSG_SEND_1(void, opts, MT_SEL("setEnableLogging:"), bool, enable);
}
