#pragma once

#include "game/macros/ops.h"

// `CALL_FOR_EACH_ARGLIST()` recursive macros.

#define CALL_FOR_EACH_ARGLIST0(p_function, p_arglist, ...) CAT(p_function, ())

#define CALL_FOR_EACH_ARGLIST1(p_function, p_arglist, ...) CAT(p_function, p_arglist)

#define CALL_FOR_EACH_ARGLIST2(p_function, p_arglist, ...)\
	p_function ## p_arglist;\
	CALL_FOR_EACH_ARGLIST1(p_function, __VA_ARGS__)\

#define CALL_FOR_EACH_ARGLIST3(p_function, p_arglist, ...)\
	p_function ## p_arglist;\
	CALL_FOR_EACH_ARGLIST2(p_function, __VA_ARGS__);

#define CALL_FOR_EACH_ARGLIST4(p_function, p_arglist, ...)\
	p_function ## p_arglist;\
	CALL_FOR_EACH_ARGLIST3(p_function, __VA_ARGS__)\

#define CALL_FOR_EACH_ARGLIST5(p_function, p_arglist, ...)\
	p_function ## p_arglist;\
 CALL_FOR_EACH_ARGLIST4(p_function, __VA_ARGS__)\

#define CALL_FOR_EACH_ARGLIST6(p_function, p_arglist, ...)\
	p_function ## p_arglist;\
	CALL_FOR_EACH_ARGLIST5(p_function, __VA_ARGS__)\

#define CALL_FOR_EACH_ARGLIST7(p_function, p_arglist, ...)\
	p_function ## p_arglist;\
	CALL_FOR_EACH_ARGLIST6(p_function, __VA_ARGS__)\

#define CALL_FOR_EACH_ARGLIST8(p_function, p_arglist, ...)\
	p_function ## p_arglist;\
	CALL_FOR_EACH_ARGLIST7(p_function, __VA_ARGS__)\

#define CALL_FOR_EACH_ARGLIST9(p_function, p_arglist, ...)\
	p_function ## p_arglist;\
	CALL_FOR_EACH_ARGLIST8(p_function, __VA_ARGS__)\

#define CALL_FOR_EACH_ARGLIST10(p_function, p_arglist, ...)\
	p_function ## p_arglist;\
	CALL_FOR_EACH_ARGLIST9(p_function, __VA_ARGS__)\

