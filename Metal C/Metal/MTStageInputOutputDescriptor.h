//
//  MTStageInputOutputDescriptor.h
//  Metal C
//
//  Created by Lungile Maseko on 2024/06/06.
//

#pragma once

typedef enum MTAttributeFormat {
    MTAttributeFormatInvalid = 0,
    MTAttributeFormatUChar2 = 1,
    MTAttributeFormatUChar3 = 2,
    MTAttributeFormatUChar4 = 3,
    MTAttributeFormatChar2 = 4,
    MTAttributeFormatChar3 = 5,
    MTAttributeFormatChar4 = 6,
    MTAttributeFormatUChar2Normalized = 7,
    MTAttributeFormatUChar3Normalized = 8,
    MTAttributeFormatUChar4Normalized = 9,
    MTAttributeFormatChar2Normalized = 10,
    MTAttributeFormatChar3Normalized = 11,
    MTAttributeFormatChar4Normalized = 12,
    MTAttributeFormatUShort2 = 13,
    MTAttributeFormatUShort3 = 14,
    MTAttributeFormatUShort4 = 15,
    MTAttributeFormatShort2 = 16,
    MTAttributeFormatShort3 = 17,
    MTAttributeFormatShort4 = 18,
    MTAttributeFormatUShort2Normalized = 19,
    MTAttributeFormatUShort3Normalized = 20,
    MTAttributeFormatUShort4Normalized = 21,
    MTAttributeFormatShort2Normalized = 22,
    MTAttributeFormatShort3Normalized = 23,
    MTAttributeFormatShort4Normalized = 24,
    MTAttributeFormatHalf2 = 25,
    MTAttributeFormatHalf3 = 26,
    MTAttributeFormatHalf4 = 27,
    MTAttributeFormatFloat = 28,
    MTAttributeFormatFloat2 = 29,
    MTAttributeFormatFloat3 = 30,
    MTAttributeFormatFloat4 = 31,
    MTAttributeFormatInt = 32,
    MTAttributeFormatInt2 = 33,
    MTAttributeFormatInt3 = 34,
    MTAttributeFormatInt4 = 35,
    MTAttributeFormatUInt = 36,
    MTAttributeFormatUInt2 = 37,
    MTAttributeFormatUInt3 = 38,
    MTAttributeFormatUInt4 = 39,
    MTAttributeFormatInt1010102Normalized = 40,
    MTAttributeFormatUInt1010102Normalized = 41,
    MTAttributeFormatUChar4Normalized_BGRA = 42,
    MTAttributeFormatUChar = 45,
    MTAttributeFormatChar = 46,
    MTAttributeFormatUCharNormalized = 47,
    MTAttributeFormatCharNormalized = 48,
    MTAttributeFormatUShort = 49,
    MTAttributeFormatShort = 50,
    MTAttributeFormatUShortNormalized = 51,
    MTAttributeFormatShortNormalized = 52,
    MTAttributeFormatHalf = 53,
    MTAttributeFormatFloatRG11B10 = 54,
    MTAttributeFormatFloatRGB9E5 = 55,
}MTAttributeFormat;

typedef enum MTIndexType {
    MTIndexTypeUInt16 = 0,
    MTIndexTypeUInt32 = 1,
}MTIndexType;

typedef enum MTStepFunction {
    MTStepFunctionConstant = 0,
    MTStepFunctionPerVertex = 1,
    MTStepFunctionPerInstance = 2,
    MTStepFunctionPerPatch = 3,
    MTStepFunctionPerPatchControlPoint = 4,
    MTStepFunctionThreadPositionInGridX = 5,
    MTStepFunctionThreadPositionInGridY = 6,
    MTStepFunctionThreadPositionInGridXIndexed = 7,
    MTStepFunctionThreadPositionInGridYIndexed = 8,
}MTStepFunction;

// TODO: incomplete
