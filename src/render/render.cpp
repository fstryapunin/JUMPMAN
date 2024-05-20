#include "render.hpp"

Render::Render(Adafruit_SSD1306 *displayd, GameState *gameStated, InputQueue *queued, bool *newIsGameStateUpdating){
    isGameStateUpdating = newIsGameStateUpdating;
    display = displayd;
    gameState = gameStated;
    queue = queued;
};

void Render::displayDebug(){
    GFXcanvas1 canvas(SCREEN_WIDTH, SCREEN_HEIGHT);
    canvas.fillScreen(BLACK);
    canvas.print("Motion: ");
    canvas.println(gameState->motion);
    canvas.print("Pos Y: ");
    canvas.println(gameState->playerPosition);
    canvas.print("Events: ");
    canvas.println(queue->getEventCount());
    canvas.print("Preview input: ");
    canvas.println(queue->previewEvent(0).input);
    display->drawBitmap(0, 0, canvas.getBuffer(), canvas.width(), canvas.height(), WHITE, BLACK);
    display->display();
}

void Render::renderPlayer(){

}

int Render::runCoroutine(){
    COROUTINE_LOOP(){
        displayDebug();
        COROUTINE_DELAY(FRAME_DELAY_MS);
    }
};