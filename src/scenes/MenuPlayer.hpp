/*
** EPITECH PROJECT, 2020
** MenuPlayer
** File description:
** MenuPlayer.hpp
*/

#ifndef MENUPLAYER_HPP_
#define MENUPLAYER_HPP_

#include "Menu.hpp"

class MenuPlayer : public Menu {
public:
    MenuPlayer(irr::IrrlichtDevice *&device, const std::string &path);
    ~MenuPlayer();

};

#endif /* MENUPLAYER_HPP_ */
