#pragma once

typedef unsigned long long game_size_t;

extern size_t g_cwdLen;
extern char g_cwd[];

#define CALLOC_ARRAY(array, count, type)\
{\
	ifu (((array) = calloc((count), sizeof(type))) == NULL) {\
		\
		fprintf(stderr, "`calloc() for `%s` at `%s:%d` failed.\n", (#array), __FILE__, __LINE__);\
		exit(GAME_EXIT_CALLOC);\
		\
	}\
}\

#define REALLOC_ARRAY(array, count, type)\
{\
	ifu (((array) = realloc((array), (count) * sizeof(type))) == NULL) {\
		\
		fprintf(stderr, "`realloc() for `%s` at `%s:%d` failed.\n", (#array), __FILE__, __LINE__);\
		exit(GAME_EXIT_REALLOC);\
		\
	}\
}\

#pragma region // Exiting.
enum GameExit {

	GAME_EXIT_OKAY,
	GAME_EXIT_FAILED, // For when you don't know *why!*
	GAME_EXIT_CALLOC,
	GAME_EXIT_GET_CWD,
	GAME_EXIT_REALLOC,
	GAME_EXIT_TOTAL

};

#pragma endregion
