#pragma once

#include "Gl.h"
#include "Sml.h"
#include "List.h"
#include "Assets.h"

struct Quad {

	struct SmlVec3 pos;
	struct SmlVec3 scale;
	struct SmlVec3 rotate;
	struct SmlQuat texRect;
	struct SmlQuat tintRgba;

};

struct QuadCtx {

	GLuint vao;
	GLuint vboInst;
	GLuint vboVertPos;
	GLuint vboVertTexcoords;

	struct List *list;

};

void quadSystemInit();
struct QuadCtx* quadCtxCreate();
void quadInit(struct Quad *const quad);
void quadCtxInit(struct QuadCtx *const ctx);
void quadDebug(struct Quad const *const quad);
void quadCtxDraw(struct QuadCtx const *const ctx);
struct QuadCtx* quadCtxDelete(struct QuadCtx *ctx);

#define quadVal(...) ((struct Quad) { __VA_ARGS__ })
#define quadPtr(...) ((struct Quad*) { __VA_ARGS__ })
#define quadDef() ((struct Quad) { .scale = { 1, 1 } })
#define quadCtxNew(p_ctx) quadCtxAppend(p_ctx, quadDef())
size_t quadCreate(struct QuadCtx *const ctx, size_t const count);

#define quadCtxTail(p_ctx) quadListTail(p_ctx->list)
#define quadListTail(p_list) quadListRead(p_list, p_list->size - 1)

#define quadCtxRead(p_ctx, p_id) quadListRead(p_ctx->list, p_id)
#define quadListRead(p_list, p_id) ((struct Quad*) listRead(p_list, p_id))

#define quadCtxSet(p_ctx, p_id, p_quad) quadListSet(p_ctx->list, p_id, p_quad)
#define quadListSet(p_list, p_id, p_quad) *(((struct Quad*) p_list->data) + p_id) = (p_quad)

void quadTexture(struct Quad *const quad, enum AtlasName const atlas, enum TextureName texture);

#define quadCtxAppend(p_ctx, p_quad) quadListAppend(p_ctx->list, p_quad)
#define quadListAppend(p_list, p_quad) *(((struct Quad*) p_list->data) + p_list->size++) = (p_quad)
