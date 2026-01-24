#pragma once
#include <stddef.h>
#define listCreateType(p_type) listCreate(sizeof(p_type))
#define listCreateStruct(p_struct) listCreateType(struct p_struct)

struct List {

	size_t size;
	size_t stride;
	size_t capacity;
	unsigned char *data;

};

struct List* listCreate(size_t const stride);
struct List* listDelete(struct List *const list);
void* listRead(struct List *list, size_t const id);
struct List* listExpand(struct List *const list, size_t const count);
struct List* listWrite(struct List *const list, size_t const count, void *const bytes);
struct List* listAppend(struct List *const list, size_t const count, void *const data);
