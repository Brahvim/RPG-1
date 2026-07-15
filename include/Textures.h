#pragma once
#include "Gl.h"
#include "Sml.h"
#include "List.h"
#include <stddef.h>

typedef unsigned char pixel_t;

struct TextureStore {

	pixel_t **images;
	size_t capacity;
	size_t count;
	int *heights;
	int *widths;

};

struct Texture {

	pixel_t *image;
	int channel;
	int height;
	int width;

};

struct Atlas {

	// size_t count;       // ...of *textures* in the atlas!

	// 4 bytes each!:
	int width;			// ...of the atlas.
	int height;			// ...of the atlas.
	GLuint glTextureId;	// ...of the atlas!

	// These last 2 are all 8 bytes:

	struct Rect *rects; // `x`, `y`, `w`, `h`. Ordered like `Atlas::textures`!
	struct TextureStore *textures; // What textures does thou hold...?!

};

struct TextureStore* textureStoreCreate();
struct Texture textureStoreRemove(size_t const id);
// struct TextureStore* textureStoreDelete(struct textureStore const *const store);
struct TextureStore* textureStoreAppend(struct TextureStore const *const store, struct Texture const *const texture);
