/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** AButton.cpp
*/

#include "AButton.hpp"

AButton::AButton(buttonFunction func, const Vector3f &pos, const Vector3f &size) :
    AEntity(IEntity::Button, pos, size), _func(func)
{}

void AButton::pressed(void) const noexcept
{
    _func();
}
