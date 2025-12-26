//
//  MTBlitCommandEncoder.h
//  Metal C
//
//  Created by Lungile Maseko on 2025/05/31.
//
#pragma once
#include "MTFoundation/defines.h"

typedef void* MTBlitCommandEncoder;
typedef void* MTTexture;
typedef void* MTFence;
typedef void* MTResource;
typedef void* MTBuffer;

typedef enum MTBlitOption {
    MTLBlitOptionNone                       = 0,
    MTLBlitOptionDepthFromDepthStencil      = 1 << 0,
    MTLBlitOptionStencilFromDepthStencil    = 1 << 1,
    MTLBlitOptionRowLinearPVRTC             = 1 << 2,
} MTBlitOption;

MT_INLINE void mt_blit_encoder_synchronize_resource(MTBlitCommandEncoder encoder, MTResource resource) {
    MT_MSG_SEND_1(void, encoder, MT_SEL("synchronizeResource:"), id, resource);
}

MT_INLINE void mt_blit_encoder_synchronize_texture(MTBlitCommandEncoder encoder, MTTexture texture, NSUInteger slice, NSUInteger level) {
    MT_MSG_SEND_3(void, encoder, MT_SEL("synchronizeTexture:slice:mipmapLevel:"), id, texture, NSUInteger, slice, NSUInteger, level);
}

MT_INLINE void mt_blit_copy_texture(MTBlitCommandEncoder enc, MTTexture src, MTTexture dst) {
    MT_MSG_SEND_2(void, enc, MT_SEL("copyFromTexture:toTexture:"), id, src, id, dst);
}

MT_INLINE void mt_blit_copy_buffer(MTBlitCommandEncoder enc, MTBuffer src, unsigned long src_offset, MTBuffer dst, unsigned long dst_offset, unsigned long size) {
    MT_MSG_SEND_5(void, enc, MT_SEL("copyFromBuffer:sourceOffset:toBuffer:destinationOffset:size:"), id, src, unsigned long, src_offset, id, dst, unsigned long, dst_offset, unsigned long, size);
}

MT_INLINE void mt_blit_update_fence(MTBlitCommandEncoder enc, MTFence fence) {
    MT_MSG_SEND_1(void, enc, MT_SEL("updateFence:"), id, fence);
}

MT_INLINE void mt_blit_wait_for_fence(MTBlitCommandEncoder enc, MTFence fence) {
    MT_MSG_SEND_1(void, enc, MT_SEL("waitForFence:"), id, fence);
}

MT_INLINE void mt_blit_optimize_contents_for_gpu(MTBlitCommandEncoder enc, MTTexture tex) {
    MT_MSG_SEND_1(void, enc, MT_SEL("optimizeContentsForGPUAccess:"), id, tex);
}

MT_INLINE void mt_blit_optimize_contents_for_gpu_with_slice_level(MTBlitCommandEncoder enc, MTTexture tex, unsigned long slice, unsigned long level) {
    MT_MSG_SEND_3(void, enc, MT_SEL("optimizeContentsForGPUAccess:slice:level:"), id, tex, unsigned long, slice, unsigned long, level);
}

MT_INLINE void mt_blit_optimize_contents_for_cpu(MTBlitCommandEncoder enc, MTTexture tex) {
    MT_MSG_SEND_1(void, enc, MT_SEL("optimizeContentsForCPUAccess:"), id, tex);
}

MT_INLINE void mt_blit_optimize_contents_for_cpu_with_slice_level(MTBlitCommandEncoder enc, MTTexture tex, NSUInteger slice, NSUInteger level) {
    MT_MSG_SEND_3(void, enc, MT_SEL("optimizeContentsForCPUAccess:slice:level:"), id, tex, NSUInteger, slice, NSUInteger, level);
}
