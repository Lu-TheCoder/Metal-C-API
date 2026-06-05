//
//  MT4CompilerTask.h
//  Metal C
//
//  Asynchronous Metal 4 compilation. The async compiler entry points return an
//  MT4CompilerTask you can poll or wait on; the built pipeline state is
//  delivered to your callback. Use these to compile pipelines off the main
//  thread without blocking.
//

#pragma once
#include "MTFoundation/defines.h"
#include "MTFoundation/MTString.h"  // mt_object_set_label

// Metal's MTL4CompilerTaskStatus.
typedef enum MT4CompilerTaskStatus : long {
    MT4CompilerTaskStatusNone      = 0,
    MT4CompilerTaskStatusScheduled = 1,
    MT4CompilerTaskStatusCompiling = 2,
    MT4CompilerTaskStatusFinished  = 3,
} MT4CompilerTaskStatus;

// ---- Task ----------------------------------------------------------------

MT_INLINE MT4CompilerTaskStatus mt4_compiler_task_get_status(MT4CompilerTask task) {
    return MT_MSG_SEND(MT4CompilerTaskStatus, task, MT_SEL("status"));
}

MT_INLINE void mt4_compiler_task_wait_until_completed(MT4CompilerTask task) {
    MT_MSG_SEND(void, task, MT_SEL("waitUntilCompleted"));
}

MT_INLINE MT4Compiler mt4_compiler_task_get_compiler(MT4CompilerTask task) {
    return MT_MSG_SEND(void*, task, MT_SEL("compiler"));
}

// ---- Task options --------------------------------------------------------

MT_INLINE MT4CompilerTaskOptions mt4_compiler_task_options_create(void) {
    return MT_ALLOC_INIT("MTL4CompilerTaskOptions");
}

MT_INLINE void mt4_compiler_task_options_set_label(MT4CompilerTaskOptions options, const char* label) {
    mt_object_set_label(options, label);
}

// ---- Asynchronous compilation --------------------------------------------

typedef void (*mt4_render_pipeline_callback_t)(void* userdata, MTRenderPipelineState pipeline, MTError error);
typedef void (*mt4_compute_pipeline_callback_t)(void* userdata, MTComputePipelineState pipeline, MTError error);

// Kicks off an async render-pipeline build; `callback` fires on completion.
// Returns the in-flight task (you may wait on / poll it). Compiler is from MT4Compiler.h.
MT_INLINE MT4CompilerTask mt4_compiler_create_render_pipeline_state_async(MT4Compiler compiler, MT4RenderPipelineDescriptor desc, mt4_render_pipeline_callback_t callback, void* userdata) {
    void (^handler)(id, MTError) = ^(id pipeline, MTError error) { callback(userdata, (MTRenderPipelineState)pipeline, error); };
    return MT_MSG_SEND_3(void*, compiler, MT_SEL("newRenderPipelineStateWithDescriptor:compilerTaskOptions:completionHandler:"), id, desc, id, NULL, void (^)(id, MTError), handler);
}

MT_INLINE MT4CompilerTask mt4_compiler_create_compute_pipeline_state_async(MT4Compiler compiler, MT4ComputePipelineDescriptor desc, mt4_compute_pipeline_callback_t callback, void* userdata) {
    void (^handler)(id, MTError) = ^(id pipeline, MTError error) { callback(userdata, (MTComputePipelineState)pipeline, error); };
    return MT_MSG_SEND_3(void*, compiler, MT_SEL("newComputePipelineStateWithDescriptor:compilerTaskOptions:completionHandler:"), id, desc, id, NULL, void (^)(id, MTError), handler);
}
