#pragma once
#include <glad.h>
#include "main.h"

extern GLenum g_errorGl;
#define ERRGL(x) x;\
if ((g_errorGl = glGetError()) != GL_NO_ERROR) {\
	printf("OpenGL error `%d` (%s), %s:%d.\n", g_errorGl, glGetErrorString(g_errorGl), __FILE__, __LINE__);\
}\

char const* glGetErrorString(GLenum error);
GLint gameShaderFromFile(GLchar const **buffer, char const *path);

#pragma region // Textures.
enum GameTex {

	GAME_TEX_NULL,
	GAME_TEX_TEST0,
	GAME_TEX_TEST1,
	GAME_TEX_TEST2,
	GAME_TEX_TOTAL

};

enum GameTexFlips {

	GAME_FLIP_NONE,
	GAME_FLIP_BOTH,
	GAME_FLIP_VERTICAL,
	GAME_FLIP_HORIZONTAL,
	GAME_FLIP_TOTAL

};

void gameTexesLoad(void);

extern int g_gameTexesW[GAME_TEX_TOTAL];
extern int g_gameTexesH[GAME_TEX_TOTAL];
extern GLuint g_gameTexesGl[GAME_TEX_TOTAL];
extern char const *g_gameTexesPaths[GAME_TEX_TOTAL];
extern unsigned char *g_gameTexesData[GAME_TEX_TOTAL];
#pragma endregion
