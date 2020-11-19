/*
** EPITECH PROJECT, 2020
** ControlMenu
** File description:
** ControlMenu.cpp
*/

#include "ControlMenu.hpp"
#include "Game.hpp"
#include "EventListener.hpp"

ControlMenu::ControlMenu(irr::IrrlichtDevice *&device, const std::string &path) : Menu(device, path)
{
    irr::s32 buttonWidth = 267;
    irr::s32 buttonHeight = 73;
    irr::s32 pos = 300;

    addTexture((_ressourcesPath + "sprites/players_background.jpg").c_str());
    addTexture((_ressourcesPath + "sprites/background_shadow.png").c_str(), irr::core::vector2di(0, 0), std::pair<bool, bool>(false, false), irr::core::rect<irr::s32>(0, 0, 0, 0), "", false);
    addTexture((_ressourcesPath + "titles/press_button.png").c_str(), irr::core::vector2di(0, 0), std::pair<bool, bool>(true, true), irr::core::rect<irr::s32>(0, 0, 0, 0), "", false);
    addTexture((_ressourcesPath + "titles/button_assigned.png").c_str(), irr::core::vector2di(0, 0), std::pair<bool, bool>(true, true), irr::core::rect<irr::s32>(0, 0, 0, 0), "", false);
    addTexture((_ressourcesPath + "titles/controls.png").c_str(), irr::core::vector2di(0, 0), std::pair<bool, bool>(true, false));
    addTexture((_ressourcesPath + "titles/normal.png").c_str(), irr::core::vector2di(_screenSize.Width / 3 * 2 + 82 / 2 + 33, 300 + 196 / 2 - 23 / 2), std::pair<bool, bool>(false, false), irr::core::rect<irr::s32>(0, 0, 0, 0), "", true);
    addTexture((_ressourcesPath + "titles/difficult.png").c_str(), irr::core::vector2di(_screenSize.Width / 3 * 2 + 82 / 2 + 20, 300 + 196 / 2 - 23 / 2), std::pair<bool, bool>(false, false), irr::core::rect<irr::s32>(0, 0, 0, 0), "", false);
    addTexture((_ressourcesPath + "titles/easy.png").c_str(), irr::core::vector2di(_screenSize.Width / 3 * 2 + 82 / 2 + 58, 300 + 196 / 2 - 23 / 2), std::pair<bool, bool>(false, false), irr::core::rect<irr::s32>(0, 0, 0, 0), "", false);
    addTexture((_ressourcesPath + "titles/normal_lock.png").c_str(), irr::core::vector2di(_screenSize.Width / 3 * 2 + 82 / 2 + 33, 300 + 196 / 2 - 23 / 2), std::pair<bool, bool>(false, false), irr::core::rect<irr::s32>(0, 0, 0, 0), "", false);
    addTexture((_ressourcesPath + "titles/difficult_lock.png").c_str(), irr::core::vector2di(_screenSize.Width / 3 * 2 + 82 / 2 + 20, 300 + 196 / 2 - 23 / 2), std::pair<bool, bool>(false, false), irr::core::rect<irr::s32>(0, 0, 0, 0), "", false);
    addTexture((_ressourcesPath + "titles/easy_lock.png").c_str(), irr::core::vector2di(_screenSize.Width / 3 * 2 + 82 / 2 + 58, 300 + 196 / 2 - 23 / 2), std::pair<bool, bool>(false, false), irr::core::rect<irr::s32>(0, 0, 0, 0), "", false);
    _buttons.push_back(addButton(PLAY, irr::core::rect<irr::s32>(_screenSize.Width / 2 - buttonWidth / 2, pos, _screenSize.Width / 2 + buttonWidth / 2, pos + buttonHeight), L"START"));
    pos += buttonHeight + 40;
    _buttons.push_back(addButton(BEGIN, irr::core::rect<irr::s32>(_screenSize.Width / 2 - buttonWidth / 2, pos, _screenSize.Width / 2 + buttonWidth / 2, pos + buttonHeight), L"RETURN"));
    pos = 300 + 196 / 2;
    _buttons.push_back(addButton(DIFFICULTYDOWN, irr::core::rect<irr::s32>(_screenSize.Width / 3 * 2 - 82 / 2, pos - 82 / 2, _screenSize.Width / 3 * 2 + 82 / 2, pos + 82 / 2), L""));
    _buttons.push_back(addButton(DIFFICULTYUP, irr::core::rect<irr::s32>(_screenSize.Width / 3 * 2 + 278 - 82 / 2, pos - 82 / 2, _screenSize.Width / 3 * 2 + 278 + 82 / 2, pos + 82 / 2), L""));
    setButtonsState(false);
    for (auto it : _buttons) {
        switch (std::get<0>(it)) {
        case DIFFICULTYUP:
            setupRightArrow(std::get<1>(it), true);
            break;
        case DIFFICULTYDOWN:
            setupLeftArrow(std::get<1>(it), true);
            break;
        default:
            setupButtonSprite(std::get<1>(it));
            break;
        }
    }
}

