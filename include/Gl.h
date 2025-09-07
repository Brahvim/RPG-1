#pragma once
#include <glad/gles2.h>

extern GLenum g_errorGl;

#define ERRGL(x) x;\
if ((g_errorGl = glGetError()) != GL_NO_ERROR) {\
	printf("OpenGL error `%d` (%s), %s:%d.\n", g_errorGl, glGetErrorString(g_errorGl), __FILE__, __LINE__);\
}\

char const* glGetErrorString(GLenum const error);
