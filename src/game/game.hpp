#pragma once
#include <AceRoutine.h>
#include "../src/input/input_queue.hpp"

using namespace ace_routine;

#define MAX_OBSTACLE_COUNT 2

#define UPDATE_DELAY 10
#define JUMP_HEIGHT 40
#define GROUND_HEIGHT 3

#define PLAYER_HEIGHT 20
#define PLAYER_WIDTH 10

#define PLAYER_OFFSET_X 10
#define PLAYER_OFFSET_Y 4

#define OBSTACLE_HEIGHT 20
#define OBSTACLE_WIDTH 10


enum PlayerMotion
{
    JUMPING = 1,
    FALLINGD = 2,
    STATIONARY = 3
};

struct Obstacles {
    int count;
    int positions[MAX_OBSTACLE_COUNT];
};

struct GameState {
    PlayerMotion motion;
    int playerPosition;
    Obstacles obstacles;
    int animCounter;
    int score;
    bool dead;
};

class Game : public Coroutine {
    private:
        GameState *gameState;
        InputQueue *eventQueue;
        bool *updating;
        void generateObstacle();
        bool checkIfDead();
        void updateMotion();
        void updatePosition();
        void updateAnimCounter();
        void updateScore(int prevObstacles);
        void shiftObstaclePositions();
        int getHorizontalDistanceFromObstacle(int obstaclePosition);
    public:
        Game(GameState *gameState, InputQueue *eventQueue, bool *updating);
        int runCoroutine() override;
        void initGameState();
};