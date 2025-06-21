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
