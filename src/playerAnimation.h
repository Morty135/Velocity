#ifndef PLAYERANIMATION_H
#define PLAYERANIMATION_H

#include <raylib.h>
#include <iostream>

class playerAnimation
{
    private:

    int pathsLenght = 2;

    Texture2D animations[2];

    const char* animationPaths[2] = {
        "resources/player/run.png",
        "resources/player/idle.png"
    };

    Vector2* playerVelocity;

    public:

    playerAnimation(Vector2* playerVelocity);
    ~playerAnimation();

    void animate();

    void idleAnimation();
    void runAnimation();
};



#endif