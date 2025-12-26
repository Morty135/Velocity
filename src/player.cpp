#include "player.h"



player::player(Rectangle* collisionRecs, int collisionRecsLength)
{
    this->collisionRecs = collisionRecs;
    this->collisionRecsLenght = collisionRecsLength;

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

    if (inputManager.getAxisHorizontal() < 0)
    {
        velocity.x -= movementSpeed * deltaTime;
    }
    else if (inputManager.getAxisHorizontal() > 0)
    {
        velocity.x += movementSpeed * deltaTime;
    }
    else
    {
        if (velocity.x > 0)
        {
            velocity.x = std::max(0.0f, velocity.x - horizontalDampening * deltaTime);
        }
        else if (velocity.x < 0)
        {
            velocity.x = std::min(0.0f, velocity.x + horizontalDampening * deltaTime);
        }
    }

    if (velocity.x >  maxVelocity.x) velocity.x =  maxVelocity.x;
    if (velocity.x < -maxVelocity.x) velocity.x = -maxVelocity.x;
    


    if(inputManager.getAxisHorizontal() > 0.6f || inputManager.getAxisHorizontal() < -0.6f)
    {
        maxVelocity.x = maxHorizontalVelocityFast;
    }
    else
    {
        maxVelocity.x = maxHorizontalVelocitySlow;
    }

    if(wallCheckLeft == true && inputManager.getAxisJump() && inputManager.getAxisHorizontal() < 0 && wallJumpTimer >= wallJumpCooldown)
    {
        wallJumpTimer = 0.0f;
        velocity.y += -jumpForce * 2.0f;
        velocity.x += jumpForce;
    }

    if(WallCheckRight == true && inputManager.getAxisJump() && inputManager.getAxisHorizontal() > 0 && wallJumpTimer >= wallJumpCooldown)
    {
        wallJumpTimer = 0.0f;
        velocity.y += -jumpForce * 2.0f;
        velocity.x += -jumpForce;
    }

    wallJumpTimer += deltaTime;

    if(inputManager.getAxisHorizontal() != 0)
    {
        if((wallCheckLeft == true && inputManager.getAxisHorizontal() < 0) || (WallCheckRight == true && inputManager.getAxisHorizontal() > 0))
        {
            maxVelocity.y = maxVelocityYWall;
        }
        else
        {
            maxVelocity.y = maxVelocityYFall;
        }
    }
    else
    {
        maxVelocity.y = maxVelocityYFall;
    }
    


    if(inputManager.getAxisJump() && groundCheck == true)
    {
        velocity.y += -jumpForce;
    }

    position.x += velocity.x;
    horizontalCollision();

    if(velocity.y <= maxVelocity.y)
    {
        velocity.y += gravity * GetFrameTime();
    }

    position.y += velocity.y;
    verticalCollision();

    DrawRectangleLinesEx(getCollisionRec(), 1, RED);
    DrawCircleV(position, 3, BLUE);

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
    if(velocity.x > 0.1)
    {
        frameRec.width = frameWidth;
    }
    else
    {
        frameRec.width = -frameWidth;
    }
    if(velocity.x < -0.15f || velocity.x > 0.15f)
    {
        animation(0);
    }
    if(velocity.x <= 0.15f && velocity.x >= -0.15f)
    {
        animation(1);
    }
}



void player::horizontalCollision()
{
    Rectangle rec = getCollisionRec();
    wallCheckLeft = false;
    WallCheckRight = false;

    for (int i = 0; i < collisionRecsLenght; i++)
    {
        if (CheckCollisionRecs(rec, collisionRecs[i]))
        {
            if (velocity.x > 0)
            {
                position.x += (collisionRecs[i].x - (rec.x + rec.width));
                WallCheckRight = true;
            }
            else if (velocity.x < 0)
            {
                position.x += ((collisionRecs[i].x + collisionRecs[i].width) - rec.x);
                wallCheckLeft = true;
            }

            velocity.x = 0;
            break;
        }
    }
}



void player::verticalCollision()
{
    Rectangle rec = getCollisionRec();
    groundCheck = false;

    for (int i = 0; i < collisionRecsLenght; i++)
    {
        if (CheckCollisionRecs(rec, collisionRecs[i]))
        {
            if (velocity.y > 0)
            {
                position.y +=
                    (collisionRecs[i].y - (rec.y + rec.height));
                groundCheck = true;
            }
            else if (velocity.y < 0)
            {
                position.y +=
                    ((collisionRecs[i].y + collisionRecs[i].height) - rec.y);
            }

            velocity.y = 0;
            break;
        }
    }

    gravity = groundCheck ? 0.0f : defaultGravity;
}


// collision rectangle
Rectangle player::getCollisionRec()
{
    float w = colliderSize.x * colliderScale;
    float h = colliderSize.y * colliderScale;

    return {
        position.x - w * 0.5f + colliderOffset.x * colliderScale,
        position.y - h * 0.5f + colliderOffset.y * colliderScale,
        w,
        h
    };
}