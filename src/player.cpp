#include "player.h"



player::player(): anim(&velocity, &position)
{
    defaultGravity = gravity;
}



player::~player()
{
}


void player::draw()
{
    float deltaTime = GetFrameTime();

    if (IsKeyDown(KEY_A))
    {
        velocity.x -= movementSpeed * deltaTime;
    }
    else if (IsKeyDown(KEY_D))
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
    


    if(IsKeyDown(KEY_SPACE) && groundCheck == true)
    {
        velocity.y += -jumpForce;
    }

    position.x += velocity.x;
    position.y += velocity.y;

    collisonRec = {position.x-32, position.y - 64 ,64,128};

    //DrawRectangleRec(collisonRec, {0,0,0,100});
    anim.animate();
}



void player::collisionCheck(Rectangle * envRecs, int envRecsLenght)
{
    int colRecs = 0;
    for (int i = 0; i < envRecsLenght; i++)
    {
        Rectangle envRec = envRecs[i];
        if (CheckCollisionRecs(collisonRec, envRec))
        {
            colRecs++;
        }
    }
    if(colRecs > 0)
    {
        groundCheck = true;
        velocity.y = 0;
        gravity = 0;
    }
    else
    {
        groundCheck = false;
        if(velocity.y <= maxVelocity.y)
        {
            velocity.y += gravity * GetFrameTime();
        }
        gravity = defaultGravity;
    }
}