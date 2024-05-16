#include "input_queue.hpp"

InputQueue::InputQueue(InputEvent *events){
    events = events;
    event_count = 0;
}
void InputQueue::pushEvent(InputEvent event){
    if(event_count < 4){
        events[event_count] = event;
        event_count++;
    }
}

int InputQueue::getEventCount(){
    return event_count;
}

InputEvent InputQueue::popEvent(){
    auto event = events[event_count - 1];
    event_count--;
    return event;
}