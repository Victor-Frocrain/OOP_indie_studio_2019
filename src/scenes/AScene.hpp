/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** AScene.hpp
*/

#ifndef ASCENE_HPP_
#define ASCENE_HPP_

#include "IScene.hpp"
#include <map>
#include <vector>
#include <tuple>
#include "../entity/AEntity.hpp"
#include "../tools/Tools.hpp"
#include "../map/Entities.hpp"
#include "../map/Logger.hpp"

#pragma comment(lib, "Irrlicht.lib")

class AScene : public IScene {
public:
    AScene(irr::IrrlichtDevice *&device, const std::string &path);
    virtual ~AScene() = default;

    virtual void displayScene() const = 0;
    virtual void manageScene() = 0;
    void manageControls();
    void removeControlSlots();
    void addControlSlots();
    void updateControlButtons();

    std::tuple<buttonTypes, irr::gui::IGUIButton *, bool> addButton(const buttonTypes &type, const irr::core::rect<irr::s32> rect,
                                                                    const wchar_t *text = 0, const irr::s32 id = -1);
    void setButtonsState(const bool state);
    void setSavingButtonsState(const bool &state);

    static sceneType getCurrentScene() noexcept;
    irr::scene::ISceneManager *getRootScene() const noexcept;
    std::vector<std::tuple<buttonTypes, irr::gui::IGUIButton *, bool>> getButtons() const noexcept;
    int getNbPlayers() const noexcept;
    int getNbComputers() const noexcept;
    static std::map<playerType, bool> getAIMap() noexcept;
    static void setAIMap(const playerType &type, const bool &isPresent);
    static void setPlayerMap(const playerType &type, const bool &isPresent);

    static void setCurrentScene(const sceneType &type);
    void addTexture(const char *path, const irr::core::vector2di position = irr::core::vector2di(0, 0),
                    const std::pair<bool, bool> isCenter = std::pair<bool, bool>(false, false),
                    const irr::core::rect<irr::s32> crop = irr::core::rect<irr::s32>(0, 0, 0, 0), irr::io::path name = "", const bool &toDisplay = true);

    static irr::EKEY_CODE getKeyDetectedToParam() noexcept;
    static void setKeyDetectedToParam(const irr::EKEY_CODE &key);

    //static std::map<playerType, std::map<controlTypes, irr::EKEY_CODE>> getControls(void);
    void updateSound();
    void updateLoadButton(const bool &enabled);

    void displayGameSaving(const bool &display);
    void takeEntities();
    void clearEntities();

    void manageDifficultyText();
    void manageDifficultyButtons();

    void setupLeftArrow(irr::gui::IGUIButton *button, const bool &enabled);
    void setupRightArrow(irr::gui::IGUIButton *button, const bool &enabled);

    static void setPlayersRotations(const playerType &player, const rotationTypes &rotation);
    static std::map<playerType, rotationTypes> getPlayersRotations() noexcept;

    static void fillPlayerAndAIAssets();

protected:
    void manageButtons();
    void manageSavingButtons(const irr::s32 &id);

protected:
    irr::IrrlichtDevice *_device;
    irr::video::IVideoDriver *_driver;
    std::string _ressourcesPath;
    irr::scene::ISceneManager *_rootScene;
    irr::gui::IGUIEnvironment *_rootGUI;
    static sceneType _currentScene;
    irr::scene::ISceneManager *_scene;
    irr::scene::ICameraSceneNode *_camera;
    std::vector<std::tuple<irr::video::ITexture *, irr::core::vector2di, irr::core::rect<irr::s32>, bool>> _textures;
    std::vector<std::tuple<buttonTypes, irr::gui::IGUIButton *, bool>> _buttons;
    static std::map<IEntity::EntityType, std::vector<irr::scene::IMeshSceneNode *>> _assets;
    static std::map<IEntity::EntityType, std::vector<irr::scene::IAnimatedMeshSceneNode *>> _animatedAssets;
    static std::map<IEntity::EntityType, irr::scene::IAnimatedMesh *> _animatedMesh;
    static std::vector<irr::scene::IAnimatedMeshSceneNode *> _characterAssets;
    static std::vector<irr::scene::IAnimatedMeshSceneNode *> _playerAssets;
    static std::vector<irr::scene::IAnimatedMeshSceneNode *> _aiAssets;
    irr::core::dimension2du _screenSize;

    static entityMap _entities;
    static int _nbPlayers;
    static int _nbComputers;
    static irr::EKEY_CODE _keyDetectedToParam;
    static Entities *_entityClass;
    //static std::map<playerType, std::map<controlTypes, irr::EKEY_CODE>> _controls;

    static const std::map<buttonTypes, sceneType> _buttonMap;
    static std::map<buttonTypes, bool> _playersMap;
    static std::map<playerType, bool> _aiMap;
    static std::map<buttonTypes, playerType> _buttonPlayersMap;

    static std::map<sceneType, sf::Music> _musics;
    static std::map<SoundEffect, sf::Music> _soundEffects;
    static float _musicsVolume;
    static bool _isMuted;
    static std::map<playerType, rotationTypes> _playersRotations;

    Logger *_logger;
};

#endif /* ASCENE_HPP_ */
