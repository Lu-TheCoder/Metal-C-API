//
//  VertexData.h
//  Metal C
//
//  Created by Lungile Maseko on 2024/06/06.
//

#pragma once
#include <simd/simd.h>

typedef struct VertexData {
    simd_float4 position;
    simd_float4 textureCoordinate;
}VertexData;

typedef struct TransformationData {
    simd_float4x4 modelMatrix;
    simd_float4x4 viewMatrix;
    simd_float4x4 perspectiveMatrix;
}TransformationData;
