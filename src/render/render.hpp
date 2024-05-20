#pragma once
#include <AceRoutine.h>
#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#include "../src/game/game.hpp"
#include "../src/input/input_queue.hpp"
#include "global.hpp"

#define FRAME_DELAY_MS 50
#define GROUND_LEVEL 3
using namespace ace_routine;

class Render : public Coroutine {
    private:
        Adafruit_SSD1306 *display;
        GameState *gameState;
        InputQueue *queue;
        bool *isGameStateUpdating;
        void displayDebug(GFXcanvas1 *frame);
        void renderPlayer(GFXcanvas1 *frame);
        void renderGround(GFXcanvas1 *frame);
    public:
        Render(Adafruit_SSD1306 *display, GameState *gameState, InputQueue *queue, bool *isGameStateUpdating);
        int runCoroutine() override;
};