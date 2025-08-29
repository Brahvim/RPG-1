#include "game/list.h"
#include "game/main.h"

int main(int p_argc, char const **p_argv) {
	struct GameList *list = gameListCreate1(sizeof(size_t));

	for (size_t i = 0; i < 10; ++i) {

		list = gameListAppend(list, &i);

	}

	for (size_t i = 0; i < list->size; ++i) {

		size_t const *const value = gameListCheckedGet(list, i);
		printf("`list->items[%zu]` stores `%zu`.\n", i, *value);

	}

	list = gameListDestroy(list);

	gameExit(GAME_EXIT_OKAY);
}
