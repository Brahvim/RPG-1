#pragma once
#include <stddef.h>

struct List {

	char *data;
	size_t size;
	size_t stride;
	size_t capacity;

};

struct List* listCreate(size_t const stride);
struct List* listDelete(struct List *const list);
char* listRead(struct List *list, size_t const id);
struct List* listExpand(struct List *const list, size_t const count);
struct List* listWrite(struct List *const list, size_t const count, void *const bytes);
struct List* listAppend(struct List *const list, size_t const count, void *const data);
