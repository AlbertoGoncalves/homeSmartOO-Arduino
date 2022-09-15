#include <IRremote.h>
//#include <IRremoteInt.h>

  const int RECEBE_PINO = 2; // pino 6 no arduino    
  int ledverde = 7;// led no pino 10    
  int ledamarelo = 6;    
  int ledvermelho = 5;    
  IRrecv ir_recebe(RECEBE_PINO); // declarando a variável do sensor    
  decode_results codigo_recebido; // resultado    
  void setup()    
  {    
  Serial.begin(9600); //mostra o resultado no computador    
  ir_recebe.enableIRIn(); // inicia a recepção    
  pinMode(ledverde, OUTPUT); //defini led como saída    
  pinMode(ledamarelo, OUTPUT);    
  pinMode(ledvermelho, OUTPUT);    
  }    
  void loop() {    
  if (ir_recebe.decode(&codigo_recebido)) {//verifica se um codigo foi recebido    
   if (codigo_recebido.value != 0 ){   
   Serial.println(codigo_recebido.value, HEX); //mostra no serial o resultado    
   }   
   //tem que colocar o 0x antes do numero hexadecimal, pois só assim para poder comparar no if    
   //liga led verde    
   if ((codigo_recebido.value == 0x39C618E7) || (codigo_recebido.value == 0xFF30CF)){// verifica se foi pressionado o numero 1 dos controles    
   digitalWrite(ledverde, HIGH);    
   delay(500);    
   }    
   //desliga led verde    
   if ((codigo_recebido.value == 0x39C658A7) || (codigo_recebido.value == 0xFF10EF)){// verifica se foi pressionado o numero 4 dos controles    
   digitalWrite(ledverde, LOW);    
   delay(500);    
   }    
   //liga led amarelo    
   if ((codigo_recebido.value == 0x39C69867) || (codigo_recebido.value == 0xFF18E7)){// verifica se foi pressionado o numero 2 dos controles    
   digitalWrite(ledamarelo, HIGH);    
   delay(500);    
   }    
   //desliga led amarelo    
   if ((codigo_recebido.value == 0x39C628D7) || (codigo_recebido.value == 0xFF38C7)){// verifica se foi pressionado o numero 5 dos controles    
   digitalWrite(ledamarelo, LOW);    
   delay(500);    
   }    
   //liga led vermelho    
   if ((codigo_recebido.value == 0x39C6D02F) || (codigo_recebido.value == 0xFF7A85)){// verifica se foi pressionado o numero 3 dos controles    
   digitalWrite(ledvermelho, HIGH);   
   delay(500);    
   }    
   //desliga led vermelho    
   if ((codigo_recebido.value == 0x39C6E01F) || (codigo_recebido.value == 0xFF5AA5)){// verifica se foi pressionado o numero 6 dos controles    
   digitalWrite(ledvermelho, LOW);    
   delay(500);    
   }    
   ir_recebe.resume(); // recebe o próximo código   
   delay(200);    
  }    
  }   

