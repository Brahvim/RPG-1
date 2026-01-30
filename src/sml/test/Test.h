#pragma once

#include "Sml.h"
#include "Log.h"
#include <math.h>
#include <stdio.h>
#include "Macros.h"
#include <stdlib.h>
#include <memory.h>
#include <stdbool.h>

typedef bool (*test_t)(void);

struct Test {

	test_t function;
	const char *const name;

};

int testRunTests(int const count, struct Test const *const tests);

#define testfn static bool

#define testCreateTest(p_function)	\
{ (p_function), STR2(p_function) }

#define testRunTestsArray(p_array)	\
testRunTests(sizearr(p_array), p_array)

#define testCreateArray(...)	\
((struct Test const []) { __VA_ARGS__ })

#define testCheck(p_prefix, p_condition)	\
if (unlikely(!(p_prefix (p_condition)))) {	\
	\
	printe("Failure!\n", STR2(p_condition));	\
	\
}

#define testCheckFloat(p_prefix, p_result, p_answer)	\
testCheck(p_prefix, smlFloatCompareFltEpsilon(p_result, p_answer))

#define testCheckFloatEpsilon(p_prefix, p_result, p_answer, p_epsilon)	\
testCheck(p_prefix, smlFloatCompare(p_result, p_answer, p_epsilon))
