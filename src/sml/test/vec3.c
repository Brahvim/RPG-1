#include "Sml.h"
#include "Log.h"
#include "Test.h"
#include <stdio.h>
#include "Macros.h"
#include <stdlib.h>
#include <memory.h>
#include <stdbool.h>

testfn add() {
	float arr[] = { 1, 2, 3, };
	struct SmlVec3 vec1 = smlVec3Val(1, 2, 3);
	puti("Adding:");
	printi("%f, %f, %f.\n", vec1.x, vec1.y, vec1.z);

	struct SmlVec3 vec2 = smlVec3(arr);
	printi("%f, %f, %f.\n", vec2.x, vec2.y, vec2.z);

	puti("Result:");
	smlVec3Add(&vec1, &vec2, &vec1);
	printi("%f, %f, %f.\n", vec1.x, vec1.y, vec1.z);
}

testfn create() {
	float arr[] = { 1, 2, 3, };
	struct SmlVec3 v = smlVec3(arr);
	puti("Vector:");
	printi("%f, %f, %f.\n", v.x, v.y, v.z);
}

int main(int const p_count, char *p_values[]) {
	return testRunTestsArray(testCreateArray(

		testCreateTest(add),
		testCreateTest(create)

	));
}
