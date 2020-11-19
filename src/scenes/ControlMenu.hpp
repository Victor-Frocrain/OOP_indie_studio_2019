/*
** EPITECH PROJECT, 2020
** ControlMenu
** File description:
** ControlMenu.hpp
*/

#ifndef CONTROLMENU_HPP_
#define CONTROLMENU_HPP_

#include "Menu.hpp"
#include <ctime>

class ControlMenu : public Menu {
public:
    ControlMenu(irr::IrrlichtDevice *&device, const std::string &path);

    ~ControlMenu(void) = default;

    static bool getIsWaitingKey() noexcept;
    static std::pair<playerType, std::pair<controlTypes, irr::EKEY_CODE>> getAssociatedControl() noexcept;
    static bool getSignalReiceived() noexcept;
    static bool getIsKeyError() noexcept;

    static void setIsWaitingKey(const bool &isWaiting);
    static void setAssociatedControl(const std::pair<playerType, std::pair<controlTypes, irr::EKEY_CODE>> &it);
    static void setSignalReiceived(const bool &signal);
    static void setIsKeyError(const bool &isError);

    static void setVisible(std::vector<std::tuple<buttonTypes, irr::gui::IGUIButton *, bool>> &buttons, const std::string &path,
                           std::vector<std::tuple<irr::video::ITexture *, irr::core::vector2di, irr::core::rect<irr::s32>, bool>> &textures, const bool &visible);
    static bool canChangeControl(irr::EKEY_CODE &code);
    static bool showErrorKeyMessage(std::vector<std::tuple<buttonTypes, irr::gui::IGUIButton *, bool>> &buttons, const std::string &path,
                                    std::vector<std::tuple<irr::video::ITexture *, irr::core::vector2di, irr::core::rect<irr::s32>, bool>> &textures);

    static bool updateControls();
    static controlTypes getControlFromId(const int &id);

    static void manageAIDifficulty(const buttonTypes &type);

private:
    static bool _isWaitingKey;
    static std::pair<playerType, std::pair<controlTypes, irr::EKEY_CODE>> _associatedControl;
    static bool _signalReiceived;
    static std::clock_t _clock;
    static bool _isKeyError;
};

#endif /* CONTROLMENU_HPP_ */
