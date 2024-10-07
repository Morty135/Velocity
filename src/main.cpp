#include <raylib.h>
#include "player.h"


int main()
{
    InitWindow(800,600, "Skyrunner");
    SetTargetFPS(30);

    Camera2D camera = { 0 };
    player player;

    while (WindowShouldClose() == false)
    {
        camera.target = (Vector2){0, 0};
        camera.offset = (Vector2){ GetScreenWidth()/2.0f, GetScreenHeight()/2.0f };
        camera.rotation = 0.0f;
        camera.zoom = 1.0f;

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