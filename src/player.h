#ifndef PLAYER_H
#define PLAYER_H


#include <raylib.h>

class player
{
private:

public:
    Vector2 position = {0,0};
    float movementSpeed = 5;
    Texture2D playerSpritesheet;
    float playerSize = 4.0;


    player(const char* playerImagePath);
    ~player();

    void draw();
};

#endif