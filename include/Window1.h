#pragma once
#define GLFW_INCLUDE_NONE 1
#include <GLFW/glfw3.h>

#pragma region Globals.
extern int g_window1X;
extern int g_window1Y;
extern int g_window1W;
extern int g_window1H;
extern int g_window1Wfb; // "Framebuffer"!
extern int g_window1Hfb; // "Framebuffer"!
#define g_window1HDef 720 // "Default".
extern char g_window1Full;
#define g_window1WDef 1280 // "Default".
extern int g_window1XUnFull;
extern int g_window1YUnFull;
extern int g_window1WUnFull;
extern int g_window1HUnFull;
extern GLFWwindow *g_window1;
#pragma endregion

void window1Create();
void window1Delete();
void window1Update();
void window1CbckKey(GLFWwindow *const window, int const key, int const scancode, int const action, int const mods);
