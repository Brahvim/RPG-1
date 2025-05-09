#pragma once
#include <GLFW/glfw3.h>
#include "ifs.h"

extern int g_window1X;
extern int g_window1Y;
extern int g_window1W;
extern int g_window1H;
extern int g_window1Wfb;
extern int g_window1Hfb;
extern char g_window1Full;
extern int g_window1XUnFull;
extern int g_window1YUnFull;
extern int g_window1WUnFull;
extern int g_window1HUnFull;
extern GLFWwindow *g_window1;
extern int const g_window1WDef;
extern int const g_window1HDef;

void gameWindow1Create(void);
void gameWindow1Destroy(void);
void gameWindow1UpdateVars(void);
void gameWindow1CbckKey(GLFWwindow *const window, int const key, int const scancode, int const action, int const mods);
