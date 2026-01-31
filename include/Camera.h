#pragma once
#include "Sml.h"

extern struct SmlMat44 g_cameraCurrentTransf;

#pragma region // "Make".
struct SmlMat44* cameraMakeLookAt(
	struct SmlVec3 const *const target,
	struct SmlVec3 const *const pos,
	struct SmlVec3 const *const up,
	struct SmlMat44 *const out
);

struct SmlMat44* cameraMakeOrtho(
	float const far,
	float const near,
	float const top,
	float const bottom,
	float const left,
	float const right,
	struct SmlMat44 *const out
);

struct SmlMat44* cameraMakePersp(
	float const fov,
	float const far,
	float const near,
	float const aspect,
	struct SmlMat44 *const out
);

struct SmlMat44* cameraMake2d(
	struct SmlVec3 const *const position,
	struct SmlMat44 *const out,
	float const rotation
);
#pragma endregion

#pragma region // 2D Cam.

void camera2dApply();
void camera2dUpdateOrtho();
void camera2dUpdatePersp();
extern float g_camera2dRot;
extern struct SmlVec3 g_camera2dPos;
extern struct SmlMat44 g_camera2dTransf;

#pragma endregion 
