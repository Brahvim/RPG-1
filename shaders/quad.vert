#version 300 es
precision mediump float;

out vec2 v_uv;
out vec4 v_tint;

layout(location = 0) in vec2 a0_vPos;
layout(location = 1) in vec2 a1_vTexcoords;

layout(location = 2) in vec2 a2_iPos;
layout(location = 3) in vec4 a3_iTint;
layout(location = 4) in vec2 a4_iScale;
layout(location = 5) in vec4 a5_iTexcoords; // `(x, y, w, h)` of texture rect.

void main() {
    // UV for curr vert: texrect start, plus texrect wh times vertex UVs.
    v_uv = mix(a5_iTexcoords.xy, a5_iTexcoords.zw, a1_vTexcoords.xy);
    // v_uv = a5_iTexcoords.xy + a1_vTexcoords.xy * a5_iTexcoords.zw;
    gl_Position = vec4(a0_vPos * a4_iScale + a2_iPos, 0.0, 1.0);
    v_tint = a3_iTint;
}
