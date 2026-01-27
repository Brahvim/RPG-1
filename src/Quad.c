#include "Quad.h"
#include "Exit.h"
#include "Macros.h"
#include <stdlib.h>

#pragma region Globals.
GLuint g_quadModelOffsetsTexture = 0;
struct SmlVec3 g_quadModelOffsets[4] = {

	{ -0.5f, -0.5f, 0.0f },
	{ +0.5f, -0.5f, 0.0f },
	{ -0.5f, +0.5f, 0.0f },
	{ +0.5f, +0.5f, 0.0f },

};
GLuint g_quadProgramUniformLocationCam = 0;
GLuint g_quadProgramUniformLocationAtlas = 0;
GLuint g_quadProgramUniformLocationOffsets = 0;
GLuint g_quadProgramUniformLocationOffsetsCount = 0;
#pragma endregion

void quadInitSystem() {
	ERRGL(glActiveTexture(GL_TEXTURE1));
	ERRGL(glGenTextures(1, &g_quadModelOffsetsTexture));
	ERRGL(glBindTexture(GL_TEXTURE_2D, g_quadModelOffsetsTexture));

	ERRGL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
	ERRGL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
	ERRGL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	ERRGL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	ERRGL(glTexImage2D(
		GL_TEXTURE_2D,
		0, GL_RGB32F,
		sizearr(g_quadModelOffsets), 1,
		0, GL_RGBA,
		GL_FLOAT,
		g_quadModelOffsets
	));

	// ...Do we *really* need to be cleaning up?

#define M(p_varName, p_idenStr) \
	ERRGL(g_quadProgramUniformLocation ## p_varName \
	= glGetUniformLocation(g_shaderGlIds[SHADER_QUADS], p_idenStr));

	M(Cam, "u_cam");
	M(Atlas, "u_atlas");
	M(Offsets, "u_offsets");
	M(OffsetsCount, "u_offsetsCount");

#undef M
}

struct QuadCtx* quadCreate() {
	struct QuadCtx *ctx;

	callocStruct(ctx);
	ctx->quads = listCreateStruct(Quad);

	quadInit(ctx);
	return ctx;
}

void quadInit(struct QuadCtx *const p_ctx) {
	ERRGL(glGenBuffers(1, &p_ctx->vbo));
	ERRGL(glGenVertexArrays(1, &p_ctx->vao));

	ERRGL(glBindVertexArray(p_ctx->vao));
	ERRGL(glBindBuffer(GL_ARRAY_BUFFER, p_ctx->vbo));

	// They're valid ONLY when bound, apparently!:
	// printi("VAO %s\n", glIsBuffer(p_ctx->vao) ? "valid." : "invalid!");
	// printi("VBO %s\n", glIsBuffer(p_ctx->vbo) ? "valid." : "invalid!");

	ERRGL(glVertexAttribDivisor(0, 1));
	ERRGL(glVertexAttribDivisor(1, 1));
	ERRGL(glVertexAttribDivisor(2, 1));
	ERRGL(glVertexAttribDivisor(3, 1));

	// ERRGL(glGetVertexAttribiv(2, GL_VERTEX_ATTRIB_ARRAY_DIVISOR, &cpuSideMem)); // You can READ these BACK!

	ERRGL(glEnableVertexAttribArray(0));
	ERRGL(glEnableVertexAttribArray(1));
	ERRGL(glEnableVertexAttribArray(2));
	ERRGL(glEnableVertexAttribArray(3));

	ERRGL(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(struct Quad), (void*) offsetof(struct Quad, uv)));
	ERRGL(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(struct Quad), (void*) offsetof(struct Quad, pos)));
	ERRGL(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(struct Quad), (void*) offsetof(struct Quad, scale)));
	ERRGL(glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(struct Quad), (void*) offsetof(struct Quad, angle)));

	ERRGL(glBindBuffer(GL_ARRAY_BUFFER, 0));
	ERRGL(glBindVertexArray(0));
}

void quadDebug(struct Quad const *const p_quad) {
	printi(
		"	Angle:	`%.2f`,\n",
		p_quad->angle
	);
	printi(
		"	Scale:	x: `%.2ff`, y: `%.2ff`,\n",
		p_quad->scale.x, p_quad->scale.y
	);
	printi(
		"	Pos:	x: `%.2ff`, y: `%.2ff`, z: `%.2ff`,\n",
		p_quad->pos.x, p_quad->pos.y
	);
	printi(
		"	UVs:	x: `%.2ff`, y: `%.2ff`, z: `%.2ff`, w: `%.2ff`.\n",
		p_quad->uv.x, p_quad->uv.y, p_quad->uv.z, p_quad->uv.w
	);
}

void quadDraw(struct QuadCtx const *const p_ctx) {
	ERRGL(glUniform1i(g_quadProgramUniformLocationOffsetsCount, 4));
	ERRGL(glBindBuffer(GL_ARRAY_BUFFER, p_ctx->vbo));
	ERRGL(glUseProgram(g_shaderGlIds[SHADER_QUADS]));
	ERRGL(glBindVertexArray(p_ctx->vao));

	ERRGL(glActiveTexture(GL_TEXTURE1));
	ERRGL(glBindTexture(GL_TEXTURE_2D, g_quadModelOffsetsTexture));
	ERRGL(glUniform1i(g_quadProgramUniformLocationOffsets, GL_TEXTURE1 - GL_TEXTURE0));

	ERRGL(glActiveTexture(GL_TEXTURE0));
	ERRGL(glBindTexture(GL_TEXTURE_2D, g_atlases[ATLAS_DEFAULT]->glTextureId));
	ERRGL(glUniform1i(g_quadProgramUniformLocationAtlas, GL_TEXTURE0 - GL_TEXTURE0));

	ERRGL(glBufferData(
		GL_ARRAY_BUFFER,
		p_ctx->quads->stride * p_ctx->quads->size,
		p_ctx->quads->data,
		GL_STREAM_DRAW
	));

	for (size_t i = 0; i < p_ctx->quads->size; i++) {

		quadDebug(quadListRead(p_ctx->quads, i));

	}

	ERRGL(glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, p_ctx->quads->size));
}

struct QuadCtx* quadDelete(struct QuadCtx *p_ctx) {
	listDelete(p_ctx->quads);
	free(p_ctx);
	return NULL;
}
