/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** IndieStudio.hpp
*/

#ifndef INDIESTUDIO_HPP_
#define INDIESTUDIO_HPP_

#include "irrlicht/irrlicht.h"
#include "../entity/AEntity.hpp"

class IndieStudio {
public:
    static bool compareFloat(const float &f, const float &f2, const float &epsilon = 0.01) noexcept;

    static irr::core::vector3df roundPos(const irr::core::vector3df &pos) noexcept;

    static float calcDist(const float &f, const float &s) noexcept;

    static bool isGoingCenter(const irr::core::vector3df &fPos, const float &x, const float &z) noexcept;

    static int roundPos(const int &pos) noexcept;

    static bool isCollide(const float &fPos, const float &sPos,
                          const float &fSize, const float &sSize) noexcept;

    static bool isCollide(const irr::core::vector3df &fPos,
                          const irr::core::vector3df &sPos,
                          const float &fSize = 0.5,
                          const float &sSize = 0.5) noexcept;

    static std::vector<std::string> getMap(const std::string &filepath) noexcept;

    static std::vector<IEntity *> getElemAtPos(const irr::core::vector3df &pos,
                                                         const entityMap &entityMap,
                                                         const IEntity *entity) noexcept;

    static std::vector<IEntity *> getElemAtPos(const irr::core::vector3df &pos,
                                                         const entityMap &entityMap,
                                                         const float &size) noexcept;

    static std::vector<std::string> getPlayerPref(const std::string &toFind);

    static void setPlayerPref(const std::string &toFind, const std::vector<std::string> &v) noexcept;

    static std::string boolToString(bool rad);

    static bool stringToBool(int rad);
};

#endif /* INDIESTUDIO_HPP_ */
