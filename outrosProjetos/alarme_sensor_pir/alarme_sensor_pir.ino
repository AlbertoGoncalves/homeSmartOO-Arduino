
#define leds    3
#define sensor  7
#define bozina  2  
//int pirState = LOW; 
//int val = 0; 

void setup() {

pinMode(leds,   OUTPUT);
pinMode(bozina, OUTPUT);
pinMode(sensor, INPUT); 

digitalWrite(leds, LOW);
digitalWrite(bozina, HIGH);
Serial.begin(9600);
}
boolean VALID = true;
void loop(){


if ( (digitalRead(sensor) == LOW) && (VALID == false)  ) { 
  VALID = true;
  Serial.println("Movimento detectado! mas nao alarme");}



if (digitalRead(sensor) == HIGH) { 
  
Serial.println("Movimento detectado!");

if (VALID == true){    

   VALID = false;


digitalWrite(bozina, LOW);
delay(100);
digitalWrite(bozina, HIGH);
delay(90);

digitalWrite(bozina, LOW);
delay(100);
digitalWrite(bozina, HIGH);
delay(90);

digitalWrite(bozina, LOW);
delay(100);
digitalWrite(bozina, HIGH);

}
if (VALID == false){    

digitalWrite(leds,   HIGH);
delay(40);
digitalWrite(leds,   LOW);
delay(40);
}


}//if movimento

} //void
