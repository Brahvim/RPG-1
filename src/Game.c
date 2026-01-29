#include <stb/stb_rect_pack.h>
#include "Window1.h"
#include <string.h>
#include <stdlib.h>
#include "Assets.h"
#include "Camera.h"
#include <stdio.h>
#include <math.h>
#include "Quad.h"
#include "Game.h"
#include "Exit.h"
#include "Log.h"

struct QuadCtx *g_gameQuadCtx;
double g_gameMillisSetup;
double g_gameMillisDraw;
size_t g_gameFrameCount;

void gameExit(enum ExitReason const p_reason) {
	switch (p_reason) {

		default: return;

		case EXIT_REASON_SUCCESS: {

			puti("Exiting just fine this time :)!");

		} break;

		case EXIT_REASON_FAILURE: {

			pute("Exiting for no good reason! Check meee!");

		} break;

		case EXIT_REASON_REALLOC: {

			pute("Exiting because some `realloc()` call failed.");

		} break;

		case EXIT_REASON_MALLOC: {

			pute("Exiting because `malloc()` call failed. Again.");

		} break;

		case EXIT_REASON_CALLOC: {

			pute("Exiting because `calloc()` call failed. Again.");

		} break;

	}

	gameShutdown();
	window1Delete();
	glfwTerminate();
	exit(p_reason);
}

double gameMillis() {
	return glfwGetTime() - g_gameMillisSetup;
}

void gameShutdown() {
	quadCtxDelete(g_gameQuadCtx);
}

void gameSetup() {
	quadInitSystem();
	cameraInitSystem();
	g_gameQuadCtx = quadCtxCreate();

	struct Quad q = {

		.pos = { 0 },
		.texRect = { 0 },
		.scale = { 1, 1 },
		// TODO: Quad rotation?
		// .tintRgba = { 0, 0, 1, 0 },

	};

	// TODO: `quadAdd()` for all of this!
	quadTexture(&q, ATLAS_DEFAULT, TEXTURE_GRID);
	listAppend(g_gameQuadCtx->list, 1, &q);

	q.tintRgba = ((struct SmlQuat) { 0, 0, 1, 0 });
	quadTexture(&q, ATLAS_DEFAULT, TEXTURE_BLACK);
	q.scale = ((struct SmlVec3) { 0.1f, 0.1f, 0.0f });
	q.pos = ((struct SmlVec3) { -0.5f, -0.5f, 0.0f });
	listAppend(g_gameQuadCtx->list, 1, &q);
}

void gameDraw() {
	g_camera2d.update();
	cameraUploadUbo(&g_camera2d); // TODO: Projection matrix too! Multiply on CPU-side only!
	quadListRead(g_gameQuadCtx->list, 0)->pos.x = fabs(sin(g_gameMillisDraw)) - 0.5f;

	// ERRGL(glClearColor(0, 0, 0, 0));
	ERRGL(glClearColor(0.8f, 0.6f, 1.0f, 1.0f));
	ERRGL(glViewport(0, 0, g_window1Wfb, g_window1Hfb));
	ERRGL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

	quadCtxDraw(g_gameQuadCtx); // TODO: Limit how many are drawn!
	// TODO: Perhaps also `quadCtxDrawRest()` to draw all remaining!
}
