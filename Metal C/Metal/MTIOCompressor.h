//
//  MTIOCompressor.h
//  Metal C
//
//  Created by Lungile Maseko on 2025/06/05.
//
#pragma once

typedef enum MTIOCompressionStatus {
    MTIOCompressionStatusComplete = 0,
    MTIOCompressionStatusError = 1
} MTIOCompressionStatus;

typedef void* MTIOCompressionContext;

/*
 These methods are expected to be used by offline tools that
 process and generate assets.
 */

/*
 @function MTLIOCompressionContextDefaultChunkSize
 @abstract The default chunk size to use for a compression context.
 */
extern size_t MTLIOCompressionContextDefaultChunkSize(void);

/*
 @function MTLIOCreateCompressionContext
 @abstract used to create a context that writes a stream of data to
 a path using a given codec and chunk size.
 @discussion An invalid type will cause a nil to be returned. If path is
 invalid or fails to open a nil will be returned and errno will be set.
 */
extern MTIOCompressionContext MTLIOCreateCompressionContext(const char* path, MTIOCompressionMethod type, size_t chunkSize);

/*
 @function MTLIOCompressionContextAppendData
 @abstract append data to a compression context.
 */
extern void MTLIOCompressionContextAppendData(MTIOCompressionContext ctx, const void* data, size_t size);

/*
 @function MTLIOFlushAndDestroyCompressionContext
 @abstract close the compression context and write the pack file.
 */
extern MTIOCompressionStatus MTLIOFlushAndDestroyCompressionContext(MTIOCompressionContext ctx);
