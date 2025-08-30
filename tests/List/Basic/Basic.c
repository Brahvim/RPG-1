#include <stdlib.h>
#include "List.h"

int main(int const p_argCount, char const **p_argValues) {
	struct List *list = listCreate(sizeof(size_t));

	listExpand(list, 100);

	for (size_t i = 0; i < 100; ++i) {

		listWrite(list, 1, &i);

	}

	listDelete(list);

	return EXIT_SUCCESS;
}
