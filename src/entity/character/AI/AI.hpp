/*
** EPITECH PROJECT, 2020
** AI
** File description:
** for indieStudio
*/

#ifndef AI_HPP
#define AI_HPP

#include "../ACharacter.hpp"
#include "../../AEntity.hpp"
#include "../../../scenes/IScene.hpp"

#define EASY 40
#define MEDIUM 60
#define HARD 90

class AI : public ACharacter {
public:
    AI(const IEntity::EntityType &type, entityMap &entityMap,
       const irr::core::vector3df &pos, const IScene::playerType &playerType);
    ~AI() = default;

    bool update(const double &deltaTime) noexcept final;

private:
    bool isInCenterOfBlock(void);
    void updateMap(void);
    void fillBombRange(int z, int x, int range);
    bool isPathClear(int posZ, int posX);
    void escape(int prevPos, int posZ, int posX);
    void progress(void);
    void getNewPos(int posZ, int posX);
    bool isNewDistanceShorter(int posZ, int posX);
    void getNextPos(int posZ, int posX);
    void nextPosStep(int posZ, int posX, bool isAxeZ, int incr);
    bool hadToDropBomb(int posZ, int posX);
    void goToNextPos(void);
    void kill(void);
    std::string ToLog() const noexcept;

private:
    bool _hadToMove;
    bool _isAbleToMoveOnBombPos;
    bool _attackMode;
    int _prevPos;
    int _nextPosZ;
    int _nextPosX;
    int _lvl;
    static int _mapAI[15][15];
    static unsigned int _lastNbBomb;
};

#endif /* !AI_HPP */
