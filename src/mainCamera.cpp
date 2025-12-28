#include "mainCamera.h"



mainCamera::mainCamera()
{
    
}



mainCamera::~mainCamera()
{

}


Camera2D mainCamera::update()
{
    if(inputManager.getAxisHorizontal() < 0)
    {
        currentCameraPos = {Lerp(currentCameraPos.x,targetPos->x - 300, 0.06f), Lerp(currentCameraPos.y,targetPos->y -50, 0.5f)};
        currentCameraZoom = Lerp(currentCameraZoom,0.8f, 0.04f);
    }
    else if(inputManager.getAxisHorizontal() > 0)
    {
        currentCameraPos = {Lerp(currentCameraPos.x,targetPos->x + 300, 0.06f), Lerp(currentCameraPos.y,targetPos->y -50, 0.5f)};
        currentCameraZoom = Lerp(currentCameraZoom,0.8f, 0.04f);
    }
    else
    {
        currentCameraPos = {Lerp(currentCameraPos.x,targetPos->x, 0.06f), Lerp(currentCameraPos.y,targetPos->y -50, 0.5f)};
        currentCameraZoom = Lerp(currentCameraZoom,1.4f, 0.02f);
    }
    camera.target = (Vector2){currentCameraPos};
    camera.offset = (Vector2){ GetScreenWidth()/2.0f, GetScreenHeight()/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = currentCameraZoom;

    return camera;
}
