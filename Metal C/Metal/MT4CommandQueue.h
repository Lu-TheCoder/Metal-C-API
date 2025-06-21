//
//  MT4CommandQueue.h
//  Metal C
//
//  Created by Lungile Maseko on 2025/06/20.
//
#pragma once
#include "MTUtils.h"
#include "dispatch/dispatch.h"
#include "MTTypes.h"
#include "MTResourceStateCommandEncoder.h"

typedef enum MT4CommandQueueError {
    /// Indicates the absence of any problems.
    MT4CommandQueueErrorNone          = 0,
    
    /// Indicates the workload takes longer to execute than the system allows.
    MT4CommandQueueErrorTimeout       = 1,
    
    /// Indicates a process doesn’t have access to a GPU device.
    MT4CommandQueueErrorNotPermitted  = 2,
    
    /// Indicates the GPU doesn’t have sufficient memory to execute a command buffer.
    MT4CommandQueueErrorOutOfMemory   = 3,
    
    /// Indicates the physical removal of the GPU before the command buffer completed.
    MT4CommandQueueErrorDeviceRemoved = 4,
    
    /// Indicates that the system revokes GPU access because it’s responsible for too many timeouts or hangs.
    MT4CommandQueueErrorAccessRevoked = 5,
    
    /// Indicates an internal problem in the Metal framework.
    MT4CommandQueueErrorInternal      = 6,
    
} MT4CommandQueueError;


typedef struct MT4UpdateSparseTextureMappingOperation {
    /// The mode of the mapping operation to perform.
    ///
    /// When mode is ``MTLSparseTextureMappingMode/MTLSparseTextureMappingModeMap``,
    /// Metal walks the tiles in the region in X, Y, then Z order, assigning the next
    /// tile from the heap in increasing order, starting at ``heapOffset``.
    ///
    /// When mode is ``MTLSparseTextureMappingMode/MTLSparseTextureMappingModeUnmap``,
    /// Metal unmaps the tiles in the region, ignoring the contents of member ``heapOffset``.
    MTSparseTextureMappingMode mode;
    
    /// The region in the texture to update, in tiles.
    MTRegion textureRegion;
    
    /// The index of the mipmap level in the texture to update.
    unsigned long textureLevel;
    
    /// The index of the array slice in the texture to update.
    ///
    /// Provide `0` in this member if the texture type is not an array.
    unsigned long textureSlice;
    
    /// The starting offset in the heap, in tiles.
    unsigned long heapOffset;

} MT4UpdateSparseTextureMappingOperation;

/// Groups together arguments for an operation to copy a sparse texture mapping.
typedef struct MT4CopySparseTextureMappingOperation {
    /// The region in the source texture, in tiles.
    ///
    /// The tiles remain mapped in the source texture.
    MTRegion sourceRegion;
    
    /// The index of the mipmap level in the source texture.
    unsigned long sourceLevel;
    
    /// The index of the array slice in the texture source of the copy operation.
    ///
    /// Provide `0` in this member if the texture type is not an array.
    unsigned long sourceSlice;
    
    /// The origin in the destination texture to copy into, in tiles.
    ///
    /// The X, Y and Z coordinates of the tiles relative to the origin match the same
    /// coordinates in the source region.
    MTOrigin destinationOrigin;
    
    /// The index of the mipmap level in the destination texture.
    unsigned long destinationLevel;
    
    /// The index of the array slice in the destination texture to copy into.
    ///
    /// Provide `0` in this member if the texture type is not an array.
    unsigned long destinationSlice;

} MT4CopySparseTextureMappingOperation;

/// Groups together arguments for an operation to update a sparse buffer mapping.
typedef struct MT4UpdateSparseBufferMappingOperation {
    /// The mode of the mapping operation to perform.
    ///
    /// When mode is ``MTLSparseTextureMappingMode/MTLSparseTextureMappingModeMap``,
    /// Metal walks the tiles in the range in buffer offset order, assigning the
    /// next tile from the heap in increasing order, starting at ``heapOffset``.
    ///
    /// When mode is ``MTLSparseTextureMappingMode/MTLSparseTextureMappingModeUnmap``,
    /// Metal unmaps the tiles in the range, and ignores the value of member ``heapOffset``.
    MTSparseTextureMappingMode mode;
    
    /// The range in the buffer, in tiles.
    MTRange bufferRange;
    
    /// The starting offset in the heap, in tiles.
    unsigned long heapOffset;

} MT4UpdateSparseBufferMappingOperation;

