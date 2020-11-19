/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** AScene.cpp
*/

#include "AScene.hpp"
#include "Menu.hpp"
#include "ControlMenu.hpp"
#include "../entity/character/player/APlayerController.hpp"
#include "../entity/power_up/PowerUp.hpp"
#include "../map/Entities.hpp"
#include "../map/MapGenerator.hpp"
#include "WinMenu.hpp"
#include <tuple>
#include "Game.hpp"
#include "EventListener.hpp"

/*std::map<AScene::playerType, std::map<AScene::controlTypes, irr::EKEY_CODE>> AScene::_controls {
    { P1, { { UP, irr::KEY_KEY_Z }, { DOWN, irr::KEY_KEY_S }, { LEFT, irr::KEY_KEY_Q }, { RIGHT, irr::KEY_KEY_D }, { BOMB, irr::KEY_KEY_E } }},
    { P2, { { UP, irr::KEY_UP }, { DOWN, irr::KEY_DOWN }, { LEFT, irr::KEY_LEFT }, { RIGHT, irr::KEY_RIGHT }, { BOMB, irr::KEY_RETURN } }},
    { P3, { { UP, irr::KEY_KEY_T }, { DOWN, irr::KEY_KEY_G }, { LEFT, irr::KEY_KEY_F }, { RIGHT, irr::KEY_KEY_H }, { BOMB, irr::KEY_KEY_Y } }},
    { P4, { { UP, irr::KEY_KEY_O }, { DOWN, irr::KEY_KEY_L }, { LEFT, irr::KEY_KEY_K }, { RIGHT, irr::KEY_KEY_M }, { BOMB, irr::KEY_KEY_P } }},
    { PALL, { { MEN, irr::KEY_ESCAPE } }}
};*/

irr::EKEY_CODE AScene::_keyDetectedToParam = irr::KEY_KEY_CODES_COUNT;
float AScene::_musicsVolume = 100;
std::map<AScene::SoundEffect, sf::Music> AScene::_soundEffects;
bool AScene::_isMuted = false;
entityMap AScene::_entities;
std::vector<irr::scene::IAnimatedMeshSceneNode *> AScene::_playerAssets;
std::vector<irr::scene::IAnimatedMeshSceneNode *> AScene::_characterAssets;
std::vector<irr::scene::IAnimatedMeshSceneNode *> AScene::_aiAssets;
std::map<IEntity::EntityType, std::vector<irr::scene::IMeshSceneNode *>> AScene::_assets = {};
std::map<IEntity::EntityType, std::vector<irr::scene::IAnimatedMeshSceneNode *>> AScene::_animatedAssets = {};
std::map<IEntity::EntityType, irr::scene::IAnimatedMesh *> AScene::_animatedMesh = {};

std::map<AScene::playerType, bool> AScene::_aiMap = {
    { P1, false },
    { P2, true },
    { P3, true },
    { P4, true }
};

void AScene::manageControls()
{
    static bool isPressed = false;
    static buttonTypes type = NONE;
    static irr::s32 control = -1;

    const std::map<controlTypes, IPlayerController::KeyType> correspondControls = {
        { UP, IPlayerController::KeyType::UP },
        { DOWN, IPlayerController::KeyType::DOWN },
        { RIGHT, IPlayerController::KeyType::RIGHT },
        { LEFT, IPlayerController::KeyType::LEFT },
        { BOMB, IPlayerController::KeyType::BOMB },
        { MEN, IPlayerController::KeyType::MEN }
    };
    for (auto it : _buttons) {
        if ((std::get<0>(it) == PLAYER1 || std::get<0>(it) == PLAYER2 || std::get<0>(it) == PLAYER3 || std::get<0>(it) == PLAYER4 || std::get<0>(it) == PAUSEBUTTON) &&
            std::get<1>(it)->isPressed() && !isPressed) {
            type = std::get<0>(it);
            control = std::get<1>(it)->getID();
            isPressed = true;
            break;
        }
        else if (std::get<0>(it) == type && std::get<1>(it)->getID() == control &&
                 !std::get<1>(it)->isPressed()) {
            ControlMenu::setIsWaitingKey(true);
            auto associateControl = ControlMenu::getAssociatedControl();
            associateControl.first = _buttonPlayersMap[std::get<0>(it)];
            auto player = Game::getPlayerMap()[_buttonPlayersMap[std::get<0>(it)]];
            ControlMenu::setAssociatedControl(associateControl);
            
            switch (std::get<1>(it)->getID()) {
            case 1:
                Menu::setControlToDefine(UP);
                break;
            case 2:
                Menu::setControlToDefine(DOWN);
                break;
            case 3:
                Menu::setControlToDefine(RIGHT);
                break;
            case 4:
                Menu::setControlToDefine(LEFT);
                break;
            case 5:
                Menu::setControlToDefine(BOMB);
                break;
            case 9:
                Menu::setControlToDefine(MEN);
                break;
            default:
                break;
            }
            IPlayerController::KeyType key = correspondControls.at(Menu::getControlToDefine());
            if (type != PAUSEBUTTON) {
                EventListener::setWatingKey(player->getPlayerController()->setKeyCode(key));
            }
            ControlMenu::setVisible(_buttons, _ressourcesPath, _textures, false);
            type = NONE;
            control = -1;
            isPressed = false;
        }
    }
}

