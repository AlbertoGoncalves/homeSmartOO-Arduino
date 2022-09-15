//Programa : Medidor de distancia com HC‐SR04
//Autor : Arduino e Cia
#include <Ultrasonic.h> //Carrega a biblioteca Ultrasonic
#include <LiquidCrystal.h> //Carrega a biblioteca LCD
//Define o pino do Arduino a ser utilizado com o pino Trigger do sensor
#define PINO_TRIGGER 13
//Define o pino do Arduino a ser utilizado com o pino Echo do sensor
#define PINO_ECHO 12
//definir pino 9 para o botão 
#define botao 9
#define motor 6

#define TEMPO_ATUALIZACAO 300

#define maximo  50
//Inicializa o sensor ultrasonico
Ultrasonic ultrasonic(PINO_TRIGGER, PINO_ECHO);
//Define os pinos que serão ligados ao LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
void setup()
{
Serial.begin(9600); //Inicializa a serial
lcd.begin(8,2); //Inicializa LCD
lcd.clear(); //Limpa o LCD
pinMode(botao,INPUT_PULLUP);//CONFIGURA O BOTÃO COMO ENTRADA
pinMode(motor,OUTPUT);//CONFIGURA SAIDA PARA O MOTOR
analogWrite(motor,0000);
}
void loop()
{
//DECLARANDO VARIAVEIS   
int cmMsec, inMsec;
int TEMP = 800,CONT = 0, med = 0,med1 = 0;
int medida[maximo];//vetor
boolean valid = true;

//Le os dados do sensor, com o tempo de retorno do sinal
long microsec = ultrasonic.timing();
//Calcula a distancia em centimetros
cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
//Calcula a distancia em polegadas
inMsec = ultrasonic.convert(microsec, Ultrasonic::IN);
//Apresenta os dados, em centimetros, no LCD e na Serial

//PROGRAMA ORIGINAL 
lcd.setCursor(0,0);
lcd.print("C:");
lcd.print(" ");
lcd.setCursor(2,0);
lcd.print(cmMsec);
Serial.print("C:");
Serial.print(cmMsec);
//Apresenta os dados, em polegadas, no LCD e na Serial
lcd.setCursor(0,1);
lcd.print("P:");
lcd.print(" ");
lcd.setCursor(2,1);
lcd.print(inMsec);
Serial.print(", P:");
Serial.println(inMsec);
delay(500);
}

//PROGRAMA ALBERTO JUNIOR

/*
//-------------- PROGRAMA LCD MENSAGEM INICIAR ------------------//

int inicio = 0, tamanho = 0;
boolean alterar = false;
String nome = "PRESSIONE O BOTAO PARA INICIAR O SISTEMA";
while (digitalRead(botao) != LOW)
{
 lcd.clear();//limpa o display LCD  
 if (tamanho < 8)
 { lcd.setCursor(8 - tamanho, 0);// posiciona o cursor na coordenada especificada
 lcd.print(nome.substring(inicio, tamanho));//mostra no LCD
 lcd.setCursor(8 - tamanho, 1);// posiciona o cursor na coordenada especificada
 lcd.print(nome.substring(inicio, tamanho));//mostra no LCD
 tamanho++;
 }
 else
 { if (!alterar)
 { alterar = !alterar;
 tamanho = 8;
 lcd.setCursor(0, 0);
 }
 lcd.setCursor(0, 0);
 lcd.print(nome.substring(inicio, inicio + tamanho));
 lcd.setCursor(0, 1);
 lcd.print(nome.substring(inicio, inicio + tamanho));
 inicio++;
 }
 if (inicio > nome.length())
 { inicio = 0;
 tamanho = 1;
 alterar = !alterar;
 }
 
 delay(TEMPO_ATUALIZACAO);
}

//-------------- PROGRAMA LCD MENSAGEM INICIAR ------------------//
analogWrite(motor,200);
lcd.clear();//limpa o display LCD    
lcd.setCursor(0,0);
lcd.print("INICIAR");
delay(1900);
lcd.setCursor(0,1);
lcd.print("EM:");
delay(TEMP);
//lcd.clear();
lcd.setCursor(3,1);
lcd.print("5");
delay(TEMP);
//lcd.clear();
lcd.setCursor(4,1);
lcd.print("4");
delay(TEMP);
//lcd.clear();
lcd.setCursor(5,1);
lcd.print("3");
delay(TEMP);
//lcd.clear();
lcd.setCursor(6,1);
lcd.print("2");
delay(TEMP);
//lcd.clear();
lcd.setCursor(7,1);
lcd.print("1");
delay(TEMP);
lcd.clear();
analogWrite(motor,1023);
//digitalWrite(motor,HIGH);
delay(100);
//INICIAR COLETA DE MEDIDAS PARA O VETOR
for(int i = 0;i<maximo;i++)
{
//Le os dados do sensor, com o tempo de retorno do sinal
long microsec = ultrasonic.timing();
//Calcula a distancia em centimetros
cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
lcd.clear();
lcd.setCursor(0,0);
lcd.print("MEDIDA");
lcd.print(i+1);
lcd.setCursor(0,1);
lcd.print("C:");
lcd.print(" ");
lcd.setCursor(2,1);
lcd.print(cmMsec);  
Serial.print("C");
Serial.print(i+1);
Serial.print(": ");
Serial.print(cmMsec);
Serial.print("\n");
medida[i] = cmMsec;              
delay(100);
}
//digitalWrite(motor,LOW);
analogWrite(motor,0000);
/*
//MOSTRAR MEDIDAS SALVAS NO VETOR
lcd.clear();
lcd.setCursor(0,0);
lcd.print("MOSTRAR");
delay(TEMP);
lcd.setCursor(0,1);
lcd.print("MEDIDA");
delay(TEMP);
lcd.clear();
for(int IND = 0;IND<maximo;IND++)
{
lcd.clear();  
lcd.setCursor(0,0);
lcd.print("MEDIDA");
lcd.print(IND+1);
lcd.setCursor(0,1);
lcd.print(medida[IND]);
Serial.print("MEDIDA");
Serial.print(IND+1);
Serial.print(": ");
Serial.print(medida[IND]);
Serial.print("\n");
delay(1000);
}


for(int IND = 0;IND<maximo;IND++)
{
medida[med] = medida[IND+1];

  if(valid == true)  //---
  {
  Serial.print("1");  
  Serial.print("\n");
   if(medida[IND] > medida[med])
   {  
     Serial.print("2 ");
     Serial.print("\n");
    while (medida[IND] > medida[med] )
    {
    medida[med++];
    Serial.print("3 ");
    Serial.print("\n");
    }
    valid = false;
    CONT++;
    Serial.print("4 ");
    Serial.print("\n");
   } 
  } 

  if(valid == false)  //+++
  {
   if(medida[IND] < medida[med])
   {  
  
    while (medida[IND] < medida[med] )
    {
    medida[med++];
    }
    valid = true;
    CONT++;
   } 
  }   
  

}

lcd.clear();  
lcd.setCursor(0,0);
lcd.print("N MANGAS");
lcd.setCursor(0,1);
lcd.print(CONT);
Serial.print("N MANGAS:");
Serial.print(CONT);
Serial.print("\n");
delay(9000);

lcd.clear();
lcd.setCursor(0,0);
lcd.print("FIM");
delay(1500);
lcd.clear();

}
*/

