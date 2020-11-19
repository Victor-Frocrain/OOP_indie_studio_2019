/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** AWall.hpp
*/

#ifndef AWALL_HPP_
#define AWALL_HPP_

#include "IWall.hpp"
#include "../AEntity.hpp"

class AWall : public IWall, public AEntity {
public:
    AWall(const IEntity::EntityType &type, entityMap &map,
            const irr::core::vector3df &pos, const bool &isBreakable);

    virtual ~AWall(void) = default;

    virtual const bool &isBreakable(void) const noexcept final;

    virtual std::string ToLog() const noexcept override;


private:
    const bool _isBreakable;
};

#endif /* AWALL_HPP_ */
