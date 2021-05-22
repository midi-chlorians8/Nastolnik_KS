#pragma once
#include "Arduino.h"
#include <Wire.h>
// Температура влажность и атмосферное давление
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#define SEALEVELPRESSURE_HPA (1013.25) // Для высоты

// Температура влажность и атмосферное давление

class AirData // Меряет параметры воздуха
{
private:
 /*
// Блок Со2
    //int VOC;        // Летучие органические вещества
    int Co2Val = 1700; // Концентрация С02

    // Переменные для симуляции подделки Со2
    unsigned long timing;// Для симуляции Сo2
    //bool Kacheli = false;
    // Переменные для симуляции подделки Со2
// Блок Со2
 */
// Блок Bme280
Adafruit_BME280 bme; // I2C
// Блок Bme280
public:
    int GetCo2();
    AirData(){
        // Температура влажность и атмосферное давление
        unsigned status;
        
        // default settings
        status = bme.begin(0x76);  
        // You can also pass in a Wire library object like &Wire2
        // status = bme.begin(0x76, &Wire2)
        if (!status) {
            Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
            Serial.print("SensorID was: 0x"); Serial.println(bme.sensorID(),16);

            while (1) delay(10);
        }
        
        Serial.println("-- Default Test --");

        Serial.println();
        bme.setSampling(Adafruit_BME280::MODE_NORMAL,
                        Adafruit_BME280::SAMPLING_X4,  // temperature
                        Adafruit_BME280::SAMPLING_X16, // pressure
                        Adafruit_BME280::SAMPLING_X16,  // humidity
                        Adafruit_BME280::FILTER_X16,
                        Adafruit_BME280::STANDBY_MS_0_5 );
        // Температура влажность и атмосферное давление
    }
    float GetTemp(){
        return bme.readTemperature();
    }
    float GetHum(){
        return bme.readHumidity();
    }
    float GetPressure(){
        return bme.readPressure() / 133.3F; // В мм рт ст
    }
    void Print(){
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
    }
    // /*
    void GenerateRandValueCo2();
    //void GetValueFromSensorCo2(int data){
    //    Co2Val = data;
    //}
    // */

};