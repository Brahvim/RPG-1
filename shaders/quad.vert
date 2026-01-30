#version 300 es
precision mediump float;

// `inout`
out vec2 v_uv;
out vec4 v_tint;

uniform mat4 u_camera;

// Vertex attributes.
layout(location = 0) in vec3 a0_vPos;
layout(location = 1) in vec2 a1_vTexcoords;

// Instance attributes.
layout(location = 2) in vec3 a2_iPos;
layout(location = 3) in vec4 a3_iTint;
layout(location = 4) in vec3 a4_iScale;
layout(location = 5) in vec3 a5_iRotation;
layout(location = 6) in vec4 a6_iTexcoords; // `(x, y, w, h)` of texture rect.

mat3 mat3RotateX(float p_angle) {
	float c = cos(p_angle);
	float s = sin(p_angle);
	return mat3(1, 0, 0, 0, c, -s, 0, s, c);
}

mat3 mat3RotateY(float p_angle) {
	float c = cos(p_angle);
	float s = sin(p_angle);
	return mat3(c, 0, s, 0, 1, 0, -s, 0, c);
}

mat3 mat3RotateZ(float p_angle) {
	float c = cos(p_angle);
	float s = sin(p_angle);
	return mat3(c, -s, 0, s, c, 0, 0, 0, 1);
}

void main() {
	v_tint = a3_iTint;

	mat3 mat3Rotate 
		/**/ = mat3RotateX(a5_iRotation.x) 
		/**/ * mat3RotateY(a5_iRotation.y)
		/**/ * mat3RotateZ(a5_iRotation.z);

	// `a0_vPos` is the *local* coord.
	//
	// vec3 scaled = a0_vPos * a4_iScale;
	// vec3 rotated = mat3Rotate * scaled;
	// vec3 translated = rotated + a2_iPos;
	// gl_Position = vec4(translated, 1.0);
	//
	// `translated` is the *world* coordinate.

	// `v_uv = aabb_start_2d + aabb_dimensions_2d * vert_uv_2d`;
	// i.e. `a6_iTexcoords.xy + a1_vTexcoords.xy * a6_iTexcoords.zw`:
	v_uv = mix(a6_iTexcoords.xy, a6_iTexcoords.zw, a1_vTexcoords.xy);
	gl_Position = u_camera * vec4(mat3Rotate * (a0_vPos * a4_iScale) + a2_iPos, 1.0f);
}
