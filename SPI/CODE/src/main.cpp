#include <LiquidCrystal.h>
#include <Keypad.h>
#include "eeprom.h"
using namespace std ; 
#define DATAOUT 11 //MOSI
#define DATAIN  12 //MISO
#define SPICLOCK  13 //sck
#define SLAVESELECT 10 //ss

char key ;
String myAddress ; 
String myData ; 
bool addressIsValid ;
bool addressOrData=false ;
word storeAddress=0;
byte readdata;
const byte ROWS = 4; 
const byte COLS = 3;
char keys[ROWS][COLS] = {
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'},
    {'*','0','#'}
};

byte rowPins[ROWS] = {4, 3, 2, 0};
byte colPins[COLS] = {7, 6, 5}; 
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );



void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  Serial.begin(9600);
  pinMode(DATAOUT, OUTPUT);
  pinMode(DATAIN, INPUT);
  pinMode(SPICLOCK,OUTPUT);
  pinMode(SLAVESELECT,OUTPUT);
  SPI.begin();

  digitalWrite(SLAVESELECT,HIGH); //disable device

}


void loop() {
     key = keypad.getKey();
    if (key) {
      if (key =='*'){
          if(! addressOrData){
             addressIsValid= (myAddress.toInt() < 65536) ?true:false ;
             if(addressIsValid){
            addressOrData=true ;
            storeAddress = myAddress.toInt();
             myAddress="";
             }
            else {
               lcd.clear();
               lcd.print("Invalid address");
                myAddress = "";}

            }
            else
            {   addressOrData = false;
                byte storedata = myData.toInt();
                write_eeprom(storeAddress, storedata);
                myData = "";
                lcd.clear();
                lcd.print(storedata);
                lcd.print(" stored in");
                lcd.setCursor(0, 1);
                lcd.print(storeAddress);
            }


      }
      else if (key =='#'){
       addressIsValid= (myAddress.toInt() < 65536) ?true:false ;
        if(addressIsValid){
         word address = myAddress.toInt();
         readdata = read_eeprom(address);
             lcd.setCursor(0, 1);

         lcd.print("data:");
        lcd.print(readdata);
        myAddress = "";
      } 
        else{
       lcd.clear();
        lcd.print("Invalid address");
        myAddress = "";
        }


      }
      else{
        if(addressOrData){

        myData +=key;
        lcd.clear();
        lcd.print("Data:");
        lcd.print(myData);
        }
        else{
          myAddress +=key;
          lcd.clear();
          lcd.print("Address:");
          lcd.print(myAddress);
        }
      }        
    }
    
}

