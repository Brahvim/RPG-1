#include <stdlib.h>
#include <string.h>
#include "game/main.h"
#include "game/list.h"

struct GameList* gameListCreate1(size_t const p_elementBytes) {
	return gameListCreate2(p_elementBytes, 1);
}

struct GameList* gameListDestroy(struct GameList *const p_list) {
	if (p_list) {

		free(p_list->items);
		free(p_list);
		return NULL;

	}

	return p_list; // *Just* in case somebody chooses to rewrite a 50 year-old libc!
}

void* gameListCheckedGet(struct GameList const *const p_list, size_t const p_id) {
	// If floating-point indices were a thing, this address check would be useful:
	//
	// char const *const items = (char*) p_list->items;
	// void const *const element = (char*) items + p_id * p_list->elementBytes;
	// void const *const tail = (char*) items + ((p_list->size - 1) * p_list->elementBytes);
	// return (element < items || element > tail) ? NULL : element;

	return (p_id >= p_list->size)
		? NULL
		: ((char*) p_list->items) + p_id * p_list->elementBytes;
}

struct GameList* gameListAppend(struct GameList *const p_list, void *const p_item) {
	if (p_list->size >= p_list->capacity) {

		p_list->capacity += (p_list->capacity < 1); // Branchless `0`-check.
		p_list->capacity *= 2;
		REALLOC_ARRAY_ESIZE(p_list->items, p_list->capacity, p_list->elementBytes);

	}

	void *target = (char*) p_list->items + (p_list->size * p_list->elementBytes);
	memcpy(target, p_item, p_list->elementBytes);

	++p_list->size;
	return p_list;
}

struct GameList* gameListRemoveIndex(struct GameList *const p_list, size_t const p_id) {
	if (p_id >= p_list->size) {

		// ERRONEOUS();
		return p_list;

	}

	size_t const sizePostRemoval = p_list->size - p_id - 1;

	if (sizePostRemoval > 0) {

		void *const dst = (char*) p_list->items + (p_id * p_list->elementBytes);
		void const *const src = (char*) dst + p_list->elementBytes;
		memmove(dst, src, sizePostRemoval * p_list->elementBytes);

		--p_list->size;
		return p_list;

	}

	return p_list;
}

struct GameList* gameListCreate2(size_t const p_elementBytes, size_t const p_capacity) {
	struct GameList *list;
	CALLOC_ARRAY(list, 1, struct GameList);

	list->size = 0;
	list->elementBytes = p_elementBytes;
	list->capacity = p_capacity + (p_capacity < 1);
	CALLOC_ARRAY_ESIZE(list->items, list->capacity, list->elementBytes);

	return list;
}

struct GameList* gameListRemoveItem(struct GameList *const p_list, void *const p_item) {
	for (size_t i = 0; i < p_list->size; ++i) {

		void const *const current = (char*) p_list->items + (i * p_list->elementBytes);

		if (memcmp(current, p_item, p_list->elementBytes) == 0) {

			return gameListRemoveIndex(p_list, i);

		}

	}

	return p_list;
}

void* gameListCheckedGetDefaulting(struct GameList *const p_list, size_t const p_id, void *p_defaultItem) {
	void *item = gameListCheckedGet(p_list, p_id);
	return item ? item : p_defaultItem;
}

struct GameList* gameListCheckedSet(struct GameList *const p_list, size_t const p_id, void *const p_item) {
	void *const target = (char*) p_list->items + (p_id * p_list->elementBytes);
	memcpy(target, p_item, p_list->elementBytes);
	return p_list;
}

struct GameList* gameListCreate3(size_t const p_elementBytes, size_t const p_capacity, void *const p_items) {
	struct GameList *list = gameListCreate2(p_elementBytes, p_capacity);
	memcpy(list->items, p_items, p_capacity * p_elementBytes);
	list->size = p_capacity;
	return list;
}

struct GameListUnordered* gameListRemoveItemFast(struct GameListUnordered *const p_list, void *const p_item) {
	for (size_t i = 0; i < p_list->size; ++i) {

		void const *const current = (char*) p_list->items + (i * p_list->elementBytes);

		if (memcmp(current, p_item, p_list->elementBytes) == 0) {

			return gameListRemoveIndexFast(p_list, i);

		}

	}

	return p_list;
}

