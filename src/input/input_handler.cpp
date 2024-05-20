#include "input_handler.hpp"
#define FILTER_TIME 10
#define SAMPLE_PERIOD 1

InputHandler::InputHandler(int up_button_pin, InputQueue *queue_ptr) {
    up_button_pin = up_button_pin;
    up_button_counter = 0;
    queue = queue_ptr;
} 

bool InputHandler::readButton(int pin){
    return digitalRead(pin) == 0;
}

int InputHandler::runCoroutine(){
    COROUTINE_LOOP() {
        auto read_value = readButton(up_button_pin);
        if(read_value){
            up_button_counter++;
        } else {
            up_button_counter = 0;
        }
        if(up_button_counter >= FILTER_TIME){
            up_button_counter = 0;
            COROUTINE_AWAIT(queue->getLocked() == false);
            queue->lock();
            queue->pushEvent(InputType::UP);
            queue->unlock();
            COROUTINE_AWAIT(!readButton(up_button_pin));
        }
        COROUTINE_DELAY(SAMPLE_PERIOD);
    }
}