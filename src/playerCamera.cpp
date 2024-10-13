#include "playerCamera.h"



playerCamera::playerCamera(Vector2* playerPos)
{
    currentCameraPos = (Vector2){*playerPos};
    this->playerPos = playerPos;
}



playerCamera::~playerCamera()
{

}


Camera2D playerCamera::update()
{
    if(IsKeyDown(KEY_A))
    {
        currentCameraPos = {Lerp(currentCameraPos.x,playerPos->x - 300, 0.06f), Lerp(currentCameraPos.y,playerPos->y -50, 0.06f)};
        currentCameraZoom = Lerp(currentCameraZoom,0.8f, 0.04f);
    }
    else if(IsKeyDown(KEY_D))
    {
        currentCameraPos = {Lerp(currentCameraPos.x,playerPos->x + 300, 0.06f), Lerp(currentCameraPos.y,playerPos->y -50, 0.06f)};
        currentCameraZoom = Lerp(currentCameraZoom,0.8f, 0.04f);
    }
    else
    {
        currentCameraPos = {Lerp(currentCameraPos.x,playerPos->x, 0.06f), Lerp(currentCameraPos.y,playerPos->y -50, 0.06f)};
        currentCameraZoom = Lerp(currentCameraZoom,1.4f, 0.02f);
    }
    camera.target = (Vector2){currentCameraPos};
    camera.offset = (Vector2){ GetScreenWidth()/2.0f, GetScreenHeight()/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = currentCameraZoom;

    return camera;
}
