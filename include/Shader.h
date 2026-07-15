#pragma once
#include "Gl.h"
#include "Sml.h"
#include "List.h"
#include <stdio.h>
#include <stddef.h>

struct Shader;

struct ShaderProgram {

	struct Shader vert;
	struct Shader frag;

};

// Let's be honest, an AoS ***will* do** here.
struct ShaderStore {

	GLuint *g_shaderGlIds;

	char **g_shaderPathsVert;
	char **g_shaderPathsFrag;

	GLuint *g_shaderGlIdsVert;
	GLuint *g_shaderGlIdsFrag;

	GLchar **g_shaderSourcesVert;
	GLchar **g_shaderSourcesFrag;

	size_t *g_shaderPathLengthsVert;
	size_t *g_shaderPathLengthsFrag;

	GLint *g_shaderSourceLengthsVert;
	GLint *g_shaderSourceLengthsFrag;

};

struct Shader {

	size_t len;
	char *src;
	GLuint gl;

};
