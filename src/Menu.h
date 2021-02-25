#pragma once


/*
#ifdef U8X8_HAVE_HW_I2C 
#include <Wire.h>
#endif
*/

#include "EEPROMUtil.h"
//#include "AirData.h"
#include "LightPodsvetka.h"
#include "Sound.h"
//#include "Timer.h"
#include "Button.h"
#include "Graph.h"
// Для экрана.
class Timer;
class U8G2_SSD1309_128X64_NONAME0_F_4W_SW_SPI;
#include "AirData.h"

class Menu
{

    // Переменные меню основные
    int menuLayer = 0;             // Уровень меню
    int16_t verticalPosition = 0;  // Ползунок по вертикали. Для координат где мы находимся в дереве меню
    int8_t horizontalPosition = 1; // Ползунок по горизонтали. Для координат где мы находимся в дереве меню

    // Переменные меню вспомогательные
    bool oneRazPosition1_1 = false;     // Один раз записать текущее значение параметра системы в старую переменную, чтобы при выходе из меню начиркав не сохранять чиркаш
    int16_t old_DangerLevelCo2Treshold; // Один раз записать текущее значение параметра системы в старую переменную, чтобы при выходе из меню начиркав не сохранять чиркаш
    bool saveBlink_sensOnValue1_1;      // Нужно чтобы при выходе не сбрасывалось значение

    bool oneRazPosition4_2 = false;     // Один раз записать текущее значение параметра системы в старую переменную, чтобы при выходе из меню начиркав не сохранять чиркаш
    int16_t old_SEWorkTime; // Один раз записать текущее значение параметра системы в старую переменную, чтобы при выходе из меню начиркав не сохранять чиркаш

    bool oneRazPosition4_3 = false;
    int16_t old_SEChillTime; // Один раз записать текущее значение параметра системы в старую переменную, чтобы при выходе из меню начиркав не сохранять чиркаш

    bool oneRazPosition4_4 = false;
    
    // Параметры системы
    int16_t DangerLevelCo2Treshold = 900;


    // Переменные отрисовка меню
    int CursorPosY = 18; // Позиция курсора

    bool saveBlink =false; //Для моргания save; Было ли нажатия save
    unsigned long timingSave; //Для моргания save; Отсчёт сколько времени save не светится 
    bool OneRazTimingSave = false;  // Один раз присвоить текущее время переменной timingSave

    //Переменные отрисовка график
    
    enum DrawStates {
       wait,
       draw 
    };
    
    // Другое
    U8G2_SSD1309_128X64_NONAME0_F_4W_SW_SPI& u8g2;

    void DrawSave(); // Чтобы надпись save моргнула

    class Drop{
        //int startXpos; // Должно быть     
        // Drop start coords
        struct CoordsDrop{
            int8_t horizont = 50; // Для смещения
            int x0 = horizont;
            int y0 = 0;   
            int x1 = horizont -5;
            int y1 = 0   +5;
        };
        CoordsDrop CoordsDrop1;
        bool nowWaitBool =false;
        //CoordsDrop CoordsDrop2;
        // Drop start coords
        public:
            Drop(){
                RandomShiftDrop();
            }

        void RandomDelayBeforDraw(){
            // Один раз замерять текущее время
            CoordsDrop1.x0 = 255;
            CoordsDrop1.y0 = 255;   
            CoordsDrop1.x1 = 255;
            CoordsDrop1.y1 = 255;

            //return  draw;
        }
        void MooveDrop(){
            CoordsDrop1.x0-=5;
            CoordsDrop1.y0+=5;
            CoordsDrop1.x1-=5;
            CoordsDrop1.y1+=5;
        }    
        void CheckBorder(){
            // Проверка был ли перелёт нижней границы и обработка этого
            if( (Drop::CoordsDrop1.y0>64 or Drop::CoordsDrop1.x1<0)  ){ //Если капля перелетела низ экрана или коснулась левого бока то вернуть каплю

                // Вернуть исходные координаты
                CoordsDrop1.x0 = CoordsDrop1.horizont;
                CoordsDrop1.y0 = 0;   
                CoordsDrop1.x1 = CoordsDrop1.horizont -5;
                CoordsDrop1.y1 = 0   +5;
                // Вернуть исходные координаты
            
                RandomShiftDrop();
            }
        }
        void RandomShiftDrop(){
            CoordsDrop1.horizont = random(10, 255);
        }
        void TimingControl(){
           // if(nowWaitBool == true){
                delay(1000);
            //    nowWaitBool = false;
           // }
        }
        CoordsDrop GetCoords(){
            return CoordsDrop1;
        }
        void SetDrawStates(DrawStates s){
            if(s==wait){
                nowWaitBool = true;
            }
            if(s==draw){
                nowWaitBool = false;
            }
        }

        DrawStates GetDrawStates(){
            if(nowWaitBool==true){
                return wait;
            }
            if(nowWaitBool == false){
                return draw;
            }
        }


    };
    std::vector<Drop> drops;  

public:

    Menu(U8G2_SSD1309_128X64_NONAME0_F_4W_SW_SPI& u8g2);
    void LogicMenu(LightPodsvetka& light,Sound& sound,Timer &timer);
    void DrawMenu(LightPodsvetka& light,Timer &timer,Sound& sound, const std::vector<int>& airData, int airDataInd,AirData airData_TempHumPress); //,Timer &timer
    void Print();

    int GetMenuLayer();
    void SetMenuLayer(int); // Уровень меню
    int16_t GetVerticalPosition();
    void SetVerticalPosition(int16_t); // Ползунок по вертикали. Для координат где мы находимся в дереве меню
    int8_t GetHorizontalPosition();    // Ползунок по горизонтали. Для координат где мы находимся в дереве меню
    void SetHorizontalPosition(int8_t);
    int16_t GetDangerLevelCo2Treshold();
    void SetDangerLevelCo2Treshold(int16_t);

    void NavigateRight(ButtonEvent b){
        if(b == ButtonEvent::Clicked){
            SetHorizontalPosition(GetHorizontalPosition() + 1);
        }

    }
    void NavigateLeft(ButtonEvent b){
        if(b == ButtonEvent::Clicked){
            SetHorizontalPosition(GetHorizontalPosition() - 1);
        }

    }
    void NavigateUp(ButtonEvent b){
        if(b == ButtonEvent::Clicked){
            SetVerticalPosition(GetVerticalPosition() - 1);
        }
        if(b == ButtonEvent::Hold){
            if(menuLayer != 0 and menuLayer != 1 and menuLayer != 2 ){
                SetVerticalPosition(GetVerticalPosition() - 1);
            }
        }

    }
    void NavigateDown(ButtonEvent b){
        if(b == ButtonEvent::Clicked){
            SetVerticalPosition(GetVerticalPosition() + 1);
        }
        if(b == ButtonEvent::Hold){
            if(menuLayer != 0 and menuLayer != 1 and menuLayer != 2 ){
                SetVerticalPosition(GetVerticalPosition() + 1);
            }
        }

    }
/*
    void SetVerticalHorizontPos(){ // Чтоб при нажатии кнопки сразу же переключится на старт

    }
*/

        
};
