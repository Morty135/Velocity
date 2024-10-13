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
        position.x -= movementSpeed;
        frameRec = { 0.0f, 32.0f, -(float)playerSpritesheet.width/8, 64.0f};
    }
    if(IsKeyDown(KEY_D))
    {
        position.x += movementSpeed;
    }

    Rectangle destRec = { position.x, position.y, frameRec.width * playerSize, frameRec.height * playerSize };
    DrawRectangle(position.x-20, position.y,40,40, BLUE);

    Vector2 origin = { 32.0f, 88.0f };
    DrawTexturePro(playerSpritesheet, frameRec, destRec, origin, 0.0f, WHITE);
}
