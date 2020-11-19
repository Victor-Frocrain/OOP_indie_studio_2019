/*
** EPITECH PROJECT, 2020
** Options
** File description:
** Options.cpp
*/

#include "Options.hpp"
#include "../entity/character/player/APlayerController.hpp"
#include "EventListener.hpp"

Options::Options(irr::IrrlichtDevice *&device, const std::string &path) : Menu(device, path)
{
    irr::s32 buttonWidth = 267;
    irr::s32 buttonHeight = 73;
    irr::s32 pos = 300;

    addTexture((_ressourcesPath + "sprites/menu_background.png").c_str());
    addTexture((_ressourcesPath + "sprites/background_shadow.png").c_str(), irr::core::vector2di(0, 0), std::pair<bool, bool>(false, false), irr::core::rect<irr::s32>(0, 0, 0, 0), "", false);
    addTexture((_ressourcesPath + "titles/press_button.png").c_str(), irr::core::vector2di(0, 0), std::pair<bool, bool>(true, true), irr::core::rect<irr::s32>(0, 0, 0, 0), "", false);
    addTexture((_ressourcesPath + "titles/button_assigned.png").c_str(), irr::core::vector2di(0, 0), std::pair<bool, bool>(true, true), irr::core::rect<irr::s32>(0, 0, 0, 0), "", false);
    addTexture((_ressourcesPath + "titles/options.png").c_str(), irr::core::vector2di(0, 0), std::pair<bool, bool>(true, false));
    addTexture((_ressourcesPath + "sprites/sound_bar_empty.png").c_str(), irr::core::vector2di(_screenSize.Width / 2 - 476 / 2 + 102 / 2, pos + 54 / 4), std::pair<bool, bool>(false, false));
    addTexture((_ressourcesPath + "sprites/sound_bar_filled.png").c_str(), irr::core::vector2di(_screenSize.Width / 2 - 476 / 2 + 102 / 2, pos + 54 / 4), std::pair<bool, bool>(false, false));
    _buttons.push_back(addButton(SOUND, irr::core::rect<irr::s32>(_screenSize.Width / 2 - 82 / 2 - 496 / 2, pos, _screenSize.Width / 2 + 82 / 2 - 496 / 2, pos + 82), 0, 6));
    for (auto it : _textures) {
        if (Tools::to_string(std::get<0>(it)->getName().getPath()) == _ressourcesPath + "sprites/sound_bar_empty.png") {
            _buttons.push_back(addButton(SOUNDCURSOR, irr::core::rect<irr::s32>(std::get<1>(it).X + 476 - 53, pos + 54 / 4, std::get<1>(it).X + 476, pos + 54 + 54 / 4), 0, 8));
            break;
        }
    }
    pos += 82 + 40;
    addTexture((_ressourcesPath + "titles/pause_key.png").c_str(), irr::core::vector2di(_screenSize.Width / 2 - 302 / 2 - 89 / 2, pos + 37 / 4), std::pair<bool, bool>(false, false));
    _buttons.push_back(addButton(PAUSEBUTTON, irr::core::rect<irr::s32>(_screenSize.Width / 2 - 69 / 2 + 322 / 2 , pos, _screenSize.Width / 2 + 69 / 2 + 322 / 2 , pos + 67), APlayerController::getEventToString()[EventListener::getKeyPause()], 9));
    pos += 67 + 40;
    _buttons.push_back(addButton(MAIN, irr::core::rect<irr::s32>(_screenSize.Width / 2 - buttonWidth / 2, pos, _screenSize.Width / 2 + buttonWidth / 2, pos + buttonHeight), L"RETURN"));
    setButtonsState(false);
    for (auto it : _buttons) {
        if (std::get<0>(it) == SOUND) {
            setupSoundButton(std::get<1>(it));
        }
        else if (std::get<0>(it) == SOUNDCURSOR) {
            setupCursorSound(std::get<1>(it));
        }
        else if (std::get<0>(it) == PAUSEBUTTON) {
            setupPauseButton(std::get<1>(it));
        }
        else {
            setupButtonSprite(std::get<1>(it));
        }
    }
}

Options::~Options()
{}

void Options::setupPauseButton(irr::gui::IGUIButton *button)
{
    button->setSpriteBank(_buttonSprite);
    button->setSprite(irr::gui::EGBS_BUTTON_UP, 8);
    button->setDrawBorder(false);
    button->setUseAlphaChannel(true);
}

void Options::setupSoundButton(irr::gui::IGUIButton *button)
{
    button->setSpriteBank(_buttonSprite);
    button->setSprite(irr::gui::EGBS_BUTTON_MOUSE_OFF, 9);
    button->setSprite(irr::gui::EGBS_BUTTON_DOWN, 11);
    button->setSprite(irr::gui::EGBS_BUTTON_UP, 10);
    button->setDrawBorder(false);
    button->setUseAlphaChannel(true);
}

void Options::setupCursorSound(irr::gui::IGUIButton *button)
{
    button->setSpriteBank(_buttonSprite);
    button->setSprite(irr::gui::EGBS_BUTTON_UP, 15);
    button->setSprite(irr::gui::EGBS_BUTTON_DOWN, 17);
    button->setSprite(irr::gui::EGBS_BUTTON_MOUSE_OVER, 16);
    button->setDrawBorder(false);
    button->setUseAlphaChannel(true);
}