#include "EEPROMUtil.h"
#include "EEPROM.h"

int readIntFromEEPROM(int address)
{
    return ((int)EEPROM.read(address) << 24) +
           ((int)EEPROM.read(address + 1) << 16) +
           ((int)EEPROM.read(address + 2) << 8) +
           (int)EEPROM.read(address + 3);
}

void writeIntIntoEEPROM(int address, int number)
{
    EEPROM.write(address, (number >> 24) & 0xFF);
    EEPROM.write(address + 1, (number >> 16) & 0xFF);
    EEPROM.write(address + 2, (number >> 8) & 0xFF);
    EEPROM.write(address + 3, number & 0xFF);
    EEPROM.commit();
}
bool readBoolFromEEPROM(int address)
{
    return (bool)EEPROM.read(address);
}
void writeBoolIntoEEPROM(int address, bool boolean){
    EEPROM.write(address , boolean );
    EEPROM.commit();
}

byte readByteFromEEPROM(int address)
{
    return EEPROM.read(address);
}
void writeByteIntoEEPROM(int address, byte data){
    EEPROM.write(address , data );
    EEPROM.commit();
}


bool EEPROMBegin(int memorySize)
{
    return EEPROM.begin(memorySize);
}

