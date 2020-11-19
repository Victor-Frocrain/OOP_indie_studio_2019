/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** Fire.cpp
*/

#include "Fire.hpp"
#include "../../utils/IndieStudio.hpp"
#include "../character/ACharacter.hpp"
#include "../wall/Wall.hpp"

Fire::Fire(const irr::core::vector3df &pos, entityMap &map) :
    AEntity(IEntity::EntityType::FIRE, map, pos), _lifeTime(0)
{}

const float Fire::_timeBeforeExtinguish = 0.5;

bool Fire::update(const double &deltaTime) noexcept
{
    auto elem = IndieStudio::getElemAtPos(getPos(), _map, this);
    for (auto it : elem) {
        if (!it->isImmortal()) {
            if (it->getType() == IEntity::PLAYER || it->getType() == IEntity::IA) {
                dynamic_cast<ACharacter *>(it)->setIsDead(true);
                it->setPos(irr::core::vector3df(-1000, -1000, -1000));
            } else if (it->getType() != IEntity::UNBREAKABLEWALL) {
                if (it->getType() == IEntity::BREAKABLEWALL)
                    dynamic_cast<BreakableWall *>(it)->dropPowerUp();
                delete it;
            }
        }
    }
    _lifeTime += deltaTime;
    if (_lifeTime >= _timeBeforeExtinguish)
        return false;
    return AEntity::update(deltaTime);
}
