#define __USE_XOPEN
#include <stb/stb_image.h>
#include <glad/gles2.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "Window1.h"
#include "Window.h"
#include "Macros.h"
#include "Assets.h"
#include "Game.h"
#include "Exit.h"
#include "Log.h"
#include "Gl.h"
#undef __USE_XOPEN

static void cliFlagGpu(int const p_argCount, char const **p_argValues) {
	char gpu = 'i';
	if (p_argCount != 2) goto print;

	char const *const flag = p_argValues[1];
	size_t const len = strlen(flag);

	if (len != 3) goto print;
	if (flag[0] != '-') goto print;
	if (flag[1] != 'g') goto print;

	gpu = flag[2];
	switch (gpu) {

		case 'd': {

			system("echo __NV_PRIME_RENDER_OFFLOAD=${__NV_PRIME_RENDER_OFFLOAD}");
			system("echo __GLX_VENDOR_LIBRARY_NAME=${__GLX_VENDOR_LIBRARY_NAME}");

		} break;

		case 'i': break;
		default: return;

	};

print:
	printi("Running on %cGPU!\n", gpu);
}

int main(int const p_argCount, char const **p_argValues) {
	cliFlagGpu(p_argCount, p_argValues);

	void* arr = ((void*) { "Brahvim" });
	puti((char const *const) arr);

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
	printi("OpenGL Vendor: \"%s\".\n", glGetString(GL_VENDOR));

	gameSetup();

	while (likely(!glfwWindowShouldClose(g_window1))) {

		glfwPollEvents();

		g_gameMillisDraw = glfwGetTime();
		++g_gameFrameCount;
		window1Update();
		gameDraw();

		glfwSwapBuffers(g_window1);

	}

	gameExit(EXIT_REASON_SUCCESS);
}