bool ControlMenu::_isWaitingKey = false;

bool ControlMenu::_signalReiceived = false;

std::pair<ControlMenu::playerType, std::pair<ControlMenu::controlTypes, irr::EKEY_CODE>> ControlMenu::_associatedControl = { PNONE, { ZERO, irr::KEY_KEY_CODES_COUNT } };

std::clock_t ControlMenu::_clock = 0;

bool ControlMenu::_isKeyError = false;

bool ControlMenu::getIsWaitingKey() noexcept
{
    return _isWaitingKey;
}

std::pair<ControlMenu::playerType, std::pair<ControlMenu::controlTypes, irr::EKEY_CODE>> ControlMenu::getAssociatedControl() noexcept
{
    return _associatedControl;
}

bool ControlMenu::getSignalReiceived() noexcept
{
    return _signalReiceived;
}

bool ControlMenu::getIsKeyError() noexcept
{
    return _isKeyError;
}

void ControlMenu::setIsWaitingKey(const bool &isWaiting)
{
    _isWaitingKey = isWaiting;
}

void ControlMenu::setAssociatedControl(const std::pair<playerType, std::pair<controlTypes, irr::EKEY_CODE>> &it)
{
    _associatedControl = it;
}

void ControlMenu::setSignalReiceived(const bool &signal)
{
    _signalReiceived = signal;
}

void ControlMenu::setIsKeyError(const bool &isError)
{
    _isKeyError = isError;
}

void ControlMenu::manageAIDifficulty(const buttonTypes &type)
{
    int level = Game::getAILevel();
    int diff = 0;

    if (type == DIFFICULTYUP) {
        diff = 1;
    }
    else if (type == DIFFICULTYDOWN) {
        diff = -1;
    }
    level += diff;
    if (level > 2) {
        level = 0;
    }
    else if (level < 0) {
        level = 2;
    }
    Game::setAILevel(level);
}

void ControlMenu::setVisible(std::vector<std::tuple<buttonTypes, irr::gui::IGUIButton *, bool>> &buttons, const std::string &path,
std::vector<std::tuple<irr::video::ITexture *, irr::core::vector2di, irr::core::rect<irr::s32>, bool>> &textures, const bool &visible)
{
    for (auto all : buttons) {
        std::get<1>(all)->setEnabled(visible);
        std::get<1>(all)->setVisible(visible);
    }
    for (size_t i = 0; i < textures.size(); i++) {
        if (Tools::to_string(std::get<0>(textures[i])->getName().getPath()) == path + "sprites/background_shadow.png" ||
            Tools::to_string(std::get<0>(textures[i])->getName().getPath()) == path + "titles/press_button.png") {
            std::get<3>(textures[i]) = !visible;
        }
        if (Tools::to_string(std::get<0>(textures[i])->getName().getPath()) == path + "sprites/controls_p1.png" ||
            Tools::to_string(std::get<0>(textures[i])->getName().getPath()) == path + "sprites/controls_p2.png" ||
            Tools::to_string(std::get<0>(textures[i])->getName().getPath()) == path + "sprites/controls_p3.png" ||
            Tools::to_string(std::get<0>(textures[i])->getName().getPath()) == path + "sprites/controls_p4.png" ||
            Tools::to_string(std::get<0>(textures[i])->getName().getPath()) == path + "sprites/sound_bar_empty.png" ||
            Tools::to_string(std::get<0>(textures[i])->getName().getPath()) == path + "sprites/sound_bar_filled.png" ||
            Tools::to_string(std::get<0>(textures[i])->getName().getPath()) == path + "titles/pause_key.png" ||
            Tools::to_string(std::get<0>(textures[i])->getName().getPath()) == path + "titles/normal.png" ||
            Tools::to_string(std::get<0>(textures[i])->getName().getPath()) == path + "titles/easy.png" ||
            Tools::to_string(std::get<0>(textures[i])->getName().getPath()) == path + "titles/difficult.png" ||
            Tools::to_string(std::get<0>(textures[i])->getName().getPath()) == path + "titles/normal_lock.png" ||
            Tools::to_string(std::get<0>(textures[i])->getName().getPath()) == path + "titles/easy_lock.png" ||
            Tools::to_string(std::get<0>(textures[i])->getName().getPath()) == path + "titles/difficult_lock.png") {
            std::get<3>(textures[i]) = visible;
        }
    }
}

