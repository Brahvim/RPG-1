#pragma once

#define STR(x) #x
#define STR2(x) STR(x)
#define CAT(x, y) x ## y
#define CAT2(x, y) CAT(x, y)

#define asarr(p_type, p_body) 	((p_type[]) p_body)
#define sizearr(p_array) 		(sizeof(p_array) / sizeof(p_array[0]))
#define likely(p_condition) 	__builtin_expect((long) (p_condition), 1)
#define unlikely(p_condition) 	__builtin_expect((long) (p_condition), 0)

#pragma region Allocation.
// #include <stdlib.h> // Nope! *They* must do the `#include`. They MUST know!
// #include <stdio.h>

#define mallocArrayStride(p_array, p_count, p_stride) {\
	if (unlikely((((p_array) = malloc((p_count) * (p_stride))) == NULL))) {\
		\
		printe("`malloc() for `%s` in function `%s` at `%s:%d` failed.\n", (#p_array), __FUNCTION__, __FILE__, __LINE__);\
		gameExit(EXIT_REASON_MALLOC);\
		\
	}\
}\

#define callocArrayStride(p_array, p_count, p_stride) {\
	if (unlikely((((p_array) = calloc((p_count), (p_stride))) == NULL))) {\
		\
		printe("`calloc() for `%s` in function `%s` at `%s:%d` failed.\n", (#p_array), __FUNCTION__, __FILE__, __LINE__);\
		gameExit(EXIT_REASON_CALLOC);\
		\
	}\
}\

#define reallocArrayStride(p_array, p_count, p_stride) {\
	if (unlikely((((p_array) = realloc((p_array), (p_count) * (p_stride))) == NULL))) {\
		\
		printe("`realloc() for `%s` in function `%s` at `%s:%d` failed.\n", (#p_array), __FUNCTION__, __FILE__, __LINE__);\
		gameExit(EXIT_REASON_REALLOC);\
		\
	}\
}\

#pragma region Derivatives.
#define callocStruct(p_ptr) callocArrayStride(p_ptr, 1, sizeof(typeof(*p_ptr)))
#define MALLOC_STRUCT(p_ptr) mallocArrayStride(p_ptr, 1, sizeof(typeof(*p_ptr)))
#define REALLOC_STRUCT(p_ptr) reallocArrayStride(p_ptr, 1, sizeof(typeof(*p_ptr)))

#define callocStructType(p_ptr, p_name) callocArrayStride(p_ptr, 1, sizeof(struct p_name))
#define mallocStructType(p_ptr, p_name) mallocArrayStride(p_ptr, 1, sizeof(struct p_name))
#define reallocStructType(p_ptr, p_name) reallocArrayStride(p_ptr, 1, sizeof(struct p_name))

#define callocArray(p_array, p_count) callocArrayStride(p_array, p_count, sizeof(typeof(p_array[0])))
#define mallocArray(p_array, p_count) mallocArrayStride(p_array, p_count, sizeof(typeof(p_array[0])))
#define reallocArray(p_array, p_count) reallocArrayStride(p_array, p_count, sizeof(typeof(p_array[0])))

#define callocArrayType(p_array, p_count, p_type) callocArrayStride(p_array, p_count, sizeof(p_type))
#define mallocArrayType(p_array, p_count, p_type) mallocArrayStride(p_array, p_count, sizeof(p_type))
#define reallocArrayType(p_array, p_count, p_type) reallocArrayStride(p_array, p_count, sizeof(p_type))
#pragma endregion
#pragma endregion
