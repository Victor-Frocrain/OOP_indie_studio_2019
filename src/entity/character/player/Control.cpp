/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** Control.cpp
*/

#include "Control.hpp"

Control::Control(std::function<void()> func) :
    _key(irr::EKEY_CODE::KEY_KEY_CODES_COUNT), _func(func), _isKeyPressed(false)
{}

irr::EKEY_CODE *Control::setKey(void) noexcept
{
    return &_key;
}

void Control::setKey(const int &key) noexcept
{
    _key = static_cast<irr::EKEY_CODE>(key);
}

const irr::EKEY_CODE &Control::getKey(void) const noexcept
{
    return _key;
}

void Control::operator()(void) const noexcept
{
    if (_isKeyPressed)
        _func();
}

void Control::setIsKeyPressed(const bool &isKeypressed) noexcept
{
    _isKeyPressed = isKeypressed;
}
