#include <stb/stb_image.h>
#include <glad/gles2.h>
#include <stdlib.h>
#include <stdio.h>

#include "UtilMacros.h"
#include "Window1.h"
#include "Assets.h"
#include "Game.h"
#include "Gl.h"

void myGpuCheck() {
	char const *const envGpu = getenv("gpu");
	char const gpu = envGpu ? envGpu[0] : 'i';

	printf("Running on %cGPU!\n", gpu);

	if (gpu == 'd') {

		system("echo __NV_PRIME_RENDER_OFFLOAD=${__NV_PRIME_RENDER_OFFLOAD}");
		system("echo __GLX_VENDOR_LIBRARY_NAME=${__GLX_VENDOR_LIBRARY_NAME}");

	}
}

int main(int const p_argCount, char const **p_argValues) {
	myGpuCheck();

	glfwInit();
	window1Create();
	glfwSwapInterval(0);
	glfwMakeContextCurrent(g_window1);
	gladLoadGLES2(glfwGetProcAddress);

	loadCwd();
	loadShaders();
	loadTextures();
	loadMappedAtlases();

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

	gameExit(EXIT_REASON_SUCCESS);
}
