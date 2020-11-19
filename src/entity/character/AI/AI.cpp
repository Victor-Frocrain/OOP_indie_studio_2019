/*
** EPITECH PROJECT, 2020
** AI
** File description:
** for indieStudio
*/

#include "AI.hpp"
#include "../../AEntity.hpp"
#include "../../bomb/Bomb.hpp"
#include "../player/Player.hpp"
#include "../../../scenes/Game.hpp"
#include <iostream>
#include "../../../utils/IndieStudio.hpp"

int AI::_mapAI[15][15];

unsigned int AI::_lastNbBomb = 42;

AI::AI(const IEntity::EntityType &type, entityMap &entityMap,
       const irr::core::vector3df &pos, const IScene::playerType &playerType)
    :ACharacter(type, entityMap, pos, playerType),
     _hadToMove(false),_isAbleToMoveOnBombPos(false), _attackMode(false), _prevPos(0),_nextPosZ(getPos().Z / 10), _nextPosX(getPos().X / 10)
{
    if (Game::getAILevel() == 0) {
        _lvl = EASY;
    } else if (Game::getAILevel() == 1) {
        _lvl = MEDIUM;
    } else {
        _lvl = HARD;
    }
}

bool AI::update(const double &deltaTime) noexcept
{
    int z = IndieStudio::roundPos(getPos()).Z / 10;
    int x = IndieStudio::roundPos(getPos()).X / 10;
    int randLvl = rand() % 100;

    if (_lastNbBomb != _map[BOMB].size())
        updateMap();
    if (z == _nextPosZ && x == _nextPosX && _attackMode && randLvl <= _lvl) {
        _hadToMove = true;
        kill();
        updateMap();
    }
    if (_hadToMove || _prevPos == 0 || isInCenterOfBlock()) {
        if (!isPathClear(z, x) && randLvl <= _lvl) {
            _isAbleToMoveOnBombPos = true;
            _attackMode = false;
            _nextPosX = 42;
            _nextPosX = 42;
            escape(0, z, x);
            getNextPos(z, x);
            _isAbleToMoveOnBombPos = false;
        } else if ((_mapAI[_nextPosZ][_nextPosX] != 0 || (z == _nextPosZ && x == _nextPosX)) && randLvl <= _lvl) {
            _isAbleToMoveOnBombPos = false;
            _attackMode = false;
            _nextPosX = 42;
            _nextPosX = 42;
            progress();
            getNextPos(z, x);
        }
    }
    goToNextPos();
    return ACharacter::update(deltaTime);
}

bool AI::isInCenterOfBlock(void)
{
    int z = getPos().Z;
    int x = getPos().X;

    if (_prevPos == 3 && z < _nextPosZ * 10 + 0.6 * SCREEN_SCALE)
        return true;
    else if (_prevPos == 1 && z > _nextPosZ * 10 - 0.6 * SCREEN_SCALE)
        return true;
    else if (_prevPos == 4 && x < _nextPosX * 10 + 0.6 * SCREEN_SCALE)
        return true;
    else if (_prevPos == 2 && x > _nextPosX * 10 - 0.6 * SCREEN_SCALE)
        return true;
    return false;
}

void AI::updateMap(void)
{
    for (int i = 0; i < 15; i++)
        for (int j = 0; j < 15; j++)
            _mapAI[i][j] = 0;
    for (auto it : _map) {
        switch (it.first) {
        case BREAKABLEWALL:
            for (auto that : it.second) {
                int z = static_cast<int>(that->getPos().Z) / 10;
                int x = static_cast<int>(that->getPos().X) / 10;
                _mapAI[z][x] = 2;
            }
            break;
        case UNBREAKABLEWALL:
            for (auto that : it.second) {
                int z = static_cast<int>(that->getPos().Z) / 10;
                int x = static_cast<int>(that->getPos().X) / 10;
                _mapAI[z][x] = 3;
            }
            break;
        case BOMB:
            for (auto that : it.second) {
                int z = static_cast<int>(that->getPos().Z) / 10;
                int x = static_cast<int>(that->getPos().X) / 10;
                _mapAI[z][x] = 1;
                Bomb *bomb = dynamic_cast<Bomb*>(that);
                if (bomb != NULL)
                    fillBombRange(z, x, bomb->getRange());
            }
            break;
        default:
            break;
        }
    }
    _lastNbBomb = _map[BOMB].size();
}

