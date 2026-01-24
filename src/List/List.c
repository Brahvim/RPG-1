#include "UtilMacros.h"
#include <memory.h>
#include <stdlib.h>
#include <stdio.h>
#include "List.h"

/**
 * Uses `calloc*()`-and-co. macros. `List::capacity` is `1` for non-zero mult.
 * Make sure never to zero-out `List::capacity`. I know you'll not...! <:)!
 */
struct List* listCreate(size_t const p_stride) {
	struct List *list;
	callocStruct(list);

	callocArrayStride(list->data, 1, p_stride);
	list->stride = p_stride;
	list->capacity = 1;
	list->size = 0;

	return list;
}

/** `free()`s-up `struct List`, returns `NULL` hoping you write `list = listDelete()`. */
struct List* listDelete(struct List *const p_list) {
	free(p_list->data);
	free(p_list);
	return NULL;
}

/**
 * ...Think `list[p_id]`. This function uses `int stride` of `struct List`!
 * MAKE SURE TO CAST YOUR RESULT TO YOUR TYPE! Consider making such a macro:
 * `#define typeListRead(p_list, p_id) ((struct Type*) listRead(p_list, p_id))`
*/
void* listRead(struct List *p_list, size_t const p_id) {
	return &(p_list->data[p_id * p_list->stride]);
}

/**
 * Doubles the size of the list using `realloc()` till it hits `p_count`.
 * ...Unless it has enough space.
 */
struct List* listDouble(struct List *const p_list, size_t const p_count) {
	size_t listCapacity = p_list->capacity;

	while (unlikely(listCapacity <= p_list->size + p_count)) {

		listCapacity *= 2;

	}

	p_list->data = realloc(p_list->data, p_list->stride * listCapacity);
	p_list->capacity = listCapacity;
	return p_list;
}

/**
 * Doubles the size of the list till it hits `p_count` (unless it has enough space!).
 * (If `listDouble()` has changed, that explanation up there is now invalid!)
 * *This* function (`listExpand()`) zeroes the newly-allocated memory.
 */
struct List* listExpand(struct List *const p_list, size_t const p_count) {
	listDouble(p_list, p_count);
	memset(
		p_list->data + (p_list->size * p_list->stride),
		0,
		(p_list->capacity - p_list->size) * p_list->stride
	);
	return p_list;
}

/** Copies elements to the list from the very beginning...! */
struct List* listWrite(struct List *const p_list, size_t const p_count, void *const p_bytes) {
	// ...Yeah, removing this makes sure there IS garbage data for crashes:
	// memset(
	// 	p_list->data + ((p_list->size + p_count) * p_list->stride),
	// 	0,
	// 	(p_list->capacity - p_list->size) * p_list->stride
	// );
	memmove(
		p_list->data + (p_list->size * p_list->stride),
		p_bytes,
		p_count * p_list->stride
	);
	p_list->size += p_count;
	return p_list;
}

/** Copies elements to the list's end...! */
struct List* listAppend(struct List *const p_list, size_t const p_count, void *const p_data) {
	listDouble(p_list, p_count);
	listWrite(p_list, p_count, p_data);
	return p_list;
}
