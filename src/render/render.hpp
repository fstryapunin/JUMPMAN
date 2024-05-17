#pragma once
#include <AceRoutine.h>
#include <Arduino.h>
#include <SPI.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiSpi.h"
#include "../src/game/game.hpp"
#include "../src/input/input_queue.hpp"

#define FRAME_DELAY_MS 50
using namespace ace_routine;

class Render : public Coroutine {
    private:
        SSD1306AsciiSpi *display;
        GameState *gameState;
        InputQueue *queue;
        void displayDebug();
    public:
        Render(SSD1306AsciiSpi *display, GameState *gameState, InputQueue *queue);
        int runCoroutine() override;
};