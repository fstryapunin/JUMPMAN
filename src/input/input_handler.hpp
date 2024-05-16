#pragma once
#include <AceRoutine.h>
#include <Arduino.h>
#include "input_queue.hpp"

using namespace ace_routine;

class InputHandler : public Coroutine {
    private:
        int up_button_pin;
        uint8_t up_button_counter;
        InputQueue *queue;
        bool readButton(int pin);
    public:
        InputHandler(int up_button_pin, InputQueue *queue);
        int runCoroutine() override;
};
