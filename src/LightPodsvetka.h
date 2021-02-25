#pragma once
// Ws2812
#include <NeoPixelBus.h>
#include <NeoPixelBrightnessBus.h> // instead of NeoPixelBus.h

const uint16_t PixelCount = 3; // make sure to set this to the number of pixels in your strip
const uint8_t PixelPin = 16;   // make sure to set this to the correct pin, ignored for Esp8266

const RgbColor red(255, 0, 0);
const RgbColor yellow(255, 255, 0);
const RgbColor green(0, 128, 0);
const RgbColor Purple(139,0,255);
const RgbColor off(0, 0, 0);
// Ws2812

#include "Menu.h"
//#include "Timer.h"
//class Timer;


enum color
{
  RED,
  GREEN,
  YELLOW
};
enum States
{
  OFF,
  ON
};
enum LightSmoothly
{
  NoSmoothly,
  Smoothly
};
enum StateWorkOrChill{ //! А не закинуть ли тут и в таймире в прайват
    No,
    Work,
    Chill
};


class LightPodsvetka
{
private:
  bool OnLight = true; // Включено или выключено// В настройках можно включить - выключить подсветку
  bool OnSmoothly =false;// Плавный свет Медленно пульсирующий
  bool IsNowChangeLightFromSE = false;
  color NowColor;
  NeoPixelBrightnessBus<NeoGrbFeature, Neo800KbpsMethod> strip;

   
  void StaticLights(RgbColor c){
     strip.SetBrightness(128);
      for(int i=0; i<PixelCount; i++){
          strip.SetPixelColor(i, c);
      }
      strip.Show(); 
  }

  unsigned long timing; // Для скорости дыхания подсветки
  int BrigtnessIterator = 128;
  bool Kacheli = false; // Дыхание подсветки

  bool demoLight = false; // Чтоб показать цвет подстветки при перерыве из меню
    void DynamicLights(RgbColor c){
      
      for(int i=0; i<PixelCount; i++){ strip.SetPixelColor(i, c);    }
          
      if (millis() - timing > 25){ // Вместо 10000 подставьте нужное вам значение паузы 
          strip.SetBrightness(BrigtnessIterator);//strip.Show();

          if(BrigtnessIterator >7 and Kacheli == false){ 
            BrigtnessIterator--;
            if(BrigtnessIterator == 7){
              Kacheli =true;
            }
          }
          if(BrigtnessIterator >=7 and Kacheli == true){ 
            BrigtnessIterator++;
            if(BrigtnessIterator == 128){
              Kacheli =false;
            }
          }
          strip.Show(); 
          //Serial.print ("Kacheli:");Serial.print(Kacheli);Serial.print (" BrigtnessIterator");Serial.println(BrigtnessIterator);
          timing = millis(); 
      }

  }

public:
  LightPodsvetka() : strip(PixelCount, PixelPin)
  {
    strip.Begin();
    strip.Show();
    strip.SetBrightness(1);
  }

  void SetOnOff(States s)
  {
    if (s == ON)
    {
      OnLight = true;
    }
    if (s == OFF)
    {
      OnLight = false;
    }
  }
  States GetIsOnOrOff(){
    if(OnLight == true){
      return ON;
    } 
    else{
      return OFF;
    }
  }

  void SetSmoothly(LightSmoothly s)
  {
    if (s == Smoothly)
    {
      OnSmoothly = true;
    }
    if (s == NoSmoothly)
    {
      OnSmoothly = false;
    }
  }
  LightSmoothly GetSmoothlyOrNot(){
    if(OnSmoothly == true){
      return Smoothly;
    } 
    else{
      return NoSmoothly;
    }
  }


  States GetIsChangeLightFromSE(){
    if(IsNowChangeLightFromSE == true){ return ON; } 
    else{ return OFF; }
  }
  void SetIsChangeLightFromSE(States s)
  {
    if (s == ON) {IsNowChangeLightFromSE = true; }
    if (s == OFF){IsNowChangeLightFromSE = false;}  
  }

    void SetDemoLight(States s)
  {
    if (s == ON) {demoLight = true; }
    if (s == OFF){demoLight = false;}  
  }
  LightPodsvetka &LogicLight(int Co2, int16_t Co2Treshold)
  { // На основе Со2 решает каким цветом должна быть подсветка
    if (Co2 < (Co2Treshold * 10) - 100)
    {
      NowColor = GREEN;
    }
    if (Co2 > (Co2Treshold * 10) - 100 and Co2 < Co2Treshold * 10)
    {
      NowColor = YELLOW;
    }
    if (Co2 > (Co2Treshold * 10))
    {
      NowColor = RED;
    }
    return *this;
  }


class Timer;
  void MakeLight(StateWorkOrChill s)
  {
    // Serial.print(" GetIsChangeLightFromSE(): ");Serial.print(GetIsChangeLightFromSE() ); 
    if (OnLight) // Если подсветка включена
    { 
        if(demoLight == false){ // Если мы сейчас не в меню 4.4
            if(IsNowChangeLightFromSE == true and s == Chill){
                StaticLights(Purple);     
            }
            else{
              switch (NowColor)
                {
                    case GREEN:
                        if( GetSmoothlyOrNot() == NoSmoothly){ // Если выбрано просто постоянное светчение
                          StaticLights(green);
                        }
                        else{
                          DynamicLights(green);
                        }
                    break;

                    case YELLOW:
                        if( GetSmoothlyOrNot() == NoSmoothly){ // Если выбрано просто постоянное светчение
                          StaticLights(yellow);
                        }
                        else{
                          DynamicLights(yellow);
                        }
                    break;

                    case RED:
                        if( GetSmoothlyOrNot() == NoSmoothly){ // Если выбрано просто постоянное светчение
                          StaticLights(red);
                        }
                        else{
                          DynamicLights(red);
                        }
                    break;

                }
        
              }
        }
        else{ // А если в меню 4.4 то показать какая будет подсветка при перерыве 
            StaticLights(Purple);
        }
    }
    if(!OnLight)
    {
      strip.SetPixelColor(0, off);
      strip.SetPixelColor(1, off);
      strip.SetPixelColor(2, off);
      strip.Show();
    }
  }
};