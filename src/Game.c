#include <stb/stb_rect_pack.h>
#include "Window1.h"
#include "Assets.h"
#include <stdio.h>
#include "Quads.h"
#include "Game.h"

double g_gameMillisSetup;
size_t g_gameFrameCount;
double g_gameMillisDraw;

double gameMillis(void) {
	return glfwGetTime() - g_gameMillisSetup;
}

void gameSetup(void) {
	quadInit();
}

void gameDraw(void) {
	ERRGL(glViewport(0, 0, g_window1Wfb, g_window1Hfb));
	ERRGL(glClearColor(0.8f, 0.6f, 1.0f, 0.1f));
	ERRGL(glClear(GL_COLOR_BUFFER_BIT));
}
