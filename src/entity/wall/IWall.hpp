/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** IWall.hpp
*/

#ifndef IWALL_HPP_
#define IWALL_HPP_

class IWall {
public:
    virtual ~IWall(void) = default;

    virtual const bool &isBreakable(void) const noexcept = 0;
};

#endif /* IWALL_HPP_ */
