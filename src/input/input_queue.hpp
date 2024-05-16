#pragma once

enum InputType
{
    UP = 1,
};

struct InputEvent {
    InputType input;
};

class InputQueue
{
    private:
        InputEvent *events;
        int event_count;
    public:
        InputQueue(InputEvent *events);
        void pushEvent(InputEvent event);
        InputEvent popEvent();
        int getEventCount();
};