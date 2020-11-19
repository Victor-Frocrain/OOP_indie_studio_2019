/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** ILogger
*/

#ifndef ILOGGER_HPP_
#define ILOGGER_HPP_

#include <map>
#include <vector>
#include <fstream>
#include <iostream>
#include "../entity/IEntity.hpp"
#include "../entity/AEntity.hpp"

class ILogger {
    public:
        virtual ~ILogger() = default;
        virtual bool SaveLog() = 0;
        virtual void LoggerMap() = 0;
};

#endif /* !ILOGGER_HPP_ */
