#ifndef INPUT_H
#define INPUT_H

#include <raylib.h>

class input
{
private:

public:
    input();
    ~input();

    float getAxisHorizontal();
    float getAxisVertical();
    bool getAxisJump();
};

#endif