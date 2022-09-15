//Programa : Teste HC-SR04 e biblioteca Ultrasonic
//Autor : Adilson Thomsen

#include <Ultrasonic.h>

//Define os pinos do Arduino ligados ao Trigger e Echo
#define PINO_TRG  13
#define PINO_ECHO 12

//Inicializa o sensor ultrasonico nos pinos especificados
Ultrasonic ultrasonic(PINO_TRG, PINO_ECHO);

void setup()
{
  //Inicializa a serial
  Serial.begin(9600);
}

void loop()
{
  //Variaveis para guardar os valores em 
  //cm (cmSec) e polegadas (inMsec)
  float cmMsec, inMsec;
  
  //Le os valores do sensor ultrasonico
  long microsec = ultrasonic.timing();
  //Atribui os valores em cm ou polegadas as variaveis
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  inMsec = ultrasonic.convert(microsec, Ultrasonic::IN);
  
  //Mostra os valores na serial
  Serial.print("Centimetros: ");
  Serial.print(cmMsec);
  Serial.print(" - Polegadas: ");
  Serial.println(inMsec);
  
  //Aguarda 1 segundo e reinicia o processo
  delay(1000);
}
