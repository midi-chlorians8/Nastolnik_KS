//10.01.21 Проект Настольник. И Романовский при участии Е Субоч
//17.01.21 Починил таймер - буззер програмно
//Первый правки draw menu после перестройки кода егором z
//18.01.21 Егор Реструкт правки по button. Я подправил

//26.02.2021
#include <Arduino.h>

#include "Nastolnik.h"
Nastolnik *nastolnikPtr = nullptr;

TaskHandle_t button;   //Хэндл который не используется
bool waitOneMinGlobal; // Костыль. Нужен для того чтоб продлить на минуту время работы. Служит для общения между собой классов Timer и CapacityButton
bool impuls=false; // Костыль. Для печати раз в секунду отладочной инфы sound + timer print

 


void setup()
{
  // put your setup code here, to run once:
  delay(500);
  Serial.begin(115200);

  // i2c
    Wire.begin(); //Inialize I2C Hardware
  // i2c
 
  nastolnikPtr = new Nastolnik();

  
  // Если не стартовал Eeprom
  if (!nastolnikPtr->IsRomInitSuccess())
  {
    Serial.println("Failed to initialise EEPROM");
    Serial.println("Restarting...");
    delay(1000);
    delete nastolnikPtr;
    ESP.restart();
  }
  // Если не стартовал Eeprom

   



}

void loop()
{
      nastolnikPtr->UpdateButtons();
      nastolnikPtr->HandleButtonsEvents();
      nastolnikPtr->UpdateAirData(); //Читаем данные об Сo2
      nastolnikPtr->UpdateMenu();
      nastolnikPtr->UpdateLight();

   
}
