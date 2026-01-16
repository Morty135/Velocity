#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

enum class scenes
{
    EXIT,
    MAINMENU,
    LEVEL0,
};

extern scenes currentScene;

class sceeneManager
{
private:

public:
    sceeneManager();
    ~sceeneManager();

};

#endif