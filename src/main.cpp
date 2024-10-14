#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include "player.h"
#include "playerCamera.h"



int main()
{
    InitWindow(800,600, "Skyrunner");
    SetTargetFPS(30);

    player player("resources/playerSheet.png");
    playerCamera camera(&player.position);

    while (WindowShouldClose() == false)
    {

        BeginDrawing();
        ClearBackground(Color{139, 109, 156, 1});
        BeginMode2D(camera.update());


        DrawRectangle(-600,64,1200,40,BLACK);
        player.draw();

        EndMode2D();

        EndDrawing();
    }

    CloseWindow();
    
}