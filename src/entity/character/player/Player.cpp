/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** Player.cpp
*/

#include "Player.hpp"
#include "../../../scenes/Game.hpp"

Player::Player(entityMap &map, const irr::core::vector3df &pos,
    const Scenes::playerType &playerType)
    : ACharacter(EntityType::PLAYER, map, pos, playerType),
      _playerController(new APlayerController(this, playerType))
{}

Player::~Player(void)
{
    delete _playerController;
}

bool Player::update(const double &deltaTime) noexcept
{
    for (auto it : APlayerController::getKeyTypes())
        (*_playerController)(it);
    return ACharacter::update(deltaTime);
}

IPlayerController *Player::getPlayerController(void) noexcept
{
    return _playerController;
}

std::string Player::ToLog() const noexcept
{
    return "Player(" + ACharacter::ToLog() + ", PlayerController(" + std::to_string(_playerController->getPlayerType()) + ")";
}
