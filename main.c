#pragma region // Headers.
#pragma region // Not my headers!
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <AL/al.h>

#include <stb/stb_image.h>

#define STB_VORBIS_HEADER_ONLY
#include <stb/stb_vorbis.h>
#pragma endregion

#include "ifs.h"
#include "game/main.h"
#include "game/quads.h"
#include "game/window1.h"
#pragma endregion

GLenum g_errorGl;
char g_cwd[FILENAME_MAX];
struct GameQuadsCtx *ctx;
size_t g_cwdLen = FILENAME_MAX;

GLint gameShaderFromFile(GLchar const **p_buffer, char const *p_path) {
	FILE *file = fopen(p_path, "rb");

	ifu(!file) {

		return -1;

	}

	fseek(file, 0, SEEK_END);
	GLint const length = ftell(file);

	ifu(length < 0) {

		fclose(file);
		return -1;

	}

	GLchar *buffer = malloc(sizeof(GLchar) * (1 + length));

	ifu(!buffer) {

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

char const* glGetErrorString(GLenum p_error) {
	switch (p_error) {

		case GL_INVALID_ENUM: return "GL_INVALID_ENUM";
		case GL_INVALID_VALUE: return "GL_INVALID_VALUE";
		case GL_OUT_OF_MEMORY: return "GL_OUT_OF_MEMORY";
		case GL_INVALID_OPERATION: return "GL_INVALID_OPERATION";
		case GL_INVALID_FRAMEBUFFER_OPERATION: return "GL_INVALID_FRAMEBUFFER_OPERATION";

	}

	return "GL_NO_ERROR";
}

void gameTexesLoad(void) {
	stbi_set_flip_vertically_on_load(1);
	ERRGL(glActiveTexture(GL_TEXTURE0));
	ERRGL(glGenTextures(GAME_TEX_TOTAL, g_gameTexesGl));

	for (int i = 0; i < GAME_TEX_TOTAL; ++i) {

		char fname[FILENAME_MAX];
		// NOLINTBEGIN
		memset(fname, 0, FILENAME_MAX);
		strncat(fname, g_cwd, g_cwdLen);
		strncat(fname, "/", g_cwdLen);
		strncat(fname + 1 + g_cwdLen, g_gameTexesPaths[i], g_cwdLen);
		// NOLINTEND

		g_gameTexesData[i] = stbi_load(fname, &g_gameTexesW[i], &g_gameTexesH[i], NULL, STBI_rgb_alpha);
		printf("Attempted loading `%s`, width `%d`, height `%d`...\n", g_gameTexesPaths[i], g_gameTexesW[i], g_gameTexesH[i]);
	}

	// Check and free!...:
	for (int i = 0; i < GAME_TEX_TOTAL; ++i) {

		void *ptr = g_gameTexesData[i];
		ifl(ptr) {

			// You can set these HERE, but can generate a mipmap *only* after binding, yes:
			ERRGL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
			ERRGL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
			ERRGL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
			ERRGL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

			ERRGL(glBindTexture(GL_TEXTURE_2D, g_gameTexesGl[i]));
			ERRGL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, g_gameTexesW[i], g_gameTexesH[i], 0, GL_RGBA, GL_UNSIGNED_BYTE, ptr));
			ERRGL(glGenerateMipmap(GL_TEXTURE_2D));
			stbi_image_free(ptr);

		} else {

			printf("Failed to load texture `%s`.\n", g_gameTexesPaths[i]);

		}

	}

	ERRGL(glBindTexture(GL_TEXTURE_2D, g_gameTexesGl[GAME_TEX_NULL]));
}

void gameSetup(void) {
	gameQuadsInit();
	ctx = gameQuadsCtxAlloc();
	ERRGL(glGenBuffers(1, &ctx->vbo));
	ERRGL(glGenVertexArrays(1, &ctx->vao));

	game_quad_t quads[1];
	gameQuadsCtxInit(ctx);
	gameQuadsCreate(ctx, quads, 1);
	// gameQuadsDestroy(ctx, quads, 1);
	smlVec3Set(&ctx->positions[quads[0]], 0, 0, 0);
}

void gameDraw(void) {
	static int frameCount = 0;
	static enum GameTex tex = 0;

	ifu(frameCount % 75 == 0) {

		++tex;

		ifu(tex == GAME_TEX_TOTAL) {

			tex = GAME_TEX_NULL;

		}

		ctx->textures[0] = tex;

	}

	ERRGL(glClearColor(0.8f, 0.6f, 1.0f, 0.1f));
	ERRGL(glClear(GL_COLOR_BUFFER_BIT));
	gameQuadsCtxDraw(ctx);
	++frameCount;
}

int main(int const p_count, char const **p_args) {
	glfwInit();
	glfwSwapInterval(0);
	g_window1 = glfwCreateWindow(g_window1WDef, g_window1HDef, "Game", NULL, NULL);
	glfwSetKeyCallback(g_window1, gameWindow1CbckKey);

	ifl(getcwd(g_cwd, sizeof(g_cwd)) != NULL) {

		printf("Current working directory: `%s`.\n", g_cwd);
		g_cwdLen = strlen(g_cwd);

	} else {

		perror("Failed to `getcwd()` the current working directory.\n");
		exit(GAME_EXIT_GET_CWD);

	}

	glfwMakeContextCurrent(g_window1);
	gladLoadGL(glfwGetProcAddress);
	gameWindow1UpdateVars();
	gameTexesLoad();
	gameSetup();

	whilel(!glfwWindowShouldClose(g_window1)) {

		glfwPollEvents();
		gameWindow1UpdateVars();
		ERRGL(glViewport(0, 0, g_window1Wfb, g_window1Hfb));

		gameDraw();
		glfwSwapBuffers(g_window1);

	}

	glfwDestroyWindow(g_window1);
	glfwTerminate();
}
