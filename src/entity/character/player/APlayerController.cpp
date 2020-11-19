/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** APlayerController.cpp
*/

#include "APlayerController.hpp"
#include "../../../utils/FileReader.hpp"
#include "../../../finder/Finder.hpp"
#include "../../../utils/IndieStudio.hpp"
#include <sstream>
#include <iostream>

APlayerController::APlayerController(ACharacter *player, const Scenes::playerType &nbPlayer) :
    _controls({
            Control(std::bind(&ACharacter::front, player)),
            Control(std::bind(&ACharacter::back, player)),
            Control(std::bind(&ACharacter::left, player)),
            Control(std::bind(&ACharacter::right, player)),
            Control(std::bind(&ACharacter::dropBomb, player))}),
    _type(nbPlayer)
{
    try {
        auto param = IndieStudio::getPlayerPref("Player" + std::to_string(nbPlayer));
        if (param.size() != 5)
            return;
        _controls[IPlayerController::UP].setKey(std::stoi(param[0]));
        _controls[IPlayerController::DOWN].setKey(std::stoi(param[1]));
        _controls[IPlayerController::LEFT].setKey(std::stoi(param[2]));
        _controls[IPlayerController::RIGHT].setKey(std::stoi(param[3]));
        _controls[IPlayerController::BOMB].setKey(std::stoi(param[4]));
    } catch (...) {}
}

void APlayerController::setIsKeyPressed(const KeyType &keyType, const bool &isKeyPressed) noexcept
{
    _controls[keyType].setIsKeyPressed(isKeyPressed);
}

void APlayerController::savePlayerPref(void) const
{
    std::vector<std::string> v;

    for (auto it : _controls)
        v.push_back(std::to_string(it.getKey()));
    IndieStudio::setPlayerPref("Player" + std::to_string(_type), v);
}

const std::vector<IPlayerController::KeyType> APlayerController::_keyTypes = {
    IPlayerController::UP,
    IPlayerController::DOWN,
    IPlayerController::LEFT,
    IPlayerController::RIGHT,
    IPlayerController::BOMB
};

const std::vector<IPlayerController::KeyType> &APlayerController::getKeyTypes(void) noexcept
{
    return _keyTypes;
}

const wchar_t *APlayerController::_defaultToString = L"UNKNOWN";

const wchar_t *APlayerController::getString(const irr::EKEY_CODE &state) const noexcept
{
    auto it = _eventToString.find(state);
    if (it != _eventToString.end())
        return it->second;
    std::cerr << "Unrecognized command id: " << state << std::endl;
    return _defaultToString;
}

std::map<irr::EKEY_CODE, const wchar_t *> APlayerController::getEventToString() noexcept
{
    return _eventToString;
}

const irr::EKEY_CODE &APlayerController::getKeyCode(const KeyType &keyType) const noexcept
{
    return _controls[keyType].getKey();
}

const wchar_t *APlayerController::toString(const KeyType &keyType) const noexcept
{
    return getString(getKeyCode(keyType));
}

void APlayerController::operator()(const KeyType &keyType) const noexcept
{
    _controls[keyType]();
}

irr::EKEY_CODE *APlayerController::setKeyCode(const KeyType &keyType) noexcept
{
    return _controls[keyType].setKey();
}

Scenes::playerType APlayerController::getPlayerType() const noexcept
{
    return _type;
}

