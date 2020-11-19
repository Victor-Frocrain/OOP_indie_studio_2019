/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** IButton.hpp
*/

#ifndef IBUTTON_HPP_
#define IBUTTON_HPP_

class IButton {
public:

    virtual ~IButton(void) = default;

    virtual void pressed(void) const noexcept = 0;
};

#endif /* IBUTTON_HPP_ */
