#include "game.hpp"

Game::Game(GameState *newGameState, InputQueue *newEventQueue, bool *updatingptr){
    updating = updatingptr;
    gameState = newGameState;
    eventQueue = newEventQueue;
};

bool Game::checkIfDead() {};

void Game::generateObstacle() {
    bool shoudGenerate = gameState->obstacles.count == 0 || (gameState->obstacles.count < 2 && gameState->obstacles.positions[0] < SCREEN_WIDTH / 2);
    if(shoudGenerate){
        // bool createObstacle = rand() % 2 == 0;
        // if(createObstacle){
            gameState->obstacles.positions[1] = SCREEN_WIDTH + OBSTACLE_WIDTH;
        // }
    }
};
void Game::shiftObstaclePositions() {
    int new_indexes[MAX_OBSTACLE_COUNT];
    int new_obstacle_count = 0;
    for (int obstacleIndex; obstacleIndex < gameState->obstacles.count; obstacleIndex++){
        if(gameState->obstacles.positions[obstacleIndex] <= 0 - OBSTACLE_WIDTH){
            new_indexes[obstacleIndex] = -1;
        } else {
            new_indexes[new_obstacle_count] = gameState->obstacles.positions[obstacleIndex] - 1;
            new_obstacle_count++;
        }
    }
    gameState->obstacles.count = new_obstacle_count;
    for (int positionIndex = 0; positionIndex < new_obstacle_count; positionIndex++){
        gameState->obstacles.positions[positionIndex] = new_indexes[positionIndex];
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
    if(gameState->animCounter >= 128) {
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
        *updating = false;
        COROUTINE_DELAY(UPDATE_DELAY);
    }
};