void AI::fillBombRange(int z, int x, int range)
{
    for (int i = 1; i <= range; i++) {
        if (_mapAI[z + i][x] == 0) {
            _mapAI[z + i][x] = 1;
        } else if (_mapAI[z + i][x] == 2) {
            _mapAI[z + i][x] = 1;
            break;
        } else {
            break;
        }
    }
    for (int i = 1; i <= range; i++) {
        if (_mapAI[z - i][x] == 0) {
            _mapAI[z - i][x] = 1;
        } else if (_mapAI[z - i][x] == 2) {
            _mapAI[z - i][x] = 1;
            break;
        } else {
            break;
        }
    }
    for (int i = 1; i <= range; i++) {
        if (_mapAI[z][x + i] == 0) {
            _mapAI[z][x + i] = 1;
        } else if (_mapAI[z][x + i] == 2) {
            _mapAI[z][x + i] = 1;
            break;
        } else {
            break;
        }
    }
    for (int i = 1; i <= range; i++) {
        if (_mapAI[z][x - i] == 0) {
            _mapAI[z][x - i] = 1;
        } else if (_mapAI[z][x - i] == 2) {
            _mapAI[z][x - i] = 1;
            break;
        } else {
            break;
        }
    }
}

bool AI::isPathClear(int posZ, int posX)
{
    if (posZ < _nextPosZ) {
        for (int nextPos = posZ; nextPos <= _nextPosZ; nextPos++)
            if (_mapAI[nextPos][posX] != 0)
                return false;
    } else if (posZ > _nextPosZ) {
        for (int nextPos = posZ; nextPos >= _nextPosZ; nextPos--)
            if (_mapAI[nextPos][posX] != 0)
                return false;
    } else if (posX < _nextPosX) {
        for (int nextPos = posX; nextPos <= _nextPosX; nextPos++)
            if (_mapAI[posZ][nextPos] != 0)
                return false;
    } else if (posX > _nextPosX) {
        for (int nextPos = posX; nextPos >= _nextPosX; nextPos--)
            if (_mapAI[posZ][nextPos] != 0)
                return false;
    }
    if (_mapAI[posZ][posX] != 0)
        return false;
    return true;
}

void AI::escape(int prevPos, int posZ, int posX)
{
    if (_mapAI[posZ - 1][posX] == 0 && posZ - 1 != posZ) {
        if (isNewDistanceShorter(posZ - 1, posX)) {
            _nextPosZ = posZ - 1;
            _nextPosX = posX;
        }
    } else if ((_mapAI[posZ - 1][posX] == 0 || _mapAI[posZ - 1][posX] == 1) && prevPos != 3) {
        escape(1, posZ - 1, posX);
    }
    if (_mapAI[posZ + 1][posX] == 0 && posZ + 1 != posZ) {
        if (isNewDistanceShorter(posZ + 1, posX)) {
            _nextPosZ = posZ + 1;
            _nextPosX = posX;
        }
    } else if ((_mapAI[posZ + 1][posX] == 0 || _mapAI[posZ + 1][posX] == 1) && prevPos != 1) {
        escape(3, posZ + 1, posX);
    }
    if (_mapAI[posZ][posX - 1] == 0 && posX - 1 != posX) {
        if (isNewDistanceShorter(posZ, posX - 1)) {
            _nextPosZ = posZ;
            _nextPosX = posX - 1;
        }
    } else if ((_mapAI[posZ][posX - 1] == 0 || _mapAI[posZ][posX - 1] == 1) && prevPos != 4) {
        escape(2, posZ, posX - 1);
    }
    if (_mapAI[posZ][posX + 1] == 0 && posX + 1 != posX) {
        if (isNewDistanceShorter(posZ, posX + 1)) {
            _nextPosZ = posZ;
            _nextPosX = posX + 1;
        }
    } else if ((_mapAI[posZ][posX + 1] == 0 || _mapAI[posZ][posX + 1] == 1) && prevPos != 2) {
        escape(4, posZ, posX + 1);
    }
}

