#include <Button.h>

Button::Button(int8_t pin, unsigned long debounce_threshold) : pin(pin), state(ButtonState::NotPressed), event(ButtonEvent::None),
                                                               debounce_threshold(debounce_threshold), debounce_state(ButtonState::NotPressed)
{
    pinMode(pin, INPUT_PULLDOWN);
    state_change_time = debounce_state_change_time = millis();
    Serial.println("BUTTON CONSTRUCTED");
}

void Button::Update()
{

    event = ButtonEvent::None;
    unsigned long last_state_duration = millis() - state_change_time;

    ButtonState current_state = static_cast<ButtonState>(digitalRead(pin));

    if (current_state != debounce_state)
    {
        debounce_state_change_time = millis();
        debounce_state = current_state;
    }

    if (millis() - debounce_state_change_time > debounce_threshold)
    {
        if (state != current_state)
        {
            if (current_state == ButtonState::NotPressed && last_state_duration < 300)
            {
                event = ButtonEvent::Clicked;
            }

            state = current_state;
            state_change_time = millis();
        }
    }
    
    last_state_duration = millis() - state_change_time;
    if(state == ButtonState::Pressed && last_state_duration > 300)
        event = ButtonEvent::Hold;
    
}

unsigned long Button::GetStateDuration()
{
    return millis() - state_change_time;
}

ButtonState Button::GetState()
{
    return state;
}

ButtonEvent Button::GetEvent()
{
    return event;
}
