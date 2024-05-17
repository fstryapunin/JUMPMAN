#include "input_queue.hpp"

InputQueue::InputQueue(InputEvent events[4]){
    events = events;
    event_count = 0;
    read_index = 0;
    write_index = 0;
    locked = false;
}
void InputQueue::pushEvent(InputEvent event){
    if(event_count < 4){
        events[write_index] = event;
        write_index++;
        if(write_index > MAX_EVENTS - 1){
            write_index = 0;
        }
        event_count++;
    }
}

int InputQueue::getEventCount(){
    return event_count;
}

InputEvent InputQueue::previewEvent(int index){
 return events[index];
}

InputEvent InputQueue::popEvent(){
    auto event = events[read_index];
    read_index++;
    if(read_index > MAX_EVENTS - 1){
        read_index = 0;
    }
    event_count--;
    return event;
}

void InputQueue::lock(){
    locked = true;
}

void InputQueue::unlock(){
    locked = false;
}

bool InputQueue::getLocked(){
    return locked;
}