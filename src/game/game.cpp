#include "game.hpp"

Game::Game(GameState *newGameState, InputQueue *newEventQueue){
    gameState = newGameState;
    eventQueue = newEventQueue;
};

bool Game::checkIfDead() {};

int Game::generateObstacle() {};

void Game::updateMotion(){
    if(eventQueue->getEventCount() > 0){
        auto event = eventQueue->popEvent();
        if(event.input == InputType::UP && gameState->motion == PlayerMotion::STATIONARY){
            gameState->motion = PlayerMotion::JUMPING;
        }
    }
    if(gameState->playerPosition == PLAYER_OFFSET_Y && gameState->playerPosition == PlayerMotion::FALLINGD){
        gameState->motion = PlayerMotion::STATIONARY;
    }
    if(gameState->playerPosition >= PLAYER_OFFSET_Y + JUMP_HEIGHT){
        gameState->motion = PlayerMotion::FALLINGD;
    }
}

void Game::updatePosition() {
    if(gameState->motion == PlayerMotion::JUMPING && gameState->playerPosition + JUMP_SPEED <= JUMP_HEIGHT + PLAYER_OFFSET_Y){
        gameState->playerPosition = gameState->playerPosition + JUMP_SPEED;
    }
    if(gameState->motion == PlayerMotion::FALLINGD && gameState->playerPosition - JUMP_SPEED >= PLAYER_OFFSET_Y){
        gameState->playerPosition = gameState->playerPosition - JUMP_SPEED;
    }
};

void Game::increaseScore() {
    // gameState->score++;
};

void Game::shiftObstaclePositions() {};

int Game::runCoroutine(){
    COROUTINE_LOOP(){
        updateMotion();
        updatePosition();
        COROUTINE_DELAY(UPDATE_DELAY);
    }
};