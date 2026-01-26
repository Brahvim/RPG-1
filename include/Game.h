#pragma once

#include "Gl.h"
#include "Itq.h"
#include <stddef.h>

void gameDraw();
void gameSetup();
double gameMillis();

extern size_t g_gameFrameCount;
extern double g_gameMillisDraw;
extern double g_gameMillisSetup;
extern struct ItqCtx *g_gameQuadCtx;
