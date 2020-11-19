/*
** EPITECH PROJECT, 2020
** Scenes
** File description:
** Scenes.hpp
*/

#ifndef SCENES_HPP_
#define SCENES_HPP_

#include "AScene.hpp"

class Scenes : public AScene {
public:

    Scenes(irr::IrrlichtDevice *&device, const std::string &path);

    ~Scenes();

    std::map<sceneType, AScene *> getScenes() const noexcept;
    AScene *getSceneInstance(const sceneType &type) noexcept;

    void addScene(const sceneType &type);
    void displayScene() const;
    void manageScene();
    void playMusic(const sceneType &type);
    void stopMusic(const sceneType &type);
    static void playSoundEffect(const SoundEffect &soundEffect) noexcept;
    static void stopSoundEffect(const SoundEffect& soundEffect);

    static void setDeltaTime(irr::f32 newDeltaTime);
    //std::map<sceneType, sf::Music> getMusics() noexcept;

    static irr::f32 getDeltaTime(void);

private:
    std::map<sceneType, AScene *> _scenes;

    static irr::f32 _deltaTime;

    static const std::map<sceneType, sceneType> _musicsMap;
};

#endif /* SCENES_HPP_ */
