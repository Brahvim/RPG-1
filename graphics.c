#include "game/graphics.h"

int g_gameTexesW[GAME_TEX_TOTAL];
int g_gameTexesH[GAME_TEX_TOTAL];
GLuint g_gameTexesGl[GAME_TEX_TOTAL];
char const *g_gameTexesPaths[GAME_TEX_TOTAL] = {

    "assets/null.png",
    "assets/test0.png",
    "assets/test1.png",
    "assets/test2.png",

};
unsigned char *g_gameTexesData[GAME_TEX_TOTAL];
