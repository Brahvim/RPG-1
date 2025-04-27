#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#include "ifs.h"
#include "game/cam.h"
#include "game/quads.h"

#pragma region // Globals.
GLint g_gameQuadsFragLen = 0;
GLint g_gameQuadsVertLen = 0;
GLchar const *g_gameQuadsVertSrc = NULL;
GLchar const *g_gameQuadsFragSrc = NULL;

struct SmlVec2 g_gameQuadsVertexOffs[4] = {

	{ -0.5f, -0.5f },
	{ -0.5f, +0.5f },
	{ +0.5f, -0.5f },
	{ +0.5f, +0.5f },

};

game_size_t g_gameQuadsCtxDefaultCapacity = 4;
char const *const g_gameQuadsVertPath = "assets/quads.vert";
char const *const g_gameQuadsFragPath = "assets/quads.frag";
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

	ctx->vboData = NULL;
	ctx->vboDataCapacity = 0;
	ctx->vboUsage = GL_STREAM_DRAW;
	ctx->maxId = g_gameQuadsCtxDefaultCapacity;
	ctx->activeCapacity = g_gameQuadsCtxDefaultCapacity;
	ctx->inactiveCapacity = g_gameQuadsCtxDefaultCapacity;

	CALLOC_ARRAY(ctx->active, ctx->activeCapacity, game_quad_t);
	CALLOC_ARRAY(ctx->flips, ctx->inactiveCapacity, unsigned char);
	CALLOC_ARRAY(ctx->textures, ctx->inactiveCapacity, unsigned int);
	CALLOC_ARRAY(ctx->inactive, ctx->inactiveCapacity, game_quad_t);
	CALLOC_ARRAY(ctx->positions, ctx->inactiveCapacity, struct SmlVec3);
	CALLOC_ARRAY(ctx->scalesAndAngles, ctx->inactiveCapacity, struct SmlVec3);

	return ctx;
}

void gameQuadsCtxInit(struct GameQuadsCtx *const p_ctx) {
	p_ctx->shPid = ERRGL(glCreateProgram());
	p_ctx->shVid = ERRGL(glCreateShader(GL_VERTEX_SHADER));
	p_ctx->shFid = ERRGL(glCreateShader(GL_FRAGMENT_SHADER));

	ERRGL(glShaderSource(p_ctx->shVid, 1, &(p_ctx->shVsrc), &(p_ctx->shVlen)));
	ERRGL(glShaderSource(p_ctx->shFid, 1, &(p_ctx->shFsrc), &(p_ctx->shFlen)));

	ERRGL(glCompileShader(p_ctx->shVid));
	ERRGL(glCompileShader(p_ctx->shFid));

	ERRGL(glAttachShader(p_ctx->shPid, p_ctx->shVid));
	ERRGL(glAttachShader(p_ctx->shPid, p_ctx->shFid));

	ERRGL(glLinkProgram(p_ctx->shPid));

	GLchar slogBuf[16384];
	GLsizei slogLen = 16384, slogStrlen;

	memset(slogBuf, 0, slogLen); // NOLINT
	ERRGL(glGetShaderInfoLog(p_ctx->shVid, 16384, &slogLen, slogBuf));
	printf("Quads vertex shader log: %s.\n", slogBuf);

	memset(slogBuf, 0, slogLen); // NOLINT
	ERRGL(glGetShaderInfoLog(p_ctx->shFid, 16384, &slogLen, slogBuf));
	printf("Quads fragment shader log: %s.\n", slogBuf);

	memset(slogBuf, 0, slogLen); // NOLINT
	ERRGL(glGetProgramInfoLog(p_ctx->shPid, 16384, &slogLen, slogBuf));
	printf("Quads program log: %s.\n", slogBuf);

	ERRGL(glBindVertexArray(p_ctx->vao));
	ERRGL(glBindBuffer(GL_ARRAY_BUFFER, p_ctx->vbo));

	ERRGL(glEnableVertexAttribArray(0));
	ERRGL(glEnableVertexAttribArray(1));
	ERRGL(glEnableVertexAttribArray(2));

	ERRGL(glVertexAttribDivisor(0, 0));
	ERRGL(glVertexAttribDivisor(1, 0));
	ERRGL(glVertexAttribDivisor(2, 0));

	ERRGL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(struct GameQuadsVbo), (void*) offsetof(struct GameQuadsVbo, pos)));
	ERRGL(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(struct GameQuadsVbo), (void*) offsetof(struct GameQuadsVbo, scaleAndAngle)));
	ERRGL(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(struct GameQuadsVbo), (void*) offsetof(struct GameQuadsVbo, uv)));
}

