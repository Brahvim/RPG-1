#pragma once
#include <stdio.h>
#include <stddef.h>

void loadCwd(void);
extern size_t g_cwdLen;
extern char g_cwd[FILENAME_MAX];

#pragma region Textures.
enum Texture {

    TEXTURES_NULL,
    TEXTURES_TEST,
    TEXTURES_TOTAL

};

enum TextureFlip {

    TEXTURE_FLIP_NONE,
    TEXTURE_FLIP_BOTH,
    TEXTURE_FLIP_VERTICAL,
    TEXTURE_FLIP_HORIZONTAL,
    TEXTURE_FLIP_TOTAL

};

extern int g_textureWidths[TEXTURES_TOTAL];
extern GLuint g_textureIds[TEXTURES_TOTAL];
extern int g_textureHeights[TEXTURES_TOTAL];
extern char const *g_texturePaths[TEXTURES_TOTAL];
extern unsigned char *g_texturesBytes[TEXTURES_TOTAL];

void loadTextures(void);
#pragma endregion
