#pragma once

#include "global.hpp"

#define MAX_EVENTS 4

struct InputEvent {
    InputType input;
};

class InputQueue
{
    private:
        InputEvent *events;
        int event_count;
        bool locked;
        int read_index;
        int write_index;
    public:
        InputQueue(InputEvent (&eventsd)[4]);
        void pushEvent(InputType type);
        InputEvent popEvent();
        InputEvent previewEvent(int index);
        int getEventCount();
        void lock();
        void unlock();
        bool getLocked();
};