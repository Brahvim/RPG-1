#version 300 es
precision mediump float;

out vec2 v_uv;

layout(location = 0) in vec2 a0_vPos;
layout(location = 1) in vec2 a1_vTexcoords;

layout(location = 2) in vec2 a2_iPos;
layout(location = 3) in vec2 a3_iScale;
layout(location = 4) in vec4 a4_iTexcoords; // `(x, y, w, h)` of texture rect.

void main() {
    // UV for curr vert: texrect start, plus texrect wh times vertex UVs.
    v_uv = a4_iTexcoords.xy + a1_vTexcoords.xy * a4_iTexcoords.zw;
    // gl_Position = vec4(a0_vPos, 0.0f, 1.0f); // Debug help!
    gl_Position = vec4(a0_vPos * a3_iScale + a2_iPos, 0.0f, 1.0f);
}
