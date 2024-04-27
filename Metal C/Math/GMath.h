//
//  GMath.h
//  Metal C
//
//  Created by Lungile Maseko on 2024/06/04.
//

#pragma once
#include <simd/simd.h>
#include <math.h>

#define COLOR(r, g, b, a) ((vector_float4){(r)/255.0f, (g)/255.0f, (b)/255.0f, (a)/255.0f})

typedef struct vfloat2
{
    float x, y;
}vfloat2;

typedef struct vfloat3
{
    float x, y, z;
}vfloat3;

typedef union vfloat4
{
    struct {
        float x, y, z, w;
    };
    struct {
        float r, g, b, a;
    };
}vfloat4;

typedef struct {
    vector_float3 position;
    vector_float4 color; // optional, if you want per-vertex color
} GizmoVertex;

matrix_float4x4 make_perspective_matrix(float fovY, float aspect, float nearZ, float farZ) {
    float yScale = 1.0f / tanf(fovY * 0.5f);
    float xScale = yScale / aspect;
    float zRange = farZ - nearZ;
    float zScale = -(farZ + nearZ) / zRange;
    float wzScale = -2 * farZ * nearZ / zRange;

    matrix_float4x4 m = {{
        { xScale, 0, 0, 0 },
        { 0, yScale, 0, 0 },
        { 0, 0, zScale, -1 },
        { 0, 0, wzScale, 0 }
    }};
    return m;
}

matrix_float4x4 make_translation(float x, float y, float z) {
    return (matrix_float4x4){{
        { 1, 0, 0, 0 },
        { 0, 1, 0, 0 },
        { 0, 0, 1, 0 },
        { x, y, z, 1 }
    }};
}

matrix_float4x4 rotate_y(float radians) {
    return (matrix_float4x4){{
        { cosf(radians), 0, sinf(radians), 0 },
        { 0, 1, 0, 0 },
        { -sinf(radians), 0, cosf(radians), 0 },
        { 0, 0, 0, 1 }
    }};
}

#define CYLINDER_SEGMENTS 10
#define CYLINDER_RADIUS 0.006f

#define CONE_HEIGHT 0.2f
#define CONE_RADIUS 0.05f
#define CONE_SEGMENTS 16

// Cross product helper
Vec3 cross(Vec3 a, Vec3 b) {
    return (Vec3){a.y*b.z - a.z*b.y,
                  a.z*b.x - a.x*b.z,
                  a.x*b.y - a.y*b.x};
}

// Normalize helper
vector_float3 normalize3(vector_float3 v) {
    return simd_normalize(v);
}

// Multiply vec3 by scalar
vector_float3 mul3(vector_float3 v, float s) {
    return v * s;
}

// Add two vec3
vector_float3 add3(vector_float3 a, vector_float3 b) {
    return a + b;
}

GizmoVertex* generate_cylinder_strip(vector_float3 start, vector_float3 end, vector_float4 color, int* outVertexCount) {
    vector_float3 axis = simd_normalize(end - start);
    vector_float3 tmp = fabsf(axis.x) < 0.99f ? (vector_float3){1, 0, 0} : (vector_float3){0, 1, 0};
    vector_float3 side1 = simd_normalize(simd_cross(axis, tmp));
    vector_float3 side2 = simd_cross(axis, side1);

    int ringSegments = CYLINDER_SEGMENTS;
    int totalVerts = (ringSegments + 1) * 2;  // +1 to close the loop
    GizmoVertex* verts = malloc(sizeof(GizmoVertex) * totalVerts);

    for (int i = 0; i <= ringSegments; i++) {
        float angle = 2.0f * M_PI * i / ringSegments;
        float cosA = cosf(angle);
        float sinA = sinf(angle);
        vector_float3 offset = (side1 * cosA + side2 * sinA) * CYLINDER_RADIUS;

        // Bottom ring vertex
        verts[i * 2].position = start + offset;
        verts[i * 2].color = color;

        // Top ring vertex
        verts[i * 2 + 1].position = end + offset;
        verts[i * 2 + 1].color = color;
    }

    *outVertexCount = totalVerts;
    return verts;
}

GizmoVertex* generate_cone_triangles(vector_float3 baseCenter, vector_float3 direction, float height, float radius, vector_float4 color, int* outVertexCount) {
    vector_float3 axis = simd_normalize(direction);
    vector_float3 tmp = fabsf(axis.x) < 0.99f ? (vector_float3){1, 0, 0} : (vector_float3){0, 1, 0};
    vector_float3 side1 = simd_normalize(simd_cross(axis, tmp));
    vector_float3 side2 = simd_cross(axis, side1);

    int segments = CONE_SEGMENTS;
    int triangleCount = segments;
    int totalVerts = triangleCount * 3;

    GizmoVertex* verts = malloc(sizeof(GizmoVertex) * totalVerts);

    vector_float3 tip = baseCenter + axis * height;

    for (int i = 0; i < segments; i++) {
        float angle0 = 2.0f * M_PI * i / segments;
        float angle1 = 2.0f * M_PI * (i + 1) / segments;

        vector_float3 offset0 = (side1 * cosf(angle0) + side2 * sinf(angle0)) * radius;
        vector_float3 offset1 = (side1 * cosf(angle1) + side2 * sinf(angle1)) * radius;

        vector_float3 p0 = baseCenter + offset0;
        vector_float3 p1 = baseCenter + offset1;

        // Triangle: tip, p0, p1
        verts[i * 3 + 0].position = tip;
        verts[i * 3 + 0].color = color;

        verts[i * 3 + 1].position = p0;
        verts[i * 3 + 1].color = color;

        verts[i * 3 + 2].position = p1;
        verts[i * 3 + 2].color = color;
    }

    *outVertexCount = totalVerts;
    return verts;
}
