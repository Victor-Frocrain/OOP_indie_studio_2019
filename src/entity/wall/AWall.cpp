/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** AWall.cpp
*/

#include "AWall.hpp"

AWall::AWall(const IEntity::EntityType &type, entityMap &map,
            const irr::core::vector3df &pos, const bool &isBreakable) :
    AEntity(type, map, pos), _isBreakable(isBreakable)
{}

const bool &AWall::isBreakable(void) const noexcept
{
    return _isBreakable;
}

std::string AWall::ToLog() const noexcept
{
    return AEntity::ToLog();
}
