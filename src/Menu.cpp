#include "Menu.h"
#include <U8g2lib.h>
#include "LightPodsvetka.h"
#include "Sound.h"
#include "Timer.h"
#include "Graph.h"
#include <vector>

// Комплекс сделай один раз. Актуален для мой меню чтоб не плодить кода лишнего
bool OneRazCopyBool = false; // Для работы функции RazOneCopy
States OneRazCopy(States voChto, States Chto)
{
    if (OneRazCopyBool == false)
    {
        voChto = Chto;
        OneRazCopyBool = true;
    }
    return voChto;
}
LightSmoothly OneRazCopy(LightSmoothly voChto, LightSmoothly Chto)
{
    if (OneRazCopyBool == false)
    {
        voChto = Chto;
        OneRazCopyBool = true;
    }
    return voChto;
}
Sound::States OneRazCopy(Sound::States voChto, Sound::States Chto)
{
    if (OneRazCopyBool == false)
    {
        voChto = Chto;
        OneRazCopyBool = true;
    }
    return voChto;
}

void OneRazCopyReset()
{
    OneRazCopyBool = false;
}
// Комплекс сделай один раз. Актуален для мой меню чтоб не плодить кода лишнего

// Внутренние переменные для меню которые СОВСЕМ не нужны при исполнении других частей кода
Sound::States OldStateSound;

States OldStateLight; // Когда перебираем включить - выключить чтоб сразу включалась и выключалась
bool IsBeSaved_lightOnOff3_1 = false;

LightSmoothly OldStateSmoothly;
bool IsBeSaved_lightOnOff3_2 = false;

States OldStateSaveEyesMode;
bool IsBeSaved_lightOnOff4_1 = false;

bool IsBeSaved_lightOnOff4_2 = false;

bool IsBeSaved_lightOnOff4_3 = false;

States OldStateLightFromSEMode; // Когда перебираем включить - выключить чтоб сразу включалась и выключалась
bool IsBeSaved_lightOnOff4_4 = false;

void Menu::DrawSave()
{ // Чтобы надпись save моргнула
    if (saveBlink == false)
    {
        u8g2.drawStr(105, 50, "save");
    }
    else
    {
        // Один раз присвоить текущее время переменной timingSave
        if (OneRazTimingSave == false)
        {
            timingSave = millis();
            u8g2.drawStr(105, 50, "    ");
            OneRazTimingSave = true;
        }
        // Один раз присвоить текущее время переменной timingSave
        if (millis() - timingSave > 100)
        { // Вместо 10000 подставьте нужное вам значение паузы
            u8g2.drawStr(105, 50, "save");

            //timingSave = millis();
            //Serial.println ("10 seconds");
            OneRazTimingSave = false;
            saveBlink = false;
        }
    }
}

Menu::Menu(U8G2_SSD1309_128X64_NONAME0_F_4W_SW_SPI &display) : u8g2(display), drops(10)
{
    //DangerLevelCo2Treshold=EEPROM.readInt(1); // Чтение из eeprom значения DangerLevelCo2Treshold
}

