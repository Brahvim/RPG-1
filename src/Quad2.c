#include "Exit.h"
#include "Quad2.h"
#include <stdlib.h>

static struct SmlVec2 s_quad2Model[4] = {

	{.x = -0.5f, .y = -0.5f},
	{.x = +0.5f, .y = -0.5f},
	{.x = -0.5f, .y = +0.5f},
	{.x = +0.5f, .y = +0.5f},

};
static struct SmlVec2 s_quad2Texcoords[4] = {

	{.x = 0, .y = 0},
	{.x = 1, .y = 0},
	{.x = 1, .y = 1},
	{.x = 0, .y = 1},

};
// static GLuint s_quad2ProgramUniformLocation = 0;
static GLuint s_quad2ProgramUniformLocationAtlas = 0;

void quad2InitSystem(void) {
#define M(p_varName, p_idenStr) \
	ERRGL(s_quad2ProgramUniformLocation ## p_varName \
	= glGetUniformLocation(g_shaderGlIds[SHADER_QUAD2], p_idenStr))

	M(Atlas, "u_atlas");

#undef M
}

struct Quad2Ctx* quad2CtxCreate() {
	struct Quad2Ctx *ctx;
	callocStruct(ctx);

	ctx->list = listCreateStruct(Quad2);

	quad2CtxInit(ctx);
	return ctx;
}

void quad2CtxInit(struct Quad2Ctx *const p_ctx) {
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

	ERRGL(glBindBuffer(GL_ARRAY_BUFFER, p_ctx->vboVertPos));
	ERRGL(glBufferData(GL_ARRAY_BUFFER, sizeof(s_quad2Model), s_quad2Model, GL_STATIC_DRAW));
	ERRGL(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0));
	ERRGL(glEnableVertexAttribArray(0));
	ERRGL(glVertexAttribDivisor(0, 0));

	// It's not important to fill the buffers RIGHT here.
	// ...Just that they *are* bound right now; so I just... fill them here!
	// Buuuuuuuuut driver shenanigans exist! Most likely shouldn't fill HERE...!
	// It's probably best to fill them (i.e. call `glBuffer*Data()`) beforehand or something...!

	ERRGL(glBindBuffer(GL_ARRAY_BUFFER, p_ctx->vboVertTexcoords));
	ERRGL(glBufferData(GL_ARRAY_BUFFER, sizeof(s_quad2Texcoords), s_quad2Texcoords, GL_STATIC_DRAW));
	ERRGL(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0));
	ERRGL(glEnableVertexAttribArray(1));
	ERRGL(glVertexAttribDivisor(1, 0));

	ERRGL(glBindBuffer(GL_ARRAY_BUFFER, p_ctx->vboInst));
	// ERRGL(glBufferData(GL_ARRAY_BUFFER, sizeof(struct Quad2), NULL, GL_STREAM_DRAW));
	ERRGL(glBufferData(GL_ARRAY_BUFFER, listBytesSize(p_ctx->list), p_ctx->list->data, GL_STREAM_DRAW));

	ERRGL(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(struct Quad2), (void*) offsetof(struct Quad2, pos)));
	ERRGL(glEnableVertexAttribArray(2));
	ERRGL(glVertexAttribDivisor(2, 1));

	// ERRGL(glBindBuffer(GL_ARRAY_BUFFER, p_ctx->vboInst)); // Repeated. GOD KNOWS what the driver likes.
	ERRGL(glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(struct Quad2), (void*) offsetof(struct Quad2, scale)));
	ERRGL(glEnableVertexAttribArray(3));
	ERRGL(glVertexAttribDivisor(3, 1));

	// ERRGL(glBindBuffer(GL_ARRAY_BUFFER, p_ctx->vboInst)); // Repeated. GOD KNOWS what the driver likes.
	ERRGL(glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(struct Quad2), (void*) offsetof(struct Quad2, texRect)));
	ERRGL(glEnableVertexAttribArray(4));
	ERRGL(glVertexAttribDivisor(4, 1));

	// ERRGL(glBindBuffer(GL_ARRAY_BUFFER, 0));
	// ERRGL(glBindVertexArray(0));
	// *"Clean up!", they said.*
}

void quad2Debug(struct Quad2 const *const p_quad) {
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

void quad2CtxDraw(struct Quad2Ctx const *const p_ctx) {
	ERRGL(glActiveTexture(GL_TEXTURE0));
	ERRGL(glBindVertexArray(p_ctx->vao));
	ERRGL(glUseProgram(g_shaderGlIds[SHADER_QUAD2]));
	ERRGL(glBindTexture(GL_TEXTURE_2D, g_atlases[ATLAS_DEFAULT]->glTextureId));
	ERRGL(glUniform1i(s_quad2ProgramUniformLocationAtlas, GL_TEXTURE0 - GL_TEXTURE0));

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
	// printi("Quads list size in bytes: `%d`.\n", listBytesSize(p_ctx->list));
}

struct Quad2* quad2Create(struct Quad2Ctx *const p_ctx) {
	struct Quad2 quad = { 0 };
	listAppend(p_ctx->list, 1, &quad);
	return quad2ListRead(p_ctx->list, p_ctx->list->size - 1);
}

struct Quad2Ctx* quad2CtxDelete(struct Quad2Ctx *p_ctx) {
	listDelete(p_ctx->list);
	free(p_ctx);
	return NULL;
}

void quad2Texture(struct Quad2 *const p_quad, enum AtlasName const p_atlas, enum TextureName p_texture) {
	float const tx = g_textureRects[p_texture].x;
	float const ty = g_textureRects[p_texture].y;
	float const tw = g_textureRects[p_texture].w;
	float const th = g_textureRects[p_texture].h;
	float const ah = g_atlases[p_atlas]->height;
	float const aw = g_atlases[p_atlas]->width;

	// p_quad->texRect.x = tx / aw; 
	// p_quad->texRect.y = ty / ah; 
	// p_quad->texRect.z = tw / aw; 
	// p_quad->texRect.w = th / ah;
	// 
	// Done!
	//
	// ...But wait!
	// Textures in an atlas can BLEED after mipmapping!
	// ...To fix that, we limit their exact bounds by half a pixel or so, as done below...!:

	// Inversion:
	float const ahi = 1.0f / ah;
	float const awi = 1.0f / aw;

	// Offsetting:
	p_quad->texRect.x = (tx + 0.5f) * awi;
	p_quad->texRect.y = (ty + 0.5f) * ahi;
	p_quad->texRect.z = (tw - 1.0f) * awi;
	p_quad->texRect.w = (th - 1.0f) * ahi;
}
