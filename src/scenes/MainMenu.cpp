/*
** EPITECH PROJECT, 2020
** MainMenu
** File description:
** MainMenu.cpp
*/

#include "MainMenu.hpp"

#ifndef WIN32
#define HOME "/home/"
#include <dirent.h>
#include <sys/types.h>
#endif /* WIN32 */

#ifdef WIN32
#define HOME "C:/"
#include "../../WINDOWS/dirent/include/dirent.h"
#endif /* WIN32 */

MainMenu::MainMenu(irr::IrrlichtDevice *&device, const std::string &path) : Menu(device, path)
{
    irr::s32 buttonWidth = 267;
    irr::s32 buttonHeight = 73;
    irr::s32 pos = 350;
    std::vector<buttonTypes> types = { BEGIN, LOAD, OPT, QUIT };
    std::vector<const wchar_t *> texts = { L"PLAY", L"LOAD GAME", L"OPTIONS", L"QUIT" };

    addTexture((_ressourcesPath + "sprites/menu_background.png").c_str());
    addTexture((_ressourcesPath + "titles/bomberman.png").c_str(), irr::core::vector2di(0, 0), std::pair<bool, bool>(true, false));
    for (size_t i = 0; i < texts.size() && i < types.size(); i++, pos += buttonHeight + 40) {
        _buttons.push_back(addButton(types[i], irr::core::rect<irr::s32>(_screenSize.Width / 2 - buttonWidth / 2, pos, _screenSize.Width / 2 + buttonWidth / 2, pos + buttonHeight), texts[i]));
    }
    for (auto it : _buttons) {
        setupButtonSprite(std::get<1>(it));
    }
    if (!hasFiles(_ressourcesPath)) {
        for (auto it : _buttons) {
            if (std::get<0>(it) == LOAD) {
                std::get<1>(it)->setEnabled(false);
                break;
            }
        }
    }
}

MainMenu::~MainMenu()
{}

bool MainMenu::hasFiles(const std::string &path)
{
    DIR *dir = opendir((path).c_str());
    std::vector<std::string> saveFiles;

    if (dir != nullptr) {
        struct dirent *content;
        for (content = readdir(dir); content != nullptr; content = readdir(dir)) {
            std::string name = content->d_name;
            if (name != "." && name != "..") {
                saveFiles.push_back(name);
            }
        }
        closedir(dir);
    }
    for (size_t i = 0; i < saveFiles.size(); i++) {
        if (saveFiles[i] == "log.txt") {
            std::ifstream fs(path + "log.txt");
            if (!fs.fail()) {
                std::string line;
                std::getline(fs, line);
                if (!line.empty()) {
                    fs.close();
                    return true;
                }
                fs.close();
            }
        }
    }
    return false;
}