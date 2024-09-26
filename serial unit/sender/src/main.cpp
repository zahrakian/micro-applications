#include <Arduino.h>

int loworhigh ;  
int first = 1;	
int last = 100;	    
int middle;		
int guess;

void setup()
{
  Serial.begin(9600); 
}


void loop()
{ 

	while (first <= last)
	{
	
		middle = (first + last) / 2;
		guess= middle ; 
	
    Serial.write(guess);
	delay(160);
	int isaval = Serial.available();
		if (isaval){

   loworhigh= Serial.read();                                
		
			if (1 == loworhigh)
			{
				first = middle + 1;
			}
			else if (2 == loworhigh)
			{
				last = middle - 1;
			}
      	else if (3 == loworhigh)
			{
       Serial.end() ;
			}}
		}
	}