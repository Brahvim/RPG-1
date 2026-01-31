#include <math.h>
#include <stdio.h>
#include "Camera.h"
#include "Window1.h"
#include <glad/gles2.h>

struct SmlMat44 g_cameraCurrentTransf = { 0 };

struct SmlMat44* cameraMakeLookAt(
	struct SmlVec3 const *const p_target,
	struct SmlVec3 const *const p_pos,
	struct SmlVec3 const *const p_up,
	struct SmlMat44 *const p_out
) {
	struct SmlVec3 forward;
	smlVec3Sub(p_pos, p_target, &forward);
	smlVec3Normalize(&forward, &forward);

	struct SmlVec3 right;
	smlVec3Cross(p_up, &forward, &right);
	smlVec3Normalize(&right, &right);

	struct SmlVec3 up;
	smlVec3Cross(&forward, &right, &up);

	// ```
	// | r.x   r.y   r.z   -dot(r, eye) |
	// | u.x   u.y   u.z   -dot(u, eye) |
	// | f.x   f.y   f.z   -dot(f, eye) |
	// |  0     0     0          1      |
	// ```

	smlMat44Identity(p_out);

	p_out->r34 = -smlVec3Dot(&forward, p_pos);
	p_out->r14 = -smlVec3Dot(&right, p_pos);
	p_out->r24 = -smlVec3Dot(&up, p_pos);

	p_out->r31 = forward.x;
	p_out->r32 = forward.y;
	p_out->r33 = forward.z;

	p_out->r11 = right.x;
	p_out->r12 = right.y;
	p_out->r13 = right.z;

	p_out->r21 = up.x;
	p_out->r22 = up.y;
	p_out->r23 = up.z;

	return p_out;
}

struct SmlMat44* cameraMakeOrtho(
	float const p_far,
	float const p_near,
	float const p_top,
	float const p_bottom,
	float const p_left,
	float const p_right,
	struct SmlMat44 *const p_out
) {
	smlMat44Identity(p_out);

	// ```
	// | 2 / (r - l)        0              0        -1 * ((r + l) / (r - l)) |
	// |   0           2 / (t - b)         0        -1 * ((t + b) / (t - b)) |
	// |   0                0        -2 / (f - n)   -1 * ((f + n) / (f - n)) |
	// |   0                0              0                      1          |
	// ```

	float const diffRightLeft = p_right - p_left;
	float const diffTopBottom = p_top - p_bottom;
	float const diffFarNear = p_far - p_near;

	p_out->r14 = -(p_right + p_left) / diffRightLeft;
	p_out->r24 = -(p_top + p_bottom) / diffTopBottom;
	p_out->r34 = -(p_far + p_near) / diffFarNear;

	p_out->r11 = +2.0f / diffRightLeft;
	p_out->r22 = +2.0f / diffTopBottom;
	p_out->r33 = -2.0f / diffFarNear;

	return p_out;
}

struct SmlMat44* cameraMakePersp(
	float const p_fov,
	float const p_far,
	float const p_near,
	float const p_aspect,
	struct SmlMat44 *const p_out
) {
	smlMat44Identity(p_out);

	// ```
	// | f / aspect   0                0                                 0              |
	// |    0         f                0                                 0              |
	// |    0         0   (far + near) / (near - far)   (2 * far * near) / (near - far) |
	// |    0         0               -1                                 0              |
	// ```
	// ...where `f = 1 / tan(fov / 2)`!
	float const f = 1.0f / tanf(p_fov * 0.5f);

	p_out->r44 = 0; // In an iden. mat., this is `1`!
	p_out->r22 = f;
	p_out->r43 = -1; // Causes perspective divide, apparently. `+` for left-handed.
	p_out->r11 = f / p_aspect;
	p_out->r33 = (p_far + p_near) / (p_near - p_far);		// OpenGL ONLY!
	p_out->r34 = (2 * p_far * p_near) / (p_near - p_far);	// OpenGL ONLY!

	return p_out;
}

struct SmlMat44* cameraMake2d(
	struct SmlVec3 const *const p_pos,
	struct SmlMat44 *const p_out,
	float const p_rotation
) {
	smlMat44Identity(p_out);

	// Inverse rotation (`z` axis!):
	float const c = cosf(-p_rotation);
	float const s = sinf(-p_rotation);

	p_out->r11 = +c;
	p_out->r12 = -s;
	p_out->r21 = +s;
	p_out->r22 = +c;

	// Inverse translation:
	p_out->r14 = -p_pos->x;
	p_out->r24 = -p_pos->y;
	p_out->r34 = -p_pos->z;

	return p_out;
}

#pragma region // 2D Cam.
struct SmlMat44 g_camera2dTransf = { 0 };
struct SmlVec3 g_camera2dPos = { 0 };
float g_camera2dRot = 0;

void camera2dUpdateOrtho() {
	// TODO: Like the current cam, make a "current window"!
	float const cx = g_window1Wfb * 0.5f;
	float const cy = g_window1Hfb * 0.5f;
	float const w = g_window1Wfb;
	float const h = g_window1Hfb;

	smlMat44Mult(

		cameraMakeOrtho(
			+1, -1,
			+cy, -cy,
			-cx, +cx,
			smlMat44Ptr()
		),

		cameraMake2d(
			&g_camera2dPos,
			smlMat44Ptr(),
			g_camera2dRot
		),

		&g_camera2dTransf

	);
}

void camera2dUpdatePersp() {
	struct SmlVec3 pos = g_camera2dPos;
	float const w = g_window1Wfb;
	float const h = g_window1Hfb;
	pos.z = 100;

	smlMat44Mult(

		cameraMakePersp(
			SML_RADIANS(90),
			100.0f, 0.1f,
			w / h,
			&g_cameraCurrentTransf
		),

		cameraMake2d(
			&pos,
			smlMat44Ptr(),
			g_camera2dRot
		),

		&g_camera2dTransf

	);


}

void camera2dApply() {
	g_cameraCurrentTransf = g_camera2dTransf;
}
#pragma endregion
