#version 330 core

layout (location = 0) in vec2 in_pos;
layout (location = 1) in vec2 in_uv;

uniform mat4 u_transform;

out vec2 vo_uv;

void main() {
	vo_uv = in_uv;
	gl_Position = u_transform * vec4(in_pos, 0.0, 1.0);
}
