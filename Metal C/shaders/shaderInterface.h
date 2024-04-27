//
//  shaderInterface.h
//  Metal C
//
//  Created by Lungile Maseko on 2024/06/02.
//

#pragma once
#include <simd/simd.h>
// This header is shared between our C++ code and
// our Metal shaders, so we have a common interface
// for sending data from the CPU to the GPU

enum VertexAttributeIndex {
    VertexAttributeIndex_Position = 0,
    VertexAttributeIndex_Normal = 1,
    VertexAttributeIndex_UV = 2,
    VertexAttributeIndex_Color = 3,
    VertexAttributeIndex_TexCoords = 4,
    VertexAttributeIndex_Count
};

enum VertexBufferIndex  {
    VertexBufferIndex_Attributes = 0,
    VertexBufferIndex_Uniforms = 1,
    BufferIndexCount
};

typedef struct Uniforms {
    matrix_float4x4 mvp;
    vector_float4 color;
}__attribute__((packed)) Uniforms;