bool ControlMenu::canChangeControl(irr::EKEY_CODE &code)
{
    const std::map<IPlayerController::KeyType, controlTypes> correspondControls = {
        { IPlayerController::KeyType::UP, UP },
        { IPlayerController::KeyType::DOWN, DOWN },
        { IPlayerController::KeyType::RIGHT, RIGHT },
        { IPlayerController::KeyType::LEFT, LEFT },
        { IPlayerController::KeyType::BOMB, BOMB }
    };
    std::map<IScene::playerType, Player *> players = Game::getPlayerMap();
    std::vector<IPlayerController::KeyType> controls = APlayerController::getKeyTypes();
    if (code == EventListener::getKeyPause() && Menu::getControlToDefine() != MEN) {
        EventListener::reverseKey();
        return false;
    }
    auto binds = Game::getPlayersBind();
    for (auto it : binds) {
        if (it.second != nullptr) {
            for (size_t i = 0; i < controls.size(); i++) {
                irr::EKEY_CODE exists = it.second->getPlayerController()->getKeyCode(controls[i]);
                if (exists == code && (std::get<0>(it) != _associatedControl.first || correspondControls.at(controls[i]) != Menu::getControlToDefine())) {
                    EventListener::reverseKey();
                    return false;
                }
            }
        }
    }
    return true;
}

bool ControlMenu::showErrorKeyMessage(std::vector<std::tuple<buttonTypes, irr::gui::IGUIButton *, bool>> &buttons, const std::string &path,
std::vector<std::tuple<irr::video::ITexture *, irr::core::vector2di, irr::core::rect<irr::s32>, bool>> &textures)
{
    static bool isShowing = false;

    _clock += std::clock();
    if (_clock / CLOCKS_PER_SEC <= 250) {
        if (!isShowing) {
            for (size_t i = 0; i < textures.size(); i++) {
                if (Tools::to_string(std::get<0>(textures[i])->getName().getPath()) == path + "titles/press_button.png") {
                    std::get<3>(textures[i]) = false;
                }
                else if (Tools::to_string(std::get<0>(textures[i])->getName().getPath()) == path + "titles/button_assigned.png") {
                    std::get<3>(textures[i]) = true;
                }
            }
            isShowing = true;
        }
    }
    else {
        for (size_t i = 0; i < textures.size(); i++) {
            if (Tools::to_string(std::get<0>(textures[i])->getName().getPath()) == path + "titles/button_assigned.png") {
                std::get<3>(textures[i]) = false;
                break;
            }
        }
        isShowing = false;
        _isKeyError = false;
        _clock = 0;
        setVisible(buttons, path, textures, true);
        return false;
    }
    return true;
}

ControlMenu::controlTypes ControlMenu::getControlFromId(const int &id)
{
    switch (id) {
        case 1:
            return UP;
        case 2:
            return DOWN;
        case 3:
            return RIGHT;
        case 4:
            return LEFT;
        case 5:
            return BOMB;
        case 9:
            return MEN;
        default:
            break;
    }
    return ZERO;
}

bool ControlMenu::updateControls()
{
    irr::EKEY_CODE code;

    std::map<IScene::playerType, Player *> players = Game::getPlayerMap();
    if (_associatedControl.first != PNONE && _associatedControl.second.first != ZERO && _associatedControl.second.second != irr::KEY_KEY_CODES_COUNT &&
        _signalReiceived) {
        _isWaitingKey = false;
        _signalReiceived = false;
        code = _associatedControl.second.second;
        if (canChangeControl(code)) {
            return true;
        }
        else {
            _associatedControl = { PNONE, { ZERO, irr::KEY_KEY_CODES_COUNT } };
            _clock = std::clock();
            _isKeyError = true;
        }
    }
    return false;
}
