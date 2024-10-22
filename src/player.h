#ifndef PLAYER_H
#define PLAYER_H


#include <raylib.h>
#include <raymath.h>

#include <iostream>

#include "playerAnimation.h"

class player
{
private:
    float gravity = 100.5f;
    float defaultGravity;

    playerAnimation anim;

public:
    Texture2D playerSprites[2];
    float playerSize = 4.0;

    Vector2 position = {0,0};
    Vector2 velocity = {0,0};
    Vector2 maxVelocity = {12, 100};
    float movementSpeed = 80.0f;
    float jumpForce = 20;
    float horizontalDampening = 25;

    bool groundCheck = true;

    Rectangle collisonRec = {position.x-32, position.y - 64 ,64,128};

    player();
    ~player();

    void draw();

    void collisionCheck(Rectangle *envItems, int envRecsLenght);
};

#endif