#include <stb/stb_rect_pack.h>
#include <stb/stb_image.h>
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
	for (size_t i = 0; i < TEXTURE_TOTAL; ++i) {

		free(g_textureData[i]);

	}

	for (size_t i = 0; i < SHADER_TOTAL; ++i) {

		free(g_shaderSourcesFrag[i]);
		free(g_shaderSourcesVert[i]);

	}

	for (size_t i = 0; i < ATLAS_TOTAL; ++i) {

		free(g_atlases[i].rects);
		free(g_atlases[i].textures);

	}

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
	quadSystemInit();
	struct QuadCtx *qc = g_gameQuadCtx = quadCtxCreate();

	listExpand(qc->list, 2);
	quadCtxAppend(qc, quadDef());
	quadTexture(quadListTail(qc->list), ATLAS_DEFAULT, TEXTURE_GRID);

	quadCtxAppend(
		qc,
		quadVal(
			.scale = smlVec3Val(0.1f, 0.1f),
			.tintRgba = smlQuatVal(1, 0, 0, 0),
			.pos = smlVec3Val(-0.5f, -0.5f, 0.0f)
		)
	);
	// quadTexture(quadListTail(qc->list), ATLAS_DEFAULT, TEXTURE_MISSING);
}

void gameDraw() {
	camera2dUpdate();
	quadListRead(g_gameQuadCtx->list, 1)->rotate.z = g_gameMillisDraw;
	// quadListRead(g_gameQuadCtx->list, 0)->pos.z = fabs(sin(g_gameMillisDraw)) * 2;
	quadListRead(g_gameQuadCtx->list, 0)->pos.x = fabs(sin(g_gameMillisDraw)) - 0.5f;

	ERRGL(glClearColor(0.8f, 0.6f, 1.0f, 1.0f));
	ERRGL(glViewport(0, 0, g_window1Wfb, g_window1Hfb));
	ERRGL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

	quadCtxDraw(g_gameQuadCtx); // TODO: Limit how many are drawn!
	// TODO: Perhaps also `quadCtxDrawRest()` to draw all remaining!
}
