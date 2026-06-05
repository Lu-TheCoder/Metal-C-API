//
//  MT4BinaryFunction.h
//  Metal C
//
//  MTL4BinaryFunction — a precompiled GPU function (for function pointers /
//  visible & intersection functions). You describe one with a name + a function
//  descriptor, then compile it via the MTL4 compiler.
//

#pragma once
#include "MTFoundation/defines.h"
#include "MTFoundation/MTString.h"  // mt_string_*

// Metal's MTL4BinaryFunctionOptions.
typedef enum MT4BinaryFunctionOptions : unsigned long {
    MT4BinaryFunctionOptionNone                = 0,
    MT4BinaryFunctionOptionPipelineIndependent = 1 << 1,
} MT4BinaryFunctionOptions;

MT_INLINE MT4BinaryFunctionDescriptor mt4_binary_function_descriptor_create(void) {
    return MT_ALLOC_INIT("MTL4BinaryFunctionDescriptor");
}

MT_INLINE void mt4_binary_function_descriptor_set_name(MT4BinaryFunctionDescriptor desc, const char* name) {
    id ns = mt_string_create(name);
    MT_MSG_SEND_1(void, desc, MT_SEL("setName:"), id, ns);
    mt_string_release(ns);
}

// Pass a MT4LibraryFunctionDescriptor (cast to MT4FunctionDescriptor).
MT_INLINE void mt4_binary_function_descriptor_set_function_descriptor(MT4BinaryFunctionDescriptor desc, MT4FunctionDescriptor fn) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setFunctionDescriptor:"), id, fn);
}

MT_INLINE void mt4_binary_function_descriptor_set_options(MT4BinaryFunctionDescriptor desc, MT4BinaryFunctionOptions options) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setOptions:"), MT4BinaryFunctionOptions, options);
}

// Compile the binary function (+1 owned). Compiler comes from MT4Compiler.h.
MT_INLINE MT4BinaryFunction mt4_compiler_create_binary_function(MT4Compiler compiler, MT4BinaryFunctionDescriptor desc, MTError* outError) {
    return MT_MSG_SEND_2(void*, compiler, MT_SEL("newBinaryFunctionWithDescriptor:error:"), id, desc, MTError*, outError);
}
