#include "render.hpp"

Render::Render(SSD1306AsciiSpi *displayd, GameState *gameStated, InputQueue *queued){
    display = displayd;
    gameState = gameStated;
    queue = queued;
};

void Render::displayDebug(){
    display->clear();
    display->print("Motion: ");
    display->println(gameState->motion);
    display->print("Pos Y: ");
    display->println(gameState->playerPosition);
    display->print("Events:");
    display->println(queue->getEventCount());
    display->print("Preview input: ");
    display->println(queue->previewEvent(0).input);
}

int Render::runCoroutine(){
    COROUTINE_LOOP(){
        displayDebug();
        COROUTINE_DELAY(FRAME_DELAY_MS);
    }
};