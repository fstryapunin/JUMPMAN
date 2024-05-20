#include "render.hpp"

Render::Render(Adafruit_SSD1306 *displayd, GameState *gameStated, InputQueue *queued, bool *newIsGameStateUpdating): frame(SCREEN_WIDTH, SCREEN_HEIGHT){
    isGameStateUpdating = newIsGameStateUpdating;
    display = displayd;
    gameState = gameStated;
    queue = queued;
};

void Render::displayDebug(){
    frame.print("Motion: ");
    frame.println(gameState->motion);
    frame.print("Pos Y: ");
    frame.println(gameState->playerPosition);
    frame.print("Events: ");
    frame.println(queue->getEventCount());
    frame.print("Preview input: ");
    frame.println(queue->previewEvent(0).input);
    frame.print("Updating :");
    frame.println(*isGameStateUpdating);
}


int Render::runCoroutine(){
    COROUTINE_LOOP(){
        frame.setCursor(0, 0);
        frame.fillScreen(BLACK);
        COROUTINE_AWAIT(*isGameStateUpdating == false);
        
        display->drawBitmap(0, 0, frame.getBuffer(), frame.width(), frame.height(), WHITE, BLACK);
        display->display();
        COROUTINE_DELAY(FRAME_DELAY_MS);
    }
};