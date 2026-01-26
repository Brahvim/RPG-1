/* "Instanced, Textured-Quads" */
#pragma once

#include "Gl.h"
#include "Sml.h"
#include "List.h"
#include "Assets.h"

#define itqListRead(p_list, p_id) ((struct Itq*) listRead(p_list, p_id))

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

	struct List *list;

};

extern struct SmlVec2 g_itqModel[4];
extern struct SmlVec2 g_itqTexcoords[4];
// extern GLuint g_itqProgramUniformLocation;
extern GLuint g_itqProgramUniformLocationAtlas;

void itqInitSystem();
struct ItqCtx* itqCtxCreate();
void itqCtxInit(struct ItqCtx *const ctx);
void itqDebug(struct Itq const *const quad);
struct Itq* itqCreate(struct ItqCtx *const ctx);
void itqCtxDraw(struct ItqCtx const *const ctx);
struct ItqCtx* itqCtxDelete(struct ItqCtx *ctx);
void itqTexture(struct Itq *const quad, enum AtlasName const atlas, enum TextureName const tex);