void AI::progress(void)
{
    std::vector<IEntity*> characterTab = _map[PLAYER];

    for (auto it : _map[IA])
        if (getPos() != it->getPos())
            characterTab.push_back(it);
    for (auto it : characterTab) {
        if (isNewDistanceShorter(it->getPos().Z / 10, it->getPos().X / 10)) {
            _nextPosZ = it->getPos().Z / 10;
            _nextPosX = it->getPos().X / 10;
        }
    }
}

bool AI::isNewDistanceShorter(int posZ, int posX)
{
    int distance = 0;
    int newDistance = 0;

    if (_nextPosZ < getPos().Z / 10) {
        for (int i = _nextPosZ; i != IndieStudio::roundPos(getPos()).Z / 10; i++) {
            distance++;
            if (distance < 0 || distance > 30)
                break;
        }
    } else {
        for (int i = _nextPosZ; i != IndieStudio::roundPos(getPos()).Z / 10; i--) {
            distance++;
            if (distance < 0 || distance > 30)
                break;
        }
    }
    if (_nextPosX < getPos().X / 10) {
        for (int i = _nextPosX; i != IndieStudio::roundPos(getPos()).X / 10; i++) {
            distance++;
            if (distance < 0 || distance > 30)
                break;
        }
    } else {
        for (int i = _nextPosX; i != IndieStudio::roundPos(getPos()).X / 10; i--) {
            distance++;
            if (distance < 0 || distance > 30)
                break;
        }
    }
    if (posZ < getPos().Z / 10) {
        for (int i = posZ; i != IndieStudio::roundPos(getPos()).Z / 10; i++) {
            newDistance++;
            if (newDistance < 0 || newDistance > 30)
                break;
        }
    } else {
        for (int i = posZ; i != IndieStudio::roundPos(getPos()).Z / 10; i--) {
            newDistance++;
            if (newDistance < 0 || newDistance > 30)
                break;
        }
    }
    if (posX < getPos().X / 10) {
        for (int i = posX; i != IndieStudio::roundPos(getPos()).X / 10; i++) {
            newDistance++;
            if (newDistance < 0 || newDistance > 30)
                break;
        }
    } else {
        for (int i = posX; i != IndieStudio::roundPos(getPos()).X / 10; i--){
            newDistance++;
            if (newDistance < 0 || newDistance > 30)
                break;
        }
    }
    if (newDistance <= distance)
        return true;
    return false;
}