/// Groups together arguments for an operation to copy a sparse buffer mapping.
typedef struct MT4CopySparseBufferMappingOperation {
    /// The range in the source buffer, in tiles.
    ///
    /// The tiles remain mapped in the source buffer.
    MTRange sourceRange;
    
    /// The origin in the destination buffer, in tiles.
    unsigned long destinationOffset;
} MT4CopySparseBufferMappingOperation;

typedef void* MTDevice;
typedef void* MT4CommandQueue;
typedef void* MT4CommandQueueDescriptor;
typedef void* MT4CommitOptions;
typedef void* MT4CommandBuffer;
typedef void* MTString;
typedef void* MTEvent;
typedef void* MTDrawable;
typedef void* MTResidencySet;
typedef void* MTTexture;
typedef void* MTBuffer;
typedef void* MTHeap;

typedef void* MTL4CommitFeedback;
typedef void (^MT4CommitFeedbackHandler)(MTL4CommitFeedback commitFeedback);

MT_INLINE void mt4_commit_options_add_feedback_handler(
    MT4CommitOptions options,
    MT4CommitFeedbackHandler handler
) {
    if (!options || !handler) return;

    SEL sel = sel_getUid("addFeedbackHandler:");
    ((void (*)(id, SEL, MT4CommitFeedbackHandler))objc_msgSend)(options, sel, handler);
}

MT_INLINE void mt4_command_queue_descriptor_set_label(
    MT4CommandQueueDescriptor desc,
    const char* label
) {
    if (!desc || !label) return;

    SEL sel = sel_getUid("setLabel:");
    id nsLabel = ((id (*)(Class, SEL, const char*))objc_msgSend)(
        objc_getClass("NSString"),
        sel_getUid("stringWithUTF8String:"),
        label
    );

    ((void (*)(id, SEL, id))objc_msgSend)(desc, sel, nsLabel);
}

MT_INLINE MTString mt4_command_queue_descriptor_get_label(MT4CommandQueueDescriptor desc) {
    if (!desc) return NULL;

    SEL sel = sel_getUid("label");
    return ((MTString (*)(id, SEL))objc_msgSend)(desc, sel);
}

MT_INLINE void mt4_command_queue_descriptor_set_feedback_queue(
    MT4CommandQueueDescriptor desc,
    dispatch_queue_t queue
) {
    if (!desc) return;

    SEL sel = sel_getUid("setFeedbackQueue:");
    ((void (*)(id, SEL, dispatch_queue_t))objc_msgSend)(desc, sel, queue);
}

MT_INLINE dispatch_queue_t mt4_command_queue_descriptor_get_feedback_queue(MT4CommandQueueDescriptor desc) {
    if (!desc) return NULL;

    SEL sel = sel_getUid("feedbackQueue");
    return ((dispatch_queue_t (*)(id, SEL))objc_msgSend)(desc, sel);
}

MT_INLINE MTDevice mt4_command_queue_get_device(MT4CommandQueue queue) {
    if (!queue) return NULL;
    SEL sel = sel_getUid("device");
    return ((MTDevice (*)(id, SEL))objc_msgSend)(queue, sel);
}

MT_INLINE MTString mt4_command_queue_get_label(MT4CommandQueue queue) {
    if (!queue) return NULL;
    SEL sel = sel_getUid("label");
    return ((MTString (*)(id, SEL))objc_msgSend)(queue, sel);
}

MT_INLINE void mt4_command_queue_commit(MT4CommandQueue queue, MT4CommandBuffer* buffers, uintptr_t count) {
    if (!queue || !buffers) return;
    SEL sel = sel_getUid("commit:count:");
    ((void (*)(id, SEL, MT4CommandBuffer*, uintptr_t))objc_msgSend)(queue, sel, buffers, count);
}

MT_INLINE void mt4_command_queue_commit_with_options(MT4CommandQueue queue, MT4CommandBuffer* buffers, uintptr_t count, MT4CommitOptions options) {
    if (!queue || !buffers || !options) return;
    SEL sel = sel_getUid("commit:count:options:");
    ((void (*)(id, SEL, MT4CommandBuffer*, uintptr_t, MT4CommitOptions))objc_msgSend)(queue, sel, buffers, count, options);
}

MT_INLINE void mt4_command_queue_signal_event(MT4CommandQueue queue, MTEvent event, uint64_t value) {
    if (!queue || !event) return;
    SEL sel = sel_getUid("signalEvent:value:");
    ((void (*)(id, SEL, MTEvent, uint64_t))objc_msgSend)(queue, sel, event, value);
}

MT_INLINE void mt4_command_queue_wait_for_event(MT4CommandQueue queue, MTEvent event, uint64_t value) {
    if (!queue || !event) return;
    SEL sel = sel_getUid("waitForEvent:value:");
    ((void (*)(id, SEL, MTEvent, uint64_t))objc_msgSend)(queue, sel, event, value);
}

