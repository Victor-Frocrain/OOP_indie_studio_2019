/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** MapGenerator.hpp
*/

#ifndef MAPGENERATOR_HPP_
#define MAPGENERATOR_HPP_

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>

class MapGenerator {
public:
    MapGenerator(const int &width, const int &height, const int &nbPlayer,
                 const int &nbIa, const std::string &path);
    ~MapGenerator(void) = default;

    bool createAndFillFileMap(const std::string &name = "map.txt");

    const std::vector<std::string> &getMap(void) const noexcept;

private:
    const std::string generateFirstAndLastLine(void);
    void initMap(void);
    void placePlayer(void);
    void placeIa(void);
    void generateunbreakWall(void);
    void generateRandomBreakWall(void);

private:
    int _width;
    int _height;
    int _nbPlayer;
    int _nbIa;
    std::string _path;
    std::vector<std::string> _map;
};

#endif /* !MAPGENERATOR_HPP_ */
