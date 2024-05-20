#include <Arduino.h>
#include <SPI.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "SSD1306Ascii.h"
#include "SSD1306AsciiSpi.h"
#include "../src/input/input_handler.hpp" 
#include "../src/input/input_queue.hpp"
#include "../src/game/game.hpp"
#include "../src/render/render.hpp"
#include "global.hpp"

using namespace ace_routine;

// pin definitions
#define CS_PIN  PA4
#define RST_PIN PB0
#define DC_PIN  PA8 //BEWARE - CHANGE with respect to KEILstudio code
const auto up_input_pin = PA10;

SSD1306AsciiSpi oled;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
  &SPI, DC_PIN, RST_PIN, CS_PIN);

bool isGameStateUpdating = false;
InputEvent events[4] = {};
InputQueue queue = InputQueue(events);
Screen screen;
GameState gameState;

InputHandler inputHandler = InputHandler(up_input_pin, &queue);
Game game = Game(&gameState, &queue, &isGameStateUpdating);
Render render = Render(&display, &gameState, &queue, &isGameStateUpdating);

void setup() {
  // put your setup code here, to run once:
  pinMode(up_input_pin, INPUT_PULLUP);

  // Initializing display alone doesnt work, idk why.
  oled.begin(&Adafruit128x64, CS_PIN, DC_PIN, RST_PIN);
  display.setFont();
  display.setTextSize(1);
  display.begin(SSD1306_SWITCHCAPVCC, true, true);
  game.initGameState();
  display.clearDisplay();
  display.display();
}


void loop() {
  inputHandler.runCoroutine();
  game.runCoroutine();
  render.runCoroutine();
}

