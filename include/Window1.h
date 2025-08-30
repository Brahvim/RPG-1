#pragma once
#include <GLFW/glfw3.h>

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

void window1Create(void);
void window1Delete(void);
void window1UpdateVars(void);
void window1CbckKey(GLFWwindow *const window, int const key, int const scancode, int const action, int const mods);