void gameQuadsCtxDraw(struct GameQuadsCtx *const p_ctx) {
	ifu(p_ctx->vboDataCapacity != (4 * p_ctx->activeLength)) {

		p_ctx->vboDataCapacity = 4 * p_ctx->activeLength;
		REALLOC_ARRAY(p_ctx->vboData, p_ctx->vboDataCapacity, struct GameQuadsVbo);
		memset(p_ctx->vboData, 0, sizeof(struct GameQuadsVbo) * p_ctx->vboDataCapacity);

	}

	// Positions:
	for (size_t i = 0; i < p_ctx->vboDataCapacity; ++i) {

		p_ctx->vboData[i].pos.x = p_ctx->positions[i].x + g_gameQuadsVertexOffs[i % 4].x;
		p_ctx->vboData[i].pos.y = p_ctx->positions[i].y + g_gameQuadsVertexOffs[i % 4].y;
		p_ctx->vboData[i].pos.z = p_ctx->positions[i].z;

	}

	// Scales-and-angles:
	for (size_t i = 0; i < p_ctx->vboDataCapacity; ++i) {

		p_ctx->vboData[i].scaleAndAngle = p_ctx->scalesAndAngles[i];

	}

	// Flips:
	for (size_t i = 0; i < p_ctx->vboDataCapacity; ++i) {

		switch (p_ctx->flips[i]) {

			case GAME_FLIP_NONE: {

				switch (i % 4) {

					case 0: {

						p_ctx->vboData[i].uv.x = 0;
						p_ctx->vboData[i].uv.y = 0;

					} break;

					case 1: {

						p_ctx->vboData[i].uv.x = 0;
						p_ctx->vboData[i].uv.y = 1;

					} break;

					case 2: {

						p_ctx->vboData[i].uv.x = 1;
						p_ctx->vboData[i].uv.y = 0;

					} break;

					case 3: {

						p_ctx->vboData[i].uv.x = 1;
						p_ctx->vboData[i].uv.y = 1;

					} break;

				}

			} break;

			case GAME_FLIP_BOTH: {

				switch (i % 4) {

					case 0: {

						p_ctx->vboData[i].uv.x = 1;
						p_ctx->vboData[i].uv.y = 1;

					} break;

					case 1: {

						p_ctx->vboData[i].uv.x = 1;
						p_ctx->vboData[i].uv.y = 0;

					} break;


					case 2: {

						p_ctx->vboData[i].uv.x = 0;
						p_ctx->vboData[i].uv.y = 1;

					} break;


					case 3: {

						p_ctx->vboData[i].uv.x = 0;
						p_ctx->vboData[i].uv.y = 0;

					} break;

				}

			} break;

			case GAME_FLIP_VERTICAL: {

				switch (i % 4) {

					case 0: {

						p_ctx->vboData[i].uv.x = 0;
						p_ctx->vboData[i].uv.y = 1;

					} break;

					case 1: {
						p_ctx->vboData[i].uv.x = 0;
						p_ctx->vboData[i].uv.y = 0;

					} break;


					case 2: {

						p_ctx->vboData[i].uv.x = 1;
						p_ctx->vboData[i].uv.y = 1;

					} break;

					case 3: {

						p_ctx->vboData[i].uv.x = 1;
						p_ctx->vboData[i].uv.y = 0;

					} break;

				}

			} break;

			case GAME_FLIP_HORIZONTAL: {

				switch (i % 4) {

					case 0: {

						p_ctx->vboData[i].uv.x = 1;
						p_ctx->vboData[i].uv.y = 0;

					} break;


					case 1: {

						p_ctx->vboData[i].uv.x = 1;
						p_ctx->vboData[i].uv.y = 1;

					} break;


					case 2: {

						p_ctx->vboData[i].uv.x = 0;
						p_ctx->vboData[i].uv.y = 0;

					} break;

					case 3: {

						p_ctx->vboData[i].uv.x = 0;
						p_ctx->vboData[i].uv.y = 1;

					} break;

				}

			} break;

		}

	}

	// Multiply UVs by texture position in atlas:
	for (size_t i = 0; i < p_ctx->vboDataCapacity; ++i) {

		// enum GameTex const tex = p_ctx->textures[i / 4];

		p_ctx->vboData[i].uv.x *= 1; // g_gameTexes[tex];
		p_ctx->vboData[i].uv.y *= 1; // g_gameTexes[tex];

	}

	ERRGL(glUseProgram(p_ctx->shPid));
	ERRGL(glBindVertexArray(p_ctx->vao));
	ERRGL(glBindBuffer(GL_ARRAY_BUFFER, p_ctx->vbo));
	ERRGL(glBufferData(GL_ARRAY_BUFFER, sizeof(struct GameQuadsVbo) * p_ctx->vboDataCapacity, p_ctx->vboData, p_ctx->vboUsage));

	ERRGL(glActiveTexture(GL_TEXTURE0));
	ERRGL(glBindTexture(GL_TEXTURE_2D, g_gameTexesGl[GAME_TEX_TEST1]));
	ERRGL(glUniform1i(glGetUniformLocation(p_ctx->shPid, "u_atlas"), 0));
	ERRGL(glUniform2fv(glGetUniformLocation(p_ctx->shPid, "u_vertexOffs"), 8, (GLfloat*) g_gameQuadsVertexOffs));
	ERRGL(glUniformMatrix4fv(glGetUniformLocation(p_ctx->shPid, "u_cam"), 1, GL_FALSE, (GLfloat*) g_cam->transform));

	struct GameQuadsVbo *v;

	v = p_ctx->vboData + 0;
	printf("pos = (%f, %f, %f), scaleAndAngle = (%f, %f, %f), uv = (%f, %f)\n",
		v->pos.x, v->pos.y, v->pos.z,
		v->scaleAndAngle.x, v->scaleAndAngle.y, v->scaleAndAngle.z,
		v->uv.x, v->uv.y
	);

	v = p_ctx->vboData + 1;
	printf("pos = (%f, %f, %f), scaleAndAngle = (%f, %f, %f), uv = (%f, %f)\n",
		v->pos.x, v->pos.y, v->pos.z,
		v->scaleAndAngle.x, v->scaleAndAngle.y, v->scaleAndAngle.z,
		v->uv.x, v->uv.y
	);

	v = p_ctx->vboData + 2;
	printf("pos = (%f, %f, %f), scaleAndAngle = (%f, %f, %f), uv = (%f, %f)\n",
		v->pos.x, v->pos.y, v->pos.z,
		v->scaleAndAngle.x, v->scaleAndAngle.y, v->scaleAndAngle.z,
		v->uv.x, v->uv.y
	);

	v = p_ctx->vboData + 3;
	printf("pos = (%f, %f, %f), scaleAndAngle = (%f, %f, %f), uv = (%f, %f)\n",
		v->pos.x, v->pos.y, v->pos.z,
		v->scaleAndAngle.x, v->scaleAndAngle.y, v->scaleAndAngle.z,
		v->uv.x, v->uv.y
	);


	// -0.5f, -0.5f, // V
	// +0.0f, +0.0f, // T

	// -0.5f, +0.5f, // V
	// +0.0f, +1.0f, // T

	// +0.5f, -0.5f, // V
	// +1.0f, +0.0f, // T

	// +0.5f, +0.5f, // V
	// +1.0f, +1.0f, // T

	ERRGL(glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, p_ctx->activeLength));
}

