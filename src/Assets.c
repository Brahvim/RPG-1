#include <stb/stb_image.h>
#include <glad/gles2.h>
#include <unistd.h>
#include <memory.h>
#include <stdio.h>

#include "UtilMacros.h"
#include "Assets.h"
#include "Sml.h"
#include "Gl.h"

#pragma region Maps.
int g_atlasTexturesDefault[] = {

	TEXTURE_TEST2,
	TEXTURE_TEST1,
	TEXTURE_NONE,

};

int *g_atlasTextures[ATLAS_TOTAL] = {

	g_atlasTexturesDefault,

};

static inline void mapTextures(void) {
#define M(p_texture, p_path) g_texturePaths[p_texture] = p_path; g_texturePathLengths[p_texture] = sizeof(p_path)
	M(TEXTURE_TEST2, "test1.png");
	M(TEXTURE_TEST1, "test0.png");
	M(TEXTURE_NONE, "none.png");
#undef M
}

static inline void mapShaders(void) {
#define M(p_shader, p_vert, p_frag)\
	g_shaderPathsVert[p_shader] = p_vert; g_shaderPathsFrag[p_shader] = p_frag;\
	g_shaderPathLengthsVert[p_shader] = sizeof(p_vert); g_shaderPathLengthsFrag[p_shader] = sizeof(p_frag)
	M(SHADER_QUADS, "quad.vert", "quad.frag");
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
static void loadShadersFromFiles(char *p_paths[SHADER_TOTAL], size_t p_pathLengths[SHADER_TOTAL], GLchar *p_sources[SHADER_TOTAL]) {
	for (size_t i = 0; i < SHADER_TOTAL; i++) {

		char fpath[FILENAME_MAX];
		char fdir[] = "/shaders/";
		char const *fname = p_paths[i];

		memset(fpath, 0, FILENAME_MAX);
		strncat(fpath, g_cwd, sizeof(char) * g_cwdLen);
		strncat(fpath, fdir, sizeof(char) * sizeof(fdir));
		strncat(fpath, fname, sizeof(char) * p_pathLengths[i]);
		loadShaderSource(&p_sources[i], fpath);

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
	CALLOC_STRUCT(atlas);
	atlas->count = p_count;
	CALLOC_ARRAY(atlas->rects, atlas->count);

	int width = 0; 	// Widths' max.
	int height = 0; // Heights' sum.
	struct stbrp_rect *rects;
	CALLOC_ARRAY(rects, atlas->count);

	// Find the highest width as well as the sum of heights:
	for (size_t i = 0; i < atlas->count; ++i) {

		int const w = g_textureRects[i].w;
		int const h = g_textureRects[i].h;
		int const t = p_textures[i];

		if (w > width) {

			width = w;

		}

		height += h;

	}

	// Convert data in `Rect`-form to local `stbrp_rect`s:
	for (size_t i = 0; i < atlas->count; ++i) {

		int const w = g_textureRects[i].w;
		int const h = g_textureRects[i].h;
		int const t = p_textures[i];

		rects[i].id = t;
		rects[i].w = w;
		rects[i].h = h;

	}

	atlas->width = width;
	atlas->height = height;

	struct stbrp_node *nodes;
	struct stbrp_context ctx;

	CALLOC_ARRAY(nodes, width);

	// Sort rects based on `enum Texture`:
	// qsort(rects, sizeof(stbrp_rect), atlas->count, cmpStbrpRectId);

	CALLOC_ARRAY(atlas->pixels, atlas->height * atlas->width);
	stbrp_init_target(&ctx, width, height, nodes, width);

	int const packed = stbrp_pack_rects(&ctx, rects, atlas->count);

	if (!packed) {

		puts("Atlas packing failed!");

	}

	free(nodes);

	// Blit packed textures into atlas:
	for (size_t i = 0; i < atlas->count; ++i) {

		pixel_t const *const tex = g_textureData[rects[i].id];
		int const x = rects[i].x;
		int const y = rects[i].y;
		int const w = rects[i].w;
		int const h = rects[i].h;

		for (int row = 0; row < y; ++row) {

			pixel_t *dst = atlas->pixels + (width * (y + row) + x);
			pixel_t const *const src = tex + (w * row);
			memcpy(dst, src, x * sizeof(pixel_t));

		}

	}

	// Change back to the `struct Rect` format:
	for (size_t i = 0; i < atlas->count; ++i) {

		struct stbrp_rect const *const r2 = rects + i;
		struct Rect *r1 = atlas->rects + i;

		r1->x = r2->x;
		r1->y = r2->y;
		r1->w = r2->w;
		r1->h = r2->h;

	}

	free(rects);

	ERRGL(glActiveTexture(GL_TEXTURE0));
	ERRGL(glGenTextures(1, &atlas->glTextureId));
	ERRGL(glBindTexture(GL_TEXTURE_2D, atlas->glTextureId));

	ERRGL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	ERRGL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	ERRGL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
	ERRGL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

	ERRGL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, atlas->width, atlas->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, atlas->pixels));
	ERRGL(glGenerateMipmap(GL_TEXTURE_2D)); // Not *quite* 3D, are we?!
	ERRGL(glBindTexture(GL_TEXTURE_2D, 0)); // Cleaning up? Us? HAH!

	return atlas;
}

