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
    if(IsKeyDown(KEY_A))
    {
        if(velocity.x >= -maxVelocity.x)
        {
            velocity.x -= movementSpeed * GetFrameTime();
        }
    }
    if(IsKeyDown(KEY_D))
    {
        if(velocity.x >= maxVelocity.x)
        {
            velocity.x -= movementSpeed * GetFrameTime();
        }
        velocity.x += movementSpeed * GetFrameTime();
    }
    else
    {
        if(velocity.x > 0.1)
        {
            velocity.x -= horizontalDampening * GetFrameTime();
        }
        else if(velocity.x < -0.1)
        {
            velocity.x += horizontalDampening * GetFrameTime();
        }
        else
        {
            velocity.x = 0;
        }
    }
    


    if(IsKeyDown(KEY_SPACE) && groundCheck == true)
    {
        velocity.y += -jumpForce;
    }

    position.x += velocity.x;
    position.y += velocity.y;

    collisonRec = {position.x-32, position.y - 64 ,64,128};

    DrawRectangleRec(collisonRec, {0,0,0,100});
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