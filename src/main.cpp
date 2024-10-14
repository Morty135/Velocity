#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include "player.h"
#include "playerCamera.h"



int main()
{
    InitWindow(800,600, "Skyrunner");
    SetTargetFPS(30);

    Rectangle envRecs[] =
    {
        {-600,64,1200,40}
    };

    int envRecsLength = sizeof(envRecs)/sizeof(envRecs[0]);

    player player("resources/playerSheet.png");
    playerCamera camera(&player.position);

    while (WindowShouldClose() == false)
    {

        BeginDrawing();
        ClearBackground(Color{139, 109, 156, 1});
        BeginMode2D(camera.update());


        DrawRectangleRec(envRecs[0],BLACK);

        player.collisionCheck(envRecs, envRecsLength);
        player.draw();

        EndMode2D();

        EndDrawing();
    }

    CloseWindow();
    
}