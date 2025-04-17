#include <game/window1.h>

int g_window1X = 0;
int g_window1Y = 0;
int g_window1W = 0;
int g_window1H = 0;
int g_window1Wfb = 0;
int g_window1Hfb = 0;
char g_window1Full = 0;
int g_window1XUnFull = 0;
int g_window1YUnFull = 0;
int g_window1WUnFull = 0;
int g_window1HUnFull = 0;
GLFWwindow *g_window1 = NULL;
int const g_window1WDef = 640;
int const g_window1HDef = 480;

void gameWindow1UpdateVars(void) {
	glfwGetWindowPos(g_window1, &g_window1X, &g_window1Y);
	glfwGetWindowSize(g_window1, &g_window1W, &g_window1H);
	glfwGetFramebufferSize(g_window1, &g_window1Wfb, &g_window1Hfb);
}

void gameWindow1CbckKey(GLFWwindow *const p_window, int const p_key, int const p_scancode, int const p_action, int const p_mods) {
	// "Likely" so exits are fastest:
	ifl(p_key == GLFW_KEY_ESCAPE && p_action == GLFW_PRESS) { // Will eventually use `GLFW_REPEAT` *kinda' like* `SURVEY_PROGRAM.exe`...!

		glfwSetWindowShouldClose(g_window1, GLFW_TRUE);

	}

	ifu((p_key == GLFW_KEY_F11 || p_key == GLFW_KEY_ENTER && (p_mods & GLFW_MOD_ALT)) && p_action == GLFW_PRESS) {

		ifu(g_window1Full) { // When leaving FS mode.

			glfwSetWindowMonitor(g_window1, NULL, g_window1XUnFull, g_window1YUnFull, g_window1WUnFull, g_window1HUnFull, GLFW_DONT_CARE);

		} else {

			g_window1XUnFull = g_window1X;
			g_window1YUnFull = g_window1Y;
			g_window1WUnFull = g_window1W;
			g_window1HUnFull = g_window1H;
			glfwGetWindowPos(g_window1, &g_window1X, &g_window1Y);
			glfwGetWindowSize(g_window1, &g_window1W, &g_window1H);

			const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
			glfwSetWindowMonitor(g_window1, glfwGetPrimaryMonitor(), 0, 0, mode->width, mode->height, GLFW_DONT_CARE);

		}

		g_window1Full = !g_window1Full;

	}
}
