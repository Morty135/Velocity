#include "player.h"



player::player()
{

}



player::~player()
{

}


void player::draw()
{
    if(IsKeyDown(KEY_A))
    {
        position.x -= movementSpeed;
    }
    if(IsKeyDown(KEY_D))
    {
        position.x += movementSpeed;
    }
    DrawRectangle(position.x, position.y,40,40, BLUE);
}
