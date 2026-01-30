#include "Sml.h"
#include "Log.h"
#include <stdio.h>
#include "Macros.h"
#include <stdlib.h>
#include <memory.h>

#define F "%.2f\n" \
printi(		\
	"x: "F	\
	"y: "F	\
	"z: "F	\
	"w: "F	\
	"\n", 	\
	quat.x, quat.y, quat.z, quat.w 	\
)

int main(int const p_count, char *p_values[]) {
	struct SmlQuat quat = { 0, 1, 2, 3 };
	return EXIT_SUCCESS;
}

#undef F
