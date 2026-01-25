#include <stb/stb_rect_pack.h>
#include "Window1.h"
#include <string.h>
#include <stdlib.h>
#include "Assets.h"
#include "Camera.h"
#include <stdio.h>
#include "Quad.h"
#include "Game.h"
#include "Exit.h"
#include "Log.h"

size_t g_gameFrameCount;
double g_gameMillisDraw;
double g_gameMillisSetup;
struct QuadCtx *g_gameQuadCtx;

double gameMillis(void) {
	return glfwGetTime() - g_gameMillisSetup;
}

void gameSetup(void) {
	quadInitSystem();
	cameraInitSystem();
	g_gameQuadCtx = quadCreate();
	listAppend(g_gameQuadCtx->quads, 1, &((struct Quad) {

		/**/.uv = { .x = 0.75f, .y = 0.75f, .z = 0.75f, .w = 0.75f },
			// .pos = { .x = 0.25f, .y = 0.25f, .z = 0, },
			.pos = { .x = 0.0f, .y = 0.0f, .z = 0.0f, },
			.scale = { .x = 1, .y = 1 },
			.angle = 0,

	}));
}

void gameDraw(void) {
	g_camera2d.update();

	// ERRGL(glClearColor(1, 1, 1, 1));
	ERRGL(glClearColor(0.8f, 0.6f, 1.0f, 0.1f));
	ERRGL(glViewport(0, 0, g_window1Wfb, g_window1Hfb));
	ERRGL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

	cameraUploadUbo(&g_camera2d);
	quadDraw(g_gameQuadCtx);
}
