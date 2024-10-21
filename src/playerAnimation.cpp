#include <playerAnimation.h>



playerAnimation::playerAnimation(Vector2* playerVelocity)
{
    this->playerVelocity = playerVelocity;
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
    animations[1];
}



void playerAnimation::runAnimation()
{
    animations[0];
}