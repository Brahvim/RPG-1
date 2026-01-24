#include "Gl.h"
#include <stdio.h>
#include "Camera.h"
#include <glad/gles2.h>

#pragma region // 2D Cam.

float g_camera2dRot = 0;
GLuint g_cameraMat4Ubo = 0;
struct Camera g_camera2d = {

	.update = camera2dUpdate,
	.transform = &g_camera2dTransf,

};
struct SmlVec2 g_camera2dPos = { 0 };
struct SmlMat44 g_camera2dTransf = { // IDEN!

	// 3x3 inside for rotations...
	.r11 = 1,	.r12 = 0,	.r13 = 0,	.r14 = 0, // These three fields are

	.r21 = 0,	.r22 = 1,	.r23 = 0,	.r24 = 0, // used literally for

	.r31 = 0,	.r32 = 0,	.r33 = 1,	.r34 = 0, // translation only!

	.r41 = 0,	.r42 = 0,	.r43 = 0,	.r44 = 1, // Homogenous coord.

};

void camera2dUpdate(void) {
	// TODO: How about a 4x4 *transformations* API in SML? Not matrices, graphics transforms!

	smlMat44Identity(&g_camera2dTransf);
	g_camera2dTransf.r14 = -g_camera2dPos.x;
	g_camera2dTransf.r24 = -g_camera2dPos.y;
	smlMat33RotateZ(&g_camera2dTransf.mat33, -g_camera2dRot);
}

#pragma endregion

void cameraInitSystem(void) {
	ERRGL(glGenBuffers(1, &g_cameraMat4Ubo));
	ERRGL(glBindBuffer(GL_UNIFORM_BUFFER, g_cameraMat4Ubo));
	ERRGL(glBindBufferBase(GL_UNIFORM_BUFFER, 1, g_cameraMat4Ubo));
	// ERRGL(glBindBuffer(GL_UNIFORM_BUFFER, 0)); // Next master *always* commands servant...!
}

void cameraUploadUbo(struct Camera const *const p_camera) {
	ERRGL(glBindBuffer(GL_UNIFORM_BUFFER, g_cameraMat4Ubo));
	ERRGL(glBindBufferBase(GL_UNIFORM_BUFFER, 1, g_cameraMat4Ubo));
	ERRGL(glBufferData(GL_UNIFORM_BUFFER, sizeof(struct SmlMat44), &p_camera->transform, GL_STREAM_DRAW));
}
