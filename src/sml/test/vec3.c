#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "Sml.h"

char create() {
	float arr[] = { 1, 2, 3, };
	struct SmlVec3 v = smlVec3(arr);

	puts("Vector:");
	printf("%f, %f, %f.\n", v.x, v.y, v.z);
}

char add() {
	float arr[] = { 1, 2, 3, };
	struct SmlVec3 vec1 = smlVec3Val(1, 2, 3);
	puts("Adding:");
	printf("%f, %f, %f.\n", vec1.x, vec1.y, vec1.z);

	struct SmlVec3 vec2 = smlVec3(arr);
	printf("%f, %f, %f.\n", vec2.x, vec2.y, vec2.z);

	puts("Result:");
	smlVec3Add(&vec1, &vec2, &vec1);
	printf("%f, %f, %f.\n", vec1.x, vec1.y, vec1.z);
}

typedef char (*tests)(void);
int main(int const p_count, char *p_values[]) {
	tests t = add;
	t();
	return EXIT_SUCCESS;
}
