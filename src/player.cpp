#include "player.h"



player::player()
{
    for (size_t i = 0; i < pathsLenght; i++)
    {
        animations[i] = LoadTexture(animationPaths[i]);
    }
}



player::~player()
{
    for (size_t i = 0; i < pathsLenght; i++)
    {
        UnloadTexture(animations[i]);
    }
}


void player::draw()
{
    float deltaTime = GetFrameTime();

    if (inputManager.getAxisHorizontal() < -0.6f)
    {
        position.x -= speed * 1.5f * deltaTime;
    }
    else if (inputManager.getAxisHorizontal() < 0)
    {
        position.x -= speed * deltaTime;
    }

    if (inputManager.getAxisHorizontal() > 0.6f)
    {
        position.x += speed * 1.5f * deltaTime;
    }
    else if (inputManager.getAxisHorizontal() > 0)
    {
        position.x += speed * deltaTime;
    }
    
    if (inputManager.getAxisJump() && canJump)
    {
        velocity = -jumpForce;
        canJump = false;
    }

    VerticalCollision();

    std::cout << "Player Y position: " << position.y << std::endl;
    std::cout << "position X: " << position.x << std::endl;
    std::cout << "Can Jump: " << canJump << std::endl;

    DrawRectangleLinesEx(getCollisionRec(), 1, RED);
    DrawRectangleLinesEx({position.x - getCollisionRec().width*0.5f, position.y + getCollisionRec().height*0.7f, 30, 10}, 1, GREEN);
    DrawRectangleLinesEx({position.x - getCollisionRec().width*0.5f - 15, position.y + 10, 10, 30}, 1, GREEN);
    DrawRectangleLinesEx({position.x + getCollisionRec().width*0.5f, position.y + 10, 10, 30}, 1, GREEN);
    DrawCircleV(position, 30, BLUE);

    animator();
}



void player::animation(int animationIndex, float frameDelay)
{
    frameRec.x = frameWidth * frameOffset;

    Rectangle destRec = { position.x, position.y, frameRec.width * playerSize, frameRec.height * playerSize };

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



void player::animator()
{
    if(inputManager.getAxisHorizontal() > 0)
    {
        frameRec.width = frameWidth;
    }
    else
    {
        frameRec.width = -frameWidth;
    }
    if(inputManager.getAxisHorizontal() == 0)
    {
        animation(1);
    }
    if(inputManager.getAxisHorizontal() > 0 || inputManager.getAxisHorizontal() < 0)
    {
        animation(0);
    }
}



// collision rectangle
Rectangle player::getCollisionRec()
{
    float w = colliderSize.x * colliderScale;
    float h = colliderSize.y * colliderScale;
    float offsetX = colliderOffset.x;
    float offsetY = colliderOffset.y;

    if(inputManager.getAxisVertical() > 0 && canJump == false)
    {
        w = colliderSizeUpper.x * colliderScale;
        h = colliderSizeUpper.y * colliderScale;
        offsetX = colliderOffsetUpper.x;
        offsetY = colliderOffsetUpper.y;
    }
    if(inputManager.getAxisVertical() < 0)
    {
        w = colliderSizeLower.x * colliderScale;
        h = colliderSizeLower.y * colliderScale;
        offsetX = colliderOffsetLower.x;
        offsetY = colliderOffsetLower.y;
    }

    return {
        position.x - w * 0.5f + offsetX * colliderScale,
        position.y - h * 0.5f + offsetY * colliderScale,
        w,
        h
    };
}



void player::VerticalCollision()
{
    float deltaTime = GetFrameTime();
    bool hitObstacle = false;
    for (int i = 0; i < collisionRecsLenght; i++)
    {
        Rectangle col = collisionRecs[i];
        Rectangle collisionRec = getCollisionRec();
        if (col.x <= collisionRec.x &&
            col.x + col.width >= collisionRec.x &&
            col.y >= collisionRec.y &&
            col.y <= collisionRec.y + velocity * deltaTime)
        {
            hitObstacle = true;
            velocity = 0.0f;
            collisionRec.y = col.y;
            break;
        }
    }

    if (!hitObstacle)
    {
        position.y += velocity * deltaTime;
        velocity += gravity * deltaTime;
        canJump = false;
    }
    else
    {
        canJump = true;
    }
}