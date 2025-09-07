#include "Quads.h"

GLuint g_quadOffsetsVbo = 0;
struct SmlVec2 g_quadOffsets[4] = {

	{ -0.5f, -0.5f },
	{ +0.5f, -0.5f },
	{ -0.5f, +0.5f },
	{ +0.5f, +0.5f },

};

void quadInit(void) {
	ERRGL(glGenBuffers(1, &g_quadOffsetsVbo));
	ERRGL(glBindBuffer(GL_ARRAY_BUFFER, g_quadOffsetsVbo));
	ERRGL(glBufferData(GL_ARRAY_BUFFER, sizeof(g_quadOffsets), g_quadOffsets, GL_STATIC_DRAW));
	// ERRGL(glBindBuffer(GL_ARRAY_BUFFER, 0)); // Do we *really* need to be the ones cleaning up?
}
