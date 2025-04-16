#pragma once
#include "game/graphics.h"

typedef unsigned long long game_quad_t;
game_size_t g_gameGraphicsQuadsCtxDefaultCapacity = 4;

struct GameGraphicsQuadsCtx {

	GLuint vao;
	GLuint vbo;

	game_size_t maxId;
	game_quad_t *active;
	game_quad_t *inactive;

	game_size_t activeCount;
	game_size_t inactiveCount;

	game_size_t activeCapacity;
	game_size_t inactiveCapacity;

};

/*
- Imagine that `gameGraphicsQuadsCtxDraw()` first `memset()`s a CPU-side VBO to `0`, then:
- Sorts a `GameGraphicsQuadAos1*` according to `GameGraphicsQuadAos1::order`.
- Sorts a `GameGraphicsQuadAos2*` according to `GameGraphicsQuadAos1::order`. Maybe `order` should be in a separate AoS?!
- Next, it fills the VBO with tex coords based on `GameGraphicsQuadAos1`, texture ID and flips and all - **we'll use an atlas**!
- Next, we fill all other data.
- `glDrawArraysInstanced()`...?
*/

struct GameGraphicsQuadAos {

	float z;
	float rotation;
	unsigned int flips;
	enum GameTex texture;
	struct SmlVec2 scale;
	struct SmlVec2 position;

};

struct GameGraphicsQuadsCtx* gameGraphicsQuadsCtxCreate();
game_quad_t gameGraphicsQuadsCreate(struct GameGraphicsQuadsCtx *const ctx);
void gameGraphicsQuadsCtxDraw(struct GameGraphicsQuadsCtx const *const ctx);
void gameGraphicsQuadsDestroy(struct GameGraphicsQuadsCtx *const ctx, game_quad_t const quad);
