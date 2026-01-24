#pragma once
#include "Sml.h"

/*
* Uhhh, not at ALL batch-friendly,
* ...but *hey*, how many cameras will you use at once in a single-screen game?
*/
struct Camera {

	void (*update)(void);
	struct SmlMat44 *transform;

};

#pragma region // 2D Cam.
void camera2dUpdate(void);
extern float g_camera2dRot;
extern struct Camera g_camera2d;
extern struct SmlVec2 g_camera2dPos;
extern struct SmlMat44 g_camera2dTransf;
#pragma endregion 

void cameraInitSystem(void);
void cameraUploadUbo(struct Camera const *const camera);
