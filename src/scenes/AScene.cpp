/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** AScene.cpp
*/

#include "AScene.hpp"
#include "Menu.hpp"
#include "MenuPlayer.hpp"
#include "Pause.hpp"
#include "Game.hpp"
#include "ControlMenu.hpp"
#include "../map/Entities.hpp"
#include "../map/Logger.hpp"

AScene::AScene(irr::IrrlichtDevice *&device, const std::string &path) : _device(device), _driver(device->getVideoDriver()), _ressourcesPath(path),
_rootScene(device->getSceneManager()), _rootGUI(device->getGUIEnvironment()), _scene(_rootScene->createNewSceneManager()), _camera(_scene->addCameraSceneNode(0, {70, 70, 30}, {0, 0, 0}))
{
    _logger = new Logger(Game::_entities, _ressourcesPath);
    _screenSize = _driver->getViewPort().getSize();
}

AScene::sceneType AScene::_currentScene = AScene::MENU;
Entities *AScene::_entityClass = nullptr;
std::map<AScene::playerType, AScene::rotationTypes> AScene::_playersRotations;

const std::map<AScene::buttonTypes, AScene::sceneType> AScene::_buttonMap {
    { PLAY, GAME },
    { QUIT, EXIT },
    { OPT, OPTIONS },
    { MAIN, MENU },
    { PAUS, PAUSE },
    { BEGIN, PLAYERCHOICE },
    { PLAYER1, ADDPLAYER },
    { PLAYER2, ADDPLAYER },
    { PLAYER3, ADDPLAYER },
    { PLAYER4, ADDPLAYER },
    { CONTS, CONTROLS },
    { SOUND, MUTE },
    { SAVE, DEFAULT },
    { DIFFICULTYUP, DEFAULT },
    { DIFFICULTYDOWN, DEFAULT },
    { LOAD, GAME }
};

int AScene::_nbPlayers = 1;
int AScene::_nbComputers = 3;
std::map<AScene::sceneType, sf::Music> AScene::_musics;

irr::scene::ISceneManager *AScene::getRootScene() const noexcept
{
    return _rootScene;
}

AScene::sceneType AScene::getCurrentScene() noexcept
{
    return _currentScene;
}

std::vector<std::tuple<AScene::buttonTypes, irr::gui::IGUIButton *, bool>> AScene::getButtons() const noexcept
{
    return _buttons;
}

int AScene::getNbPlayers() const noexcept
{
    return _nbPlayers;
}

int AScene::getNbComputers() const noexcept
{
    return _nbComputers;
}

std::map<AScene::playerType, AScene::rotationTypes> AScene::getPlayersRotations() noexcept
{
    return _playersRotations;
}

void AScene::setPlayersRotations(const playerType &player, const rotationTypes &rotation)
{
    _playersRotations[player] = rotation;
}

void AScene::setCurrentScene(const sceneType &type)
{
    _currentScene = type;
}

std::tuple<AScene::buttonTypes, irr::gui::IGUIButton *, bool> AScene::addButton(const buttonTypes &type, const irr::core::rect<irr::s32> rect, const wchar_t *text, const irr::s32 id)
{
    std::tuple<buttonTypes, irr::gui::IGUIButton *, bool> tri;
    std::get<0>(tri) = type;
    std::get<1>(tri) = _rootGUI->addButton(rect, 0, id, text);
    //std::get<1>(tri)->setIsPushButton(true);
    std::get<2>(tri) = false;
    return tri;
}

void AScene::addTexture(const char *path, const irr::core::vector2di position, const std::pair<bool, bool> isCenter,
                        const irr::core::rect<irr::s32> crop, irr::io::path name, const bool &toDisplay)
{
    if (path != nullptr) {
        std::tuple<irr::video::ITexture *, irr::core::vector2di, irr::core::rect<irr::s32>, bool> params;
        irr::core::vector2di finalPos = position;
        irr::video::IImage *image = _driver->createImageFromFile(path);

        if (Tools::to_string(name) == "") {
            name = path;
        }

        irr::video::ITexture *texture = _driver->addTexture(name, image);
        if (texture != nullptr) {
            std::get<0>(params) = texture;
            if (isCenter.first) {
                finalPos.X = _screenSize.Width / 2 - (texture->getSize().Width / 2);
            }
            if (isCenter.second) {
                finalPos.Y = _screenSize.Height / 2 - (texture->getSize().Height / 2);
            }
            std::get<1>(params) = finalPos;
            if (crop.getSize().Width == 0 && crop.getSize().Height == 0) {
                irr::core::dimension2du size = texture->getSize();
                std::get<2>(params) = irr::core::rect<irr::s32>(0, 0, size.Width, size.Height);
            }
            else {
                std::get<2>(params) = crop;
            }
            std::get<3>(params) = toDisplay;
            _textures.push_back(params);
        }
    }
}

