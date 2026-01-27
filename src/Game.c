#include <stb/stb_rect_pack.h>
#include "Window1.h"
#include <string.h>
#include <stdlib.h>
#include "Assets.h"
#include "Camera.h"
#include <stdio.h>
#include "Quad2.h"
#include <math.h>
#include "Game.h"
#include "Exit.h"
#include "Log.h"

struct Quad2Ctx *g_gameQuad2Ctx;
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
	quad2CtxDelete(g_gameQuad2Ctx);
}

void gameSetup() {
	quad2InitSystem();
	cameraInitSystem();
	g_gameQuad2Ctx = quad2CtxCreate();

	struct Quad2 q = {

		.pos = { 0 },
		.texRect = { 0 },
		.scale = {.x = 1, .y = 1 },

	};

	quad2Texture(&q, ATLAS_DEFAULT, TEXTURE_TEST1);
	listAppend(g_gameQuad2Ctx->list, 1, &q);
}

void gameDraw() {
	g_camera2d.update();
	cameraUploadUbo(&g_camera2d);
	quad2ListRead(g_gameQuad2Ctx->list, 0)->pos.x = fabs(sin(g_gameMillisDraw)) - 0.5f;

	ERRGL(glClearColor(0.8f, 0.6f, 1.0f, 0.1f));
	ERRGL(glViewport(0, 0, g_window1Wfb, g_window1Hfb));
	ERRGL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

	quad2CtxDraw(g_gameQuad2Ctx);
}
