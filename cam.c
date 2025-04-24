#include <stdio.h>

#include "cam.h"

struct GameCam *g_cam = &g_cam1;

struct GameCam g_cam1 = {

	.transform = { 0 },
	.update = gameCam1Update,

};

struct SmlVec3 g_cam1Up;
struct SmlVec3 g_cam1Target;
struct SmlVec3 g_cam1Position;
struct SmlMat44 g_cam1Transform;

void gameCam1Update(void) {

}
