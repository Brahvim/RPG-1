#pragma once

#include "Gl.h"
#include "Quad2.h"
#include <stddef.h>

void gameDraw();
void gameSetup();
void gameShutdown();
double gameMillis();

extern size_t g_gameFrameCount;
extern double g_gameMillisDraw;
extern double g_gameMillisSetup;
extern struct Quad2Ctx *g_gameQuad2Ctx;
