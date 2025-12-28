#ifndef LEVEL0_H
#define LEVEL0_H

#include <raylib.h>
#include <raymath.h>
#include <iostream>

#include "player.h"
#include "mainCamera.h"


class level0
{
private:
    Rectangle envRecs[4] =
    {
        {-600,64,1200,40},
        {300, 100,600,40},
        {600, 100,600,3000},
        {1500, 100,600,3000},
    };

    int envRecsLength = sizeof(envRecs)/sizeof(envRecs[0]);

    player player0;
    mainCamera camera;

public:
    level0();

    void draw();

};

#endif