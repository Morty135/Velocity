#ifndef PLAYER_H
#define PLAYER_H


#include <raylib.h>
#include <raymath.h>

#include <iostream>

#include "input.h"

class player
{
private:
    // animation
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

    input inputManager;

    // collider
    Vector2 colliderSize = {8, 24};
    Vector2 colliderOffset = {0, 4};
    float colliderScale = 4.0f;

    // the scale is the same for all
    Vector2 colliderSizeUpper = {8, 12};
    Vector2 colliderOffsetUpper = {0, -2};

    Vector2 colliderSizeLower = {8, 12};
    Vector2 colliderOffsetLower = {0, 10};

    Rectangle getCollisionRec();

    // movement
    float velocity;
    bool canJump;

    bool wallCheckLeft = false;
    bool wallCheckRight = false;
    bool groundCheck = false;

    float gravity = 2700.0f;
    float jumpForce = 770.0f;
    float speed = 470.0f;

    void VerticalCollision();
    void collision();


public:

    Rectangle* collisionRecs = nullptr;
    int collisionRecsLenght = 0;

    Vector2 position = {0, 0};

    player();
    ~player();

    void draw();
};

#endif