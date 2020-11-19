/*
** EPITECH PROJECT, 2020
** Pause
** File description:
** Pause.cpp
*/

#include "Pause.hpp"

Pause::Pause(irr::IrrlichtDevice *&device, const std::string &path) : Menu(device, path)
{
    irr::s32 buttonWidth = 267;
    irr::s32 buttonHeight = 73;
    irr::s32 pos = 300;

    addTexture((_ressourcesPath + "sprites/players_background.jpg").c_str());
    addTexture((_ressourcesPath + "sprites/background_shadow.png").c_str(), irr::core::vector2di(0, 0), std::pair<bool, bool>(false, false), irr::core::rect<irr::s32>(0, 0, 0, 0), "", false);
    addTexture((_ressourcesPath + "titles/save.png").c_str(), irr::core::vector2di(0, _screenSize.Height / 2 - 77), std::pair<bool, bool>(true, false), irr::core::rect<irr::s32>(0, 0, 0, 0), "", false);
    addTexture((_ressourcesPath + "titles/pause.png").c_str(), irr::core::vector2di(0, 0), std::pair<bool, bool>(true, false));
    _buttons.push_back(addButton(PLAY, irr::core::rect<irr::s32>(_screenSize.Width / 2 - buttonWidth / 2, pos, _screenSize.Width / 2 + buttonWidth / 2, pos + buttonHeight), L"RESUME"));
    pos += buttonHeight + 40;
    _buttons.push_back(addButton(MAIN, irr::core::rect<irr::s32>(_screenSize.Width / 2 - buttonWidth / 2, pos, _screenSize.Width / 2 + buttonWidth / 2, pos + buttonHeight), L"MAIN MENU"));
    pos += buttonHeight + 40;
    _buttons.push_back(addButton(QUIT, irr::core::rect<irr::s32>(_screenSize.Width / 2 - buttonWidth / 2, pos, _screenSize.Width / 2 + buttonWidth / 2, pos + buttonHeight), L"QUIT"));

    std::vector<const wchar_t *> texts = { L"YES", L"NO", L"CANCEL" };
    pos = _screenSize.Width / 2 - (buttonWidth * 3 + 40) / 2;
    for (size_t i = 0; i < texts.size(); i++, pos += buttonWidth + 20) {
        _buttons.push_back(addButton(SAVE, irr::core::rect<irr::s32>(pos, _screenSize.Height / 2 - buttonHeight / 2 + 77, pos + buttonWidth, _screenSize.Height / 2 + buttonHeight / 2 + 77), texts[i], 20 + i));
    }
    setButtonsState(false);
    for (auto it : _buttons) {
        setupButtonSprite(std::get<1>(it));
    }
}

Pause::~Pause()
{}

bool Pause::_isWaiting = false;
Pause::buttonTypes Pause::_action = NONE;

void Pause::setIsWaiting(const bool &waiting)
{
    _isWaiting = waiting;
}

bool Pause::getIsWaiting() noexcept
{
    return _isWaiting;
}

void Pause::setAction(const buttonTypes &type)
{
    _action = type;
}

Pause::buttonTypes Pause::getAction() noexcept
{
    return _action;
}