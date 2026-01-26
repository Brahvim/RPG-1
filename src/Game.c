#include <stb/stb_rect_pack.h>
#include "Window1.h"
#include <string.h>
#include <stdlib.h>
#include "Assets.h"
#include "Camera.h"
#include <stdio.h>
#include "Game.h"
#include "Exit.h"
#include "Log.h"
#include "Itq.h"

struct ItqCtx *g_gameQuadCtx;
double g_gameMillisSetup;
double g_gameMillisDraw;
size_t g_gameFrameCount;

double gameMillis() {
	return glfwGetTime() - g_gameMillisSetup;
}

void gameSetup() {
	itqInitSystem();
	cameraInitSystem();
	g_gameQuadCtx = itqCtxCreate();

	struct Itq q = {

		.texRect = { 0 },
		.scale = {.x = 1, .y = 1 },
		.pos = {.x = 0.25f, .y = 0.25f, },

	};

	itqTexture(&q, ATLAS_DEFAULT, TEXTURE_NONE);
	listAppend(g_gameQuadCtx->list, 1, &q);
	itqDebug(&q);
}

void gameDraw() {
	g_camera2d.update();
	cameraUploadUbo(&g_camera2d);

	// ERRGL(glClearColor(1, 1, 1, 1));
	ERRGL(glClearColor(0.8f, 0.6f, 1.0f, 0.1f));
	ERRGL(glViewport(0, 0, g_window1Wfb, g_window1Hfb));
	ERRGL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

	itqCtxDraw(g_gameQuadCtx);
}
