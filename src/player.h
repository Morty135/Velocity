#ifndef PLAYER_H
#define PLAYER_H


#include <raylib.h>

class player
{
private:

public:
    Vector2 position = {0,0};
    float movementSpeed = 5;


    player();
    ~player();

    void draw();
};

#endif