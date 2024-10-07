#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include "player.h"



int main()
{
    InitWindow(800,600, "Skyrunner");
    SetTargetFPS(30);

    Camera2D camera = { 0 };
    player player;
    Vector2 currentCameraPos;
    float currentCameraZoom = 1.0;

    while (WindowShouldClose() == false)
    {
        currentCameraPos = {Lerp(currentCameraPos.x,player.position.x, 0.06f), Lerp(currentCameraPos.y,player.position.y -50, 0.06f)};
        camera.target = (Vector2){currentCameraPos};
        camera.offset = (Vector2){ GetScreenWidth()/2.0f, GetScreenHeight()/2.0f };
        camera.rotation = 0.0f;
        if(IsKeyDown(KEY_A) || IsKeyDown(KEY_D))
        {
            currentCameraZoom = Lerp(currentCameraZoom,0.8f, 0.04f);
        }
        else
        {
            currentCameraZoom = Lerp(currentCameraZoom,2.0f, 0.02f);
        }
        camera.zoom = currentCameraZoom;

        BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode2D(camera);


        DrawRectangle(-600,40,1200,40,BLACK);
        player.draw();

        EndMode2D();

        EndDrawing();
    }

    CloseWindow();
    
}