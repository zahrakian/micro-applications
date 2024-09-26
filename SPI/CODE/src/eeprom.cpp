#include "eeprom.h"

void write_eeprom(word address, byte data) 
{
     digitalWrite(SLAVESELECT,LOW);
    SPI.transfer(WREN); //write enable
    digitalWrite(SLAVESELECT,HIGH);
    delay(10);
   digitalWrite(SLAVESELECT,LOW);
    SPI.transfer(WRITE);//write instruction
    SPI.transfer((char)(address >> 8));    //send MSByte address first
    SPI.transfer((char)address);           //send LSByte address
    SPI.transfer(data);
   digitalWrite(SLAVESELECT,HIGH); //release chip

  //wait for eeprom to finish writing

  delay(3000);
}

byte read_eeprom(word EEPROM_address)
{
  //READ EEPROM

  byte data;

  digitalWrite(SLAVESELECT,LOW);

  SPI.transfer(READ);          //transmit read opcode

  SPI.transfer((char)(EEPROM_address>>8));   //send MSByte address first

  SPI.transfer((char)(EEPROM_address));      //send LSByte address

  data = SPI.transfer(0xFF); //get data byte

  digitalWrite(SLAVESELECT,HIGH); //release chip, signal end transfer

  return data;
}

