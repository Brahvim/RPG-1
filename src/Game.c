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

size_t g_gameFrameCount;
double g_gameMillisDraw;
double g_gameMillisSetup;
struct Quad *g_gameQuadBg;
struct QuadCtx *g_gameQuadCtx;
struct QuadCtx *g_gameQuadCtxBg;

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
	quadCtxDelete(g_gameQuadCtxBg);
}

void gameSetup() {
	quadSystemInit();
	smlMat44Identity(&g_camera2dTransf);
	smlMat44Identity(&g_cameraCurrentTransf);
	struct QuadCtx *qc = g_gameQuadCtx = quadCtxCreate();
	struct QuadCtx *bg = g_gameQuadCtxBg = quadCtxCreate();

	quadCtxNew(bg);
	g_gameQuadBg = quadListTail(bg->list);
	g_gameQuadBg->tintRgba = smlQuatVal(0.8f, 0.6f, 1.0f, 0.1f); // *Strawberry milk!*
	// g_gameQuadBg->tintRgba = smlQuatVal(0.8f, 0.6f, 1.0f, 1); // Texture-missing purple.

	listExpand(qc->list, 2);

	quadCtxAppend(
		qc,
		quadVal(
			.tintRgba = smlQuatVal(0, 0, 0, 1),
			.scale = (*smlVec3ScaleSame(smlVec3Ptr(1.25f, 1), 50))
		)
	);
	quadTexture(quadListTail(qc->list), ATLAS_DEFAULT, TEXTURE_GRID);

	quadCtxAppend(
		qc,
		quadVal(
			.tintRgba = smlQuatVal(1, 0, 0, 0.25f),
			.scale = (*smlVec3ScaleSame(smlVec3Ptr(1, 1, 1), 15))
		)
	);
	// quadTexture(quadListTail(qc->list), ATLAS_DEFAULT, TEXTURE_MISSING);
}

void gameDraw() {
	ERRGL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	ERRGL(glViewport(0, 0, g_window1Wfb, g_window1Hfb));
	ERRGL(glClear(GL_DEPTH_BUFFER_BIT));

	ERRGL(glDisable(GL_DEPTH_TEST));
	ERRGL(glDisable(GL_CULL_FACE));
	ERRGL(glDepthMask(GL_FALSE));
	ERRGL(glEnable(GL_BLEND));

	g_camera2dPos.x = ((sinf(g_gameMillisDraw))) * 250;
	g_camera2dPos.y = ((cosf(g_gameMillisDraw))) * 15;
	g_camera2dRot = fabs(((g_gameMillisDraw)));

	g_gameQuadBg->scale = smlVec3Val(g_window1Wfb, g_window1Hfb, 1);
	smlMat44Identity(&g_cameraCurrentTransf);
	quadCtxDraw(g_gameQuadCtxBg);
	camera2dUpdatePersp();
	camera2dApply();

	quadListRead(g_gameQuadCtx->list, 1)->rotate.z = g_gameMillisDraw * 2;
	quadListRead(g_gameQuadCtx->list, 0)->pos.x = fabs(sin(g_gameMillisDraw)) - 0.5f;

	ERRGL(glDisable(GL_DEPTH_TEST));
	ERRGL(glDisable(GL_CULL_FACE));
	ERRGL(glEnable(GL_BLEND));

	// If a fragment's depth is less than the depth of the pixel in the place it wants overwrite,
	// it is drawn; it appears towards the front.
	ERRGL(glDepthFunc(GL_LESS));
	// Of course, this requires that your framebuffer have a depth attachment...!
	ERRGL(glDepthMask(GL_TRUE)); // Yes, we'd like to actually use said depth attachment...!

	quadCtxDraw(g_gameQuadCtx);
}
