//
//  MT4CompilerTask.h
//  Metal C
//
//  Created by Lungile Maseko on 2025/06/21.
//
#pragma once

typedef enum MT4CompilerTaskStatus {
    /// No status.
    MT4CompilerTaskStatusNone      = 0,
    
    /// The compiler task is currently scheduled.
    MT4CompilerTaskStatusScheduled = 1,
    
    /// The compiler task is currently compiling.
    MT4CompilerTaskStatusCompiling = 2,
    
    /// The compiler task is finished.
    MT4CompilerTaskStatusFinished  = 3,
} MT4CompilerTaskStatus;

typedef void* MT4Compiler;
typedef void* MT4CompilerTask;

MT_INLINE MT4Compiler mt4_compiler_task_get_compiler(MT4CompilerTask task) {
    if (!task) return nil;
    return ((MT4Compiler (*)(void*, SEL))objc_msgSend)(
        task,
        sel_getUid("compiler")
    );
}

MT_INLINE MT4CompilerTaskStatus mt4_compiler_task_get_status(MT4CompilerTask task) {
    if (!task) return 0; // Assuming MTL4CompilerTaskStatusNone = 0
    return ((MT4CompilerTaskStatus (*)(void*, SEL))objc_msgSend)(
        task,
        sel_getUid("status")
    );
}

MT_INLINE void mt4_compiler_task_wait_until_completed(MT4CompilerTask task) {
    if (!task) return;
    ((void (*)(void*, SEL))objc_msgSend)(
        task,
        sel_getUid("waitUntilCompleted")
    );
}
