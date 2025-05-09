#pragma once
#include "sml.h"
#include "game/graphics.h"

typedef unsigned long long game_quad_t;

extern GLint g_gameQuadsFragLen;
extern GLint g_gameQuadsVertLen;
extern GLchar const *g_gameQuadsVertSrc;
extern GLchar const *g_gameQuadsFragSrc;
extern char const *const g_gameQuadsFragPath;
extern char const *const g_gameQuadsVertPath;
extern struct SmlVec2 g_gameQuadsVertexOffs[4];
extern game_size_t g_gameQuadsCtxDefaultCapacity;

struct GameQuadsVbo {

	struct SmlVec3 pos;
	struct SmlVec3 scaleAndAngle;
	struct SmlVec2 uv;

};

struct GameQuadsCtx {

	game_quad_t *active;
	game_quad_t *inactive;

	game_size_t activeLength;
	game_size_t inactiveLength;

	game_size_t activeCapacity;
	game_size_t inactiveCapacity;

	game_size_t vboDataCapacity;
	struct GameQuadsVbo *vboData;

	// -- End of first x86 cache line! --

	// Actual data:
	unsigned char *flips;
	unsigned int *textures;
	struct SmlVec3 *positions;
	struct SmlVec3 *scalesAndAngles;
	// These were going to be in an AoS TILL I realized that user-access is like...
	// SUPER non-uni, AND I WAS going to be using separate loops anyway.

	// Least accessed (shouldn't be at the beginning of the structure then, I guess?!):
	GLuint shPid;
	GLuint vao;
	GLuint vbo;

	game_size_t maxId;
	GLenum vboUsage;

	// -- End of second x86 cache line... --

	GLuint shVid;
	GLuint shFid;

	GLint shVlen;
	GLint shFlen;

	GLchar const *shVsrc;
	GLchar const *shFsrc;

};

void gameQuadsInit();
struct GameQuadsCtx* gameQuadsCtxAlloc();
void gameQuadsCtxDraw(struct GameQuadsCtx *const ctx);
void gameQuadsCtxInit(struct GameQuadsCtx *const ctx);
void gameQuadsCtxFree(struct GameQuadsCtx *const ctx);
void gameQuadsDestroy(struct GameQuadsCtx *const ctx, game_quad_t const *quads, game_size_t const count);
game_quad_t* gameQuadsCreate(struct GameQuadsCtx *const ctx, game_quad_t *const out, game_size_t const count);
