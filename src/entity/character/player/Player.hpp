/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** Player.hpp
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "../ACharacter.hpp"
#include "../../../scenes/Scenes.hpp"
#include "APlayerController.hpp"

class Player : public ACharacter {
public:
    Player(entityMap &map, const irr::core::vector3df &pos,
    const Scenes::playerType &playerType);

    ~Player(void);

    bool update(const double &deltaTime) noexcept final;

    IPlayerController *getPlayerController(void) noexcept;

    std::string ToLog() const noexcept;

private:
    IPlayerController *_playerController;
};

#endif /* PLAYER_HPP_ */
