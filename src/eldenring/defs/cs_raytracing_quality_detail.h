#pragma once

typedef struct cs_raytracing_quality_detail_s {
    /* Enable Raytracing Ambient Occlusion */
    unsigned char enableRaytraceAO;

    /* Enable Raytracing Shadows */
    unsigned char enableRaytraceShadows;

    unsigned char Unk0x02;

    unsigned char Unk0x03;

    float UnkFloat0x04;

    int Unk0x08;

    float UnkFloat0x0C;

    int Unk0x10;

    /* Penumbra Size
     *   Sun source radius */
    float penumbraSize;

    /* Render Distance */
    float renderDistance;
} cs_raytracing_quality_detail_t;
