/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** APowerUp.cpp
*/

#include "APowerUp.hpp"
#include <iostream>

APowerUp::APowerUp(const Bonus &speed, const Bonus &range, const Bonus &nbBomb,
                   const bool &wallPass) :
    _speed(speed), _range(range), _nbBomb(nbBomb), _wallPass(wallPass)
{}

APowerUp::APowerUp(const PowerUpType &powerUpType) :
    _speed(powerUpType == SPEED), _range(powerUpType == RANGE),
    _nbBomb(powerUpType == NBBOMB), _wallPass(powerUpType == WALLPASS)
{}

bool APowerUp::isUnderRange(const int &nb, const int &max, const int &min) noexcept
{
    return nb % 10 >= min && nb % 10 < max;
}

const Bonus &APowerUp::getNbBomb(void) const noexcept
{
    return _nbBomb;
}

const Bonus &APowerUp::getRange(void) const noexcept
{
    return _range;
}

const Bonus &APowerUp::getSpeed(void) const noexcept
{
    return _speed;
}

const bool &APowerUp::getWallPass(void) const noexcept
{
    return _wallPass;
}

void APowerUp::setNbBomb(const Bonus &nbBomb) noexcept
{
    _nbBomb = nbBomb;
}

void APowerUp::setRange(const Bonus &range) noexcept
{
    _range = range;
}

void APowerUp::setSpeed(const Bonus &speed) noexcept
{
    _speed = speed;
}

void APowerUp::setWallPass(const bool &wallPass) noexcept
{
    _wallPass = wallPass;
}
