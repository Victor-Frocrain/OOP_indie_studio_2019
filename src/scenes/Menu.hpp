/*
** EPITECH PROJECT, 2020
** Menu
** File description:
** Menu.hpp
*/

#ifndef MENU_HPP_
#define MENU_HPP_

#include "AScene.hpp"
#include "Scenes.hpp"

class Menu : public AScene {
public:
    Menu(irr::IrrlichtDevice *&device, const std::string &path);
    ~Menu();

    irr::scene::ISceneManager *getScene() const noexcept;
    irr::gui::IGUIButton *getButton(const buttonTypes &type) noexcept;

    //void addButton(const buttonTypes &type);
    //void manageButtons();
    void displayScene() const;
    void manageScene();

    static void setupButtonSprite(irr::gui::IGUIButton *button);
    static irr::gui::IGUISpriteBank *getSpriteBank() noexcept;
    static controlTypes getControlToDefine() noexcept;
    static void setControlToDefine(const controlTypes &control);

    irr::gui::IGUIEnvironment *getGUIEnv() const noexcept;

protected:
    static irr::gui::IGUISpriteBank *_buttonSprite;
    static controlTypes _controlToDefine;

protected:
    void setupPlayerSlotSprites(std::tuple<buttonTypes, irr::gui::IGUIButton *, bool> button);
    void setupPlayerSlotTexts(std::tuple<buttonTypes, irr::gui::IGUIButton *, bool> button);
    void managePlayersButton();
    void manageCursorSound();
    void computeVolumeSound(const float &limit, const float &total);

};

#endif /* MENU_HPP_ */
