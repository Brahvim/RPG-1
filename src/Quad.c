#include "Exit.h"
#include "Quad.h"
#include <stdlib.h>

static struct SmlVec2 s_quadModel[4] = {

	{.x = -0.5f, .y = -0.5f},
	{.x = +0.5f, .y = -0.5f},
	{.x = -0.5f, .y = +0.5f},
	{.x = +0.5f, .y = +0.5f},

};
static struct SmlVec2 s_quadTexcoords[4] = {

	{.x = 0, .y = 0},
	{.x = 1, .y = 0},
	{.x = 0, .y = 1},
	{.x = 1, .y = 1},

};
// static GLuint s_quadProgramUniformLocation = 0;
static GLuint s_quadProgramUniformLocationAtlas = 0;

void quadInitSystem(void) {
#define M(p_varName, p_idenStr) \
	ERRGL(s_quadProgramUniformLocation ## p_varName \
	= glGetUniformLocation(g_shaderGlIds[SHADER_QUADS], p_idenStr))

	M(Atlas, "u_atlas");

#undef M
}

struct QuadCtx* quadCtxCreate() {
	struct QuadCtx *ctx;
	callocStruct(ctx);

	ctx->list = listCreateStruct(Quad);

	quadCtxInit(ctx);
	return ctx;
}

void quadCtxInit(struct QuadCtx *const p_ctx) {
	ERRGL(glGenVertexArrays(1, &p_ctx->vao));
	ERRGL(glBindVertexArray(p_ctx->vao));
	{ // VBO allocs.
#define N 3
		GLuint bufs[N];
		ERRGL(glGenBuffers(N, bufs));

		p_ctx->vboInst = 			/**/ bufs[0];
		p_ctx->vboVertPos = 		/**/ bufs[1];
		p_ctx->vboVertTexcoords = 	/**/ bufs[2];
#undef N
	}
	GLuint attrib;

	attrib = 0; // `a0_vPos`.
#pragma region
	ERRGL(glBindBuffer(GL_ARRAY_BUFFER, p_ctx->vboVertPos));
	ERRGL(glBufferData(GL_ARRAY_BUFFER, sizeof(s_quadModel), s_quadModel, GL_STATIC_DRAW));
	ERRGL(glVertexAttribPointer(attrib, 2, GL_FLOAT, GL_FALSE, 0, 0));
	ERRGL(glEnableVertexAttribArray(attrib));
	ERRGL(glVertexAttribDivisor(attrib, 0));

	// It's not important to fill the buffers RIGHT here.
	// ...Just that they *are* bound right now; so I just... fill them here!
	// Buuuuuuuuut driver shenanigans exist! Most likely shouldn't fill HERE...!
	// It's probably best to fill them (i.e. call `glBuffer*Data()`) beforehand or something...!
#pragma endregion

	attrib = 1; // `a1_vTexcoords`.
#pragma region
	ERRGL(glBindBuffer(GL_ARRAY_BUFFER, p_ctx->vboVertTexcoords));
	ERRGL(glBufferData(GL_ARRAY_BUFFER, sizeof(s_quadTexcoords), s_quadTexcoords, GL_STATIC_DRAW));
	ERRGL(glVertexAttribPointer(attrib, 2, GL_FLOAT, GL_FALSE, 0, 0));
	ERRGL(glEnableVertexAttribArray(attrib));
	ERRGL(glVertexAttribDivisor(attrib, 0));

	ERRGL(glBindBuffer(GL_ARRAY_BUFFER, p_ctx->vboInst));
	// ERRGL(glBufferData(GL_ARRAY_BUFFER, sizeof(struct Quad), NULL, GL_STREAM_DRAW));
	ERRGL(glBufferData(GL_ARRAY_BUFFER, listBytesSize(p_ctx->list), p_ctx->list->data, GL_STREAM_DRAW));
#pragma endregion

	attrib = 2; // `a2_iPos`.
#pragma region
	ERRGL(glVertexAttribPointer(attrib, 2, GL_FLOAT, GL_FALSE, sizeof(struct Quad), (void*) offsetof(struct Quad, pos)));
	ERRGL(glEnableVertexAttribArray(attrib));
	ERRGL(glVertexAttribDivisor(attrib, 1));
#pragma endregion

	attrib = 3; // `a3_iTint`.
#pragma region
	// ERRGL(glBindBuffer(GL_ARRAY_BUFFER, p_ctx->vboInst)); // Repeated. GOD KNOWS what the driver likes.
	ERRGL(glVertexAttribPointer(attrib, 4, GL_FLOAT, GL_FALSE, sizeof(struct Quad), (void*) offsetof(struct Quad, tintRgba)));
	ERRGL(glEnableVertexAttribArray(attrib));
	ERRGL(glVertexAttribDivisor(attrib, 1));
#pragma endregion

	attrib = 4; // `a4_iScale`.
#pragma region
	// ERRGL(glBindBuffer(GL_ARRAY_BUFFER, p_ctx->vboInst)); // Repeated. GOD KNOWS what the driver likes.
	ERRGL(glVertexAttribPointer(attrib, 2, GL_FLOAT, GL_FALSE, sizeof(struct Quad), (void*) offsetof(struct Quad, scale)));
	ERRGL(glEnableVertexAttribArray(attrib));
	ERRGL(glVertexAttribDivisor(attrib, 1));
#pragma endregion

	attrib = 5; // `a5_iTexcoords`.
#pragma region
	// ERRGL(glBindBuffer(GL_ARRAY_BUFFER, p_ctx->vboInst)); // Repeated. GOD KNOWS what the driver likes.
	ERRGL(glVertexAttribPointer(attrib, 4, GL_FLOAT, GL_FALSE, sizeof(struct Quad), (void*) offsetof(struct Quad, texRect)));
	ERRGL(glEnableVertexAttribArray(attrib));
	ERRGL(glVertexAttribDivisor(attrib, 1));
#pragma endregion

	// ERRGL(glBindBuffer(GL_ARRAY_BUFFER, 0));
	// ERRGL(glBindVertexArray(0));
	// *"Clean up!", they said.*
}

