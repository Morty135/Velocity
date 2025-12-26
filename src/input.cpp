#include "input.h"



input::input()
{
    
}



input::~input()
{
    
}



float input::getAxisHorizontal()
{
    float horizontal = 0.0f;

    if (IsKeyDown(KEY_A))
    {
        if(IsKeyDown(KEY_LEFT_SHIFT))
        {
            horizontal -= 1.0f;
        }
        else
        {
            horizontal -= 0.5f;
        }
    }
    if (IsKeyDown(KEY_D))
    {
        if(IsKeyDown(KEY_LEFT_SHIFT))
        {
            horizontal += 1.0f;
        }
        else
        {
            horizontal += 0.5f;
        }
    }
    if(GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X) > 0.1f || GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X) < -0.1f)
    {
        horizontal = GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X);
    }

    return horizontal;
}



float input::getAxisVertical()
{
    float vertical = 0.0f;

    if (IsKeyDown(KEY_W))
    {
        vertical -= 1.0f;
    }
    if (IsKeyDown(KEY_S))
    {
        vertical += 1.0f;
    }

    return vertical;
}



bool input::getAxisJump()
{
    if(IsKeyDown(KEY_SPACE))
    {
        return true;
    }
    if(IsGamepadAvailable(0) && IsGamepadButtonDown(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN))
    {
        return true;
    }
    return false;
}