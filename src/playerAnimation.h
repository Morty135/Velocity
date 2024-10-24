#ifndef PLAYERANIMATION_H
#define PLAYERANIMATION_H

#include <raylib.h>
#include <iostream>

class playerAnimation
{
    private:

    float playerSize = 4;

    int frameOffset = 0;
    int pathsLenght = 2;
    float frameDelay = 0.1f;
    float frameTime;

    //in pixels
    float frameWidth = 16;

    Texture2D animations[2];

    const char* animationPaths[2] = {
        "resources/player/runDebug.png",
        "resources/player/idle.png"
    };

    Vector2* playerVelocity;
    Vector2* playerPosition;

    Rectangle frameRec = { 0.0f , 0.0f, frameWidth, 32.0f};

    void animation(int animationIndex);
    
    public:

    playerAnimation(Vector2* playerVelocity, Vector2* playerPosition);
    ~playerAnimation();

    void animate();
};



#endif