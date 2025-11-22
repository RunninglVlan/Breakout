#pragma once

#include <vector>

#include "TextureAsset.h"
#include "Vector.h"
#include "Matrix.h"

struct Vertex {
    constexpr Vertex(const float3 &inPosition, const float2 &inUV) : position(inPosition),
                                                                     uv(inUV) {}

    float3 position;
    float2 uv;
};

typedef uint16_t Index;

class Model {
public:
    inline Model(
            std::vector<Vertex> vertices,
            std::vector<Index> indices,
            std::shared_ptr<TextureAsset> spTexture)
            : vertices_(std::move(vertices)),
              indices_(std::move(indices)),
              spTexture_(std::move(spTexture)),
              modelMatrix_() {}

    void setPosition(const float3 &position) {
        modelMatrix_ = float4x4::Translation(position);
    }

    void translate(const float3 &offset) {
        float4x4 translation = float4x4::Translation(offset);
        modelMatrix_ = float4x4::mul(translation, modelMatrix_);
    }

    inline const float4x4 &getModelMatrix() const {
        return modelMatrix_;
    }

    inline const Vertex *getVertexData() const {
        return vertices_.data();
    }

    inline const size_t getIndexCount() const {
        return indices_.size();
    }

    inline const Index *getIndexData() const {
        return indices_.data();
    }

    inline const TextureAsset &getTexture() const {
        return *spTexture_;
    }

private:
    std::vector<Vertex> vertices_;
    std::vector<Index> indices_;
    std::shared_ptr<TextureAsset> spTexture_;
    float4x4 modelMatrix_;
};
