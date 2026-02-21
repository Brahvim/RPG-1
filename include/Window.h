#pragma once

#include "List.h"
#include <stddef.h>
#include <stdbool.h>
#define GLFW_INCLUDE_NONE 1
#include <GLFW/glfw3.h>

struct Window {

	int x;
	int y;
	int w;
	int h;

	int xu; // "Un-full".
	int yu; // "Un-full".
	int wu; // "Un-full".
	int hu; // "Un-full".

	int wf; // "Framebuffer".
	int hf; // "Framebuffer".
	int const hd; // "Default".
	int const wd; // "Default".

	bool isFullscreen;
	struct GLFWwindow *glfw;

};

extern struct List g_windowList;

size_t windowGetIndex();
struct Window* windowGet();
struct Window* windowDelete(struct Window *const window);
struct Window* windowSet(struct Window const *const window); // Calls `glfwMakeContextCurrent()`.
struct Window *const windowCreate(struct Window *const storage);

#define windowVal(...)							((struct Window) { __VA_ARGS__ } )
#define windowPtr(...)							(&((struct Window*) { __VA_ARGS__ } ))
#define windowListTail(p_list)					windowListRead(p_list, p_list->size - 1)
#define windowListRead(p_list, p_id)			((struct Window*) listRead(p_list, p_id))
#define windowListAppend(p_list, p_window)		*(((struct Window*) p_list->data) + p_list->size++) = (p_window)
#define windowListSet(p_list, p_id, p_window)	*(((struct Window*) p_list->data) + p_id) = (p_window)
