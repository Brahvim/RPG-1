#pragma once

#include "Gl.h"
#include "Quad.h"
#include <stddef.h>

void gameDraw();
void gameSetup();
void gameShutdown();
double gameMillis();

extern size_t g_gameFrameCount;
extern double g_gameMillisDraw;
extern double g_gameMillisSetup;
extern struct QuadCtx *g_gameQuadCtx;
