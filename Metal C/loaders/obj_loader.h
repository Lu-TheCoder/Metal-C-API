//
//  obj_loader.h
//  Metal C
//
//  Created by Lungile Maseko on 2025/06/06.
//
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//
//#define MAX_VERTICES 100000
//#define MAX_INDICES 100000
//
//typedef struct {
//    float x, y, z;
//} Vec3;
//
//typedef struct {
//    float u, v;
//} Vec2;
//
//typedef struct {
//    Vec3 pos;
//    Vec2 uv;
//    Vec3 normal;
//} Vertex;
//
//typedef struct {
//    Vertex* vertices;
//    unsigned int* indices;
//    size_t vertex_count;
//    size_t index_count;
//} Mesh;
//
//static Vec3 temp_positions[MAX_VERTICES];
//static Vec2 temp_texcoords[MAX_VERTICES];
//static Vec3 temp_normals[MAX_VERTICES];
//
//static Vertex final_vertices[MAX_VERTICES];
//static unsigned int final_indices[MAX_INDICES];
//
//static size_t pos_count = 0, uv_count = 0, norm_count = 0;
//static size_t vert_index = 0, idx_index = 0;
//
//int parse_obj(const char* path, Mesh* out_mesh) {
//    FILE* file = fopen(path, "r");
//    if (!file) {
//        printf("No FIle! \n");
//        return 0;
//    }
//
//    char line[512];
//    while (fgets(line, sizeof(line), file)) {
//        if (strncmp(line, "v ", 2) == 0) {
//            sscanf(line + 2, "%f %f %f",
//                   &temp_positions[pos_count].x,
//                   &temp_positions[pos_count].y,
//                   &temp_positions[pos_count].z);
//            pos_count++;
//        } else if (strncmp(line, "vt ", 3) == 0) {
//            sscanf(line + 3, "%f %f",
//                   &temp_texcoords[uv_count].u,
//                   &temp_texcoords[uv_count].v);
//            uv_count++;
//        } else if (strncmp(line, "vn ", 3) == 0) {
//            sscanf(line + 3, "%f %f %f",
//                   &temp_normals[norm_count].x,
//                   &temp_normals[norm_count].y,
//                   &temp_normals[norm_count].z);
//            norm_count++;
//        } else if (strncmp(line, "f ", 2) == 0) {
//            unsigned int vi[3], ti[3], ni[3];
//            sscanf(line + 2, "%u/%u/%u %u/%u/%u %u/%u/%u",
//                   &vi[0], &ti[0], &ni[0],
//                   &vi[1], &ti[1], &ni[1],
//                   &vi[2], &ti[2], &ni[2]);
//
//            for (int i = 0; i < 3; i++) {
//                Vertex v;
//                v.pos = temp_positions[vi[i] - 1];
//                v.uv = temp_texcoords[ti[i] - 1];
//                v.normal = temp_normals[ni[i] - 1];
//
//                final_vertices[vert_index] = v;
//                final_indices[idx_index] = (unsigned int)vert_index;
//
//                vert_index++;
//                idx_index++;
//            }
//        }
//    }
//
//    fclose(file);
//
//    out_mesh->vertices = final_vertices;
//    out_mesh->indices = final_indices;
//    out_mesh->vertex_count = vert_index;
//    out_mesh->index_count = idx_index;
//    
//    printf("Parsed Obj File successfully.\n");
//    return 1;
//}

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX_VERTICES 10000
#define MAX_INDICES  20000
#define MAX_LINE     512

typedef struct {
    float x, y, z;
} Vec3;

typedef struct {
    float u, v;
} Vec2;

typedef struct {
    uint32_t v, vt, vn;
} VertexIndex;

typedef struct {
    Vec3 position;
    Vec3 normal;
    Vec2 uv;
} Vertex;

// Align to 16 bytes for Metal compatibility
_Static_assert(sizeof(Vertex) == 32, "Vertex size must be 32 bytes (Metal aligned)");

