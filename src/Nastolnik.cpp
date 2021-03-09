#include "Nastolnik.h"
#include "EEPROMUtil.h"
#include "Sound.h"

#define CCS811_ADDR 0x5A //Alternate I2C Address

//Nastolnik::Nastolnik() : u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE), menu(u8g2)
Nastolnik::Nastolnik() : u8g2(U8G2_R0, 18, 19, 27, 25, 23), menu(u8g2), airDataVect(32, 0), airDataInd(0)
{
    u8g2.begin();
    u8g2.setContrast(255);
    // включаем поддержку UTF8
    u8g2.enableUTF8Print();
    u8g2.clearBuffer();

    ROMInitSuccess = EEPROMBegin(512);

    if (ROMInitSuccess)
    {
        menu.SetDangerLevelCo2Treshold(readIntFromEEPROM(1));
        // 3.1 read
        if (readBoolFromEEPROM(5) == true)
        {
            light.SetOnOff(ON);
        }
        else
        {
            light.SetOnOff(OFF);
        }
        // 3.1 read

        // 3.2 read
        if (readBoolFromEEPROM(6) == true)
        {
            light.SetSmoothly(Smoothly);
        }
        else
        {
            light.SetSmoothly(NoSmoothly);
        }
        // 3.2 read

        // 4.1 read
        if (readBoolFromEEPROM(7) == true)
        {
            timer.SetSafeEyesMode(ON);
        }
        else
        {
            timer.SetSafeEyesMode(OFF);
        }
        // 4.1 read
        timer.SetSEWorkTime(readIntFromEEPROM(8));
        timer.SetSEChillTime(readIntFromEEPROM(13));
        if (readBoolFromEEPROM(17) == true)
        {
            light.SetIsChangeLightFromSE(ON);
        }
        else
        {
            light.SetIsChangeLightFromSE(OFF);
        }
        //writeIntIntoEEPROM(13, timer.GetSEChillTime() );writeIntIntoEEPROM(13, timer.GetSEChillTime() );
        if (readBoolFromEEPROM(18) == true)
        {
            sound.SetState(Sound::ON);
        }
        else
        {
            sound.SetState(Sound::OFF);
        }

        buttons.emplace(ButtonType::Left, LeftButtonPin);
        buttons.emplace(ButtonType::Right, RightButtonPin);
        buttons.emplace(ButtonType::Up, UpButtonPin);
        buttons.emplace(ButtonType::Down, DownButtonPin);
    }
/*
    if (mySensor.begin() == false)
    {

        while (1)
        {
            Serial.print("CCS811 error. Please check wiring. Freezing...");
        }
    }
*/
}

void Nastolnik::UpdateButtons()
{
    for (auto &&type_and_button : buttons)
    {
        type_and_button.second.Update();
    }

    capButton.IsPressed(menu,timer);  //.Print(menu,true); // Чтение и обработка кнопок
    
}

//TODO:
// Добавить в меню методы NavigateUp, NavigateDown, NavigateLeft, NavigateRight
// использовать их вместо SetHorizontalPosition(...)
// Внутри menu в зависимости от Layer обрабатывать логику в новых методах

void Nastolnik::HandleButtonsEvents()
{
    for (auto type_and_button : buttons)
    {
        ButtonType type = type_and_button.first;
        Button &button = type_and_button.second;

        if (button.GetEvent() == ButtonEvent::Clicked)
        {
            switch (type)
            {
            case ButtonType::Left:
                menu.NavigateLeft(ButtonEvent::Clicked);
                break;
            case ButtonType::Right:
                menu.NavigateRight(ButtonEvent::Clicked);
                break;
            case ButtonType::Up:
                menu.NavigateUp(ButtonEvent::Clicked);
                break;
            case ButtonType::Down:
                menu.NavigateDown(ButtonEvent::Clicked);
                break;
            default:
                break;
            }
        }
        else if (button.GetEvent() == ButtonEvent::Hold)
        {
            switch (type)
            {
            case ButtonType::Left:
                break;
            case ButtonType::Right:
                break;
            case ButtonType::Up:
                menu.NavigateUp(ButtonEvent::Hold);
                break;
            case ButtonType::Down:
                menu.NavigateDown(ButtonEvent::Hold);
                break;
            default:
                break;
            }
        }

        // Тут вход в главное меню с нажатия 2х кнопок левой и правой
        if (buttons.at(ButtonType::Left).GetEvent() == ButtonEvent::Hold &&
            buttons.at(ButtonType::Right).GetEvent() == ButtonEvent::Hold)
        {
            //Serial.println("OOOOOOOOOOOOOOO");
            if (
                buttons.at(ButtonType::Left).GetStateDuration() > 1300 &&
                buttons.at(ButtonType::Right).GetStateDuration() > 1300)
            {
                //Serial.println("IIIIIIIIIIIIIII");
                if (menu.GetMenuLayer() == 0)
                {
                    menu.SetMenuLayer(1);
                    menu.SetHorizontalPosition(1);
                    menu.SetVerticalPosition(1);
                }
            }
        }
    }
}

void Nastolnik::UpdateAirData()
{
    //MHZ19C.ReadMHZ19C(500); 
     int airValueCO2 = MHZ19C.ReadMHZ19C(2000);
        /*
        Serial.print("Air Data: ");
        Serial.print(airValue);
        Serial.println("");
        */
        airDataVect[airDataInd] = airValueCO2;
        airDataInd = (airDataInd + 1) % airDataVect.size();
       /* 
    if (mySensor.dataAvailable())
    {
        //If so, have the sensor read and calculate the results.
        //Get them later
        mySensor.readAlgorithmResults();

        int airValueCO2 = mySensor.getCO2();
        
        Serial.print("Air Data: ");
        Serial.print(airValue);
        Serial.println("");
      
        airDataVect[airDataInd] = airValueCO2;
        airDataInd = (airDataInd + 1) % airDataVect.size();
    }
    */
    // delay(10); //Don't spam the I2C bus
    //buttons.Print(menu,false); // Второй параметр означает делать ли перенос строки

    //airData.GenerateRandValue(); //
}

void Nastolnik::UpdateMenu()
{
    menu.LogicMenu(light, sound, timer);                     // Логика меню
    menu.DrawMenu(light, timer, sound, airDataVect, airDataInd,airData_TempHumPress); // Отрисовка меню ,timer
    //airData_TempHumPress.Print();
    //menu.Print();
    //graph.FillVector();
    //graph.Print();
    //sound.ReceiveKommand(Sound:: Nop);
    timer.CountTime(capButton,sound); //Подкидышъ считает время
    timer.NotifyPereriv(sound);

    timer.Print(); //Tog
    
    //buttons.Print(menu,true);
    sound.ReceiveKommand(); //Подкидышъ
    sound.BeepLogic();
    //sound.Print(); //Tog
}

//Sound::Kommands z; // Только для  sound.BeepLogic(z);
void Nastolnik::UpdateLight()
{
    int lastAirData = airDataVect[(airDataInd + airDataVect.size() - 1) % airDataVect.size()];

    light.LogicLight(lastAirData, menu.GetDangerLevelCo2Treshold()).MakeLight(timer.WhatDoingNow);
    //sound.BeepLogic(Sound::Kommands TimerTime); !! TUT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}