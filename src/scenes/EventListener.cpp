/*
** EPITECH PROJECT, 2020
** EventListener
** File description:
** EventListener.cpp
*/

#include "EventListener.hpp"
#include "AScene.hpp"
#include "ControlMenu.hpp"
#include "../entity/character/player/Player.hpp"
#include "../entity/character/player/APlayerController.hpp"
#include "Pause.hpp"
#include "Game.hpp"

EventListener::EventListener(void)
{}

irr::EKEY_CODE *EventListener::_keyToSet;
irr::EKEY_CODE EventListener::_keyPause = irr::KEY_ESCAPE;
irr::EKEY_CODE EventListener::_oldKey;
bool EventListener::_enterOnPause = false;

void EventListener::setupPlayers(std::vector<Player *> &players) noexcept
{
    _players = players;
}

void EventListener::setWatingKey(irr::EKEY_CODE *keyToSet) noexcept
{
    _keyToSet = keyToSet;
}

bool EventListener::OnEvent(const irr::SEvent& event)
{
    if (event.EventType == irr::EEVENT_TYPE::EET_KEY_INPUT_EVENT &&
        APlayerController::getEventToString()[event.KeyInput.Key] != 0) {
        if (ControlMenu::getIsWaitingKey()) {
            auto associateControl = ControlMenu::getAssociatedControl();
            associateControl.second.first = Menu::getControlToDefine();
            if (Menu::getControlToDefine() != IScene::MEN) {
                _oldKey = *_keyToSet;
                *_keyToSet = event.KeyInput.Key;
                //_keyToSet = nullptr;
            }
            else {
                _oldKey = _keyPause;
                _keyPause = event.KeyInput.Key;
            }
            associateControl.second.second = event.KeyInput.Key;
            ControlMenu::setAssociatedControl(associateControl);
            ControlMenu::setSignalReiceived(true);
            return true;
        } else if (Scenes::getCurrentScene() == AScene::GAME) {
            auto keyTypes = APlayerController::getKeyTypes();
            for (auto player : Game::getPlayerMap()) {
                for (auto keyType : keyTypes) {
                    if (player.second->getPlayerController()->getKeyCode(keyType) == event.KeyInput.Key) {
                        if (event.KeyInput.PressedDown) {
                            player.second->getPlayerController()->setIsKeyPressed(keyType, true);
                        }
                        else {
                            player.second->getPlayerController()->setIsKeyPressed(keyType, false);
                        }
                        //player.second->getPlayerController()->getFunction(keyType)();
                        return true;
                    }
                }
            }
            if (event.KeyInput.Key == _keyPause) {
                _enterOnPause = true;
                Scenes::setCurrentScene(Scenes::PAUSE);
                return true;
            }
        }
    }
    return false;
}

irr::EKEY_CODE EventListener::getKeyPause() noexcept
{
    return _keyPause;
}

void EventListener::setKeyPause(const irr::EKEY_CODE &code)
{
    _keyPause = code;
}

void EventListener::reverseKey()
{
    *_keyToSet = _oldKey;
}

bool EventListener::getEnterOnPause() noexcept
{
    return _enterOnPause;
}

void EventListener::setEnterOnPause(const bool enter)
{
    _enterOnPause = enter;
}