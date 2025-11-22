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

inline float4 operator*(const float4 &a, const float &b) {
    return float4(a.x * b, a.y * b, a.z * b, a.w * b);
}

inline float4 operator+(const float4 &a, const float4 &b) {
    return float4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}
