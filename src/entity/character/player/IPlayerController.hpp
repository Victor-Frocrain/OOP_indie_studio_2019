/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** IPlayerController.hpp
*/

#ifndef IPLAYERCONTROLLER_HPP_
#define IPLAYERCONTROLLER_HPP_

#include <utility>
#include <functional>
#include "irrlicht/irrlicht.h"
#include <vector>
#include "../../../scenes/Scenes.hpp"

typedef std::pair<irr::EKEY_CODE, std::function<void(void)>> Func;

class IPlayerController {
public:
    enum KeyType {UP, DOWN, LEFT, RIGHT, BOMB, MEN };

    virtual ~IPlayerController(void) = default;

    virtual void savePlayerPref(void) const = 0;

    /*
    ** Getter
    */
    virtual const wchar_t *toString(const KeyType &keyType) const noexcept = 0;

    virtual void operator()(const KeyType &keyType) const noexcept = 0;

    virtual const irr::EKEY_CODE &getKeyCode(const KeyType &keyType) const noexcept = 0;

    /*
    ** Setter
    */
    virtual irr::EKEY_CODE *setKeyCode(const KeyType &keyType) noexcept = 0;

    virtual void setIsKeyPressed(const KeyType &keyType, const bool &isKeyPressed) noexcept = 0;

    virtual Scenes::playerType getPlayerType() const noexcept = 0;

private:

    virtual const wchar_t *getString(const irr::EKEY_CODE &state) const noexcept = 0;
};

#endif /* IPLAYERCONTROLLER_HPP_ */
