/*
** EPITECH PROJECT, 2020
** Game
** File description:
** Game.cpp
*/

#include "Game.hpp"
#include "../map/MapGenerator.hpp"
#include "../map/Entities.hpp"
#include <fstream>

Game::Game(irr::IrrlichtDevice *&device, const std::string &path) : AScene(device, path)
{
    addTexture((_ressourcesPath + "asset/box.png").c_str(), irr::core::vector2di(0, 0), std::pair<bool, bool>(true, true), irr::core::rect<irr::s32>(0, 0, 0, 0), "", false);
    addTexture((_ressourcesPath + "asset/wall.png").c_str(), irr::core::vector2di(0, 0), std::pair<bool, bool>(true, true), irr::core::rect<irr::s32>(0, 0, 0, 0), "", false);
    addTexture((_ressourcesPath + "asset/floor.jpg").c_str(), irr::core::vector2di(0, 0), std::pair<bool, bool>(true, true), irr::core::rect<irr::s32>(0, 0, 0, 0), "", false);
    addTexture((_ressourcesPath + "asset/bombPowerUp.png").c_str(), irr::core::vector2di(0, 0), std::pair<bool, bool>(true, true), irr::core::rect<irr::s32>(0, 0, 0, 0), "", false);
    addTexture((_ressourcesPath + "asset/speedPowerUp.png").c_str(), irr::core::vector2di(0, 0), std::pair<bool, bool>(true, true), irr::core::rect<irr::s32>(0, 0, 0, 0), "", false);
    addTexture((_ressourcesPath + "asset/wallPowerUp.png").c_str(), irr::core::vector2di(0, 0), std::pair<bool, bool>(true, true), irr::core::rect<irr::s32>(0, 0, 0, 0), "", false);
    addTexture((_ressourcesPath + "asset/rangePowerUp.png").c_str(), irr::core::vector2di(0, 0), std::pair<bool, bool>(true, true), irr::core::rect<irr::s32>(0, 0, 0, 0), "", false);
    addTexture((_ressourcesPath + "asset/player1.png").c_str(), irr::core::vector2di(0, 0), std::pair<bool, bool>(true, true), irr::core::rect<irr::s32>(0, 0, 0, 0), "", false);
    addTexture((_ressourcesPath + "asset/player2.png").c_str(), irr::core::vector2di(0, 0), std::pair<bool, bool>(true, true), irr::core::rect<irr::s32>(0, 0, 0, 0), "", false);
    addTexture((_ressourcesPath + "asset/player3.png").c_str(), irr::core::vector2di(0, 0), std::pair<bool, bool>(true, true), irr::core::rect<irr::s32>(0, 0, 0, 0), "", false);
    addTexture((_ressourcesPath + "asset/player4.png").c_str(), irr::core::vector2di(0, 0), std::pair<bool, bool>(true, true), irr::core::rect<irr::s32>(0, 0, 0, 0), "", false);
    addTexture((_ressourcesPath + "asset/bomb.png").c_str(), irr::core::vector2di(0, 0), std::pair<bool, bool>(true, true), irr::core::rect<irr::s32>(0, 0, 0, 0), "", false);
    addTexture((_ressourcesPath + "asset/fire.png").c_str(), irr::core::vector2di(0, 0), std::pair<bool, bool>(true, true), irr::core::rect<irr::s32>(0, 0, 0, 0), "", false);

    _animatedMesh[IEntity::BOMB] = _scene->getMesh((_ressourcesPath + "asset/bomb.b3d").c_str());
    _animatedMesh[IEntity::FIRE] = _scene->getMesh((_ressourcesPath + "asset/fire.b3d").c_str());
    for (size_t i = 0; i < 4; i++) {
        _characterAssets.push_back(_scene->addAnimatedMeshSceneNode(_scene->getMesh((_ressourcesPath + "asset/player.b3d").c_str()), 0, -1, {-1000, -1000, -1000}, {0, 0, 0}, {10, 10, 10}));
        _characterAssets[i]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        _characterAssets[i]->setMaterialTexture( 0, _driver->getTexture((_ressourcesPath + "asset/player" + std::to_string(i + 1) + ".png").c_str()));
        auto standAnim = _statesAnimations[STAND];
        _characterAssets[i]->setFrameLoop(standAnim.first, standAnim.second);
    }

    //Floor creation.
    irr::scene::IAnimatedMesh *floor = _scene->addHillPlaneMesh("floor", irr::core::dimension2d<irr::f32>(50.0f, 50.0f), irr::core::dimension2d<irr::u32>(20, 20), 0, 0.0f, irr::core::dimension2d<irr::f32>(0.0f, 0.0f), irr::core::dimension2d<irr::f32>(80.0f, 80.0f));
    irr::scene::IAnimatedMeshSceneNode *terrain_node = _scene->addAnimatedMeshSceneNode(floor);
    terrain_node->setPosition({0, -40, 150});
    terrain_node->setMaterialTexture(0, _driver->getTexture((_ressourcesPath + "asset/floor.jpg").c_str()));
    terrain_node->setMaterialFlag(irr::video::EMF_LIGHTING, false);

    //Lights creation.
    _scene->addLightSceneNode(0, irr::core::vector3df(0, 30, 0), irr::video::SColorf(1, 1, 1, 1), 5000);
    _scene->addLightSceneNode(0, irr::core::vector3df(70, 30, 0), irr::video::SColorf(1, 1, 1, 1), 5000);
    _scene->addLightSceneNode(0, irr::core::vector3df(150, 30, 0), irr::video::SColorf(1, 1, 1, 1), 5000);
    _scene->addLightSceneNode(0, irr::core::vector3df(0, 30, 70), irr::video::SColorf(1, 1, 1, 1), 5000);
    _scene->addLightSceneNode(0, irr::core::vector3df(70, 30, 70), irr::video::SColorf(1, 1, 1, 1), 5000);
    _scene->addLightSceneNode(0, irr::core::vector3df(150, 30, 70), irr::video::SColorf(1, 1, 1, 1), 5000);
    _scene->addLightSceneNode(0, irr::core::vector3df(0, 30, 150), irr::video::SColorf(1, 1, 1, 1), 5000);
    _scene->addLightSceneNode(0, irr::core::vector3df(150, 30, 150), irr::video::SColorf(1, 1, 1, 1), 5000);
}

