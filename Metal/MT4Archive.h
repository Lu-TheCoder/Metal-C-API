//
//  MT4Archive.h
//  Metal C
//
//  MTL4Archive — a serialized set of pipeline binaries on disk (produced by an
//  MT4PipelineDataSetSerializer). Open it from a URL and look up pipeline
//  states by descriptor to skip recompilation. Pass an archive to a compiler
//  via MT4CompilerTaskOptions.lookupArchives (see MT4CompilerTask.h).
//

#pragma once
#include "MTFoundation/defines.h"
#include "MTFoundation/MTURL.h"
#include "MTFoundation/MTString.h"  // mt_object_set_label

MT_INLINE MT4Archive mt4_device_create_archive_with_url(MTDevice device, MTURL url, MTError* outError) {
    return MT_MSG_SEND_2(void*, device, MT_SEL("newArchiveWithURL:error:"), id, url, MTError*, outError);
}

MT_INLINE void mt4_archive_set_label(MT4Archive archive, const char* label) {
    mt_object_set_label(archive, label);
}

// Look up a previously-serialized render pipeline state (+1 owned).
MT_INLINE MTRenderPipelineState mt4_archive_create_render_pipeline_state(MT4Archive archive, MT4RenderPipelineDescriptor desc, MTError* outError) {
    return MT_MSG_SEND_2(void*, archive, MT_SEL("newRenderPipelineStateWithDescriptor:error:"), id, desc, MTError*, outError);
}

// Look up a previously-serialized compute pipeline state (+1 owned).
MT_INLINE MTComputePipelineState mt4_archive_create_compute_pipeline_state(MT4Archive archive, MT4ComputePipelineDescriptor desc, MTError* outError) {
    return MT_MSG_SEND_2(void*, archive, MT_SEL("newComputePipelineStateWithDescriptor:error:"), id, desc, MTError*, outError);
}
