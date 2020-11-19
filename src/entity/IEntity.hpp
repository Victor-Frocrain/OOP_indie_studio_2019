/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** IEntity.hpp
*/

#ifndef IENTITY_HPP_
#define IENTITY_HPP_

#include <irrlicht/irrlicht.h>
#include <string>
#include "ILog.hpp"

class IEntity: public ILog {
public:
    enum EntityType {PLAYER, IA, BREAKABLEWALL, UNBREAKABLEWALL, BOMB, BONUS, FIRE};

    virtual ~IEntity(void) = default;

    virtual const irr::core::vector3df &getPos(void) const noexcept = 0;

    virtual const IEntity::EntityType &getType(void) const noexcept = 0;

    virtual std::string ToLog() const noexcept = 0;

    virtual void setPos(const irr::core::vector3df &pos) noexcept = 0;

    virtual bool update(const double &deltaTime) noexcept = 0;

    virtual const float &getCollisionSize(void) const noexcept = 0;

    virtual const bool &isImmortal(void) const noexcept = 0;
};

#endif /* IENTITY_HPP_ */
