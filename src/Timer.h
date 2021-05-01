#pragma once

#include "CapacityButtons.h"
#include "Sound.h"
#include "EEPROMUtil.h"

extern bool impuls;
extern bool waitOneMinGlobal;

//extern  SemaphoreHandle_t xSerialSemaphore;
// Click - старт
// LongClick - пауза
// SuperLongClick - cброс. ****Возможно когда прикрутятся часы то можно в EEPROM начинать записывать итоги дня. (Если небыло сброса, то после 23.59 прописать результат общего раб времени в меню) А затем пролистать их в меню

// Описание работы таймера замеряющего рабочее время. При нажатии Click тамер начинает отсчёт с нуля. 
//                          При нажатии LongClick - пауза. Это подсчёт рабочего времени. 
//                          При нажатии SuperLongClick - cброс по нулям.

struct T_time{
       int sec = 0; 
       int min = 0;
       int hour = 0;
       int AverageMin = 0; // Всё время прошедшее в минутах

       int8_t output_sec= 0;    // То что идёт на дисплей
       int8_t output_min = 0;   // То что идёт на дисплей
       int8_t output_hour = 0;  // То что идёт на дисплей
};
/*
enum StateWorkOrChill{
    No,
    Work,
    Chill
};
*/
class Timer{
private:
    unsigned long timing; // Для подсчёта времени таймером

    bool SafeEyesMode = false; // Режим который при пуске отсчёта рабочего времени - каждый "час" вводит перерыв на "10мин"
    uint8_t SEWorkTime;  // Настраеваемый "час"
    uint8_t SEChillTime; // Настраеваемый "10мин"
    bool ChangeLightFromSE = false; // Во время перерыва менять ли цвет подсветки 

    bool OneRazSendBeepKommand = false; // 
    //bool OneRazCopSEWorkTime = false; 
    int MySEWorkTime=999;
    bool OneRazPlusMySEWorkTime = false;
    bool PriStateImetSostWork = false; // Чтобь в пункте 4 меню при первом нажатии отсчёт таймера сразу появилось Work
    
    bool letsBeginOtvhet = false;
    bool waitOneMin=false;

    bool freezUntilBreak = false; // Не считать время во время перерыва
    bool showContinue = false; // Показать надпись continue после выхода с перерыва. И не продолжать считать время если небыло нажатия.
public:
    StateWorkOrChill WhatDoingNow;
    bool OneRazCopSEWorkTime = false; 
    T_time TimerTime;
    
    void CountTime(CapacityButton b,Sound &sound) //Cчитаю время с нажатия кнопки
        {
            if (b.GetSensorButtonState() == Clicked){
                letsBeginOtvhet = true;
            }
            if (b.GetSensorButtonState() == DoubleClicked){
                letsBeginOtvhet = false;
            }

            if(letsBeginOtvhet == true){
               waitOneMin = waitOneMinGlobal; 
                    if (millis() - timing > 1000){ // Вместо 10000 подставьте нужное вам значение паузы 
                        if(showContinue == false){
                            TimerTime.sec+=1;  writeByteIntoEEPROM(21, TimerTime.sec);
                            timing = millis(); 

                            impuls =true;
                            // Перевод в минуты и часы
                            if (TimerTime.sec>59){
                                TimerTime.sec = 0;
                                TimerTime.min +=1;      writeByteIntoEEPROM(19, TimerTime.min);
                                TimerTime.AverageMin +=1; // Пользуемся этим в таймере save eyes
                                if (TimerTime.min>59){ //Cпециально вложил чтоб меньше проверок было за цикл. Быстрее работало
                                    TimerTime.min = 0;
                                    TimerTime.hour +=1; writeByteIntoEEPROM(20, TimerTime.hour);
                                }
                            }
                            // Перевод в минуты и часы
                            //Serial.print(TimerTime.hour);Serial.print(":");Serial.print(TimerTime.min); Serial.print(":");Serial.print(TimerTime.sec); Serial.println();
                            if(freezUntilBreak == false){ //Если сейчас не перерыв то считать секунды
                                TimerTime.output_sec = TimerTime.sec;
                                TimerTime.output_min = TimerTime.min;
                                TimerTime.output_hour = TimerTime.hour;
                            }  
                        }
                    }
                    // Один раз скопировать заданное кол-во рабочих меню из переменной в меню при нажатии кнопки старт таймер
                    if(OneRazCopSEWorkTime == false){
                        MySEWorkTime = SEWorkTime; 
                        if (PriStateImetSostWork == false){
                            WhatDoingNow = Work; 
                            PriStateImetSostWork = true;
                        }
                        OneRazCopSEWorkTime = true;
                    }
                    // Один раз скопировать заданное кол-во рабочих меню из переменной в меню при нажатии кнопки старт таймер
            }

            if(b.GetSensorButtonState() == LongClicked and WhatDoingNow == Chill and waitOneMin == false){ // При продлении на 1мин рабочего времени
                TimerTime.AverageMin+=1;
                waitOneMin = true;
                waitOneMinGlobal = waitOneMin;
                sound.StepWorkToNull(); //Перезарядить 3 пика на начало 
            }
            // }
            if(b.GetSensorButtonState() == SuperLongClick){
                SbrosTimer();
            }
         
            if(impuls ==true){
                //Serial.print(" b.GetSensorButtonState(): ");Serial.print(b.GetSensorButtonState()); 
            }
            /*
            if(b.GetSensorButtonState() == LongClicked and WhatDoingNow == Work){
                //TimerTime.AverageMin+=1;
                b.SetStatePressed();
            }
            */
    }
    T_time GetTimerTime() const {    //Отдаю время кто попоросит
        return TimerTime;
    }
    StateWorkOrChill GetWhatDoingNow(){
        return WhatDoingNow;
    }
// Геттеры - сеттеры для пункта в меню save eyes
    // SafeEyesMode
    void SetSafeEyesMode(States s){//Вкл-Выкл режим спаси глаза
        if (s == ON){
            SafeEyesMode =true;
        }
        else{
            SafeEyesMode =false;
        }
    }
    States GetSafeEyesMode() const{      //Говорю включени или нет режим
        if (SafeEyesMode ==true){
            return ON;
        }
        else{
            return OFF;
        }
    }
    // SafeEyesMode

