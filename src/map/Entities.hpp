/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** Entities.cpp
*/

#ifndef ENTITIES_HPP_
#define ENTITIES_HPP_

#include "MapGenerator.hpp"
#include "../entity/AEntity.hpp"
#include <map>

class Entities {
public:
    Entities(const std::vector<std::string> &map, entityMap &entities);

    ~Entities(void) = default;

    entityMap &getEntities(void) noexcept;

    void fillEntities(void) noexcept;

private:
    entityMap &_entities;
    std::vector<std::string> _map;
    irr::scene::IMeshSceneNode *_boxAsset;
};

#endif /* ENTITIES_HPP_ */
