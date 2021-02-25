#pragma once

int readIntFromEEPROM(int address);

void writeIntIntoEEPROM(int address, int number);

bool readBoolFromEEPROM(int address);

void writeBoolIntoEEPROM(int address, bool boolean);

bool EEPROMBegin(int memorySize);
/*
int EEPROMReadByte(int address);

void writeByteIntoEEPROM(int address, unsigned char  data)
*/