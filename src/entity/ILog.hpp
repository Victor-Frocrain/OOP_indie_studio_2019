/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** ILog
*/

#ifndef ILOG_HPP_
#define ILOG_HPP_

#include <string>

class ILog {
    public:
        virtual ~ILog(void) = default;
        virtual std::string ToLog() const noexcept = 0;
};

#endif /* !ILOG_HPP_ */
