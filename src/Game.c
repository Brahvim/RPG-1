#include <stb/stb_rect_pack.h>
#include "Window1.h"
#include "Assets.h"
#include <string.h>
#include "Camera.h"
#include <stdio.h>
#include "Quad.h"
#include "Game.h"

struct QuadCtx *g_gameQuadCtx;
double g_gameMillisSetup;
double g_gameMillisDraw;
size_t g_gameFrameCount;

double gameMillis(void) {
	return glfwGetTime() - g_gameMillisSetup;
}

void gameSetup(void) {
	quadInitSystem();
	cameraInitSystem();
	g_gameQuadCtx = quadCreate();
	listAppend(g_gameQuadCtx->quads, 1, &((struct Quad) {

		/**/.uv = { .x = 0.75, .y = 0.75, .z = 0.75, .w = 0.75 },
			.pos = { .x = 0.25, .y = 0.25, .z = 0, },
			.scale = { .x = 1, .y = 1 },
			.angle = 0,

	}));
}

void gameDraw(void) {
	ERRGL(glClearColor(1, 1, 1, 1));
	// ERRGL(glClearColor(0.8f, 0.6f, 1.0f, 0.1f));
	ERRGL(glViewport(0, 0, g_window1Wfb, g_window1Hfb));
	ERRGL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

	g_camera2d.update();
	cameraUploadUbo(&g_camera2d);
	quadDraw(g_gameQuadCtx);
}
