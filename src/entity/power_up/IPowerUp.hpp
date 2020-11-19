/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** IPowerUp.hpp
*/

#ifndef IPOWERUP_HPP_
#define IPOWERUP_HPP_

typedef unsigned int Bonus;

class IPowerUp {
public:
    enum PowerUpType {SPEED, RANGE, NBBOMB, WALLPASS, NOBONUS};
    virtual ~IPowerUp(void) = default;

    /*
    ** Getter
    */
    virtual const Bonus &getSpeed(void) const noexcept = 0;

    virtual const Bonus &getRange(void) const noexcept = 0;

    virtual const Bonus &getNbBomb(void) const noexcept = 0;

    virtual const bool &getWallPass(void) const noexcept = 0;

    /*
    ** Setter
    */
    virtual void setSpeed(const Bonus &speed) noexcept = 0;

    virtual void setRange(const Bonus &range) noexcept = 0;

    virtual void setNbBomb(const Bonus &nbBomb) noexcept = 0;

    virtual void setWallPass(const bool &wallPass) noexcept = 0;
};

#endif /* IPOWERUP_HPP_ */
