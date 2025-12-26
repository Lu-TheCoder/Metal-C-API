//
//  MTBinaryArchive.h
//  Metal C
//
//  Created by Lungile Maseko on 2025/06/05.
//
#pragma once
#include "MTFoundation/defines.h"

typedef void* MTComputePipelineDescriptor;
typedef void* MTRenderPipelineDescriptor;
typedef void* MTTileRenderPipelineDescriptor;
typedef void* MTStitchedLibraryDescriptor;
typedef void* MTBinaryArchiveDescriptor;
typedef void* MTFunctionDescriptor;
typedef void* MTBinaryArchive;
typedef void* MTURL;
typedef void* MTLibrary;
typedef void* MTError;

typedef enum MTBinaryArchiveError {
    MTBinaryArchiveErrorNone = 0,
    MTBinaryArchiveErrorInvalidFile = 1,
    MTBinaryArchiveErrorUnexpectedElement = 2,
    MTBinaryArchiveErrorCompilationFailure = 3,
    MTBinaryArchiveErrorInternalError = 4,
} MTBinaryArchiveError;

// Create a new MTLBinaryArchiveDescriptor
MT_INLINE MTBinaryArchiveDescriptor mt_binary_archive_descriptor_create(void) {
    return MT_MSG_SEND_CLASS(id, MT_CLASS("MTLBinaryArchiveDescriptor"), MT_SEL("new"));
}

// Set the URL property
MT_INLINE void mt_binary_archive_descriptor_set_url(MTBinaryArchiveDescriptor desc, MTURL url) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setUrl:"), id, url);
}

// Get the URL property
MT_INLINE MTURL mt_binary_archive_descriptor_get_url(MTBinaryArchiveDescriptor desc) {
    return MT_MSG_SEND(id, desc, MT_SEL("url"));
}

// Set label
MT_INLINE void mt_binary_archive_set_label(MTBinaryArchive archive, const char* label) {
    id str = MT_MSG_SEND_CLASS_1(id, MT_CLASS("NSString"), MT_SEL("stringWithUTF8String:"), const char*, label);
    MT_MSG_SEND_1(void, archive, MT_SEL("setLabel:"), id, str);
}

// Get device
MT_INLINE void* mt_binary_archive_get_device(MTBinaryArchive archive) {
    return MT_MSG_SEND(id, archive, MT_SEL("device"));
}

// Add Compute Pipeline
MT_INLINE bool mt_binary_archive_add_compute_pipeline(MTBinaryArchive archive, MTComputePipelineDescriptor desc, MTError** outError) {
    return MT_MSG_SEND_2(BOOL, archive, MT_SEL("addComputePipelineFunctionsWithDescriptor:error:"), id, desc, MTError**, outError);
}

// Add Render Pipeline
MT_INLINE bool mt_binary_archive_add_render_pipeline(MTBinaryArchive archive, MTRenderPipelineDescriptor desc, MTError** outError) {
    return MT_MSG_SEND_2(BOOL, archive, MT_SEL("addRenderPipelineFunctionsWithDescriptor:error:"), id, desc, MTError**, outError);
}

// Add Tile Render Pipeline
MT_INLINE bool mt_binary_archive_add_tile_pipeline(MTBinaryArchive archive, MTTileRenderPipelineDescriptor desc, MTError** outError) {
    return MT_MSG_SEND_2(BOOL, archive, MT_SEL("addTileRenderPipelineFunctionsWithDescriptor:error:"), id, desc, MTError**, outError);
}

// Add Mesh Pipeline (available on macOS 15+ / iOS 18+)
MT_INLINE bool mt_binary_archive_add_mesh_pipeline(MTBinaryArchive archive, void* meshPipelineDescriptor, MTError** outError) {
    return MT_MSG_SEND_2(BOOL, archive, MT_SEL("addMeshRenderPipelineFunctionsWithDescriptor:error:"), id, meshPipelineDescriptor, MTError**, outError);
}

// Add Stitched Library
MT_INLINE bool mt_binary_archive_add_library(MTBinaryArchive archive, MTStitchedLibraryDescriptor desc, MTError** outError) {
    return MT_MSG_SEND_2(BOOL, archive, MT_SEL("addLibraryWithDescriptor:error:"), id, desc, MTError**, outError);
}

// Serialize to URL
MT_INLINE bool mt_binary_archive_serialize_to_url(MTBinaryArchive archive, MTURL url, MTError** outError) {
    return MT_MSG_SEND_2(BOOL, archive, MT_SEL("serializeToURL:error:"), id, url, MTError**, outError);
}

// Add Function With Descriptor and Library
MT_INLINE bool mt_binary_archive_add_function(MTBinaryArchive archive, MTFunctionDescriptor descriptor, MTLibrary library, MTError** outError) {
    return MT_MSG_SEND_3(BOOL, archive, MT_SEL("addFunctionWithDescriptor:library:error:"), id, descriptor, id, library, MTError**, outError);
}