Game::~Game()
{}

std::tuple<irr::EKEY_CODE, irr::EKEY_CODE, irr::EKEY_CODE, irr::EKEY_CODE, irr::EKEY_CODE> Game::_playerInstances = { irr::KEY_KEY_CODES_COUNT, irr::KEY_KEY_CODES_COUNT, irr::KEY_KEY_CODES_COUNT, irr::KEY_KEY_CODES_COUNT, irr::KEY_KEY_CODES_COUNT };
std::vector<std::string> Game::_map;
std::map<Game::playerType, Player *> Game::_playerMap = {};
std::map<Game::playerType, Player *> Game::_playersBind = {};
int Game::_AILevel = 1;
bool Game::_win = false;
bool Game::_loose = false;

std::map<Game::rotationTypes, irr::core::vector3df> Game::_rotations = {
    { RUP, irr::core::vector3df(0, 180, 0) },
    { RDOWN, irr::core::vector3df(0, 0, 0) },
    { RLEFT, irr::core::vector3df(0, 90, 0) },
    { RRIGHT, irr::core::vector3df(0, 270, 0) }
};

std::map<Game::stateTypes, std::pair<irr::s32, irr::s32>> Game::_statesAnimations = {
    { DANCE, {0, 144} },
    { DEAD, {144, 212} },
    { DROP, {212, 256} },
    { FLOATING, {256, 498} },
    { STAND, {498, 848} },
    { LOOSE, {848, 975} },
    { RUN, {975, 999} }
};

std::map<Game::playerType, Game::stateTypes> Game::_playersStates = {
    { P1, STAND },
    { P2, STAND },
    { P3, STAND },
    { P4, STAND }
};

std::map<Game::rotationTypes, irr::core::vector3df> Game::getRotations() noexcept
{
    return _rotations;
}

void Game::manageScene()
{
    std::vector<IEntity *> toDelete;
    clearEntities();
    if (endOfGame()) {
        return;
    }
    if (_entityClass == nullptr)
        _entityClass = new Entities(Game::getMap(), Game::_entities);
    for (auto &it : _entityClass->getEntities()) {
        for (auto entity = it.second.begin(); entity != it.second.end();) {
            if (!(*entity)->update(Scenes::getDeltaTime())) {
                IEntity *toDelete = *entity;
                entity = it.second.erase(entity);
                delete toDelete;
            } else
                entity++;
        }
    }
    Game::_entities = _entityClass->getEntities();
    takeEntities();
    checkIfOver();
}

