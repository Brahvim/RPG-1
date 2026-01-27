#include <stb/stb_image.h>
#include <glad/gles2.h>
#include <unistd.h>
#include <memory.h>
#include <stdio.h>

#include "Macros.h"
#include "Assets.h"
#include "Exit.h"
#include "Sml.h"
#include "Gl.h"

#pragma region Maps.
int g_atlasTexturesDefault[] = {

	TEXTURE_TEST1,
	TEXTURE_TEST0,
	TEXTURE_NONE,

};

int *g_atlasTextures[ATLAS_TOTAL] = {

	g_atlasTexturesDefault,

};

static inline void mapTextures(void) {
#define M(p_texture, p_path) g_texturePaths[p_texture] = p_path; g_texturePathLengths[p_texture] = sizeof(p_path)
	M(TEXTURE_TEST1, "test1.png");
	M(TEXTURE_TEST0, "test0.png");
	M(TEXTURE_NONE, "none.png");
#undef M
}

static inline void mapShaders(void) {
#define M(p_shader, p_vert, p_frag)\
	g_shaderPathsVert[p_shader] = p_vert; g_shaderPathsFrag[p_shader] = p_frag;\
	g_shaderPathLengthsVert[p_shader] = sizeof(p_vert); g_shaderPathLengthsFrag[p_shader] = sizeof(p_frag)
	M(SHADER_QUADS, "quad.vert", "quad.frag");
	M(SHADER_QUAD2, "q2.vert", "q2.frag");
#undef M
}
#pragma endregion

#pragma region Global!
size_t g_cwdLen = 0;
char g_cwd[FILENAME_MAX];

struct Atlas *g_atlases[ATLAS_TOTAL];

pixel_t *g_textureData[TEXTURE_TOTAL];
char const *g_texturePaths[TEXTURE_TOTAL];
struct Rect g_textureRects[TEXTURE_TOTAL];
size_t g_texturePathLengths[TEXTURE_TOTAL];

GLuint g_shaderGlIds[SHADER_TOTAL];
char *g_shaderPathsVert[SHADER_TOTAL];
char *g_shaderPathsFrag[SHADER_TOTAL];
GLuint g_shaderGlIdsVert[SHADER_TOTAL];
GLuint g_shaderGlIdsFrag[SHADER_TOTAL];
GLchar *g_shaderSourcesVert[SHADER_TOTAL];
GLchar *g_shaderSourcesFrag[SHADER_TOTAL];
size_t g_shaderPathLengthsVert[SHADER_TOTAL];
size_t g_shaderPathLengthsFrag[SHADER_TOTAL];
GLint g_shaderSourceLengthsVert[SHADER_TOTAL];
GLint g_shaderSourceLengthsFrag[SHADER_TOTAL];
#pragma endregion

#pragma region Static.
static void loadShaderArrays(char *p_paths[SHADER_TOTAL], size_t p_pathLengths[SHADER_TOTAL], GLchar *p_sources[SHADER_TOTAL]) {
	for (enum ShaderName i = 0; i < SHADER_TOTAL; i++) {

		char fpath[FILENAME_MAX];
		char fdir[] = "/shaders/";
		char const *fname = p_paths[i];

		memset(fpath, 0, FILENAME_MAX);
		strncat(fpath, g_cwd, sizeof(char) * g_cwdLen);
		strncat(fpath, fdir, sizeof(char) * sizeof(fdir));
		strncat(fpath, fname, sizeof(char) * p_pathLengths[i]);
		loadShaderSourceFromPath(&p_sources[i], fpath);

	}
}

static int cmpStbrpRectId(void const *p_first, void const *p_second) {
	struct stbrp_rect const *second = p_second;
	struct stbrp_rect const *first = p_first;
	return first->id - second->id;
}
#pragma endregion

struct Atlas* atlasCreate(size_t const p_count, int const *const p_textures) {
	struct Atlas *atlas;
	callocStruct(atlas);
	atlas->count = p_count;
	callocArray(atlas->rects, atlas->count);

	int width = 0; 	// Widths' max.
	int height = 0; // Heights' sum.
	struct stbrp_rect *rects;
	callocArray(rects, atlas->count);

	// Find the highest width as well as the sum of heights:
	// puti("\nIn the loop that finds the highest width as well as the sum of heights:");
	for (size_t i = 0; i < atlas->count; ++i) {

		int const t = p_textures[i];
		int const w = g_textureRects[t].w;
		int const h = g_textureRects[t].h;

		// printi(
		// 	"`%s`, width `%d`, height `%d`.\n",
		// 	g_texturePaths[t], w, h
		// );

		if (w > width) {

			width = w;

		}

		height += h;

	}

