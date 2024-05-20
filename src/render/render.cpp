#include "render.hpp"

Render::Render(Adafruit_SSD1306 *displayd, GameState *gameStated, InputQueue *queued, bool *newIsGameStateUpdating){
    isGameStateUpdating = newIsGameStateUpdating;
    display = displayd;
    gameState = gameStated;
    queue = queued;
};

void Render::displayDebug(GFXcanvas1 *frame){
    frame->fillScreen(BLACK);
    frame->print("Motion: ");
    frame->println(gameState->motion);
    frame->print("Pos Y: ");
    frame->println(gameState->playerPosition);
    frame->print("Events: ");
    frame->println(queue->getEventCount());
    frame->print("Preview input: ");
    frame->println(queue->previewEvent(0).input);
    frame->print("Updating :");
    frame->println(*isGameStateUpdating);
    display->drawBitmap(0, 0, frame->getBuffer(), frame->width(), frame->height(), WHITE, BLACK);
    display->display();
}

void Render::renderPlayer(GFXcanvas1 *frame){

}

int Render::runCoroutine(){
    COROUTINE_LOOP(){
        COROUTINE_AWAIT(*isGameStateUpdating == false);
        GFXcanvas1 frame(SCREEN_WIDTH, SCREEN_HEIGHT);
        displayDebug(&frame);
        COROUTINE_DELAY(FRAME_DELAY_MS);
    }
};