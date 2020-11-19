/*
** EPITECH PROJECT, 2020
** Menu
** File description:
** Menu.cpp
*/

#include "../include/Menu.hpp"

Menu::Menu(irr::IrrlichtDevice *&device) : AScene(device), _gui(device->getGUIEnvironment()), _scene(_rootScene->createNewSceneManager())
{
    addButton(PLAY);
    addButton(QUIT);
}

Menu::~Menu()
{}

irr::gui::IGUIEnvironment *Menu::getGUIEnv() const noexcept
{
    return _gui;
}

irr::scene::ISceneManager *Menu::getScene() const noexcept
{
    return _scene;
}

irr::gui::IGUIButton *Menu::getButton(const buttonTypes &type) noexcept
{
    return _buttons[type];
}

void Menu::addButton(const buttonTypes &type)
{
    switch (type) {
        case PLAY: {
            _buttons[type] = _gui->addButton(irr::core::rect<irr::s32>(WIDTH / 2 - 100, 80, WIDTH / 2 + 100, 120), 0, -1, L"PLAY");
            break;
        }
        case QUIT: {
            _buttons[type] = _gui->addButton(irr::core::rect<irr::s32>(WIDTH / 2 - 100, 160, WIDTH / 2 + 100, 200), 0, -1, L"QUIT");
            break;
        }
        default: {
            break;
        }
    }
}

void Menu::manageButtons(AScene &scenes) const
{
    std::map<buttonTypes, irr::gui::IGUIButton *>::const_iterator it;
    buttonTypes type = NONE;

    for (it = _buttons.begin(); it != _buttons.end(); it++) {
        if(it->second->isPressed()) {
            type = it->first;
            break;
        }
    }
    
}

void Menu::displayScene() const
{
    _gui->drawAll();
    _scene->drawAll();
}