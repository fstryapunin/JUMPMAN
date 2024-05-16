#pragma once
#include <AceRoutine.h>
#include "input_queue.hpp"

using namespace ace_routine;

#define UPDATE_DELAY 100
#define JUMP_HEIGHT 40
#define GROUND_HEIGHT 3

#define PLAYER_HEIGHT 20
#define PLAYER_WIDTH 10

#define PLAYER_OFFSET_X 10
#define PLAYER_OFFSET_Y 4

#define OBSTACLE_WIDTH 10


enum PlayerMotion
{
    JUMPING = 1,
    FALLINGD = 2,
    STATIONARY = 3
};

struct Obstacles {
    int count;
    int positions[2];
};

struct GameState {
    PlayerMotion motion;
    int playerPosition;
    Obstacles obstacles;
    int score;
    bool dead;
};

class Game : public Coroutine {
    private:
        GameState *gameState;
        InputQueue *eventQueue;
        int generateObstacle();
        bool checkIfDead();
        void updateMotion();
        void updatePosition();
        void increaseScore();
        void shiftObstaclePositions();
    public:
        Game(GameState *gameState, InputQueue *eventQueue);
        int runCoroutine() override;
};