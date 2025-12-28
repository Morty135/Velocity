#include "level0.h"

level0::level0()
{
    player0.collisionRecs = envRecs;
    player0.collisionRecsLenght = envRecsLength;
    camera.targetPos = &player0.position;
}

void level0::draw()
{
    BeginDrawing();
    ClearBackground(Color{139, 109, 156, 1});
    BeginMode2D(camera.update());

    for (int i = 0; i < envRecsLength; i++)
    {
        DrawRectangleRec(envRecs[i],BLACK);
    }

    player0.draw();

    EndMode2D();

    EndDrawing();
}