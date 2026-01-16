#include <raylib.h>
#include <raymath.h>
#include <iostream>

#include "level0.h"
#include "menu.h"


int main()
{
    InitWindow(1920,1080, "Velocity");
    InitAudioDevice();
    SetTargetFPS(60);
    SetExitKey(KEY_NULL);
    level0 level0;
    menu menu;

    while (WindowShouldClose() == false && currentScene != scenes::EXIT)
    {
        if(currentScene == scenes::LEVEL0)
        {
            level0.draw();
        }
        if(currentScene == scenes::MAINMENU)
        {
            menu.draw();
        }
    }

    CloseWindow();
    
}