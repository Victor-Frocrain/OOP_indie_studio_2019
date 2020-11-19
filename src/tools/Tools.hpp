/*
** EPITECH PROJECT, 2020
** Tools
** File description:
** Tools.hpp
*/

#ifndef TOOLS_HPP_
#define TOOLS_HPP_

#include <irrlicht/irrlicht.h>
#include <string>
#include <vector>

class Tools {
public:
    static std::string to_string(const irr::io::path &str);
    static std::vector<std::string> getMap(const std::string &filepath) noexcept;
};

#endif /* TOOLS_HPP_ */
