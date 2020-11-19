/*
** EPITECH PROJECT, 2020
** Indie Studio
** File description:
** MapGenerator.cpp
*/

#include "MapGenerator.hpp"

MapGenerator::MapGenerator(const int &width, const int &height,
                           const int &nbPlayer, const int &nbIa,
                           const std::string &path) :
    _width(width), _height(height), _nbPlayer(nbPlayer), _nbIa(nbIa), _path(path)
{
    initMap();
    placePlayer();
    placeIa();
    generateunbreakWall();
    generateRandomBreakWall();
}

const std::vector<std::string> &MapGenerator::getMap(void) const noexcept
{
    return _map;
}

const std::string MapGenerator::generateFirstAndLastLine(void)
{
    std::string firstAndLastLine(_width, 'x');
    return firstAndLastLine;
}

void MapGenerator::initMap(void)
{
    std::string line(_width, ' ');

    std::fill(line.begin(), line.begin() + 1, 'x');
    std::fill(line.begin() + (_width - 1), line.end(), 'x');
    _map.push_back(generateFirstAndLastLine());
    for(int i = 1; i != _height - 1; i++) {
        _map.push_back(line);
    }
    _map.push_back(generateFirstAndLastLine());
}

void MapGenerator::placePlayer(void)
{
    int count = 0;

    for (int i = 0; i != _height; i++) {
        if (count >= _nbPlayer)
            break;
        for (int j = 0; j != _width; j++) {
            if (_map[i][j] == ' ' && i == 1 && j == 1) {
                _map[i][j] = '1';
                count++;
            }
            if (_map[i][j] == ' ' && i == 1 && j == (_width - 2)) {
                _map[i][j] = '1';
                count++;
            }
            if (_map[i][j] == ' ' && i == (_height - 2) && j == 1) {
                _map[i][j] = '1';
                count++;
            }
            if (_map[i][j] == ' ' && i == (_height - 2) && j == (_width - 2)) {
                _map[i][j] = '1';
                count++;
            }
            if (count >= _nbPlayer)
                break;
        }
    }
}

void MapGenerator::placeIa(void)
{
    int count = 0;

    for (int i = 0; i != _height; i++) {
        if (count >= _nbIa)
            break;
        for (int j = 0; j != _width; j++) {
            if (_map[i][j] == ' ' && i == 1 && j == 1) {
                _map[i][j] = '2';
                count++;
            }
            if (_map[i][j] == ' ' && i == 1 && j == (_width - 2)) {
                _map[i][j] = '2';
                count++;
            }
            if (_map[i][j] == ' ' && i == (_height - 2) && j == 1) {
                _map[i][j] = '2';
                count++;
            }
            if (_map[i][j] == ' ' && i == (_height - 2) && j == (_width - 2)) {
                _map[i][j] = '2';
                count++;
            }
            if (count >= _nbIa)
                break;
        }
    }
}

void MapGenerator::generateunbreakWall(void)
{
    for (int j = 1; j != _height - 2; j++) {
        if (j % 2 == 0) {
            for (int i = 1; i != _width - 2; i++) {
                if (i % 2 == 0)
                    _map[j][i] = 'x';
            }
        }
    }
}

void MapGenerator::generateRandomBreakWall(void)
{
    std::srand(std::time(nullptr));
    int rand  = 0;
    int x = 0;

    for (int j = 1; j != _height - 1; j++) {
        rand = std::rand() % _width;
        for (; rand >= std::count(_map[j].begin(), _map[j].end(), ' ') || rand <= (std::count(_map[j].begin(), _map[j].end(), ' ') / 2) + 2; rand = std::rand() % _width);
        for (int i = 0, count = 0; i != _width && count != rand; i++) {
            x = std::rand() % _width;
            for (; _map[j][x] != ' '; x = std::rand() % _width);
            if ((_map[j][x - 1] != '1' && _map[j][x - 1] != '2') && (_map[j][x + 1] != '1' && _map[j][x + 1] != '2') && (_map[j - 1][x] != '1' && _map[j - 1][x] != '2') && (_map[j + 1][x] != '1' && _map[j + 1][x] != '2')) {
                _map[j][x] = 'o';
                count++;
            }
        }
    }
}

bool MapGenerator::createAndFillFileMap(const std::string &name)
{
    std::ofstream file;
    if (name.empty())
        file.open(_path + "map/map.txt", std::ofstream::out);
    else
        file.open(_path + "map/" + name, std::ofstream::out);
    //file.open("map.txt");
    if (file.bad())
        return false;
    for (size_t i = 0; i != _map.size(); i++)
        file << _map[i] << std::endl;
    int rand = std::rand();
    file << std::to_string(rand) << std::endl;
    file.close();
    return true;
}
