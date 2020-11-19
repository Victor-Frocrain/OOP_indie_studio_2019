/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** Bomb.hpp
*/

#ifndef BOMB_HPP_
#define BOMB_HPP_

#include "../AEntity.hpp"
#include "../power_up/PowerUp.hpp"
#include <vector>

class Bomb : public AEntity {
public:
    Bomb(const int &range, entityMap &map, const irr::core::vector3df &pos,
        size_t &nbBomb);

    ~Bomb(void);

    virtual bool update(const double &deltaTime) noexcept final;

    std::vector<irr::core::vector3df> getExplosingPos(void) const noexcept;

    int getRange(void) const;

    void destroyEntity(void) const noexcept;

    /* Private method */
private:
    int isExplosionStopped(const irr::core::vector3df &crossPos) const noexcept;

    bool isCollision(const IEntity *entity, const IEntity::EntityType &entityType,
                     const irr::core::vector3df &explosionPos) const noexcept;

    irr::core::vector3df getCrossPosition(const std::pair<int, int> &
                                          cross, const int &range) const noexcept;

private:
    static const double _timeBeforeExplosion;
    const int _range;
    double _lifeTime;
    size_t &_nbBomb;
};

#endif /* BOMB_HPP_ */