	// puti("\nIn the loop that converts data in `Rect`-form to local `stbrp_rect`s:");
	// Convert data in `Rect`-form to local `stbrp_rect`s:
	for (size_t i = 0; i < atlas->count; ++i) {

		int const t = p_textures[i];
		int const w = g_textureRects[t].w;
		int const h = g_textureRects[t].h;

		// printi(
		// 	"`%s`, width `%d`, height `%d`.\n",
		// 	g_texturePaths[t], w, h
		// );

		rects[i].id = t;
		rects[i].w = w;
		rects[i].h = h;

	}

	atlas->width = width;
	atlas->height = height;

	struct stbrp_node *nodes;
	struct stbrp_context ctx;

	callocArray(nodes, width);

	stbrp_init_target(&ctx, width, height, nodes, width);
	// callocArray(atlas->pixels, atlas->height * atlas->width);
	// qsort(rects, sizeof(stbrp_rect), atlas->count, cmpStbrpRectId); // `TextureName`-sort.

	int const packed = stbrp_pack_rects(&ctx, rects, atlas->count);
	free(nodes);

	if (!packed) {

		pute("Atlas packing failed!");
		free(atlas->rects);
		free(atlas);
		free(rects);
		return NULL;

	}

	ERRGL(glActiveTexture(GL_TEXTURE0));
	ERRGL(glGenTextures(1, &atlas->glTextureId));
	ERRGL(glBindTexture(GL_TEXTURE_2D, atlas->glTextureId));

	ERRGL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
	ERRGL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	ERRGL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	ERRGL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST));

	ERRGL(glTexImage2D(
		GL_TEXTURE_2D,
		0, GL_RGBA8,
		atlas->width,
		atlas->height,
		0, GL_RGBA,
		GL_UNSIGNED_BYTE,
		NULL
	));

	// puti("\n...In some atlas:");

	// Blit packed textures into atlas:
	for (size_t i = 0; i < atlas->count; ++i) {

		int const texid = rects[i].id;
		pixel_t const *const texpix = g_textureData[texid];

		int const x = rects[i].x;
		int const y = rects[i].y;
		int const w = rects[i].w;
		int const h = rects[i].h;
		int const glY = atlas->height - (y + h); // Feel free *not* to invert the placement of all sprites...!

		// printi(
		// 	"Placed `%s`, width `%d`, height `%d` at position `(%d, %d)`.\n",
		// 	g_texturePaths[texid], w, h, x, y
		// );

		ERRGL(glTexSubImage2D(
			GL_TEXTURE_2D, 0,
			x, glY, w, h, GL_RGBA,
			GL_UNSIGNED_BYTE, texpix
		));

	}

	ERRGL(glGenerateMipmap(GL_TEXTURE_2D));
	ERRGL(glBindTexture(GL_TEXTURE_2D, 0)); // Cleaning up? Us? HAH!

	// Change back to the `struct Rect` format:
	for (size_t i = 0; i < atlas->count; ++i) {

		struct stbrp_rect const *const rs = rects + i;
		struct Rect *ra = atlas->rects + i;

		ra->x = rs->x;
		ra->y = rs->y;
		ra->w = rs->w;
		ra->h = rs->h;

	}

	free(rects);
	return atlas;
}

GLint loadShaderSourceFromPath(GLchar **p_buffer, char const *p_path) {
	// Code to help with FS changes, unused...!:
	// size_t retries = 0;
	// retry:
	// if (retries > 5) {
	// 
	//	return -1;
	// 
	// }

	FILE *file = fopen(p_path, "rb");

	if (unlikely(!file)) {

		return -1;

	}

	fseek(file, 0, SEEK_END);
	long length = ftell(file);

	if (unlikely(length < 0)) {

		fclose(file);
		return -1;

	}

	GLchar *buffer = malloc(sizeof(GLchar) * (1 + length));

	if (unlikely(!buffer)) {

		fclose(file);
		return -1;

	}

	rewind(file);
	fread(buffer, 1, length, file);
	fclose(file);

	// Code to help with FS changes, unused...!:
	// if (unlikely(fread(buffer, 1, length, file) != (size_t) length)) {
	//
	// 	fclose(file);
	// 	free(buffer);
	// 	goto retry;
	//
	// }

	buffer[length] = '\0';
	*p_buffer = buffer;

	return length;
}

void loadMappedAtlases(void) {
#define M(p_enum, p_var) \
g_atlases[ATLAS_DEFAULT] = atlasCreate(sizearr(p_var), g_atlasTextures[p_enum] = p_var)

	M(ATLAS_DEFAULT, g_atlasTexturesDefault);

#undef M
}

