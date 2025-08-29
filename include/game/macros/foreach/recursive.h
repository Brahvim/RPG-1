#pragma once

#include "game/macros/ops.h"

// `CALL_RECURSIVE_MACROS_FOR_EACH()` recursive macros *and* mechanism.

// A classic from [ https://stackoverflow.com/a/1872506 ]...!:

#pragma region // Recursive stuff.

#define CALL_RECURSIVE_MACROS_FOR_EACH1(p_function, p_arglist, ...) p_function##p_arglist

#define CALL_RECURSIVE_MACROS_FOR_EACH2(p_function, p_arglist, ...)\
	p_function ## p_arglist;\
	CALL_RECURSIVE_MACROS_FOR_EACH1(p_function, __VA_ARGS__)\

#define CALL_RECURSIVE_MACROS_FOR_EACH3(p_function, p_arglist, ...)\
	p_function ## p_arglist;\
	CALL_RECURSIVE_MACROS_FOR_EACH2(p_function, __VA_ARGS__);

#define CALL_RECURSIVE_MACROS_FOR_EACH4(p_function, p_arglist, ...)\
	p_function ## p_arglist;\
	CALL_RECURSIVE_MACROS_FOR_EACH3(p_function, __VA_ARGS__)\

#define CALL_RECURSIVE_MACROS_FOR_EACH5(p_function, p_arglist, ...)\
	p_function ## p_arglist;\
 CALL_RECURSIVE_MACROS_FOR_EACH4(p_function, __VA_ARGS__)\

#define CALL_RECURSIVE_MACROS_FOR_EACH6(p_function, p_arglist, ...)\
	p_function ## p_arglist;\
	CALL_RECURSIVE_MACROS_FOR_EACH5(p_function, __VA_ARGS__)\

#define CALL_RECURSIVE_MACROS_FOR_EACH7(p_function, p_arglist, ...)\
	p_function ## p_arglist;\
	CALL_RECURSIVE_MACROS_FOR_EACH6(p_function, __VA_ARGS__)\

#define CALL_RECURSIVE_MACROS_FOR_EACH8(p_function, p_arglist, ...)\
	p_function ## p_arglist;\
	CALL_RECURSIVE_MACROS_FOR_EACH7(p_function, __VA_ARGS__)\

#define CALL_RECURSIVE_MACROS_FOR_EACH9(p_function, p_arglist, ...)\
	p_function ## p_arglist;\
	CALL_RECURSIVE_MACROS_FOR_EACH8(p_function, __VA_ARGS__)\

#define CALL_RECURSIVE_MACROS_FOR_EACH10(p_function, p_arglist, ...)\
	p_function ## p_arglist;\
	CALL_RECURSIVE_MACROS_FOR_EACH9(p_function, __VA_ARGS__)\

#pragma endregion

// This macro receives all actual arguments and *then* numbers from `CALL_RECURSIVE_MACROS_FOR_EACH_SEQUENCE`.
// The number that lands in `p_count` tells us the number of arguments that came in!
// Think `CALL_RECURSIVE_MACROS_FOR_EACH_SELECT_MACRO_IMPL(call, arg1, arg2, 10, /* ... */, 3, 2)`.
// The last argument was `2`. It was indeed `p_count`!
// Ellipses (`...`) "drains out" extra numbers.
#define CALL_RECURSIVE_MACROS_FOR_EACH_ARG_SELECT_LAST_OF_11_ARGS(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, p_count, ...) p_count

#define CALL_RECURSIVE_MACROS_FOR_EACH_SELECT_MACRO_IMPL(...)\
CALL_RECURSIVE_MACROS_FOR_EACH_ARG_SELECT_LAST_OF_11_ARGS(__VA_ARGS__)

// Total count is fetched from these CSVs:
#define CALL_RECURSIVE_MACROS_FOR_EACH_SEQUENCE \
10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0

// ...by this macro. It pushes all arguments received and *the numbers* into `CALL_RECURSIVE_MACROS_FOR_EACH_SELECT_MACRO_IMPL()`
// which calls `CALL_RECURSIVE_MACROS_FOR_EACH_ARG_SELECT_LAST_OF_11_ARGS()` so the number of arguments can be counted.
// `CALL_RECURSIVE_MACROS_FOR_EACH_SELECT_MACRO_IMPL()` exists to stringize macros:
#define CALL_RECURSIVE_MACROS_FOR_EACH_SELECT_MACRO(...)\
CALL_RECURSIVE_MACROS_FOR_EACH_SELECT_MACRO_IMPL(__VA_ARGS__, CALL_RECURSIVE_MACROS_FOR_EACH_SEQUENCE)

// `CAT()` chooses one of the `CALL_RECURSIVE_MACROS_FOR_EACH_*()` macros to call.
#define CALL_RECURSIVE_MACROS_FOR_EACH_IMPL(p_recursiveMacroName, p_count, p_function, ...)\
CAT(p_recursiveMacroName, p_count)(p_function, __VA_ARGS__)

/**
 * @param	`p_recursiveMacroName` is the name used to call macro-functions;
 *			it is suffixed with a number to detect which exact macro to call.
 *			The called macro then calls the macro with the smaller number suffixed to it.
 * @param	`p_function` is the macro-function or C function to call in a loop.
 */
#define CALL_RECURSIVE_MACROS_FOR_EACH(p_recursiveMacroName, p_function, ...)\
CALL_RECURSIVE_MACROS_FOR_EACH_IMPL(\
	p_recursiveMacroName,\
	CALL_RECURSIVE_MACROS_FOR_EACH_SELECT_MACRO(__VA_ARGS__),\
	p_function, __VA_ARGS__\
)

#pragma endregion
