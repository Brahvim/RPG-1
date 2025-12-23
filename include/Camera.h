#pragma once
#include "Sml.h"

// Uhhh, not at ALL batch-friendly, but *hey*, how many cameras will you use at once in a single-screen game?:
struct Camera {

    void (*update)(void);
    struct SmlMat44 *transform;

};

extern struct Camera g_camera2d;
extern float g_cameraRotation2d;
extern struct SmlVec2 g_cameraPosition2d;
extern struct SmlMat44 g_cameraTransform2d;

void cameraUpdate2d(void);
void cameraInitSystem(void);
void cameraUploadUbo(struct Camera const *const camera);
