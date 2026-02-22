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
struct Quad* quadInit(struct Quad *const quad);
struct QuadCtx* quadCtxDelete(struct QuadCtx *ctx);
struct Quad* quadDebug(struct Quad const *const quad);
struct QuadCtx* quadCtxInit(struct QuadCtx *const ctx);
struct QuadCtx* quadCtxDraw(struct QuadCtx const *const ctx);
struct QuadCtx* quadCtxDrawRange(struct QuadCtx const *const ctx, size_t const start, size_t const count);

#define quadDefPtr() (&quadDef())
#define quadPtr(...) (&quadVal(__VA_ARGS__))
#define quadVal(...) ((struct Quad) { __VA_ARGS__ })
#define quadCtxNew(p_ctx) quadCtxAppend(p_ctx, quadDef())
size_t quadCreate(struct QuadCtx *const ctx, size_t const count);
#define quadDef(...) ((struct Quad) { .scale = { 1, 1 }, __VA_ARGS__ })

#define quadCtxTail(p_ctx) quadListTail(p_ctx->list)
#define quadListTail(p_list) quadListRead(p_list, p_list->size - 1)

#define quadCtxRead(p_ctx, p_id) quadListRead(p_ctx->list, p_id)
#define quadListRead(p_list, p_id) ((struct Quad*) listRead(p_list, p_id))

#define quadCtxSet(p_ctx, p_id, p_quad) quadListSet(p_ctx->list, p_id, p_quad)
#define quadListSet(p_list, p_id, p_quad) *(((struct Quad*) p_list->data) + p_id) = (p_quad)

struct Quad* quadTexture(struct Quad *const quad, enum AtlasName const atlas, enum TextureName texture);

#define quadCtxAppend(p_ctx, p_quad) quadListAppend(p_ctx->list, p_quad)
#define quadListAppend(p_list, p_quad) (*(((struct Quad*) p_list->data) + p_list->size++) = (p_quad))
