//
//  shaders.metal
//  Metal C
//
//  Created by Lungile Maseko on 2024/06/02.
//

#include <metal_stdlib>

using namespace metal;

#include "shaderInterface.h"
//#include "../Math/GMath.h"

struct VertexInput {
    float2 position [[attribute(VertexAttributeIndex_Position)]];
};

struct ShaderInOut {
    float4 position [[position]];
    float4 color;
};

vertex ShaderInOut vert(VertexInput in [[stage_in]],
                        constant Uniforms& uniforms [[buffer(VertexBufferIndex_Uniforms)]])
{
    ShaderInOut out;
    out.position = float4(in.position.x + uniforms.pos.x, in.position.y + uniforms.pos.y, 0.0, 1.0);
    out.color = float4(uniforms.color.r, uniforms.color.g, uniforms.color.b, uniforms.color.a);
    return out;
}

fragment float4 frag(ShaderInOut in [[stage_in]])
{
    return in.color;
}
