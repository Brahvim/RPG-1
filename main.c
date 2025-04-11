#pragma region // Headers.
#pragma region // Not my headers!
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <GL/gl.h>
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

void gameExit(int const p_reason) {
	exit(p_reason);
}

void gameTexesLoad(void) {

	for (int i = 0; i < GAME_TEX_TOTAL; ++i) {

		char fname[FILENAME_MAX];
		memset(fname, 0, FILENAME_MAX);
		strncat(fname, g_cwd, g_cwdLen);
		strncat(fname, "/", g_cwdLen);
		strncat(fname + 1 + g_cwdLen, g_gameTexesPaths[i], g_cwdLen);

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

			free(ptr);

		}

	}
}

void glDrawTrigs(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBegin(GL_TRIANGLES);

	glVertex2f(0, 0);
	glVertex2f(0, 100);
	glVertex2f(100, 0);
	glEnd();
}

int main(int const p_count, char const **p_args) {
	glfwInit();
	glfwSwapInterval(0);
	g_window1 = glfwCreateWindow(100, 100, "Game", NULL, NULL);

	ifl(getcwd(g_cwd, sizeof(g_cwd)) != NULL) {

		printf("Current working directory: `%s`.\n", g_cwd);
		g_cwdLen = strlen(g_cwd);

	} else {

		perror("Failed to `getcwd()` the current working directory.\n");
		gameExit(GAME_EXIT_GET_CWD);

	}

	gameTexesLoad();
	gameWindow1UpdateVars();
	glfwMakeContextCurrent(g_window1);

	while (!glfwWindowShouldClose(g_window1)) {

		glfwPollEvents();
		gameWindow1UpdateVars();

		glViewport(0, 0, g_window1FbW, g_window1FbH);
		glMatrixMode(GL_PROJECTION); glLoadIdentity();
		glOrtho(0, g_window1FbW, 0, g_window1FbH, -1, 1); // "L, R, Bot, Top, Near, Far"!
		glMatrixMode(GL_MODELVIEW); glLoadIdentity();

		glDrawTrigs();
		glfwSwapBuffers(g_window1);

	}

	glfwDestroyWindow(g_window1);
	gameTexesFree();
	glfwTerminate();
}
