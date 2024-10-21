#ifndef MAINCAMERA_H
#define MAINCAMERA_H


#include <raylib.h>
#include <raymath.h>
#include <iostream>

class mainCamera
{
private:
    Vector2* targetPos;

public:
    Camera2D camera = { 0 };
    Vector2 currentCameraPos;
    float currentCameraZoom = 1.0;

    mainCamera(Vector2* targetPos);
    ~mainCamera();

    Camera2D update();
};

#endif