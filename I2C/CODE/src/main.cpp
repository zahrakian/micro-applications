#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
void setup()
{
  lcd.begin(16, 2);
   Wire.beginTransmission(104); // 1101000 is device address
  Wire.write(0); 
    Wire.write(0); // 0 sec
   Wire.write(54); // 36
    Wire.write(9); // 9
    Wire.write(0); 
    Wire.write(6);//6
    Wire.write(3); // 3
    Wire.write(33); // 21 
    Wire.endTransmission();
  Serial.begin(9600);

}

void loop()
{ 

  Wire.beginTransmission(104); 
  Wire.write(0);
  Wire.endTransmission();
  Wire.requestFrom(104, 7);
  if(Wire.available()) {
   int sec=Wire.read(); 
  int min =Wire.read(); 
   int hour= Wire.read();
   int dayofweek = Wire.read();
   int day= Wire.read();
   int month= Wire.read();
   int year= Wire.read();
       
    sec = (((sec & B11110000)>>4)*10 + (sec & B00001111));
    min = (((min & B11110000)>>4)*10 + (min & B00001111));
    hour   = (((hour & B00110000)>>4)*10 + (hour & B00001111)); 
    day    = (((day & B00110000)>>4)*10 + (day & B00001111)); 
    month   = (((month & B00010000)>>4)*10 + (month & B00001111)); 
    year    = (((year & B11110000)>>4)*10 + (year & B00001111));
    
    lcd.setCursor (0,0);
    lcd.print("DATE :");
    lcd.print(day);
    lcd.print("/");
    lcd.print(month);
    lcd.print("/");
     lcd.print("20"); 
    lcd.print(year);
    lcd.setCursor (0,1);
    lcd.print("TIME :");
    lcd.print(hour);
    lcd.print(":");
    lcd.print(min);
    if (hour <12)
        lcd.print("AM");
    else 
            lcd.print("PM");
  } 
}