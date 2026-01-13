#ifndef MAINCAMERA_H
#define MAINCAMERA_H


#include <raylib.h>
#include <raymath.h>
#include <iostream>

class mainCamera
{
private:
    Camera2D camera = { 0 };
    Vector2 currentCameraPos = {0.0f, 0.0f};
    float currentCameraZoom = 1.0;

    Vector2 lastTargetPos = {0.0f, 0.0f};

public:
    Vector2* targetPos = nullptr;

    mainCamera();
    ~mainCamera();

    Camera2D update();
};

#endif