GLint loadShaderSource(GLchar **p_buffer, char const *p_path) {
	FILE *file = fopen(p_path, "rb");

	if (unlikely(!file)) {

		return -1;

	}

	fseek(file, 0, SEEK_END);
	long const length = ftell(file);

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

	buffer[length] = '\0';
	*p_buffer = buffer;

	return length;
}

void loadTextures(void) {
	stbi_set_flip_vertically_on_load(1);
	mapTextures();

	for (unsigned int i = 0; i < TEXTURE_TOTAL; ++i) {

		char fpath[FILENAME_MAX];
		char const fdir[] = "/textures/";
		char const *fname = g_texturePaths[i];

		memset(fpath, 0, FILENAME_MAX);
		strncat(fpath, g_cwd, sizeof(char) * g_cwdLen);
		strncat(fpath, fdir, sizeof(char) * sizeof(fdir));
		strncat(fpath, fname, sizeof(char) * strlen(fname));

		g_textureData[i] = stbi_load(fpath, &g_textureRects[i].w, &g_textureRects[i].h, NULL, STBI_rgb_alpha);
		printf("Attempted loading `%s`, width `%d`, height `%d`...\n", g_texturePaths[i], g_textureRects[i].w, g_textureRects[i].h);

	}

	// Log failures:
	for (unsigned int i = 0; i < TEXTURE_TOTAL; ++i) {

		void *ptr = g_textureData[i];
		if (unlikely(!ptr)) {

			fprintf(stderr, "Failed to load texture `%s`.\n", g_texturePaths[i]);
			continue;

		}

	}

	puts("Textures ready to go!");
}

void loadAtlases(void) {
#define M(p_enum, p_var) g_atlases[ATLAS_DEFAULT] = atlasCreate(sizeof(p_var) / sizeof(p_var[0]), &(*g_atlasTextures[p_enum]));
	// #define M(p_enum, p_var) g_atlases[p_enum] = atlasCreate(sizeof(p_var) / sizeof(p_var[0]), g_atlasTextures[p_enum])
	M(ATLAS_DEFAULT, g_atlasTexturesDefault);
#undef M
}

void loadShaders(void) {
	mapShaders();
	loadShadersFromFiles(g_shaderPathsVert, g_shaderPathLengthsVert, g_shaderSourcesVert);
	loadShadersFromFiles(g_shaderPathsFrag, g_shaderPathLengthsFrag, g_shaderSourcesFrag);

#define FERR(x) F(ERRGL(x))
#define F(x) for (size_t i = 0; i < SHADER_TOTAL; i++) x
	F(g_shaderSourceLengthsVert[i] = strlen(g_shaderSourcesVert[i]));
	F(g_shaderSourceLengthsFrag[i] = strlen(g_shaderSourcesFrag[i]));

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
		if (logLen)	printf("Fragment shader `%d` log: %s.\n", i, logBuf);

		memset(logBuf, 0, logLen);
		ERRGL(glGetShaderInfoLog(g_shaderGlIdsVert[i], L, &logLen, logBuf));
		if (logLen)	printf("Vertex shader `%d` log: %s.\n", i, logBuf);

		memset(logBuf, 0, logLen);
		ERRGL(glGetProgramInfoLog(g_shaderGlIds[i], L, &logLen, logBuf));
		if (logLen)	printf("Program `%d` log: %s.\n", i, logBuf);

#undef L
	}
}

void loadCwd(void) {
	if (likely(getcwd(g_cwd, sizeof(g_cwd)) != NULL)) {

		printf("Current working directory: `%s`.\n", g_cwd);
		g_cwdLen = strlen(g_cwd);

	}
	else {

		perror("Failed to `getcwd()` the current working directory.\n");
		gameExit(EXIT_FAILURE);

	}
}
