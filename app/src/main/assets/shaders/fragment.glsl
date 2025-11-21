#version 300 es
precision mediump float;

in vec2 fragUV;

uniform sampler2D uTexture;
uniform vec4 uColor;
uniform bool uHasTexture;

out vec4 outColor;

void main() {
    if (uHasTexture) {
        outColor = texture(uTexture, fragUV);
    } else {
        outColor = uColor;
    }
}
