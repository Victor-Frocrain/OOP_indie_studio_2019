/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** AButton.hpp
*/

#ifndef ABUTTON_HPP_
#define ABUTTON_HPP_

#include "irrlicht/irrlicht.h"
#include "../entity/AEntity.hpp"
#include "IButton.hpp"
#include <functional>

using namespace irr;
using namespace gui;

typedef const std::function<void()> &buttonFunction;

class AButton : IButton, AEntity {
public:
    AButton(buttonFunction func, const Vector3f &pos, const Vector2f &size,
            IGUIEnvironment *GUIenv, const std::string &text);

    virtual ~AButton(void) = default;

    virtual void pressed(void) const noexcept;

    virtual void display(void) final;

protected:
    buttonFunction _func;
    Vector2f _size;
    IGUIEnvironment *_GUIenv;
    const std::string &_text;
};

#endif /* ABUTTON_HPP_ */
