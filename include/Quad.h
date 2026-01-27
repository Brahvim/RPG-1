#pragma once

#include "Gl.h"
#include "Sml.h"
#include "List.h"
#include "Assets.h"

struct Quad {

	struct SmlVec2 pos;
	struct SmlVec2 scale;
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

void quadInitSystem();
struct QuadCtx* quadCtxCreate();
void quadCtxInit(struct QuadCtx *const ctx);
void quadDebug(struct Quad const *const quad);
void quadCtxDraw(struct QuadCtx const *const ctx);
struct QuadCtx* quadCtxDelete(struct QuadCtx *ctx);
struct Quad* quadCreate(struct QuadCtx *const ctx);
#define quadListRead(p_list, p_id) ((struct Quad*) listRead(p_list, p_id))
void quadTexture(struct Quad *const quad, enum AtlasName const atlas, enum TextureName texture);
