#version 300 es
precision highp float;

out vec2 v_uv;
uniform sampler2D u_atlas;
layout(std140) uniform Camera {
    mat4 u_cam;
};
layout(location = 0) in vec4 l0_uv;
layout(location = 1) in vec3 l1_pos;
layout(location = 2) in vec2 l2_scale;
layout(location = 3) in vec2 l3_corner;
layout(location = 4) in float l4_angle;

void main() {
    float s = sin(l4_angle);
    float c = cos(l4_angle);
    mat2 rotation = mat2(c, -s, s, c);

    vec2 scaled = l3_corner * l2_scale;
    vec2 rotated = rotation * scaled;
    vec2 translated = rotated + l1_pos.xy;

    v_uv = mix(l0_uv.xy, l0_uv.zw, l3_corner.xy + 0.5);
    // vec4 model = vec4(translated, l1_pos.z, 1);
    gl_Position = vec4(l3_corner, 0, 0);
    // gl_Position = u_cam * model;
}
