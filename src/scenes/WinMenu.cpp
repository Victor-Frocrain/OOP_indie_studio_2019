/*
** EPITECH PROJECT, 2020
** WinMenu
** File description:
** WinMenu.cpp
*/

#include "WinMenu.hpp"
#include "Game.hpp"

WinMenu::WinMenu(irr::IrrlichtDevice *&device, const std::string &path) : Menu(device, path)
{
    irr::s32 buttonWidth = 267;
    irr::s32 buttonHeight = 73;
    irr::s32 pos = 300;

    addTexture((_ressourcesPath + "sprites/victory_background.png").c_str(), irr::core::vector2di(0, 0));
    addTexture((_ressourcesPath + "titles/congratulations.png").c_str(), irr::core::vector2di(0, 0), std::pair<bool, bool>(true, false));
    _buttons.push_back(addButton(MAIN, irr::core::rect<irr::s32>(_screenSize.Width / 2 - buttonWidth / 2, pos, _screenSize.Width / 2 + buttonWidth / 2, pos + buttonHeight), L"MAIN MENU"));
    pos += buttonHeight + 40;
    _buttons.push_back(addButton(QUIT, irr::core::rect<irr::s32>(_screenSize.Width / 2 - buttonWidth / 2, pos, _screenSize.Width / 2 + buttonWidth / 2, pos + buttonHeight), L"QUIT"));
    setButtonsState(false);
    for (auto it : _buttons) {
        setupButtonSprite(std::get<1>(it));
    }

    addTexture((_ressourcesPath + "asset/player1.png").c_str(), irr::core::vector2di(0, 0), std::pair<bool, bool>(true, true), irr::core::rect<irr::s32>(0, 0, 0, 0), "", false);
    addTexture((_ressourcesPath + "asset/player2.png").c_str(), irr::core::vector2di(0, 0), std::pair<bool, bool>(true, true), irr::core::rect<irr::s32>(0, 0, 0, 0), "", false);
    addTexture((_ressourcesPath + "asset/player3.png").c_str(), irr::core::vector2di(0, 0), std::pair<bool, bool>(true, true), irr::core::rect<irr::s32>(0, 0, 0, 0), "", false);
    addTexture((_ressourcesPath + "asset/player4.png").c_str(), irr::core::vector2di(0, 0), std::pair<bool, bool>(true, true), irr::core::rect<irr::s32>(0, 0, 0, 0), "", false);

    std::vector<playerType> types = { P1, P2, P3, P4 };
    for (size_t i = 0; i < 4; i++) {
        _playerModels[types[i]] = _scene->addAnimatedMeshSceneNode(_scene->getMesh((_ressourcesPath + "asset/player.b3d").c_str()), 0, -1, {-1000, -1000, -1000}, {0, 0, 0}, {10, 10, 10});
        _playerModels[types[i]]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        _playerModels[types[i]]->setMaterialTexture( 0, _driver->getTexture((_ressourcesPath + "asset/player" + std::to_string(i + 1) + ".png").c_str()));
        auto standAnim = Game::getStatesAnimations()[STAND];
        _playerModels[types[i]]->setFrameLoop(standAnim.first, standAnim.second);
    }

    _intro.openFromFile(_ressourcesPath + "musics/win_intro.ogg");
    _camera->setPosition({0, 0, -30});
}

WinMenu::~WinMenu()
{}

bool WinMenu::_introIsEnded = false;
bool WinMenu::_introStarted = false;
sf::Music WinMenu::_intro;

void WinMenu::setIntroIsEnded(const bool &isEnded)
{
    _introIsEnded = isEnded;
}

bool WinMenu::getIntriIsEnded() noexcept
{
    return _introIsEnded;
}

void WinMenu::setIntroIsStarted(const bool &isStarted)
{
    _introStarted = isStarted;
}

bool WinMenu::getIntriIsStarted() noexcept
{
    return _introStarted;
}

void WinMenu::setIntroVolume(const float &volume)
{
    _intro.setVolume(volume);
}

float WinMenu::getIntroVolume()
{
    return _intro.getVolume();
}

void WinMenu::manageMusics()
{
    if (_currentScene == WIN) {
        if (!_introIsEnded && !_introStarted && _intro.getStatus() != sf::Music::Playing) {
            _introStarted = true;
            _intro.play();
        }
        else if (!_introIsEnded && _intro.getStatus() != sf::Music::Playing) {
            _introStarted = false;
            _introIsEnded = true;
            _intro.stop();
            _musics[WIN].play();
        }
    }
    else {
        if (_intro.getStatus() == sf::Music::Playing) {
            _intro.stop();
        }
        if (_musics[WIN].getStatus() == sf::Music::Playing) {
            _musics[WIN].stop();
        }
    }
}

void WinMenu::managePlayersPodium()
{
    auto players = Game::getPlayerMap();
    auto animations = Game::getStatesAnimations();
    float pos = 12;

    if (!_playerModels.empty()) {
        for (auto it = players.begin(); it != players.end(); it++) {
            if (!it->second->getIsDead()) {
                _playerModels[it->first]->setFrameLoop(animations[DANCE].first, animations[DANCE].second);
                _scene->addLightSceneNode(0, irr::core::vector3df(0, 0, -20), irr::video::SColorf(1, 1, 1, 1), 5000);
                _playerModels[it->first]->setPosition({0, -15, 0});
            }
            else {
                _playerModels[it->first]->setFrameLoop(animations[LOOSE].first, animations[LOOSE].second);
                _scene->addLightSceneNode(0, irr::core::vector3df(pos, -5, -10), irr::video::SColorf(1, 1, 1, 1), 5000);
                _playerModels[it->first]->setPosition({pos, -20, 10});
                pos += 12;
            }
        }
    }
}

void WinMenu::resetPlayersPodium()
{
    auto models = _playerModels.begin();
    for (; models != _playerModels.end(); models++) {
        models->second->setPosition({-1000, -1000, -1000});
    }
}