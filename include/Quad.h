#pragma once
#include "Gl.h"
#include "Sml.h"
#include "List.h"
#include "Assets.h"

#define quadListRead(p_list, p_id) ((struct Quad*) listRead(p_list, p_id))

struct Quad {

	float angle;
	struct SmlQuat uv;
	struct SmlVec3 pos;
	struct SmlVec2 scale;

};

struct QuadCtx {

	GLuint vao;
	GLuint vbo;
	struct List *quads;

};

void quadInitSystem(void);
struct QuadCtx* quadCreate();
void quadInit(struct QuadCtx *const ctx);
void quadDebug(struct Quad const *const quad);
void quadDraw(struct QuadCtx const *const ctx);
struct QuadCtx* quadDelete(struct QuadCtx *ctx);

extern GLuint g_quadModelVbo;
extern struct SmlVec2 g_quadOffsets[4];
extern GLuint g_quadProgramUniformLocationCam;
extern GLuint g_quadProgramUniformLocationAtlas;
extern GLuint g_quadProgramUniformLocationQuadOffsets;
