/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** PowerUp.hpp
*/

#ifndef POWERUP_HPP_
#define POWERUP_HPP_

#include "../AEntity.hpp"
#include "APowerUp.hpp"
#include <iostream>

class EntityPowerUp : public AEntity, public APowerUp {
public:
    EntityPowerUp(entityMap &map, const irr::core::vector3df &pos);

    //EntityPowerUp(entityMap &map, const irr::core::vector3df &pos, bool dropped);

    ~EntityPowerUp(void) = default;

    bool update(const double &deltaTime) noexcept final;

    void drop(void) noexcept;

    std::string ToLog(void) const noexcept;

    const PowerUpType &getPowerUpType(void) const noexcept;

    void setPowerUpType(const PowerUpType &poweruptype) noexcept;

    PowerUpType choosePowerUp(void) noexcept;

    bool getDropped(void) noexcept;

    void setImmortalityTimer(const float &imortalityTimer) noexcept;

    void setDropped(const bool &dropped) noexcept;

private:
    static const float _immortalityTime;
    float _imortalityTimer;
    bool _dropped;
    PowerUpType _powerUpType;
};

class PowerUp : public APowerUp, public ILog {
public:
    PowerUp(void);

    ~PowerUp(void) = default;

    std::string ToLog() const noexcept;
};

void operator+=(PowerUp &powerUp, const EntityPowerUp *entityPowerUp);

#endif /* POWERUP_HPP_ */