std::map<AScene::buttonTypes, bool> AScene::_playersMap {
    { PLAYER1, true },
    { PLAYER2, false },
    { PLAYER3, false },
    { PLAYER4, false }
};

std::map<AScene::buttonTypes, AScene::playerType> AScene::_buttonPlayersMap {
    { PLAYER1, P1 },
    { PLAYER2, P2 },
    { PLAYER3, P3 },
    { PLAYER4, P4 },
    { PAUSEBUTTON, PALL}
};

void AScene::removeControlSlots()
{
    for (size_t i = 0; i < 4; i++) {
        irr::video::ITexture *texture = _driver->getTexture((_ressourcesPath + "sprites/controls_p" + std::to_string(i + 1) + ".png").c_str());
        std::vector<std::tuple<irr::video::ITexture *, irr::core::vector2di, irr::core::rect<irr::s32>, bool>>::iterator it = _textures.begin();
        for (size_t i = 0; i < _textures.size() && it != _textures.end(); i++, it++) {
            if (Tools::to_string(std::get<0>(_textures[i])->getName().getPath()) == Tools::to_string(texture->getName().getPath())) {
                _textures.erase(it);
                break;
            }
        }
        if (texture != nullptr) {
            _driver->removeTexture(texture);
        }
    }
    std::vector<std::tuple<buttonTypes, irr::gui::IGUIButton *, bool>>::iterator itButton = _buttons.begin();
    for (size_t i = 0; i < _buttons.size() && itButton != _buttons.end(); i++) {
        if (std::get<1>(_buttons[i])->getID() >= 1 && std::get<1>(_buttons[i])->getID() <= 5) {
            std::get<1>(_buttons[i])->remove();
            itButton = _buttons.erase(itButton);
            i--;
        }
        else {
            itButton++;
        }
    }
}

