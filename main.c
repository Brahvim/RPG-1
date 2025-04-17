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
#include "game/graphics.h"
#include "game/window1.h"
#pragma endregion

GLenum g_errorGl;
char g_cwd[FILENAME_MAX];
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

			// You can set these HERE, but can generate a mipmap *only* after binding, yes:
			ERRORGL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
			ERRORGL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
			ERRORGL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
			ERRORGL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

			ERRORGL(glBindTexture(GL_TEXTURE_2D, g_gameTexesGl[i]));
			ERRORGL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, g_gameTexesW[i], g_gameTexesH[i], 0, GL_RGBA, GL_UNSIGNED_BYTE, g_gameTexesData[i]));
			ERRORGL(glGenerateMipmap(GL_TEXTURE_2D));

			stbi_image_free(ptr);

		} else {

			printf("Failed to load texture `%s`.\n", g_gameTexesPaths[i]);

		}

	}

	ERRORGL(glBindTexture(GL_TEXTURE_2D, g_gameTexesGl[GAME_TEX_NULL]));
}

void gameSetup(void) {
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
	GLint const svlen = gameShaderFromFile(&svsrc, "shader.vert");
	GLint const sflen = gameShaderFromFile(&sfsrc, "shader.frag");

	ERRORGL(glShaderSource(svgl, 1, &svsrc, &svlen));
	ERRORGL(glShaderSource(sfgl, 1, &sfsrc, &sflen));

	ERRORGL(glCompileShader(svgl));
	ERRORGL(glCompileShader(sfgl));

	// Attach *after* compilation:
	ERRORGL(glAttachShader(pgl, svgl));
	ERRORGL(glAttachShader(pgl, sfgl));

	GLchar slogBuf[16384]; GLsizei slogLen = 16384, slogStrlen;

	memset(slogBuf, 0, slogLen); // NOLINT
	ERRORGL(glGetShaderInfoLog(svgl, 16384, &slogLen, slogBuf));
	printf("Vertex shader log: %s.\n", slogBuf);

	memset(slogBuf, 0, slogLen); // NOLINT
	ERRORGL(glGetShaderInfoLog(sfgl, 16384, &slogLen, slogBuf));
	printf("Fragment shader log: %s.\n", slogBuf);

	memset(slogBuf, 0, slogLen); // NOLINT
	ERRORGL(glGetProgramInfoLog(pgl, 16384, &slogLen, slogBuf));
	printf("Program log: %s.\n", slogBuf);

	ERRORGL(glLinkProgram(pgl));
	ERRORGL(glUseProgram(pgl));

	ERRORGL(glBindVertexArray(vao));
	ERRORGL(glBindBuffer(GL_ARRAY_BUFFER, vbo));

	ERRORGL(glActiveTexture(GL_TEXTURE0));
	enum GameTex const tex = GAME_TEX_NULL;

	// float const time = (float) glfwGetTime();
	// float const angleY = sinf(time), angleZ = cosf(time);

	// float mat[16] = {

	// 	+cosf(angleZ),	-sinf(angleZ), 	0.2f * +sinf(angleY),	0.0f,
	// 	+sinf(angleZ),	+cosf(angleZ), 	0.2f * +cosf(angleY),	0.0f,
	// 	0.0f,			0.0f, 			1.0f, 					0.0f,
	// 	0.0f, 			0.0f,			0.0f, 					1.0f,

	// };

	float mat[16] = {

		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f,

	};

	ERRORGL(glBindTexture(GL_TEXTURE_2D, g_gameTexesGl[tex]));
	ERRORGL(glUniform1i(glGetUniformLocation(pgl, "u_tex"), 0));
	ERRORGL(glUniformMatrix4fv(glGetUniformLocation(pgl, "u_transform"), 1, GL_TRUE, mat));
	ERRORGL(glUniform2f(glGetUniformLocation(pgl, "u_texRes"), g_gameTexesW[tex], g_gameTexesH[tex]));

	ERRORGL(glEnableVertexAttribArray(0));
	ERRORGL(glEnableVertexAttribArray(1));
	ERRORGL(glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW));
	ERRORGL(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0));
	ERRORGL(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*) (2 * sizeof(GLfloat))));
}

void gameDraw(void) {
	static int frameCount = 0;
	static enum GameTex tex = 0;

	ifu(frameCount % 75 == 0) {

		++tex;

		ifu(tex == GAME_TEX_TOTAL) {

			tex = GAME_TEX_NULL;

		}

		ERRORGL(glBindTexture(GL_TEXTURE_2D, g_gameTexesGl[tex]));

	}

	ERRORGL(glClearColor(0.8f, 0.6f, 1.0f, 0.1f));
	ERRORGL(glClear(GL_COLOR_BUFFER_BIT));
	ERRORGL(glDrawArrays(GL_TRIANGLE_STRIP, 0, 4));
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
		ERRORGL(glViewport(0, 0, g_window1Wfb, g_window1Hfb));

		gameDraw();

		glfwSwapBuffers(g_window1);

	}

	glfwDestroyWindow(g_window1);
	glfwTerminate();
}
