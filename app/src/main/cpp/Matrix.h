#pragma once

#include "Vector.h"

struct float4x4 {
    float4 c0, c1, c2, c3;

    float4x4() {
        c0 = {1.f, 0.f, 0.f, 0.f};
        c1 = {0.f, 1.f, 0.f, 0.f};
        c2 = {0.f, 0.f, 1.f, 0.f};
        c3 = {0.f, 0.f, 0.f, 1.f};
    }

    float4x4(float m00, float m01, float m02, float m03,
             float m10, float m11, float m12, float m13,
             float m20, float m21, float m22, float m23,
             float m30, float m31, float m32, float m33) {
        c0 = {m00, m10, m20, m30};
        c1 = {m01, m11, m21, m31};
        c2 = {m02, m12, m22, m32};
        c3 = {m03, m13, m23, m33};
    }

    /**
     * Returns a float4x4 centered orthographic projection matrix.
     * @param width The width of the view volume
     * @param height The height of the view volume
     * @param near The distance to the near plane
     * @param far The distance to the far plane
     */
    static float4x4 Orthographic(float width, float height, float near, float far) {
        float depth = far - near;
        return float4x4(
                2.0f / width, 0.0f, 0.0f, 0.0f,
                0.0f, 2.0f / height, 0.0f, 0.0f,
                0.0f, 0.0f, -2.0f / depth, -(far + near) * depth,
                0.0f, 0.0f, 0.0f, 1.0f
        );
    }
};