void AScene::addControlSlots()
{
    irr::s32 slotWidth = 324;
    irr::s32 slotPosX = 0;
    irr::s32 slotPosY = 600;

    const std::map<IPlayerController::KeyType, controlTypes> correspondControls = {
        { IPlayerController::KeyType::UP, UP },
        { IPlayerController::KeyType::DOWN, DOWN },
        { IPlayerController::KeyType::RIGHT, RIGHT },
        { IPlayerController::KeyType::LEFT, LEFT },
        { IPlayerController::KeyType::BOMB, BOMB },
        { IPlayerController::KeyType::MEN, MEN }
    };
    const std::map<playerType, buttonTypes> correspondPlayers = {
        { P1, PLAYER1 },
        { P2, PLAYER2 },
        { P3, PLAYER3 },
        { P4, PLAYER4 }
    };
    if (_nbPlayers > 0) {
        std::map<IScene::playerType, Player *> players = Game::getPlayerMap();
        std::map<IScene::playerType, Player *>::iterator it = players.begin();
        slotPosX = (_screenSize.Width / _nbPlayers - slotWidth) / 2;
        for (size_t i = 0; i < players.size() && it != players.end(); i++, it++) {
            irr::s32 buttonWidth = 69;
            irr::s32 buttonHeight = 67;
            std::vector<irr::s32> posX = { slotPosX + 20, 185, 0, -185, 95 };
            std::vector<irr::s32> posY = { slotPosY + 60, 0, 130, 0, -60 };
            std::vector<IPlayerController::KeyType> controls = { IPlayerController::KeyType::UP, IPlayerController::KeyType::DOWN, IPlayerController::KeyType::RIGHT, IPlayerController::KeyType::LEFT, IPlayerController::KeyType::BOMB };
            irr::s32 buttonPosX = 0;
            irr::s32 buttonPosY = 0;

            int nbTexture = static_cast<int>(it->first);
            if (nbTexture <= 4 && nbTexture > 0) {
                addTexture((_ressourcesPath + "sprites/controls_p" + std::to_string(nbTexture) + ".png").c_str(), irr::core::vector2di(slotPosX, slotPosY));
            }
            for (size_t i = 0; i < posX.size() && i < posY.size() && controls.size(); i++) {
                buttonPosX += posX[i];
                buttonPosY += posY[i];
                auto eventIt = APlayerController::getEventToString().at(it->second->getPlayerController()->getKeyCode(controls[i]));
                _buttons.push_back(addButton(correspondPlayers.at(it->first), irr::core::rect<irr::s32>(buttonPosX, buttonPosY, buttonPosX + buttonWidth, buttonPosY + buttonHeight), eventIt, i + 1));
            }
            slotPosX += slotWidth + _screenSize.Width / _nbPlayers - slotWidth;
        }
    }
    std::vector<std::tuple<buttonTypes, irr::gui::IGUIButton *, bool>>::iterator itButton = _buttons.begin();
    for (size_t i = 0; i < _buttons.size() && itButton != _buttons.end(); i++, itButton++) {
        if (std::get<1>(_buttons[i])->getID() >= 1 && std::get<1>(_buttons[i])->getID() <= 5) {
            std::get<1>(_buttons[i])->setSpriteBank(Menu::getSpriteBank());
            std::get<1>(_buttons[i])->setSprite(irr::gui::EGBS_BUTTON_UP, 8);
            std::get<1>(_buttons[i])->setDrawBorder(false);
            std::get<1>(_buttons[i])->setUseAlphaChannel(true);
        }
    }
}

irr::EKEY_CODE AScene::getKeyDetectedToParam() noexcept
{
    return _keyDetectedToParam;
}

void AScene::setKeyDetectedToParam(const irr::EKEY_CODE &key)
{
    _keyDetectedToParam = key;
}

void AScene::updateControlButtons()
{
    const std::map<controlTypes, IPlayerController::KeyType> correspondControls = {
        { UP, IPlayerController::KeyType::UP },
        { DOWN, IPlayerController::KeyType::DOWN },
        { RIGHT, IPlayerController::KeyType::RIGHT },
        { LEFT, IPlayerController::KeyType::LEFT },
        { BOMB, IPlayerController::KeyType::BOMB },
        { MEN, IPlayerController::KeyType::MEN }
    };
    std::map<IScene::playerType, Player *> players = Game::getPlayerMap();
    for (size_t i = 0; i < _buttons.size(); i++) {
        controlTypes type = ControlMenu::getControlFromId(std::get<1>(_buttons[i])->getID());
        if ((std::get<1>(_buttons[i])->getID() >= 1 && std::get<1>(_buttons[i])->getID() <= 5)) {
            if (type != ZERO) {
                auto eventIt = APlayerController::getEventToString()[players[_buttonPlayersMap[std::get<0>(_buttons[i])]]->getPlayerController()->getKeyCode(correspondControls.at(type))];
                std::get<1>(_buttons[i])->setText(eventIt);
            }
        }
        else if (std::get<1>(_buttons[i])->getID() == 9) {
            if (type != ZERO) {
                auto eventIt = APlayerController::getEventToString()[EventListener::getKeyPause()];
                std::get<1>(_buttons[i])->setText(eventIt);
            }
        }
    }
    ControlMenu::setVisible(_buttons, _ressourcesPath, _textures, true);
    manageDifficultyText();
}

