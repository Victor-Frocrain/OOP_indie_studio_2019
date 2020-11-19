/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** Control.hpp
*/

#ifndef CONTROL_HPP_
#define CONTROL_HPP_

#include "irrlicht/irrlicht.h"
#include <functional>

class Control {
public:
    Control(std::function<void()> func);

    ~Control(void) = default;

    irr::EKEY_CODE *setKey(void) noexcept;

    void setKey(const int &key) noexcept;

    const irr::EKEY_CODE &getKey(void) const noexcept;

    void operator()(void) const noexcept;

    void setIsKeyPressed(const bool &isKeypressed) noexcept;

private:
    irr::EKEY_CODE _key;
    const std::function<void()> _func;
    bool _isKeyPressed;
};

#endif /* CONTROL_HPP_ */
