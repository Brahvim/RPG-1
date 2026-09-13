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

	struct List(struct Quad) *list;

};

void quadSystemInit();
struct QuadCtx* quadCtxCreate();
struct Quad* quadInit(struct Quad *const quad);
struct QuadCtx* quadCtxDelete(struct QuadCtx *ctx);
struct Quad* quadDebug(struct Quad const *const quad);
struct QuadCtx* quadCtxInit(struct QuadCtx *const ctx);
struct QuadCtx* quadCtxDraw(struct QuadCtx const *const ctx);
struct QuadCtx* quadCtxDrawRange(struct QuadCtx const *const ctx, size_t const start, size_t const count);

#define quadPtr(...) (&quadVal(__VA_ARGS__))
#define quadDefPtr(...) (&quadDef(__VA_ARGS__))
#define quadVal(...) ((struct Quad) { __VA_ARGS__ })
#define quadCtxNew(p_ctx) listAppend(p_ctx, quadDef())
size_t quadCreate(struct QuadCtx *const ctx, size_t const count);
#define quadDef(...) ((struct Quad) { .scale = { 1, 1 }, .tintRgba = { 0, 0, 0, 1 }, __VA_ARGS__ })

struct Quad* quadTexture(struct Quad *const quad, enum AtlasName const atlas, enum TextureName texture);

