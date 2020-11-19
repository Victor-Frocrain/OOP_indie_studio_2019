/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** AEntity.hpp
*/

#ifndef AENTITY_HPP_
#define AENTITY_HPP_

#include "IEntity.hpp"
#include "ILog.hpp"
#include <vector>
#include <map>
#include <cstring>

typedef std::map<IEntity::EntityType, std::vector<IEntity *>> entityMap;

class AEntity : public IEntity {
public:
    AEntity(const IEntity::EntityType &type, entityMap &map,
            const irr::core::vector3df &pos, const float &collisionSize = 0.5);

    virtual ~AEntity(void);

    /*
    ** Herited Method
    */
    virtual const irr::core::vector3df &getPos(void) const noexcept final;

    virtual const IEntity::EntityType &getType(void) const noexcept final;

    virtual std::string ToLog() const noexcept override;

    virtual void setPos(const irr::core::vector3df &pos) noexcept final;

    virtual bool update(const double &deltaTime) noexcept override;

    virtual const float &getCollisionSize(void) const noexcept final;

    virtual const bool &isImmortal(void) const noexcept final;
private:
    irr::core::vector3df _pos;
    const IEntity::EntityType _type;
    const float _collisionSize;

protected:
    entityMap &_map;
    bool _isImmortal; // rajouter sa dans le to_log permet d'éviter que quand un item dropped il soit annhiler par le feu par exemple
};

#endif /* AENTITY_HPP_ */
