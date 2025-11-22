#version 300 es
in vec3 inPosition;
in vec2 inUV;

out vec2 fragUV;

uniform mat4 uModel;
uniform mat4 uProjection;

void main() {
    fragUV = inUV;
    vec4 position = uModel * vec4(inPosition, 1.0);
    gl_Position = uProjection * position;
}
