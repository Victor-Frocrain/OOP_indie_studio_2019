/*
** EPITECH PROJECT, 2020
** Menu
** File description:
** Menu.cpp
*/

#include "Menu.hpp"
#include <iostream>
#include "ControlMenu.hpp"
#include "Options.hpp"
#include "Game.hpp"
#include "WinMenu.hpp"

irr::gui::IGUISpriteBank *Menu::_buttonSprite = nullptr;

Menu::Menu(irr::IrrlichtDevice *&device, const std::string &path)
    : AScene(device, path)
{
    if (!_buttonSprite) {
        _buttonSprite = _rootGUI->addEmptySpriteBank("ButtonSprite");
        _buttonSprite->addTextureAsSprite(_driver->getTexture(std::string(_ressourcesPath + "sprites/button_hover.png").c_str()));
        _buttonSprite->addTextureAsSprite(_driver->getTexture(std::string(_ressourcesPath + "sprites/button_down.png").c_str()));
        _buttonSprite->addTextureAsSprite(_driver->getTexture(std::string(_ressourcesPath + "sprites/button_normal.png").c_str()));
        _buttonSprite->addTextureAsSprite(_driver->getTexture(std::string(_ressourcesPath + "sprites/player_slot1.png").c_str()));
        _buttonSprite->addTextureAsSprite(_driver->getTexture(std::string(_ressourcesPath + "sprites/player_slot2.png").c_str()));
        _buttonSprite->addTextureAsSprite(_driver->getTexture(std::string(_ressourcesPath + "sprites/player_slot3.png").c_str()));
        _buttonSprite->addTextureAsSprite(_driver->getTexture(std::string(_ressourcesPath + "sprites/player_slot4.png").c_str()));
        _buttonSprite->addTextureAsSprite(_driver->getTexture(std::string(_ressourcesPath + "sprites/player_slot_none.png").c_str()));
        _buttonSprite->addTextureAsSprite(_driver->getTexture(std::string(_ressourcesPath + "sprites/key_button.png").c_str()));
        _buttonSprite->addTextureAsSprite(_driver->getTexture(std::string(_ressourcesPath + "sprites/soundOK_normal.png").c_str()));
        _buttonSprite->addTextureAsSprite(_driver->getTexture(std::string(_ressourcesPath + "sprites/soundOK_hover.png").c_str()));
        _buttonSprite->addTextureAsSprite(_driver->getTexture(std::string(_ressourcesPath + "sprites/soundOK_down.png").c_str()));
        _buttonSprite->addTextureAsSprite(_driver->getTexture(std::string(_ressourcesPath + "sprites/soundKO_normal.png").c_str()));
        _buttonSprite->addTextureAsSprite(_driver->getTexture(std::string(_ressourcesPath + "sprites/soundKO_hover.png").c_str()));
        _buttonSprite->addTextureAsSprite(_driver->getTexture(std::string(_ressourcesPath + "sprites/soundKO_down.png").c_str()));
        _buttonSprite->addTextureAsSprite(_driver->getTexture(std::string(_ressourcesPath + "sprites/sound_cursor_normal.png").c_str()));
        _buttonSprite->addTextureAsSprite(_driver->getTexture(std::string(_ressourcesPath + "sprites/sound_cursor_hold.png").c_str()));
        _buttonSprite->addTextureAsSprite(_driver->getTexture(std::string(_ressourcesPath + "sprites/sound_cursor_down.png").c_str()));
        _buttonSprite->addTextureAsSprite(_driver->getTexture(std::string(_ressourcesPath + "sprites/rightArrow_normal.png").c_str()));
        _buttonSprite->addTextureAsSprite(_driver->getTexture(std::string(_ressourcesPath + "sprites/rightArrow_over.png").c_str()));
        _buttonSprite->addTextureAsSprite(_driver->getTexture(std::string(_ressourcesPath + "sprites/rightArrow_pressed.png").c_str()));
        _buttonSprite->addTextureAsSprite(_driver->getTexture(std::string(_ressourcesPath + "sprites/leftArrow_normal.png").c_str()));
        _buttonSprite->addTextureAsSprite(_driver->getTexture(std::string(_ressourcesPath + "sprites/leftArrow_over.png").c_str()));
        _buttonSprite->addTextureAsSprite(_driver->getTexture(std::string(_ressourcesPath + "sprites/leftArrow_pressed.png").c_str()));
        _buttonSprite->addTextureAsSprite(_driver->getTexture(std::string(_ressourcesPath + "sprites/leftArrow_disabled.png").c_str()));
        _buttonSprite->addTextureAsSprite(_driver->getTexture(std::string(_ressourcesPath + "sprites/rightArrow_disabled.png").c_str()));
    }
}

Menu::~Menu()
{}

Menu::controlTypes Menu::_controlToDefine = ZERO;

