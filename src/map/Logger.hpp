/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Logger
*/

#ifndef LOGGER_HPP_
#define LOGGER_HPP_

#include "ILogger.hpp"
#include "../scenes/IScene.hpp"
#include "../utils/IndieStudio.hpp"
#include "../../src/entity/power_up/IPowerUp.hpp"

class Logger : public ILogger {
    public:
        Logger(entityMap &entities, const std::string &path);
        ~Logger();
        void LoggerMap();
        bool SaveLog();
    private: //function
        IPowerUp::PowerUpType convertIntinPowerUpType(int playerType);
        IScene::playerType convertIntinPlayerType(int playerType);
        std::pair<irr::core::vector3df, std::vector<int>> parseAentity(std::string entity, std::string type, std::string posOrPowerUp, int nb_arg, bool isPosAndPowerUp);
        std::pair<float, int> oneArg(std::string entity, std::string type, std::string type2);
        void parseInfo(std::vector<std::string> info);
    private: //variable
        entityMap &_entities;
        std::string _path;
};

#endif /* !LOGGER_HPP_ */
