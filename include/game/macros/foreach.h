#pragma once

#include "game/macros/ops.h"

#include "game/macros/erroneous.h"

#include "game/macros/foreach/arg.h"
#include "game/macros/foreach/argslist.h"
#include "game/macros/foreach/recursive.h"

#define ERRONEOUS(p_function, ...) 				CALL_RECURSIVE_MACROS_FOR_EACH(ERRONEOUS, p_function, __VA_ARGS__)
#define CALL_FOR_EACH_ARG(p_function, ...)		CALL_RECURSIVE_MACROS_FOR_EACH(CALL_FOR_EACH_ARG, p_function, __VA_ARGS__)
#define STRUCTS_ABI_CHECK(p_function, ...)		CALL_RECURSIVE_MACROS_FOR_EACH(STRUCTS_ABI_CHECK, p_function, __VA_ARGS__)
#define CALL_FOR_EACH_ARGLIST(p_function, ...)	CALL_RECURSIVE_MACROS_FOR_EACH(CALL_FOR_EACH_ARGLIST, p_function, __VA_ARGS__)