void gameQuadsCtxFree(struct GameQuadsCtx *const p_ctx) {
	glDeleteVertexArrays(1, &p_ctx->vao);
	glDeleteBuffers(1, &p_ctx->vbo);
	glDeleteProgram(p_ctx->shPid);
	glDeleteShader(p_ctx->shFid);
	glDeleteShader(p_ctx->shVid);

	free((void*) (p_ctx->shVsrc));
	free((void*) (p_ctx->shFsrc));

	free(p_ctx->scalesAndAngles);
	free(p_ctx->positions);
	free(p_ctx->textures);
	free(p_ctx->flips);

	free(p_ctx->inactive);
	free(p_ctx->vboData);
	free(p_ctx->active);

	free(p_ctx);
}

void gameQuadsDestroy(struct GameQuadsCtx *const p_ctx, game_quad_t const *p_quads, game_size_t const p_count) {
	for (game_size_t i = 0; i < p_ctx->activeLength; ++i) {
		game_quad_t const id = p_quads[i];

		for (game_size_t j = 0; j < p_count; ++j) {

			ifu(p_ctx->active[j] == id) {

				p_ctx->active[j] = p_ctx->active[p_ctx->activeLength - 1];
				p_ctx->activeLength--;
				break;

			}

		}

	}

	for (game_size_t i = 0; i < p_count; ++i) {

		game_quad_t const id = p_quads[i];

		ifu(p_ctx->inactiveLength >= p_ctx->inactiveCapacity) {

			p_ctx->inactiveCapacity *= 2;
			REALLOC_ARRAY(p_ctx->inactive, p_ctx->inactiveCapacity, game_quad_t);

		}

		p_ctx->inactive[p_ctx->inactiveLength] = id;
		++p_ctx->inactiveLength;

		p_ctx->flips[id] = 0;
		p_ctx->textures[id] = 0;
		p_ctx->positions[id] = (struct SmlVec3) { 0, 0, 0 };
		p_ctx->scalesAndAngles[id] = (struct SmlVec3) { 1, 1, 0 };
	}
}

