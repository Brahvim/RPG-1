#include "Gl.h"
#include <stdio.h>
#include "Camera.h"
#include <glad/gles2.h>

GLuint g_cameraMat4Ubo = 0;
float g_cameraRotation2d = 0;
struct Camera g_camera2d = {

	.update = cameraUpdate2d,
	.transform = &g_cameraTransform2d,

};
struct SmlVec2 g_cameraPosition2d = { 0 };
struct SmlMat44 g_cameraTransform2d = { 0 };

void cameraInitSystem(void) {
	ERRGL(glGenBuffers(1, &g_cameraMat4Ubo));
	ERRGL(glBindBuffer(GL_UNIFORM_BUFFER, g_cameraMat4Ubo));
	ERRGL(glBindBufferBase(GL_UNIFORM_BUFFER, 1, g_cameraMat4Ubo));
	// ERRGL(glBindBuffer(GL_UNIFORM_BUFFER, 0)); // Do we *really* need to be cleaning up?
}

void cameraUpdate2d(void) {
	smlMat44Identity(&g_cameraTransform2d);
	g_cameraTransform2d.r14 = -g_cameraPosition2d.x;
	g_cameraTransform2d.r24 = -g_cameraPosition2d.y;
	smlMat33RotateZ(&g_cameraTransform2d.mat33, -g_cameraRotation2d);
}

void cameraUploadUbo(struct Camera const *const p_camera) {
	ERRGL(glBindBuffer(GL_UNIFORM_BUFFER, g_cameraMat4Ubo));
	ERRGL(glBindBufferBase(GL_UNIFORM_BUFFER, 1, g_cameraMat4Ubo));
	ERRGL(glBufferData(GL_UNIFORM_BUFFER, sizeof(struct SmlMat44), &p_camera->transform, GL_STREAM_DRAW));
}
