#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include "player.h"
#include "playerCamera.h"



int main()
{
    InitWindow(800,600, "Skyrunner");
    SetTargetFPS(30);

    player player;
    playerCamera camera(&player.position);

    while (WindowShouldClose() == false)
    {

        BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode2D(camera.update());


        DrawRectangle(-600,40,1200,40,BLACK);
        player.draw();

        EndMode2D();

        EndDrawing();
    }

    CloseWindow();
    
}