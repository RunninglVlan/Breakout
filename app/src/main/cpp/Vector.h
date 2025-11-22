#pragma once

union float2 {
    struct {
        float x, y;
    };
    struct {
        float u, v;
    };
};

struct float3 {
    float x, y, z;
};

struct float4 {
    float x, y, z, w;
};
