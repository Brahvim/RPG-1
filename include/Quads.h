#pragma once
#include "Gl.h"
#include "Sml.h"
#include "List.h"
#include "Assets.h"

#define quadReadList(p_list, p_id) ((struct Quad*) listRead(p_list, p_id))

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

void quadInit(void);
extern GLuint g_quadOffsetsVbo;
extern struct SmlVec2 g_quadOffsets[4];
