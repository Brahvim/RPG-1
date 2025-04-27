#pragma once
#include "main.h"
#include "sml.h"

#define GAME_CAM_DEFAULT g_cam2d

// Uhhh, not at ALL batch-friendly, but *hey*, how many cameras will you use at once in a single-screen game?:
struct GameCam {

	void (*update)(void);
	struct SmlMat44 *transform;

};

extern struct GameCam *g_cam;

// 2D Camera (angle, pos):
void gameCam2dUpdate(void);
extern float g_cam2dRotation;
extern struct GameCam g_cam2d;
extern struct SmlVec2 g_cam2dPosition;
extern struct SmlMat44 g_cam2dTransform;