void AScene::manageButtons()
{
    buttonTypes type = NONE;
    irr::s32 id = -1;
    irr::core::vector2di mouse = _device->getCursorControl()->getPosition();

    for (size_t i = 0; i < _buttons.size(); i++) {
        if(std::get<1>(_buttons[i])->isPressed()) {
            std::get<2>(_buttons[i]) = true;
            break;
        }
        else if (!std::get<1>(_buttons[i])->isPressed() && std::get<2>(_buttons[i]) && std::get<1>(_buttons[i])->isPointInside(mouse)) {
            type = std::get<0>(_buttons[i]);
            std::get<2>(_buttons[i]) = false;
            id = std::get<1>(_buttons[i])->getID();
            break;
        }
        else if (!std::get<1>(_buttons[i])->isPointInside(mouse)) {
            std::get<2>(_buttons[i]) = false;
        }
    }
    if (type != NONE) {
        std::map<buttonTypes, sceneType>::const_iterator iterator;
        for (iterator = _buttonMap.begin(); iterator != _buttonMap.end(); iterator++) {
            if (iterator->first == type && iterator->second == ADDPLAYER) {
                break;
            }
            else if (iterator->first == type && iterator->second == MUTE) {
                updateSound();
                break;
            }
            else if (iterator->first == type) {
                if (iterator->first == BEGIN || iterator->first == MAIN) {
                    if (Scenes::getCurrentScene() == CONTROLS) {
                        auto players = Game::getPlayerMap();
                        for (auto it : players) {
                            it.second->getPlayerController()->savePlayerPref();
                        }
                    }
                    Game::clearPlayerMap();
                    Game::clearMap();
                }
                else if (iterator->first == PLAY && _currentScene == CONTROLS) {
                    auto players = Game::getPlayerMap();
                    auto keys = APlayerController::getKeyTypes();
                    for (auto it : players) {
                        for (size_t i = 0; i < keys.size(); i++) {
                            if (it.second->getPlayerController()->getKeyCode(keys[i]) == irr::KEY_KEY_CODES_COUNT) {
                                Scenes::setCurrentScene(CONTROLS);
                                return;
                            }
                        }
                    }
                    Game::setMap(_ressourcesPath + "maps/map.txt");
                    _entityClass = new Entities(Game::getMap(), Game::_entities);
                    _entityClass->fillEntities();
                    Game::_entities = _entityClass->getEntities();
                    for (auto it : players) {
                        it.second->getPlayerController()->savePlayerPref();
                    }
                }
                if (_currentScene == PAUSE && (iterator->first == MAIN || iterator->first == QUIT) && !Pause::getIsWaiting()) {
                    Pause::setIsWaiting(true);
                    Pause::setAction(iterator->first);
                    displayGameSaving(true);
                }
                else if (iterator->first == SAVE && Pause::getIsWaiting()) {
                    Pause::setIsWaiting(false);
                    displayGameSaving(false);
                    manageSavingButtons(id);
                }
                else if (iterator->first == DIFFICULTYUP || iterator->first == DIFFICULTYDOWN) {
                    ControlMenu::manageAIDifficulty(iterator->first);
                    manageDifficultyText();
                }
                else if (iterator->first == LOAD) {
                    _logger->LoggerMap();
                    setCurrentScene(iterator->second);
                }
                else {
                    setCurrentScene(iterator->second);
                }
                break;
            }
        }
    }
}

void AScene::setAIMap(const playerType &type, const bool &isPresent)
{
    _aiMap[type] = isPresent;
}

void AScene::setPlayerMap(const playerType &type, const bool &isPresent)
{
    std::map<playerType, buttonTypes> buttons = {
        { P1, PLAYER1 },
        { P2, PLAYER2 },
        { P3, PLAYER3 },
        { P4, PLAYER4 }
    };
    _playersMap[buttons[type]] = isPresent;
}

void AScene::manageSavingButtons(const irr::s32 &id)
{
    for (size_t i = 0; i < _buttons.size(); i++) {
        if (id == std::get<1>(_buttons[i])->getID()) {
            if (id == 20 && Pause::getAction() != NONE) {
                if (_logger == nullptr) {
                    _logger = new Logger(Game::_entities, _ressourcesPath);
                }
                if (_logger->SaveLog()) {
                    std::cerr << "Game saved" << std::endl;
                }
                setCurrentScene(_buttonMap.at(Pause::getAction()));
                Game::clearPlayerMap();
                Game::clearAll();
                clearEntities();
            }
            else if (id == 21 && Pause::getAction() != NONE) {
                setCurrentScene(_buttonMap.at(Pause::getAction()));
                Game::clearPlayerMap();
                Game::clearAll();
                clearEntities();
            }
            else if (id == 22) {
            }
        break;
        }
    }
}

void AScene::setButtonsState(const bool state)
{
    std::map<buttonTypes, irr::gui::IGUIButton *>::const_iterator it;

    if (!_buttons.empty()) {
        for (size_t i = 0; i < _buttons.size(); i++) {
            std::get<1>(_buttons[i])->setVisible(state);
        }
    }
}

void AScene::setSavingButtonsState(const bool &state)
{
    if (!_buttons.empty()) {
        for (size_t i = 0; i < _buttons.size(); i++) {
            if (std::get<1>(_buttons[i])->getID() >= 20 && std::get<1>(_buttons[i])->getID() <= 22) {
                std::get<1>(_buttons[i])->setVisible(state);
            }
        }
    }
}
