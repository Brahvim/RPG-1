#version 300 es
precision highp float;

out vec2 v_uv;
uniform sampler2D u_atlas;
uniform int u_offsetsCount;
uniform sampler2D u_offsets;
layout(std140) uniform Camera {
    mat4 u_cam;
};
layout(location = 0) in vec4 a0_uv;
layout(location = 1) in vec3 a1_pos;
layout(location = 2) in vec2 a2_scale;
layout(location = 3) in float a3_angle;

void main() {
    // float s = sin(a3_angle);
    // float c = cos(a3_angle);
    // mat2 rotation = mat2(c, -s, s, c);

    // vec2 scaled = a3_corner * a2_scale;
    // vec2 rotated = rotation * scaled;
    // vec2 translated = rotated + a1_pos.xy;

    int cornerId = gl_VertexID % u_offsetsCount;
    vec3 corner = texelFetch(u_offsets, ivec2(cornerId, 0), 0).xyz;

    v_uv = mix(a0_uv.xy, a0_uv.zw, corner.xy + 0.5);
    // v_uv = mix(a0_uv.xy, a0_uv.zw, a3_corner + 0.5);
    // vec4 model = vec4(translated, a1_pos.z, 1);

    gl_Position = vec4(corner, 0);

    // Debug-"Cheating":
    // switch (gl_VertexID % 4) {
    //
    //     case 0: gl_Position = vec4(-0.5, -0.5, 0, 0);
    //     case 1: gl_Position = vec4(+0.5, -0.5, 0, 0);
    //     case 2: gl_Position = vec4(-0.5, +0.5, 0, 0);
    //     case 3: gl_Position = vec4(+0.5, +0.5, 0, 0);
    //
    // }

    // gl_Position = vec4(a3_corner, 0, 0);
    // gl_Position = u_cam * model;
}