void Game::displayScene() const
{
    _scene->drawAll();
}

void Game::clearAll()
{
    _entities.clear();
}

void Game::loadPlayers()
{
    for (auto it : _playersMap) {
        if (std::get<1>(it)) {
            _playerMap[_buttonPlayersMap[std::get<0>(it)]] = new Player(Game::_entities, {0, 0, 0}, _buttonPlayersMap[std::get<0>(it)]);
        }
    }
}

void Game::setPlayerBinds()
{
    _playersBind[P1] = new Player(Game::_entities, {0, 0, 0}, P1);
    _playersBind[P2] = new Player(Game::_entities, {0, 0, 0}, P2);
    _playersBind[P3] = new Player(Game::_entities, {0, 0, 0}, P3);
    _playersBind[P4] = new Player(Game::_entities, {0, 0, 0}, P4);
}

std::map<IScene::playerType, Player *> Game::getPlayersBind() noexcept
{
    return _playersBind;
}

void Game::updatePlayerBinds()
{
    for (auto it : _playerMap) {
        _playersBind[std::get<0>(it)] = std::get<1>(it);
    }
}

void Game::setAILevel(const int &level)
{
    _AILevel = level;
}

int Game::getAILevel() noexcept
{
    return _AILevel;
}

void Game::setPlayerInstance(const playerType &playerType, const irr::EKEY_CODE &code)
{
    switch ((int)playerType) {
    case 1:
        std::get<0>(_playerInstances) = code;
        break;
    case 2:
        std::get<1>(_playerInstances) = code;
        break;
    case 3:
        std::get<2>(_playerInstances) = code;
        break;
    case 4:
        std::get<3>(_playerInstances) = code;
        break;
    case 5:
        std::get<4>(_playerInstances) = code;
        break;
    default:
        break;
    }
}

std::tuple<irr::EKEY_CODE, irr::EKEY_CODE, irr::EKEY_CODE, irr::EKEY_CODE, irr::EKEY_CODE> Game::getPlayerInstances(void)
{
    return _playerInstances;
}

void Game::setPlayerMap(const std::map<playerType, Player *> &playerMap)
{
    _playerMap = playerMap;
}

void Game::clearPlayerMap()
{
    _playerMap.clear();
}

std::map<AScene::playerType, Player *> &Game::getPlayerMap(void)
{
    return _playerMap;
}

std::vector<std::string> Game::getMap() noexcept
{
    return _map;
}

void Game::clearMap()
{
    _map.clear();
}

void Game::setMap(const std::string &path)
{
    MapGenerator generator(15, 15, _nbPlayers, _nbComputers, path);

    _map = generator.getMap();
}

std::map<Game::stateTypes, std::pair<irr::s32, irr::s32>> Game::getStatesAnimations() noexcept
{
    return _statesAnimations;
}

std::map<Game::playerType, Game::stateTypes> Game::getPlayersStates() noexcept
{
    return _playersStates;
}

void Game::setPlayersStates(const playerType &player, const stateTypes &state)
{
    _playersStates[player] = state;
}

void Game::checkIfOver()
{
    auto players = _entities[IEntity::PLAYER];
    auto AIs = _entities[IEntity::IA];
    int nbPlayersAlive = 0;
    int nbIAsAlive = 0;

    for (size_t i = 0; i < players.size(); i++) {
        ACharacter *player = static_cast<ACharacter *>(players[i]);
        if (!player->getIsDead()) {
            nbPlayersAlive++;
        }
    }
    for (size_t i = 0; i < AIs.size(); i++) {
        ACharacter *AI = static_cast<ACharacter *>(AIs[i]);
        if (!AI->getIsDead()) {
            nbIAsAlive++;
        }
    }
    if (nbPlayersAlive == 1 && nbIAsAlive == 0) {
        _win = true;
    }
    else if (nbPlayersAlive == 0) {
        _loose = true;
    }
}

bool Game::endOfGame()
{
    if (_win) {
        setCurrentScene(WIN);
        return true;
    }
    else if (_loose) {
        setCurrentScene(LOSE);
        return true;
    }
    return false;
}

void Game::resetWinAndLose()
{
    _win = false;
    _loose = false;
}

void Game::setPlayerMap(std::map<playerType, Player *> &players)
{
    _playerMap = players;
}

void Game::addPlayerInMap(const playerType &type, Player *player)
{
    _playerMap[type] = player;
}
