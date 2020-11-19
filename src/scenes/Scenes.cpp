/*
** EPITECH PROJECT, 2020
** Scenes
** File description:
** Scenes.cpp
*/

#include "Scenes.hpp"
#include "MainMenu.hpp"
#include "Game.hpp"
#include "Options.hpp"
#include "Pause.hpp"
#include "MenuPlayer.hpp"
#include "ControlMenu.hpp"
#include "EventListener.hpp"
#include "WinMenu.hpp"
#include "GameOver.hpp"
#include "../finder/Finder.hpp"

Scenes::Scenes(irr::IrrlichtDevice *&device, const std::string &path) : AScene(device, path)
{
    addScene(Scenes::sceneType::MENU);
    addScene(Scenes::sceneType::GAME);
    addScene(Scenes::sceneType::OPTIONS);
    addScene(Scenes::sceneType::PAUSE);
    addScene(Scenes::sceneType::PLAYERCHOICE);
    addScene(Scenes::sceneType::CONTROLS);
    addScene(Scenes::sceneType::WIN);
    addScene(Scenes::sceneType::LOSE);
    _musics[MENU].openFromFile(_ressourcesPath + "musics/menu.ogg");
    _musics[MENU].setLoop(true);
    _musics[GAME].openFromFile(_ressourcesPath + "musics/game.ogg");
    _musics[GAME].setLoop(true);
    _musics[WIN].openFromFile(_ressourcesPath + "musics/win.ogg");
    _musics[WIN].setLoop(true);
    _musics[LOSE].openFromFile(_ressourcesPath + "musics/game_over.ogg");
    _soundEffects[BOMB_EXPLOSION].openFromFile(_ressourcesPath + "musics/explosion.ogg");
    playMusic(_currentScene);
    Game::setPlayerBinds();
}

Scenes::~Scenes()
{
    for (auto it : _scenes) {
        delete it.second;
    }
}

irr::f32 Scenes::_deltaTime = 0;

const std::map<Scenes::sceneType, Scenes::sceneType> Scenes::_musicsMap {
    { MENU, MENU },
    { OPTIONS, MENU },
    { PLAYERCHOICE, MENU },
    { PAUSE, GAME },
    { CONTROLS, MENU },
    { GAME, GAME },
    { WIN, WIN },
    { LOSE, LOSE }
};

std::map<AScene::sceneType, AScene *> Scenes::getScenes() const noexcept
{
    return _scenes;
}

AScene *Scenes::getSceneInstance(const AScene::sceneType &type) noexcept
{
    return _scenes[type];
}

void Scenes::playSoundEffect(const SoundEffect &soundEffect) noexcept
{
    _soundEffects[soundEffect].play();
}

void Scenes::stopSoundEffect(const SoundEffect& soundEffect)
{
    _soundEffects[soundEffect].stop();
}

void Scenes::addScene(const sceneType &type)
{
    AScene *newScene = nullptr;

    switch (type) {
        case sceneType::MENU: {
            newScene = new MainMenu(_device, _ressourcesPath);
            break;
        }
        case sceneType::GAME: {
            newScene = new Game(_device, _ressourcesPath);
            break;
        }
        case sceneType::OPTIONS: {
            newScene = new Options(_device, _ressourcesPath);
            break;
        }
        case sceneType::PAUSE: {
            newScene = new Pause(_device, _ressourcesPath);
            break;
        }
        case sceneType::PLAYERCHOICE: {
            newScene = new MenuPlayer(_device, _ressourcesPath);
            break;
        }
        case sceneType::CONTROLS: {
            newScene = new ControlMenu(_device, _ressourcesPath);
            break;
        }
        case sceneType::WIN: {
            newScene = new WinMenu(_device, _ressourcesPath);
            break;
        }
        case sceneType::LOSE: {
            newScene = new GameOver(_device, _ressourcesPath);
            break;
        }
        default: {
            break;
        }
    }
    if (newScene != nullptr) {
        _scenes[type] = newScene;
    }
}

void Scenes::manageScene()
{
    sceneType current = _currentScene;

    Scenes::setCurrentScene(_currentScene);
    _scenes[_currentScene]->manageScene();
    setCurrentScene(Scenes::getCurrentScene());
    if (_currentScene == GAME && current != GAME) {
        if (_playerAssets.empty() && _aiAssets.empty()) {
            fillPlayerAndAIAssets();
        }
    }
    if (_currentScene == MENU && current != MENU) {
        WinMenu::setIntroIsEnded(false);
        WinMenu::setIntroIsStarted(false);
        Game::resetWinAndLose();
        _playerAssets.clear();
        _aiAssets.clear();
        _scenes[_currentScene]->updateLoadButton(MainMenu::hasFiles(_ressourcesPath));
        Game::clearPlayerMap();
        Game::clearAll();
        clearEntities();
    }
    if (_currentScene == CONTROLS && Game::getPlayerMap().empty()) {
        Game::loadPlayers();
    }
    if (current == CONTROLS && _currentScene != CONTROLS) {
        _scenes[current]->removeControlSlots();
    }
    else if (current != CONTROLS && _currentScene == CONTROLS) {
        _scenes[_currentScene]->addControlSlots();
        _scenes[_currentScene]->manageDifficultyText();
        _scenes[_currentScene]->manageDifficultyButtons();
    }
    if ((current != _currentScene || EventListener::getEnterOnPause()) && current != DEFAULT && _currentScene != DEFAULT && current != EXIT && _currentScene != EXIT) {
        stopMusic(_currentScene);
        if (_currentScene != WIN) {
            playMusic(_currentScene);
        }
        _scenes[current]->setButtonsState(false);
        _scenes[_currentScene]->setButtonsState(true);
        if (_currentScene == PAUSE) {
            _scenes[_currentScene]->setSavingButtonsState(false);
            EventListener::setEnterOnPause(false);
        }
    }
    if (_currentScene == WIN || (current == WIN && _currentScene != WIN)) {
        WinMenu *win = static_cast<WinMenu *>(_scenes[WIN]);
        win->manageMusics();
        if (_currentScene != WIN) {
            win->resetPlayersPodium();
        }
        else if (current != WIN) {
            win->managePlayersPodium();
        }
    }
    if (_currentScene == LOSE || (current == LOSE && _currentScene != LOSE)) {
        GameOver *lose = static_cast<GameOver *>(_scenes[LOSE]);
        if (_currentScene != LOSE) {
            lose->resetPlayerShame();
            _musics[LOSE].stop();
        }
        else if (current != LOSE) {
            lose->managePlayerShame();
        }
    }
}

void Scenes::displayScene() const
{}

void Scenes::stopMusic(const sceneType &type)
{
    std::map<sceneType, sf::Music>::iterator it;
    for (it = _musics.begin(); it != _musics.end(); it++) {
        if (it->first != _musicsMap.at(type)) {
            if (it->second.getStatus() == sf::Music::Playing) {
                it->second.stop();
            }
            break;
        }
    }
}

void Scenes::playMusic(const sceneType &type)
{
    std::map<sceneType, sf::Music>::iterator it;
    for (it = _musics.begin(); it != _musics.end(); it++) {
        if (it->first == _musicsMap.at(type)) {
            if (it->second.getStatus() != sf::Music::Playing) {
                it->second.play();
            }
            break;
        }
    }
}

void Scenes::setDeltaTime(irr::f32 newDeltaTime)
{
    _deltaTime = newDeltaTime;
}

irr::f32 Scenes::getDeltaTime(void)
{
    return _deltaTime;
}
