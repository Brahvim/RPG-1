#include <stdlib.h>
#include "Window.h"
#include "Macros.h"
#include <stdio.h>

size_t s_windowCount = 0;

struct Window* windowDelete(struct Window *const p_window) {
	glfwDestroyWindow(p_window->glfw);
	free(p_window);
	return NULL;
}

struct Window *const windowCreate(struct Window *const p_window) {
	char title[64];
	++s_windowCount;
	snprintf(title, sizearr(title), "RPG Window %zu", s_windowCount);
	p_window->glfw = glfwCreateWindow(p_window->wd, p_window->hd, title, NULL, NULL);
	return p_window;
}
