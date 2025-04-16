#include <stdlib.h>
#include <memory.h>

#include "ifs.h"
#include "sml.h"
#include "game/main.h"
#include "game/graphics/quads.h"

struct GameGraphicsQuadsCtx* gameGraphicsQuadsCtxCreate() {
	struct GameGraphicsQuadsCtx *ctx = malloc(sizeof(struct GameGraphicsQuadAos2));

	memset(ctx, 0, sizeof(struct GameGraphicsQuadsCtx));
	ctx->inactiveCapacity = g_gameGraphicsQuadsCtxDefaultCapacity;
	ctx->inactive = calloc(ctx->inactiveCapacity, sizeof(game_quad_t));

	sizeof(float);
	sizeof(enum GameTex);
	sizeof(unsigned int);
	sizeof(game_size_t);
	sizeof(struct SmlVec2);

	return ctx;
}

game_quad_t gameGraphicsQuadsCreate(struct GameGraphicsQuadsCtx *const p_ctx) {
	game_quad_t const id = p_ctx->maxId;

	ifl(p_ctx->inactiveCount > 0) {

		--p_ctx->inactiveCount;
		p_ctx->inactive[p_ctx->inactiveCount];

	} else 	ifu(p_ctx->maxId >= p_ctx->activeCapacity) {

		p_ctx->activeCapacity *= 2;

		p_ctx->texes = realloc(p_ctx->texes, sizeof(enum GameTex) * p_ctx->activeCapacity);
		p_ctx->flips = realloc(p_ctx->flips, sizeof(unsigned char) * p_ctx->activeCapacity);
		p_ctx->active = realloc(p_ctx->active, sizeof(game_quad_t) * p_ctx->activeCapacity);
		p_ctx->scales = realloc(p_ctx->scales, sizeof(struct SmlVec2) * p_ctx->activeCapacity);
		p_ctx->rotations = realloc(p_ctx->rotations, sizeof(struct SmlVec2) * p_ctx->activeCapacity);
		p_ctx->positions = realloc(p_ctx->positions, sizeof(struct SmlVec2) * p_ctx->activeCapacity);

	}

	++p_ctx->maxId;
	++p_ctx->activeCount;
	return id;
}

void gameGraphicsQuadsCtxDraw(struct GameGraphicsQuadsCtx const *const p_ctx) {

}

void gameGraphicsQuadsDestroy(struct GameGraphicsQuadsCtx *p_ctx, game_quad_t const p_quad) {

}
