#include <assert.h>

#include "game/list.h"
#include "game/main.h"

int main(int argc, char const **argv) {
	// Create list that goes from `0` to `19`:
	struct GameList *list = gameListCreate2(sizeof(size_t), 4);

	for (size_t i = 0; i < 20; ++i) {

		list = gameListAppend(list, &i);

	}

	// Remove a few elements via value:
	size_t const removeThese[] = { 5, 10, 15 };
	list = gameListRemoveItemsMany(list, 3, removeThese);

	// Check remaining thingies:
	printf("After value-based removal:\n");
	for (size_t i = 0; i < list->size; ++i) {

		size_t const *const val = gameListCheckedGet(list, i);
		printf("[%zu] = %zu\n", i, *val);

	}

	list = gameListRemoveIndexesMany(list, 3, (size_t*) { 0, 3, 5 });

	// Print again:
	printf("\nAfter index-based removal:\n");
	for (size_t i = 0; i < list->size; ++i) {

		size_t *val = gameListCheckedGet(list, i);
		printf("[%zu] = %zu\n", i, *val);

	}

	// Try remove a value that ain't there:
	size_t const invalid = 100;
	list = gameListRemoveItem(list, &invalid); // Should do nothing!

	// Append more during partial traversal (CRAP):
	for (size_t i = 0; i < 5; ++i) {

		size_t const value = 100 + i;
		list = gameListAppend(list, &value);

	}

	printf("\nAfter appending extras:\n");
	for (size_t i = 0; i < list->size; ++i) {

		size_t *const val = gameListCheckedGet(list, i);
		printf("[%zu] = %zu\n", i, *val);

	}

	// Destroy:
	list = gameListDestroy(list);
	assert(list == NULL);

	gameExit(GAME_EXIT_OKAY);
}
