#include <game/window1.h>

int g_window1X = 0;
int g_window1Y = 0;
int g_window1W = 0;
int g_window1H = 0;
int g_window1FbW = 0;
int g_window1FbH = 0;
GLFWwindow *g_window1;

void gameWindow1UpdateVars(void) {
	glfwGetWindowPos(g_window1, &g_window1X, &g_window1Y);
	glfwGetWindowSize(g_window1, &g_window1W, &g_window1H);
	glfwGetFramebufferSize(g_window1, &g_window1FbW, &g_window1FbH);
}
