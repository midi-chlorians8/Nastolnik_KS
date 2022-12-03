#include "CapacityButtons.h"
#define printDebug
extern bool waitOneMinGlobal;
bool quickFixNoAutoStartTimer = false;
#include "Timer.h"

CapacityButton::CapacityButton()
{

}

CapacityButton& CapacityButton::IsPressed(Menu &menu,Timer &timer)
{
    //Serial.print("millis:");Serial.print(millis());
    //Serial.print(" TimePress:");Serial.print(TimePress);
    //Serial.print(" touchRead:");Serial.println(touchRead(StartWorkTimePin));

    if (touchRead(StartWorkTimePin) < 30)
    { // 30 - середина между 70 и 10. Считаю за границу пересечения. Вобще это чуствительность
        //TouchBtn = true;

        // Один раз начать замер времени нажатия
        if (OneRazTouch == false)
        {
            TimePress = millis(); // Захват времени начала нажатия
            
            OneRazTouch = true;
        }
        // Один раз начать замер времени нажатия
        if (millis() - TimePress > LONGCLICK_TIME)
        {
            if (IsBeLongTouch == false)
            {
                /*
                Serial.print("\tmillis(): ");
                Serial.print(millis());

                Serial.print("\tTimePress: ");
                Serial.print(TimePress);
*/
                Serial.println("\tLONGCLICK"); waitOneMinGlobal = false;
                TimePress = millis();

                IsBeLongTouch = true;
                SensorState = LongClicked;

                menu.SetMenuLayer(0);
                menu.SetHorizontalPosition(3);
                menu.SetVerticalPosition(1);
            }
        }
        if (millis() - TimePress > SUPERLONGCLICK)
        {
            if (IsBeLongTouch2 == false)
            {
                #ifdef printDebug
                /*
                Serial.print("\tmillis(): ");
                Serial.print(millis());

                Serial.print("\tTimePress: ");
                Serial.print(TimePress);
                */
                Serial.println("\tSuperLongClick");
                #endif
                TimePress = millis();

                IsBeLongTouch2 = true;
                SensorState = SuperLongClick;
            }
        }
    }
    else
    {
       
        if (millis() - TimePress > CLICK_TIME and IsBeLongTouch == false)
        {
            #ifdef printDebug
            
            Serial.print("StartWorkTimePin"); Serial.print(touchRead(StartWorkTimePin));
            Serial.print("\tmillis(): "); Serial.print(millis());           
            Serial.print("\tTimePress: "); Serial.print(TimePress);
            
            Serial.println("\tCLICK");
            #endif
            SensorState = Clicked;

            //!menu.SetMenuLayer(0); //Вернуть для функционала верхней сенс кнопки таймер время работы за ПК
            //!menu.SetHorizontalPosition(3); //Вернуть для функционала верхней сенс кнопки таймер время работы за ПК
            //!menu.SetVerticalPosition(1); //Вернуть для функционала верхней сенс кнопки таймер время работы за ПК
            OneRazTouch = false; // Перезаряд захват времени при косании. Сдесь мы отпустили - и перезаряд

            timer.SetShowContinue(false);

            {// DoublePressChek
            // DoublePressChek
                // Захватили время когда нажат каждый следущий клик
                if(counter%2 != 0){
                    doubleClickTimeOne = millis();
                }
                else{
                    doubleClickTimeTwo = millis();
                }
                counter++;
                // Захватили время когда нажат каждый следущий клик
                #ifdef printDebug
                /*
                Serial.print("\tdoubleClickTimeOne: ");
                Serial.print(doubleClickTimeOne);
                Serial.print("\tdoubleClickTimeTwo: ");
                Serial.print(doubleClickTimeTwo);
                Serial.println("");
                */
                #endif
                // Анализируем вычитанием был ли двойной клик
                // Serial.print("Double click:"); Serial.println(abs(doubleClickTimeOne-doubleClickTimeTwo));
                if(doubleClickTimeOne>doubleClickTimeTwo){
                    result = doubleClickTimeOne - doubleClickTimeTwo;
                }
                if(doubleClickTimeOne<doubleClickTimeTwo){
                    result = doubleClickTimeTwo - doubleClickTimeOne;
                }


                if(   result < 260   ){
                    #ifdef printDebug
                    Serial.println("Double click!");
                    #endif
                    SensorState = DoubleClicked;
                }
                // Анализируем вычитанием был ли двойной клик
            // DoublePressChek
            }

        }
        IsBeLongTouch = false;  // Перезаряд один раз вывести долгок нажатие
        IsBeLongTouch2 = false; // SuperLongClick Перезаряд
        TimePress = millis();
    }

    // Обработка сенсорных кнопок
    return *this;
}
void CapacityButton::Print(Menu &menu, bool Endl)
{
    /*
    Serial.print("Вертикаль:");
    Serial.print(menu.GetVerticalPosition());

    Serial.print(" Горизонталь:");
    Serial.print(menu.GetHorizontalPosition());

    Serial.print(" MenuLayer:");
    Serial.print(menu.GetMenuLayer());
    */
    if (Endl)
    {
        Serial.println();
    }
}

void DoublePressChek(){
    
}