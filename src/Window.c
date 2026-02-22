#include "Window.h"
#include <stdlib.h>

struct List g_windowList;
struct Window *s_windowCurrent;

size_t windowGetIndex() {

}

struct Window* windowGet() {
	return s_windowCurrent;
}

struct Window* windowDelete(struct Window *const p_window) {
	glfwDestroyWindow(p_window->glfw);
	free(p_window);
	return NULL;
}

struct Window* windowSet(struct Window *const p_window) {
	struct Window *prev = s_windowCurrent;
	glfwMakeContextCurrent(p_window->glfw);
	s_windowCurrent = p_window;
	return prev;
}

struct Window *const windowCreate(struct Window *const p_storage) {
	p_storage->glfw = glfwCreateWindow(p_storage->wd, p_storage->hd, NULL, NULL, NULL);
	return p_storage;
}
