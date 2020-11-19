/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** Entities.cpp
*/

#include "Entities.hpp"
#include "../scenes/Game.hpp"
#include "../entity/wall/Wall.hpp"
#include "../entity/character/player/Player.hpp"
#include "../entity/character/AI/AI.hpp"
#include "../entity/character/player/APlayerController.hpp"

Entities::Entities(const std::vector<std::string> &map, entityMap &entities) :
    _entities(entities), _map(map)
{}

entityMap &Entities::getEntities(void) noexcept
{
    return _entities;
}

void Entities::fillEntities(void) noexcept
{
    irr::core::vector3df pos = {0, 0, 0};
    std::map<IScene::playerType, Player *> player = Game::getPlayerMap();
    std::vector<Player *> players;
    std::map<AScene::playerType, bool> aiMap = AScene::getAIMap();

    auto aiType = aiMap.begin();
    for (auto it : player)
        players.push_back(it.second);
    for (size_t y = 0, i = 0; y < _map.size(); y++) {
        for (size_t x = 0; x < _map[y].size(); x++) {
            pos = {static_cast<float>(x * 10), -30.0f, static_cast<float>(y * 10)};
            if (_map[y][x] == 'x')
                _entities[IEntity::EntityType::UNBREAKABLEWALL].push_back(new UnBreakableWall(_entities, pos));
            if (_map[y][x] == 'o')
                _entities[IEntity::EntityType::BREAKABLEWALL].push_back(new BreakableWall(_entities, pos));
            if (_map[y][x] == '1') {
                players[i]->setPos(pos);
                _entities[IEntity::EntityType::PLAYER].push_back(players[i++]);
            }
            if (_map[y][x] == '2') {
                for (; aiType != aiMap.end() && !aiType->second; aiType++);
                _entities[IEntity::EntityType::IA].push_back(new AI(IEntity::EntityType::IA, _entities, pos, aiType->first));
                if (aiType != aiMap.end()) {
                    aiType++;
                }
            }
        }
    }
}
