//
//  MTForwardDecls.h
//  Metal C
//
//  Created on 2026-05-30.
//
//  Opaque, type-safe handles.
//
//  Each Metal object is exposed as a pointer to a distinct (never-defined)
//  struct. This costs nothing at runtime — every handle is still a single
//  pointer — but lets the C compiler catch mistakes like passing an MTTexture
//  where an MTBuffer is expected, or assigning one handle type to another.
//
//  The objc_msgSend wrapper macros (see MTFoundation/defines.h) take and
//  return values through `(id)` / `void*`, both of which convert cleanly to
//  and from these handles, so the wrapper's own inline functions stay
//  warning-free while *your* call sites get checked.
//
//  Note on Metal's class hierarchy: C has no subtyping, so the "base" handles
//  (MTResource, MTDrawable) are distinct types from their concrete leaves
//  (MTBuffer/MTTexture, CAMetalDrawable). When you intentionally treat a leaf
//  as its base — e.g. querying storage mode on a buffer via an MTResource
//  function — use an explicit cast: mt_resource_get_storage_mode((MTResource)buffer).
//  The cast is the signal that you meant it.

#pragma once

#define MT_HANDLE(name) typedef struct name##_s* name

MT_HANDLE(CAMetalDrawable);
MT_HANDLE(CGColorSpace);
MT_HANDLE(MTAccelerationStructure);
MT_HANDLE(MTArray);
MT_HANDLE(MTArrayType);
MT_HANDLE(MTAttribute);
MT_HANDLE(MTAutoreleasePool);
MT_HANDLE(MTBinaryArchive);
MT_HANDLE(MTBinaryArchiveDescriptor);
MT_HANDLE(MTBinding);
MT_HANDLE(MTBlitCommandEncoder);
MT_HANDLE(MTBlitPassDescriptor);
MT_HANDLE(MTBuffer);
MT_HANDLE(MTBufferBinding);
MT_HANDLE(MTBundle);
MT_HANDLE(MTCommandBuffer);
MT_HANDLE(MTCommandBufferDescriptor);
MT_HANDLE(MTCommandQueue);
MT_HANDLE(MTCommandQueueDescriptor);
MT_HANDLE(MTCompileOptions);
MT_HANDLE(MTComputeCommandEncoder);
MT_HANDLE(MTComputePipelineDescriptor);
MT_HANDLE(MTComputePipelineState);
MT_HANDLE(MTDepthStencilDescriptor);
MT_HANDLE(MTDepthStencilState);
MT_HANDLE(MTDevice);
MT_HANDLE(MTDictionary);
MT_HANDLE(MTDrawable);
MT_HANDLE(MTError);
MT_HANDLE(MTEvent);
MT_HANDLE(MTFence);
MT_HANDLE(MTFunction);
MT_HANDLE(MTFunctionConstantValues);
MT_HANDLE(MTFunctionDescriptor);
MT_HANDLE(MTHeap);
MT_HANDLE(MTHeapDescriptor);
MT_HANDLE(MTIOCommandBuffer);
MT_HANDLE(MTIOCommandQueue);
MT_HANDLE(MTIOCommandQueueDescriptor);
MT_HANDLE(MTIOCompressionContext);
MT_HANDLE(MTIOFileHandle);
MT_HANDLE(MTIndirectCommandBuffer);
MT_HANDLE(MTIndirectCommandBufferDescriptor);
MT_HANDLE(MTIndirectComputeCommand);
MT_HANDLE(MTIndirectRenderCommand);
MT_HANDLE(MTIntersectionFunctionDescriptor);
MT_HANDLE(MTIntersectionFunctionTable);
MT_HANDLE(MTLFunctionConstant);
MT_HANDLE(MTLibrary);
MT_HANDLE(MTObjectPayloadBinding);
MT_HANDLE(MTPipelineBufferDescriptor);
MT_HANDLE(MTPointerType);
MT_HANDLE(MTRenderCommandEncoder);
MT_HANDLE(MTRenderPassAttachmentDescriptor);
MT_HANDLE(MTRenderPassColorAttachmentDescriptor);
MT_HANDLE(MTRenderPassColorAttachmentDescriptorArray);
MT_HANDLE(MTRenderPassDescriptor);
MT_HANDLE(MTRenderPipelineColorAttachmentDescriptor);
MT_HANDLE(MTRenderPipelineColorAttachmentDescriptorArray);
MT_HANDLE(MTRenderPipelineDescriptor);
MT_HANDLE(MTRenderPipelineReflection);
MT_HANDLE(MTComputePipelineReflection);
MT_HANDLE(MTRenderPipelineState);
MT_HANDLE(MTResource);
MT_HANDLE(MTSamplerDescriptor);
MT_HANDLE(MTSamplerState);
MT_HANDLE(MTSharedEvent);
MT_HANDLE(MTSharedTextureHandle);
MT_HANDLE(MTStencilDescriptor);
MT_HANDLE(MTStitchedLibraryDescriptor);
MT_HANDLE(MTString);
MT_HANDLE(MTStructMember);
MT_HANDLE(MTStructType);
MT_HANDLE(MTTexture);
MT_HANDLE(MTTextureBinding);
MT_HANDLE(MTTextureDescriptor);
MT_HANDLE(MTTextureReferenceType);
MT_HANDLE(MTThreadgroupBinding);
MT_HANDLE(MTTileRenderPipelineDescriptor);
MT_HANDLE(MTType);
MT_HANDLE(MTURL);
MT_HANDLE(MTVertexAttribute);
MT_HANDLE(MTVertexAttributeDescriptor);
MT_HANDLE(MTVertexAttributeDescriptorArray);
MT_HANDLE(MTVertexBufferLayoutDescriptor);
MT_HANDLE(MTVertexBufferLayoutDescriptorArray);
MT_HANDLE(MTVertexDescriptor);
MT_HANDLE(MTVisibleFunctionTable);
MT_HANDLE(MT_CAMetalDrawable);
MT_HANDLE(MT_CAMetalLayer);

