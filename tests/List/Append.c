#include "List.h"
#include <stdlib.h>

int main(int const p_argCount, char const **p_argValues) {
    struct List *list = listCreate(sizeof(size_t));

    for (size_t i = 0; i < 100; ++i) {

        listAppend(list, 1, &i);

    }

    listDelete(list);

    return EXIT_SUCCESS;
}
