#pragma once

#include "sml.h"
#include "game/graphics.h"

typedef unsigned long long game_quad_t;

#define GAME_QUADS_VERT_PATH "assets/quads.vert"
#define GAME_QUADS_FRAG_PATH "assets/quads.frag"

extern struct SmlVec2 g_gameQuadsVertexOffs[4];

extern char const *const g_gameQuadsFragPath;
extern char const *const g_gameQuadsVertPath;

extern game_t g_gameQuadsCtxDefaultCapacity;

extern GLchar const *g_gameQuadsVertSrc;
extern GLchar const *g_gameQuadsFragSrc;

extern GLint g_gameQuadsFragLen;
extern GLint g_gameQuadsVertLen;

struct GameQuadsCtx {

	game_quad_t *active;
	game_quad_t *inactive;

	game_t activeLength;
	game_t inactiveLength;

	game_t activeCapacity;
	game_t inactiveCapacity;

	game_t vboDataCapacity;
	struct GameQuadsVbo *vboData;

	/* -- End of first 64-byte cache line! -- */

	// Actual data:
	unsigned char *flips;
	unsigned int *textures;
	struct SmlVec3 *positions;
	struct SmlVec3 *scalesAndAngles;
	// These were going to be in an AoS TILL I realized that user-access is like...
	// SUPER non-uni, AND I WAS going to be using separate loops anyway.

	// Least accessed (shouldn't be at the beginning of the structure then, I guess?!):
	GLuint idProgram;
	GLuint vao;
	GLuint vbo;

	game_t maxId;
	GLenum vboUsage;

	/* -- End of second 64-byte cache line... -- */

	GLuint idShaderVert;
	GLuint idShaderFrag;

	GLint lenShaderVert;
	GLint lenShaderFrag;

	GLchar const *strShaderVert;
	GLchar const *strShaderFrag;

};

void gameQuadsInit();
struct GameQuadsCtx* gameQuadsCtxAlloc();
void gameQuadsCtxDraw(struct GameQuadsCtx *const ctx);
void gameQuadsCtxInit(struct GameQuadsCtx *const ctx);
void gameQuadsCtxFree(struct GameQuadsCtx *const ctx);
void gameQuadsDestroy(struct GameQuadsCtx *const ctx, game_quad_t const *quads, game_t const count);
game_quad_t* gameQuadsCreate(struct GameQuadsCtx *const ctx, game_quad_t *const out, game_t const count);