void AI::getNextPos(int posZ, int posX)
{
    int moveRand = rand() % 2;

    if (moveRand == 0) {
        if (posZ < _nextPosZ) {
            if (_mapAI[posZ + 1][posX] == 0 || (_isAbleToMoveOnBombPos && _mapAI[posZ + 1][posX] == 1)) {
                nextPosStep(posZ, posX, true, 1);
            } else if (moveRand == 0) {
                if (_mapAI[posZ][posX + 1] == 0 || (_isAbleToMoveOnBombPos && _mapAI[posZ][posX + 1] == 1))
                    nextPosStep(posZ, posX, false, 1);
                else if (_mapAI[posZ][posX - 1] == 0 || (_isAbleToMoveOnBombPos && _mapAI[posZ][posX - 1] == 1))
                    nextPosStep(posZ, posX, false, -1);
                else if (_mapAI[posZ - 1][posX] == 0 || (_isAbleToMoveOnBombPos && _mapAI[posZ - 1][posX] == 1))
                    nextPosStep(posZ, posX, true, -1);
                else {
                    _nextPosZ = posZ;
                    _nextPosX = posX;
                }
            } else {
                if (_mapAI[posZ][posX - 1] == 0 || (_isAbleToMoveOnBombPos && _mapAI[posZ][posX - 1] == 1))
                    nextPosStep(posZ, posX, false, -1);
                else if (_mapAI[posZ][posX + 1] == 0 || (_isAbleToMoveOnBombPos && _mapAI[posZ][posX + 1] == 1))
                    nextPosStep(posZ, posX, false, 1);
                else if (_mapAI[posZ - 1][posX] == 0 || (_isAbleToMoveOnBombPos && _mapAI[posZ - 1][posX] == 1))
                    nextPosStep(posZ, posX, true, -1);
                else {
                    _nextPosZ = posZ;
                    _nextPosX = posX;
                }
            }
        } else if (posZ > _nextPosZ) {
            if (_mapAI[posZ - 1][posX] == 0 || (_isAbleToMoveOnBombPos && _mapAI[posZ - 1][posX] == 1)) {
                nextPosStep(posZ, posX, true, -1);
            } else if (moveRand == 0) {
                if (_mapAI[posZ][posX + 1] == 0 || (_isAbleToMoveOnBombPos && _mapAI[posZ][posX + 1] == 1))
                    nextPosStep(posZ, posX, false, 1);
                else if (_mapAI[posZ][posX - 1] == 0 || (_isAbleToMoveOnBombPos && _mapAI[posZ][posX - 1] == 1))
                    nextPosStep(posZ, posX, false, -1);
                else if (_mapAI[posZ + 1][posX] == 0 || (_isAbleToMoveOnBombPos && _mapAI[posZ + 1][posX] == 1))
                    nextPosStep(posZ, posX, true, 1);
                else {
                    _nextPosZ = posZ;
                    _nextPosX = posX;
                }
            } else {
                if (_mapAI[posZ][posX - 1] == 0 || (_isAbleToMoveOnBombPos && _mapAI[posZ][posX - 1] == 1))
                    nextPosStep(posZ, posX, false, -1);
                else if (_mapAI[posZ][posX + 1] == 0 || (_isAbleToMoveOnBombPos && _mapAI[posZ][posX + 1] == 1))
                    nextPosStep(posZ, posX, false, 1);
                else if (_mapAI[posZ + 1][posX] == 0 || (_isAbleToMoveOnBombPos && _mapAI[posZ + 1][posX] == 1))
                    nextPosStep(posZ, posX, true, 1);
                else {
                    _nextPosZ = posZ;
                    _nextPosX = posX;
                }
            }
        } else if (posX > _nextPosX) {
            if (_mapAI[posZ][posX - 1] == 0 || (_isAbleToMoveOnBombPos && _mapAI[posZ][posX - 1] == 1)) {
                nextPosStep(posZ, posX, false, -1);
            } else if (moveRand == 0) {
                if (_mapAI[posZ + 1][posX] == 0 || (_isAbleToMoveOnBombPos && _mapAI[posZ + 1][posX] == 1))
                    nextPosStep(posZ, posX, true, 1);
                else if (_mapAI[posZ - 1][posX] == 0 || (_isAbleToMoveOnBombPos && _mapAI[posZ - 1][posX] == 1))
                    nextPosStep(posZ, posX, true, -1);
                else if (_mapAI[posZ][posX + 1] == 0 || (_isAbleToMoveOnBombPos && _mapAI[posZ][posX + 1] == 1))
                    nextPosStep(posZ, posX, false, 1);
                else {
                    _nextPosZ = posZ;
                    _nextPosX = posX;
                }
            } else {
                if (_mapAI[posZ - 1][posX] == 0 || (_isAbleToMoveOnBombPos && _mapAI[posZ - 1][posX] == 1))
                    nextPosStep(posZ, posX, true, -1);
                else if (_mapAI[posZ + 1][posX] == 0 || (_isAbleToMoveOnBombPos && _mapAI[posZ + 1][posX] == 1))
                    nextPosStep(posZ, posX, true, 1);
                else if (_mapAI[posZ][posX + 1] == 0 || (_isAbleToMoveOnBombPos && _mapAI[posZ][posX + 1] == 1))
                    nextPosStep(posZ, posX, false, 1);
                else {
                    _nextPosZ = posZ;
                    _nextPosX = posX;
                }
            }
        } else if (posX < _nextPosX) {
            if (_mapAI[posZ][posX + 1] == 0 || (_isAbleToMoveOnBombPos && _mapAI[posZ][posX + 1] == 1)) {
                nextPosStep(posZ, posX, false, 1);
            } else if (moveRand == 0) {
                if (_mapAI[posZ - 1][posX] == 0 || (_isAbleToMoveOnBombPos && _mapAI[posZ - 1][posX] == 1))
                    nextPosStep(posZ, posX, true, -1);
                else if (_mapAI[posZ + 1][posX] == 0 || (_isAbleToMoveOnBombPos && _mapAI[posZ + 1][posX] == 1))
                    nextPosStep(posZ, posX, true, 1);
                else if (_mapAI[posZ][posX - 1] == 0 || (_isAbleToMoveOnBombPos && _mapAI[posZ][posX - 1] == 1))
                    nextPosStep(posZ, posX, false, -1);
                else {
                    _nextPosZ = posZ;
                    _nextPosX = posX;
                }
            } else {
                if (_mapAI[posZ + 1][posX] == 0 || (_isAbleToMoveOnBombPos && _mapAI[posZ + 1][posX] == 1))
                    nextPosStep(posZ, posX, true, 1);
                else if (_mapAI[posZ - 1][posX] == 0 || (_isAbleToMoveOnBombPos && _mapAI[posZ - 1][posX] == 1))
                    nextPosStep(posZ, posX, true, -1);
                else if (_mapAI[posZ][posX - 1] == 0 || (_isAbleToMoveOnBombPos && _mapAI[posZ][posX - 1] == 1))
                    nextPosStep(posZ, posX, false, -1);
                else {
                    _nextPosZ = posZ;
                    _nextPosX = posX;
                }
            }
        }
    } else {
        if (posX > _nextPosX) {
            if (_mapAI[posZ][posX - 1] == 0 || (_isAbleToMoveOnBombPos && _mapAI[posZ][posX - 1] == 1)) {
                nextPosStep(posZ, posX, false, -1);
            } else if (moveRand == 0) {
                if (_mapAI[posZ + 1][posX] == 0 || (_isAbleToMoveOnBombPos && _mapAI[posZ + 1][posX] == 1))
                    nextPosStep(posZ, posX, true, 1);
                else if (_mapAI[posZ - 1][posX] == 0 || (_isAbleToMoveOnBombPos && _mapAI[posZ - 1][posX] == 1))
                    nextPosStep(posZ, posX, true, -1);
                else if (_mapAI[posZ][posX + 1] == 0 || (_isAbleToMoveOnBombPos && _mapAI[posZ][posX + 1] == 1))
                    nextPosStep(posZ, posX, false, 1);
                else {
                    _nextPosZ = posZ;
                    _nextPosX = posX;
                }
            } else {
                if (_mapAI[posZ - 1][posX] == 0 || (_isAbleToMoveOnBombPos && _mapAI[posZ - 1][posX] == 1))
                    nextPosStep(posZ, posX, true, -1);
                else if (_mapAI[posZ + 1][posX] == 0 || (_isAbleToMoveOnBombPos && _mapAI[posZ + 1][posX] == 1))
                    nextPosStep(posZ, posX, true, 1);
                else if (_mapAI[posZ][posX + 1] == 0 || (_isAbleToMoveOnBombPos && _mapAI[posZ][posX + 1] == 1))
                    nextPosStep(posZ, posX, false, 1);
                else {
                    _nextPosZ = posZ;
                    _nextPosX = posX;
                }
            }
        } else if (posX < _nextPosX) {
            if (_mapAI[posZ][posX + 1] == 0 || (_isAbleToMoveOnBombPos && _mapAI[posZ][posX + 1] == 1)) {
                nextPosStep(posZ, posX, false, 1);
            } else if (moveRand == 0) {
                if (_mapAI[posZ - 1][posX] == 0 || (_isAbleToMoveOnBombPos && _mapAI[posZ - 1][posX] == 1))
                    nextPosStep(posZ, posX, true, -1);
                else if (_mapAI[posZ + 1][posX] == 0 || (_isAbleToMoveOnBombPos && _mapAI[posZ + 1][posX] == 1))
                    nextPosStep(posZ, posX, true, 1);
                else if (_mapAI[posZ][posX - 1] == 0 || (_isAbleToMoveOnBombPos && _mapAI[posZ][posX - 1] == 1))
                    nextPosStep(posZ, posX, false, -1);
                else {
                    _nextPosZ = posZ;
                    _nextPosX = posX;
                }
            } else {
                if (_mapAI[posZ + 1][posX] == 0 || (_isAbleToMoveOnBombPos && _mapAI[posZ + 1][posX] == 1))
                    nextPosStep(posZ, posX, true, 1);
                else if (_mapAI[posZ - 1][posX] == 0 || (_isAbleToMoveOnBombPos && _mapAI[posZ - 1][posX] == 1))
                    nextPosStep(posZ, posX, true, -1);
                else if (_mapAI[posZ][posX - 1] == 0 || (_isAbleToMoveOnBombPos && _mapAI[posZ][posX - 1] == 1))
                    nextPosStep(posZ, posX, false, -1);
                else {
                    _nextPosZ = posZ;
                    _nextPosX = posX;
                }
            }
        } else if (posZ < _nextPosZ) {
            if (_mapAI[posZ + 1][posX] == 0 || (_isAbleToMoveOnBombPos && _mapAI[posZ + 1][posX] == 1)) {
                nextPosStep(posZ, posX, true, 1);
            } else if (moveRand == 0) {
                if (_mapAI[posZ][posX + 1] == 0 || (_isAbleToMoveOnBombPos && _mapAI[posZ][posX + 1] == 1))
                    nextPosStep(posZ, posX, false, 1);
                else if (_mapAI[posZ][posX - 1] == 0 || (_isAbleToMoveOnBombPos && _mapAI[posZ][posX - 1] == 1))
                    nextPosStep(posZ, posX, false, -1);
                else if (_mapAI[posZ - 1][posX] == 0 || (_isAbleToMoveOnBombPos && _mapAI[posZ - 1][posX] == 1))
                    nextPosStep(posZ, posX, true, -1);
                else {
                    _nextPosZ = posZ;
                    _nextPosX = posX;
                }
            } else {
                if (_mapAI[posZ][posX - 1] == 0 || (_isAbleToMoveOnBombPos && _mapAI[posZ][posX - 1] == 1))
                    nextPosStep(posZ, posX, false, -1);
                else if (_mapAI[posZ][posX + 1] == 0 || (_isAbleToMoveOnBombPos && _mapAI[posZ][posX + 1] == 1))
                    nextPosStep(posZ, posX, false, 1);
                else if (_mapAI[posZ - 1][posX] == 0 || (_isAbleToMoveOnBombPos && _mapAI[posZ - 1][posX] == 1))
                    nextPosStep(posZ, posX, true, -1);
                else {
                    _nextPosZ = posZ;
                    _nextPosX = posX;
                }
            }
        } else if (posZ > _nextPosZ) {
            if (_mapAI[posZ - 1][posX] == 0 || (_isAbleToMoveOnBombPos && _mapAI[posZ - 1][posX] == 1)) {
                nextPosStep(posZ, posX, true, -1);
            } else if (moveRand == 0) {
                if (_mapAI[posZ][posX + 1] == 0 || (_isAbleToMoveOnBombPos && _mapAI[posZ][posX + 1] == 1))
                    nextPosStep(posZ, posX, false, 1);
                else if (_mapAI[posZ][posX - 1] == 0 || (_isAbleToMoveOnBombPos && _mapAI[posZ][posX - 1] == 1))
                    nextPosStep(posZ, posX, false, -1);
                else if (_mapAI[posZ + 1][posX] == 0 || (_isAbleToMoveOnBombPos && _mapAI[posZ + 1][posX] == 1))
                    nextPosStep(posZ, posX, true, 1);
                else {
                    _nextPosZ = posZ;
                    _nextPosX = posX;
                }
            } else {
                if (_mapAI[posZ][posX - 1] == 0 || (_isAbleToMoveOnBombPos && _mapAI[posZ][posX - 1] == 1))
                    nextPosStep(posZ, posX, false, -1);
                else if (_mapAI[posZ][posX + 1] == 0 || (_isAbleToMoveOnBombPos && _mapAI[posZ][posX + 1] == 1))
                    nextPosStep(posZ, posX, false, 1);
                else if (_mapAI[posZ + 1][posX] == 0 || (_isAbleToMoveOnBombPos && _mapAI[posZ + 1][posX] == 1))
                    nextPosStep(posZ, posX, true, 1);
                else {
                    _nextPosZ = posZ;
                    _nextPosX = posX;
                }
            }
        }
    }
}