std::map<irr::EKEY_CODE, const wchar_t *> APlayerController::_eventToString {
    { irr::KEY_LBUTTON, L"MOUSE LEFT" },
    { irr::KEY_RBUTTON, L"MOUSE RIGHT" },
    { irr::KEY_CANCEL, L"CANCEL" },
    { irr::KEY_MBUTTON, L"MOUSE WHEEL" },
    { irr::KEY_XBUTTON1, L"XBUTTON1" },
    { irr::KEY_XBUTTON2, L"XBUTTON2" },
    { irr::KEY_BACK, L"BACK" },
    { irr::KEY_TAB, L"TAB" },
    { irr::KEY_HOME, L"HOME" },
    { irr::KEY_CLEAR, L"CLEAR" },
    { irr::KEY_RETURN, L"ENTER" },
    { irr::KEY_KEY_A, L"A" },
    { irr::KEY_KEY_B, L"B" },
    { irr::KEY_KEY_C, L"C" },
    { irr::KEY_KEY_D, L"D" },
    { irr::KEY_KEY_E, L"E" },
    { irr::KEY_KEY_F, L"F" },
    { irr::KEY_KEY_G, L"G" },
    { irr::KEY_KEY_H, L"H" },
    { irr::KEY_KEY_I, L"I" },
    { irr::KEY_KEY_J, L"J" },
    { irr::KEY_KEY_K, L"K" },
    { irr::KEY_KEY_L, L"L" },
    { irr::KEY_KEY_M, L"M" },
    { irr::KEY_KEY_N, L"N" },
    { irr::KEY_KEY_O, L"O" },
    { irr::KEY_KEY_P, L"P" },
    { irr::KEY_KEY_Q, L"Q" },
    { irr::KEY_KEY_R, L"R" },
    { irr::KEY_KEY_S, L"S" },
    { irr::KEY_KEY_T, L"T" },
    { irr::KEY_KEY_U, L"U" },
    { irr::KEY_KEY_V, L"V" },
    { irr::KEY_KEY_W, L"W" },
    { irr::KEY_KEY_X, L"X" },
    { irr::KEY_KEY_Y, L"Y" },
    { irr::KEY_KEY_Z, L"Z" },
    { irr::KEY_UP, L"UP" },
    { irr::KEY_DOWN, L"DOWN" },
    { irr::KEY_LEFT, L"LEFT" },
    { irr::KEY_RIGHT, L"RIGHT" },
    { irr::KEY_ACCEPT, L"ENTER" },
    { irr::KEY_SPACE, L"SPACE" },
    { irr::KEY_ESCAPE, L"ESCAPE" },
    { irr::KEY_KEY_0, L"0" },
    { irr::KEY_KEY_1, L"1" },
    { irr::KEY_KEY_2, L"2" },
    { irr::KEY_KEY_3, L"3" },
    { irr::KEY_KEY_4, L"4" },
    { irr::KEY_KEY_5, L"5" },
    { irr::KEY_KEY_6, L"6" },
    { irr::KEY_KEY_7, L"7" },
    { irr::KEY_KEY_8, L"8" },
    { irr::KEY_KEY_9, L"9" },
    { irr::KEY_DELETE, L"DELETE" },
    { irr::KEY_BACK, L"BACK" },
    { irr::KEY_ADD, L"ADD" },
    { irr::KEY_COMMA, L"," },
    { irr::KEY_F1, L"F1" },
    { irr::KEY_F2, L"F2" },
    { irr::KEY_F3, L"F3" },
    { irr::KEY_F4, L"F4" },
    { irr::KEY_F5, L"F5" },
    { irr::KEY_F6, L"F6" },
    { irr::KEY_F7, L"F7" },
    { irr::KEY_F8, L"F8" },
    { irr::KEY_F9, L"F9" },
    { irr::KEY_F10, L"F10" },
    { irr::KEY_F11, L"F11" },
    { irr::KEY_F12, L"F12" },
    { irr::KEY_DIVIDE, L"/" },
    { irr::KEY_LSHIFT, L"SHIFT" },
    { irr::KEY_RSHIFT, L"SHIFT" },
    { irr::KEY_LCONTROL, L"CTRL" },
    { irr::KEY_RCONTROL, L"CTRL" },
    { irr::KEY_MINUS, L"-" },
    { irr::KEY_MULTIPLY, L"*" },
    { irr::KEY_SEPARATOR, L"." },
    { irr::KEY_NUMPAD0, L"0" },
    { irr::KEY_NUMPAD1, L"1" },
    { irr::KEY_NUMPAD2, L"2" },
    { irr::KEY_NUMPAD3, L"3" },
    { irr::KEY_NUMPAD4, L"4" },
    { irr::KEY_NUMPAD5, L"5" },
    { irr::KEY_NUMPAD6, L"6" },
    { irr::KEY_NUMPAD7, L"7" },
    { irr::KEY_NUMPAD8, L"8" },
    { irr::KEY_NUMPAD9, L"9" },
    { irr::KEY_ADD, L"+" },
    { irr::KEY_PLUS, L"+" },
    { irr::KEY_SUBTRACT, L"-" },
    { irr::KEY_NUMLOCK, L"NUM LOCK" },
    { irr::KEY_KEY_CODES_COUNT, L"" }
};
