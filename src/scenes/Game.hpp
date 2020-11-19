/*
** EPITECH PROJECT, 2020
** Game
** File description:
** Game.hpp
*/

#ifndef GAME_HPP_
#define GAME_HPP_

#include "AScene.hpp"
#include "../entity/character/player/Player.hpp"

class Game : public AScene {
public:
    Game(irr::IrrlichtDevice *&device, const std::string &path);
    ~Game(void);

    void displayScene() const;
    void manageScene();
    void checkIfOver();
    bool endOfGame();

    static void setPlayerInstance(const playerType &playerType, const irr::EKEY_CODE &code);
    static std::tuple<irr::EKEY_CODE, irr::EKEY_CODE, irr::EKEY_CODE, irr::EKEY_CODE, irr::EKEY_CODE> getPlayerInstances(void);
    static void setPlayerMap(const std::map<playerType, Player *> &playerMap);
    static void clearPlayerMap();
    static std::map<playerType, Player *> &getPlayerMap(void);
    static void loadPlayers();
    static std::vector<std::string> getMap() noexcept;
    static void clearMap();
    static void setMap(const std::string &path);
    static void loadAssets();

    static void clearAll();

    static void setAILevel(const int &level);
    static int getAILevel() noexcept;

    static void setPlayerBinds();
    static void setPlayerMap(std::map<playerType, Player *> &players);
    static void addPlayerInMap(const playerType &type, Player *player);
    static std::map<playerType, Player *> getPlayersBind() noexcept;
    static void updatePlayerBinds();
    static std::map<rotationTypes, irr::core::vector3df> getRotations() noexcept;
    static std::map<stateTypes, std::pair<irr::s32, irr::s32>> getStatesAnimations() noexcept;
    static std::map<playerType, stateTypes> getPlayersStates() noexcept;
    static void setPlayersStates(const playerType &player, const stateTypes &state);
    static void resetWinAndLose();

private:
    irr::scene::IMeshSceneNode *_cube;

    static std::vector<std::string> _map;
    static std::tuple<irr::EKEY_CODE, irr::EKEY_CODE, irr::EKEY_CODE, irr::EKEY_CODE, irr::EKEY_CODE> _playerInstances;
    static std::map<playerType, Player *> _playerMap;
    static std::map<playerType, Player *> _playersBind;
    static std::map<IEntity::EntityType, irr::scene::IAnimatedMeshSceneNode *> _animatedAssets;
    static std::map<rotationTypes, irr::core::vector3df> _rotations;
    static std::map<stateTypes, std::pair<irr::s32, irr::s32>> _statesAnimations;
    static std::map<playerType, stateTypes> _playersStates;
    static int _AILevel;
    static bool _win;
    static bool _loose;
};

#endif /* GAME_HPP_ */
