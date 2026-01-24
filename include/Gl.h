#pragma once
#include "Log.h"
#include "Macros.h"
#include <glad/gles2.h>

extern GLenum g_glerr;

#define ERRGL(x) x;\
if (likely((g_glerr = glGetError()) != GL_NO_ERROR)) {\
	printe("OpenGL error `%d` (%s), %s:%d.\n", g_glerr, glGetErrorString(g_glerr), __FILE__, __LINE__);\
}\

char const* glGetErrorString(GLenum const error);