void AScene::updateSound()
{
    irr::s32 id = 0;

    for (size_t i = 0; i < _buttons.size(); i++) {
        if (std::get<1>(_buttons[i])->getID() == 6) {
            id = std::get<1>(_buttons[i])->getID();
            std::get<1>(_buttons[i])->setID(7);
            std::get<1>(_buttons[i])->setSprite(irr::gui::EGBS_BUTTON_MOUSE_OFF, 12);
            std::get<1>(_buttons[i])->setSprite(irr::gui::EGBS_BUTTON_DOWN, 14);
            std::get<1>(_buttons[i])->setSprite(irr::gui::EGBS_BUTTON_UP, 13);
            _isMuted = true;
            break;
        }
        else if (std::get<1>(_buttons[i])->getID() == 7) {
            id = std::get<1>(_buttons[i])->getID();
            std::get<1>(_buttons[i])->setID(6);
            std::get<1>(_buttons[i])->setSprite(irr::gui::EGBS_BUTTON_MOUSE_OFF, 9);
            std::get<1>(_buttons[i])->setSprite(irr::gui::EGBS_BUTTON_DOWN, 11);
            std::get<1>(_buttons[i])->setSprite(irr::gui::EGBS_BUTTON_UP, 10);
            _isMuted = false;
            break;
        }
    }
    std::map<sceneType, sf::Music>::iterator it;
    for (it = _musics.begin(); it != _musics.end(); it++) {
        if (id == 6) {
            _musicsVolume = it->second.getVolume();
            it->second.setVolume(0);
        }
        else if (id == 7) {
            it->second.setVolume(_musicsVolume);
        }
    }
    std::map<SoundEffect, sf::Music>::iterator it2 = _soundEffects.begin();
    for (; it2 != _soundEffects.end(); it2++) {
        if (id == 6) {
            it2->second.setVolume(0);
        }
        else if (id == 7) {
            it2->second.setVolume(_musicsVolume);
        }
    }
    if (id == 6) {
        WinMenu::setIntroVolume(0);
    }
    else if (id == 7) {
        WinMenu::setIntroVolume(_musicsVolume);
    }
}

void AScene::displayGameSaving(const bool &display)
{
    for (size_t i = 0; i < _textures.size(); i++) {
        std::string name = Tools::to_string(std::get<0>(_textures[i])->getName().getPath());
        if (name == _ressourcesPath + "sprites/background_shadow.png" || name == _ressourcesPath + "titles/save.png") {
            std::get<3>(_textures[i]) = display;
        }
    }
    for (size_t i = 0; i < _buttons.size(); i++) {
        std::get<1>(_buttons[i])->setVisible(!display);
    }
    setSavingButtonsState(display);
}

