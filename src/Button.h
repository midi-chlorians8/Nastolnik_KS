#pragma once
#include <Arduino.h>

enum class ButtonState
{
    NotPressed = 0,
    Pressed = 1
};

enum class ButtonEvent
{
    None,
    Clicked,
    Hold
};

class Button
{
    public:
        //Button() = default;
        Button(int8_t pin, unsigned long debounce_threshold = 8);
        void Update();
        unsigned long GetStateDuration();
        ButtonState GetState();
        ButtonEvent GetEvent();

    private:
        int8_t pin;
   
        ButtonState state;
        unsigned long state_change_time;

        ButtonEvent event;

        unsigned long debounce_threshold;
        ButtonState debounce_state;
        unsigned long debounce_state_change_time;
};