void Menu::LogicMenu(LightPodsvetka &light, Sound &sound, Timer &timer)
{
    if (menuLayer == 0)
    { // Главный экран

        if(verticalPosition == 1){
            if (horizontalPosition < 1)
            {
                horizontalPosition = 3;
            } // Для скролла
            if (horizontalPosition > 3)
            {
                horizontalPosition = 1;
            } // Для скролла
        }
        if(verticalPosition == 0){
            if (horizontalPosition < 1)
            {
                horizontalPosition = 2;
            } // Для скролла
            if (horizontalPosition > 2)
            {
                horizontalPosition = 1;
            } // Для скролла
        }

        if (verticalPosition < 0)
        {
            verticalPosition = 1;
        } // Для вертикального выбора между Сo2 Комбинациям и Заставками
        if (verticalPosition > 1)
        {
            verticalPosition = 0;
        } // Для вертикального выбора между Сo2 Комбинациям и Заставками
    }
    if (menuLayer == 1)
    { // Меню
        // Вертикальный скроллинг курсора

        if (verticalPosition < 1)
        {
            verticalPosition = 5;
            menuLayer = 2;
        } // Ограничить вертикальный ползунок при движении вверх
        if (verticalPosition > 5)
        {
            verticalPosition = 1;
            menuLayer = 1;
        } // Ограничить вертикальный ползунок при движении вниз

        // Вертикальный скроллинг курсора

        if (verticalPosition == 1)
        {
            CursorPosY = 18;
            if (horizontalPosition == 2)
            {
                menuLayer = 101;
                verticalPosition = 1;
                horizontalPosition = 1;
            }
        }
        if (verticalPosition == 2)
        {
            CursorPosY = 29;
            if (horizontalPosition == 2)
            {
                menuLayer = 20;
                verticalPosition = 1;
                horizontalPosition = 1;
            }
        }
        if (verticalPosition == 3)
        {
            CursorPosY = 39;
            if (horizontalPosition == 2)
            {
                menuLayer = 30;
                verticalPosition = 1;
                horizontalPosition = 1;
            }
        }
        if (verticalPosition == 4)
        {
            CursorPosY = 48;
            menuLayer = 1;
            if (horizontalPosition == 2)
            {
                menuLayer = 40;
                verticalPosition = 1;
                horizontalPosition = 1;
            }
        }
        if (verticalPosition == 5)
        {
            CursorPosY = 18;
            menuLayer = 2;
        }
        //if( horizontalPosition == 0) {menuLayer=0; }  // Если мы жмякаем в левую сторону на exit
        oneRazPosition1_1 = false;        // menuLayer == 101
        saveBlink_sensOnValue1_1 = false; // menuLayer == 101
        saveBlink = false;                // Нажато ли в меню menuLayer == 101 save

        //OneRazTimingSave = false; // Часть функции Save
        if (horizontalPosition == 0)
        {
            menuLayer = 0;
            verticalPosition = 1;
        }
    }
    if (menuLayer == 2)
    { // Меню

        if (verticalPosition == 4)
        {
            CursorPosY = 48;
            menuLayer = 1;
        }

        // Когда курсор на Exit при нажатии вправо или влево выйти в главное меню
        if (horizontalPosition == 2)
        {
            menuLayer = 0;
            verticalPosition = 1;
        }
        if (horizontalPosition == 0)
        {
            menuLayer = 0;
            verticalPosition = 1;
        }
        // Когда курсор на Exit при нажатии вправо или влево выйти в главное меню

        // Ограничить вертикальный ползунок при движении вверх
        if (verticalPosition < 1)
        {
            verticalPosition = 5;
            menuLayer = 2;
        }
        if (verticalPosition > 5)
        {
            verticalPosition = 1;
            menuLayer = 1;
        } // Ограничить вертикальный ползунок при движении вниз
    }
    // 1.1
    if (menuLayer == 101) //1.1 Co2 Treshold
    {
        if (oneRazPosition1_1 == false)
        { // Один раз исполнить. Чтобы появилось в менюшке правильное значение которое в системе
            old_DangerLevelCo2Treshold = DangerLevelCo2Treshold;
            verticalPosition = map(DangerLevelCo2Treshold, 0, 30, -180, -210);// Исполнить один раз чтоб галочка соответствовала значению
            oneRazPosition1_1 = true;
        } // Один раз исполнить. Чтобы появилось в менюшке правильное значение которое в системе

        DangerLevelCo2Treshold = abs((180 + verticalPosition));

        // Km/h  verticalPosition
        // 0        -180
        // 99       -81
        //DangerLevelCo2Treshold=constrain(DangerLevelCo2Treshold,0,2000);
        //if( verticalPosition>2000){verticalPosition=2000;}  // Защита от выхода за диапазон)
        //if( verticalPosition<0){verticalPosition=0;}  // Защита от выхода за диапазон)

        if (horizontalPosition == 2)
        { // save
            writeIntIntoEEPROM(1, DangerLevelCo2Treshold);  //Тут ввод нового значения переменной и сохранения в EEPROM

            saveBlink_sensOnValue1_1 = true; // Нужно чтобы при выходе не сбрасывалось значение
            saveBlink = true;                // Чтобы моргала надпись save
            horizontalPosition = 1;          // Вернуть ползунок по горизонтали
        }

        if (horizontalPosition == 0) // back
        {

            if (saveBlink_sensOnValue1_1 != true)
            {
                DangerLevelCo2Treshold = old_DangerLevelCo2Treshold;
            }
            menuLayer = 1;
            verticalPosition = 1;
            horizontalPosition = 1;
        }

    }
    // 1.1
    // 2
    if (menuLayer == 20)
    {
        // Вертикальный скроллинг курсора
        // Ограничить вертикальный ползунок при движении вверх
        if (verticalPosition < 1)
        {
            verticalPosition = 2;
        }
        // Ограничить вертикальный ползунок при движении вниз
        if (verticalPosition > 2)
        {
            verticalPosition = 1;
        }
        // Вертикальный скроллинг курсора

        if (verticalPosition == 1)
        {
            CursorPosY = 20 - 1;
        } //Перебираем курсором
        if (verticalPosition == 2)
        {
            CursorPosY = 45 - 1;
        } //Перебираем курсором

        if (verticalPosition == 1)
        { // Если войти в вкл - выкл подсветка
            if (horizontalPosition == 2)
            {
                menuLayer = 201;
                horizontalPosition = 1;

                // Делаем чтобы курсор был на выбранном значении при входе в пункт меню
                if (sound.GetState() == Sound::ON)
                {
                    verticalPosition = 1;
                }
                else
                {
                    verticalPosition = 2;
                }
                // Делаем чтобы курсор был на выбранном значении при входе в пункт меню
            }
        }
        if (verticalPosition == 2)
        { // Если войти в вкл - выкл подсветка
            if (horizontalPosition == 2)
            {
                menuLayer = 202;
                horizontalPosition = 1;

                // Делаем чтобы курсор был на выбранном значении при входе в пункт меню
                if (1)
                { //if(light.GetSmoothlyOrNot() == Smoothly){
                    verticalPosition = 1;
                }
                else
                {
                    verticalPosition = 2;
                }
                // Делаем чтобы курсор был на выбранном значении при входе в пункт меню
            }
        }

        if (horizontalPosition == 0)
        {
            menuLayer = 1;
            verticalPosition = 2;
            horizontalPosition = 1;
        } // Вернутся на уровень назад
        OneRazCopyReset();
        IsBeSaved_lightOnOff3_1 = false;
    }
    // 2
    // 2.1
    if (menuLayer == 201)
    {
        // Ограничить вертикальный ползунок при движении вверх
        if (verticalPosition < 1)
        {
            verticalPosition = 2;
        }
        // Ограничить вертикальный ползунок при движении вниз
        if (verticalPosition > 2)
        {
            verticalPosition = 1;
        }

        OldStateSound = OneRazCopy(OldStateSound, sound.GetState());

        if (verticalPosition == 1)
        {
            sound.SetState(Sound::ON);
            sound.DemoSignalFromMenu(Sound::ON);
        }
        if (verticalPosition == 2)
        {
            sound.SetState(Sound::OFF);
            sound.DemoSignalFromMenu(Sound::OFF);
        }

        if (horizontalPosition == 0) // back
        {
            sound.DemoSignalFromMenu(Sound::OFF); // Перезарядка Демо Пик из меню
            menuLayer = 20;
            verticalPosition = 1;
            horizontalPosition = 1;
            if (IsBeSaved_lightOnOff3_1 != true)
            {
                sound.SetState(OldStateSound);
            }
        }
        if (horizontalPosition == 2)
        { // save
            if (verticalPosition == 1)
            {
                sound.SetState(Sound::ON);
            }
            if (verticalPosition == 2)
            {
                sound.SetState(Sound::OFF);
            }
            saveBlink = true;               // Чтоб надпись save моргала как надо
            IsBeSaved_lightOnOff3_1 = true; // Нужно чтобы при выходе не сбрасывалось значение
            writeBoolIntoEEPROM(18, sound.GetState());
            sound.DemoSignalFromMenu(Sound::OFF); // Перезарядка Демо Пик из меню
            horizontalPosition = 1;
        }
    }
    // 2.1
    // 3
    if (menuLayer == 30)
    {
        // Вертикальный скроллинг курсора
        // Ограничить вертикальный ползунок при движении вверх
        if (verticalPosition < 1)
        {
            verticalPosition = 2;
        }
        // Ограничить вертикальный ползунок при движении вниз
        if (verticalPosition > 2)
        {
            verticalPosition = 1;
        }
        // Вертикальный скроллинг курсора

        if (verticalPosition == 1)
        {
            CursorPosY = 20 - 1;
        } //Перебираем курсором
        if (verticalPosition == 2)
        {
            CursorPosY = 45 - 1;
        } //Перебираем курсором

        if (verticalPosition == 1)
        { // Если войти в вкл - выкл подсветка
            if (horizontalPosition == 2)
            {
                menuLayer = 301;
                horizontalPosition = 1;

                // Делаем чтобы курсор был на выбранном значении при входе в пункт меню
                if (light.GetIsOnOrOff() == ON)
                {
                    verticalPosition = 1;
                }
                else
                {
                    verticalPosition = 2;
                }
                // Делаем чтобы курсор был на выбранном значении при входе в пункт меню
            }
        }
        if (verticalPosition == 2)
        { // Если войти в вкл - выкл подсветка
            if (horizontalPosition == 2)
            {
                menuLayer = 302;
                horizontalPosition = 1;

                // Делаем чтобы курсор был на выбранном значении при входе в пункт меню
                if (light.GetSmoothlyOrNot() == Smoothly)
                {
                    verticalPosition = 1;
                }
                else
                {
                    verticalPosition = 2;
                }
                // Делаем чтобы курсор был на выбранном значении при входе в пункт меню
            }
        }

        if (horizontalPosition == 0)
        {
            menuLayer = 1;
            verticalPosition = 3;
            horizontalPosition = 1;
        } // Вернутся на уровень назад
        OneRazCopyReset();
        IsBeSaved_lightOnOff3_1 = false;
        IsBeSaved_lightOnOff3_2 = false;
    }
    // 3
    // 3.1
    if (menuLayer == 301)
    {
        // Ограничить вертикальный ползунок при движении вверх
        if (verticalPosition < 1)
        {
            verticalPosition = 2;
        }
        // Ограничить вертикальный ползунок при движении вниз
        if (verticalPosition > 2)
        {
            verticalPosition = 1;
        }

        OldStateLight = OneRazCopy(OldStateLight, light.GetIsOnOrOff());

        if (verticalPosition == 1)
        {
            light.SetOnOff(ON);
        }
        if (verticalPosition == 2)
        {
            light.SetOnOff(OFF);
        }

        if (horizontalPosition == 0) // back
        {
            menuLayer = 30;
            verticalPosition = 1;
            horizontalPosition = 1;
            if (IsBeSaved_lightOnOff3_1 != true)
            {
                light.SetOnOff(OldStateLight);
            }
        }
        if (horizontalPosition == 2)
        { // save
            if (verticalPosition == 1)
            {
                light.SetOnOff(ON);
            }
            if (verticalPosition == 2)
            {
                light.SetOnOff(OFF);
            }
            saveBlink = true;               // Чтоб надпись save моргала как надо
            IsBeSaved_lightOnOff3_1 = true; // Нужно чтобы при выходе не сбрасывалось значение
            writeBoolIntoEEPROM(5, light.GetIsOnOrOff());
            horizontalPosition = 1;
        }
    }
    // 3.1

    // 3.2
    if (menuLayer == 302)
    {
        // Ограничить вертикальный ползунок при движении вверх
        if (verticalPosition < 1)
        {
            verticalPosition = 2;
        }
        // Ограничить вертикальный ползунок при движении вниз
        if (verticalPosition > 2)
        {
            verticalPosition = 1;
        }

        OldStateSmoothly = OneRazCopy(OldStateSmoothly, light.GetSmoothlyOrNot());

        if (verticalPosition == 1)
        {
            light.SetSmoothly(Smoothly);
        }
        if (verticalPosition == 2)
        {
            light.SetSmoothly(NoSmoothly);
        }

        if (horizontalPosition == 0) // back
        {
            menuLayer = 30;
            verticalPosition = 2;
            horizontalPosition = 1;
            if (IsBeSaved_lightOnOff3_2 != true)
            {
                light.SetSmoothly(OldStateSmoothly);
            }
        }
        if (horizontalPosition == 2)
        { // save
            if (verticalPosition == 1)
            {
                light.SetSmoothly(Smoothly);
            }
            if (verticalPosition == 2)
            {
                light.SetSmoothly(NoSmoothly);
            }
            saveBlink = true;               // Чтоб надпись save моргала как надо
            IsBeSaved_lightOnOff3_2 = true; // Нужно чтобы при выходе не сбрасывалось значение
            writeBoolIntoEEPROM(6, light.GetSmoothlyOrNot());
            horizontalPosition = 1;
        }
    }
    // 3.2
    // 4
    if (menuLayer == 40)
    {
        // Вертикальный скроллинг курсора

        // Ограничить вертикальный ползунок при движении вниз
        if (verticalPosition > 2)
        {
            menuLayer = 41;
            verticalPosition = 3;
        }
        // Ограничить вертикальный ползунок при движении вверх
        if (verticalPosition < 1)
        {
            menuLayer = 41;
            verticalPosition = 4;
        }
        // Вертикальный скроллинг курсора

        if (verticalPosition == 1)
        {
            CursorPosY = 20 - 1;
        } //Перебираем курсором
        if (verticalPosition == 2)
        {
            CursorPosY = 45 - 1;
        } //Перебираем курсором

        if (verticalPosition == 1)
        { // Если войти в вкл - выкл подсветка
            if (horizontalPosition == 2)
            {
                menuLayer = 401;
                horizontalPosition = 1;

                // Делаем чтобы курсор был на выбранном значении при входе в пункт меню
                if (timer.GetSafeEyesMode() == ON)
                {
                    verticalPosition = 1;
                }
                else
                {
                    verticalPosition = 2;
                }
                // Делаем чтобы курсор был на выбранном значении при входе в пункт меню
            }
        }
        if (verticalPosition == 2)
        { // Если войти в вкл - выкл подсветка
            if (horizontalPosition == 2)
            {
                menuLayer = 402;
                horizontalPosition = 1;
                verticalPosition = 1;
            }
        }

        if (horizontalPosition == 0)
        {
            menuLayer = 1;
            verticalPosition = 4;
            horizontalPosition = 1;
        } // Вернутся на уровень назад
        OneRazCopyReset();
        IsBeSaved_lightOnOff4_1 = false;
        //IsBeSaved_lightOnOff3_2 = false;
        oneRazPosition4_2 = false;       // menuLayer == 101
        IsBeSaved_lightOnOff4_2 = false; // menuLayer == 101
        saveBlink = false;               // Нажато ли в меню menuLayer == 101 save
    }
    if (menuLayer == 41)
    {
        // Вертикальный скроллинг курсора
        // Ограничить вертикальный ползунок при движении вверх
        if (verticalPosition < 3)
        {
            menuLayer = 40;
            verticalPosition = 2;
        }
        // Ограничить вертикальный ползунок при движении вниз
        if (verticalPosition > 4)
        {
            menuLayer = 40;
            verticalPosition = 1;
        }
        // Вертикальный скроллинг курсора

        if (verticalPosition == 3)
        {
            CursorPosY = 20 - 1;
        } //Перебираем курсором
        if (verticalPosition == 4)
        {
            CursorPosY = 45 - 1;
        } //Перебираем курсором

        if (verticalPosition == 3)
        { // Если войти в вкл - выкл подсветка
            if (horizontalPosition == 2)
            {
                menuLayer = 403;
                //verticalPosition = 1;
                horizontalPosition = 1;

                // Делаем чтобы курсор был на выбранном значении при входе в пункт меню

                //if(timer.GetSafeEyesMode() == ON){
                verticalPosition = 1;
                // }
                // else{
                //     verticalPosition = 2;
                // }
                // Делаем чтобы курсор был на выбранном значении при входе в пункт меню
            }
        }
        if (verticalPosition == 4)
        { // Если войти в вкл - выкл подсветка
            if (horizontalPosition == 2)
            {
                menuLayer = 404;
                horizontalPosition = 1;

                // Делаем чтобы курсор был на выбранном значении при входе в пункт меню
                if (light.GetIsChangeLightFromSE() == ON)
                {
                    verticalPosition = 1;
                }
                else
                {
                    verticalPosition = 2;
                }
                // Делаем чтобы курсор был на выбранном значении при входе в пункт меню
            }
        }

        if (horizontalPosition == 0)
        {
            menuLayer = 1;
            verticalPosition = 4;
            horizontalPosition = 1;
        } // Вернутся на уровень назад
        OneRazCopyReset();
        IsBeSaved_lightOnOff4_4 = false;
        //IsBeSaved_lightOnOff3_2 = false;
        oneRazPosition4_3 = false;       // menuLayer == 101
        IsBeSaved_lightOnOff4_3 = false; // menuLayer == 101
        saveBlink = false;               // Нажато ли в меню menuLayer == 101 save
    }
    // 4
    // 4.1
    if (menuLayer == 401)
    {
        // Ограничить вертикальный ползунок при движении вверх
        if (verticalPosition < 1)
        {
            verticalPosition = 2;
        }
        // Ограничить вертикальный ползунок при движении вниз
        if (verticalPosition > 2)
        {
            verticalPosition = 1;
        }

        OldStateSaveEyesMode = OneRazCopy(OldStateSaveEyesMode, timer.GetSafeEyesMode());

        if (verticalPosition == 1)
        {
            timer.SetSafeEyesMode(ON);
        }
        if (verticalPosition == 2)
        {
            timer.SetSafeEyesMode(OFF);
        }

        if (horizontalPosition == 0) // back
        {
            menuLayer = 40;
            verticalPosition = 1;
            horizontalPosition = 1;
            if (IsBeSaved_lightOnOff4_1 != true)
            {
                timer.SetSafeEyesMode(OldStateSaveEyesMode);
            }
        }
        if (horizontalPosition == 2)
        { // save
            if (verticalPosition == 1)
            {
                timer.SetSafeEyesMode(ON);
            }
            if (verticalPosition == 2)
            {
                timer.SetSafeEyesMode(OFF);
            }
            saveBlink = true;               // Чтоб надпись save моргала как надо
            IsBeSaved_lightOnOff4_1 = true; // Нужно чтобы при выходе не сбрасывалось значение
            writeBoolIntoEEPROM(7, timer.GetSafeEyesMode());
            horizontalPosition = 1;
        }
    }
    // 4.1
    // 4.2
    if (menuLayer == 402)
    {
        if (oneRazPosition4_2 == false)
        { // Один раз исполнить. Чтобы появилось в менюшке правильное значение которое в системе
            old_SEWorkTime = timer.GetSEWorkTime();

            verticalPosition = map(timer.GetSEWorkTime(), 0, 30, -180, -210); // Исполнить один раз чтоб галочка соответствовала значению

            oneRazPosition4_2 = true;
        } // Один раз исполнить. Чтобы появилось в менюшке правильное значение которое в системе
        // Ограничители диапазона
        if (verticalPosition > -181)
        {
            verticalPosition = -181;
        }
        if (verticalPosition < -430)
        {
            verticalPosition = -430;
        }
        // Ограничители диапазона

        timer.SetSEWorkTime(abs((180 + verticalPosition)));

        if (horizontalPosition == 2) // save
        { 
            writeIntIntoEEPROM(8, timer.GetSEWorkTime());//Тут ввод нового значения переменной и сохранения в EEPROM

            IsBeSaved_lightOnOff4_2 = true;    // Нужно чтобы при выходе не сбрасывалось значение
            saveBlink = true;                  // Чтобы моргала надпись save

            sound.BeepReset(); // Cбрасываем пики
            timer.SbrosTimer();// Cбрасываем таймер
            horizontalPosition = 1;            // Вернуть ползунок по горизонтали
        }

        if (horizontalPosition == 0) // back
        {
            if (IsBeSaved_lightOnOff4_2 != true)
            {
                timer.SetSEWorkTime(old_SEWorkTime);
            }
            menuLayer = 40;
            verticalPosition = 2;
            horizontalPosition = 1;
        }
    }
    // 4.2
    // 4.3
    if (menuLayer == 403)
    {
        if (oneRazPosition4_3 == false)
        { // Один раз исполнить. Чтобы появилось в менюшке правильное значение которое в системе
            old_SEChillTime = timer.GetSEChillTime();
            verticalPosition = map(timer.GetSEChillTime(), 0, 30, -180, -210); // Исполнить один раз чтоб галочка соответствовала значению
            oneRazPosition4_3 = true;
        } // Один раз исполнить. Чтобы появилось в менюшке правильное значение которое в системе
        // Ограничители диапазона
        if (verticalPosition > -181)
        {
            verticalPosition = -181;
        }
        if (verticalPosition < -430)
        {
            verticalPosition = -430;
        }
        // Ограничители диапазона

        timer.SetSEChillTime(abs((180 + verticalPosition)));

        if (horizontalPosition == 2)
        { // save
            //Тут должен быть ввод нового значения переменной и сохранения в EEPROM
            writeIntIntoEEPROM(13, timer.GetSEChillTime());

            IsBeSaved_lightOnOff4_3 = true; // Нужно чтобы при выходе не сбрасывалось значение
            saveBlink = true;               // Чтобы моргала надпись save

            sound.BeepReset(); // Cбрасываем пики
            timer.SbrosTimer();// Cбрасываем таймер
            horizontalPosition = 1;         // Вернуть ползунок по горизонтали
        }
        if (horizontalPosition == 0) // back
        {
            if (IsBeSaved_lightOnOff4_3 != true)
            {
                timer.SetSEChillTime(old_SEChillTime);
            }
            menuLayer = 41;
            verticalPosition = 3;
            horizontalPosition = 1;
        }
    }
    // 4.3
    // 4.4
    if (menuLayer == 404)
    {
        // Ограничить вертикальный ползунок при движении вверх
        if (verticalPosition < 1)
        {
            verticalPosition = 2;
        }
        // Ограничить вертикальный ползунок при движении вниз
        if (verticalPosition > 2)
        {
            verticalPosition = 1;
        }

        OldStateLightFromSEMode = OneRazCopy(OldStateLightFromSEMode, light.GetIsChangeLightFromSE());

        if (verticalPosition == 1)
        {
            light.SetIsChangeLightFromSE(ON);
            light.SetDemoLight(ON);
        }
        if (verticalPosition == 2)
        {
            light.SetIsChangeLightFromSE(OFF);
            light.SetDemoLight(OFF);
        }

        if (horizontalPosition == 0) // back
        {
            menuLayer = 41;
            verticalPosition = 4;
            horizontalPosition = 1;
            if (IsBeSaved_lightOnOff4_4 != true)
            {
                light.SetIsChangeLightFromSE(OldStateLightFromSEMode);
            }
            light.SetDemoLight(OFF);
        }
        if (horizontalPosition == 2)
        { // save
            if (verticalPosition == 1)
            {
                light.SetIsChangeLightFromSE(ON);
            }
            if (verticalPosition == 2)
            {
                light.SetIsChangeLightFromSE(OFF);
            }
            saveBlink = true;               // Чтоб надпись save моргала как надо
            IsBeSaved_lightOnOff4_4 = true; // Нужно чтобы при выходе не сбрасывалось значение
            writeBoolIntoEEPROM(17, light.GetIsChangeLightFromSE());
            horizontalPosition = 1;
        }
    }
    // 4.4
}
void Menu::DrawMenu(LightPodsvetka &light, Timer &timer, Sound &sound, const std::vector<int> &airData, int airDataInd, AirData airData_TempHumPress) //,Timer &timer
{
    bool drawLines = false;

    if (menuLayer == 0)
    {
        //Serial.print("verticalPosition:");Serial.print(verticalPosition);
        //Serial.print(" horizontalPosition:");Serial.println(horizontalPosition);
        if (verticalPosition == 1)
        {
            int airDataSize = airData.size();
            int lastInd = (airDataInd + airDataSize - 1) % airDataSize;

            if (horizontalPosition == 1)
            {                       // Если только СO2
                u8g2.clearBuffer(); // clear the internal memory

                u8g2.setFont(u8g2_font_profont29_tf);
                u8g2.setCursor(0, 40);

                u8g2.print(airData[lastInd]); u8g2.print(" Ppm");

                u8g2.setCursor(0, 60);
                u8g2.setFont(u8g2_font_profont10_tf);
                u8g2.print("Temp:");u8g2.print(airData_TempHumPress.GetTemp());u8g2.print("°C   ");
                u8g2.print("Hum:");u8g2.print(airData_TempHumPress.GetHum());u8g2.print("%");                
                
                u8g2.sendBuffer(); // transfer internal memory to the display

            }
            /*
            if (horizontalPosition == 2)
            {
                u8g2.clearBuffer(); // clear the internal memory
                u8g2.setFont(u8g2_font_7x14B_tr);
                //u8g2.drawStr(30, 15 - 3, "Co2+Graph"); //u8g2.drawStr(35+10, 40-3, "Off");  
                u8g2.setCursor(5, 15 - 3);
                u8g2.print(data.GetCo2());

                //u8g2.setCursor(66 + 5, 40);
                u8g2.print(" Ppm");

                u8g2.sendBuffer();                     // transfer internal memory to the display
                FirstInToOnlyGraph = false;            // Перезарядка каждый раз сбрасывать при входе в Only Graph
            } 
           */
            if (horizontalPosition == 2)
            {

                u8g2.clearBuffer(); // clear the internal memory

                u8g2.setFont(u8g2_font_7x14B_tr);
                //u8g2.drawStr(30, 15 - 3, "Only Graph"); //u8g2.drawStr(35+10, 40-3, "Off");
                u8g2.setCursor(5, 15 - 3);
                u8g2.print(airData[lastInd]);
                u8g2.print(" Ppm");

                for (int i = 0; i < airDataSize - 1; i++)
                {
                    int actualInd = (airDataInd + i) % airDataSize;
                    int nextInd = (airDataInd + i + 1) % airDataSize;

                    if (airData[actualInd] != 0 && airData[nextInd] != 0)
                    {
                        int actualDrawY = map(airData[actualInd], 0, 2000, 64, 32);
                        int nextDrawY = map(airData[nextInd], 0, 2000, 64, 32);

                        int actualDrawX = 4 * i;
                        int nextDrawX = 4 * i;

                        if (drawLines)
                            nextDrawX += 4;

                        u8g2.drawLine(actualDrawX, actualDrawY, nextDrawX, nextDrawY);
                    }
                }

                /*
                int PixelPos = map(data.GetCo2(), 0, 2000, 64, 32); // Разрешение: 128 x 64 точек

                if (millis() - timingUpdateGraph > 1000)
                { // Вместо 10000 подставьте нужное вам значение паузы

                    if (FirsVxodGraphGorizont == true)
                    {
                        x0 = x1;
                        y0 = y1;
                    }
                    // Если это первый проход по горизонтали
                    if (FirsVxodGraphGorizont == false)
                    { //Если только началась отрисовка графика слева на право
                        x0 = 0;
                        y0 = 64;
                        FirsVxodGraphGorizont = true;
                    }
                    // Если это первый проход по горизонтали

                    x1 = x0 + 5;
                    y1 = PixelPos;

                    timingUpdateGraph = millis();
           
                }
                u8g2.drawLine(x0, y0, x1, y1);
                if (x0 > 128)
                {
                    // Тут происходит возврат к началу координат графика.
                    FirsVxodGraphGorizont = false;
                    // Тут происходит возврат к началу координат графика.
                    u8g2.clearBuffer();
                    u8g2.setFont(u8g2_font_7x14B_tr);
                    u8g2.drawStr(30, 15 - 3, "Only Graph"); //u8g2.drawStr(35+10, 40-3, "Off");
                }
               */
                u8g2.sendBuffer(); // transfer internal memory to the display
            }

            if (horizontalPosition == 3)
            {
                u8g2.clearBuffer(); // clear the internal memory
                u8g2.setFont(u8g2_font_profont10_tf);

                u8g2.setCursor(0, 10);
                u8g2.print("S.E Mode:");

                u8g2.setCursor(45, 10);
                if (timer.GetSafeEyesMode() == ON)
                {
                    u8g2.print("ON");
                }
                else
                {
                    u8g2.print("OFF");
                }

                // /*
                if (timer.GetWhatDoingNow() == Work)
                {
                    u8g2.setCursor(65, 10);
                    u8g2.print("Work");
                }
                if (timer.GetWhatDoingNow() == Chill)
                {
                    u8g2.setCursor(65, 10);
                    u8g2.print("Chill");
                }
                //Serial.print("timer.GetWhatDoingNow()");
                //Serial.println(timer.GetWhatDoingNow() );
                // */

                //u8g2.drawStr(20, 35-3,"Only Co2");  //"Only Co2" u8g2.drawStr(35+10, 40-3, "Off");

                //FirstInToOnlyGraph = false; // ! Костыль от бага в графике! Переделать график и убрать строку
                //timer.GetTimerTime().sec;

                //timer.Print();

                u8g2.setFont(u8g2_font_profont29_tn);

                u8g2.setCursor(0 + 5, 60);
                u8g2.print(timer.GetTimerTime().hour);
                u8g2.print(":");
                u8g2.print(timer.GetTimerTime().min);
                u8g2.print(":");
                u8g2.print(timer.GetTimerTime().sec);

                //u8g2.drawStr(20, 35-3,"Only Co2");  //"Only Co2" u8g2.drawStr(35+10, 40-3, "Off");
                //u8g2.sendBuffer();          // transfer internal memory to the display
                u8g2.sendBuffer(); // transfer internal memory to the display
            }
        }
        if (verticalPosition == 0) // Тут заставки Rain и Мatrix
        {
            /*
            // Проскролливают циклично заставки если жать только вправо или влево
            if (horizontalPosition < 1)
            {
                horizontalPosition = 2;
            }
            if (horizontalPosition > 2)
            {
                horizontalPosition = 1;
            }
            // Проскролливают циклично заставки если жать только вправо или влево
            */

            if (horizontalPosition == 1)
            {
                u8g2.clearBuffer(); // clear the internal memory
                u8g2.setFont(u8g2_font_7x14B_tr);
                u8g2.drawStr(5, 35 - 3, "Zastavka Rain"); //u8g2.drawStr(35+10, 40-3, "Off");

                for(auto&& drop : drops)
                {
                    drop.MooveDrop();
                    drop.CheckBorder();
                    u8g2.drawLine(drop.GetCoords().x0, drop.GetCoords().y0, drop.GetCoords().x1, drop.GetCoords().y1);
                }
                u8g2.sendBuffer(); 
            }
            if (horizontalPosition == 2)
            {
                u8g2.clearBuffer(); // clear the internal memory
                u8g2.setFont(u8g2_font_7x14B_tr);
                u8g2.drawStr(5, 35 - 3, "Zastavka Matrix"); //u8g2.drawStr(35+10, 40-3, "Off");
                u8g2.sendBuffer();                          // transfer internal memory to the display
            }
        }
    }
    if (menuLayer == 1)
    {
        u8g2.clearBuffer(); // clear the internal memory
        u8g2.setFont(u8g2_font_6x12_tr);
        //u8g2.setFont(u8g2_font_cu12_t_cyrillic);
        u8g2.drawStr(45, 7, " Menu");               // write something to the internal memory
        u8g2.drawStr(5, 25 - 3, "1 Threshold CO2"); // write something to the internal memory
        u8g2.drawStr(5, 35 - 3, "2 Sound");         // write something to the internal memory
        u8g2.drawStr(5, 45 - 3, "3 Backlight");
        u8g2.drawStr(5, 55 - 3, "4 Save Eyes"); // write something to the internal memory
        u8g2.drawTriangle(110 + 20, CursorPosY - 5, 95 + 20, CursorPosY, 110 + 20, CursorPosY + 5);
        u8g2.sendBuffer(); // transfer internal memory to the display
    }
    if (menuLayer == 2)
    {
        u8g2.clearBuffer(); // clear the internal memory
        u8g2.setFont(u8g2_font_6x12_tr);
        //u8g2.setFont(u8g2_font_cu12_t_cyrillic);
        u8g2.drawStr(45, 7, " Menu");    // write something to the internal memory
        u8g2.drawStr(5, 25 - 3, "Exit"); // write something to the internal memory
        /*
        u8g2.drawStr(5, 35 - 3, "2 Sound");         // write something to the internal memory
        u8g2.drawStr(5, 45 - 3, "3 Backlight");
        u8g2.drawStr(5, 55 - 3, "4 Save Eyes"); // write something to the internal memory
        */
        u8g2.drawTriangle(110 + 20, CursorPosY - 5, 95 + 20, CursorPosY, 110 + 20, CursorPosY + 5);
        u8g2.sendBuffer(); // transfer internal memory to the display
    }
    if (menuLayer == 101)
    {
        u8g2.clearBuffer(); // clear the internal memory

        u8g2.setFont(u8g2_font_6x12_tr);         //u8g2.setFont(u8g2_font_7x14B_tr);
        u8g2.drawStr(15, 7, "1.1 Co2 Treshold"); // write something to the internal memory

        u8g2.drawStr(0, 35, "Treshold:");
        u8g2.setFont(u8g2_font_10x20_tr);

        u8g2.setCursor(56, 35);
        u8g2.print(DangerLevelCo2Treshold * 10);

        u8g2.drawTriangle(85 + 12, 28, 88 + 12, 16, 91 + 12, 28);
        u8g2.drawTriangle(85 + 12, 32, 88 + 12, 44, 91 + 12, 32);

        u8g2.setFont(u8g2_font_7x14_tr);

        u8g2.drawTriangle(108, 62, 128, 57, 108, 52); // стрелка под save
        u8g2.drawTriangle(20, 62, 0, 57, 20, 52);     // стрелка по back

        u8g2.setFont(u8g2_font_7x14_tf);
        u8g2.drawStr(46, 60, "0 - 2K");

        u8g2.setFont(u8g2_font_6x12_tr);

        u8g2.drawStr(0, 50, "back");
        //u8g2.drawStr(105, 50, "save");
        DrawSave();
        u8g2.sendBuffer(); // transfer internal memory to the display
    }

    if (menuLayer == 20)
    {

        u8g2.clearBuffer(); // clear the internal memory
        u8g2.setFont(u8g2_font_6x12_tr);
        u8g2.drawStr(30, 7, " 2 Sound ");        // write something to the internal memory
        u8g2.drawStr(0, 25 - 3, "2.1 Activate"); // write something to the internal memory
        u8g2.drawStr(0, 32, "Sound");            // write something to the internal memory

        if (sound.GetState() == Sound::ON)
        {
            u8g2.drawStr(97, 25 - 3, "On");
        }
        else
        {
            u8g2.drawStr(97, 25 - 3, "Off");
        }

        u8g2.drawLine(0, 32 + 5, 105, 32 + 5);

        u8g2.drawStr(0, 32 + 17, "2.2 Thomsing");
        u8g2.drawStr(0, 42 + 17, "else");
        //u8g2.setCursor(97,32+17);
        //u8g2.print(SettingMaxVolumeOnSpeed);
        if (sound.GetState() == Sound::ON)
        {
            u8g2.drawStr(97, 32 + 17, "On");
        }
        else
        {
            u8g2.drawStr(97, 32 + 17, "Off");
        }

        u8g2.drawTriangle(110 + 20, CursorPosY - 5, 95 + 20, CursorPosY, 110 + 20, CursorPosY + 5);
        u8g2.sendBuffer(); // transfer internal memory to the display
    }

    if (menuLayer == 201)
    { // 3.1

        u8g2.clearBuffer(); // clear the internal memory

        u8g2.setFont(u8g2_font_6x12_tr);
        u8g2.drawStr(5, 7, "2.1 Activate Sound"); // write something to the internal memory

        u8g2.setFont(u8g2_font_7x14B_tr);
        u8g2.drawStr(35 + 10, 25 - 3, "On");
        u8g2.drawStr(35 + 10, 40 - 3, "Off");

        // Исполнить один раз чтоб галочка соответствовала значению

        // Исполнить один раз чтоб галочка соответствовала значению
        u8g2.setFont(u8g2_font_7x14_tr);
        if (verticalPosition == 1)
        {
            u8g2.drawStr(95 - 10, 21, "V");
        }
        if (verticalPosition == 2)
        {
            u8g2.drawStr(95 - 10, 21 + 15, "V");
        }

        u8g2.drawTriangle(108, 62, 128, 57, 108, 52);
        u8g2.drawTriangle(20, 62, 0, 57, 20, 52);

        u8g2.setFont(u8g2_font_6x12_tr);

        //u8g2.drawStr(105, 50, "save");
        DrawSave();
        u8g2.drawStr(0, 50, "back");

        u8g2.sendBuffer(); // transfer internal memory to the display
    }

    if (menuLayer == 30)
    {

        u8g2.clearBuffer(); // clear the internal memory
        u8g2.setFont(u8g2_font_6x12_tr);
        u8g2.drawStr(30, 7, " 3 Light ");        // write something to the internal memory
        u8g2.drawStr(0, 25 - 3, "3.1 Activate"); // write something to the internal memory
        u8g2.drawStr(0, 32, "Light");            // write something to the internal memory

        if (light.GetIsOnOrOff() == true)
        {
            u8g2.drawStr(97, 25 - 3, "On");
        }
        else
        {
            u8g2.drawStr(97, 25 - 3, "Off");
        }

        u8g2.drawLine(0, 32 + 5, 105, 32 + 5);

        u8g2.drawStr(0, 32 + 17, "3.2 Smoothly");
        u8g2.drawStr(0, 42 + 17, "Light");
        //u8g2.setCursor(97,32+17);
        //u8g2.print(SettingMaxVolumeOnSpeed);
        if (light.GetSmoothlyOrNot() == Smoothly)
        {
            u8g2.drawStr(97, 32 + 17, "On");
        }
        else
        {
            u8g2.drawStr(97, 32 + 17, "Off");
        }

        //CursorPosY = 18;
        u8g2.drawTriangle(110 + 20, CursorPosY - 5, 95 + 20, CursorPosY, 110 + 20, CursorPosY + 5);
        u8g2.sendBuffer(); // transfer internal memory to the display
    }

    if (menuLayer == 301)
    { // 3.1

        u8g2.clearBuffer(); // clear the internal memory

        u8g2.setFont(u8g2_font_6x12_tr);
        u8g2.drawStr(5, 7, "3.1 Activate Light"); // write something to the internal memory

        u8g2.setFont(u8g2_font_7x14B_tr);
        u8g2.drawStr(35 + 10, 25 - 3, "On");
        u8g2.drawStr(35 + 10, 40 - 3, "Off");

        // Исполнить один раз чтоб галочка соответствовала значению

        // Исполнить один раз чтоб галочка соответствовала значению
        u8g2.setFont(u8g2_font_7x14_tr);
        if (verticalPosition == 1)
        {
            u8g2.drawStr(95 - 10, 21, "V");
        }
        if (verticalPosition == 2)
        {
            u8g2.drawStr(95 - 10, 21 + 15, "V");
        }

        u8g2.drawTriangle(108, 62, 128, 57, 108, 52);
        u8g2.drawTriangle(20, 62, 0, 57, 20, 52);

        u8g2.setFont(u8g2_font_6x12_tr);

        //u8g2.drawStr(105, 50, "save");
        DrawSave();
        u8g2.drawStr(0, 50, "back");

        u8g2.sendBuffer(); // transfer internal memory to the display
    }

    if (menuLayer == 302)
    { // 3.2

        u8g2.clearBuffer(); // clear the internal memory

        u8g2.setFont(u8g2_font_6x12_tr);
        u8g2.drawStr(5, 7, "3.2 Smoothly Light"); // write something to the internal memory

        u8g2.setFont(u8g2_font_7x14B_tr);
        u8g2.drawStr(35 + 10, 25 - 3, "On");
        u8g2.drawStr(35 + 10, 40 - 3, "Off");

        // Исполнить один раз чтоб галочка соответствовала значению

        // Исполнить один раз чтоб галочка соответствовала значению
        u8g2.setFont(u8g2_font_7x14_tr);
        if (verticalPosition == 1)
        {
            u8g2.drawStr(95 - 10, 21, "V");
        }
        if (verticalPosition == 2)
        {
            u8g2.drawStr(95 - 10, 21 + 15, "V");
        }

        u8g2.drawTriangle(108, 62, 128, 57, 108, 52);
        u8g2.drawTriangle(20, 62, 0, 57, 20, 52);

        u8g2.setFont(u8g2_font_6x12_tr);

        //u8g2.drawStr(105, 50, "save");
        DrawSave();
        u8g2.drawStr(0, 50, "back");

        u8g2.sendBuffer(); // transfer internal memory to the display
    }
    if (menuLayer == 40)
    {

        u8g2.clearBuffer(); // clear the internal memory
        u8g2.setFont(u8g2_font_6x12_tr);
        u8g2.drawStr(30, 7, " 4 Eyes ");         // write something to the internal memory
        u8g2.drawStr(0, 25 - 3, "4.1 Activate"); // write something to the internal memory
        u8g2.drawStr(0, 32, "Save Eyes");        // write something to the internal memory

        if (timer.GetSafeEyesMode() == true)
        {
            u8g2.drawStr(97, 25 - 3, "On");
        }
        else
        {
            u8g2.drawStr(97, 25 - 3, "Off");
        }

        u8g2.drawLine(0, 32 + 5, 105, 32 + 5);

        u8g2.drawStr(0, 32 + 17, "4.2 S.E timer");
        u8g2.drawStr(0, 42 + 17, "work set");

        u8g2.setCursor(97, 32 + 17);
        u8g2.print(timer.GetSEWorkTime());
        /*
        if (light.GetSmoothlyOrNot() == Smoothly)
        {
            u8g2.drawStr(97, 32 + 17, "On");
        }
        else
        {
            u8g2.drawStr(97, 32 + 17, "Off");
        }
        */
        //CursorPosY = 18;
        u8g2.drawTriangle(110 + 20, CursorPosY - 5, 95 + 20, CursorPosY, 110 + 20, CursorPosY + 5);
        u8g2.sendBuffer(); // transfer internal memory to the display
    }
    if (menuLayer == 41)
    {

        u8g2.clearBuffer(); // clear the internal memory
        u8g2.setFont(u8g2_font_6x12_tr);
        u8g2.drawStr(30, 7, " 4 Eyes ");          // write something to the internal memory
        u8g2.drawStr(0, 25 - 3, "4.3 S.E timer"); // write something to the internal memory
        u8g2.drawStr(0, 32, "chill set");         // write something to the internal memory
                                                  /*
        if (timer.GetSafeEyesMode() == true){u8g2.drawStr(97, 32 + 17, "On");} 
        else                                {u8g2.drawStr(97, 32 + 17, "Off"); }  
*/
        u8g2.setCursor(97, 25 - 3);
        u8g2.print(timer.GetSEChillTime());

        u8g2.drawLine(0, 32 + 5, 105, 32 + 5);

        u8g2.drawStr(0, 32 + 17, "4.4 Change ");
        u8g2.drawStr(0, 42 + 17, "light from S.E");

        //u8g2.setCursor(97 , 32 + 17);
        //u8g2.print(timer.GetChangeLightFromSEMode() );
        if (light.GetIsChangeLightFromSE() == ON)
        {
            u8g2.drawStr(97, 32 + 17, "On");
        }
        else
        {
            u8g2.drawStr(97, 32 + 17, "Off");
        }

        u8g2.drawTriangle(110 + 20, CursorPosY - 5, 95 + 20, CursorPosY, 110 + 20, CursorPosY + 5);
        u8g2.sendBuffer(); // transfer internal memory to the display
    }

    if (menuLayer == 401)
    { // 4.1

        u8g2.clearBuffer(); // clear the internal memory

        u8g2.setFont(u8g2_font_6x12_tr);
        u8g2.drawStr(5, 7, "4.1 Act. Save Eyes"); // write something to the internal memory

        u8g2.setFont(u8g2_font_7x14B_tr);
        u8g2.drawStr(35 + 10, 25 - 3, "On");
        u8g2.drawStr(35 + 10, 40 - 3, "Off");

        // Исполнить один раз чтоб галочка соответствовала значению

        // Исполнить один раз чтоб галочка соответствовала значению
        u8g2.setFont(u8g2_font_7x14_tr);
        if (verticalPosition == 1)
        {
            u8g2.drawStr(95 - 10, 21, "V");
        }
        if (verticalPosition == 2)
        {
            u8g2.drawStr(95 - 10, 21 + 15, "V");
        }

        u8g2.drawTriangle(108, 62, 128, 57, 108, 52);
        u8g2.drawTriangle(20, 62, 0, 57, 20, 52);

        u8g2.setFont(u8g2_font_6x12_tr);

        //u8g2.drawStr(105, 50, "save");
        DrawSave();
        u8g2.drawStr(0, 50, "back");

        u8g2.sendBuffer(); // transfer internal memory to the display
    }
    if (menuLayer == 402)
    {
        u8g2.clearBuffer(); // clear the internal memory

        u8g2.setFont(u8g2_font_6x12_tr);         //u8g2.setFont(u8g2_font_7x14B_tr);
        u8g2.drawStr(15, 7, "4.2 S.E work set"); //write something to the internal memory

        u8g2.drawStr(0, 35, "Work min:");
        u8g2.setFont(u8g2_font_10x20_tr);

        u8g2.setCursor(56, 35);
        u8g2.print(timer.GetSEWorkTime());

        u8g2.drawTriangle(85 + 12, 28, 88 + 12, 16, 91 + 12, 28);
        u8g2.drawTriangle(85 + 12, 32, 88 + 12, 44, 91 + 12, 32);

        u8g2.setFont(u8g2_font_7x14_tr);

        u8g2.drawTriangle(108, 62, 128, 57, 108, 52); // стрелка под save
        u8g2.drawTriangle(20, 62, 0, 57, 20, 52);     // стрелка по back

        u8g2.setFont(u8g2_font_7x14_tf);
        u8g2.drawStr(26, 60, "0 - 255 min");

        u8g2.setFont(u8g2_font_6x12_tr);

        u8g2.drawStr(0, 50, "back");
        //u8g2.drawStr(105, 50, "save");
        DrawSave();
        u8g2.sendBuffer(); // transfer internal memory to the display
    }
    if (menuLayer == 403)
    {
        u8g2.clearBuffer(); // clear the internal memory

        u8g2.setFont(u8g2_font_6x12_tr);          //u8g2.setFont(u8g2_font_7x14B_tr);
        u8g2.drawStr(15, 7, "4.3 S.E chill set"); //write something to the internal memory

        u8g2.drawStr(0, 35, "Chill min:");
        u8g2.setFont(u8g2_font_10x20_tr);

        u8g2.setCursor(60, 35);
        u8g2.print(timer.GetSEChillTime());

        u8g2.drawTriangle(85 + 12, 28, 88 + 12, 16, 91 + 12, 28);
        u8g2.drawTriangle(85 + 12, 32, 88 + 12, 44, 91 + 12, 32);

        u8g2.setFont(u8g2_font_7x14_tr);

        u8g2.drawTriangle(108, 62, 128, 57, 108, 52); // стрелка под save
        u8g2.drawTriangle(20, 62, 0, 57, 20, 52);     // стрелка по back

        u8g2.setFont(u8g2_font_7x14_tf);
        u8g2.drawStr(26, 60, "1 - 255 min");

        u8g2.setFont(u8g2_font_6x12_tr);

        u8g2.drawStr(0, 50, "back");
        //u8g2.drawStr(105, 50, "save");
        DrawSave();
        u8g2.sendBuffer(); // transfer internal memory to the display
    }
    if (menuLayer == 404)
    { // 4.4

        u8g2.clearBuffer(); // clear the internal memory

        u8g2.setFont(u8g2_font_6x12_tr);
        u8g2.drawStr(5, 7, "4.4 Pereriv light"); // write something to the internal memory

        u8g2.setFont(u8g2_font_7x14B_tr);
        u8g2.drawStr(35 + 10, 25 - 3, "On");
        u8g2.drawStr(35 + 10, 40 - 3, "Off");

        // Исполнить один раз чтоб галочка соответствовала значению

        // Исполнить один раз чтоб галочка соответствовала значению
        u8g2.setFont(u8g2_font_7x14_tr);
        if (verticalPosition == 1)
        {
            u8g2.drawStr(95 - 10, 21, "V");
        }
        if (verticalPosition == 2)
        {
            u8g2.drawStr(95 - 10, 21 + 15, "V");
        }

        u8g2.drawTriangle(108, 62, 128, 57, 108, 52);
        u8g2.drawTriangle(20, 62, 0, 57, 20, 52);

        u8g2.setFont(u8g2_font_6x12_tr);

        //u8g2.drawStr(105, 50, "save");
        DrawSave();
        u8g2.drawStr(0, 50, "back");

        u8g2.sendBuffer(); // transfer internal memory to the display
    }
}

