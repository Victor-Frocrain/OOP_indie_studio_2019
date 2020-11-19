/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Logger
*/

#include "Logger.hpp"
#include "../entity/wall/Wall.hpp"
#include "../entity/power_up/APowerUp.hpp"
#include "../entity/character/player/Player.hpp"
#include "../entity/character/AI/AI.hpp"
#include "../scenes/AScene.hpp"
#include "../scenes/Game.hpp"

Logger::Logger(entityMap &entities, const std::string &path) : _entities(entities), _path(path)
{}

Logger::~Logger()
{}

bool Logger::SaveLog()
{
    std::string unbreakableWall;
    std::string breakableWall;
    std::string player;
    std::string Ia;
    std::string entitypowerup;
    std::ofstream file;

    for (size_t i = 0; i != _entities[IEntity::EntityType::UNBREAKABLEWALL].size(); i++)
        unbreakableWall += _entities[IEntity::EntityType::UNBREAKABLEWALL][i]->ToLog() + "\n";

    for (size_t i = 0; i != _entities[IEntity::EntityType::BREAKABLEWALL].size(); i++) {
        breakableWall += _entities[IEntity::EntityType::BREAKABLEWALL][i]->ToLog() + "\n";
    }

    for (size_t i = 0; i != _entities[IEntity::EntityType::PLAYER].size(); i++)
        player += _entities[IEntity::EntityType::PLAYER][i]->ToLog() + "\n";

    for (size_t i = 0; i != _entities[IEntity::EntityType::IA].size(); i++)
        Ia += _entities[IEntity::EntityType::IA][i]->ToLog() + "\n";

    for (size_t i = 0; i != _entities[IEntity::EntityType::BONUS].size(); i++)
        entitypowerup += _entities[IEntity::EntityType::BONUS][i]->ToLog() + "\n";
    file.open(_path + "log.txt");
    if (file.bad())
        return false;
    file << unbreakableWall;
    file << breakableWall;
    file << player;
    file << Ia;
    file << entitypowerup;
    file.close();
    return true;
}

std::pair<irr::core::vector3df, std::vector<int>> Logger::parseAentity(std::string entity, std::string type, std::string posOrPowerUp, int nb_arg, bool isPosAndPowerUp)
{
    std::vector<int> power;
    irr::core::vector3df posA = {0, 0, 0};
    int pos = entity.find(type);
    std::string cpy;
    std::string sub = entity.substr(pos); // find type

    pos = sub.find(posOrPowerUp);

    if (pos != std::string::npos) {
        sub = sub.substr(pos); //find AEntity

        pos = sub.find("(");
        sub = sub.substr(pos + 1);
        pos = sub.find(",");
        cpy = sub.substr(pos - pos, pos);
        if (isPosAndPowerUp == false)
            posA.X = std::stof(cpy);
        else
            power.push_back(std::atoi(cpy.c_str()));
        for (int i = 0; i != nb_arg - 2; i++) {
            sub = sub.substr(pos + 2);
            pos = sub.find(",");
            cpy = sub.substr(pos - pos, pos);
            if (isPosAndPowerUp == false)
                posA.Y = std::stof(cpy);
            else
                power.push_back(std::atoi(cpy.c_str()));
        }

        sub = sub.substr(pos + 2);
        pos = sub.find(")");
        cpy = sub.substr(pos - pos, pos);
        if (isPosAndPowerUp == false)
            posA.Z = std::stof(cpy);
        else
            power.push_back(std::atoi(cpy.c_str()));
        return {posA, power};
    } else {
        power.push_back(0);
        return {posA, power};
    }
}

std::pair<float, int> Logger::oneArg(std::string entity, std::string type, std::string type2)
{
    int pos = entity.find(type);
    std::string sub = entity.substr(pos);

    pos = sub.find(type2);
    sub = sub.substr(pos);
    pos = sub.find("(");
    sub = sub.substr(pos + 1);
    pos = sub.find(")");
    sub = sub.substr(pos - pos, pos);

    if (type2 == "LastBombTimer")
        return {std::stof(sub), 0};
    return {0, std::atoi(sub.c_str())};
}

Scenes::playerType Logger::convertIntinPlayerType(int playerType)
{
    if (playerType == 1)
        return Scenes::playerType::P1;
    else if (playerType == 2)
        return Scenes::playerType::P2;
    else if (playerType == 3)
        return Scenes::playerType::P3;
    else if (playerType == 4)
        return Scenes::playerType::P4;
    else
        return Scenes::playerType::PNONE;
}

IPowerUp::PowerUpType Logger::convertIntinPowerUpType(int powerUpType)
{
    if (powerUpType == 0)
        return IPowerUp::PowerUpType::SPEED;
    else if (powerUpType == 1)
        return IPowerUp::PowerUpType::RANGE;
    else if (powerUpType == 2)
        return IPowerUp::PowerUpType::NBBOMB;
    else if (powerUpType == 3)
        return IPowerUp::PowerUpType::WALLPASS;
    return IPowerUp::PowerUpType::NOBONUS;
}

