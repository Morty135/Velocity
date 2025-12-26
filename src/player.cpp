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
        velocity.y = 0.0f;
        wallJumpTimer = 0.0f;
        velocity.y += -jumpForce * 1.3f;
        velocity.x += jumpForce * 0.7f;
    }

    if(WallCheckRight == true && inputManager.getAxisJump() && inputManager.getAxisHorizontal() > 0 && wallJumpTimer >= wallJumpCooldown)
    {
        velocity.y = 0.0f;
        wallJumpTimer = 0.0f;
        velocity.y += -jumpForce * 1.3f;
        velocity.x += -jumpForce * 0.7f;
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

    std::cout << groundCheck << std::endl;
    


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



// this thing is broken at so many levels Me need fix
void player::verticalCollision()
{
    Rectangle rec = getCollisionRec();
    groundCheck = false;

    for (int i = 0; i < collisionRecsLenght; i++)
    {
        if (!CheckCollisionRecs(rec, collisionRecs[i]))
            continue;

        float overlapBottom = (rec.y + rec.height) - collisionRecs[i].y;

        float overlapTop = (collisionRecs[i].y + collisionRecs[i].height) - rec.y;

        if (overlapBottom > 0 && overlapBottom < overlapTop + 0.5f)
        {
            position.y -= overlapBottom;
            groundCheck = true;
        }
        else if (overlapTop > 0)
        {
            position.y += overlapTop;
        }

        velocity.y = 0;
        break;
    }

    gravity = groundCheck ? 0.0f : defaultGravity;
}


// collision rectangle
Rectangle player::getCollisionRec()
{
    float w = colliderSize.x * colliderScale;
    float h = colliderSize.y * colliderScale;
    float offsetX = colliderOffset.x;
    float offsetY = colliderOffset.y;

    if(inputManager.getAxisVertical() > 0 && groundCheck == false)
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