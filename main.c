#pragma region // Headers.
#pragma region // Not my headers!
#include "glad.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <AL/al.h>

#include "stb/stb_image.h"

#define STB_VORBIS_HEADER_ONLY
#include "stb/stb_vorbis.h"
#pragma endregion

#include "ifs.h"
#include "game/main.h"
#include "game/window1.h"
#pragma endregion

char g_cwd[FILENAME_MAX];
size_t g_cwdLen = FILENAME_MAX;

GLint shRead(GLchar const** buffer, char const *path);
GLint shRead(GLchar const** p_buffer, char const *p_path) {
	GLint read = 0;
	GLint next = 4096;
	FILE *file = fopen(p_path, "r");
	char *buffer = calloc(4096, sizeof(char));

reading:
	for (; read < next && !feof(file); ++read) {

		buffer[read] = fgetc(file);

	}

	if (!feof(file)) {
		buffer = realloc(buffer, sizeof(char) * (next = read + 4096));
		goto reading;
	}

	*p_buffer = buffer;
	return read;
}

char const* glGetErrorString(GLenum error);
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

GLenum errorGl;
#define ERRORGL(x) x;\
if ((errorGl = glGetError()) != GL_NO_ERROR) {\
	printf("OpenGL error `%d` (%s), %s:%d.\n", errorGl, glGetErrorString(errorGl), __FILE__, __LINE__);\
}\

void gameExit(int const p_reason) {
	exit(p_reason);
}

void gameTexesLoad(void) {
	stbi_set_flip_vertically_on_load(1);
	ERRORGL(glActiveTexture(GL_TEXTURE0));
	ERRORGL(glGenTextures(GAME_TEX_TOTAL, g_gameTexesGl));

	for (int i = 0; i < GAME_TEX_TOTAL; ++i) {

		char fname[FILENAME_MAX];
		// NOLINTBEGIN
		memset(fname, 0, FILENAME_MAX);
		strncat(fname, g_cwd, g_cwdLen);
		strncat(fname, "/", g_cwdLen);
		strncat(fname + 1 + g_cwdLen, g_gameTexesPaths[i], g_cwdLen);
		// NOLINTEND

		g_gameTexesData[i] = stbi_load(fname, &g_gameTexesW[i], &g_gameTexesH[i], NULL, STBI_rgb_alpha);
		printf("Loaded texture `%s` with width `%d` and height `%d`.\n", g_gameTexesPaths[i], g_gameTexesW[i], g_gameTexesH[i]);
	}

	// Check and free!...:
	for (int i = 0; i < GAME_TEX_TOTAL; ++i) {

		void *ptr = g_gameTexesData[i];
		ifl(ptr) {

			ERRORGL(glBindTexture(GL_TEXTURE_2D, g_gameTexesGl[i]));
			ERRORGL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, g_gameTexesW[i], g_gameTexesH[i], 0, GL_RGBA, GL_UNSIGNED_BYTE, g_gameTexesData[i]));
			// stbi_image_free(ptr);

		} else {

			printf("Failed to load texture `%s`.\n", g_gameTexesPaths[i]);

		}

	}
}

void gameSetup() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	GLfloat data[] = {

		-0.5f, -0.5f, // V
		+0.0f, +0.0f, // T

		-0.5f, +0.5f, // V
		+0.0f, +1.0f, // T

		+0.5f, -0.5f, // V
		+1.0f, +0.0f, // T

		+0.5f, +0.5f, // V
		+1.0f, +1.0f, // T

	};

	GLuint vao, vbo;
	GLuint pgl = ERRORGL(glCreateProgram());
	GLuint svgl = ERRORGL(glCreateShader(GL_VERTEX_SHADER));
	GLuint sfgl = ERRORGL(glCreateShader(GL_FRAGMENT_SHADER));

	ERRORGL(glGenBuffers(1, &vbo));
	ERRORGL(glGenVertexArrays(1, &vao));

	GLchar const *svsrc, *sfsrc;
	GLint const svlen = shRead(&svsrc, "shader.vert");
	GLint const sflen = shRead(&sfsrc, "shader.frag");

	ERRORGL(glShaderSource(svgl, 1, &svsrc, &svlen));
	ERRORGL(glShaderSource(sfgl, 1, &sfsrc, &sflen));

	ERRORGL(glCompileShader(svgl));
	ERRORGL(glCompileShader(sfgl));

	// Attach *after* compilation:
	ERRORGL(glAttachShader(pgl, svgl));
	ERRORGL(glAttachShader(pgl, sfgl));

	GLchar slogBuf[16384]; GLsizei slogLen = 16384, slogStrlen;

	memset(slogBuf, 0, slogLen);
	ERRORGL(glGetShaderInfoLog(svgl, 16384, &slogLen, slogBuf));
	printf("Vertex shader log: %s.\n", slogBuf);

	memset(slogBuf, 0, slogLen);
	ERRORGL(glGetShaderInfoLog(sfgl, 16384, &slogLen, slogBuf));
	printf("Fragment shader log: %s.\n", slogBuf);

	memset(slogBuf, 0, slogLen);
	ERRORGL(glGetProgramInfoLog(pgl, 16384, &slogLen, slogBuf));
	printf("Program log: %s.\n", slogBuf);

	ERRORGL(glLinkProgram(pgl));
	ERRORGL(glUseProgram(pgl));

	ERRORGL(glBindVertexArray(vao));
	ERRORGL(glGenerateMipmap(GL_TEXTURE_2D));
	ERRORGL(glBindBuffer(GL_ARRAY_BUFFER, vbo));

	ERRORGL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	ERRORGL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	ERRORGL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	ERRORGL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	ERRORGL(glActiveTexture(GL_TEXTURE0));
	enum GameTex const tex = GAME_TEX_NULL;
	ERRORGL(glBindTexture(GL_TEXTURE_2D, g_gameTexesGl[tex]));
	ERRORGL(glUniform1i(glGetUniformLocation(pgl, "u_tex"), 0));
	ERRORGL(glUniform2f(glGetUniformLocation(pgl, "u_texRes"), g_gameTexesW[tex], g_gameTexesH[tex]));

	ERRORGL(glEnableVertexAttribArray(0));
	ERRORGL(glEnableVertexAttribArray(1));
	ERRORGL(glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW));
	ERRORGL(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0));
	ERRORGL(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*) (2 * sizeof(GLfloat))));
}

void gameDraw() {
	ERRORGL(glClearColor(0.8f, 0.6f, 1.0f, 0.1f));
	ERRORGL(glClear(GL_COLOR_BUFFER_BIT));
	ERRORGL(glDrawArrays(GL_TRIANGLE_STRIP, 0, 4));
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
		gameExit(GAME_EXIT_GET_CWD);

	}

	glfwMakeContextCurrent(g_window1);
	gladLoadGL(glfwGetProcAddress);
	gameWindow1UpdateVars();
	gameTexesLoad();
	gameSetup();

	whilel(!glfwWindowShouldClose(g_window1)) {

		glfwPollEvents();
		gameWindow1UpdateVars();
		ERRORGL(glViewport(0, 0, g_window1Wfb, g_window1Hfb));

		gameDraw();

		glfwSwapBuffers(g_window1);

	}

	glfwDestroyWindow(g_window1);
	glfwTerminate();
}
