#version 330 core

in vec2 vo_uv;

out vec4 o_fragColor;

uniform vec2 u_texRes;
uniform sampler2D u_tex;

void main() {
	vec3 tex = texture(u_tex, vo_uv).rgb;
	o_fragColor = vec4(tex, 1.0);
}
