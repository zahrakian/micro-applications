#include<Arduino.h>
#include <LiquidCrystal.h>
#include <Keypad.h>
#include <string.h>
using namespace std ; 

char key ;
int savedpass = 1234;
String  passinput = "" ;
bool flag = false ;
int passlen ;
volatile const byte buttonpin = 2 ;

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'},
    {'*','0','#'}
};

byte rowPins[ROWS] = {10, 9, 8, 7}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {13, 12, 11}; //connect to the column pinouts of the keypad

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


void printpass(){

if(flag){

    lcd.clear() ; 
    lcd.setCursor(0,0);
    lcd.print(passinput);

}
else {

    lcd.clear() ; 
    lcd.setCursor(0,0);
const char * passinputchar = passinput.c_str() ; 
 passlen = strlen(passinputchar) ; 
    for (int i =0 ; i<passlen ; i++)
       lcd.print('*');


}

}
void deletechar(){

const char * passinputchar = passinput.c_str() ; 
 passlen = strlen(passinputchar) ; 
 passinput[passlen-1] = '\0';
    printpass() ; 


   }

 
void submitpass(){
   const char * passinputchar = passinput.c_str() ; 

     int numericpassinput = atoi(passinputchar)-atoi('0');

    if (numericpassinput ==savedpass){
           lcd.clear() ; 
    lcd.setCursor(0,0);
    lcd.print("right password");
    delay(1000) ; 
    passinput = "" ;
const char * passinputchar = passinput.c_str() ; 
 passlen = strlen(passinputchar) ; 
     lcd.clear() ; 
    lcd.setCursor(0,0);

        }
    else {
        lcd.clear() ; 
    lcd.setCursor(0,0);
    lcd.print("wrong password");
    delay(1000) ; 
    passinput = "" ;
const char * passinputchar = passinput.c_str() ; 
 passlen = strlen(passinputchar) ;      lcd.clear() ; 
    lcd.setCursor(0,0);
    }

}

void changeflag()
{
flag = !flag ;
printpass();

}

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  pinMode(buttonpin , INPUT_PULLUP);
  attachInterrupt (digitalPinToInterrupt(buttonpin),changeflag,RISING) ;


}


void loop() {
     key = keypad.getKey();
    if (key) {
        switch (key)
        {case('#'):
        deletechar();
        break ;
         case('*'):
        submitpass();
         break ;
         default :  
        passinput+=key ; 
        printpass() ; 
      
        
    }
   
     

        
    }
    
}
