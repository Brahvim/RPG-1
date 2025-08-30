#include <memory.h>
#include <stdlib.h>
#include "List.h"
#include "UtilMacros.h"

struct List* listCreate(size_t const p_stride) {
	struct List *list = calloc(1, sizeof(struct List));

	list->size = 0;
	list->capacity = 1;
	list->stride = p_stride;
	list->data = calloc(1, p_stride);

	return list;
}

struct List* listDelete(struct List *const p_list) {
	free(p_list->data);
	free(p_list);
	return NULL;
}

char* listRead(struct List *p_list, size_t const p_id) {
	return &(p_list->data[p_id * p_list->stride]);
}

struct List* listDouble(struct List *const p_list, size_t const p_count) {
	size_t listCapacity = p_list->capacity;

	while (unlikely(listCapacity <= p_list->size + p_count)) {

		listCapacity *= 2;

	}

	p_list->data = realloc(p_list->data, p_list->stride * listCapacity);
	p_list->capacity = listCapacity;
	return p_list;
}

struct List* listExpand(struct List *const p_list, size_t const p_count) {
	listDouble(p_list, p_count);
	memset(
		(char*) p_list->data + (p_list->size * p_list->stride),
		0,
		(p_list->capacity - p_list->size) * p_list->stride
	);
	return p_list;
}

struct List* listWrite(struct List *const p_list, size_t const p_count, void *const p_bytes) {
	// ...Yeah, removing this makes sure there IS garbage data for crashes:
	// memset(
	// 	p_list->data + ((p_list->size + p_count) * p_list->stride),
	// 	0,
	// 	(p_list->capacity - p_list->size) * p_list->stride
	// );
	memmove(
		(char*) p_list->data + (p_list->size * p_list->stride),
		p_bytes,
		p_count * p_list->stride
	);
	p_list->size += p_count;
	return p_list;
}

struct List* listAppend(struct List *const p_list, size_t const p_count, void *const p_data) {
	listDouble(p_list, p_count);
	listWrite(p_list, p_count, p_data);
	return p_list;
}