struct GameListUnordered* gameListRemoveIndexFast(struct GameListUnordered *const p_list, size_t const p_id) {
	if (p_id >= p_list->size) {

		// ERRONEOUS();
		return p_list;

	}

	// Replace item at `p_id` with the last one:
	void *const last = (char*) p_list->items + ((p_list->size - 1) * p_list->elementBytes);
	void *const target = (char*) p_list->items + (p_id * p_list->elementBytes);
	memcpy(target, last, p_list->elementBytes);
	--p_list->size;
	return p_list;
}

struct GameList* gameListRemoveIndexRange(struct GameList *const p_list, size_t const p_start, size_t const p_end) {
	if (!p_list || p_start >= p_list->size || p_end > p_list->size || p_start >= p_end) {

		// ERRONEOUS();
		return p_list;

	}

	size_t const range_size = p_end - p_start;
	size_t const tail_count = p_list->size - p_end;

	if (tail_count > 0) {
		void *dst = (char*) p_list->items + (p_start * p_list->elementBytes);
		void *src = (char*) p_list->items + (p_end * p_list->elementBytes);
		memmove(dst, src, tail_count * p_list->elementBytes);
	}

	p_list->size -= range_size;
	return p_list;
}

struct GameList* gameListRemoveIndexesManyFast(struct GameList *const p_list, size_t const p_idCount, size_t *const p_ids) {
	if (!p_list || !p_ids || p_idCount <= 0) {

		// ERRONEOUS();
		return p_list;

	}

	void *const itemsOriginal = p_list->items;

	for (size_t i = 0; i < p_idCount; ++i) {

		size_t const id = p_ids[i];

		if (id >= p_list->size) {

			continue;

		}

		// Manual copy like in `gameListRemoveIndex()`:
		size_t const sizePostRemoval = p_list->size - id - 1;

		if (sizePostRemoval > 0) {

			void *const dst = (char*) itemsOriginal + (id * p_list->elementBytes);
			void const *const src = (char*) dst + p_list->elementBytes;
			memmove(dst, src, sizePostRemoval * p_list->elementBytes);

		}

		p_list->size--;

		// Now adjust all *later* IDs to account for the shift:
		for (size_t j = i + 1; j < p_idCount; ++j) {

			if (p_ids[j] > id) {

				p_ids[j]--;

			}

		}

	}

	free(p_ids);
	return p_list;
}

struct GameList* gameListRemoveItemsMany(struct GameList *const p_list, size_t const p_itemCount, void const *const p_items) {
	if (!p_list || !p_items || p_itemCount <= 0 || p_list->size <= 0) {

		CALL_FOR_EACH_ARG(
			puts
			, "1"
			, "2"
			, "3"
			, "4"
			, "5"
			, "6"
			, "7"
			, "8"
			, "9"
			, "10"
			// , "11"
		);

		return p_list;

	}

	char *const itemsOriginal = (char*) p_list->items;
	size_t const elementBytes = p_list->elementBytes;
	size_t countOriginalsRemoved = 0;

	for (size_t countOriginalsRead = 0; countOriginalsRead < p_list->size; ++countOriginalsRead) {

		bool currentOriginalNeedsRemoval = false;
		void const *const currentOriginal = itemsOriginal + (countOriginalsRead * elementBytes);

		for (size_t countRemovablesRead = 0; countRemovablesRead < p_itemCount; ++countRemovablesRead) {

			void const *const target = (char*) p_items + (countRemovablesRead * elementBytes);

			if (memcmp(currentOriginal, target, elementBytes) == 0) {

				currentOriginalNeedsRemoval = true;
				break;

			}

		}

		if (!currentOriginalNeedsRemoval) {

			if (countOriginalsRemoved != countOriginalsRead) {

				void *const dest = itemsOriginal + (countOriginalsRemoved * elementBytes);
				memmove(dest, currentOriginal, elementBytes);

			}

			++countOriginalsRemoved;
		}
	}

	p_list->size = countOriginalsRemoved;
	return p_list;
}

struct GameList* gameListRemoveIndexesMany(struct GameList *const p_list, size_t const p_idCount, size_t const *const p_ids) {
	size_t *copy;
	MALLOC_ARRAY(copy, p_idCount, size_t);
	memcpy(copy, p_ids, sizeof(size_t) * p_idCount);

	gameListRemoveIndexesManyFast(p_list, p_idCount, copy);

	free(copy);
	return p_list;
}
