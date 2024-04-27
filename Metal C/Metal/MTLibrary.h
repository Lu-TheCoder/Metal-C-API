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

typedef void MTDevice;

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

void* (*ms_send_file_and_error)(void*, SEL, MTString*, MTError*) = (void* (*)(void*, SEL, MTString*, MTError*)) objc_msgSend;

MT_INLINE MTLibrary* mt_library_new_default_library(MTDevice* device){
    return ms_send(device, sel_registerName("newDefaultLibrary"));
}

MT_INLINE MTLibrary* mt_library_new_library_withURL(MTDevice* device, MTURL* url, MTError** error) {
    return ms_send_file_and_error(device, sel_registerName("newLibraryWithURL:error:"), url, error);
}

void* (*ms_send_string)(void*, SEL, MTString*) = (void* (*)(void*, SEL, MTString*)) objc_msgSend;

MT_INLINE MTFunction* mt_library_new_function(MTLibrary* library, MTString* name){
    return ms_send_string(library, sel_registerName("newFunctionWithName:"), name);
}
