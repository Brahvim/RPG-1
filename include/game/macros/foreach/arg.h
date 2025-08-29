#pragma once

#include "game/macros/ops.h"

// `CALL_FOR_EACH_ARG()` recursive macros.

#define CALL_FOR_EACH_ARG0(p_function, p_arg, ...) p_function()

#define CALL_FOR_EACH_ARG1(p_function, p_arg, ...) p_function(p_arg)

#define CALL_FOR_EACH_ARG2(p_function, p_arg, ...)\
	p_function(p_arg);\
	CALL_FOR_EACH_ARG1(p_function, __VA_ARGS__)\

#define CALL_FOR_EACH_ARG3(p_function, p_arg, ...)\
	p_function(p_arg);\
	CALL_FOR_EACH_ARG2(p_function, __VA_ARGS__);

#define CALL_FOR_EACH_ARG4(p_function, p_arg, ...)\
	p_function(p_arg);\
	CALL_FOR_EACH_ARG3(p_function, __VA_ARGS__)\

#define CALL_FOR_EACH_ARG5(p_function, p_arg, ...)\
	p_function(p_arg);\
 CALL_FOR_EACH_ARG4(p_function, __VA_ARGS__)\

#define CALL_FOR_EACH_ARG6(p_function, p_arg, ...)\
	p_function(p_arg);\
	CALL_FOR_EACH_ARG5(p_function, __VA_ARGS__)\

#define CALL_FOR_EACH_ARG7(p_function, p_arg, ...)\
	p_function(p_arg);\
	CALL_FOR_EACH_ARG6(p_function, __VA_ARGS__)\

#define CALL_FOR_EACH_ARG8(p_function, p_arg, ...)\
	p_function(p_arg);\
	CALL_FOR_EACH_ARG7(p_function, __VA_ARGS__)\

#define CALL_FOR_EACH_ARG9(p_function, p_arg, ...)\
	p_function(p_arg);\
	CALL_FOR_EACH_ARG8(p_function, __VA_ARGS__)\

#define CALL_FOR_EACH_ARG10(p_function, p_arg, ...)\
	p_function(p_arg);\
	CALL_FOR_EACH_ARG9(p_function, __VA_ARGS__)\

