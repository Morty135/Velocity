#ifndef MENU_H
#define MEUN_H

#include <raylib.h>
#include <raymath.h>
#include <iostream>

#include "player.h"
#include "sceneManager.h"


class menu
{
private:
    Texture2D background;
    Sound clickFx;

    Rectangle playRec;
    Rectangle settingsRec;
    Rectangle exitRec;

    int buttonHeight = 100;

public:
    menu();
    ~menu();

    void draw();

    void button(Rectangle buttonRec, const char * text);
};

#endif