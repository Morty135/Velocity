#ifndef PLAYER_H
#define PLAYER_H


#include <raylib.h>
#include <raymath.h>

#include <iostream>

#include "input.h"

class player
{
private:

    Vector2 velocity = {0,0};
    Vector2 maxVelocity = {0.0f, 0.0f};
    float wallJumpCooldown = 0.4f;

    float wallJumpTimer = 0.0f;
    float maxHorizontalVelocitySlow = 8.0f;
    float maxHorizontalVelocityFast = 12.0f;
    float maxVelocityYFall = 70.0f;
    float maxVelocityYWall = 5.0f;
    float movementSpeed = 80.0f;
    float jumpForce = 15;
    float horizontalDampening = 25;
    float defaultGravity = 70.5f;

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

    Rectangle getCollisionRec();

    void horizontalCollision();
    void verticalCollision();

    Rectangle* collisionRecs = nullptr;
    int collisionRecsLenght = 0;

    //misc
    bool groundCheck = true;
    bool wallCheckLeft = false;
    bool WallCheckRight = false;
    float gravity = 0.0f;
public:

    Vector2 position = {0, 0};

    player(Rectangle* collisionRecs, int collisionRecsLength);
    ~player();

    void draw();
};

#endif