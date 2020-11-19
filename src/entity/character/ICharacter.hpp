/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** ICharacter.hpp
*/

#ifndef ICHARACTER_HPP_
#define ICHARACTER_HPP_

#include "../power_up/PowerUp.hpp"
#include "../AEntity.hpp"
#include "../../scenes/IScene.hpp"

class ICharacter {
public:
    virtual ~ICharacter(void) = default;

    virtual PowerUp &getPowerUp(void) noexcept = 0;

    virtual void setIsDead(const bool &isDead) noexcept = 0;

    virtual const bool &getIsDead(void) const noexcept = 0;

    virtual void front(void) noexcept = 0;

    virtual void back(void) noexcept = 0;

    virtual void right(void) noexcept = 0;

    virtual void left(void) noexcept = 0;

    virtual void dropBomb(void) noexcept = 0;

    virtual irr::core::vector3df canMoveThere(const short &x, const short &z) noexcept = 0;

    virtual bool isAvailablePos(const irr::core::vector3df &pos) noexcept = 0;

    virtual void addBonus(const EntityPowerUp *powerUp) noexcept = 0;

    virtual const IScene::playerType &getPlayerType(void) const noexcept = 0;

    virtual const IScene::stateTypes &getPlayerState(void) const noexcept = 0;
};

#endif /* ICHARACTER_HPP_ */
