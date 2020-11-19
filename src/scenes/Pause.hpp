/*
** EPITECH PROJECT, 2020
** Pause
** File description:
** Pause.hpp
*/

#ifndef PAUSE_HPP_
#define PAUSE_HPP_

#include "Menu.hpp"

class Pause : public Menu {
public:
    Pause(irr::IrrlichtDevice *&device, const std::string &path);
    ~Pause();

    static void setIsWaiting(const bool &waiting);
    static bool getIsWaiting() noexcept;
    static void setAction(const buttonTypes &type);
    static buttonTypes getAction() noexcept;

private:
    static bool _isWaiting;
    static buttonTypes _action;
};

#endif /* PAUSE_HPP_ */
