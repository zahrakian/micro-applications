#include <Arduino.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
int value = 0;
int randomnum ;
int loworhigh ;
int guess ;

void setup()
{
  lcd.begin(16, 2);
  Serial.begin(9600); 
}

void loop()
{
 value= analogRead(A0);
 randomnum = value %100 ;
 
     int isaval = Serial.available();
      if (isaval){
 guess=Serial.read();

 
if(guess==randomnum)
{loworhigh=3;
lcd.print(guess);
lcd.clear();
         lcd.print(guess);

         lcd.print(" FOUND IT");
       
        Serial.end() ;

      
}


else if(guess>randomnum){
  loworhigh=2;
  lcd.clear();
  lcd.print(guess);


}


else if(guess<randomnum){
      loworhigh=1;
      lcd.clear();
      lcd.print(guess);
}
 Serial.write(loworhigh);
                                   delay(60);
      }

}