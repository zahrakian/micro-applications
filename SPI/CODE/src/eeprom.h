#pragma once
#include <Arduino.h>
#include <SPI.h>
//opcodes
#define WREN 6
#define WRDI 4
#define READ 3
#define WRITE 2
#define SLAVESELECT 10 

void write_eeprom(word EEPROM_address, byte EEPROM_data) ;
byte read_eeprom(word EEPROM_address);
