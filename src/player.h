#ifndef PLAYER_H
#define PLAYER_H


#include <raylib.h>
#include <raymath.h>

#include <iostream>

#include "input.h"

class player
{
private:
    Rectangle* collisionRecs = nullptr;
    int collisionRecsLenght = 0;

    float gravity = 100.5f;
    float defaultGravity;

    void animator();

    void animation(int animationIndex, float frameDelay = 0.1f);

    float playerSize = 4;

    int frameOffset = 0;
    int pathsLenght = 2;
    double frameTime;

    //in pixels
    float frameWidth = 16;

    int animationsLenght = 2;

    Texture2D animations[2];

    const char* animationPaths[2] = {
        "resources/player/runDebug.png",
        "resources/player/idle.png"
    };

    Rectangle frameRec = { 0.0f , 0.0f, frameWidth, 32.0f};

    void horizontalCollision();
    void verticalCollision();

    input inputManager;

    float maxHorizontalVelocitySlow = 8.0f;
    float maxHorizontalVelocityFast = 12.0f;
public:
    Vector2 position = {0,0};
    Vector2 velocity = {0,0};
    Vector2 maxVelocity = {12, 100};
    float movementSpeed = 80.0f;
    float jumpForce = 20;
    float horizontalDampening = 25;

    bool groundCheck = true;

    Rectangle collisionRec = {position.x, position.y, 48, 128};

    player(Rectangle* collisionRecs, int envRecsLength);
    ~player();

    void draw();
};

#endif