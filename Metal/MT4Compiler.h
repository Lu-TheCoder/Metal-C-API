//
//  MT4Compiler.h
//  Metal C
//
//  MTL4Compiler — the explicit Metal 4 compilation API. You create a compiler
//  once, then use it to build libraries and pipeline states. The pipeline
//  states it produces are the *classic* MTRenderPipelineState /
//  MTComputePipelineState the encoders consume.
//
//  Functions for pipelines are specified via descriptor objects
//  (MTL4LibraryFunctionDescriptor: a function name + the library it lives in),
//  not MTFunction objects.
//
//  This header covers the synchronous compile path (compilerTaskOptions are
//  passed as NULL). Asynchronous MTL4CompilerTask-based compilation, binary
//  functions and dynamic libraries are deferred to a later stage.
//

#pragma once
#include "MTFoundation/defines.h"
#include "MTFoundation/MTString.h"  // mt_object_set_label

// ---- Library descriptor (source -> MTLibrary via the compiler) -----------

MT_INLINE MT4LibraryDescriptor mt4_library_descriptor_create(void) {
    return MT_ALLOC_INIT("MTL4LibraryDescriptor");
}

MT_INLINE void mt4_library_descriptor_set_source(MT4LibraryDescriptor desc, const char* source) {
    id ns = mt_string_create(source);
    MT_MSG_SEND_1(void, desc, MT_SEL("setSource:"), id, ns);
    mt_string_release(ns);
}

MT_INLINE void mt4_library_descriptor_set_name(MT4LibraryDescriptor desc, const char* name) {
    id ns = mt_string_create(name);
    MT_MSG_SEND_1(void, desc, MT_SEL("setName:"), id, ns);
    mt_string_release(ns);
}

MT_INLINE void mt4_library_descriptor_set_options(MT4LibraryDescriptor desc, MTCompileOptions options) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setOptions:"), id, options);
}

// ---- Function descriptor (names a function inside a library) -------------

MT_INLINE MT4LibraryFunctionDescriptor mt4_library_function_descriptor_create(void) {
    return MT_ALLOC_INIT("MTL4LibraryFunctionDescriptor");
}

MT_INLINE void mt4_library_function_descriptor_set_name(MT4LibraryFunctionDescriptor desc, const char* name) {
    id ns = mt_string_create(name);
    MT_MSG_SEND_1(void, desc, MT_SEL("setName:"), id, ns);
    mt_string_release(ns);
}

MT_INLINE void mt4_library_function_descriptor_set_library(MT4LibraryFunctionDescriptor desc, MTLibrary library) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setLibrary:"), id, library);
}

// ---- Compiler descriptor + creation --------------------------------------

MT_INLINE MT4CompilerDescriptor mt4_compiler_descriptor_create(void) {
    return MT_ALLOC_INIT("MTL4CompilerDescriptor");
}

MT_INLINE void mt4_compiler_descriptor_set_label(MT4CompilerDescriptor desc, const char* label) {
    mt_object_set_label(desc, label);
}

MT_INLINE MT4Compiler mt4_device_create_compiler(MTDevice device, MT4CompilerDescriptor desc, MTError* outError) {
    return MT_MSG_SEND_2(void*, device, MT_SEL("newCompilerWithDescriptor:error:"), id, desc, MTError*, outError);
}

// ---- Synchronous compilation ---------------------------------------------

// Build a library from a MT4LibraryDescriptor. Returns a classic MTLibrary (+1).
MT_INLINE MTLibrary mt4_compiler_create_library(MT4Compiler compiler, MT4LibraryDescriptor desc, MTError* outError) {
    return MT_MSG_SEND_2(void*, compiler, MT_SEL("newLibraryWithDescriptor:error:"), id, desc, MTError*, outError);
}

// Build a render pipeline state (+1). Pass a MT4RenderPipelineDescriptor.
MT_INLINE MTRenderPipelineState mt4_compiler_create_render_pipeline_state(MT4Compiler compiler, MT4RenderPipelineDescriptor desc, MTError* outError) {
    return MT_MSG_SEND_3(void*, compiler, MT_SEL("newRenderPipelineStateWithDescriptor:compilerTaskOptions:error:"), id, desc, id, NULL, MTError*, outError);
}

// Build a compute pipeline state (+1). Pass a MT4ComputePipelineDescriptor.
MT_INLINE MTComputePipelineState mt4_compiler_create_compute_pipeline_state(MT4Compiler compiler, MT4ComputePipelineDescriptor desc, MTError* outError) {
    return MT_MSG_SEND_3(void*, compiler, MT_SEL("newComputePipelineStateWithDescriptor:compilerTaskOptions:error:"), id, desc, id, NULL, MTError*, outError);
}
