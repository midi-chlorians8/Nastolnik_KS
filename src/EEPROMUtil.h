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
int EEPROMReadByte(int address);

void writeByteIntoEEPROM(int address, unsigned char  data)
*/