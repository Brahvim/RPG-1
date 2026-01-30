#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#include "Sml.h"

int main(int const p_count, char *p_values[]) {
	struct SmlQuat quat = {

		.x = 0,
		.y = 1,
		.z = 2,
		.w = 3,

	};

#define F "%.2f\n"
	printf(
		"x: "F
		"y: "F
		"z: "F
		"w: "F
		"\n",

		quat.x,
		quat.y,
		quat.z,
		quat.w
	);
#undef F

	return EXIT_SUCCESS;
}
