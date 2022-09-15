// Controle a posição de um servomotor pelo uso de um potenciômetro
// por Michal Rinott <http://people.interaction-ivrea.it/m.rinott&gt;

#include <Servo.h>

Servo myservo; // crie objeto Servo para controlar o servomotor

int potpin = 0; // pino analógico usado para conectar o potenciômetro
int val; // variável para ler o valor do pino analógico

void setup() 
   { 
    myservo.attach(9); // ligue o servomotor no pino 9 ao objeto Servo 
    Serial.begin(9600);
   }

void loop() 
   { 
    val = analogRead(potpin); // leia o valor do potenciômetro (valor entre 0 e 1023) 
    val = map(val, 0, 1023, 0, 179); // mapeie para o uso do servo (valor entre 0 and 180     graus) 
    myservo.write(val); // ajuste a posição do servomotor de acordo com o mapeamento
    Serial.println(val);
    delay(15); // aguarde um pouco até o servomotor chegar lá
   }
