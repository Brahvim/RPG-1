#include "Quad.h"
#include <stdlib.h>
#include "UtilMacros.h"

#pragma region Globals.
GLuint g_quadModelVbo = 0;
struct SmlVec2 g_quadOffsets[4] = {

	{ -0.5f, -0.5f },
	{ +0.5f, -0.5f },
	{ -0.5f, +0.5f },
	{ +0.5f, +0.5f },

};
GLuint g_quadProgramUniformLocationCam = 0;
GLuint g_quadProgramUniformLocationAtlas = 0;
GLuint g_quadProgramUniformLocationQuadOffsets = 0;
#pragma endregion

void quadInitSystem(void) {
	ERRGL(glGenBuffers(1, &g_quadModelVbo));
	ERRGL(glBindBuffer(GL_ARRAY_BUFFER, g_quadModelVbo));
	// ERRGL(glBindBufferBase(GL_ARRAY_BUFFER, 0, g_quadModelVbo));
	ERRGL(glBufferData(GL_ARRAY_BUFFER, sizeof(g_quadOffsets), g_quadOffsets, GL_STATIC_DRAW));
	// ERRGL(glBindBuffer(GL_UNIFORM_BUFFER, 0)); // Do we *really* need to be cleaning up?

	ERRGL(g_quadProgramUniformLocationCam = glGetUniformLocation(g_shaderGlIds[SHADER_QUADS], "u_cam"));
	ERRGL(g_quadProgramUniformLocationAtlas = glGetUniformLocation(g_shaderGlIds[SHADER_QUADS], "u_atlas"));
	ERRGL(g_quadProgramUniformLocationQuadOffsets = glGetUniformLocation(g_shaderGlIds[SHADER_QUADS], "u_quadOffsets"));
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
	// printf("VAO %s\n", glIsBuffer(p_ctx->vao) ? "valid." : "invalid!");
	// printf("VBO %s\n", glIsBuffer(p_ctx->vbo) ? "valid." : "invalid!");

	ERRGL(glVertexAttribDivisor(0, 1));
	ERRGL(glVertexAttribDivisor(1, 1));
	ERRGL(glVertexAttribDivisor(2, 1));
	ERRGL(glVertexAttribDivisor(3, 0));
	ERRGL(glVertexAttribDivisor(4, 1));

	ERRGL(glEnableVertexAttribArray(0));
	ERRGL(glEnableVertexAttribArray(1));
	ERRGL(glEnableVertexAttribArray(2));
	ERRGL(glEnableVertexAttribArray(3));
	ERRGL(glEnableVertexAttribArray(4));

	ERRGL(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(struct Quad), (void*) offsetof(struct Quad, uv)));
	ERRGL(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(struct Quad), (void*) offsetof(struct Quad, pos)));
	ERRGL(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(struct Quad), (void*) offsetof(struct Quad, scale)));
	// There's no third attribute. It's `l_corner`! *That* gets injected-in from `g_quadModelVbo` by the OpenGL driver!
	ERRGL(glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, sizeof(struct Quad), (void*) offsetof(struct Quad, angle)));

	// ...And we define that "injection" here:
	ERRGL(glBindBuffer(GL_ARRAY_BUFFER, g_quadModelVbo));
	// printf("VBO %s\n", glIsBuffer(g_quadModelVbo) ? "valid." : "invalid!");
	ERRGL(glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(struct SmlVec2), (void*) 0));

	ERRGL(glBindBuffer(GL_ARRAY_BUFFER, 0));
	ERRGL(glBindVertexArray(0));
}

void quadDebug(struct Quad const *const p_quad) {
	printf(
	"	Angle:	`%.2f`,\n",
	p_quad->angle
	);
	printf(
		"	Scale:	x: %.2f, y: %.2f,\n",
		p_quad->scale.x, p_quad->scale.y
	);
	printf(
		"	Pos:	x: %.2f, y: %.2f, z: %.2f,\n",
		p_quad->pos.x, p_quad->pos.y
	);
	printf(
		"	UVs:	x: %.2f, y: %.2f, z: %.2f, w: %.2f.\n",
		p_quad->uv.x, p_quad->uv.y, p_quad->uv.z, p_quad->uv.w
	);
}

void quadDraw(struct QuadCtx const *const p_ctx) {
	ERRGL(glBindBuffer(GL_ARRAY_BUFFER, p_ctx->vbo));
	ERRGL(glUseProgram(g_shaderGlIds[SHADER_QUADS]));
	ERRGL(glBindVertexArray(p_ctx->vao));

	ERRGL(glActiveTexture(GL_TEXTURE0));
	ERRGL(glBindTexture(GL_TEXTURE_2D, g_atlases[ATLAS_DEFAULT]->glTextureId));
	ERRGL(glUniform1i(g_quadProgramUniformLocationAtlas, GL_TEXTURE0 - GL_TEXTURE0));

	ERRGL(glBufferData(
		GL_ARRAY_BUFFER,
		p_ctx->quads->stride * p_ctx->quads->size,
		p_ctx->quads->data,
		GL_STREAM_DRAW
	));

	ERRGL(glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, p_ctx->quads->size));

	// for (size_t i = 0; i < p_ctx->quads->size; i++)
	// 	quadDebug(quadListRead(p_ctx->quads, i));
}

struct QuadCtx* quadDelete(struct QuadCtx *p_ctx) {
	listDelete(p_ctx->quads);
	free(p_ctx);
	return NULL;
}
