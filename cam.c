#include <stdio.h>

#include <glad.h>

#include "game/cam.h"

struct GameCam *g_cam = &GAME_CAM_DEFAULT;

struct GameCam g_cam2d = {

	.update = gameCam2dUpdate,
	.transform = &g_cam2dTransform,

};

float g_cam2dRotation = 0;
struct SmlVec2 g_cam2dPosition = { 0 };
struct SmlMat44 g_cam2dTransform = { 0 };

void gameCam2dUpdate(void) {
	smlMat44Identity(&g_cam2dTransform);
	g_cam2dTransform.r14 = -g_cam2dPosition.x;
	g_cam2dTransform.r24 = -g_cam2dPosition.y;
	smlMat33RotateZ(&g_cam2dTransform.mat33, -g_cam2dRotation);
}