    // Work Time
    void SetSEWorkTime(uint8_t min){
        if(min<256){
            SEWorkTime = min;
        }
    }
    uint8_t GetSEWorkTime() const {
        return SEWorkTime;
    }
    // Work Time

    // Chill Time
    void SetSEChillTime(uint8_t min){
        if(min<256){
            SEChillTime = min;
        }
    }
    uint8_t GetSEChillTime() const{
        return SEChillTime;
    }
    // Chill Time

    // Цвет подсветки меняется во время перерыва для глаз
    void SetChangeLightFromSEMode(States s){//!Вкл-Выкл режим спаси глаза
        if (s == ON){
            ChangeLightFromSE =true;
        }
        else{
            ChangeLightFromSE =false;
        }
    }
    States GetChangeLightFromSEMode() const {      //!Говорю включени или нет режим
        if (ChangeLightFromSE ==true){
            return ON;
        }
        else{
            return OFF;
        }
    }
    // Цвет подсветки меняется во время перерыва для глаз
// Геттеры - сеттеры для пункта в меню save eyes
    void NotifyPereriv(Sound& s){
      //  /*
        if(MySEWorkTime==TimerTime.AverageMin  ){ //Момент начала перерыва

            //Serial.println("Work Time end");

            if(OneRazSendBeepKommand == false){ // Послать один раз команду попищать
                    s.MySoundKommand = PererivHour;
                    WhatDoingNow = Chill;
                    OneRazPlusMySEWorkTime = false; // Перезаряд
                    freezUntilBreak = true; // Остановить отсчёт времени
                OneRazSendBeepKommand = true;   // Послать один раз команду попищать
                
            }
            OneRazPlusMySEWorkTime = false;
        } 
        if(MySEWorkTime+SEChillTime <= TimerTime.AverageMin){ //Момент конца перерыва
           
            // Один раз увеличить свою переменную рабочего времени += величина раб времени из меню
            if(OneRazPlusMySEWorkTime == false){
                    MySEWorkTime+=SEWorkTime+SEChillTime;

                    s.MySoundKommand = StopPererivHour;
                    WhatDoingNow = Work;
                    OneRazSendBeepKommand=false;
                    freezUntilBreak = false; // Продолжить отсчёт времени

                    TimerTime.sec = TimerTime.output_sec;
                    TimerTime.min = TimerTime.output_min;
                    TimerTime.hour = TimerTime.output_hour;

                    showContinue = true;

                OneRazPlusMySEWorkTime = true;
            }
            // Один раз увеличить свою переменную рабочего времени += величина раб времени из меню
        }

    }
    bool GetIsShowContinue(){
        if(showContinue == true){
            return true;
        }
        else{
            return false;
        }
    }
    void SetShowContinue(bool en){
        if(en == true){
            showContinue = true;
        }
        else{
            showContinue = false;
        }
    }
 
    void SbrosTimer(){
                TimerTime.sec=0;
                TimerTime.min=0;  writeByteIntoEEPROM(19, TimerTime.min);
                TimerTime.hour=0; writeByteIntoEEPROM(20, TimerTime.hour);
                WhatDoingNow = No;
                OneRazCopSEWorkTime = false; // Перезаряд // Один раз скопировать заданное кол-во рабочих меню из переменной в меню при нажатии кнопки старт таймер
                PriStateImetSostWork = false;
                OneRazSendBeepKommand = false;
                TimerTime.AverageMin=0;
        }

    void Print(){
      
        if(impuls ==true){
            //if ( xSemaphoreTake( xSerialSemaphore, ( TickType_t ) 5 ) == pdTRUE )
           // {
                Serial.print("SEWorkTime: ");Serial.print(SEWorkTime); 
                Serial.print(" MySEWorkTime: ");Serial.print(MySEWorkTime); 
                Serial.print(" SEChillTime: ");Serial.print(SEChillTime); 
                Serial.print(" TimerTime.AverageMin: ");Serial.print(TimerTime.AverageMin);Serial.print(" ");
                Serial.print(TimerTime.hour);Serial.print(":");
                Serial.print(TimerTime.min); Serial.print(":");
                Serial.print(TimerTime.sec); Serial.print(" ");

                Serial.print(" OneRazPlusMySEWorkTime: ");Serial.print(OneRazPlusMySEWorkTime); 
                
                Serial.print(" timer.GetWhatDoingNow()");
                Serial.print(GetWhatDoingNow() );

                Serial.println();
               // xSemaphoreGive( xSerialSemaphore );
           // }
            
            /*
            Serial.print(" OneRazPlusMySEWorkTime: ");Serial.print(OneRazPlusMySEWorkTime);
            */
            impuls = false;
           
        }
    }


    void SetReadedEEPROMTime(byte min,byte hour, byte sec){
        TimerTime.min = min;
        TimerTime.hour = hour;
        TimerTime.sec = sec;
    }

};