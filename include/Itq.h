#pragma once
#include "Gl.h"
#include "Sml.h"
#include "List.h"
#include "Assets.h"

#define itqListRead(list, id) ((struct Itq*) listRead(list, id))
// "Instanced Textured-Quads".

struct Itq {

	struct SmlVec2 pos;
	struct SmlVec2 scale;
	struct SmlQuat texRect;

};

struct ItqCtx {

	GLuint vao;
	GLuint vboInst;
	GLuint vboVertPos;
	GLuint vboVertTexcoords;

	struct List *listInst;
	struct List *listVertPos;
	struct List *listVertTexcoords;
	// ...Could use one 6-`float` list!

};

GLuint g_itqProgramUniformLocationAtlas;

void itqInitSystem();
struct ItqCtx* itqCtxCreate();
void itqCtxInit(struct ItqCtx *const ctx);
struct Itq* itqCreate(struct ItqCtx *const ctx);
void itqCtxDraw(struct ItqCtx const *const ctx);
struct ItqCtx* itqCtxDelete(struct ItqCtx *ctx);
void itqDebug(struct ItqCtx const *const ctx, size_t const id);
