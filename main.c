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

GLchar const *const svsrc =
"#version 330 core" \
"layout (location = 0) in vec2 in_position;" \
"layout (location = 1) in vec2 in_uv;" \
"void main() {" \
"    gl_Position = vec4(in_position, 0.0, 1.0);" \
"}";

GLchar const *const sfsrc =
"#version 330 core" \
"out vec4 o_fragColor;" \
"void main() {" \
"    gl_FragColor = vec4(1.0, 0.0, 1.0, 1.0);" \
"}";

int svlen = 0, sflen = 0;

void gameSetup() {
	GLfloat data[] = {

		-0.5f, -0.5f, // V
		+0.0f, +0.0f, // T

		-0.5f, +0.5f, // V
		+0.0f, +0.0f, // T

		+0.5f, -0.5f, // V
		+0.0f, +0.0f, // T

		+0.5f, +0.5f, // V
		+0.0f, +0.0f, // T

	};

	GLuint vao, vbo, tex;
	GLuint pgl = glCreateProgram();
	GLuint svgl = glCreateShader(GL_VERTEX_SHADER);
	GLuint sfgl = glCreateShader(GL_FRAGMENT_SHADER);

	glGenBuffers(1, &vbo);
	glGenTextures(1, &tex);
	glGenVertexArrays(1, &vao);
	glGenTextures(GAME_TEX_TOTAL, g_gameTexesGl);

	svlen = strlen(svsrc);
	sflen = strlen(sfsrc);

	glShaderSource(svgl, 1, &svsrc, &svlen);
	glShaderSource(sfgl, 1, &sfsrc, &sflen);

	glAttachShader(pgl, svgl);
	glAttachShader(pgl, sfgl);

	glCompileShader(svgl);
	glCompileShader(sfgl);

	// GLsizei lens[10];
	// GLchar buf[BUFSIZ];
	// glGetShaderInfoLog(GL_VERTEX_SHADER, BUFSIZ, lens, buf);
	// printf("Vertex shader log: %s.\n", buf);
	// buf = { 0 };
	// glGetShaderInfoLog(GL_FRAGMENT_SHADER, BUFSIZ, lens, buf);
	// printf("Fragment shader log: %s.\n", buf);

	glLinkProgram(pgl);
	glUseProgram(pgl);

	// glActiveTexture(GL_TEXTURE1);
	// glUniform1i(glGetUniformLocation(sfgl, "u_tex"), GL_TEXTURE1 - GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, g_gameTexesW[0], g_gameTexesH[0], 0, GL_RGBA, GL_UNSIGNED_BYTE, g_gameTexes[0]);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*) (2 * sizeof(GLfloat)));
}

void gameDraw() {
	glClearColor(0.8f, 0.6f, 1.0f, 0.1f);
	glClear(GL_COLOR_BUFFER_BIT);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void gameExit(int const p_reason) {
	exit(p_reason);
}

void gameTexesLoad(void) {

	for (int i = 0; i < GAME_TEX_TOTAL; ++i) {

		char fname[FILENAME_MAX];
		// NOLINTBEGIN
		memset(fname, 0, FILENAME_MAX);
		strncat(fname, g_cwd, g_cwdLen);
		strncat(fname, "/", g_cwdLen);
		strncat(fname + 1 + g_cwdLen, g_gameTexesPaths[i], g_cwdLen);
		// NOLINTEND

		g_gameTexes[i] = stbi_load(fname, &g_gameTexesW[i], &g_gameTexesH[i], 0, STBI_rgb_alpha);

	}

	// CHECK!:
	for (int i = 0; i < GAME_TEX_TOTAL; ++i) {

		ifu(!g_gameTexes[i]) {

			printf("Failed to load texture `%s`.\n", g_gameTexesPaths[i]);

		}

	}
}

void gameTexesFree(void) {
	for (int i = 0; i < GAME_TEX_TOTAL; ++i) {

		void *ptr = g_gameTexes[i];
		ifl(ptr) {

			stbi_image_free(ptr);

		}

	}
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

		gameDraw();

		glfwSwapBuffers(g_window1);

	}

	glfwDestroyWindow(g_window1);
	gameTexesFree();
	glfwTerminate();
}
