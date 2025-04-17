#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#include "ifs.h"
#include "game/quads.h"

#pragma region // Globals.
GLint g_gameQuadsFragLen = 0;
GLint g_gameQuadsVertLen = 0;
GLchar const *g_gameQuadsVertSrc = NULL;
GLchar const *g_gameQuadsFragSrc = NULL;
game_size_t g_gameQuadsCtxDefaultCapacity = 4;
char const *const g_gameQuadsFragPath = "assets/quads.vert";
char const *const g_gameQuadsVertPath = "assets/quads.frag";
#pragma endregion

void gameQuadsInit() {
	g_gameQuadsVertLen = gameShaderFromFile(&g_gameQuadsVertSrc, g_gameQuadsVertPath);
	g_gameQuadsFragLen = gameShaderFromFile(&g_gameQuadsFragSrc, g_gameQuadsFragPath);
}

struct GameQuadsCtx* gameQuadsCtxAlloc() {
	struct GameQuadsCtx *ctx = malloc(sizeof(struct GameQuadsCtx));

	memset(ctx, 0, sizeof(struct GameQuadsCtx)); // NOLINT

	ctx->shVsrc = g_gameQuadsVertSrc;
	ctx->shFsrc = g_gameQuadsFragSrc;

	ctx->shVlen = g_gameQuadsVertLen;
	ctx->shFlen = g_gameQuadsFragLen;

	ctx->maxId = g_gameQuadsCtxDefaultCapacity;
	ctx->activeCapacity = g_gameQuadsCtxDefaultCapacity;
	ctx->inactiveCapacity = g_gameQuadsCtxDefaultCapacity;
	CALLOC_ARRAY(ctx->active, ctx->activeCapacity, game_quad_t);
	CALLOC_ARRAY(ctx->inactive, ctx->inactiveCapacity, game_quad_t);

	CALLOC_ARRAY(ctx->flips, ctx->inactiveCapacity, unsigned char);
	CALLOC_ARRAY(ctx->textures, ctx->inactiveCapacity, enum GameTex);
	CALLOC_ARRAY(ctx->positions, ctx->inactiveCapacity, struct SmlVec3);
	CALLOC_ARRAY(ctx->scalesAndAngles, ctx->inactiveCapacity, struct SmlVec3);

	return ctx;
}

void gameQuadsCtxInit(struct GameQuadsCtx *const p_ctx) {
	p_ctx->shPid = ERRORGL(glCreateProgram());
	p_ctx->shVid = ERRORGL(glCreateShader(GL_VERTEX_SHADER));
	p_ctx->shFid = ERRORGL(glCreateShader(GL_FRAGMENT_SHADER));

	glShaderSource(p_ctx->shVid, 1, &(p_ctx->shVsrc), &(p_ctx->shVlen));
	glShaderSource(p_ctx->shFid, 1, &(p_ctx->shFsrc), &(p_ctx->shFlen));

	glCompileShader(p_ctx->shVid);
	glCompileShader(p_ctx->shFid);

	glAttachShader(p_ctx->shPid, p_ctx->shVid);
	glAttachShader(p_ctx->shPid, p_ctx->shFid);

	glLinkProgram(p_ctx->shPid);

	GLchar slogBuf[16384];
	GLsizei slogLen = 16384, slogStrlen;

	memset(slogBuf, 0, slogLen); // NOLINT
	ERRORGL(glGetShaderInfoLog(p_ctx->shVid, 16384, &slogLen, slogBuf));
	printf("Quads vertex shader log: %s.\n", slogBuf);

	memset(slogBuf, 0, slogLen); // NOLINT
	ERRORGL(glGetShaderInfoLog(p_ctx->shFid, 16384, &slogLen, slogBuf));
	printf("Quads fragment shader log: %s.\n", slogBuf);

	memset(slogBuf, 0, slogLen); // NOLINT
	ERRORGL(glGetProgramInfoLog(p_ctx->shPid, 16384, &slogLen, slogBuf));
	printf("Quads program log: %s.\n", slogBuf);

	ERRORGL(glBindVertexArray(p_ctx->vao));
	ERRORGL(glUniform1i(glGetUniformLocation(p_ctx->shPid, "u_atlas"), 0));
	ERRORGL(glUniform2fv(glGetUniformLocation(p_ctx->shPid, "u_vertexOffs"), 0, 0));

	ERRORGL(glActiveTexture(GL_TEXTURE0));
	enum GameTex const tex = GAME_TEX_NULL;
	ERRORGL(glBindTexture(GL_TEXTURE_2D, g_gameTexesGl[tex]));

	ERRORGL(glEnableVertexAttribArray(0));
	ERRORGL(glEnableVertexAttribArray(1));
	ERRORGL(glBufferData(GL_ARRAY_BUFFER, p_ctx->vboDataCapacity, p_ctx->vboData, p_ctx->vboUsage));
	ERRORGL(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0));
	ERRORGL(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*) (2 * sizeof(GLfloat))));
}

