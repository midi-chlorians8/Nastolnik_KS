// Блок MHZ19C Сo2
#include "MHZ19.h" // Библиотека для датчика                                       

class MyMHZ19C{
  private:
    #define RXD2 15
    #define TXD2 12     // Device to MH-Z19 Serial baudrate (should not be changed)
    MHZ19 myMHZ19;                                   // Constructor for library 

    unsigned long getDataTimer = 0;
    int CO2; 
 
public:
    MyMHZ19C(){
      // Блок MHZ19C
      Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
      myMHZ19.begin(Serial2);                                // *Serial(Stream) refence must be passed to library begin(). 
      myMHZ19.autoCalibration();                              // Turn auto calibration ON (OFF autoCalibration(false))
      // Блок MHZ19C
    }
    int ReadMHZ19C(int readingInterval) { // Вопрос Егору про секунды
        // Блок MHZ19C
        if (millis() - getDataTimer >=readingInterval)
        {
            /* note: getCO2() default is command "CO2 Unlimited". This returns the correct CO2 reading even 
            if below background CO2 levels or above range (useful to validate sensor). You can use the 
            usual documented command with getCO2(false) */

            CO2 = myMHZ19.getCO2();                             // Request CO2 (as ppm)
            int8_t Temp = myMHZ19.getTemperature();             // Request Temperature (as Celsius)

            Serial.print("CO2 (ppm): ");    Serial.println(CO2);     
            //Serial.print("Temperature (C): ");    Serial.println(Temp);               
            getDataTimer = millis();
        }
        return CO2;
        //return  random(0, 2000);
        
        // Блок MHZ19C
    }

  
};