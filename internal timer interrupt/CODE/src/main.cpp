#include <Arduino.h> 

int value = 0 ; 
int toggle =0 ;
void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
   pinMode (4 , OUTPUT) ; 
 pinMode (A0 , INPUT) ; 

  cli() ; 
  TCCR1A = 0 ;
  TCCR1B = 0 ;  
  TCNT1 = 0 ; 
  OCR1A = 1023 ; 
  TCCR1B |= (1<<WGM12) | (1 << CS11) ; 
  TIMSK1 |= (1 << OCIE1A) ; 
  sei () ; 

 
}
ISR (TIMER1_COMPA_vect)
{
    if (toggle==1){
       toggle = 0 ; 

         digitalWrite(4, HIGH);
          OCR1A = map(value, 0, 1023, 1023*0.1, 1023*0.9);

    }

    else { 
        toggle = 1 ; 
                 digitalWrite(4, LOW);
                 OCR1A = 1023 -map(value, 0, 1023, 1023*0.1, 1023*0.9);
        
    }

}

void loop() {
  // put your main code here, to run repeatedly:
    value = analogRead(A0) ; 
      Serial.println(value);


 
}