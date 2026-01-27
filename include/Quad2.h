#pragma once

#include "Gl.h"
#include "Sml.h"
#include "List.h"
#include "Assets.h"

#define quad2ListRead(p_list, p_id) ((struct Quad2*) listRead(p_list, p_id))

struct Quad2 {

	struct SmlVec2 pos;
	struct SmlVec2 scale;
	struct SmlQuat texRect;

};

struct Quad2Ctx {

	GLuint vao;
	GLuint vboInst;
	GLuint vboVertPos;
	GLuint vboVertTexcoords;

	struct List *list;

};

void quad2InitSystem();
struct Quad2Ctx* quad2CtxCreate();
void quad2CtxInit(struct Quad2Ctx *const ctx);
void quad2Debug(struct Quad2 const *const quad);
void quad2CtxDraw(struct Quad2Ctx const *const ctx);
struct Quad2Ctx* quad2CtxDelete(struct Quad2Ctx *ctx);
struct Quad2* quad2Create(struct Quad2Ctx *const ctx);
void quad2Texture(struct Quad2 *const quad, enum AtlasName const atlas, enum TextureName texture);
