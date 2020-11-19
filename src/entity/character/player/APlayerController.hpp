/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** APlayerController.hpp
*/

#ifndef APLAYERCONTROLLER_HPP_
#define APLAYERCONTROLLER_HPP_

#include "IPlayerController.hpp"
#include <map>
#include "Player.hpp"
#include "irrlicht/irrlicht.h"
#include <vector>
#include "Control.hpp"

class APlayerController : public IPlayerController {
public:
    APlayerController(ACharacter *player, const Scenes::playerType &nbPlayer);

    ~APlayerController(void) = default;

    virtual void savePlayerPref(void) const final;

    /*
    ** Getter
    */
    virtual const wchar_t *toString(const KeyType &keyType) const noexcept final;

    virtual void operator()(const KeyType &keyType) const noexcept final;

    virtual const irr::EKEY_CODE &getKeyCode(const KeyType &keyType) const noexcept final;

    /*
    ** Setter
    */
    virtual irr::EKEY_CODE *setKeyCode(const KeyType &keyType) noexcept final;

    virtual void setIsKeyPressed(const KeyType &keyType, const bool &isKeyPressed) noexcept final;

    static std::map<irr::EKEY_CODE, const wchar_t *> getEventToString(void) noexcept;

    static const std::vector<IPlayerController::KeyType> &getKeyTypes(void) noexcept;

    Scenes::playerType getPlayerType() const noexcept; // savoir si le joueur est p1 p2 p3 p4

private:
    virtual const wchar_t *getString(const irr::EKEY_CODE &state) const noexcept final;

private:
    std::vector<Control> _controls;

    const Scenes::playerType &_type;

    static std::map<irr::EKEY_CODE, const wchar_t *> _eventToString;
    static const wchar_t *_defaultToString;
    static const std::vector<IPlayerController::KeyType> _keyTypes;
};

#endif /* APLAYERCONTROLLER_HPP_ */
