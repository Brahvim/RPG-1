#version 300 es
precision mediump float;

uniform sampler2D u_atlas;
out vec4 f_fragment;
in vec4 v_tint;
in vec2 v_uv;

void main() {
	vec4 texel = texture(u_atlas, v_uv);
	f_fragment.xyz = texel.xyz + v_tint.xyz;
	f_fragment.a = texel.a * v_tint.a;
}
