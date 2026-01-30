#pragma once

#include "Sml.h"
#include "Log.h"
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
#define testRunTestsArray(p_array)	testRunTests(sizearr(p_array), p_array)
#define testCreateTest(p_function)	{ (p_function), STR2(p_function) }
#define testCreateArray(...)		((struct Test const []) { __VA_ARGS__ })
