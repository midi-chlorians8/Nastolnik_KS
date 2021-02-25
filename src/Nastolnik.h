#pragma once
#include "Arduino.h"
#include <U8g2lib.h>

//#include "SparkFunCCS811.h" //Click here to get the library: http://librarymanager/All#SparkFun_CCS811
#include "MHZ19.h"      
#include "MyMHZ19C.h"


#include <map>
#include <vector>

#include "Menu.h"
#include "Timer.h"
#include "LightPodsvetka.h"
#include "CapacityButtons.h"
#include "Button.h"
#include "Sound.h"
//#include "Graph.h"

#include "AirData.h"
#define RightButtonPin 26
#define LeftButtonPin 32
#define UpButtonPin 4
#define DownButtonPin 5//2 // Оранж провод

enum class ButtonType
{
    Right,
    Left,
    Up,
    Down
};

class Nastolnik
{
private:
    
    //U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2;
    U8G2_SSD1309_128X64_NONAME0_F_4W_SW_SPI u8g2;
    Timer timer;
    LightPodsvetka light;
    Menu menu;
    //CCS811 mySensor;
    MyMHZ19C MHZ19C;
    
    
    CapacityButton capButton; // Создали наши кнопки
    std::map<ButtonType, Button> buttons;
    //std::vector<int> A = {11,2,3,14};

    //std::sort(A.begin(),A.end() ); 
    Sound sound;
    Graph graph;
   
    bool ROMInitSuccess;
    std::vector<int> airDataVect;
    int airDataInd;

    AirData airData_TempHumPress;
public:
    Nastolnik();
    bool IsRomInitSuccess() { return ROMInitSuccess;
    }

    void UpdateButtons();
    void HandleButtonsEvents();

    void UpdateAirData();
    void UpdateMenu();
    void UpdateLight(); 
};