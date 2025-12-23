#pragma once
#include "Exit.h"

#define likely(p_condition) __builtin_expect((long) (p_condition), 1)
#define unlikely(p_condition) __builtin_expect((long) (p_condition), 0)

#pragma region Allocation.

// #include <stdlib.h> // Nope! *They* must do the `#include`. They MUST know!
// #include <stdio.h>

#define MALLOC_ARRAY_STRIDE(p_array, p_count, p_elementSize) {\
	if (unlikely((((p_array) = malloc((p_count) * (p_elementSize))) == NULL))) {\
		\
		fprintf(stderr, "`malloc() for `%s` in function `%s` at `%s:%d` failed.\n", (#p_array), __FUNCTION__, __FILE__, __LINE__);\
		gameExit(EXIT_REASON_MALLOC);\
		\
	}\
}\

#define CALLOC_ARRAY_STRIDE(p_array, p_count, p_elementSize) {\
	if (unlikely((((p_array) = calloc((p_count), (p_elementSize))) == NULL))) {\
		\
		fprintf(stderr, "`calloc() for `%s` in function `%s` at `%s:%d` failed.\n", (#p_array), __FUNCTION__, __FILE__, __LINE__);\
		gameExit(EXIT_REASON_CALLOC);\
		\
	}\
}\

#define REALLOC_ARRAY_STRIDE(p_array, p_count, p_elementSize) {\
	if (unlikely((((p_array) = realloc((p_array), (p_count) * (p_elementSize))) == NULL))) {\
		\
		fprintf(stderr, "`realloc() for `%s` in function `%s` at `%s:%d` failed.\n", (#p_array), __FUNCTION__, __FILE__, __LINE__);\
		gameExit(EXIT_REASON_REALLOC);\
		\
	}\
}\

#pragma region Derivatives.

#define CALLOC_STRUCT(p_ptr) CALLOC_ARRAY_STRIDE(p_ptr, 1, sizeof(typeof(*p_ptr)))
#define MALLOC_STRUCT(p_ptr) MALLOC_ARRAY_STRIDE(p_ptr, 1, sizeof(typeof(*p_ptr)))
#define REALLOC_STRUCT(p_ptr) REALLOC_ARRAY_STRIDE(p_ptr, 1, sizeof(typeof(*p_ptr)))

#define CALLOC_STRUCT_TYPE(p_ptr, p_name) CALLOC_ARRAY_STRIDE(p_ptr, 1, sizeof(struct p_name))
#define MALLOC_STRUCT_TYPE(p_ptr, p_name) MALLOC_ARRAY_STRIDE(p_ptr, 1, sizeof(struct p_name))
#define REALLOC_STRUCT_TYPE(p_ptr, p_name) REALLOC_ARRAY_STRIDE(p_ptr, 1, sizeof(struct p_name))

#define CALLOC_ARRAY(p_array, p_count) CALLOC_ARRAY_STRIDE(p_array, p_count, sizeof(typeof(p_array[0])))
#define MALLOC_ARRAY(p_array, p_count) MALLOC_ARRAY_STRIDE(p_array, p_count, sizeof(typeof(p_array[0])))
#define REALLOC_ARRAY(p_array, p_count) REALLOC_ARRAY_STRIDE(p_array, p_count, sizeof(typeof(p_array[0])))

#define CALLOC_ARRAY_TYPE(p_array, p_count, p_type) CALLOC_ARRAY_STRIDE(p_array, p_count, sizeof(p_type))
#define MALLOC_ARRAY_TYPE(p_array, p_count, p_type) MALLOC_ARRAY_STRIDE(p_array, p_count, sizeof(p_type))
#define REALLOC_ARRAY_TYPE(p_array, p_count, p_type) REALLOC_ARRAY_STRIDE(p_array, p_count, sizeof(p_type))

#pragma endregion

#pragma endregion
