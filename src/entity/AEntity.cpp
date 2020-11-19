/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** AEntity.cpp
*/

#include "AEntity.hpp"
#include <iostream>
#include "../utils/IndieStudio.hpp"

std::vector<irr::io::path> _EXTENSION2D_ = {".jpg", ".png", ".pgm", \
".psd", ".bmp", ".rgb", ".pcx", "ppm", ".pbm", ".tga", ".wal", ".rgba"};

std::vector<irr::io::path> _EXTENSION3D_ = {".pk3", ".zip", ".pak", ".npk"};

AEntity::AEntity(const IEntity::EntityType &type, entityMap &map,
                 const irr::core::vector3df &pos, const float &collisionSize)
    : _pos(pos), _type(type), _collisionSize(collisionSize), _map(map), _isImmortal(false)
{}

AEntity::~AEntity(void)
{
    for (auto itEntity = _map[_type].begin();
         itEntity != _map[_type].end(); itEntity++) {
        if (*itEntity == this) {
            _map[_type].erase(itEntity);
            return;
        }
    }
}

const bool &AEntity::isImmortal(void) const noexcept
{
    return _isImmortal;
}

const float &AEntity::getCollisionSize(void) const noexcept
{
    return _collisionSize;
}

const IEntity::EntityType &AEntity::getType(void) const noexcept
{
    return _type;
}

bool AEntity::update(const double &deltaTime) noexcept
{
    (void)deltaTime;
    return (true);
}

const irr::core::vector3df &AEntity::getPos(void) const noexcept
{
    return _pos;
}

void AEntity::setPos(const irr::core::vector3df &pos) noexcept
{
    _pos = pos;
}

std::string AEntity::ToLog() const noexcept
{
    irr::core::vector3df pos = getPos();

    return "AEntity(" + std::to_string(pos.X) + ", " + std::to_string(pos.Y) + ", " + std::to_string(pos.Z) + ", " + "Immortal" + "(" + IndieStudio::boolToString(isImmortal()) + ")";
}
