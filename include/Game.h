#pragma once
#include "Gl.h"
#include "Quad.h"
#include <stddef.h>

void gameDraw(void);
void gameSetup(void);
double gameMillis(void);

extern size_t g_gameFrameCount;
extern double g_gameMillisDraw;
extern double g_gameMillisSetup;
extern struct QuadCtx *g_gameQuadCtx;
