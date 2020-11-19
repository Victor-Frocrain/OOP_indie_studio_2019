/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** IScene.hpp
*/

#ifndef ISCENE_HPP_
#define ISCENE_HPP_

#define WIDTH 1920
#define HEIGHT 1080

#define SCREEN_SCALE (10)

#include <irrlicht/irrlicht.h>

#ifndef WIN32
#include <SFML/Audio.hpp>
#endif /* WIN32 */

#ifdef WIN32
#include "..\..\WINDOWS\SFML\include\SFML\Audio.hpp"
#endif /* WIN32 */

#include <iostream>

#pragma comment(lib, "Irrlicht.lib")

class IScene {
public:
    enum sceneType { DEFAULT, GAME, EXIT, MENU, OPTIONS, PAUSE, PLAYERCHOICE, ADDPLAYER, CONTROLS, MUTE, WIN, LOSE };
    enum buttonTypes { NONE, PLAY, QUIT, MAIN, OPT, PAUS, BEGIN, PLAYER1, PLAYER2, PLAYER3, PLAYER4, CONTS, SOUND, SOUNDCURSOR, PAUSEBUTTON, LOAD, SAVE, DIFFICULTYUP, DIFFICULTYDOWN };
    enum playerType { PNONE, P1, P2, P3, P4, PALL };
    enum controlTypes { ZERO, UP, DOWN, LEFT, RIGHT, BOMB, MEN };
    enum rotationTypes { RUP, RDOWN, RLEFT, RRIGHT };
    enum stateTypes { DANCE, DEAD, DROP, FLOATING, STAND, LOOSE, RUN };
    enum SoundEffect {BOMB_EXPLOSION};

public:
    virtual ~IScene() = default;

    virtual void displayScene() const = 0;
    virtual void manageScene() = 0;
    virtual void manageControls() = 0;
    virtual void removeControlSlots() = 0;
    virtual void addControlSlots() = 0;
    virtual void updateControlButtons() = 0;

    virtual int getNbPlayers() const noexcept = 0;
    virtual int getNbComputers() const noexcept = 0;

protected:
    virtual void manageButtons() = 0;
};

#endif /* ISCENE_HPP_ */