void Menu::setupButtonSprite(irr::gui::IGUIButton *button)
{
    button->setSpriteBank(_buttonSprite);
    button->setSprite(irr::gui::EGBS_BUTTON_MOUSE_OFF, 2);
    button->setSprite(irr::gui::EGBS_BUTTON_DOWN, 1);
    button->setSprite(irr::gui::EGBS_BUTTON_UP, 0);
    button->setDrawBorder(false);
    button->setUseAlphaChannel(true);
}

irr::gui::IGUIEnvironment *Menu::getGUIEnv() const noexcept
{
    return _rootGUI;
}

irr::scene::ISceneManager *Menu::getScene() const noexcept
{
    return _scene;
}

irr::gui::IGUISpriteBank *Menu::getSpriteBank() noexcept
{
    return _buttonSprite;
}

irr::gui::IGUIButton *Menu::getButton(const buttonTypes &type) noexcept
{
    for (size_t i = 0; i < _buttons.size(); i++) {
        if (std::get<0>(_buttons[i]) == type) {
            return std::get<1>(_buttons[i]);
        }
    }
    return nullptr;
}

Menu::controlTypes Menu::getControlToDefine() noexcept
{
    return _controlToDefine;
}

void Menu::setControlToDefine(const controlTypes &control)
{
    _controlToDefine = control;
}

void Menu::manageScene()
{
    manageButtons();
    if (_currentScene == PLAYERCHOICE) {
        managePlayersButton();
    }
    else if (_currentScene == OPTIONS) {
        manageCursorSound();
        if (!ControlMenu::getIsWaitingKey() && !ControlMenu::getIsKeyError()) {
            manageControls();
        }
        else if (ControlMenu::getIsWaitingKey() && ControlMenu::updateControls()) {
            updateControlButtons();
        }
        else if (ControlMenu::getIsKeyError()) {
            if (!ControlMenu::showErrorKeyMessage(_buttons, _ressourcesPath, _textures)) {
                manageDifficultyText();
            }
        }
    }
    else if (_currentScene == CONTROLS && !ControlMenu::getIsWaitingKey() && !ControlMenu::getIsKeyError()) {
        manageControls();
        Game::updatePlayerBinds();
    }
    else if (_currentScene == CONTROLS && (ControlMenu::getIsWaitingKey() || ControlMenu::getIsKeyError())) {
        if (ControlMenu::getIsWaitingKey() && ControlMenu::updateControls()) {
            updateControlButtons();
        }
        else if (ControlMenu::getIsKeyError()) {
            if (!ControlMenu::showErrorKeyMessage(_buttons, _ressourcesPath, _textures)) {
                manageDifficultyText();
            }
        }
    }
}

void Menu::manageCursorSound()
{
    irr::s32 cursorWidth = 54;
    irr::core::vector2di mouse = _device->getCursorControl()->getPosition();

    for (size_t i = 0; i < _buttons.size(); i++) {
        if (std::get<0>(_buttons[i]) == SOUNDCURSOR) {
            if (std::get<1>(_buttons[i])->isPressed()) {
                std::get<1>(_buttons[i])->setSprite(irr::gui::EGBS_BUTTON_MOUSE_OVER, 17);
                for (auto it : _textures) {
                    if (Tools::to_string(std::get<0>(it)->getName().getPath()) == _ressourcesPath + "sprites/sound_bar_empty.png") {
                        irr::core::rect<irr::s32> pos = std::get<1>(_buttons[i])->getRelativePosition();
                        pos.UpperLeftCorner.X = mouse.X - cursorWidth + cursorWidth / 2;
                        if (pos.UpperLeftCorner.X > std::get<1>(it).X + std::get<0>(it)->getSize().Width - cursorWidth) {
                            pos.UpperLeftCorner.X = std::get<1>(it).X + std::get<0>(it)->getSize().Width - cursorWidth;
                        }
                        else if (pos.UpperLeftCorner.X < std::get<1>(it).X) {
                            pos.UpperLeftCorner.X = std::get<1>(it).X;
                        }
                        pos.LowerRightCorner.X = pos.UpperLeftCorner.X + cursorWidth;
                        std::get<1>(_buttons[i])->setRelativePosition(pos);
                        for (size_t i = 0; i < _textures.size(); i++) {
                            if (Tools::to_string(std::get<0>(_textures[i])->getName().getPath()) == _ressourcesPath + "sprites/sound_bar_filled.png") {
                                std::get<2>(_textures[i]) = { 0, 0, pos.UpperLeftCorner.X + cursorWidth / 2 - std::get<1>(_textures[i]).X, 54 };
                                computeVolumeSound(pos.UpperLeftCorner.X - std::get<1>(_textures[i]).X, std::get<0>(it)->getSize().Width - 54);
                                break;
                            }
                        }
                        break;
                    }
                }
            }
            else {
                std::get<1>(_buttons[i])->setSprite(irr::gui::EGBS_BUTTON_MOUSE_OVER, 16);
            }
            break;
        }
    }
}

