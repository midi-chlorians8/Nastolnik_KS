#pragma once
#include "Arduino.h"
//#include "Timer.h"
extern bool impuls;

struct Restruct{
    bool GoChillPisk = false;
    bool GoWorkPisk = false;
};
enum Kommands{
    Nop,
    PererivHour,
    StopPererivHour,
    DangerCo2Level
};
 
class Timer;

class Sound{
private:
    bool State; // On - Off
   
    // Для писка
    unsigned long timingWork;
    bool OneRazSetTimeToPickWork = false;
    int stepWork=0;
    
    
    bool OneRazSetTimeToPickChill = false;
    unsigned long timingChill;
    int stepChill=0;
    // Для писка
    
    // Демо писк из меню
    bool oneRazZamerTime = false;
    unsigned long demoPiskTiming;
    // Демо писк из меню
    const int soundPin = 33;
public:
Restruct Tesak;
    enum States
    {
        OFF,
        ON
    };


    Kommands MySoundKommand = Nop;
    
    Sound(){
        pinMode(soundPin,OUTPUT);
    }
    void SetState(States s);
    States GetState();

    void BeepReset(){
        Tesak.GoChillPisk = false;
        OneRazSetTimeToPickWork = false;
        stepWork =0;

        Tesak.GoWorkPisk = false;
        OneRazSetTimeToPickChill = false;
        stepChill =0;    
    }

    void StepWorkToNull(){
        timingWork = millis();
        stepWork =0;
        //Serial.println("I am in StepWorkToNull()");
    }
    void BeepLogic(){
        if(GetState() == ON){ // Если из меню включили буззер
            if(Tesak.GoChillPisk == true){
                    // Общая идея такова - идёт осчёт рабочего времени при нажатии сенс кнопки.
                    // В меню можно включить и отключить режим защита глаз - писк по заданному интервалу времени
                    //Serial.println("GoChillPisk");
                    // Тут идёт обработка звука о превышении времени [Перерыв для глаз]
                    
                    // Присваиваем один раз текущее время
                    if(OneRazSetTimeToPickWork == false){ 
                        timingWork = millis();
                        stepWork =0;
                        //Serial.println("stepWork = 0 VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV");
                        OneRazSetTimeToPickWork = true;
                    }
                    // Присваиваем один раз текущее время

                        // Пик - пик
                        if ( (millis() - timingWork > 500) and stepWork ==0){ // Вместо 10000 подставьте нужное вам значение паузы 
                            digitalWrite(soundPin,HIGH);   
                            stepWork =1;
                            Serial.println("stepWork = 1");
                            timingWork = millis(); 
                        }
                        if ( (millis() - timingWork > 500) and stepWork ==1){ // Вместо 10000 подставьте нужное вам значение паузы 
                            digitalWrite(soundPin,LOW);   
                            stepWork =2;
                            timingWork = millis(); 
                        }
                        if ( (millis() - timingWork > 500) and stepWork ==2){ // Вместо 10000 подставьте нужное вам значение паузы 
                            digitalWrite(soundPin,HIGH);   
                            stepWork =3;
                            timingWork = millis(); 
                        }
                        if ( (millis() - timingWork > 500) and stepWork ==3){ // Вместо 10000 подставьте нужное вам значение паузы 
                            digitalWrite(soundPin,LOW);   
                            stepWork =4;
                            timingWork = millis();  
                        }
                        // Пик - пик

                        // Пик - пик - пик
                        if ( (millis() - timingWork > 9000) and stepWork ==4){ // Вместо 10000 подставьте нужное вам значение паузы 
                            digitalWrite(soundPin,HIGH);   
                            stepWork =5;
                            timingWork = millis(); 
                        }
                        if ( (millis() - timingWork > 500) and stepWork ==5){ // Вместо 10000 подставьте нужное вам значение паузы 
                            digitalWrite(soundPin,LOW);   
                            stepWork =6;
                            timingWork = millis(); 
                        }
                        if ( (millis() - timingWork > 500) and stepWork ==6){ // Вместо 10000 подставьте нужное вам значение паузы 
                            digitalWrite(soundPin,HIGH);   
                            stepWork =7;
                            timingWork = millis(); 
                        }
                        if ( (millis() - timingWork > 500) and stepWork ==7){ // Вместо 10000 подставьте нужное вам значение паузы 
                            digitalWrite(soundPin,LOW);   
                            stepWork =8;
                            timingWork = millis(); 
                        }
                        if ( (millis() - timingWork > 500) and stepWork ==8){ // Вместо 10000 подставьте нужное вам значение паузы 
                            digitalWrite(soundPin,HIGH);   
                            stepWork =9;
                            timingWork = millis(); 
                        }
                        if ( (millis() - timingWork > 500) and stepWork ==9){ // Вместо 10000 подставьте нужное вам значение паузы 
                            digitalWrite(soundPin,LOW);   
                            stepWork =10;
                            timingWork = millis(); 
                        
                        }
                        // Пик - пик - пик

                        // Пиииик
                        if ( (millis() - timingWork > 7000) and stepWork ==10){ // Вместо 10000 подставьте нужное вам значение паузы 
                            digitalWrite(soundPin,HIGH);   
                            stepWork =11;
                            timingWork = millis(); 
                        
                        }
   
                        if ( (millis() - timingWork > 2000) and stepWork ==11){ // Вместо 10000 подставьте нужное вам значение паузы 
                        digitalWrite(soundPin,LOW);   
                        stepWork =12;
                        timingWork = millis(); 
                        Tesak.GoChillPisk = false;
                        OneRazSetTimeToPickWork = false; //Перезаряд шага 0
                        stepWork =0;
                        // Было так! MySoundKommand=Nop; //Прекатить писк.
                    }
                        // Пиииик
                }

            if(Tesak.GoWorkPisk==true){
               // Присваиваем один раз текущее время
                if(OneRazSetTimeToPickChill == false){ 
                    timingChill = millis();
                    stepChill =0;
                    Serial.println("stepChill = 0");
                    OneRazSetTimeToPickChill = true;
                }
                // Присваиваем один раз текущее время
                  if ( (millis() - timingChill > 500) and stepChill == 0){ // Вместо 10000 подставьте нужное вам значение паузы 
                        digitalWrite(soundPin,HIGH);   
                        stepChill =1;
                        Serial.println("stepChill = 1");
                        timingChill = millis(); 
                    }
                   if ( (millis() - timingChill > 2500) and stepChill ==1){ // Вместо 10000 подставьте нужное вам значение паузы 
                        digitalWrite(soundPin,LOW);   
                        //stepWork =0;
                        //Serial.println("stepChill = 0");
                        stepChill =3;
                        timingChill = millis(); 
                        Tesak.GoWorkPisk=false;
                        OneRazSetTimeToPickChill = false; //Перезаряд шага 0
                        MySoundKommand=Nop; //Прекатить писк.

                    }
        }
        }
    }
    
