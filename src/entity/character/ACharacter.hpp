/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** ACharacter.hpp
*/

#ifndef ACHARACTER_HPP_
#define ACHARACTER_HPP_

#include "../bomb/Bomb.hpp"
#include "../AEntity.hpp"
#include "ICharacter.hpp"
#include "../../scenes/IScene.hpp"
#include "../../utils/IndieStudio.hpp"

class ACharacter : public AEntity, public ICharacter {
public:
    ACharacter(const IEntity::EntityType &type, entityMap &map,
            const irr::core::vector3df &pos, const IScene::playerType &playerType);

    ~ACharacter(void) = default;

    virtual bool update(const double &deltaTime) noexcept override;

    virtual PowerUp &getPowerUp(void) noexcept final;

    virtual void setIsDead(const bool &isDead) noexcept final;

    virtual const bool &getIsDead(void) const noexcept final;

    virtual std::string ToLog() const noexcept override;

    virtual void front(void) noexcept final;

    virtual void back(void) noexcept final;

    virtual void right(void) noexcept final;

    virtual void left(void) noexcept final;

    virtual void dropBomb(void) noexcept final;

    virtual irr::core::vector3df canMoveThere(const short &x, const short &z) noexcept final;

    virtual bool isAvailablePos(const irr::core::vector3df &pos) noexcept final;

    virtual void addBonus(const EntityPowerUp *powerUp) noexcept final;

    virtual const IScene::playerType &getPlayerType(void) const noexcept final;

    virtual const IScene::stateTypes &getPlayerState(void) const noexcept final;

    void resetBombs();

private:
    PowerUp _powerUp;

    size_t _nbBomb; // add le nbbomb dans Acahracter qui correspond au nb de bombe au sol

    bool _isDead;

    float _lastBombTimer; // addd aussi ça

    IScene::stateTypes _state;

    bool _isStanding;

    static const float _timeBetweenBomb;

protected:
    const IScene::playerType _playerType;
};

std::ostream &operator<<(std::ostream &os, const irr::core::vector3df &pos);

#endif /* ACHARACTER_HPP_ */
