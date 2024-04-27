//
//  gizmo_shader.metal
//  Metal C
//
//  Created by Lungile Maseko on 2025/06/06.
//
#include <metal_stdlib>
using namespace metal;

// Match buffer and attribute indices
enum {
    VertexBufferIndex_GizmoVertices = 0,
    VertexBufferIndex_GizmoUniforms = 1
};

struct GizmoInput {
    float3 position [[attribute(0)]];
    float4 color    [[attribute(1)]];
};

struct GizmoVarying {
    float4 position [[position]];
    float4 color;
};

struct GizmoUniforms {
    float4x4 mvp;
};

vertex GizmoVarying gizmo_vertex(GizmoInput in [[stage_in]],
                                 constant GizmoUniforms& uniforms [[buffer(VertexBufferIndex_GizmoUniforms)]])
{
    GizmoVarying out;
    out.position = uniforms.mvp * float4(in.position, 1.0);
    out.color = in.color;
    return out;
}

fragment float4 gizmo_fragment(GizmoVarying in [[stage_in]])
{
    return in.color;
}
