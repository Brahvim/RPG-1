#pragma once

typedef unsigned long long game_size_t;

extern size_t g_cwdLen;
extern char g_cwd[];

#pragma region // Exiting.
enum GameExit {

	GAME_EXIT_OKAY,
	GAME_EXIT_FAILED, // For when you don't know *why!*
	GAME_EXIT_GET_CWD,
	GAME_EXIT_TOTAL

};

void gameExit(int const reason);
#pragma endregion
