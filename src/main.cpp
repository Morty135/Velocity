#include <raylib.h>
#include <raymath.h>
#include <iostream>

#include "level0.h"



int main()
{
    InitWindow(800,600, "Velocity");
    SetTargetFPS(60);
    level0 level0;

    while (WindowShouldClose() == false)
    {
        level0.draw();
    }

    CloseWindow();
    
}