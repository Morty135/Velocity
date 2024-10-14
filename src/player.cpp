#include "player.h"



player::player(const char* playerImagePath)
{
    playerSpritesheet = LoadTexture(playerImagePath);
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
        if(velocity.x > 0)
        {
            velocity.x -= horizontalDampening;
        }
        else if(velocity.x < 0)
        {
            velocity.x += horizontalDampening;
        }
        else
        {
            velocity.x = velocity.x;
        }
    }
    position.x += velocity.x;

    Rectangle destRec = { position.x, position.y, frameRec.width * playerSize, frameRec.height * playerSize };
    DrawRectangle(position.x-32, position.y - 64 ,64,128, {0,0,0,100});

    Vector2 origin = {32.0f, 64.0f };
    DrawTexturePro(playerSpritesheet, frameRec, destRec, origin, 0.0f, WHITE);
}
