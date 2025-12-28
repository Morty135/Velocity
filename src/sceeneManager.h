#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

enum class scenes
{
    MAINMENU,
    LEVEL0,
};

class sceeneManager
{
private:

public:
    scenes currentScene = scenes::MAINMENU;

    sceeneManager();
    ~sceeneManager();

};

#endif