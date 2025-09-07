#pragma once
#include "Gl.h"
#include "Sml.h"
#include "List.h"
#include <stdio.h>
#include <stddef.h>
#include <stb/stb_rect_pack.h>

typedef unsigned char pixel_t;

#pragma region Working dir!
extern char g_cwd[FILENAME_MAX];
extern size_t g_cwdLen;
void loadCwd(void);
#pragma endregion

#pragma region Textures.
struct Rect {

	union {

		int list[4];
		int x, y, w, h;

	};

};

enum Flip {

	FLIP_NONE,
	FLIP_VERTICAL,
	FLIP_HORIZONTAL,
	FLIP_ON_BOTH_AXES,

};

enum TextureName {

	TEXTURE_NONE,
	TEXTURE_TEST1,
	TEXTURE_TEST2,

	TEXTURE_TOTAL

};

void loadTextures(void);

extern pixel_t *g_textureData[TEXTURE_TOTAL];
extern struct Rect g_textureRects[TEXTURE_TOTAL];
extern char const *g_texturePaths[TEXTURE_TOTAL];
extern size_t g_texturePathLengths[TEXTURE_TOTAL];
#pragma endregion

#pragma region Atlases.
struct Atlas {

	// These are all 4 bytes:

	int count;		// ...of *textures* in the atlas!
	int width;		// ...of the atlas.
	int height;		// ...of the atlas.
	GLuint glTextureId;	// ...of the atlas!

	// These are all 8 bytes:

	int *textures; 		// In order of `Atlas::rects`, which textures does this atlas contain?
	pixel_t *pixels;	// ...All the pixels in the atlas! It's all `pixel_t` in here.
	struct Rect *rects; // `x`, `y`, `w`, `h`. In order of `Atlas::textures`!

};

enum AtlasName {

	ATLAS_DEFAULT,

	ATLAS_TOTAL

};

void loadAtlases(void);
extern int *g_atlasTextures[ATLAS_TOTAL];
extern struct Atlas *g_atlases[ATLAS_TOTAL];
struct Atlas* atlasCreate(size_t const textureCount, int const *const textures);
#pragma endregion
