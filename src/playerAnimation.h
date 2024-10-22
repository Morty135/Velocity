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
    float frameDelay = 0.07f;
    float frameTime;

    Texture2D animations[2];

    const char* animationPaths[2] = {
        "resources/player/run.png",
        "resources/player/idle.png"
    };

    Vector2* playerVelocity;
    Vector2* playerPosition;

    void idleAnimation();
    void runAnimation();
    
    public:

    playerAnimation(Vector2* playerVelocity, Vector2* playerPosition);
    ~playerAnimation();

    void animate();
};



#endif