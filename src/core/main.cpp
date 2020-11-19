/*
** EPITECH PROJECT, 2020
** indie studio
** File description:
** main.cpp
*/

#include <irrlicht/irrlicht.h>
#include "../scenes/Scenes.hpp"
#include "../finder/Finder.hpp"
#include "../scenes/EventListener.hpp"

#pragma comment(lib, "Irrlicht.lib")

#define GUIW 1500
#define GUIH 950

int main(void)
{
    int id = 0;
    Finder finder;
    EventListener listener;
    irr::IrrlichtDevice *device = irr::createDevice(irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(WIDTH, HEIGHT), 16, false, false, false, &listener);
    irr::video::IVideoDriver *driver = device->getVideoDriver();
    Scenes scenes(device, finder.getFilePath());
    device->setWindowCaption(L"Indie Studio");
    irr::u32 pastTime = device->getTimer()->getTime();
    irr::u32 newTime = device->getTimer()->getTime();
    while (device->run()) {
        newTime = device->getTimer()->getTime();
        Scenes::setDeltaTime((irr::f32)(newTime - pastTime) / 1000.0f);
        pastTime = newTime;
        driver->beginScene(true, true, irr::video::SColor(255, 100, 100, 100));
        scenes.manageScene();
        if (Scenes::getCurrentScene() == AScene::sceneType::EXIT)
            break;
        scenes.getSceneInstance(scenes.getCurrentScene())->displayScene();
        driver->endScene();
    }
    device->drop();
    return 0;
}
