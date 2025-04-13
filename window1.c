#include <game/window1.h>

int g_window1X = 0;
int g_window1Y = 0;
int g_window1W = 0;
int g_window1H = 0;
int g_window1Wfb = 0;
int g_window1Hfb = 0;
GLFWwindow *g_window1 = NULL;
int const g_window1WDef = 640;
int const g_window1HDef = 480;

void gameWindow1UpdateVars(void) {
	glfwGetWindowPos(g_window1, &g_window1X, &g_window1Y);
	glfwGetWindowSize(g_window1, &g_window1W, &g_window1H);
	glfwGetFramebufferSize(g_window1, &g_window1Wfb, &g_window1Hfb);
}

void gameWindow1CbckKey(GLFWwindow *const p_window, int const p_key, int const p_scancode, int const p_action, int const p_mods) {
	// NOPE!
	// switch (p_action) {
	//
	// 	case GLFW_PRESS: {
	//
	// 	} break;
	//
	// 	case GLFW_REPEAT: {
	//
	// 	} break;
	//
	// 	case GLFW_RELEASE: {
	//
	// 	} break;
	//
	// }

	// We *compose!*...
	ifl(p_action == GLFW_PRESS && p_key == GLFW_KEY_ESCAPE) { // Will eventually use `GLFW_REPEAT` *kinda' like* `SURVEY_PROGRAM.exe`...!

		glfwSetWindowShouldClose(g_window1, GLFW_TRUE);

	}
}
