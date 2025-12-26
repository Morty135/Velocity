#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include "player.h"
#include "mainCamera.h"



int main()
{
    InitWindow(800,600, "Skyrunner");
    SetTargetFPS(60);

    Rectangle envRecs[] =
    {
        {-600,64,1200,40},
        {300, 100,600,40},
        {600, 100,600,3000},
        {1300, 100,600,3000},
    };

    int envRecsLength = sizeof(envRecs)/sizeof(envRecs[0]);

    player player(envRecs, envRecsLength);
    mainCamera camera(&player.position);

    while (WindowShouldClose() == false)
    {
        BeginDrawing();
        ClearBackground(Color{139, 109, 156, 1});
        BeginMode2D(camera.update());

        for (int i = 0; i < envRecsLength; i++)
        {
            DrawRectangleRec(envRecs[i],BLACK);
        }

        player.draw();

        EndMode2D();

        EndDrawing();
    }

    CloseWindow();
    
}