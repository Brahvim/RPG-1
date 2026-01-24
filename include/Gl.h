#pragma once
#include "UtilMacros.h"
#include <glad/gles2.h>

extern GLenum g_glerr;

#define glerr(x) x;\
if (likely((g_glerr = glGetError()) != GL_NO_ERROR)) {\
	printe("OpenGL error `%d` (%s), %s:%d.\n", g_glerr, glGetErrorString(g_glerr), __FILE__, __LINE__);\
}\

char const* glGetErrorString(GLenum const error);
