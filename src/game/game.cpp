#include "game.hpp"

Game::Game(GameState *newGameState, InputQueue *newEventQueue, bool *updatingptr){
    updating = updatingptr;
    gameState = newGameState;
    eventQueue = newEventQueue;
};

int Game::getHorizontalDistanceFromObstacle(int obstaclePosition){
    return abs((PLAYER_OFFSET_Y + (PLAYER_WIDTH / 2)) - (obstaclePosition - (OBSTACLE_WIDTH / 2)));
}

bool Game::checkIfDead() {
    bool isDead = false;
    for (int obstacleIndex = 0; obstacleIndex < gameState->obstacles.count; obstacleIndex++){
        int obstaclePosition = gameState->obstacles.positions[obstacleIndex];
        int horizontalDistanceFromObstacle = getHorizontalDistanceFromObstacle(obstaclePosition);
        if(horizontalDistanceFromObstacle < 5){
            if(gameState->playerPosition < OBSTACLE_HEIGHT){
                return true;
            }
        }else if(horizontalDistanceFromObstacle < 10)
        {
            if(gameState->playerPosition < (10 - horizontalDistanceFromObstacle) * 4){
                return true;
            }
        }
    }
    return false;
};

void Game::generateObstacle() {
    bool shoudGenerate = gameState->obstacles.count == 0 || (gameState->obstacles.count < 2 && gameState->obstacles.positions[0] < SCREEN_WIDTH / 2);
    if(shoudGenerate){
        bool createObstacle = rand() % 25 == 0;
        if(createObstacle){
            gameState->obstacles.positions[gameState->obstacles.count] = SCREEN_WIDTH + OBSTACLE_WIDTH;
            gameState->obstacles.count++;
        }
    }
};
void Game::shiftObstaclePositions() {
    int new_positions[MAX_OBSTACLE_COUNT];
    int new_obstacle_count = 0;
    for (int obstacleIndex = 0; obstacleIndex < gameState->obstacles.count; obstacleIndex++){
        if(gameState->obstacles.positions[obstacleIndex] > 0){
            new_positions[new_obstacle_count] = gameState->obstacles.positions[obstacleIndex] - 1;
            new_obstacle_count++;
        }
    }
    gameState->obstacles.count = new_obstacle_count;
    for (int positionIndex = 0; positionIndex < new_obstacle_count; positionIndex++){
        gameState->obstacles.positions[positionIndex] = new_positions[positionIndex];
    }
};

void Game::updateMotion(){
    if(gameState->playerPosition <= PLAYER_OFFSET_Y 
    && gameState->motion == PlayerMotion::FALLINGD
    ){
        gameState->motion = PlayerMotion::STATIONARY;
    }
    if(gameState->playerPosition >= JUMP_HEIGHT){
        gameState->motion = PlayerMotion::FALLINGD;
    }
    if(eventQueue->getEventCount() > 0){
        auto event = eventQueue->popEvent();
        if(event.input == InputType::UP && gameState->motion == PlayerMotion::STATIONARY){
            gameState->motion = PlayerMotion::JUMPING;
        }
    }
}

void Game::updatePosition() {
    if(gameState->motion == PlayerMotion::JUMPING && gameState->playerPosition + JUMP_SPEED <= JUMP_HEIGHT + PLAYER_OFFSET_Y
    ){
        gameState->playerPosition = gameState->playerPosition + JUMP_SPEED;
    }
    if(gameState->motion == PlayerMotion::FALLINGD && gameState->playerPosition - JUMP_SPEED >= PLAYER_OFFSET_Y
    ){
        gameState->playerPosition = gameState->playerPosition - JUMP_SPEED;
    }
};

void Game::updateAnimCounter(){
    gameState->animCounter++;
    if(gameState->animCounter >= SCREEN_WIDTH + OBSTACLE_WIDTH * 2) {
        gameState->animCounter = 0;
    }else{
        gameState->animCounter++;
    }
}

void Game::increaseScore() {
    // gameState->score++;
};

void Game::initGameState(){    
    gameState->dead = false;
    gameState->motion = PlayerMotion::STATIONARY;
    gameState->obstacles.count = 0;
    gameState->playerPosition = PLAYER_OFFSET_Y;
    gameState->score = 0;
    for (int i; i < MAX_OBSTACLE_COUNT; i++){
        gameState->obstacles.positions[i] = -1;
    } 
}

int Game::runCoroutine(){
    COROUTINE_LOOP(){
        COROUTINE_AWAIT(eventQueue->getLocked() == false);
        *updating = true;
        updateAnimCounter();
        eventQueue->lock();
        updateMotion();
        eventQueue->unlock();
        updatePosition();
        shiftObstaclePositions();
        generateObstacle();
        gameState->dead = checkIfDead();
        *updating = false;
        COROUTINE_DELAY(UPDATE_DELAY);
    }
};