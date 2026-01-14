#include "mainCamera.h"



mainCamera::mainCamera()
{
    
}



mainCamera::~mainCamera()
{

}


Camera2D mainCamera::update()
{
    // horizontal lookahead
    if(lastTargetPos.x > targetPos->x)
    {
        currentCameraPos.x = Lerp(currentCameraPos.x,targetPos->x - 300, 0.06f);
    }
    else if(lastTargetPos.x < targetPos->x)
    {
        currentCameraPos.x = Lerp(currentCameraPos.x,targetPos->x + 300, 0.06f);
    }
    else
    {
        currentCameraPos.x = Lerp(currentCameraPos.x,targetPos->x, 0.06f);
    }
    // zoom and vertical
    if(lastTargetPos.y != targetPos->y || lastTargetPos.x != targetPos->x)
    {
        currentCameraPos.y = Lerp(currentCameraPos.y,targetPos->y - 50, 0.6f);
        currentCameraZoom = Lerp(currentCameraZoom,0.8f, 0.04f);
    }
    else
    {
        currentCameraPos.y = Lerp(currentCameraPos.y,targetPos->y - 50, 0.6f);
        currentCameraZoom = Lerp(currentCameraZoom,1.4f, 0.02f);
    }

    camera.target = (Vector2){currentCameraPos};
    camera.offset = (Vector2){ GetScreenWidth()/2.0f, GetScreenHeight()/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = currentCameraZoom;
    lastTargetPos = *targetPos;

    return camera;
}
