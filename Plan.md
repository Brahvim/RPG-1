# RPG-1  
*Bit of a game framework, let's be honest!*  
  
# The Plan!:  

## Windowing:  
  
I'm thinking windows should work like this:  
```c
struct Window { /* ... */ };
struct List g_windowList;
size_t windowGetIndex();
struct Window windowGet();
struct Window windowSet(struct Window const *const window);

// Optionally:
typdef void (*cbck_window_changed_t)(void);
struct List g_windowCbckChangedListeners;
```
That's it.  
`windowSet()` could also set GL ctx.  
No other getters or setters required.  
Even this is overblown with that listener.

## Cameras:

As for cameras, a `struct Camera` that holds its parent window's ID to get viewport info, a `struct SmlMat44` for transforms - rather a pointer to a function that *returns* that.  
We could batch these into a list, but cameras also have the "permutations problem" where every camera is *very* unique, so having a list for their update calls and whatnot is a bad idea. A "more open" system would be one that takes an array of `enum CameraUpdateType`s, but that's *constrained* on purpose. A better method is to simply have one `struct SmlMat44 g_cameraCurrentTransform` that all renderers use - which is *essentially* what I have right now.  
I could perhaps add a camera-"vtable" to the current system to define an interface for cameras, but independent `struct Camera*`s would probably be fine alone. Fitting combinations into models is *hard.*  
...And I already have `struct SmlMat44* cameraMakeLookAt()`, `struct SmlMat44* cameraMakeOrtho()`, `struct SmlMat44* cameraMakePersp()`, `struct SmlMat44* cameraMake2d()`...

## Resources:

Resources are gunna be a *long* one. I'll see. For "efficient loading" of resources, threads are needed, but making the systems threaded is *vastly* more complex compared to making parts of the system that can *fit into* any threading library, be it pthread, SDL_Thread, etc.

## Render:

The renderer is gunna be a fun one.  
All I can really think of is a `struct MeshRendererInstanced` and `struct Mesh` *alongside it,* perhaps. Perhaps a more "straightforward" version of this, but because you can *totally* choose to store a single `struct Mesh` in one of these, I think it's useless to make that "straightforward version". Will have to make shaders etc. swappable, though. *MDI,* someday.

### **("Straightforward" a.k.a. "non-instanced" drawcall-per-object rendering.)**
### **("MDI" refers to *Multi-Draw-Instanced* and co.)**


## "Named-Arrays":
My current worry is making a dynamic texture system, TBH, threading contracts *aside* (probably not too difficult if we see it as just parallelizable, locked-and-fenced *classic* **async**).  
  
Current system simply uses some macro tricks to keep everything 100% static:  
```c
static void atlasReverseMapNames(enum AtlasName const p_atlas, long long *const p_indices) {
    for (size_t i = 0; i < TEXTURE_TOTAL; ++i) {

        g_atlasTextureIndices[p_atlas] = p_indices;

        for (size_t j = 0; j < g_atlasTextureCounts[p_atlas]; j++) {

            if (i == g_atlasTextureNames[p_atlas][j]) {

                g_atlasTextureIndices[p_atlas][i] = j;
                break;

            }

        }

    }
}

void loadMappedAtlases() {
#define M(p_enum, ...) { \
        static enum TextureName names[] = { __VA_ARGS__ }; \
        static long long indices[TEXTURE_TOTAL] = { 0 }; \
        g_atlasTextureCounts[p_enum] = sizearr(names); \
        memset(indices, -1, sizeof(indices)); \
        g_atlasTextureNames[p_enum] = names; \
        atlasReverseMapNames(p_enum, indices); \
        atlasCreate(p_enum); \
    }

    M(ATLAS_DEFAULT,

    TEXTURE_GRID,
    TEXTURE_BLACK,
    TEXTURE_WHITE,
    TEXTURE_MISSING,

    );

#undef M
}
```  
This is *very fragile* for **porting.**  
A rewrite is *definitely* a necessity.  
  
The idea behind the new system is to be dynamic, *"but **fakefully**",* however...!  
What I mean to say is: it may be dynamic, but it should NOT be without identity.  
One should NOT need to use strings and hashes to identify things.  
Games are a LOT more static than that.  
In fact, it shouldn't even be "a dynamic system", really...  
Think of a `struct MyAtlas { struct Texture myTex1; /* ... */ struct Texture myTexN; } *myAtlas;` that is passed like `struct Texture texture10 = textureLoad(((struct Texture*) &myAtlas)[offsetof(struct MyAtlas, myTex9)])`.  
*Literally,* a named array.

### **(PS `struct Texture` doesn't actually need to store data. It can store *handles* TO data.)**

## Streaming:
Streaming / dynamic, threaded loading shouldn't "break" anything TBH.  
Why would it?  
**We don't even know the requirements for those systems yet.**  
Plus, keeping I/O costs *low* is actually a very good idea.  
Streaming can be unreliable for a lot of games, I say...  
  
Anyway. *Shaders.*  
I think shaders would be *okay* being... globally-stored *objects.*  
`struct Shader` with source code, GL handle, et cetera...  
One thing worth noting is that they'd have to be a part of a `struct Window` since... *OpenGL.*  
If not that, we're still *most likely* **going to** have to separate the GL handle in some way.  
A map would be useful but since we *also* have compile-time identity a map is *literally* unnecessary.  
  
Lastly, we can have a `struct ScreenSpaceShaderPass` that draws a quad and runs a custom program for it. There *will be* a vertex-shader *default* inside it, but of course, also no restrictions.  

### ...I think that's everything covered.

Audio is OpenAL [Soft]. Game data structures will be made in a similar way to this "underlying" *"engine",* of course.
