#version 300 es
precision highp float;

out vec4 v_uv;

layout(location = 0) in vec2 a0_pos;
layout(location = 1) in vec2 a1_scale;
layout(location = 2) in vec4 a2_texcoords;

void main() {
    v_uv = a2_texcoords;
}
