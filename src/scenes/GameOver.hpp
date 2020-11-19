/*
** EPITECH PROJECT, 2020
** GameOver
** File description:
** GameOver.hpp
*/

#ifndef GAMEOVER_HPP_
#define GAMEOVER_HPP_

#include "Menu.hpp"

class GameOver : public Menu {
public:
    GameOver(irr::IrrlichtDevice *&device, const std::string &path);
    ~GameOver();

    void managePlayerShame();
    void resetPlayerShame();

private:
    std::map<playerType, irr::scene::IAnimatedMeshSceneNode *> _playerModels;
};

#endif /* GAMEOVER_HPP_ */
