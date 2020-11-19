/*
** EPITECH PROJECT, 2020
** WinMenu
** File description:
** WinMenu.hpp
*/

#ifndef WINMENU_HPP_
#define WINMENU_HPP_

#include "Menu.hpp"

class WinMenu : public Menu {
public:
    WinMenu(irr::IrrlichtDevice *&device, const std::string &path);
    ~WinMenu();

    static void setIntroIsEnded(const bool &isEnded);
    static bool getIntriIsEnded() noexcept;
    static void setIntroIsStarted(const bool &isStarted);
    static bool getIntriIsStarted() noexcept;
    static void setIntroVolume(const float &volume);
    static float getIntroVolume();

    void manageMusics();
    void managePlayersPodium();
    void resetPlayersPodium();

private:
    static bool _introIsEnded;
    static bool _introStarted;
    static sf::Music _intro;
    std::map<playerType, irr::scene::IAnimatedMeshSceneNode *> _playerModels;
};

#endif /* WINMENU_HPP_ */
