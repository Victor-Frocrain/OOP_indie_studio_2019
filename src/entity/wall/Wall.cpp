/*
** EPITECH PROJECT, 2020
** wall
** File description:
** for indieStudio
*/

#include "Wall.hpp"
#include "../../map/Entities.hpp"

BreakableWall::BreakableWall(entityMap &map, const irr::core::vector3df &pos)
    : AWall(EntityType::BREAKABLEWALL, map, pos, true), _entityPowerUp(std::rand() % 3 == 0 ? new EntityPowerUp(map, pos) : nullptr)
{}

void BreakableWall::dropPowerUp(void) const noexcept
{
    if (_entityPowerUp) {
        _map[IEntity::BONUS].push_back(_entityPowerUp);
        _entityPowerUp->drop();
    }
}

std::string BreakableWall::ToLog() const noexcept
{
    if (_entityPowerUp == nullptr)
        return "BreakableWall(" + AWall::ToLog() + ")";
    if (_entityPowerUp->getDropped() == true) {
        return _entityPowerUp->ToLog();
    }
    return "BreakableWall(" + AWall::ToLog() + "), " + _entityPowerUp->ToLog();
}

std::string UnBreakableWall::ToLog() const noexcept
{
    return "UnBreakableWall(" + AWall::ToLog() + ")";
}

UnBreakableWall::UnBreakableWall(entityMap &map, const irr::core::vector3df &pos) :
    AWall(EntityType::UNBREAKABLEWALL, map, pos, false)
{}
