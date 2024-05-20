#include "game.hpp"

Game::Game(GameState *newGameState, InputQueue *newEventQueue, bool *updatingptr){
    updating = updatingptr;
    gameState = newGameState;
    eventQueue = newEventQueue;
};

bool Game::checkIfDead() {};

int Game::generateObstacle() {};
void Game::shiftObstaclePositions() {};

void Game::updateMotion(){

    if(gameState->playerPosition <= PLAYER_OFFSET_Y 
    // && gameState->playerPosition == PlayerMotion::FALLINGD
    ){
        gameState->motion = PlayerMotion::STATIONARY;
    }
    if(gameState->playerPosition >= JUMP_HEIGHT){
        gameState->motion = PlayerMotion::FALLINGD;
    }
    if(eventQueue->getEventCount() > 0){
        auto event = eventQueue->popEvent();
        if(
         // TODO workaround fix later   
        // event.input == InputType::UP 
        gameState->motion == PlayerMotion::STATIONARY){
            gameState->motion = PlayerMotion::JUMPING;
        }
    }
}

void Game::updatePosition() {
    if(gameState->motion == PlayerMotion::JUMPING 
    && gameState->playerPosition + JUMP_SPEED <= JUMP_HEIGHT + PLAYER_OFFSET_Y
    ){
        gameState->playerPosition = gameState->playerPosition + JUMP_SPEED;
    }
    if(gameState->motion == PlayerMotion::FALLINGD 
    && gameState->playerPosition - JUMP_SPEED >= PLAYER_OFFSET_Y
    ){
        gameState->playerPosition = gameState->playerPosition - JUMP_SPEED;
    }
};

void Game::increaseScore() {
    // gameState->score++;
};

void Game::initGameState(){    
    gameState->dead = false;
    gameState->motion = PlayerMotion::STATIONARY;
    gameState->obstacles.count = 0;
    gameState->playerPosition = PLAYER_OFFSET_Y;
    gameState->score = 0;
}

int Game::runCoroutine(){
    COROUTINE_LOOP(){
        COROUTINE_AWAIT(eventQueue->getLocked() == false);
        eventQueue->lock();
        updateMotion();
        eventQueue->unlock();
        updatePosition();
        COROUTINE_DELAY(UPDATE_DELAY);
    }
};