void Menu::computeVolumeSound(const float &limit, const float &total)
{
    _musicsVolume = limit / total * 100;
    std::map<sceneType, sf::Music>::iterator it;
    std::map<SoundEffect, sf::Music>::iterator it2;

    if (!_isMuted) {
        for (it = _musics.begin(); it != _musics.end(); it++) {
            it->second.setVolume(_musicsVolume);
        }
        for (it2 = _soundEffects.begin(); it2 != _soundEffects.end(); it2++) {
            it2->second.setVolume(_musicsVolume);
        }
        WinMenu::setIntroVolume(_musicsVolume);
    }
}

void Menu::displayScene() const
{
    for (size_t i = 0; i < _textures.size(); i++) {
        if (std::get<3>(_textures[i])) {
            _driver->draw2DImage(std::get<0>(_textures[i]), std::get<1>(_textures[i]), std::get<2>(_textures[i]), 0, irr::video::SColor(255, 255, 255, 255), true);
        }
    }
    for (size_t i = 0; i < _buttons.size(); i++) {
        if (std::get<1>(_buttons[i]) != nullptr) {
            std::get<1>(_buttons[i])->draw();
        }
    }
    _scene->drawAll();
}

void Menu::setupPlayerSlotSprites(std::tuple<buttonTypes, irr::gui::IGUIButton *, bool> button)
{
    std::get<1>(button)->setSpriteBank(_buttonSprite);
    switch (std::get<0>(button)) {
    case PLAYER1: {
        std::get<1>(button)->setSprite(irr::gui::EGBS_BUTTON_UP, 3);
        break;
    }
    case PLAYER2: {
        std::get<1>(button)->setSprite(irr::gui::EGBS_BUTTON_UP, 4);
        break;
    }
    case PLAYER3: {
        std::get<1>(button)->setSprite(irr::gui::EGBS_BUTTON_UP, 5);
        break;
    }
    case PLAYER4: {
        std::get<1>(button)->setSprite(irr::gui::EGBS_BUTTON_UP, 6);
        break;
    }
    default:
        break;
    }
    std::get<1>(button)->setDrawBorder(false);
    std::get<1>(button)->setUseAlphaChannel(true);
}

void Menu::setupPlayerSlotTexts(std::tuple<buttonTypes, irr::gui::IGUIButton *, bool> button)
{
    switch (std::get<0>(button)) {
        case PLAYER1: {
            std::get<1>(button)->setText(L"PLAYER 1");
            break;
        }
        case PLAYER2: {
            std::get<1>(button)->setText(L"PLAYER 2");
            break;
        }
        case PLAYER3: {
            std::get<1>(button)->setText(L"PLAYER 3");
            break;
        }
        case PLAYER4: {
            std::get<1>(button)->setText(L"PLAYER 4");
            break;
        }
        default:
            break;
    }
}

void Menu::managePlayersButton()
{
    static bool isPressed = false;
    static buttonTypes type = NONE;

    std::map<buttonTypes, playerType> types = {
        { PLAYER1, P1 },
        { PLAYER2, P2 },
        { PLAYER3, P3 },
        { PLAYER4, P4 }
    };
    for (auto it : _buttons) {
        if ((std::get<0>(it) == PLAYER1 || std::get<0>(it) == PLAYER2 || std::get<0>(it) == PLAYER3 || std::get<0>(it) == PLAYER4) &&
            std::get<1>(it)->isPressed() && !isPressed) {
            const wchar_t *text = std::get<1>(it)->getText();
            std::string strText = "";
            for (size_t i = 0; text[i] != 0; i++) {
                strText += text[i];
            }
            if (strText == "COMPUTER") {
                setupPlayerSlotTexts(it);
                setupPlayerSlotSprites(it);
                _playersMap[std::get<0>(it)] = true;
                _aiMap[types[std::get<0>(it)]] = false;
                if (_nbPlayers < 4) {
                    _nbPlayers++;
                }
                if (_nbComputers > 0) {
                    _nbComputers--;
                }
            }
            else if (strText.find("PLAYER") != -1 && _nbPlayers > 1) {
                _playersMap[std::get<0>(it)] = false;
                if (_nbPlayers + _nbComputers > 2) {
                    std::get<1>(it)->setText(L"EMPTY");
                    std::get<1>(it)->setSprite(irr::gui::EGBS_BUTTON_UP, 7);
                    if (_nbPlayers > 1) {
                        _nbPlayers--;
                    }
                }
                else {
                    std::get<1>(it)->setText(L"COMPUTER");
                    _aiMap[types[std::get<0>(it)]] = true;
                    setupPlayerSlotSprites(it);
                    if (_nbPlayers > 1) {
                        _nbPlayers--;
                    }
                    if (_nbComputers < 3) {
                        _nbComputers++;
                    }
                }
            }
            else if (strText == "EMPTY") {
                std::get<1>(it)->setText(L"COMPUTER");
                _aiMap[types[std::get<0>(it)]] = true;
                setupPlayerSlotSprites(it);
                if (_nbComputers < 3) {
                    _nbComputers++;
                }
            }
            isPressed = true;
            type = std::get<0>(it);
            break;
        }
        else if (std::get<0>(it) == type &&
                  !std::get<1>(it)->isPressed()) {
            isPressed = false;
        }
    }
}
