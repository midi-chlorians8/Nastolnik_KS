#pragma once
#include <Arduino.h>
//#include "DebounceUpDown.h"
//#include "DebounceLeftRight.h"

#include "Menu.h"

#define StartWorkTimePin 2
//#define StopWorkTime 13



enum SensorButtonState{
    NoClicked,
    DoubleClicked,
    Clicked,
    LongClicked,
    SuperLongClick
};

class CapacityButton
{
    // Вход в меню с двойного нажатия
    bool OneRazMLayerMin1;                  // Один раз замерять текущее время
    unsigned long FirstZamerMLayerMin1_Val; // Замеряет время нажатия кнопок правого и левого поворотников. Для входа в главное меню
    // Вход в меню с двойного нажатия

    // Пакет  для сенсорной кнопки
    const int16_t CLICK_TIME = 45; // 20 ms. // 35
    const int16_t LONGCLICK_TIME = 500;
    const int16_t SUPERLONGCLICK = 2000;

    uint32_t TimePress = 522;//379; // Cюда копируется миллис при срабатывании. 37 Чтобы при старте не считалось что клавиша нажата
    bool OneRazTouch;         // Один раз начать замер времени нажатия
    bool IsBeLongTouch = false;
    bool IsBeLongTouch2 = false;

    SensorButtonState SensorState = NoClicked;

        // Обработка кнопки двойное нажатие
        int counter=1;
        int result = 0;
        //bool firstZamer=false;
        //bool secondZamer=false;
        unsigned long doubleClickTimeOne=0;
        unsigned long doubleClickTimeTwo=0;
        // Обработка кнопки двойное нажатие
    // Пакет  для сенсорной кнопки
bool oneRazTimePressSet;
public:
    CapacityButton();

    CapacityButton &IsPressed(Menu &menu,Timer &timer);

    SensorButtonState GetSensorButtonState(){
        return SensorState;
    }
    /*
    void SetStatePressed(){
        SensorState = Clicked;
    }
    */
    void Print(Menu &menu, bool Endl);

};