game_quad_t* gameQuadsCreate(struct GameQuadsCtx *const p_ctx, game_quad_t *const p_out, game_size_t const p_many) {
	ifl(p_ctx->inactiveLength >= p_many) {

		game_size_t const inactive = p_ctx->inactiveLength - 1;
		p_ctx->inactiveLength -= p_many;

		for (size_t i = 0; i < p_many; ++i) {

			p_out[i] = p_ctx->inactive[inactive - i];

		}

	} else {

		game_size_t const oldCount = p_ctx->activeLength;
		p_ctx->activeLength += p_many;
		p_ctx->activeCapacity *= 2;

		// NOLINTBEGIN
		REALLOC_ARRAY(p_ctx->active, p_ctx->activeCapacity, game_quad_t); memset(p_ctx->active, 0, p_ctx->activeLength - oldCount);

		REALLOC_ARRAY(p_ctx->flips, p_ctx->activeCapacity, unsigned char); memset(p_ctx->flips, 0, p_ctx->activeLength - oldCount);
		REALLOC_ARRAY(p_ctx->textures, p_ctx->activeCapacity, unsigned int); memset(p_ctx->textures, 0, p_ctx->activeLength - oldCount);
		REALLOC_ARRAY(p_ctx->positions, p_ctx->activeCapacity, struct SmlVec3); memset(p_ctx->positions, 0, p_ctx->activeLength - oldCount);
		REALLOC_ARRAY(p_ctx->scalesAndAngles, p_ctx->activeCapacity, struct SmlVec3); memset(p_ctx->scalesAndAngles, 0, p_ctx->activeLength - oldCount);
		// NOLINTEND

		for (size_t i = 0; i < 4 * p_many; ++i) {

			p_ctx->scalesAndAngles[i].x = 1;
			p_ctx->scalesAndAngles[i].y = 1;

		}

		for (size_t i = 0; i < p_many; ++i) {
			p_out[i] = p_ctx->maxId;
			p_ctx->maxId++;

		}

	}

	return p_out;
}
