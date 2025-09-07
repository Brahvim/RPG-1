#include <stb/stb_image.h>
#include <glad/gles2.h>
#include <stdlib.h>
#include <stdio.h>

#include "UtilMacros.h"
#include "Window1.h"
#include "Assets.h"
#include "Game.h"
#include "Gl.h"

int main(int const p_argCount, char const **p_argValues) {
	glfwInit();
	window1Create();
	glfwSwapInterval(0);
	glfwMakeContextCurrent(g_window1);
	gladLoadGLES2(glfwGetProcAddress);

	loadCwd();
	loadTextures();
	loadAtlases();

	g_gameMillisSetup = glfwGetTime();
	gameSetup();

	while (likely(!glfwWindowShouldClose(g_window1))) {

		glfwPollEvents();
		++g_gameFrameCount;
		window1UpdateVars();
		g_gameMillisDraw = glfwGetTime();

		gameDraw();
		glfwSwapBuffers(g_window1);

	}

	window1Delete();
	glfwTerminate();
	return EXIT_SUCCESS;
}
