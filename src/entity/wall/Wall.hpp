/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** Wall.hpp
*/

#ifndef WALL_HPP_
#define WALL_HPP_

#include "AWall.hpp"
#include "../power_up/PowerUp.hpp"
#include "../../utils/IndieStudio.hpp"

class UnBreakableWall : public AWall {
public:
    UnBreakableWall(entityMap &map, const irr::core::vector3df &pos);

    ~UnBreakableWall(void) = default;

    std::string ToLog() const noexcept;
};

class BreakableWall : public AWall {
public:
    BreakableWall(entityMap &map, const irr::core::vector3df &pos);

    ~BreakableWall(void) = default;

    void dropPowerUp(void) const noexcept;

    std::string ToLog() const noexcept;

private:
    EntityPowerUp *_entityPowerUp;
};

#endif /* WALL_HPP_ */