void AScene::takeEntities()
{
    size_t playerID = 0;

    for (auto it = _entities.begin(); it != _entities.end(); it++) {
        switch (it->first) {
        case IEntity::UNBREAKABLEWALL:
            for (size_t i = 0; i < it->second.size(); i++) {
                _assets[it->first].push_back(_scene->addCubeSceneNode(10.0f, 0, -1, it->second[i]->getPos()));
                _assets[it->first][i]->setMaterialTexture(0, _driver->getTexture((_ressourcesPath + "asset/wall.png").c_str()));
            }
            break;
        case IEntity::BREAKABLEWALL:
            for (size_t i = 0; i < it->second.size(); i++) {
                _assets[it->first].push_back(_scene->addCubeSceneNode(10.0f, 0, -1, it->second[i]->getPos()));
                _assets[it->first][i]->setMaterialTexture(0, _driver->getTexture((_ressourcesPath + "asset/box.png").c_str()));
            }
            break;
        case IEntity::BONUS:
            for (size_t i = 0; i < it->second.size(); i++) {
                _assets[it->first].push_back(_scene->addCubeSceneNode(7.0f, 0, -1, it->second[i]->getPos()));
                EntityPowerUp *power = dynamic_cast<EntityPowerUp *>(it->second[i]);
                switch (power->getPowerUpType()) {
                case IPowerUp::PowerUpType::RANGE:
                    _assets[it->first][i]->setMaterialTexture(0, _driver->getTexture((_ressourcesPath + "asset/rangePowerUp.png").c_str()));
                    break;
                case IPowerUp::PowerUpType::SPEED:
                    _assets[it->first][i]->setMaterialTexture(0, _driver->getTexture((_ressourcesPath + "asset/speedPowerUp.png").c_str()));
                    break;
                case IPowerUp::PowerUpType::WALLPASS:
                    _assets[it->first][i]->setMaterialTexture(0, _driver->getTexture((_ressourcesPath + "asset/wallPowerUp.png").c_str()));
                    break;
                case IPowerUp::PowerUpType::NBBOMB:
                    _assets[it->first][i]->setMaterialTexture(0, _driver->getTexture((_ressourcesPath + "asset/bombPowerUp.png").c_str()));
                    break;
                default:
                    break;
                }
                _assets[it->first][i]->setRotation({90, 0, 0});
            }
            break;
        case IEntity::PLAYER:
            for (size_t i = 0; i < it->second.size() && i < _playerAssets.size(); i++) {
                ACharacter *player = static_cast<ACharacter *>(it->second[i]);
                auto rotation = getPlayersRotations()[player->getPlayerType()];
                auto state = Game::getStatesAnimations()[player->getPlayerState()];
                irr::core::vector3df pos(-1000, -1000, -1000);
                if (!player->getIsDead()) {
                    pos = it->second[i]->getPos();
                    pos.Y -= 10;
                }
                _playerAssets[i]->setPosition(pos);
                _playerAssets[i]->setRotation(Game::getRotations()[rotation]);
                auto previousState = Game::getPlayersStates()[player->getPlayerType()];
                if (previousState != player->getPlayerState()) {
                    _playerAssets[i]->setFrameLoop(state.first, state.second);
                    Game::setPlayersStates(player->getPlayerType(), player->getPlayerState());
                }
            }
            break;
        case IEntity::IA:
            for (size_t i = 0; i < it->second.size() && i < _aiAssets.size(); i++) {
                ACharacter *ai = static_cast<ACharacter *>(it->second[i]);
                auto rotation = getPlayersRotations()[ai->getPlayerType()];
                auto state = Game::getStatesAnimations()[ai->getPlayerState()];
                irr::core::vector3df pos(-1000, -1000, -1000);
                if (!ai->getIsDead()) {
                    pos = it->second[i]->getPos();
                    pos.Y -= 10;
                }
                _aiAssets[i]->setPosition(pos);
                _aiAssets[i]->setRotation(Game::getRotations()[rotation]);
                auto previousState = Game::getPlayersStates()[ai->getPlayerType()];
                if (previousState != ai->getPlayerState()) {
                    _aiAssets[i]->setFrameLoop(state.first, state.second);
                    Game::setPlayersStates(ai->getPlayerType(), ai->getPlayerState());
                }
            }
            break;
        case IEntity::BOMB:
            for (size_t i = 0; i < it->second.size(); i++) {
                irr::core::vector3df pos = it->second[i]->getPos();
                pos.Y -= 10;
                _animatedAssets[it->first].push_back(_scene->addAnimatedMeshSceneNode(_scene->getMesh((_ressourcesPath + "asset/bomb.b3d").c_str()), 0, -1, pos, {0, 0, 0}, {8, 8, 8}));
                _animatedAssets[it->first][i]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
                _animatedAssets[it->first][i]->setMaterialTexture( 0, _driver->getTexture((_ressourcesPath + "asset/bomb.png").c_str()));
            }
            break;
        case IEntity::FIRE:
            for (size_t i = 0; i < it->second.size(); i++) {
                irr::core::vector3df pos = it->second[i]->getPos();
                pos.Y -= 10;
                _animatedAssets[it->first].push_back(_scene->addAnimatedMeshSceneNode(_scene->getMesh((_ressourcesPath + "asset/fire.b3d").c_str()), 0, -1, pos, {0, 0, 0}, {8, 8, 8}));
                _animatedAssets[it->first][i]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
                _animatedAssets[it->first][i]->setMaterialTexture( 0, _driver->getTexture((_ressourcesPath + "asset/fire.png").c_str()));
            }
            break;
        default:
            break;
        }
    }
    _camera->bindTargetAndRotation(true);
    _camera->setRotation({75, 0, 0});
}

void AScene::clearEntities()
{
    for (auto it = _assets.begin(); it != _assets.end(); it++) {
        for (size_t i = 0; i < it->second.size(); i++) {
            it->second[i]->remove();
        }
    }
    _assets.clear();
    for (auto it = _animatedAssets.begin(); it != _animatedAssets.end(); it++) {
        for (size_t i = 0; i < it->second.size(); i++) {
            it->second[i]->remove();
        }
    }
    _animatedAssets.clear();
}

void AScene::setupLeftArrow(irr::gui::IGUIButton *button, const bool &enabled)
{
    button->setSpriteBank(Menu::getSpriteBank());
    if (enabled) {
        button->setSprite(irr::gui::EGBS_BUTTON_MOUSE_OFF, 21);
        button->setSprite(irr::gui::EGBS_BUTTON_DOWN, 23);
        button->setSprite(irr::gui::EGBS_BUTTON_UP, 22);
    }
    else {
        button->setSprite(irr::gui::EGBS_BUTTON_MOUSE_OFF, 24);
        button->setSprite(irr::gui::EGBS_BUTTON_DOWN, 24);
        button->setSprite(irr::gui::EGBS_BUTTON_UP, 24);
    }
    button->setDrawBorder(false);
    button->setUseAlphaChannel(true);
}