MT_INLINE void mt4_command_queue_signal_drawable(MT4CommandQueue queue, MTDrawable drawable) {
    if (!queue || !drawable) return;
    SEL sel = sel_getUid("signalDrawable:");
    ((void (*)(id, SEL, MTDrawable))objc_msgSend)(queue, sel, drawable);
}

MT_INLINE void mt4_command_queue_wait_for_drawable(MT4CommandQueue queue, MTDrawable drawable) {
    if (!queue || !drawable) return;
    SEL sel = sel_getUid("waitForDrawable:");
    ((void (*)(id, SEL, MTDrawable))objc_msgSend)(queue, sel, drawable);
}

MT_INLINE void mt4_command_queue_add_residency_set(MT4CommandQueue queue, MTResidencySet set) {
    if (!queue || !set) return;
    SEL sel = sel_getUid("addResidencySet:");
    ((void (*)(id, SEL, MTResidencySet))objc_msgSend)(queue, sel, set);
}

MT_INLINE void mt4_command_queue_remove_residency_set(MT4CommandQueue queue, MTResidencySet set) {
    if (!queue || !set) return;
    SEL sel = sel_getUid("removeResidencySet:");
    ((void (*)(id, SEL, MTResidencySet))objc_msgSend)(queue, sel, set);
}

MT_INLINE void mt4_command_queue_add_residency_sets(
    MT4CommandQueue queue,
    MTResidencySet* sets,
    uintptr_t count
) {
    if (!queue || !sets) return;

    SEL sel = sel_getUid("addResidencySets:count:");
    ((void (*)(id, SEL, MTResidencySet*, uintptr_t))objc_msgSend)(
        queue, sel, sets, count
    );
}

MT_INLINE void mt4_command_queue_remove_residency_sets(
    MT4CommandQueue queue,
    MTResidencySet* sets,
    uintptr_t count
) {
    if (!queue || !sets) return;

    SEL sel = sel_getUid("removeResidencySets:count:");
    ((void (*)(id, SEL, MTResidencySet*, uintptr_t))objc_msgSend)(
        queue, sel, sets, count
    );
}

MT_INLINE void mt4_command_queue_update_texture_mappings(
    MT4CommandQueue queue,
    MTTexture texture,
    MTHeap heap,
    const MT4UpdateSparseTextureMappingOperation* ops,
    uintptr_t count
) {
    if (!queue || !texture || !ops) return;

    SEL sel = sel_getUid("updateTextureMappings:heap:operations:count:");
    ((void (*)(id, SEL, MTTexture, MTHeap, const MT4UpdateSparseTextureMappingOperation*, uintptr_t))objc_msgSend)(
        queue, sel, texture, heap, ops, count
    );
}

MT_INLINE void mt4_command_queue_copy_texture_mappings(
    MT4CommandQueue queue,
    MTTexture src,
    MTTexture dst,
    const MT4CopySparseTextureMappingOperation* ops,
    uintptr_t count
) {
    if (!queue || !src || !dst || !ops) return;

    SEL sel = sel_getUid("copyTextureMappingsFromTexture:toTexture:operations:count:");
    ((void (*)(id, SEL, MTTexture, MTTexture, const MT4CopySparseTextureMappingOperation*, uintptr_t))objc_msgSend)(
        queue, sel, src, dst, ops, count
    );
}

MT_INLINE void mt4_command_queue_update_buffer_mappings(
    MT4CommandQueue queue,
    MTBuffer buffer,
    MTHeap heap,
    const MT4UpdateSparseBufferMappingOperation* ops,
    uintptr_t count
) {
    if (!queue || !buffer || !ops) return;

    SEL sel = sel_getUid("updateBufferMappings:heap:operations:count:");
    ((void (*)(id, SEL, MTBuffer, MTHeap, const MT4UpdateSparseBufferMappingOperation*, uintptr_t))objc_msgSend)(
        queue, sel, buffer, heap, ops, count
    );
}

MT_INLINE void mt4_command_queue_copy_buffer_mappings(
    MT4CommandQueue queue,
    MTBuffer src,
    MTBuffer dst,
    const MT4CopySparseBufferMappingOperation* ops,
    uintptr_t count
) {
    if (!queue || !src || !dst || !ops) return;

    SEL sel = sel_getUid("copyBufferMappingsFromBuffer:toBuffer:operations:count:");
    ((void (*)(id, SEL, MTBuffer, MTBuffer, const MT4CopySparseBufferMappingOperation*, uintptr_t))objc_msgSend)(
        queue, sel, src, dst, ops, count
    );
}
