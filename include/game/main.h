#pragma once

extern char g_cwd[];
extern size_t g_cwdLen;

#pragma region // Exiting.
enum GameExit {

	GAME_EXIT_OKAY,
	GAME_EXIT_FAILED, // For when you don't know *why!*
	GAME_EXIT_GET_CWD,
	GAME_EXIT_TOTAL

};

void gameExit(int const reason);
#pragma endregion

#pragma region // Textures.
enum GameTex {

	GAME_TEX_NULL,
	GAME_TEX_TEST0,
	GAME_TEX_TEST1,
	GAME_TEX_TEST2,
	GAME_TEX_TOTAL

};

char const *g_gameTexesPaths[GAME_TEX_TOTAL] = {

	"assets/null.png",
	"assets/test0.png",
	"assets/test1.png",
	"assets/test2.png",

};

int g_gameTexesW[GAME_TEX_TOTAL];
int g_gameTexesH[GAME_TEX_TOTAL];
GLuint g_gameTexesGl[GAME_TEX_TOTAL];
unsigned char *g_gameTexesData[GAME_TEX_TOTAL];

void gameTexesLoad(void);
#pragma endregion
