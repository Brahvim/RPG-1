#pragma once
#include <stddef.h>

#define listCreateType(p_type) 			listCreate(sizeof(p_type))
#define listCreateStruct(p_struct) 		listCreateType(struct p_struct)

#define listBytesSize(p_listPtr) 		((p_listPtr)->stride * (p_listPtr)->size)
#define listBytesCapacity(p_listPtr) 	((p_listPtr)->stride * (p_listPtr)->capacity)

#define listDebug(p_listVar) 			listDebugImpl(p_listVar, "`" STR(p_listVar) "`")

struct List {

	size_t size;
	size_t stride;
	size_t capacity;
	unsigned char *data;

};

void listDebugImpl(struct List *list, char const *name);

/**
 * Uses `calloc*()`-and-co. macros. `List::capacity` is `1` for non-zero mult.
 * Make sure never to zero-out `List::capacity`. I know you'll not...! <:)!
 */
struct List* listCreate(size_t const stride);

/**
 * `free()`s-up `struct List`, returns `NULL` hoping you write `list = listDelete()`.
 */
struct List* listDelete(struct List *const list);

/**
 * ...Think `list[id]`. This function uses `int stride` of `struct List`!
 * MAKE SURE TO CAST YOUR RESULTS TO YOUR TYPE! Consider making a macro:
 * `#define typeListRead(list, id) ((struct Type*) listRead(list, id))`
 */
void* listRead(struct List *list, size_t const id);

/**
 * Allocates into `List::data` for ONE element according to `List::stride`, ...which *you* provide!
 */
struct List* listInit(struct List *const list, size_t const stride);

/**
 * Doubles the size of the list using `realloc()` till it hits `count`.
 * ...Unless it has enough space.
 */
struct List* listDouble(struct List *const list, size_t const count);

/**
 * Doubles the size of the list till it hits `count` (unless it has enough space!).
 * (If `listDouble()` has changed, that explanation up there is now invalid!)
 * *This* function (`listExpand()`) zeroes the newly-allocated memory.
 */
struct List* listExpand(struct List *const list, size_t const count);

/**
 * Copies elements to the list starting at the list's end.
 */
struct List* listWrite(struct List *const list, size_t const count, void *const bytes);

/**
 * Copies elements to the list's end...!
 */
struct List* listAppend(struct List *const list, size_t const count, void *const data);
