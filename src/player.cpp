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

    //VerticalCollision();
    collision();

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




void player::collision()
{
    Rectangle collisionRec = getCollisionRec();

    Rectangle groundCheckRec = {position.x - collisionRec.width*0.5f, position.y + collisionRec.height*0.67f, 30, 5};
    Rectangle leftWallCheckRec = {position.x - collisionRec.width*0.5f - 5, position.y + 10, 5, 30};
    Rectangle rightWallCheckRec = {position.x + collisionRec.width*0.5f, position.y + 10, 5, 30};

    DrawRectangleLinesEx(collisionRec, 1, RED);
    DrawRectangleLinesEx(groundCheckRec, 1, GREEN);
    DrawRectangleLinesEx(leftWallCheckRec, 1, GREEN);
    DrawRectangleLinesEx(rightWallCheckRec, 1, GREEN);

    groundCheck = false;
    wallCheckLeft = false;
    wallCheckRight = false;

    bool collided = false;

    Rectangle groundRec;

    for (int i = 0; i < collisionRecsLenght; i++)
    {
        Rectangle col = collisionRecs[i];
        if (CheckCollisionRecs(col, collisionRec))
        {
            collided = true;
        }
        if (CheckCollisionRecs(col, groundCheckRec))
        {
            groundRec = GetCollisionRec(col, collisionRec);
            groundCheck = true;
            velocity = 0.0f;
            position.y = col.y - collisionRec.height * 0.5f;
        }
        if (CheckCollisionRecs(col, leftWallCheckRec))
        {
            wallCheckLeft = true;
        }
        if (CheckCollisionRecs(col, rightWallCheckRec))
        {
            wallCheckRight = true;
        }
    }

    std::cout << "Ground Check: " << groundCheck << std::endl;
    std::cout << "Wall Check Left: " << wallCheckLeft << std::endl;
    std::cout << "Wall Check Right: " << wallCheckRight << std::endl;
    std::cout << "collided: " << collided << std::endl;

    if(collided == true && groundCheck == true)
    {
        //velocity = 0.0f;
        position.y = groundRec.y - collisionRec.height*0.66f;
    }
    else
    {
        position.y += velocity * GetFrameTime();
        velocity += gravity * GetFrameTime();
    }
    if(groundCheck == true)
    {
        canJump = true;
    }
}