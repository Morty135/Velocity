#include "playerAnimation.h"



playerAnimation::playerAnimation(Vector2* playerVelocity, Vector2* playerPosition)
{
    this->playerVelocity = playerVelocity;
    this->playerPosition = playerPosition;
    for (size_t i = 0; i < pathsLenght; i++)
    {
        animations[i] = LoadTexture(animationPaths[i]);
    }
    
}



playerAnimation::~playerAnimation()
{
    for (size_t i = 0; i < pathsLenght; i++)
    {
        UnloadTexture(animations[i]);
    }
    
}



void playerAnimation::animate()
{
    if(playerVelocity->x < -0.05f || playerVelocity->x > 0.05f)
    {
        void runAnimation();
    }
    if(playerVelocity->x <= 0.05f && playerVelocity->x >= -0.05f)
    {
        void idleAnimation();
    }
}



void playerAnimation::idleAnimation()
{
    float frameWidth = (float)animations[0].width/8;
    Rectangle frameRec = { 0.0f, 0.0f, frameWidth, (float)animations[0].height};


    frameTime += GetFrameTime();

    if(frameTime > frameDelay)
    {
        frameTime = 0;
        frameOffset++;
    }
    frameRec = { 0.0f + frameWidth * frameOffset, 0.0f, frameWidth, 32.0f};

    Rectangle destRec = { playerPosition->x, playerPosition->y, frameRec.width * playerSize, frameRec.height * playerSize };

    Vector2 origin = {32.0f, 64.0f };
    DrawTexturePro(animations[0], frameRec, destRec, origin, 0.0f, WHITE);
}



void playerAnimation::runAnimation()
{
    float frameWidth = (float)animations[0].width/8;
    Rectangle frameRec = { 0.0f, 0.0f, frameWidth, (float)animations[0].height};


    frameTime += GetFrameTime();

    if(frameTime > frameDelay)
    {
        frameTime = 0;
        frameOffset++;
    }
    if(playerVelocity->x < 0)
    {
        frameRec = { 0.0f + frameWidth * frameOffset, 0.0f, -frameWidth, 32.0f};
    }
    else
    {
        frameRec = { 0.0f + frameWidth * frameOffset, 0.0f, frameWidth, 32.0f};
    }

    Rectangle destRec = { playerPosition->x, playerPosition->y, frameRec.width * playerSize, frameRec.height * playerSize };

    Vector2 origin = {32.0f, 64.0f };
    DrawTexturePro(animations[0], frameRec, destRec, origin, 0.0f, WHITE);
}