#pragma once
#include "Gl.h"
#include "Sml.h"
#include "List.h"
#include <stdio.h>
#include <stddef.h>
#include <stb/stb_rect_pack.h>

typedef unsigned char pixel_t;

#pragma region Current dir!
extern char g_cwd[FILENAME_MAX];
extern size_t g_cwdLen;
void loadCwd(void);
#pragma endregion

#pragma region Textures.
struct Rect {

	int x;
	int y;
	int w;
	int h;

};

enum TextureFlip { // A frag-shader branch IS the fastest method!

	FLIP_NONE,
	FLIP_VERTICAL,
	FLIP_HORIZONTAL,
	FLIP_ON_BOTH_AXES

};

#define T(x) TEXTURE_ ## x
enum TextureName {

	T(MISSING),
	T(BLACK),
	T(WHITE),
	T(GRID),

	T(TOTAL)

};
#undef T

void loadTextures(void);

extern pixel_t *g_textureData[TEXTURE_TOTAL];
extern char const *g_texturePaths[TEXTURE_TOTAL];
extern size_t g_texturePathLengths[TEXTURE_TOTAL];
extern struct SmlVec2 g_textureDims[TEXTURE_TOTAL];
#pragma endregion

#pragma region Atlases.
struct Atlas {

	// These first 4 are all 4 bytes:

	int count;			// ...of *textures* in the atlas!
	int width;			// ...of the atlas.
	int height;			// ...of the atlas.
	GLuint glTextureId;	// ...of the atlas!

	// These last 2 are all 8 bytes:

	struct Rect *rects; 		// `x`, `y`, `w`, `h`. In order of `Atlas::textures`!
	enum TextureName *textures; // In order of `Atlas::rects`, which textures does this atlas contain?

};

#define A(x) ATLAS_ ## x
enum AtlasName {

	A(DEFAULT),

	A(TOTAL)

};
#undef A

void loadMappedAtlases(void);
extern struct Atlas g_atlases[ATLAS_TOTAL];
extern size_t g_atlasTextureCounts[ATLAS_TOTAL];
extern long long *g_atlasTextureIndices[ATLAS_TOTAL];
struct Atlas* atlasCreate(enum AtlasName const atlas);
extern enum TextureName *g_atlasTextureNames[ATLAS_TOTAL];
#pragma endregion

#pragma region Shaders.
#define S(x) SHADER_ ## x
enum ShaderName {

	S(QUADS),

	S(TOTAL)

};
#undef S

void loadShaders(void);

/*
 * Shaders upto 2 GiB only! If they have more than that many **[AS]C[II] `char`s**, this won't put those in.
 * We don't check for FS changes, don't split into a string array, don't respect that GLES contract...
 * ...But it works. Whenever it stops being enough, we rewrite this function!
 */
GLint loadShaderSourceFromPath(GLchar **buffer, char const *path);

extern GLuint g_shaderGlIds[SHADER_TOTAL];

extern char *g_shaderPathsVert[SHADER_TOTAL];
extern char *g_shaderPathsFrag[SHADER_TOTAL];

extern GLuint g_shaderGlIdsVert[SHADER_TOTAL];
extern GLuint g_shaderGlIdsFrag[SHADER_TOTAL];

extern GLchar *g_shaderSourcesVert[SHADER_TOTAL];
extern GLchar *g_shaderSourcesFrag[SHADER_TOTAL];

extern size_t g_shaderPathLengthsVert[SHADER_TOTAL];
extern size_t g_shaderPathLengthsFrag[SHADER_TOTAL];

extern GLint g_shaderSourceLengthsVert[SHADER_TOTAL];
extern GLint g_shaderSourceLengthsFrag[SHADER_TOTAL];
#pragma endregion
