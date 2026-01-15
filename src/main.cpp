#include <raylib.h>
#include <raymath.h>
#include <iostream>

#include "level0.h"
#include "menu.h"
#include "sceeneManager.h"



int main()
{
    InitWindow(1920,1080, "Velocity");
    InitAudioDevice();
    SetTargetFPS(60);
    SetExitKey(KEY_NULL);
    level0 level0;
    menu menu;

    while (WindowShouldClose() == false)
    {
        menu.draw();
        //level0.draw();
    }

    CloseWindow();
    
}