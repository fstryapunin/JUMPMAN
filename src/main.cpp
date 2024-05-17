#include <Arduino.h>
#include <SPI.h>
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

// HardwareSerial Serial2(PA_3_ALT1, PA_2_ALT1); // UART2 TX RX

SSD1306AsciiSpi oled;
InputEvent events[4] = {};
InputQueue queue = InputQueue(events);
Screen screen;
GameState gameState;

InputHandler inputHandler = InputHandler(up_input_pin, &queue);
Game game = Game(&gameState, &queue);
Render render = Render(&oled, &gameState, &queue);

void setup() {
  // put your setup code here, to run once:
  // int a = digitalRead(PA10);
  pinMode(up_input_pin, INPUT_PULLUP);
  // // Serial2.begin(115200); 
  Serial.begin(115200); 
  // analogReadResolution(12);
  oled.begin(&Adafruit128x64, CS_PIN, DC_PIN, RST_PIN);
  oled.setFont(Adafruit5x7);
  oled.clear();
  game.initGameState();
}


void loop() {

  inputHandler.runCoroutine();
  game.runCoroutine();
  render.runCoroutine();
  // oled.clear();
  // oled.print("Pos ");
  // oled.println(gameState.playerPosition);
  // oled.print("motion ");
  // oled.println(gameState.motion);
  // oled.print("Events ");
  // oled.print(queue.getEventCount());
  // delay(1);
}

