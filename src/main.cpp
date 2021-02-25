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
//SemaphoreHandle_t xSerialSemaphore;
 

//  Задачи для freeRtos. Будут параллельно исполнятся
void buttonTask(void *pvParam)
{ // Обработка кнопок независимо от всего происходящего

  if (nastolnikPtr)
  {
    while (true)
    {
      nastolnikPtr->UpdateButtons();
      nastolnikPtr->HandleButtonsEvents();
      //buttons.Print(menu,false); // Второй параметр означает делать ли перенос строки
      /*
if ( xSemaphoreTake( xSerialSemaphore, ( TickType_t ) 5 ) == pdTRUE )
      {
        Serial.print("WAKQ WADD = ");
        Serial.println("");
        xSemaphoreGive( xSerialSemaphore );
      }
      */
      vTaskDelay(pdMS_TO_TICKS(1)); // Отдать время камня другим процессам
    }
  }
}

void MenuTask(void *pvParam) // Co2 Menu Light
{ // Обработка кнопок независимо от всего происходящего
  if (nastolnikPtr)
    while (true)
    {
      nastolnikPtr->UpdateAirData(); //Читаем данные об Сo2
      nastolnikPtr->UpdateMenu();
      nastolnikPtr->UpdateLight();

//if ( xSemaphoreTake( xSerialSemaphore, ( TickType_t ) 5 ) == pdTRUE )
 //     {
   /*
        Serial.print("Temperature = ");
        Serial.print(bme.readTemperature());
        Serial.println(" *C");

        Serial.print("Pressure = ");
        Serial.print(bme.readPressure() / 100.0F);
        Serial.println(" hPa"); // В гексапаскалях

        Serial.print("Pressure = ");
        Serial.print(bme.readPressure() / 133.3F);
        Serial.println(" mm.rt."); // В мм рт ст

        Serial.print("Approx. Altitude = ");
        Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
        Serial.println(" m");

        Serial.print("Humidity = ");
        Serial.print(bme.readHumidity());
        Serial.println(" %");

        Serial.println();
        */
  //      xSemaphoreGive( xSerialSemaphore );
  //    }


      vTaskDelay(pdMS_TO_TICKS(1)); // Отдать время камня другим процессам
    }
}
//  Задачи для freeRtos. Будут параллельно исполнятся

void setup()
{
  // put your setup code here, to run once:
  delay(500);
  Serial.begin(115200);

  // i2c
    Wire.begin(); //Inialize I2C Hardware
  // i2c
 
  nastolnikPtr = new Nastolnik();

  xTaskCreate(buttonTask, "button", 1024, NULL, 1, &button);             // Cоздать задачу по обработке кнопок
  xTaskCreate(MenuTask, "Menu", 4096, NULL, 1, NULL); // Cоздать задачу по обработке кнопок
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

   

/*
   // Семафоры полезны для остановки задачи, когда она должна
   // быть поставлена на паузу для ожидания из-за необходимости
   // доступа к общему ресурсу. В нашем случае это порт Serial.
   // Семафоры должны использоваться только когда работает
   // планировщик, но здесь мы можем их настроить.
   // Проверка, что семафор уже не создан:
   
   if ( xSerialSemaphore == NULL )
   {
      // Создание мьютексного семафора, который мы будем использовать
      // для обслуживания доступа к порту Serial:
      xSerialSemaphore = xSemaphoreCreateMutex();
      if ( ( xSerialSemaphore ) != NULL )
      {
         // Если семафор создан, то делаем его доступным (Give)
         // для использования при доступе к порту Serial:
         xSemaphoreGive( ( xSerialSemaphore ) );
      }
   }
*/


}

void loop()
{

  //if ( xSemaphoreTake( xSerialSemaphore, ( TickType_t ) 5 ) == pdTRUE )
   //   {

    //    xSemaphoreGive( xSerialSemaphore );
     // }

    //vTaskDelay(pdMS_TO_TICKS(560));
   
}
