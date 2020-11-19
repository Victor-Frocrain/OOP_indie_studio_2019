/*
** EPITECH PROJECT, 2020
** MainMenu
** File description:
** MainMenu.hpp
*/

#ifndef MAINMENU_HPP_
#define MAINMENU_HPP_

#include "Menu.hpp"

class MainMenu : public Menu {
public:
    MainMenu(irr::IrrlichtDevice *&device, const std::string &path);
    ~MainMenu();

    static bool hasFiles(const std::string &path);

};

#endif /* MAINMENU_HPP_ */
