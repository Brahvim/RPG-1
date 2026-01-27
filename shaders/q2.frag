#version 300 es
precision mediump float;

in vec2 v_uv;
out vec4 f_fragment;
uniform sampler2D u_atlas;

void main() {
    f_fragment = vec4(1.0, 0.0, 0.0, 1.0);
    // f_fragment = texture(u_atlas, v_uv);
}
