#include "render.hpp"

const unsigned char jumpmanHappySprite [] PROGMEM = { 0x7f, 0x80, 0x80, 0x40, 0x80, 0x40, 0x92, 0x40, 0x80, 0x40, 0x80, 0x40, 0x92, 0x40, 0x8c, 0x40, 
0x80, 0x40, 0x7f, 0x80 };

const unsigned char jumpmanSadSprite [] PROGMEM = {
	0x7f, 0x80, 0x80, 0x40, 0xa1, 0x40, 0x92, 0x40, 0xa1, 0x40, 0x80, 0x40, 0x9e, 0x40, 0x92, 0x40, 
	0x80, 0x40, 0x7f, 0x80
};


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
    frame.println(queue->previewEvent(0).input == InputType::UP ? "yes" : "no");
    frame.print("Updating :");
    frame.println(*isGameStateUpdating);
    frame.print("Obstacles: ");
    frame.println(gameState->obstacles.count);
    for (int i = 0; i < gameState->obstacles.count; i++){
        frame.println(gameState->obstacles.positions[i]);
    }
    frame.print("Anim: ");
    frame.print(gameState->animCounter);
}

void Render::renderCrumb(int index){
    int crumbIndex = SCREEN_WIDTH - gameState->animCounter - index;
    frame.drawPixel(crumbIndex, GROUND_LEVEL - 1, WHITE);
    frame.drawPixel(crumbIndex + 1, GROUND_LEVEL - 1, WHITE);
    frame.drawPixel(crumbIndex - 1, GROUND_LEVEL - 1, WHITE);
}

void Render::renderGround(){
    frame.drawFastHLine(0, GROUND_LEVEL, SCREEN_WIDTH, WHITE);
    frame.drawFastHLine(0, GROUND_LEVEL + 1, SCREEN_WIDTH, WHITE);
}

void Render::renderPlayer(bool happy){
    frame.drawBitmap(PLAYER_OFFSET_X, SCREEN_HEIGHT - PLAYER_HEIGHT/2 - gameState->playerPosition, happy ? jumpmanHappySprite : jumpmanSadSprite, PLAYER_WIDTH, PLAYER_HEIGHT / 2, WHITE);
}

void Render::renderGameOver(){
    frame.setCursor(5, 20);
    frame.setTextSize(2);
    frame.println("GAME OVER!");
}

void Render::renderObstacles(){
    for (int obstaleIndex = 0; obstaleIndex < gameState->obstacles.count; obstaleIndex++){
        int position = gameState->obstacles.positions[obstaleIndex];
        frame.drawTriangle(
            position - OBSTACLE_WIDTH, GROUND_LEVEL, 
            position - (OBSTACLE_WIDTH/2), GROUND_LEVEL - OBSTACLE_HEIGHT, 
            position, GROUND_LEVEL, 
        WHITE);
    }
}

int Render::runCoroutine(){
    COROUTINE_LOOP(){
        frame.setCursor(0, 0);
        frame.fillScreen(BLACK);
        COROUTINE_AWAIT(*isGameStateUpdating == false);
        // displayDebug();
        renderGround();
        // renderCrumb(0);
        renderObstacles();
        renderPlayer(!(gameState->dead));
        if(gameState->dead){
            renderGameOver();
        }
        display->drawBitmap(0, 0, frame.getBuffer(), frame.width(), frame.height(), WHITE, BLACK);
        display->display();
        COROUTINE_DELAY(FRAME_DELAY_MS);
    }
};