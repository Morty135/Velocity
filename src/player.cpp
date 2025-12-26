#include "player.h"



player::player(Rectangle* collisionRecs, int envRecsLength)
{
    defaultGravity = gravity;
    this->collisionRecs = collisionRecs;
    this->collisionRecsLenght = envRecsLength;

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
    


    if(inputManager.getAxisJump() && groundCheck == true)
    {
        velocity.y += -jumpForce;
    }

    position.x += velocity.x;
    collisionRec.x = position.x - collisionRec.width * 0.5f;
    collisionRec.y = position.y - collisionRec.height * 0.5f;
    horizontalCollision();

    if(velocity.y <= maxVelocity.y)
    {
        velocity.y += gravity * GetFrameTime();
    }

    position.y += velocity.y;
    collisionRec.x = position.x - collisionRec.width * 0.5f;
    collisionRec.y = position.y - collisionRec.height * 0.5f;
    verticalCollision();

    DrawRectangleRec(collisionRec, {0,0,0,100});
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
    Rectangle rec = collisionRec;

    for (int i = 0; i < collisionRecsLenght; i++)
    {
        if (CheckCollisionRecs(rec, collisionRecs[i]))
        {
            if (velocity.x > 0)
            {
                // moving right → hit left side of wall
                position.x = collisionRecs[i].x - rec.width / 2;
            }
            else if (velocity.x < 0)
            {
                // moving left → hit right side of wall
                position.x = collisionRecs[i].x + collisionRecs[i].width + rec.width / 2;
            }

            velocity.x = 0;
            break;
        }
    }
}



void player::verticalCollision()
{
    Rectangle rec = collisionRec;
    groundCheck = false;

    for (int i = 0; i < collisionRecsLenght; i++)
    {
        if (CheckCollisionRecs(rec, collisionRecs[i]))
        {
            if (velocity.y > 0)
            {
                // falling → ground
                position.y = collisionRecs[i].y - rec.height / 2;
                groundCheck = true;
            }
            else if (velocity.y < 0)
            {
                // jumping → ceiling
                position.y = collisionRecs[i].y + collisionRecs[i].height + rec.height / 2;
            }

            velocity.y = 0;
            break;
        }
    }

    gravity = groundCheck ? 0 : defaultGravity;
}
