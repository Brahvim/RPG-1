#pragma once
#include "main.h"
#include "sml.h"

struct GameCam {

	struct SmlMat44 transform;
	void (*update)(void);

};

extern struct GameCam *g_cam;

void gameCam1Update(void);
extern struct GameCam g_cam1;
extern struct SmlVec3 g_cam1Up;
extern struct SmlVec3 g_cam1Target;
extern struct SmlVec3 g_cam1Position;
