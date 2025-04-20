#version 330 core

in vec2 v_uv;

out vec4 f_fragColor;

uniform sampler2D u_atlas;

void main() {
	vec3 tex = texture(u_atlas, v_uv).rgb;
	f_fragColor = vec4(tex, 1.0);
}
