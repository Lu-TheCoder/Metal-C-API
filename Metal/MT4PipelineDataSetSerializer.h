//
//  MT4PipelineDataSetSerializer.h
//  Metal C
//
//  MTL4PipelineDataSetSerializer — captures the pipeline descriptors / binaries
//  a compiler produces and serializes them to a binary archive on disk (for
//  warm pipeline caches) or to a pipelines script for the offline generator.
//
//  Attach a serializer to a compiler via the compiler descriptor
//  (set its pipelineDataSetSerializer), then serialize after building pipelines.
//

#pragma once
#include "MTFoundation/defines.h"
#include "MTFoundation/MTURL.h"     // MTURL, mt_url_*
#include "MTFoundation/MTString.h"

// What the serializer captures (Metal's MTL4PipelineDataSetSerializerConfiguration).
typedef enum MT4PipelineDataSetSerializerConfiguration : unsigned long {
    MT4PipelineDataSetSerializerConfigurationCaptureDescriptors = 1 << 0,
    MT4PipelineDataSetSerializerConfigurationCaptureBinaries    = 1 << 1,
} MT4PipelineDataSetSerializerConfiguration;

MT_INLINE MT4PipelineDataSetSerializerDescriptor mt4_pipeline_data_set_serializer_descriptor_create(void) {
    return MT_ALLOC_INIT("MTL4PipelineDataSetSerializerDescriptor");
}

MT_INLINE void mt4_pipeline_data_set_serializer_descriptor_set_configuration(MT4PipelineDataSetSerializerDescriptor desc, MT4PipelineDataSetSerializerConfiguration config) {
    MT_MSG_SEND_1(void, desc, MT_SEL("setConfiguration:"), MT4PipelineDataSetSerializerConfiguration, config);
}

MT_INLINE MT4PipelineDataSetSerializer mt4_device_create_pipeline_data_set_serializer(MTDevice device, MT4PipelineDataSetSerializerDescriptor desc) {
    return MT_MSG_SEND_1(void*, device, MT_SEL("newPipelineDataSetSerializerWithDescriptor:"), id, desc);
}

// Write the captured data to `url` as a binary archive. Returns true on success.
MT_INLINE bool mt4_pipeline_data_set_serializer_serialize_to_url(MT4PipelineDataSetSerializer serializer, MTURL url, MTError* outError) {
    return MT_MSG_SEND_2(bool, serializer, MT_SEL("serializeAsArchiveAndFlushToURL:error:"), id, url, MTError*, outError);
}
