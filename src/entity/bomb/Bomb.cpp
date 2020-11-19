/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** Bomb.cpp
*/

#include "Bomb.hpp"
#include "../../utils/IndieStudio.hpp"
#include "../wall/Wall.hpp"
#include <iostream>
#include "../character/ACharacter.hpp"
#include "../../scenes/Scenes.hpp"
#include "../fire/Fire.hpp"
#include "../../scenes/Game.hpp"

Bomb::Bomb(const int &range, entityMap &map, const irr::core::vector3df &pos,
    size_t &nbBomb) :
    AEntity(EntityType::BOMB, map, pos, 0.4), _range(range), _lifeTime(0),
    _nbBomb(nbBomb)
{}

Bomb::~Bomb(void)
{
    _nbBomb--;
}

const double Bomb::_timeBeforeExplosion = 3.0;

bool Bomb::update(const double &deltaTime) noexcept
{
    _lifeTime += deltaTime;
    if (_lifeTime >= _timeBeforeExplosion)
        destroyEntity();
    return AEntity::update(deltaTime);
}

int Bomb::isExplosionStopped(const irr::core::vector3df &crossPos) const noexcept
{
    auto elem = IndieStudio::getElemAtPos(crossPos, _map, this);
    for (auto it : elem) {
        if (it->getType() == IEntity::BREAKABLEWALL)
            return 1;
        if (it->getType() == IEntity::UNBREAKABLEWALL)
            return 0;
    }
    return 2;
}


irr::core::vector3df Bomb::getCrossPosition(const std::pair<int, int> &
                                          cross, const int &range) const noexcept
{
    int x = getPos().X + cross.first * range * SCREEN_SCALE;
    int z = getPos().Z + cross.second * range * SCREEN_SCALE;

    return irr::core::vector3df(x, getPos().Y, z);
}

void Bomb::destroyEntity(void) const noexcept
{
    Scenes::stopSoundEffect(Scenes::SoundEffect::BOMB_EXPLOSION);
    Scenes::playSoundEffect(Scenes::SoundEffect::BOMB_EXPLOSION);
    auto positions = getExplosingPos();
    for (auto pos : positions)
        _map[IEntity::FIRE].push_back(new Fire(pos, _map));
}

std::vector<irr::core::vector3df> Bomb::getExplosingPos(void) const noexcept
{
    std::vector<irr::core::vector3df> positions {getPos()};
    std::vector<std::pair<int, int>> mapCross {
        {1, 0},
        {0, 1},
        {0, -1},
        {-1, 0}
    };

    for (auto itCross : mapCross) {
        for (int x = 1; x <= _range; x++) {
            irr::core::vector3df pos = getCrossPosition(itCross, x);
            int nb = isExplosionStopped(pos);
            if (nb == 0)
                break;
            positions.push_back(pos);
            if (nb == 1)
                break;
        }
    }
    return positions;
}

int Bomb::getRange(void) const
{
    return _range;
}
