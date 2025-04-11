#pragma once
#include <stdio.h>

extern size_t g_cwdLen;
extern char g_cwd[FILENAME_MAX];

enum GameExit {

	GAME_EXIT_OKAY,
	GAME_EXIT_FAILED, // For when you don't know *why!*
	GAME_EXIT_GET_CWD,

};

void gameExit(int const reason);

#pragma region // Textures.
enum GameTex {

	GAME_TEX_0,
	GAME_TEX_1,
	GAME_TEX_TOTAL // Can also be treated as a `NULL` handle!

};

char const *g_gameTexesPaths[GAME_TEX_TOTAL] = {

	"assets/test.png",
	"assets/null.png",

};

int g_gameTexesW[GAME_TEX_TOTAL];
int g_gameTexesH[GAME_TEX_TOTAL];
unsigned char *g_gameTexes[GAME_TEX_TOTAL];

void gameTexesLoad(void);
void gameTexesFree(void);
#pragma endregion
