#include "game/graphics.h"

typedef unsigned long long game_quad_t;
extern game_size_t g_gameQuadsCtxDefaultCapacity;

struct GameQuadsCtx {

	// Least accessed (shouldn't be at the beginning of the structure then, I guess?!):
	GLuint vao;
	GLuint vbo;
	GLenum vboUsage;

	game_size_t maxId;

	game_quad_t *active;
	game_quad_t *inactive;

	game_size_t activeCount;
	game_size_t inactiveCount;

	game_size_t activeCapacity;
	game_size_t inactiveCapacity;

	// Actual data:
	unsigned char *flips;
	enum GameTex *texture;
	struct SmlVec3 *position;
	struct SmlVec3 *scaleAndAngle;
	// These were going to be in an AoS TILL I realized that user-access is like...
	// SUPER non-uni, AND I WAS going to be using separate loops anyway.

};

struct GameQuadsCtx* gameQuadsCtxAlloc();
void gameQuadsCtxDraw(struct GameQuadsCtx const *const ctx);
void gameQuadsDestroy(struct GameQuadsCtx *const ctx, game_quad_t const *quads, game_size_t const count);
game_quad_t* gameQuadsCreate(struct GameQuadsCtx *const ctx, game_quad_t *const out, game_size_t const count);
