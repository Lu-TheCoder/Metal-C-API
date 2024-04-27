//
//  MTBinaryArchive.h
//  Metal C
//
//  Created by Lungile Maseko on 2025/06/05.
//
#pragma once

typedef void* MTComputePipelineDescriptor;
typedef void* MTRenderPipelineDescriptor;
typedef void* MTTileRenderPipelineDescriptor;
typedef void* MTStitchedLibraryDescriptor;
typedef void* MTBinaryArchiveDescriptor;
typedef void* MTFunctionDescriptor;
typedef void* MTBinaryArchive;
typedef void* MTURL;

typedef enum MTBinaryArchiveError {
    MTBinaryArchiveErrorNone = 0,
    MTBinaryArchiveErrorInvalidFile = 1,
    MTBinaryArchiveErrorUnexpectedElement = 2,
    MTBinaryArchiveErrorCompilationFailure = 3,
    MTBinaryArchiveErrorInternalError = 4,
} MTBinaryArchiveError;

// Create a new MTLBinaryArchiveDescriptor
MT_INLINE MTBinaryArchiveDescriptor mt_binary_archive_descriptor_create(void) {
Class cls = objc_getClass("MTLBinaryArchiveDescriptor");
return (MTBinaryArchiveDescriptor)((id (*)(Class, SEL))objc_msgSend)(cls, sel_getUid("new"));
}

// Set the URL property
MT_INLINE void mt_binary_archive_descriptor_set_url(MTBinaryArchiveDescriptor desc, MTURL url) {
((void (*)(id, SEL, id))objc_msgSend)((id)desc, sel_getUid("setUrl:"), (id)url);
}

// Get the URL property
MT_INLINE MTURL mt_binary_archive_descriptor_get_url(MTBinaryArchiveDescriptor desc) {
return (MTURL)((id (*)(id, SEL))objc_msgSend)((id)desc, sel_getUid("url"));
}

// Set label
MT_INLINE void mt_binary_archive_set_label(MTBinaryArchive archive, const char* label) {
    SEL sel = sel_getUid("setLabel:");
    id str = ((id (*)(Class, SEL, const char*))objc_msgSend)(
           objc_getClass("NSString"),
           sel_getUid("stringWithUTF8String:"),
           label);
    ((void (*)(id, SEL, id))objc_msgSend)((id)archive, sel, str);
}

// Get device
MT_INLINE void* mt_binary_archive_get_device(MTBinaryArchive archive) {
return ((id (*)(id, SEL))objc_msgSend)((id)archive, sel_getUid("device"));
}

// Add Compute Pipeline
MT_INLINE bool mt_binary_archive_add_compute_pipeline(MTBinaryArchive archive, MTComputePipelineDescriptor desc, MTError* error_out) {
return ((BOOL (*)(id, SEL, id, MTError**))objc_msgSend)((id)archive, sel_getUid("addComputePipelineFunctionsWithDescriptor:error:"), (id)desc, (MTError**)error_out);
}

// Add Render Pipeline
MT_INLINE bool mt_binary_archive_add_render_pipeline(MTBinaryArchive archive, MTRenderPipelineDescriptor desc, MTError* error_out) {
return ((BOOL (*)(id, SEL, id, MTError**))objc_msgSend)((id)archive, sel_getUid("addRenderPipelineFunctionsWithDescriptor:error:"), (id)desc, (MTError**)error_out);
}

// Add Tile Render Pipeline
MT_INLINE bool mt_binary_archive_add_tile_pipeline(MTBinaryArchive archive, MTTileRenderPipelineDescriptor desc, MTError* error_out) {
return ((BOOL (*)(id, SEL, id, MTError**))objc_msgSend)((id)archive, sel_getUid("addTileRenderPipelineFunctionsWithDescriptor:error:"), (id)desc, (MTError**)error_out);
}

// Add Mesh Pipeline (available on macOS 15+ / iOS 18+)
MT_INLINE bool mt_binary_archive_add_mesh_pipeline(MTBinaryArchive archive, void* meshPipelineDescriptor, MTError* error_out) {
return ((BOOL (*)(id, SEL, id, MTError**))objc_msgSend)((id)archive, sel_getUid("addMeshRenderPipelineFunctionsWithDescriptor:error:"), (id)meshPipelineDescriptor, (MTError**)error_out);
}

// Add Stitched Library
MT_INLINE bool mt_binary_archive_add_library(MTBinaryArchive archive, MTStitchedLibraryDescriptor desc, MTError* error_out) {
return ((BOOL (*)(id, SEL, id, MTError**))objc_msgSend)((id)archive, sel_getUid("addLibraryWithDescriptor:error:"), (id)desc, (MTError**)error_out);
}

// Serialize to URL
MT_INLINE bool mt_binary_archive_serialize_to_url(MTBinaryArchive archive, MTURL url, MTError* error_out) {
return ((BOOL (*)(id, SEL, id, MTError**))objc_msgSend)((id)archive, sel_getUid("serializeToURL:error:"), (id)url, (MTError**)error_out);
}

// Add Function With Descriptor and Library
MT_INLINE bool mt_binary_archive_add_function(MTBinaryArchive archive, MTFunctionDescriptor descriptor, MTLibrary library, MTError* error_out) {
return ((BOOL (*)(id, SEL, id, id, MTError**))objc_msgSend)((id)archive, sel_getUid("addFunctionWithDescriptor:library:error:"), (id)descriptor, (id)library, (MTError**)error_out);
}
