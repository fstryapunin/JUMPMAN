#pragma once

#include "global.hpp"

#define MAX_EVENTS 4

struct InputEvent {
    InputType input;
};

class InputQueue
{
    private:
        InputEvent events[4];
        int event_count;
        bool locked;
        int read_index;
        int write_index;
    public:
        InputQueue(InputEvent events[4]);
        void pushEvent(InputEvent event);
        InputEvent popEvent();
        InputEvent previewEvent(int index);
        int getEventCount();
        void lock();
        void unlock();
        bool getLocked();
};