void loadTextures(void) {
	stbi_set_flip_vertically_on_load(1);
	mapTextures();

	for (unsigned int i = 0; i < TEXTURE_TOTAL; ++i) {

		char fpath[FILENAME_MAX];
		char const fdir[] = "/textures/";
		char const *fname = g_texturePaths[i];

		memset(fpath, 0, FILENAME_MAX);
		// Added `strlen()` safety is good...!:
		strncat(fpath, g_cwd, g_cwdLen * sizeof(char));
		strncat(fpath, fdir, strlen(fdir) * sizeof(char));
		strncat(fpath, fname, strlen(fname) * sizeof(char));

		// THIS helped discover the whole `union` drama inside `struct Rect`.
		// NEVER rely on `union` abuse. NEVER!!!

		// int w, h, c;
		// stbi_info(fpath, &w, &h, &c);
		// printi("`stbi_info()`: `%s`, width `%d`, height `%d`, channels-count `%d`.\n", fpath, w, h, c);

		g_textureData[i] = stbi_load(fpath, &g_textureRects[i].w, &g_textureRects[i].h, NULL, STBI_rgb_alpha);
		printi("Attempted loading `%s`, width `%d`, height `%d`...\n", g_texturePaths[i], g_textureRects[i].w, g_textureRects[i].h);

	}

	// Log failures:
	for (unsigned int i = 0; i < TEXTURE_TOTAL; ++i) {

		void *ptr = g_textureData[i];
		if (unlikely(!ptr)) {

			printe("Failed to load texture `%s`.\n", g_texturePaths[i]);
			continue;

		}

	}

	puti("Textures ready to go!");
}

void loadShaders(void) {
	mapShaders();
	loadShaderArrays(g_shaderPathsVert, g_shaderPathLengthsVert, g_shaderSourcesVert);
	loadShaderArrays(g_shaderPathsFrag, g_shaderPathLengthsFrag, g_shaderSourcesFrag);

#define FERR(x) F(ERRGL(x))
#define F(x) for (size_t i = 0; i < SHADER_TOTAL; i++) x
	// F(g_shaderSourceLengthsVert[i] = strlen(g_shaderSourcesVert[i]));
	// F(g_shaderSourceLengthsFrag[i] = strlen(g_shaderSourcesFrag[i]));

	// `valgrind` WOULDN'T advance debugging with this running `strlen(NULL)`...!:
	F(g_shaderSourceLengthsVert[i] = g_shaderSourcesVert[i] ? strlen(g_shaderSourcesVert[i]) : 0);
	F(g_shaderSourceLengthsFrag[i] = g_shaderSourcesFrag[i] ? strlen(g_shaderSourcesFrag[i]) : 0);

	FERR(g_shaderGlIds[i] = glCreateProgram());
	FERR(g_shaderGlIdsVert[i] = glCreateShader(GL_VERTEX_SHADER));
	FERR(g_shaderGlIdsFrag[i] = glCreateShader(GL_FRAGMENT_SHADER));

	FERR(glShaderSource(g_shaderGlIdsFrag[i], 1, (const GLchar *const []) { g_shaderSourcesFrag[i] }, g_shaderSourceLengthsFrag + i));
	FERR(glShaderSource(g_shaderGlIdsVert[i], 1, (const GLchar *const []) { g_shaderSourcesVert[i] }, g_shaderSourceLengthsVert + i));

	FERR(glCompileShader(g_shaderGlIdsVert[i]));
	FERR(glCompileShader(g_shaderGlIdsFrag[i]));

	FERR(glAttachShader(g_shaderGlIds[i], g_shaderGlIdsVert[i]));
	FERR(glAttachShader(g_shaderGlIds[i], g_shaderGlIdsFrag[i]));

	FERR(glLinkProgram(g_shaderGlIds[i]));
#undef F
#undef FERR

	for (size_t i = 0; i < SHADER_TOTAL; i++) {
#define L 16384

		GLchar logBuf[L];
		GLsizei logLen = L;

		memset(logBuf, 0, logLen);
		ERRGL(glGetShaderInfoLog(g_shaderGlIdsFrag[i], L, &logLen, logBuf));
		if (logLen)	printi("Fragment shader `%d` log: %s.\n", i, logBuf);

		memset(logBuf, 0, logLen);
		ERRGL(glGetShaderInfoLog(g_shaderGlIdsVert[i], L, &logLen, logBuf));
		if (logLen)	printi("Vertex shader `%d` log: %s.\n", i, logBuf);

		memset(logBuf, 0, logLen);
		ERRGL(glGetProgramInfoLog(g_shaderGlIds[i], L, &logLen, logBuf));
		if (logLen)	printi("Program `%d` log: %s.\n", i, logBuf);

#undef L
	}
}

void loadCwd(void) {
	if (likely(getcwd(g_cwd, sizeof(g_cwd)) != NULL)) {

		printi("Current working directory: `%s`.\n", g_cwd);
		g_cwdLen = strlen(g_cwd);

	}
	else {

		pute("`getcwd()` failed.\n");
		gameExit(EXIT_FAILURE);

	}
}
