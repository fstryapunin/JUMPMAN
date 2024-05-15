#include <Arduino.h>
#include <SPI.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiSpi.h"
#include <AceRoutine.h>
using namespace ace_routine;

// pin definitions
#define CS_PIN  PA4
#define RST_PIN PB0
#define DC_PIN  PA8 //BEWARE - CHANGE with respect to KEILstudio code
SSD1306AsciiSpi oled;
const int up_input_pin = PA10;
// HardwareSerial Serial2(PA_3_ALT1, PA_2_ALT1); // UART2 TX RX

int global;

class HelloWorld: public Coroutine {
  private:
    int *tst;
  public:
    HelloWorld(int *global){
      tst = global;
    }
    int runCoroutine() override {
      
      COROUTINE_LOOP() {
        COROUTINE_DELAY(500);
        oled.clear();
        oled.print(*tst);
      }
    }
};

HelloWorld hl  = HelloWorld(&global);

void setup() {
  // put your setup code here, to run once:
  int a = digitalRead(PA10);
  pinMode(up_input_pin, INPUT_PULLUP);
  // Serial2.begin(115200); 
  Serial.begin(115200); 
  analogReadResolution(12);
  oled.begin(&Adafruit128x64, CS_PIN, DC_PIN, RST_PIN);
  oled.setFont(Adafruit5x7);  
  oled.clear();
}

void loop() {
  // put your main code here, to run repeatedly:
  // delay(100);
  // int a = digitalRead(up_input_pin);
  // oled.clear();  
  // oled.print(a + 5);
  delay(2000);
  global++;
  hl.runCoroutine();
}

