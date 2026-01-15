#include "menu.h"

menu::menu()
{
    background = LoadTexture("resources/menu/ConceptReduced.png");
    clickFx = LoadSound("resources/menu/button-202966.mp3");

    playRec.height = buttonHeight + 10;
    playRec.width = 210;
    playRec.x = 190;
    playRec.y = GetScreenHeight()*0.3f - buttonHeight*0.5;

    settingsRec.height = buttonHeight + 10;
    settingsRec.width = 210;
    settingsRec.x = 190;
    settingsRec.y = GetScreenHeight()*0.5f - buttonHeight*0.5;

    exitRec.height = buttonHeight + 10;
    exitRec.width = 210;
    exitRec.x = 190;
    exitRec.y = GetScreenHeight()*0.7f - buttonHeight*0.5;
}

void menu::draw()
{
    BeginDrawing();
    ClearBackground((Color){139, 109, 156, 255});

    DrawTexture(background, 0, 0, WHITE);
    button(playRec, "Play");
    button(settingsRec, "Settings");
    button(exitRec, "Exit");

    EndDrawing();
}

void menu::button(Rectangle buttonRec, const char * text)
{
    if(CheckCollisionPointRec(GetMousePosition(), buttonRec))
    {
        DrawText(text, buttonRec.x, buttonRec.y, buttonHeight +5, GRAY);
        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            PlaySound(clickFx);
            if (text == "Play")
            {
                //switch scene
            }
            if (text == "Exit")
            {
                //switch scene
            }
        }
    }
    else
    {
        DrawText(text, buttonRec.x, buttonRec.y, buttonHeight, LIGHTGRAY);
    }
}

menu::~menu()
{
    UnloadTexture(background);
    UnloadSound(clickFx);
}