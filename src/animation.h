#ifndef ANIMATION_H
#define ANIMATION_H

#include <raylib.h>

class animation
{
private:
    Rectangle frameRec;
    int frameSpeed;

public:
    animation(float frameWidht, float frameHeight, const char* sourceFile, int numOfFrames);
    ~animation();

    void animate(float speed);
};

#endif