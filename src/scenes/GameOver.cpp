/*
** EPITECH PROJECT, 2020
** GameOver
** File description:
** GameOver.cpp
*/

#include "GameOver.hpp"
#include "Game.hpp"

GameOver::GameOver(irr::IrrlichtDevice *&device, const std::string &path) : Menu(device, path)
{
    irr::s32 buttonWidth = 267;
    irr::s32 buttonHeight = 73;
    irr::s32 pos = 300;

    addTexture((_ressourcesPath + "sprites/background_lose.png").c_str(), irr::core::vector2di(0, 0));
    addTexture((_ressourcesPath + "titles/game_over.png").c_str(), irr::core::vector2di(0, 100), std::pair<bool, bool>(true, false));
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
        auto standAnim = Game::getStatesAnimations()[LOOSE];
        _playerModels[types[i]]->setFrameLoop(standAnim.first, standAnim.second);
    }

    _camera->setPosition({0, 0, -30});
}

GameOver::~GameOver()
{}

void GameOver::managePlayerShame()
{
    auto players = Game::getPlayerMap();
    float pos = 0;
    float ratio = 0;

    switch (players.size()) {
    case 1:
        pos = 0;
        break;
    case 2:
        pos = -25;
        ratio = 50;
        break;
    case 3:
        pos = -25;
        ratio = 25;
        break;
    default:
        break;
    }
    if (!_playerModels.empty()) {
        for (auto it = players.begin(); it != players.end(); it++) {
            _scene->addLightSceneNode(0, irr::core::vector3df(pos, 0, -20), irr::video::SColorf(1, 1, 1, 1), 5000);
            _playerModels[it->first]->setPosition({pos, -15, 0});
            pos += ratio;
        }
    }
}

void GameOver::resetPlayerShame()
{
    auto models = _playerModels.begin();
    for (; models != _playerModels.end(); models++) {
        models->second->setPosition({-1000, -1000, -1000});
    }
}