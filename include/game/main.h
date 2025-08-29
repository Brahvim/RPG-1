#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "macros.h"
#include "game/macros.h"

typedef size_t game_t;

void gameSetup(void);
void gameDraw(void);

extern char g_gameCwd[];
extern size_t g_gameCwdLen;

#pragma region // Exiting.

enum GameExit {

	GAME_EXIT_OKAY,
	GAME_EXIT_FAILED, // For when you don't know *why!*
	GAME_EXIT_CALLOC,
	GAME_EXIT_MALLOC,
	GAME_EXIT_GET_CWD,
	GAME_EXIT_REALLOC,
	GAME_EXIT_TOTAL

};

void gameExit(enum GameExit const cause);

#pragma endregion
