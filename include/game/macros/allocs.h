#pragma once

// #include <stdlib.h> // Nope! *They* must do the `#include`. They MUST know!

// Allocs!

#define MALLOC_ARRAY_ESIZE(p_array, p_count, p_elementSize)\
{\
	ifu (((p_array) = malloc((p_count) * (p_elementSize))) == NULL) {\
		\
		fprintf(stderr, "`malloc() for `%s` in function `%s` at `%s:%d` failed.\n", (#p_array), __FUNCTION__, __FILE__, __LINE__);\
		exit(GAME_EXIT_MALLOC);\
		\
	}\
}\

#define CALLOC_ARRAY_ESIZE(p_array, p_count, p_elementSize)\
{\
	ifu (((p_array) = calloc((p_count), (p_elementSize))) == NULL) {\
		\
		fprintf(stderr, "`calloc() for `%s` in function `%s` at `%s:%d` failed.\n", (#p_array), __FUNCTION__, __FILE__, __LINE__);\
		exit(GAME_EXIT_CALLOC);\
		\
	}\
}\

#define REALLOC_ARRAY_ESIZE(p_array, p_count, p_elementSize)\
{\
	ifu (((p_array) = realloc((p_array), (p_count) * (p_elementSize))) == NULL) {\
		\
		fprintf(stderr, "`realloc() for `%s` in function `%s` at `%s:%d` failed.\n", (#p_array), __FUNCTION__, __FILE__, __LINE__);\
		exit(GAME_EXIT_REALLOC);\
		\
	}\
}\

#define CALLOC_ARRAY(p_array, p_count, p_type) CALLOC_ARRAY_ESIZE(p_array, p_count, sizeof(p_type))
#define MALLOC_ARRAY(p_array, p_count, p_type) MALLOC_ARRAY_ESIZE(p_array, p_count, sizeof(p_type))
#define REALLOC_ARRAY(p_array, p_count, p_type) REALLOC_ARRAY_ESIZE(p_array, p_count, sizeof(p_type))

#pragma endregion