void Logger::parseInfo(std::vector<std::string> info)
{
    auto binds = Game::getPlayersBind();
    std::vector<int> power;
    irr::core::vector3df posA = {0, 0, 0};
    int res = 0;
    float res2 = 0;
    int playerId = 0;
    int isDead = 0;
    std::vector<IScene::playerType> types = { IScene::P1, IScene::P2, IScene::P3, IScene::P4 };

    for (size_t i = 0; i < types.size(); i++) {
        AScene::setAIMap(types[i], false);
    }
    for (size_t i = 0; i != info.size(); i++) {
        if (std::strncmp(info[i].c_str(), "UnBreakableWall", 15) == 0) {
            posA = parseAentity(info[i], "UnBreakableWall", "AEntity", 3, false).first;
            _entities[IEntity::EntityType::UNBREAKABLEWALL].push_back(new UnBreakableWall(_entities, posA));
        }
        else if (std::strncmp(info[i].c_str(), "BreakableWall", 13) == 0) {
            posA = parseAentity(info[i], "BreakableWall", "AEntity", 3, false).first;
            power = parseAentity(info[i], "BreakableWall", "APowerUp", 4, true).second;
            _entities[IEntity::EntityType::BREAKABLEWALL].push_back(new BreakableWall(_entities, posA));

            if (power.size() > 1) {
                posA = parseAentity(info[i], "EntityPowerUp", "AEntity", 3, false).first;
                EntityPowerUp *powerUp = new EntityPowerUp(_entities, posA);
                powerUp->setSpeed(power[0]);
                powerUp->setRange(power[1]);
                powerUp->setNbBomb(power[2]);
                powerUp->setWallPass(power[3]);
                res2 = oneArg(info[i], "EntityPowerUp", "ImmortalityTimer").first;
                powerUp->setImmortalityTimer(res2);
                res = oneArg(info[i], "EntityPowerUp", "Droppped").second;
                powerUp->setImmortalityTimer(IndieStudio::stringToBool(res));
            }
        }
        else if (std::strncmp(info[i].c_str(), "Player", 6) == 0) {
            posA = parseAentity(info[i], "Player", "AEntity", 3, false).first;
            power = parseAentity(info[i], "Player", "APowerUp", 4, true).second;
            res = oneArg(info[i], "Player", "PlayerController").second;
            isDead = oneArg(info[i], "Player", "IsDead").second;

            for (auto it : binds) {
                if (it.first == convertIntinPlayerType(res)) {
                    _entities[IEntity::EntityType::PLAYER].push_back(it.second);
                    _entities[IEntity::EntityType::PLAYER][playerId]->setPos(posA);
                    Player *player = dynamic_cast<Player *>(_entities[IEntity::EntityType::PLAYER][playerId]);
                    player->setIsDead(isDead);
                    player->resetBombs();
                    Game::addPlayerInMap(it.first, player);
                    playerId++;
                    break;
                }
            }

            PowerUp *powerup = new PowerUp();
            powerup->setSpeed(power[0]);
            powerup->setRange(power[1]);
            powerup->setNbBomb(power[2]);
            powerup->setWallPass(power[3]);
        }
        else if (std::strncmp(info[i].c_str(), "Ia", 2) == 0) {
            posA = parseAentity(info[i], "Ia", "AEntity", 3, false).first;
            power = parseAentity(info[i], "Ia", "APowerUp", 4, true).second;
            res = oneArg(info[i], "Ia", "IaController").second;
            isDead = oneArg(info[i], "Ia", "IsDead").second;

            AI *ai = new AI(IEntity::EntityType::IA, _entities, posA, convertIntinPlayerType(res));
            AScene::setAIMap(convertIntinPlayerType(res), true);
            PowerUp *powerup = new PowerUp();
            powerup->setSpeed(power[0]);
            powerup->setRange(power[1]);
            powerup->setNbBomb(power[2]);
            powerup->setWallPass(power[3]);
            ai->setIsDead(isDead);
            _entities[IEntity::EntityType::IA].push_back(ai);
        }
        else if (std::strncmp(info[i].c_str(), "EntityPowerUp", 13) == 0) {
            posA = parseAentity(info[i], "EntityPowerUp", "AEntity", 3, false).first;
            EntityPowerUp *entitypowerup = new EntityPowerUp(_entities, posA);
            _entities[IEntity::EntityType::BONUS].push_back(entitypowerup);
            power = parseAentity(info[i], "EntityPowerUp", "APowerUp", 4, true).second;
            res = oneArg(info[i], "EntityPowerUp", "PowerUpType").second;

            entitypowerup->setSpeed(power[0]);
            entitypowerup->setRange(power[1]);
            entitypowerup->setNbBomb(power[2]);
            entitypowerup->setWallPass(IndieStudio::stringToBool(power[3]));
            entitypowerup->setPowerUpType(convertIntinPowerUpType(res));
        }
    }
}

void Logger::LoggerMap()
{
    std::string ligne;
    int count = 0;
    std::vector<std::string> info;
    std::ifstream fichier(_path + "log.txt", std::ios::in);
    if(!fichier.fail())
    {
        while(std::getline(fichier, ligne))
            info.push_back(ligne);
    } else
        std::cerr << "Impossible d'ouvrir le fichier !" << std::endl;
    parseInfo(info);
}
