#pragma once

#include <assert.h>
#include <stddef.h>
#include <stdbool.h>

#include "game/main.h"

struct GameList {

	void *items;
	size_t size;
	size_t capacity;
	size_t elementBytes;

};

struct GameListUnordered {

	void *items;
	size_t size;
	size_t capacity;
	size_t elementBytes;

};

#pragma region // ABI differences checks.
#define msg __BASE_FILE__ ": `struct GameList` and `struct GameListUnordered` *differ* at ABI-level!"

static_assert(sizeof(struct GameList) == sizeof(struct GameListUnordered), msg);
static_assert(offsetof(struct GameList, size) == offsetof(struct GameListUnordered, size), msg);
static_assert(offsetof(struct GameList, items) == offsetof(struct GameListUnordered, items), msg);
static_assert(offsetof(struct GameList, capacity) == offsetof(struct GameListUnordered, capacity), msg);
static_assert(offsetof(struct GameList, elementBytes) == offsetof(struct GameListUnordered, elementBytes), msg);

#undef msg
#pragma endregion

/**
 * # JUST A LIST!
 *
 * Allocates for one object *anyway,* by the way.
 * @param elementBytes the size of one item! Use `sizeof()`, maybe!
 */
struct GameList* gameListCreate1(size_t const elementBytes);
struct GameList* gameListDestroy(struct GameList *const list);
struct GameList* gameListAppend(struct GameList *const list, void *const item);
void* gameListCheckedGet(struct GameList const *const list, size_t const index);

/**
 * # WANT PREALLOCATION?
 * @param elementBytes the size of one item! Use `sizeof()`, maybe!
 * @param capacity however many items you want to allocate. This is NEVER `0`. ***NEVER!***
 */
struct GameList* gameListCreate2(size_t const elementBytes, size_t const capacity);
struct GameList* gameListRemoveItem(struct GameList *const list, void *const item);
struct GameList* gameListRemoveIndex(struct GameList *const list, size_t const index);

/**
 * # GOT POINTER TO ITEMS?!
 * @param elementBytes the size of one item! Use `sizeof()`, maybe!
 * @param capacity however many items you want to allocate for beforehand.
 * @param items THE POINTER to an existing C-style list you want to COPY pointers from!
 *
 */
struct GameList* gameListCreate3(size_t const elementBytes, size_t const capacity, void *const items);
void* gameListCheckedGetDefaulting(struct GameList *const list, size_t const index, void *defaultItem);
struct GameList* gameListCheckedSet(struct GameList *const list, size_t const index, void *const item);
struct GameListUnordered* gameListRemoveItemFast(struct GameListUnordered *const list, void *const item);
struct GameListUnordered* gameListRemoveIndexFast(struct GameListUnordered *const list, size_t const index);
struct GameList* gameListRemoveIndexRange(struct GameList *const list, size_t const start, size_t const end);

/**
 * Deletes elements from many indices, but:
 * ## modifies `size_t *const ids`!
 */
struct GameList* gameListRemoveIndexesManyFast(struct GameList *const list, size_t const idCount, size_t *const ids);
struct GameList* gameListRemoveIndexesMany(struct GameList *const list, size_t const idCount, size_t const *const ids);
struct GameList* gameListRemoveItemsMany(struct GameList *const list, size_t const itemCount, void const *const items);
