#include <stb/stb_image.h>
#include <glad/gles2.h>
#include <unistd.h>
#include <memory.h>
#include <stdio.h>

#include "UtilMacros.h"
#include "UtilGl.h"
#include "Assets.h"

char g_cwd[FILENAME_MAX];
size_t g_cwdLen = FILENAME_MAX;
int g_textureWidths[TEXTURES_TOTAL];
int g_textureHeights[TEXTURES_TOTAL];
GLuint g_textureGlIds[TEXTURES_TOTAL];
char const *g_texturePaths[TEXTURES_TOTAL] = {

	"assets/null.png",
	"assets/test0.png",

};
unsigned char *g_texturesBytes[TEXTURES_TOTAL];

GLint loadShader(GLchar const **p_buffer, char const *p_path) {
	FILE *file = fopen(p_path, "rb");

	if (unlikely(!file)) {

		return -1;

	}

	fseek(file, 0, SEEK_END);
	GLint const length = ftell(file);

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
	ERRGL(glActiveTexture(GL_TEXTURE0));
	ERRGL(glGenTextures(TEXTURES_TOTAL, g_textureGlIds));

	for (unsigned int i = 0; i < TEXTURES_TOTAL; ++i) {

		char fname[FILENAME_MAX];
		// NOLINTBEGIN
		memset(fname, 0, FILENAME_MAX);
		strncat(fname, g_cwd, g_cwdLen);
		strncat(fname, "/", g_cwdLen);
		strncat(fname + 1 + g_cwdLen, g_texturePaths[i], g_cwdLen);
		// NOLINTEND

		g_texturesBytes[i] = stbi_load(fname, &g_textureWidths[i], &g_textureHeights[i], NULL, STBI_rgb_alpha);
		printf("Attempted loading `%s`, width `%d`, height `%d`...\n", g_texturePaths[i], g_textureWidths[i], g_textureHeights[i]);
	}

	// Check and free!...:
	for (unsigned int i = 0; i < TEXTURES_TOTAL; ++i) {

		void *ptr = g_texturesBytes[i];
		if (likely(ptr)) {

			// You can set these HERE, but can generate a mipmap *only* after binding, yes:
			ERRGL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
			ERRGL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
			ERRGL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
			ERRGL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

			ERRGL(glBindTexture(GL_TEXTURE_2D, g_textureGlIds[i]));
			ERRGL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, g_textureWidths[i], g_textureHeights[i], 0, GL_RGBA, GL_UNSIGNED_BYTE, ptr));
			ERRGL(glGenerateMipmap(GL_TEXTURE_2D));
			stbi_image_free(ptr);

		}
		else {

			fprintf(stderr, "Failed to load texture `%s`.\n", g_texturePaths[i]);

		}

	}

	ERRGL(glBindTexture(GL_TEXTURE_2D, g_textureGlIds[TEXTURES_NULL]));
	puts("Textures ready to go!");
}

void loadCwd(void) {
	if (likely(getcwd(g_cwd, sizeof(g_cwd)) != NULL)) {

		printf("Current working directory: `%s`.\n", g_cwd);
		g_cwdLen = strlen(g_cwd);

	}
	else {

		perror("Failed to `getcwd()` the current working directory.\n");
		exit(1);

	}
}
