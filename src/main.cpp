#include <Arduino.h>
#include <SPI.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiSpi.h"
#include "../src/input/input_handler.hpp" 
#include "../src/input/input_queue.hpp"
using namespace ace_routine;

// pin definitions
#define CS_PIN  PA4
#define RST_PIN PB0
#define DC_PIN  PA8 //BEWARE - CHANGE with respect to KEILstudio code
SSD1306AsciiSpi oled;
const auto up_input_pin = PA10;
// HardwareSerial Serial2(PA_3_ALT1, PA_2_ALT1); // UART2 TX RX

InputEvent events[4] = {};
InputQueue queue = InputQueue(events);
InputHandler inputHandler = InputHandler(up_input_pin, &queue);

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
  oled.print("Hello");
}

void loop() {
  // put your main code here, to run repeatedly:
  // delay(100);
  // int a = digitalRead(up_input_pin);
  inputHandler.runCoroutine();
  auto a = queue.getEventCount();
  oled.clear();
  oled.print(a);
  oled.print(digitalRead(PA10));
  delay(500);
}

