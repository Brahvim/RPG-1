#include "Itq.h"
#include <stdlib.h>

// GLuint g_itqProgramUniformLocation = 0;
GLuint g_itqProgramUniformLocationAtlas = 0;

void itqInitSystem(void) {
#define M(p_varName, p_idenStr) \
	ERRGL(g_quadProgramUniformLocation ## p_varName \
	= glGetUniformLocation(g_shaderGlIds[SHADER_ITQS], p_idenStr));
#undef M
}

struct Itq* itqCreate(struct ItqCtx *const p_ctx) {
	struct Itq quad = { 0 };
	struct SmlVec2 pos[4] = { 0 };
	struct SmlVec2 texcoords[4] = { 0 };

	listAppend(p_ctx->listInst, 1, &quad);
	listAppend(p_ctx->listVertPos, 4, &pos);
	listAppend(p_ctx->listVertTexcoords, 4, &texcoords);

	return itqListRead(p_ctx->listInst, p_ctx->listInst->size - 1);
}

struct ItqCtx* itqCtxCreate() {
	struct ItqCtx *ctx;

	callocStruct(ctx);
	ctx->listInst = listCreateStruct(Itq);
	ctx->listVertPos = listCreateStruct(SmlVec2);
	ctx->listVertTexcoords = listCreateStruct(SmlVec2);

	itqCtxInit(ctx);
	return ctx;
}

void itqCtxInit(struct ItqCtx *const p_ctx) {
	ERRGL(glGenVertexArrays(1, &p_ctx->vao));

	ERRGL(glGenBuffers(1, &p_ctx->vboInst));
	ERRGL(glGenBuffers(1, &p_ctx->vboVertPos));
	ERRGL(glGenBuffers(1, &p_ctx->vboVertTexcoords));

	ERRGL(glBindVertexArray(p_ctx->vao));

	ERRGL(glVertexAttribDivisor(0, 0));
	ERRGL(glVertexAttribDivisor(1, 0));

	ERRGL(glVertexAttribDivisor(2, 1));
	ERRGL(glVertexAttribDivisor(3, 1));
	ERRGL(glVertexAttribDivisor(4, 1));

	ERRGL(glEnableVertexAttribArray(0));
	ERRGL(glEnableVertexAttribArray(1));
	ERRGL(glEnableVertexAttribArray(2));
	ERRGL(glEnableVertexAttribArray(3));
	ERRGL(glEnableVertexAttribArray(4));

	ERRGL(glBindBuffer(GL_ARRAY_BUFFER, p_ctx->vboInst));
	ERRGL(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(struct Itq), (void*) offsetof(struct Itq, pos)));
	ERRGL(glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(struct Itq), (void*) offsetof(struct Itq, scale)));
	ERRGL(glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(struct Itq), (void*) offsetof(struct Itq, texRect)));

	ERRGL(glBindBuffer(GL_ARRAY_BUFFER, p_ctx->vboVertPos));
	ERRGL(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(struct SmlVec2), (void*) 0));

	ERRGL(glBindBuffer(GL_ARRAY_BUFFER, p_ctx->vboVertTexcoords));
	ERRGL(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(struct SmlVec2), (void*) 0));

	// "Cleanup":
	ERRGL(glBindBuffer(GL_ARRAY_BUFFER, 0));
	ERRGL(glBindVertexArray(0));
}

