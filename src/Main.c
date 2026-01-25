#include <stb/stb_image.h>
#include <glad/gles2.h>

#define __USE_XOPEN
#include <stdlib.h>
#undef __USE_XOPEN

#include <string.h>
#include <stdio.h>

#include "Window1.h"
#include "Macros.h"
#include "Assets.h"
#include "Game.h"
#include "Log.h"
#include "Gl.h"

void cliFlagGpu(int const p_argCount, char const **p_argValues) {
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
	putchar('\n');
	cliFlagGpu(p_argCount, p_argValues);

	glfwInit();
	window1Create();
	glfwSwapInterval(0);
	glfwMakeContextCurrent(g_window1);
	gladLoadGLES2(glfwGetProcAddress);

	puti("OpenGL Vendor:");
	puti(glGetString(GL_VENDOR));

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
