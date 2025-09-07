#include <glad/gles2.h>
#include <stdio.h>
#include "Camera.h"

struct Camera g_camera2d = {

    .update = cameraUpdate2d,
    .transform = &g_cameraTransform2d,

};
float g_cameraRotation2d = 0;
struct Camera *g_camera = &CAMERA_DEFAULT;
struct SmlVec2 g_cameraPosition2d = { 0 };
struct SmlMat44 g_cameraTransform2d = { 0 };

void cameraUpdate2d(void) {
    smlMat44Identity(&g_cameraTransform2d);
    g_cameraTransform2d.r14 = -g_cameraPosition2d.x;
    g_cameraTransform2d.r24 = -g_cameraPosition2d.y;
    smlMat33RotateZ(&g_cameraTransform2d.mat33, -g_cameraRotation2d);
}