void itqCtxDraw(struct ItqCtx const *const p_ctx) {
	for (size_t i = 0; i < p_ctx->listInst->size; i++) {

		itqDebug(p_ctx, i);

	}

	ERRGL(glBindVertexArray(p_ctx->vao));
	ERRGL(glUseProgram(g_shaderGlIds[SHADER_ITQS]));

	ERRGL(glActiveTexture(GL_TEXTURE0));
	ERRGL(glBindTexture(GL_TEXTURE_2D, g_atlases[ATLAS_DEFAULT]->glTextureId));
	ERRGL(glUniform1i(g_itqProgramUniformLocationAtlas, GL_TEXTURE0 - GL_TEXTURE0));

	ERRGL(glBindBuffer(GL_ARRAY_BUFFER, p_ctx->vboInst));
	ERRGL(glBufferData(GL_ARRAY_BUFFER,
		p_ctx->listInst->size * p_ctx->listInst->stride,
		p_ctx->listInst->data, GL_STREAM_DRAW
	));

	ERRGL(glBindBuffer(GL_ARRAY_BUFFER, p_ctx->vboVertPos));
	ERRGL(glBufferData(GL_ARRAY_BUFFER,
		p_ctx->listVertPos->size * p_ctx->listVertPos->stride,
		p_ctx->listVertPos->data, GL_STREAM_DRAW
	));

	ERRGL(glBindBuffer(GL_ARRAY_BUFFER, p_ctx->vboVertTexcoords));
	ERRGL(glBufferData(GL_ARRAY_BUFFER,
		p_ctx->listVertTexcoords->size * p_ctx->listVertTexcoords->stride,
		p_ctx->listVertTexcoords->data, GL_STREAM_DRAW
	));

	ERRGL(glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, p_ctx->listInst->size));
}

struct ItqCtx* itqCtxDelete(struct ItqCtx *p_ctx) {
	listDelete(p_ctx->listVertTexcoords);
	listDelete(p_ctx->listVertPos);
	listDelete(p_ctx->listInst);
	free(p_ctx);
	return NULL;
}

void itqDebug(struct ItqCtx const *const p_ctx, size_t const p_id) {
	struct Itq *p_quad = itqListRead(p_ctx->listInst, p_id);
	struct SmlVec2 *p_quadVertPos = listRead(p_ctx->listVertPos, 4 * p_id);
	struct SmlVec2 *p_quadVertTexcoords = listRead(p_ctx->listVertTexcoords, 4 * p_id);

	printi(
		"	Pos:				x: `%.2ff`,		y: `%.2ff`,\n",
		p_quad->pos.x, p_quad->pos.y
	);
	printi(
		"	Scale:				x: `%.2ff`,		y: `%.2ff`,\n",
		p_quad->scale.x, p_quad->scale.y
	);
	printi(
		"	Texcoords:			x1: `%.2ff`,	y2: `%.2ff`,	w: `%.2ff`,		h: `%.2ff`.\n",
		p_quad->texRect.x, p_quad->texRect.y, p_quad->texRect.z, p_quad->texRect.w
	);

	puti("---------");
	puti("Vertices:");
	puti("---------");

	printi(
		"\t\tVert1 Pos:			x: `%.2ff`,		y: `%.2ff`,\n",
		p_quadVertPos[0].x, p_quadVertPos[0].y
	);
	printi(
		"\t\tVert2 Pos:			x: `%.2ff`,		y: `%.2ff`,\n",
		p_quadVertPos[0].x, p_quadVertPos[0].y
	);
	printi(
		"\t\tVert3 Pos:			x: `%.2ff`,		y: `%.2ff`,\n",
		p_quadVertPos[2].x, p_quadVertPos[2].y
	);
	printi(
		"\t\tVert4 Pos:			x: `%.2ff`,		y: `%.2ff`,\n",
		p_quadVertPos[3].x, p_quadVertPos[3].y
	);
	printi(
		"\t\tVert1 Texcoords:	x1: `%.2ff`,	y2: `%.2ff`.\n",
		p_quadVertTexcoords[0].x, p_quadVertTexcoords[0].y
	);
	printi(
		"\t\tVert2 Texcoords:	x1: `%.2ff`,	y2: `%.2ff`.\n",
		p_quadVertTexcoords[1].x, p_quadVertTexcoords[1].y
	);
	printi(
		"\t\tVert3 Texcoords:	x1: `%.2ff`,	y2: `%.2ff`.\n",
		p_quadVertTexcoords[2].x, p_quadVertTexcoords[2].y
	);
	printi(
		"\t\tVert4 Texcoords:	x1: `%.2ff`,	y2: `%.2ff`.\n",
		p_quadVertTexcoords[3].x, p_quadVertTexcoords[3].y
	);
}
