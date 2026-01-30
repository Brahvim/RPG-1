#include "Sml.h"
#include "Log.h"
#include "Test.h"
#include <stdio.h>
#include "Macros.h"
#include <stdlib.h>
#include <memory.h>
#include <stdbool.h>

#define dashl() \
puti("------------------------------------------------------------------------------")

int testRunTests(int const p_count, struct Test const *const p_tests) {
	int passed = 0;
	dashl();

	for (int i = 0; i < p_count; i++) {

		bool const result = p_tests[i].function();

		if (result) {

			++passed;
			printi("Test `%d`, `%s()`, successfully passed...\n", i, p_tests[i].name);

		}
		else {

			printe("Test `%d`, `%s()`, *failed!*\n", i, p_tests[i].name);

		}

		dashl();

	}

	puti("Test Results :)!!!");
	printi("`%d` tests passed.\n", passed);
	printi("`%d` tests failed.\n", p_count - passed);

	return
		passed == p_count
		? 0
		: passed
		;
}
