#ifndef PLAYERCAMERA_H
#define PLAYERCAMERA_H


#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include "player.h"

class playerCamera
{
private:
    Vector2* playerPos;

public:
    Camera2D camera = { 0 };
    Vector2 currentCameraPos;
    float currentCameraZoom = 1.0;

    playerCamera(Vector2* playerPos);
    ~playerCamera();

    Camera2D update();
};

#endif