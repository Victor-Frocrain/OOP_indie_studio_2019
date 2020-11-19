/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** ACharacter.cpp
*/

#include "ACharacter.hpp"
#include <iostream>
#include "../../utils/IndieStudio.hpp"
#include "../../scenes/Scenes.hpp"
#include "../power_up/PowerUp.hpp"

ACharacter::ACharacter(const IEntity::EntityType &type, entityMap &map,
                       const irr::core::vector3df &pos, const IScene::playerType &playerType) :
    AEntity(type, map, pos, 0.3), _nbBomb(0), _isDead(false), _lastBombTimer(0),
    _state(IScene::stateTypes::STAND), _isStanding(true), _playerType(playerType)
{}

const float ACharacter::_timeBetweenBomb = 0.5;

bool ACharacter::update(const double &deltaTime) noexcept
{
    if (_isStanding)
        _state = IScene::stateTypes::STAND;
    if (_lastBombTimer > 0)
        _lastBombTimer -= deltaTime;
    _isStanding = true;
    return (true);
}

PowerUp &ACharacter::getPowerUp(void) noexcept
{
    return _powerUp;
}

void ACharacter::setIsDead(const bool &isDead) noexcept
{
    _isDead = isDead;
}

const bool &ACharacter::getIsDead(void) const noexcept
{
    return _isDead;
}

void ACharacter::addBonus(const EntityPowerUp *entityPowerUp) noexcept
{
    _powerUp += entityPowerUp;
}

std::string ACharacter::ToLog() const noexcept
{
    return(AEntity::ToLog() + ", " + "NbBomb(" + std::to_string(_nbBomb) + "), " + "LastBombTimer(" + std::to_string(_lastBombTimer) + ")), " + "IsDead(" +  IndieStudio::boolToString(getIsDead()) + ")), " + _powerUp.ToLog());
}

std::ostream &operator<<(std::ostream &os, const irr::core::vector3df &pos)
{
    os << "(" << pos.X << ", " << pos.Y << ", " << pos.Z << ")";
    return os;
}

bool ACharacter::isAvailablePos(const irr::core::vector3df &pos) noexcept
{
    auto elem = IndieStudio::getElemAtPos(pos, _map, this);
    bool isAllBreakableWall = true;

    for (auto it = elem.begin(); it != elem.end();) {
        switch (static_cast<int>((*it)->getType())) {
        case IEntity::EntityType::BREAKABLEWALL:
            it++;
            break;
        case IEntity::EntityType::BONUS:
            addBonus(dynamic_cast<EntityPowerUp *>(*it));
            delete (*it);
            it = elem.erase(it);
            break;
        default:
            isAllBreakableWall = false;
            it++;
            break;
        }
    }
    if (!elem.size() || (isAllBreakableWall && _powerUp.getWallPass()))
        return true;
    return false;
}

irr::core::vector3df ACharacter::canMoveThere(const short &x, const short &z) noexcept
{
    _isStanding = false;
    _state = IScene::stateTypes::RUN;
    float speed = (2 + ((getPowerUp().getSpeed() - 1) / 2)) * SCREEN_SCALE ;
    auto newPos = getPos();
    auto toAdd = irr::core::vector3df(std::abs(x) * speed * Scenes::getDeltaTime(), 0, std::abs(z) * speed * Scenes::getDeltaTime());
    auto toAdd2 = irr::core::vector3df(std::abs(x) * SCREEN_SCALE, 0, std::abs(z) * SCREEN_SCALE);
    auto toCheck = IndieStudio::roundPos(getPos());

    if (x < 0 || z < 0) {
        newPos -= toAdd;
        toCheck -= toAdd2;
    } else {
        newPos += toAdd;
        toCheck += toAdd2;
    }
    if (isAvailablePos(toCheck))
        return newPos;
    else if (isAvailablePos(IndieStudio::roundPos(getPos())) && IndieStudio::isGoingCenter(getPos(), x, z))
        return newPos;
    else if (isAvailablePos(newPos))
        return newPos;
    return getPos();
}

void ACharacter::front(void) noexcept
{
    AScene::setPlayersRotations(_playerType, IScene::rotationTypes::RUP);
    setPos(canMoveThere(0, 1));
}

void ACharacter::back(void) noexcept
{
    AScene::setPlayersRotations(_playerType, IScene::rotationTypes::RDOWN);
    setPos(canMoveThere(0, -1));
}

void ACharacter::right(void) noexcept
{
    AScene::setPlayersRotations(_playerType, IScene::rotationTypes::RRIGHT);
    setPos(canMoveThere(1, 0));
}

void ACharacter::left(void) noexcept
{
    AScene::setPlayersRotations(_playerType, IScene::rotationTypes::RLEFT);
    setPos(canMoveThere(-1, 0));
}

void ACharacter::dropBomb(void) noexcept
{
    if (_nbBomb < _powerUp.getNbBomb() && !_isDead && _lastBombTimer <= 0) {
        _isStanding = false;
        _state = IScene::stateTypes::DROP;
        _map[IEntity::BOMB].push_back(new Bomb(_powerUp.getRange(), _map, IndieStudio::roundPos(getPos()), _nbBomb));
        _nbBomb++;
        _lastBombTimer = _timeBetweenBomb;
    }
}


const IScene::playerType &ACharacter::getPlayerType(void) const noexcept
{
    return _playerType;
}


const IScene::stateTypes &ACharacter::getPlayerState(void) const noexcept
{
    return _state;
}

void ACharacter::resetBombs()
{
    _nbBomb = 0;
}