#ifndef PLAYER_H
#define PLAYER_H


#include <raylib.h>
#include <raymath.h>

#include <iostream>

class player
{
private:
    float defaultGravity;

    void playerAnimator();

public:
    Texture2D playerSprites[2];
    float playerSize = 4.0;

    Vector2 position = {0,0};
    Vector2 velocity = {0,1};
    Vector2 maxVelocity = {12, 100};
    float movementSpeed = 100.0f;
    float jumpForce = 20;
    float gravity = 3.5f;
    float horizontalDampening = 0.5f;

    bool groundCheck = true;

    Rectangle collisonRec = {position.x-32, position.y - 64 ,64,128};


    player();
    ~player();

    void draw();

    void collisionCheck(Rectangle *envItems, int envRecsLenght);
};

#endif