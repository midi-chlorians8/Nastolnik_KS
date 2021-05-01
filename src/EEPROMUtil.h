#pragma once
#include "Arduino.h"

int readIntFromEEPROM(int address);
void writeIntIntoEEPROM(int address, int number);

bool readBoolFromEEPROM(int address);
void writeBoolIntoEEPROM(int address, bool boolean);

byte readByteFromEEPROM(int address);
void writeByteIntoEEPROM(int address, byte data);


bool EEPROMBegin(int memorySize);
/*
EEPROM MAP
Number   Type_Data      What is
21       byte           Timer.sec
*/