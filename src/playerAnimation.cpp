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
    if(playerVelocity->x > 0.1)
    {
        frameRec.width = frameWidth;
    }
    else
    {
        frameRec.width = -frameWidth;
    }
    if(playerVelocity->x < -0.15f || playerVelocity->x > 0.15f)
    {
        animation(0);
    }
    if(playerVelocity->x <= 0.15f && playerVelocity->x >= -0.15f)
    {
        animation(1);
    }
}



void playerAnimation::animation(int animationIndex, float frameDelay)
{
    frameRec.x = frameWidth * frameOffset;

    Rectangle destRec = { playerPosition->x, playerPosition->y, frameRec.width * playerSize, frameRec.height * playerSize };

    Vector2 origin = {32.0f, 64.0f };
    DrawTexturePro(animations[animationIndex], frameRec, destRec, origin, 0.0f, WHITE);

    frameTime += GetFrameTime();

    if(frameTime >= frameDelay)
    {
        frameTime = 0;
        frameOffset++;
    }

    if(frameOffset >= animations[animationIndex].width / frameWidth)
    {
        frameOffset = 0;
    }
}