void Menu::Print()
{

    Serial.print(" menuLayer:");
    Serial.print(menuLayer);
    Serial.print(" verticalPosition:");
    Serial.print(verticalPosition);
    Serial.print(" horizontalPosition:");
    Serial.print(horizontalPosition);

    Serial.print(" DangerLevelCo2Treshold:");
    Serial.print(DangerLevelCo2Treshold);

    //Serial.print(" OldStateLight:");Serial.print(States(OldStateLight));
    //Serial.print(" OldStateSmoothly: "); Serial.print(OldStateSmoothly);

    Serial.println(); //*/
}

int Menu::GetMenuLayer()
{
    return menuLayer;
}

void Menu::SetMenuLayer(int value)
{
    menuLayer = value;
}

int16_t Menu::GetVerticalPosition()
{
    return verticalPosition;
}

void Menu::SetVerticalPosition(int16_t value)
{
    verticalPosition = value;
}

int8_t Menu::GetHorizontalPosition()
{
    return horizontalPosition;
}

void Menu::SetHorizontalPosition(int8_t value)
{
    horizontalPosition = value;
}

int16_t Menu::GetDangerLevelCo2Treshold()
{
    return DangerLevelCo2Treshold;
}

void Menu::SetDangerLevelCo2Treshold(int16_t value)
{
    DangerLevelCo2Treshold = value;
}

//void Menu::Drop::DrawDrop(){
//
//}
/*
                    Serial.print(" x:");Serial.print(x); 
                    Serial.print("\t x0:");    Serial.print(x0); Serial.print(" y0:");    Serial.print(y0);
                    Serial.print("\t x1:");    Serial.print(x1); Serial.print(" y1:");    Serial.print(y1);
                    Serial.println();
                    */