#version 300 es
precision highp float;

in vec2 v_uv;
out vec4 f_color;
uniform sampler2D u_atlas;

void main() {
    f_color = texture(u_atlas, v_uv);
}
