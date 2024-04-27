//
//  MTBlitCommandEncoder.h
//  Metal C
//
//  Created by Lungile Maseko on 2025/05/31.
//
#pragma once

typedef void* MTBlitCommandEncoder;
typedef void* MTTexture;
typedef void* MTFence;
typedef void* MTResource;

typedef enum MTBlitOption {
    MTLBlitOptionNone                       = 0,
    MTLBlitOptionDepthFromDepthStencil      = 1 << 0,
    MTLBlitOptionStencilFromDepthStencil    = 1 << 1,
    MTLBlitOptionRowLinearPVRTC             = 1 << 2,
} MTBlitOption;

MT_INLINE void mt_blit_encoder_synchronize_resource(MTBlitCommandEncoder encoder, MTResource resource) {
    ((void (*)(id, SEL, id))objc_msgSend)(
        encoder,
        sel_getUid("synchronizeResource:"),
        resource
    );
}

MT_INLINE void mt_blit_encoder_synchronize_texture(MTBlitCommandEncoder encoder, MTTexture texture, NSUInteger slice, NSUInteger level) {
    ((void (*)(id, SEL, id, NSUInteger, NSUInteger))objc_msgSend)(
        encoder,
        sel_getUid("synchronizeTexture:slice:mipmapLevel:"),
        texture,
        slice,
        level
    );
}

MT_INLINE void mt_blit_copy_texture(MTBlitCommandEncoder enc, MTTexture src, MTTexture dst) {
    SEL sel = sel_getUid("copyFromTexture:toTexture:");
    ((void (*)(id, SEL, id, id))objc_msgSend)(enc, sel, src, dst);
}

MT_INLINE void mt_blit_copy_buffer(MTBlitCommandEncoder enc, MTBuffer src, unsigned long src_offset, MTBuffer dst, unsigned long dst_offset, unsigned long size) {
    SEL sel = sel_getUid("copyFromBuffer:sourceOffset:toBuffer:destinationOffset:size:");
    ((void (*)(id, SEL, id, unsigned long, id, unsigned long, unsigned long))objc_msgSend)(enc, sel, src, src_offset, dst, dst_offset, size);
}

MT_INLINE void mt_blit_update_fence(MTBlitCommandEncoder enc, MTFence fence) {
    SEL sel = sel_getUid("updateFence:");
    ((void (*)(id, SEL, id))objc_msgSend)(enc, sel, fence);
}

MT_INLINE void mt_blit_wait_for_fence(MTBlitCommandEncoder enc, MTFence fence) {
    SEL sel = sel_getUid("waitForFence:");
    ((void (*)(id, SEL, id))objc_msgSend)(enc, sel, fence);
}

MT_INLINE void mt_blit_optimize_contents_for_gpu(MTBlitCommandEncoder enc, MTTexture tex) {
    SEL sel = sel_getUid("optimizeContentsForGPUAccess:");
    ((void (*)(id, SEL, id))objc_msgSend)(enc, sel, tex);
}

MT_INLINE void mt_blit_optimize_contents_for_gpu_with_slice_level(MTBlitCommandEncoder enc, MTTexture tex, unsigned long slice, unsigned long level) {
    SEL sel = sel_getUid("optimizeContentsForGPUAccess:slice:level:");
    ((void (*)(id, SEL, id, unsigned long, unsigned long))objc_msgSend)(enc, sel, tex, slice, level);
}

MT_INLINE void mt_blit_optimize_contents_for_cpu(MTBlitCommandEncoder enc, MTTexture tex) {
    SEL sel = sel_getUid("optimizeContentsForCPUAccess:");
    ((void (*)(id, SEL, id))objc_msgSend)(enc, sel, tex);
}

MT_INLINE void mt_blit_optimize_contents_for_cpu_with_slice_level(MTBlitCommandEncoder enc, MTTexture tex, NSUInteger slice, NSUInteger level) {
    SEL sel = sel_getUid("optimizeContentsForCPUAccess:slice:level:");
    ((void (*)(id, SEL, id, NSUInteger, NSUInteger))objc_msgSend)(enc, sel, tex, slice, level);
}
