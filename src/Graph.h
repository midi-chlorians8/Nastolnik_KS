#pragma once

#include <vector>
#include <Arduino.h>
//#include <U8g2lib.h>

extern int Co2GlobalVal;
//using namespace std;
// Принять Сo2
// Перевести пропорционально для высоты экрана
// Занести его в конец массива
class Graph{
    const int step = 4; // 128/4 = 32;
    std::vector<int> Co2Values;
    
    unsigned long timing; // For Print

    int oldValueCo2 = -1; // -1  Для старта потому что значения всегда в + диапазоне

public:
    Graph (){
        Co2Values.resize(32,64); // 64 - нижняя граница дисплея
        //Co2Values.assign(32,99);
        /*
        for (int & number: Co2Values){
            number = 99;
        }
        */
    }
    void FillVector(){ // Заполним Со2 для начала. Скорость изменений графика = частоте смены значений

        
        
    }
    std::vector<int> GetCo2Values(){
        return Co2Values;
    }
    void Print(){
        if (millis() - timing > 1000){ // Вместо 10000 подставьте нужное вам значение паузы 
            Serial.print("Co2Values:");
            for (int & number : Co2Values){
                Serial.print(number);Serial.print(" ");
            }
            Serial.println("");
            timing = millis();    
        }
         
    }
};
