#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#include "ifs.h"
#include "sml.h"
#include "game/quads.h"

game_size_t g_gameQuadsCtxDefaultCapacity = 4;

struct GameQuadsCtx* gameQuadsCtxAlloc() {
	struct GameQuadsCtx *ctx = malloc(sizeof(struct GameQuadsCtx));

	memset(ctx, 0, sizeof(struct GameQuadsCtx)); // NOLINT
	ctx->maxId = g_gameQuadsCtxDefaultCapacity;
	ctx->activeCapacity = g_gameQuadsCtxDefaultCapacity;
	ctx->inactiveCapacity = g_gameQuadsCtxDefaultCapacity;
	CALLOC_ARRAY(ctx->active, ctx->activeCapacity, game_quad_t);
	CALLOC_ARRAY(ctx->inactive, ctx->inactiveCapacity, game_quad_t);

	CALLOC_ARRAY(ctx->flips, ctx->inactiveCapacity, unsigned char);
	CALLOC_ARRAY(ctx->texture, ctx->inactiveCapacity, enum GameTex);
	CALLOC_ARRAY(ctx->position, ctx->inactiveCapacity, struct SmlVec3);
	CALLOC_ARRAY(ctx->scaleAndAngle, ctx->inactiveCapacity, struct SmlVec3);

	return ctx;
}

void gameQuadsCtxDraw(struct GameQuadsCtx const *const p_ctx) {

}

void gameQuadsDestroy(struct GameQuadsCtx *const p_ctx, game_quad_t const *p_quads, game_size_t const p_count) {

}

game_quad_t* gameQuadsCreate(struct GameQuadsCtx *const p_ctx, game_quad_t *const p_out, game_size_t const p_many) {
	ifl(p_ctx->inactiveCount >= p_many) {

		game_size_t const inactive = p_ctx->inactiveCount - 1;
		p_ctx->inactiveCount -= p_many;

		foru(size_t i = 0, i < p_many, ++i) {

			p_out[i] = p_ctx->inactive[inactive - i];

		}


	} else {

		game_size_t const oldCount = p_ctx->activeCount;
		p_ctx->activeCount += p_many;
		p_ctx->activeCapacity *= 2;

		// NOLINTBEGIN
		REALLOC_ARRAY(p_ctx->active, p_ctx->activeCapacity, game_quad_t); memset(p_ctx->active, 0, p_ctx->activeCount - oldCount);
		REALLOC_ARRAY(p_ctx->active, p_ctx->activeCapacity, game_quad_t); memset(p_ctx->active, 0, p_ctx->activeCount - oldCount);
		REALLOC_ARRAY(p_ctx->flips, p_ctx->activeCapacity, unsigned char); memset(p_ctx->flips, 0, p_ctx->activeCount - oldCount);
		REALLOC_ARRAY(p_ctx->texture, p_ctx->activeCapacity, enum GameTex); memset(p_ctx->texture, 0, p_ctx->activeCount - oldCount);
		REALLOC_ARRAY(p_ctx->position, p_ctx->activeCapacity, struct SmlVec3); memset(p_ctx->position, 0, p_ctx->activeCount - oldCount);
		REALLOC_ARRAY(p_ctx->scaleAndAngle, p_ctx->activeCapacity, struct SmlVec3); memset(p_ctx->scaleAndAngle, 0, p_ctx->activeCount - oldCount);
		// NOLINTEND

		foru(size_t i = 0, i < p_many, ++i) {

			p_out[i] = p_ctx->maxId++;

		}

	}

	return p_out;
}
