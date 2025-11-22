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

    float4x4(float4 c0, float4 c1, float4 c2, float4 c3) : c0(c0),
                                                           c1(c1),
                                                           c2(c2),
                                                           c3(c3) {}

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
     * Returns a float4x4 translation matrix given a float3 translation vector.
     * @param vector The translation vector
     */
    static float4x4 Translation(float3 vector) {
        float4x4 translation;
        translation.c3.x = vector.x;
        translation.c3.y = vector.y;
        translation.c3.z = vector.z;
        return translation;
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

    /**
     * Returns the float4x4 matrix result of a matrix multiplication between a float4x4 matrix and a float4x4 matrix.
     * @return The computed matrix multiplication.
     */
    static float4x4 mul(float4x4 a, float4x4 b) {
        return float4x4(
                a.c0 * b.c0.x + a.c1 * b.c0.y + a.c2 * b.c0.z + a.c3 * b.c0.w,
                a.c0 * b.c1.x + a.c1 * b.c1.y + a.c2 * b.c1.z + a.c3 * b.c1.w,
                a.c0 * b.c2.x + a.c1 * b.c2.y + a.c2 * b.c2.z + a.c3 * b.c2.w,
                a.c0 * b.c3.x + a.c1 * b.c3.y + a.c2 * b.c3.z + a.c3 * b.c3.w);
    }
};