void AI::nextPosStep(int posZ, int posX, bool isAxeZ, int incr)
{
    int nextPos;

    if (isAxeZ) {
        if (incr > 0)
            for (nextPos = posZ; nextPos < _nextPosZ && (_mapAI[nextPos + 1][posX] == 0 || (_isAbleToMoveOnBombPos && _mapAI[nextPos + 1][posX] == 1)); nextPos++) {
                if (_mapAI[nextPos + 1][posX] == 0) {
                    _isAbleToMoveOnBombPos = false;
                }
            }
        else
            for (nextPos = posZ; nextPos > _nextPosZ && (_mapAI[nextPos - 1][posX] == 0 || (_isAbleToMoveOnBombPos && _mapAI[nextPos - 1][posX] == 1)); nextPos--) {
                if (_mapAI[nextPos - 1][posX] == 0) {
                    _isAbleToMoveOnBombPos = false;
                }
            }
        if (hadToDropBomb(nextPos, posX))
            _attackMode = true;
        _nextPosZ = nextPos;
        _nextPosX = posX;
    } else {
        if (incr > 0)
            for (nextPos = posX; nextPos < _nextPosX && (_mapAI[posZ][nextPos + 1] == 0 || (_isAbleToMoveOnBombPos && _mapAI[posZ][nextPos + 1] == 1)); nextPos++) {
                if (_mapAI[posZ][nextPos + 1] == 0) {
                    _isAbleToMoveOnBombPos = false;
                }
            }
        else
            for (nextPos = posX; nextPos > _nextPosX && (_mapAI[posZ][nextPos - 1] == 0 || (_isAbleToMoveOnBombPos && _mapAI[posZ][nextPos - 1] == 1)); nextPos--) {
                if (_mapAI[posZ][nextPos - 1] == 0) {
                    _isAbleToMoveOnBombPos = false;
                }
            }
        if (hadToDropBomb(posZ, nextPos))
            _attackMode = true;
        _nextPosZ = posZ;
        _nextPosX = nextPos;
    }
}

