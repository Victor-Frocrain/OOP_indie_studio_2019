/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** APowerUp.hpp
*/

#ifndef APOWERUP_HPP_
#define APOWERUP_HPP_

#include "IPowerUp.hpp"

class APowerUp : public IPowerUp {
public:
    APowerUp(const Bonus &speed, const Bonus &range, const Bonus &nbBomb,
             const bool &wallPass);

    APowerUp(const PowerUpType &powerUpType);

    virtual ~APowerUp(void) = default;

    /*
    ** Getter
    */
    virtual const Bonus &getSpeed(void) const noexcept final;

    virtual const Bonus &getRange(void) const noexcept final;

    virtual const Bonus &getNbBomb(void) const noexcept final;

    virtual const bool &getWallPass(void) const noexcept final;

    /*
    ** Setter
    */
    virtual void setSpeed(const Bonus &speed) noexcept final;

    virtual void setRange(const Bonus &range) noexcept final;

    virtual void setNbBomb(const Bonus &nbBomb) noexcept final;

    virtual void setWallPass(const bool &wallPass) noexcept final;

private:
    static bool isUnderRange(const int &nb, const int &max, const int &min = 0) noexcept;

private:
    Bonus _speed;
    Bonus _range;
    Bonus _nbBomb;
    bool _wallPass;
};

#endif /* APOWERUP_HPP_ */
