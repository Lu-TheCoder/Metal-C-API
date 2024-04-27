//
//  shaderInterface.h
//  Metal C
//
//  Created by Lungile Maseko on 2024/06/02.
//

#pragma once
#include "../Math/GMath.h"

// This header is shared between our C++ code and
// our Metal shaders, so we have a common interface
// for sending data from the CPU to the GPU

enum VertexAttributeIndex {
    VertexAttributeIndex_Position = 0,
    VertexAttributeIndex_Color = 1,
    VertexAttributeIndex_TexCoords = 2,
    VertexAttributeIndex_Count
};

enum VertexBufferIndex  {
    VertexBufferIndex_Attributes = 0,
    VertexBufferIndex_Uniforms = 1,
    BufferIndexCount
};

typedef struct Uniforms {
    vfloat2 pos;
    vfloat4 color;
}__attribute__((packed)) Uniforms;
