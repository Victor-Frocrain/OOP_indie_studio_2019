/*
** EPITECH PROJECT, 2020
** Tools
** File description:
** Tools.cpp
*/

#include "Tools.hpp"
#include <fstream>

std::string Tools::to_string(const irr::io::path &str)
{
    std::string result = "";

    for (irr::u32 i = 0; i < str.size(); i++) {
        result += str[i];
    }
    return result;
}

std::vector<std::string> Tools::getMap(const std::string &filepath) noexcept
{
    std::vector<std::string> result;
    std::fstream fs(filepath);
    std::string line;

    while (std::getline(fs, line))
        result.push_back(line);
    fs.close();
    return result;
}
