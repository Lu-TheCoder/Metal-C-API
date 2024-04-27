//
//  shaders.metal
//  Metal C
//
//  Created by Lungile Maseko on 2024/06/02.
//

#include <metal_stdlib>

using namespace metal;

#include "shaderInterface.h"

struct VertexInput {
    float3 position [[attribute(VertexAttributeIndex_Position)]];
    float3 normal [[attribute(VertexAttributeIndex_Normal)]];
    float3 uv [[attribute(VertexAttributeIndex_UV)]];
};

struct ShaderInOut {
    float4 position [[position]];
    float4 color;
};

vertex ShaderInOut vert(VertexInput in [[stage_in]],
                        constant Uniforms& uniforms [[buffer(VertexBufferIndex_Uniforms)]])
{
    ShaderInOut out;
    float4 pos = float4(in.position, 1.0);
    out.position = uniforms.mvp * pos;
    out.color = uniforms.color;
    return out;
}

fragment float4 frag(ShaderInOut in [[stage_in]])
{
    return in.color;
}

