#ifndef MAINCAMERA_H
#define MAINCAMERA_H


#include <raylib.h>
#include <raymath.h>
#include <iostream>

#include "input.h"

class mainCamera
{
private:
    input inputManager;

    Camera2D camera = { 0 };
    Vector2 currentCameraPos = {0.0f, 0.0f};
    float currentCameraZoom = 1.0;

public:
    Vector2* targetPos = nullptr;

    mainCamera();
    ~mainCamera();

    Camera2D update();
};

#endif