void gameQuadsCtxDraw(struct GameQuadsCtx const *const p_ctx) {
	struct GameQuadsVbo *vboData = p_ctx->vboData;
	unsigned char const *const flips = p_ctx->flips;
	game_size_t *vboDataCapacity = &p_ctx->vboDataCapacity;
	enum GameTex const *const textures = p_ctx->textures;
	struct SmlVec3 const *const positions = p_ctx->positions;
	struct SmlVec3 const *const scalesAndAngles = p_ctx->scalesAndAngles;

	foru(size_t i = 0, i < vboDataCapacity, ++i) {

		switch (flips[i]) {

			case GAME_TEX_FLIP_NONE: {

				vboData->uv[0].x = 0;
				vboData->uv[0].y = 0;

				vboData->uv[1].x = 0;
				vboData->uv[1].y = 0;

				vboData->uv[2].x = 0;
				vboData->uv[2].y = 0;

				vboData->uv[3].x = 0;
				vboData->uv[3].y = 0;

			} break;

			case GAME_TEX_FLIP_BOTH: {

				vboData->uv[0].x = 0;
				vboData->uv[0].y = 0;

				vboData->uv[1].x = 0;
				vboData->uv[1].y = 0;

				vboData->uv[2].x = 0;
				vboData->uv[2].y = 0;

				vboData->uv[3].x = 0;
				vboData->uv[3].y = 0;

			} break;

			case GAME_TEX_FLIP_VERTICAL: {

				vboData->uv[0].x = 0;
				vboData->uv[0].y = 0;

				vboData->uv[1].x = 0;
				vboData->uv[1].y = 0;

				vboData->uv[2].x = 0;
				vboData->uv[2].y = 0;

				vboData->uv[3].x = 0;
				vboData->uv[3].y = 0;

			} break;

			case GAME_TEX_FLIP_HORIZONTAL: {

				vboData->uv[0].x = 0;
				vboData->uv[0].y = 0;

				vboData->uv[1].x = 0;
				vboData->uv[1].y = 0;

				vboData->uv[2].x = 0;
				vboData->uv[2].y = 0;

				vboData->uv[3].x = 0;
				vboData->uv[3].y = 0;

			} break;

		}

	}

	foru(size_t i = 0, i < vboDataCapacity, ++i) {



	}

	foru(size_t i = 0, i < vboDataCapacity, ++i) {



	}

	foru(size_t i = 0, i < vboDataCapacity, ++i) {



	}

	glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, p_ctx->activeLength);
}

void gameQuadsDestroy(struct GameQuadsCtx *const p_ctx, game_quad_t const *p_quads, game_size_t const p_count) {

}

game_quad_t* gameQuadsCreate(struct GameQuadsCtx *const p_ctx, game_quad_t *const p_out, game_size_t const p_many) {
	ifl(p_ctx->inactiveLength >= p_many) {

		game_size_t const inactive = p_ctx->inactiveLength - 1;
		p_ctx->inactiveLength -= p_many;

		foru(size_t i = 0, i < p_many, ++i) {

			p_out[i] = p_ctx->inactive[inactive - i];

		}


	} else {

		game_size_t const oldCount = p_ctx->activeLength;
		p_ctx->activeLength += p_many;
		p_ctx->activeCapacity *= 2;

		// NOLINTBEGIN
		REALLOC_ARRAY(p_ctx->active, p_ctx->activeCapacity, game_quad_t); memset(p_ctx->active, 0, p_ctx->activeLength - oldCount);
		REALLOC_ARRAY(p_ctx->active, p_ctx->activeCapacity, game_quad_t); memset(p_ctx->active, 0, p_ctx->activeLength - oldCount);
		REALLOC_ARRAY(p_ctx->flips, p_ctx->activeCapacity, unsigned char); memset(p_ctx->flips, 0, p_ctx->activeLength - oldCount);
		REALLOC_ARRAY(p_ctx->textures, p_ctx->activeCapacity, enum GameTex); memset(p_ctx->textures, 0, p_ctx->activeLength - oldCount);
		REALLOC_ARRAY(p_ctx->positions, p_ctx->activeCapacity, struct SmlVec3); memset(p_ctx->positions, 0, p_ctx->activeLength - oldCount);
		REALLOC_ARRAY(p_ctx->scalesAndAngles, p_ctx->activeCapacity, struct SmlVec3); memset(p_ctx->scalesAndAngles, 0, p_ctx->activeLength - oldCount);
		// NOLINTEND

		foru(size_t i = 0, i < p_many, ++i) {

			p_out[i] = p_ctx->maxId++;

		}

	}

	return p_out;
}
