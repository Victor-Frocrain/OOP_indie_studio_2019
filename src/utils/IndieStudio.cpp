/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** IndieStudio.cpp
*/

#include "IndieStudio.hpp"
#include "../scenes/IScene.hpp"
#include <fstream>
#include "FileReader.hpp"
#include "../finder/Finder.hpp"

std::vector<std::string> IndieStudio::getPlayerPref(const std::string &toFind)
{
    FileReader fr(AFinder::getFilePath() + ".PlayerPref.txt");
    return fr.find(toFind);
}

void IndieStudio::setPlayerPref(const std::string &toFind, const std::vector<std::string> &v) noexcept
{
    std::string path = AFinder::getFilePath() + ".PlayerPref.txt";
    std::vector<std::string> map = IndieStudio::getMap(path);

    if (!map.size()) {
        std::ofstream ofs(path);
        ofs << toFind << ":" << std::endl;
        for (auto it : v)
            ofs << it << std::endl;
        ofs.close();
    } else {
        bool found = false;
        for (auto it = map.begin(); it != map.end();) {
            if (FileReader::isSection(*it, toFind)) {
                it++;
                while (it != map.end() && !FileReader::isSection(*it))
                    it = map.erase(it);
                for (auto str : v)
                    it = map.insert(it, str) + 1;
                found = true;
                break;
            } else
                it++;
        }
        if (!found) {
            std::ofstream ofs(path, std::ios::app);
            ofs << toFind << ":" << std::endl;
            for (auto it : v)
                ofs << it << std::endl;
            ofs.close();
        } else {
            std::ofstream ofs(path, std::ios::trunc);
            for (auto it : map)
                ofs << it << std::endl;
            ofs.close();
        }
    }
}

bool IndieStudio::compareFloat(const float &f, const float &f2, const float &epsilon) noexcept
{
    return fabs(f - f2) < epsilon;
}

irr::core::vector3df IndieStudio::roundPos(const irr::core::vector3df &pos) noexcept
{
    return irr::core::vector3df(roundPos(pos.X), roundPos(pos.Y), roundPos(pos.Z));
}

int IndieStudio::roundPos(const int &pos) noexcept
{
    if (pos % SCREEN_SCALE < 0.5 * SCREEN_SCALE)
        return (pos / SCREEN_SCALE * SCREEN_SCALE);
    return (pos / SCREEN_SCALE * SCREEN_SCALE + SCREEN_SCALE);
}

std::vector<std::string> IndieStudio::getMap(const std::string &filepath) noexcept
{
    std::vector<std::string> result;
    std::ifstream fs(filepath);
    std::string line;

    if (fs.is_open()) {
        while (std::getline(fs, line))
            result.push_back(line);
        fs.close();
    }
    return result;
}

float IndieStudio::calcDist(const float &f, const float &s) noexcept
{
    return std::abs(f - s);
}

bool IndieStudio::isGoingCenter(const irr::core::vector3df &fPos, const float &x, const float &z) noexcept
{
    float pos = (x != 0) ? fPos.X : fPos.Z;
    float round = IndieStudio::roundPos(pos);

    return calcDist(pos, round) > calcDist(pos + ((x != 0) ? x : z), round);
}


std::vector<IEntity *> IndieStudio::getElemAtPos(const irr::core::vector3df &pos,
                                           const entityMap &entityMap,
                                           const float &size) noexcept
{
    std::vector<IEntity *> elem;

    for (auto it : entityMap) {
        for (auto entity : it.second) {
            if (isCollide(pos / SCREEN_SCALE, entity->getPos() / SCREEN_SCALE, size, entity->getCollisionSize()))
                elem.push_back(entity);
        }
    }
    return elem;
}

std::vector<IEntity *> IndieStudio::getElemAtPos(const irr::core::vector3df &pos,
                                                           const entityMap &entityMap,
                                                           const IEntity *entityTested) noexcept
{
    std::vector<IEntity *> elem;

    for (auto it : entityMap) {
        for (auto entity : it.second) {
            if (entity == entityTested)
                continue;
            if (isCollide(pos / SCREEN_SCALE, entity->getPos() / SCREEN_SCALE, entityTested->getCollisionSize(), entity->getCollisionSize()))
                elem.push_back(entity);
        }
    }
    return elem;
}

bool IndieStudio::isCollide(const irr::core::vector3df &fPos,
                            const irr::core::vector3df &sPos,
                            const float &fSize, const float &sSize) noexcept
{
    return isCollide(fPos.X, sPos.X, fSize, sSize) &&
        isCollide(fPos.Y, sPos.Y, fSize, sSize) &&
        isCollide(fPos.Z, sPos.Z, fSize, sSize);
}

bool IndieStudio::isCollide(const float &fPos, const float &sPos,
                            const float &fSize, const float &sSize) noexcept
{
    return ((fPos + fSize < sPos + sSize && fPos + fSize > sPos - sSize) ||
            (fPos - fSize < sPos + sSize && fPos - fSize > sPos - sSize) ||
            (fPos + fSize < sPos + sSize == fPos - fSize > sPos - sSize));
}

std::string IndieStudio::boolToString(bool rad)
{
    return rad == true ? "1" : "0";
}

bool IndieStudio::stringToBool(int rad)
{
    return rad == 1 ? true : false;
}