void AScene::setupRightArrow(irr::gui::IGUIButton *button, const bool &enabled)
{
    button->setSpriteBank(Menu::getSpriteBank());
    if (enabled) {
        button->setSprite(irr::gui::EGBS_BUTTON_MOUSE_OFF, 18);
        button->setSprite(irr::gui::EGBS_BUTTON_DOWN, 20);
        button->setSprite(irr::gui::EGBS_BUTTON_UP, 19);
    }
    else {
        button->setSprite(irr::gui::EGBS_BUTTON_MOUSE_OFF, 25);
        button->setSprite(irr::gui::EGBS_BUTTON_DOWN, 25);
        button->setSprite(irr::gui::EGBS_BUTTON_UP, 25);
    }
    button->setDrawBorder(false);
    button->setUseAlphaChannel(true);
}

void AScene::manageDifficultyText()
{
    bool enabled = true;

    if (_nbComputers <= 0) {
        enabled = false;
    }
    std::map<int, std::string> levels_enabled = {
        { 0, _ressourcesPath + "titles/easy.png" },
        { 1, _ressourcesPath + "titles/normal.png" },
        { 2, _ressourcesPath + "titles/difficult.png" }
    };
    std::map<int, std::string> levels_disabled = {
        { 0, _ressourcesPath + "titles/easy_lock.png" },
        { 1, _ressourcesPath + "titles/normal_lock.png" },
        { 2, _ressourcesPath + "titles/difficult_lock.png" }
    };
    for (size_t i = 0; i < _textures.size(); i++) {
        std::string name = Tools::to_string(std::get<0>(_textures[i])->getName().getPath());
        if (name == _ressourcesPath + "titles/normal.png" || name == _ressourcesPath + "titles/difficult.png" || name == _ressourcesPath + "titles/easy.png" ||
        name == _ressourcesPath + "titles/normal_lock.png" || name == _ressourcesPath + "titles/difficult_lock.png" || name == _ressourcesPath + "titles/easy_lock.png") {
            if (enabled && levels_enabled[Game::getAILevel()] == name) {
                std::get<3>(_textures[i]) = true;
            }
            else if (!enabled && levels_disabled[Game::getAILevel()] == name) {
                std::get<3>(_textures[i]) = true;
            }
            else {
                std::get<3>(_textures[i]) = false;
            }
        }
    }
}

void AScene::manageDifficultyButtons()
{
    bool enabled = true;

    if (_nbComputers <= 0) {
        enabled = false;
    }
    for (size_t i = 0; i < _buttons.size(); i++) {
        if (std::get<0>(_buttons[i]) == DIFFICULTYUP || std::get<0>(_buttons[i]) == DIFFICULTYDOWN) {
            std::get<1>(_buttons[i])->setEnabled(enabled);
            if (std::get<0>(_buttons[i]) == DIFFICULTYUP) {
                setupRightArrow(std::get<1>(_buttons[i]), enabled);
            }
            else if (std::get<0>(_buttons[i]) == DIFFICULTYDOWN) {
                setupLeftArrow(std::get<1>(_buttons[i]), enabled);
            }
        }
    }
}

void AScene::updateLoadButton(const bool &enabled)
{
    for (auto it : _buttons) {
        if (std::get<0>(it) == LOAD) {
            std::get<1>(it)->setEnabled(enabled);
            break;
        }
    }
}

void AScene::fillPlayerAndAIAssets()
{
    size_t i = 0;

    std::map<playerType, size_t> types = {
        { P1, 0 },
        { P2, 1 },
        { P3, 2 },
        { P4, 3 }
    };
    auto players = Game::getPlayerMap();
    for (auto it : players) {
        if (i < _characterAssets.size()) {
            _playerAssets.push_back(_characterAssets[types[it.first]]);
        }
        i++;
    }
    i = 0;
    auto ais = _aiMap;
    for (auto it : ais) {
        if (i < _characterAssets.size()) {
            if (it.second) {
                _aiAssets.push_back(_characterAssets[types[it.first]]);
            }
        }
        i++;
    }
}

std::map<AScene::playerType, bool> AScene::getAIMap() noexcept
{
    return _aiMap;
}