#include <stb/stb_rect_pack.h>
#include "Window1.h"
#include <string.h>
#include <stdlib.h>
#include "Assets.h"
#include "Camera.h"
#include <stdio.h>
#include "Quad2.h"
#include "Game.h"
#include "Exit.h"
#include "Log.h"

struct Quad2Ctx *g_gameQuad2Ctx;
double g_gameMillisSetup;
double g_gameMillisDraw;
size_t g_gameFrameCount;

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
	listDebug(g_gameQuad2Ctx->list);

	struct Quad2 q = {

		.texRect = { 0 },
		.scale = {.x = 1, .y = 1 },
		.pos = {.x = 0.25f, .y = 0.25f, },

	};

	quad2Texture(&q, ATLAS_DEFAULT, TEXTURE_NONE);
	listAppend(g_gameQuad2Ctx->list, 1, &q);
	listDebug(g_gameQuad2Ctx->list);
	quad2Debug(&q);
}

void gameDraw() {
	g_camera2d.update();
	cameraUploadUbo(&g_camera2d);

	// ERRGL(glClearColor(1, 1, 1, 1));
	ERRGL(glClearColor(0.8f, 0.6f, 1.0f, 0.1f));
	ERRGL(glViewport(0, 0, g_window1Wfb, g_window1Hfb));
	ERRGL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

	quad2CtxDraw(g_gameQuad2Ctx);
}
