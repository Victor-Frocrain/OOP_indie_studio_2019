/*
** EPITECH PROJECT, 2020
** MenuPlayer
** File description:
** MenuPlayer.cpp
*/

#include "MenuPlayer.hpp"

MenuPlayer::MenuPlayer(irr::IrrlichtDevice *&device, const std::string &path) : Menu(device, path)
{
    irr::s32 buttonWidth = 267;
    irr::s32 buttonHeight = 73;
    irr::s32 pos = 300;

    _nbPlayers = 1;
    _nbComputers = 3;
    addTexture((_ressourcesPath + "sprites/players_background.jpg").c_str());
    addTexture((_ressourcesPath + "titles/player_selection.png").c_str(), irr::core::vector2di(0, 0), std::pair<bool, bool>(true, false));
    _buttons.push_back(addButton(CONTS, irr::core::rect<irr::s32>(_screenSize.Width / 2 - buttonWidth / 2, pos, _screenSize.Width / 2 + buttonWidth / 2, pos + buttonHeight), L"NEXT"));
    pos += buttonHeight + 20;
    _buttons.push_back(addButton(MAIN, irr::core::rect<irr::s32>(_screenSize.Width / 2 - buttonWidth / 2, pos, _screenSize.Width / 2 + buttonWidth / 2, pos + buttonHeight), L"MAIN MENU"));
    pos += buttonHeight + 20;
    _buttons.push_back(addButton(QUIT, irr::core::rect<irr::s32>(_screenSize.Width / 2 - buttonWidth / 2, pos, _screenSize.Width / 2 + buttonWidth / 2, pos + buttonHeight), L"QUIT"));

    buttonWidth = 324;
    buttonHeight = 300;
    pos = (_screenSize.Width / 4 - buttonWidth) / 2;
    _buttons.push_back(addButton(PLAYER1, irr::core::rect<irr::s32>(pos, 600, pos + buttonWidth, 900), L"PLAYER 1"));
    pos += buttonWidth + _screenSize.Width / 4 - buttonWidth;
    _buttons.push_back(addButton(PLAYER2, irr::core::rect<irr::s32>(pos, 600, pos + buttonWidth, 900), L"COMPUTER"));
    pos += buttonWidth + _screenSize.Width / 4 - buttonWidth;
    _buttons.push_back(addButton(PLAYER3, irr::core::rect<irr::s32>(pos, 600, pos + buttonWidth, 900), L"COMPUTER"));
    pos += buttonWidth + _screenSize.Width / 4 - buttonWidth;
    _buttons.push_back(addButton(PLAYER4, irr::core::rect<irr::s32>(pos, 600, pos + buttonWidth, 900), L"COMPUTER"));

    setButtonsState(false);
    for (auto it : _buttons) {
        if (std::get<0>(it) != PLAYER1 && std::get<0>(it) != PLAYER2 && std::get<0>(it) != PLAYER3 && std::get<0>(it) != PLAYER4) {
            setupButtonSprite(std::get<1>(it));
        }
        else {
            setupPlayerSlotSprites(it);
        }
    }
}

MenuPlayer::~MenuPlayer()
{}