#pragma once

#include <string>
#include <GLES3/gl3.h>

#include "Matrix.h"

class Model;

/*!
 * A class representing a simple shader program. It consists of vertex and fragment components. The
 * input attributes are a position (as a float3) and a uv (as a float2). It also takes a uniform
 * to be used as the entire model/view/projection matrix. The shader expects a single texture for
 * fragment shading, and does no other lighting calculations (thus no uniforms for lights or normal
 * attributes).
 */
class Shader {
public:
    /*!
     * Loads a shader given the full sourcecode and names for necessary attributes and uniforms to
     * link to. Returns a valid shader on success or null on failure. Shader resources are
     * automatically cleaned up on destruction.
     *
     * @param vertexSource The full source code for your vertex program
     * @param fragmentSource The full source code of your fragment program
     * @param positionAttributeName The name of the position attribute in your vertex program
     * @param uvAttributeName The name of the uv coordinate attribute in your vertex program
     * @param modelMatrixUniformName The name of model matrix uniform
     * @param projectionMatrixUniformName The name of projection matrix uniform
     * @return a valid Shader on success, otherwise null.
     */
    static Shader *loadShader(
            const std::string &vertexSource,
            const std::string &fragmentSource,
            const std::string &positionAttributeName,
            const std::string &uvAttributeName,
            const std::string &modelMatrixUniformName,
            const std::string &projectionMatrixUniformName,
            const std::string &colorUniformName,
            const std::string &hasTextureUniformName);

    inline ~Shader() {
        if (program_) {
            glDeleteProgram(program_);
            program_ = 0;
        }
    }

    /*!
     * Prepares the shader for use, call this before executing any draw commands
     */
    void activate() const;

    /*!
     * Cleans up the shader after use, call this after executing any draw commands
     */
    void deactivate() const;

    /*!
     * Renders a single model
     * @param model a model to render
     */
    void drawModel(const Model &model) const;

    /*!
     * Renders a single model as an outline
     * @param model a model to render
     */
    void drawBorder(const Model &model) const;

    /*!
     * Sets the projection matrix in the shader.
     * @param projectionMatrix a float4x4 to be used as the projection matrix
     */
    void setProjectionMatrix(const float4x4 &projectionMatrix) const;

    /*!
     * Sets the color to render with.
     * @param color an array of 4 floats, representing RGBA values.
     */
    void setColor(float *color) const;

private:
    /*!
     * Helper function to load a shader of a given type
     * @param shaderType The OpenGL shader type. Should either be GL_VERTEX_SHADER or GL_FRAGMENT_SHADER
     * @param shaderSource The full source of the shader
     * @return the id of the shader, as returned by glCreateShader, or 0 in the case of an error
     */
    static GLuint loadShader(GLenum shaderType, const std::string &shaderSource);

    /*!
     * Constructs a new instance of a shader. Use @a loadShader
     * @param program the GL program id of the shader
     * @param position the attribute location of the position
     * @param uv the attribute location of the uv coordinates
     * @param modelMatrix the uniform location of the model matrix
     * @param projectionMatrix the uniform location of the projection matrix
     * @param color the uniform location of the color
     * @param hasTexture the uniform location of the hasTexture flag
     */
    constexpr Shader(
            GLuint program,
            GLint position,
            GLint uv,
            GLint modelMatrix,
            GLint projectionMatrix,
            GLint color,
            GLint hasTexture)
            : program_(program),
              position_(position),
              uv_(uv),
              modelMatrix_(modelMatrix),
              projectionMatrix_(projectionMatrix),
              color_(color),
              hasTexture_(hasTexture) {}

    GLuint program_;
    GLint position_;
    GLint uv_;
    GLint modelMatrix_;
    GLint projectionMatrix_;
    GLint color_;
    GLint hasTexture_;
};