typedef struct {
    Vertex* vertex_data;
    uint32_t* index_data;
    size_t vertex_count;
    size_t index_count;
} Mesh;

static Vec3 positions[MAX_VERTICES];
static Vec3 normals[MAX_VERTICES];
static Vec2 uvs[MAX_VERTICES];
static Vertex vertices[MAX_VERTICES];
static uint32_t indices[MAX_INDICES];

static size_t position_count = 0;
static size_t normal_count = 0;
static size_t uv_count = 0;
static size_t vertex_count = 0;
static size_t index_count = 0;

static bool vertex_equals(const Vertex* a, const Vertex* b) {
    return memcmp(a, b, sizeof(Vertex)) == 0;
}

static int find_or_add_vertex(Vertex v) {
    for (size_t i = 0; i < vertex_count; ++i) {
        if (vertex_equals(&vertices[i], &v)) return (int)i;
    }
    if (vertex_count >= MAX_VERTICES) return -1; // overflow
    vertices[vertex_count] = v;
    return (int)vertex_count++;
}

static void parse_face(char* line) {
    VertexIndex face[4];
    int num = sscanf(line, "f %u/%u/%u %u/%u/%u %u/%u/%u %u/%u/%u",
        &face[0].v, &face[0].vt, &face[0].vn,
        &face[1].v, &face[1].vt, &face[1].vn,
        &face[2].v, &face[2].vt, &face[2].vn,
        &face[3].v, &face[3].vt, &face[3].vn);

    int verts = num / 3;
    if (verts < 3) return;

    for (int i = 1; i < verts - 1; ++i) {
        VertexIndex tri[3] = { face[0], face[i], face[i + 1] };
        for (int j = 0; j < 3; ++j) {
            VertexIndex vi = tri[j];
            if (vi.v == 0 || vi.vt == 0 || vi.vn == 0) continue;

            Vertex v = {
                .position = positions[vi.v - 1],
                .normal = normals[vi.vn - 1],
                .uv = uvs[vi.vt - 1]
            };
            int idx = find_or_add_vertex(v);
            if (idx >= 0 && index_count < MAX_INDICES) {
                indices[index_count++] = (uint32_t)idx;
            }
        }
    }
}

bool load_obj(const char* filename, Mesh* mesh) {
    FILE* file = fopen(filename, "r");
    if (!file) return false;

    // Reset counters
    position_count = normal_count = uv_count = vertex_count = index_count = 0;

    char line[MAX_LINE];
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "v ", 2) == 0) {
            Vec3 pos;
            sscanf(line + 2, "%f %f %f", &pos.x, &pos.y, &pos.z);
            positions[position_count++] = pos;
        } else if (strncmp(line, "vn ", 3) == 0) {
            Vec3 norm;
            sscanf(line + 3, "%f %f %f", &norm.x, &norm.y, &norm.z);
            normals[normal_count++] = norm;
        } else if (strncmp(line, "vt ", 3) == 0) {
            Vec2 tex;
            sscanf(line + 3, "%f %f", &tex.u, &tex.v);
            uvs[uv_count++] = tex;
        } else if (strncmp(line, "f ", 2) == 0) {
            parse_face(line);
        }
    }

    fclose(file);

    // Allocate and copy data to heap (Metal buffer will use this)
    mesh->vertex_data = malloc(sizeof(Vertex) * vertex_count);
    mesh->index_data = malloc(sizeof(uint32_t) * index_count);

    if (!mesh->vertex_data || !mesh->index_data) return false;

    memcpy(mesh->vertex_data, vertices, sizeof(Vertex) * vertex_count);
    memcpy(mesh->index_data, indices, sizeof(uint32_t) * index_count);
    mesh->vertex_count = vertex_count;
    mesh->index_count = index_count;

    return true;
}

void free_mesh(Mesh* mesh) {
    if (mesh) {
        free(mesh->vertex_data);
        free(mesh->index_data);
        mesh->vertex_data = NULL;
        mesh->index_data = NULL;
        mesh->vertex_count = 0;
        mesh->index_count = 0;
    }
}