bool AI::hadToDropBomb(int posZ, int posX)
{
    int enemyPosZ = 42;
    int enemyPosX = 42;
    int distanceRange = 42;
    std::vector<IEntity*> characterTab = _map[PLAYER];

    for (auto it : _map[IA])
        if (getPos() != it->getPos())
            characterTab.push_back(it);
    for (auto it : characterTab) {
        if (isNewDistanceShorter(it->getPos().Z / 10, it->getPos().X / 10)) {
            enemyPosZ = it->getPos().Z / 10;
            enemyPosX = it->getPos().X / 10;
        }
    }
    if (posZ == enemyPosZ || posX == enemyPosX) {
        distanceRange = 0;
        if (enemyPosZ < posZ)
            for (int i = enemyPosZ; i != posZ; i++)
                distanceRange++;
        else if (enemyPosZ > posZ)
            for (int i = enemyPosZ; i != posZ; i--)
                distanceRange++;
        else if (enemyPosX < posX)
            for (int i = enemyPosX; i != posX; i++)
                distanceRange++;
        else if (enemyPosX > posX)
            for (int i = enemyPosX; i != posX; i--)
                distanceRange++;
    }
    if ((_nextPosZ > posZ && (_mapAI[posZ + 1][posX] == 2 || distanceRange - getPowerUp().getRange() <= 0)) || (_nextPosZ < posZ && (_mapAI[posZ - 1][posX] == 2 || distanceRange - getPowerUp().getRange() <= 0)) || (_nextPosX > posX && (_mapAI[posZ][posX + 1] == 2 || distanceRange - getPowerUp().getRange() <= 0)) || (_nextPosX < posX && (_mapAI[posZ][posX - 1] == 2 || distanceRange - getPowerUp().getRange() <= 0)))
        return true;
    return false;
}

void AI::goToNextPos(void)
{
    int z = getPos().Z;
    int x = getPos().X;

    if (z < _nextPosZ * 10 - 1) {
        _prevPos = 3;
        ACharacter::front();
    } else if (z > _nextPosZ * 10 + 1) {
        _prevPos = 1;
        ACharacter::back();
    }
    if (x < _nextPosX * 10 - 1) {
        _prevPos = 4;
        ACharacter::right();
    } else if (x > _nextPosX * 10 + 1) {
        _prevPos = 2;
        ACharacter::left();
    }
}

void AI::kill(void)
{
    ACharacter::dropBomb();
}

std::string AI::ToLog() const noexcept
{
    return "Ia(" + ACharacter::ToLog() + ", IaController(" + std::to_string(getPlayerType()) + ")";
}
