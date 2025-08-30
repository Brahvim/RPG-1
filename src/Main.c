#include <stb/stb_image.h>
#include <stdlib.h>

#include "UtilMacros.h"
#include "Window1.h"
#include "Assets.h"

#include <glad/gles2.h>
#include <stdio.h>

#include "UtilGl.h"

int main(int const p_argCount, char const **p_argValues) {
	glfwInit();
	window1Create();
	glfwSwapInterval(0);
	glfwMakeContextCurrent(g_window1);
	gladLoadGLES2(glfwGetProcAddress);

	loadCwd();
	loadTextures();

	while (likely(!glfwWindowShouldClose(g_window1))) {

		glfwPollEvents();
		window1UpdateVars();

		static int frameCount = 0;
		ERRGL(glBindFramebuffer(GL_FRAMEBUFFER, 0));

		ERRGL(glViewport(0, 0, g_window1Wfb, g_window1Hfb));
		ERRGL(glClearColor(0.8f, 0.6f, 1.0f, 0.1f));
		ERRGL(glClear(GL_COLOR_BUFFER_BIT));

		++frameCount;

		glfwSwapBuffers(g_window1);

	}

	window1Delete();
	glfwTerminate();
	return EXIT_SUCCESS;
}
