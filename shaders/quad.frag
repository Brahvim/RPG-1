#version 300 es
precision mediump float;

in vec2 v_uv;
in vec4 v_tint;
out vec4 f_fragment;
uniform sampler2D u_atlas;

void main() {
	vec4 texel = texture(u_atlas, v_uv);
	f_fragment.xyz = texel.xyz + v_tint.xyz;
	f_fragment.a = texel.a * v_tint.a;
}
