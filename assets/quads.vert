#version 330 core

layout (location = 0) in vec3 in_scaleAndAngle;
layout (location = 1) in vec3 in_pos;
layout (location = 2) in vec2 in_uv;

uniform mat4 u_cam;
uniform vec2 u_vertexOffs[4];

out vec2 v_uv;

void main() {
	float sinA = sin(in_scaleAndAngle.z);
	float cosA = cos(in_scaleAndAngle.z);
	mat2 rot = mat2(cosA, -sinA, sinA, cosA);

	vec2 local = rot * (u_vertexOffs[gl_VertexID % 4] * in_scaleAndAngle.xy);
	vec3 world = in_pos + vec3(local, 0.0);

	v_uv = in_uv;
	gl_Position = u_cam * vec4(world, 1.0);
}