// ============================================================================
// Metal 4 (MTL4*) — the parallel command-submission API (SDK 26 / macOS 26).
// Coexists with the classic handles above. C functions use the mt4_* prefix.
// ============================================================================
MT_HANDLE(MTAllocation);            // base of any GPU allocation (resource/heap)
MT_HANDLE(MTResidencySet);
MT_HANDLE(MTResidencySetDescriptor);
MT_HANDLE(MT4CommandQueue);
MT_HANDLE(MT4CommandQueueDescriptor);
MT_HANDLE(MT4CommitOptions);
MT_HANDLE(MT4CommandBuffer);
MT_HANDLE(MT4CommandBufferOptions);
MT_HANDLE(MT4CommandEncoder);        // base protocol of the MTL4 encoders
MT_HANDLE(MT4CommandAllocator);
MT_HANDLE(MT4CommandAllocatorDescriptor);
MT_HANDLE(MT4RenderCommandEncoder);
MT_HANDLE(MT4ComputeCommandEncoder);
MT_HANDLE(MT4MachineLearningCommandEncoder);
MT_HANDLE(MT4ArgumentTable);
MT_HANDLE(MT4ArgumentTableDescriptor);
MT_HANDLE(MT4RenderPassDescriptor);
MT_HANDLE(MT4Compiler);
MT_HANDLE(MT4CompilerDescriptor);
MT_HANDLE(MT4RenderPipelineState);
MT_HANDLE(MT4RenderPipelineDescriptor);
MT_HANDLE(MT4ComputePipelineState);
MT_HANDLE(MT4ComputePipelineDescriptor);
MT_HANDLE(MT4MachineLearningPipelineState);
MT_HANDLE(MT4MachineLearningPipelineReflection);
MT_HANDLE(MT4PipelineOptions);
MT_HANDLE(MT4PipelineState);
MT_HANDLE(MT4Archive);
MT_HANDLE(MT4CounterHeap);
MT_HANDLE(MT4CounterHeapDescriptor);
MT_HANDLE(MT4PipelineDataSetSerializer);
MT_HANDLE(MT4PipelineDataSetSerializerDescriptor);
MT_HANDLE(MT4BinaryFunction);
MT_HANDLE(MT4BinaryFunctionDescriptor);
MT_HANDLE(MT4FunctionDescriptor);
MT_HANDLE(MT4LibraryFunctionDescriptor);
MT_HANDLE(MT4LibraryDescriptor);
MT_HANDLE(MT4PipelineDescriptor);                       // base of render/compute pipeline descriptors
MT_HANDLE(MT4RenderPipelineColorAttachmentDescriptor);
MT_HANDLE(MT4RenderPipelineColorAttachmentDescriptorArray);
MT_HANDLE(MT4MachineLearningPipelineDescriptor);
MT_HANDLE(MT4CompilerTask);
MT_HANDLE(MT4CompilerTaskOptions);
MT_HANDLE(MT4CommitFeedback);
MT_HANDLE(MTDynamicLibrary);