    void ReceiveKommand(){
         if(MySoundKommand==PererivHour){
                Serial.println("I receive command Beep beep beep(StartChill)");
                Tesak.GoChillPisk = true;
                Tesak.GoWorkPisk=false;
            MySoundKommand=Nop; //Прекатить писк.
         }
         if(MySoundKommand==StopPererivHour){
                Serial.println("I receive command Stop Chill");
                Tesak.GoChillPisk = false;
                Tesak.GoWorkPisk=true;
            MySoundKommand=Nop;
         }
    }
    void DemoSignalFromMenu(States s){
        if(s == ON){
            // Один раз замерять время
            if(oneRazZamerTime == false){
                demoPiskTiming = millis();
                oneRazZamerTime = true;
            }
            if(millis()-demoPiskTiming<500){
                digitalWrite(soundPin,HIGH);
            }
            else{
                digitalWrite(soundPin,LOW);
            }
        }
        else{
            oneRazZamerTime = false;
            digitalWrite(soundPin,LOW);
        }
    }
    void Print(){

          if(impuls ==true){
         
            
            Serial.print(" Tesak.GoChillPisk:");Serial.print(Tesak.GoChillPisk);
            Serial.print(" OneRazSetTimeToPickWork:");Serial.print(OneRazSetTimeToPickWork);
            Serial.print(" stepWork:");Serial.print(stepWork);
            Serial.print(" stepChill:");Serial.print(stepChill);
            Serial.print(" MySoundKommand:");Serial.print(MySoundKommand);
            
            Serial.println(); 
            impuls =false;
          // }
        /*
        if(Tesak.GoChillPisk == true){
            Serial.print("GoChillPisk:");Serial.println(Tesak.GoChillPisk);
        }
        */
        /*
        if(abc==1){
            Serial.println("abc 1");
        }
        */
          }
    }

};