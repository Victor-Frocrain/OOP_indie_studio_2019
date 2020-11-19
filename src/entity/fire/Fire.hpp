/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** Fire.hpp
*/

#ifndef FIRE_HPP_
#define FIRE_HPP_

#include "../AEntity.hpp"

class Fire : public AEntity {
public:
    Fire(const irr::core::vector3df &pos, entityMap &map);

    ~Fire(void) = default;

    bool update(const double &deltaTime) noexcept final;

private:
    float _lifeTime;
    static const float _timeBeforeExtinguish;
};

#endif /* FIRE_HPP_ */
