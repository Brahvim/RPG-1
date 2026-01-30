#pragma once
#include "Sml.h"

#pragma region // 2D Cam.

void camera2dUpdate(void);
extern float g_camera2dRot;
extern struct SmlVec2 g_camera2dPos;
extern struct SmlMat44 g_camera2dTransf;

#pragma endregion 
