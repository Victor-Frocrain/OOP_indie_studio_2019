/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** PowerUp.cpp
*/

#include "PowerUp.hpp"
#include "../../utils/IndieStudio.hpp"

const float EntityPowerUp::_immortalityTime = 1;

EntityPowerUp::EntityPowerUp(entityMap &map, const irr::core::vector3df &pos) :
    AEntity(EntityType::BONUS, map, pos), APowerUp(choosePowerUp()),
    _imortalityTimer(0), _dropped(false)
{}

std::string EntityPowerUp::ToLog() const noexcept
{
    return ("EntityPowerUp(" + AEntity::ToLog() + ")" + ", " + "APowerUp(" + std::to_string(getSpeed()) + ", " + std::to_string(getRange()) + ", " + std::to_string(getNbBomb()) + ", " + std::to_string(getWallPass()) + "), " + "ImmortalityTimer(" + std::to_string(_imortalityTimer) + "), " + "Droppped(" + IndieStudio::boolToString(_dropped) + "), " + "PowerUpType(" + std::to_string(getPowerUpType()) + "))");
}

void EntityPowerUp::drop(void) noexcept
{
    _isImmortal = true;
    _dropped = true;
}

void EntityPowerUp::setPowerUpType(const PowerUpType &poweruptype) noexcept
{
    _powerUpType = poweruptype;
}

IPowerUp::PowerUpType EntityPowerUp::choosePowerUp(void) noexcept
{
    int rand = std::rand() % 10;

    _powerUpType = WALLPASS;
    if (rand < 3) {
        _powerUpType = SPEED;
    } else if (rand < 6) {
        _powerUpType = RANGE;
    } else if (rand < 9)
        _powerUpType = NBBOMB;
    return _powerUpType;
}

const IPowerUp::PowerUpType &EntityPowerUp::getPowerUpType(void) const noexcept
{
    return _powerUpType;
}

bool EntityPowerUp::update(const double &deltaTime) noexcept
{
    if (_dropped) {
        _imortalityTimer += deltaTime;
        if (_imortalityTimer >= _immortalityTime) {
            _isImmortal = false;
            _dropped = false;
        }
    }
    return AEntity::update(deltaTime);
}

bool EntityPowerUp::getDropped(void) noexcept
{
    return _dropped; //segfault quand je return _dropped ???
}

void EntityPowerUp::setImmortalityTimer(const float &imortalityTimer) noexcept
{
    _imortalityTimer = imortalityTimer;
}

void EntityPowerUp::setDropped(const bool &dropped) noexcept
{
    _dropped = dropped;
}

PowerUp::PowerUp(void) :
    APowerUp(1, 1, 1, false)
{}

std::string PowerUp::ToLog() const noexcept
{
    return ("APowerUp(" + std::to_string(getSpeed()) + ", " + std::to_string(getRange()) + ", " + std::to_string(getNbBomb()) + ", " + std::to_string(getWallPass()) + ")");
}

void operator+=(PowerUp &powerUp, const EntityPowerUp *entityPowerUp)
{
    powerUp.setSpeed(powerUp.getSpeed() + entityPowerUp->getSpeed());
    powerUp.setRange(powerUp.getRange() + entityPowerUp->getRange());
    powerUp.setNbBomb(powerUp.getNbBomb() + entityPowerUp->getNbBomb());
    powerUp.setWallPass(powerUp.getWallPass() | entityPowerUp->getWallPass());
}
