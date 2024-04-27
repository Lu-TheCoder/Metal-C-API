//
//  GMath.h
//  Metal C
//
//  Created by Lungile Maseko on 2024/06/04.
//

#pragma once

typedef struct vfloat2
{
    float x, y;
}vfloat2;

typedef union vfloat4
{
    struct {
        float x, y, z, w;
    };
    struct {
        float r, g, b, a;
    };
}vfloat4;
