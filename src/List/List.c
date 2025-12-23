#include "UtilMacros.h"
#include <memory.h>
#include <stdlib.h>
#include <stdio.h>
#include "List.h"

struct List* listCreate(size_t const p_stride) {
	struct List *list;
	CALLOC_STRUCT(list);

	CALLOC_ARRAY_STRIDE(list->data, 1, p_stride);
	list->stride = p_stride;
	list->capacity = 1;
	list->size = 0;

	return list;
}

struct List* listDelete(struct List *const p_list) {
	free(p_list->data);
	free(p_list);
	return NULL;
}

void* listRead(struct List *p_list, size_t const p_id) {
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
		p_list->data + (p_list->size * p_list->stride),
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
		p_list->data + (p_list->size * p_list->stride),
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