void quadDebug(struct Quad const *const p_quad) {
	printi(
		"	Pos:		x: `%.2ff`,  y: `%.2ff`,\n",
		p_quad->pos.x, p_quad->pos.y
	);
	printi(
		"	Scale:		x: `%.2ff`,  y: `%.2ff`,\n",
		p_quad->scale.x, p_quad->scale.y
	);
	printi(
		"	Texcoords:	x1: `%.2ff`, y2: `%.2ff`, w: `%.2ff`, h: `%.2ff`.\n",
		p_quad->texRect.x, p_quad->texRect.y, p_quad->texRect.z, p_quad->texRect.w
	);
}

void quadCtxDraw(struct QuadCtx const *const p_ctx) {
	ERRGL(glActiveTexture(GL_TEXTURE0));
	ERRGL(glBindVertexArray(p_ctx->vao));
	ERRGL(glUseProgram(g_shaderGlIds[SHADER_QUADS]));
	ERRGL(glBindTexture(GL_TEXTURE_2D, g_atlases[ATLAS_DEFAULT]->glTextureId));
	ERRGL(glUniform1i(s_quadProgramUniformLocationAtlas, GL_TEXTURE0 - GL_TEXTURE0));

	ERRGL(glBindBuffer(GL_ARRAY_BUFFER, p_ctx->vboInst));
	// "Orphan" previous buffer. Let it "be GCd" for a new one:
	ERRGL(glBufferData(
		GL_ARRAY_BUFFER,
		listBytesSize(p_ctx->list),
		NULL,
		GL_STREAM_DRAW
	));
	ERRGL(glBufferData(
		GL_ARRAY_BUFFER,
		listBytesSize(p_ctx->list),
		p_ctx->list->data,
		GL_STREAM_DRAW
	));

	ERRGL(glEnable(GL_BLEND));
	ERRGL(glFrontFace(GL_CCW));
	ERRGL(glDisable(GL_CULL_FACE));
	ERRGL(glDisable(GL_DEPTH_TEST));
	ERRGL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	ERRGL(glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, p_ctx->list->size));
}

struct Quad* quadCreate(struct QuadCtx *const p_ctx) {
	struct Quad quad = { 0 };
	listAppend(p_ctx->list, 1, &quad);
	return quadListRead(p_ctx->list, p_ctx->list->size - 1);
}

struct QuadCtx* quadCtxDelete(struct QuadCtx *p_ctx) {
	listDelete(p_ctx->list);
	free(p_ctx);
	return NULL;
}

void quadTexture(struct Quad *const p_quad, enum AtlasName const p_atlas, enum TextureName p_texture) {
	struct Atlas *atlas = g_atlases[p_atlas];
	float const tx = atlas->rects[p_texture].x;
	float const ty = atlas->rects[p_texture].y;
	float const tw = atlas->rects[p_texture].w;
	float const th = atlas->rects[p_texture].h;
	float const ah = atlas->height;
	float const aw = atlas->width;

	// p_quad->texRect.x = tx / aw; // Texture AABB `x`,
	// p_quad->texRect.y = ty / ah; // Texture AABB `y`,
	// p_quad->texRect.z = tw / aw; // Texture AABB `w`,
	// p_quad->texRect.w = th / ah; // Texture AABB `h`.
	//
	// Done!
	//
	// ...But wait!
	// Textures in an atlas can BLEED into each other after mipmapping!
	// ...To fix that, we limit their exact bounds by half a pixel or so, as done below...!:

	// Inversion:
	float const ahi = 1.0f / ah;
	float const awi = 1.0f / aw;

	// Offsetting:
	p_quad->texRect.x = (tx + 0.5f) * awi; // Texture AABB `x`,
	p_quad->texRect.y = (ty + 0.5f) * ahi; // Texture AABB `y`,
	p_quad->texRect.z = (tw - 1.0f) * awi; // Texture AABB `w`,
	p_quad->texRect.w = (th - 1.0f) * ahi; // Texture AABB `h`.
}
