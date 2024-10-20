#include "player.h"



player::player(const char* playerImagePath)
{
    playerSpritesheet = LoadTexture(playerImagePath);
    defaultGravity = gravity;
}



player::~player()
{
    UnloadTexture(playerSpritesheet);
}


void player::draw()
{
    Rectangle frameRec = { 0.0f, 32.0f, (float)playerSpritesheet.width/8, 64.0f};
    
    
    if(IsKeyDown(KEY_A))
    {
        if(velocity.x >= -maxVelocity.x)
        {
            velocity.x -= movementSpeed * GetFrameTime();
        }
        frameRec = { 0.0f, 32.0f, -(float)playerSpritesheet.width/8, 64.0f};
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
            velocity.x -= horizontalDampening;
        }
        else if(velocity.x < -0.1)
        {
            velocity.x += horizontalDampening;
        }
        else
        {
            velocity.x = velocity.x;
        }
    }
    


    if(IsKeyDown(KEY_SPACE) && groundCheck == true)
    {
        velocity.y += -jumpForce;
    }

    position.x += velocity.x;
    position.y += velocity.y;

    collisonRec = {position.x-32, position.y - 64 ,64,128};

    Rectangle destRec = { position.x, position.y, frameRec.width * playerSize, frameRec.height * playerSize };
    DrawRectangleRec(collisonRec, {0,0,0,100});

    Vector2 origin = {32.0f, 64.0f };
    DrawTexturePro(playerSpritesheet, frameRec, destRec, origin, 0.0f, WHITE);
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
            velocity.y += gravity;
        }
        gravity = defaultGravity;
    }
}