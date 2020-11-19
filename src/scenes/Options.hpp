/*
** EPITECH PROJECT, 2020
** Options
** File description:
** Options.hpp
*/

#ifndef OPTIONS_HPP_
#define OPTIONS_HPP_

#include "Menu.hpp"

class Options : public Menu {
public:
    Options(irr::IrrlichtDevice *&device, const std::string &path);
    ~Options();

private:
    void setupSoundButton(irr::gui::IGUIButton *button);
    void setupCursorSound(irr::gui::IGUIButton *button);
    void setupPauseButton(irr::gui::IGUIButton *button);
};

#endif /* OPTIONS_HPP_ */
