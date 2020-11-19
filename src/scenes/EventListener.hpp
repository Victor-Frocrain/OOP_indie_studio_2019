/*
** EPITECH PROJECT, 2020
** EventListener
** File description:
** EventListener.hpp
*/

#ifndef EVENTLISTENER_HPP_
#define EVENTLISTENER_HPP_

#include <irrlicht/irrlicht.h>
#include <vector>
#include "../entity/character/player/APlayerController.hpp"

class EventListener : public irr::IEventReceiver {
public:
    EventListener(void);

    ~EventListener(void) = default;

    void setupPlayers(std::vector<Player *> &players) noexcept;

    static irr::EKEY_CODE getKeyPause() noexcept;
    static void setKeyPause(const irr::EKEY_CODE &code);

    static bool getEnterOnPause() noexcept;
    static void setEnterOnPause(const bool enter);

    virtual bool OnEvent(const irr::SEvent& event);

    static void setWatingKey(irr::EKEY_CODE *keyToSet) noexcept;

    static void reverseKey();

private:
    std::vector<Player *> _players;

    static irr::EKEY_CODE _keyPause;

    static irr::EKEY_CODE *_keyToSet;
    static irr::EKEY_CODE _oldKey;

    static bool _enterOnPause;
};

#endif /* EVENTLISTENER_HPP_ */
