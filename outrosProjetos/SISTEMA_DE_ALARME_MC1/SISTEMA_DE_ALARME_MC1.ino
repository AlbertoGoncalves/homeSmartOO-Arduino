 //Programa : SISTEMA DE ALERME
//Autor : ALBERTO JUNIOR
#include <LiquidCrystal.h> //Carrega a biblioteca LCD
 
#define SINAL_1  22//DEFEITO 1 
#define SINAL_2  23//DEFEITO 2 
#define SINAL_3  24//DEFEITO 3
#define SINAL_4  25//DEFEITO 4
#define SINAL_5  26//DEFEITO 5
#define SINAL_6  27//DEFEITO 6
#define SINAL_7  28//DEFEITO 7
#define SINAL_8  29//DEFEITO 8
#define SINAL_9  30//DEFEITO 9
#define SINAL_10 31//DEFEITO 10
#define SINAL_11 32//DEFEITO 11
#define SINAL_12 33//DEFEITO 12
#define SINAL_13 34//DEFEITO 13
#define SINAL_14 35//DEFEITO 14
#define SINAL_15 36//DEFEITO 15
#define SINAL_16 37//DEFEITO 16
#define SINAL_17 38//DEFEITO 17
#define SINAL_18 39//DEFEITO 18
#define SINAL_19 40//DEFEITO 19
#define SINAL_20 41//DEFEITO 20
#define SINAL_21 42//DEFEITO 21
#define SINAL_22 43//DEFEITO 22
#define SINAL_23 44//DEFEITO 23
#define SINAL_24 45//DEFEITO 24
#define SINAL_25 46//DEFEITO 25
#define SINAL_26 47//DEFEITO 26
#define SINAL_27 48//DEFEITO 27
#define SINAL_28 49//DEFEITO 28
#define SINAL_29 50//DEFEITO 29
#define SINAL_30 51//DEFEITO 30
#define SINAL_31 52//DEFEITO 31
#define SINAL_32 53//DEFEITO 32

#define SINAL_33  6//DEFEITO 33
#define SINAL_34  7//DEFEITO 34



#define bozina  8//bozina

//definir pino 9 para o botão PARA BOZINA 
#define Bbozina 9
//definir pino 8 para o botão LIMPAR DISPLAY
#define Bdisplay 10
#define led      13
#define TEMPO_ATUALIZACAO 300
#define TEMPO_ATU 1100


// tamanho do dispaly caso troque o msm informar novas medidas aqui 
#define   N_LINHA 16
#define   N_COLUNA 2
//Define os pinos que serão ligados ao LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup()
{
  
////////-----lcd-----//////// 
lcd.begin(N_LINHA,N_COLUNA); //Inicializa LCD
lcd.clear(); //Limpa o LCD
////////-----lcd-----////////


////////-----Serial-----//////// 

Serial.begin(9600); //Inicializa a serial

////////-----Serial-----////////

// ENTRADAS

   //BOTÕES
pinMode(Bbozina   ,INPUT_PULLUP); //CONFIGURA O BOTÃO COMO ENTRADA
pinMode(Bdisplay  ,INPUT_PULLUP); //CONFIGURA O BOTÃO COMO ENTRADA
   //BOTÕES
   
   //SINAL 5VOLTS PROBLEMAS
   pinMode(SINAL_1    ,INPUT_PULLUP); //CONFIGURA PORTA COMO ENTRADA DE SINAL
   pinMode(SINAL_2    ,INPUT_PULLUP); //CONFIGURA PORTA COMO ENTRADA DE SINAL
   pinMode(SINAL_3    ,INPUT_PULLUP); //CONFIGURA PORTA COMO ENTRADA DE SINAL
   pinMode(SINAL_4    ,INPUT_PULLUP); //CONFIGURA PORTA COMO ENTRADA DE SINAL
   pinMode(SINAL_5    ,INPUT_PULLUP); //CONFIGURA PORTA COMO ENTRADA DE SINAL
   pinMode(SINAL_6    ,INPUT_PULLUP); //CONFIGURA PORTA COMO ENTRADA DE SINAL
   pinMode(SINAL_7    ,INPUT_PULLUP); //CONFIGURA PORTA COMO ENTRADA DE SINAL
   pinMode(SINAL_8    ,INPUT_PULLUP); //CONFIGURA PORTA COMO ENTRADA DE SINAL
   pinMode(SINAL_9    ,INPUT_PULLUP); //CONFIGURA PORTA COMO ENTRADA DE SINAL
   pinMode(SINAL_10   ,INPUT_PULLUP); //CONFIGURA PORTA COMO ENTRADA DE SINAL
   pinMode(SINAL_11   ,INPUT_PULLUP); //CONFIGURA PORTA COMO ENTRADA DE SINAL
   pinMode(SINAL_12   ,INPUT_PULLUP); //CONFIGURA PORTA COMO ENTRADA DE SINAL
   pinMode(SINAL_13   ,INPUT_PULLUP); //CONFIGURA PORTA COMO ENTRADA DE SINAL
   pinMode(SINAL_14   ,INPUT_PULLUP); //CONFIGURA PORTA COMO ENTRADA DE SINAL
   pinMode(SINAL_15   ,INPUT_PULLUP); //CONFIGURA PORTA COMO ENTRADA DE SINAL
   pinMode(SINAL_16   ,INPUT_PULLUP); //CONFIGURA PORTA COMO ENTRADA DE SINAL
   pinMode(SINAL_17   ,INPUT_PULLUP); //CONFIGURA PORTA COMO ENTRADA DE SINAL
   pinMode(SINAL_18   ,INPUT_PULLUP); //CONFIGURA PORTA COMO ENTRADA DE SINAL
   pinMode(SINAL_19   ,INPUT_PULLUP); //CONFIGURA PORTA COMO ENTRADA DE SINAL
   pinMode(SINAL_20   ,INPUT_PULLUP); //CONFIGURA PORTA COMO ENTRADA DE SINAL  
   // fica pendente a configuração da forma de entrada pra os outros defeitos 
   
   //SINAL 5VOLTS PROBLEMAS

// ENTRADAS

//SAIDAS
 
  pinMode     (bozina,OUTPUT);  //CONFIGURA SAIDA PARA A BOZINA
  analogWrite (bozina,0000)  ;  //GARANTIR VALOR ZERO A SAIDA PARA BOZINA
  pinMode     (led,OUTPUT)   ;  //CONFIGURA SAIDA PARA O LED 
  digitalWrite(led,LOW)   ;
  
//SAIDAS
}

  //variaveis globais todas os loop's podem velas 
  int cont1 = 0;
  int cont2 = 0;
  int cont3 = 0; 
  int cont4 = 0;
  int cont5 = 0;
  int cont6 = 0;
  int cont7 = 0; 
  int cont8 = 0;
  int cont9 = 0;
  int cont10 = 0;
  int cont11 = 0; 
  int cont12 = 0;
  int cont13 = 0;
  int cont14 = 0;
  int cont15 = 0; 
  int cont16 = 0;
  int cont17 = 0;
  int cont18 = 0;
  int cont19 = 0; 
  int cont20 = 0;
  int cont21 = 0;
  int cont22 = 0;
  int cont23 = 0; 
  int cont24 = 0;
  int cont25 = 0;
  int cont26 = 0;
  int cont27 = 0; 
  int cont28 = 0;
  int cont29 = 0;
  int cont30 = 0;
  int cont31 = 0; 
  int cont32 = 0;
  int cont33 = 0;
  int cont34 = 0;

void Desliga_Bozina()
  {if (digitalRead(Bbozina) == LOW ) // verifica se o botão para buzina foi apertado
           {
            if( analogRead(bozina) > 0)
              {analogWrite(bozina,0);
               Serial.println("desliga bozina botão");
               Serial.println(analogRead(bozina));
              }
           }
  }//void Desliga_Bozina


void liga_Bozina()
  {// liga a bozina  (1023 valor maximo = 5volts)
   analogWrite(bozina,100);
  }//void liga_Bozina
  
   

  
void loop()  {
//-------------- PROGRAMA LCD MENSAGEM INICIAR ------------------//
analogWrite(bozina,1023);
delay(500);  
analogWrite(bozina,0000);
delay(200);  
analogWrite(bozina,1023);
delay(500);  
analogWrite(bozina,0000);
delay(200); 
analogWrite(bozina,1023);
delay(500);  
analogWrite(bozina,0000);

//CHAMA inicia alarme
verifi_defeito();
}

void verifi_defeito()
  {
    String MSG = "SISTEMA DE ALERME MC";
  //zera todos os problemas quando o display é limpo
    cont1  = 0;
    cont2  = 0;
    cont3  = 0; 
    cont4  = 0;
    cont5  = 0;
    cont6  = 0;
    cont7  = 0; 
    cont8  = 0;
    cont9  = 0;
    cont10 = 0;
    cont11 = 0; 
    cont12 = 0;
    cont13 = 0;
    cont14 = 0;
    cont15 = 0; 
    cont16 = 0;
    cont17 = 0;
    cont18 = 0;
    cont19 = 0; 
    cont20 = 0;
    cont21 = 0;
    cont22 = 0;
    cont23 = 0; 
    cont24 = 0;
    cont25 = 0;
    cont26 = 0;
    cont27 = 0; 
    cont28 = 0;
    cont29 = 0;
    cont30 = 0;
    cont31 = 0; 
    cont32 = 0;
    cont33 = 0;
    cont34 = 0;
  
  while (Test_def()) // enquanto o teste de problemas(Test_def()) retornar verdadeiro continua na msg se for negativo sai da msg e mostra o defeito    
  {
   Serial.println("SISTEMA DE ALERME MC");//mostra na serial
   
   delay(TEMPO_ATUALIZACAO);
  }  
  defeito();
  }//verifi_defeito()







void defeito() 
  {
  //DECLARANDO VARIAVEIS   
  //MSG
  int inicio = 0, tamanho = 0;
  boolean alterar = false;
  String MSG2 = "";

   //-------------- PROGRAMA LCD MENSAGEM INICIAR ------------------//
  
  liga_Bozina();
  int lin = 0;
  Serial.println("achou defeito!");
  
  
  
  
   while  (digitalRead(Bdisplay) != LOW)  // enquanto não aperta no botão limpa dispaly mostra erros
     {  
     MSG2 = MSG2 + " "; //chama função para atualizar string com erros 
  
     Desliga_Bozina();
     Test_def();
     
     lcd.setCursor(0,0);// posiciona o cursor na coordenada especificada
     lcd.print(MSG2.substring(lin, (lin + N_LINHA)));//mostra no LCD
     lin = lin + N_LINHA;
     delay(300);
   
     Desliga_Bozina();
     Test_def();
     
     if(lin >= MSG2.length() )
         {lin = 0;}
       
     Desliga_Bozina();
  
     lcd.setCursor(0,1);// posiciona o cursor na coordenada especificada
     lcd.print(MSG2.substring(lin , lin + N_LINHA));//mostra no LCD 
     delay(TEMPO_ATU);
   
     Desliga_Bozina();
   
     if (lin >= MSG2.length() )
       {lin = 0;}
   
     Desliga_Bozina();
    
    
     lcd.setCursor(0,0);// posiciona o cursor na coordenada especificada
     lcd.print("                ");//limpa somente a linha 0 do display obs: precisa ter os 16 caracteres em branco para apagar a linha toda 
    
     Desliga_Bozina();
     
     delay(50);
   
     lcd.setCursor(0,1);// posiciona o cursor na coordenada especificada
     lcd.print("                ");//limpa somente a linha 1 do display obs: precisa ter os 16 caracteres em branco para apagar a linha toda 
  
  
     Desliga_Bozina();
   }//// enquanto não aperta no botão limpa dispaly mostra erros
  
   
   lcd.clear();//limpa o display LCD
   Serial.println("limpa lcd");
   analogWrite(bozina,0000); // desliga buzina
   verifi_defeito(); //retonar para loop 2 = voltar para msg sistema de alerme  

 }//void defeito() 

 
 
 
 
 
 
 boolean Test_def()//verifica todos os dfeitos
{ boolean valid = true;
  Serial.println("Test_def");
  
  if(digitalRead(SINAL_1) == LOW ) 
   {Serial.println("teste1");
    liga_Bozina();
    valid = false;}
    
  if(digitalRead(SINAL_2) == LOW)
   {Serial.println("teste2");
     valid = false;}
    
  if(digitalRead(SINAL_3) == LOW)
   {Serial.println("teste3");
    valid = false;}
  
  if(digitalRead(SINAL_4) == LOW)
   {Serial.println("teste4");
     valid = false;}
     
  if(digitalRead(SINAL_5) == LOW)
   {Serial.println("teste5");
     valid = false;}
     
  if(digitalRead(SINAL_6) == LOW)
   {Serial.println("teste6");
     valid = false;}
  
  if(digitalRead(SINAL_7) == LOW)
   {Serial.println("teste7");
     valid = false;}
  
  if(digitalRead(SINAL_8) == LOW)
   {Serial.println("teste8");
     valid = false;}
  
  if(digitalRead(SINAL_9) == LOW)
   {Serial.println("teste9");
     valid = false;}
  
  if(digitalRead(SINAL_10) == LOW)
   {Serial.println("teste10");
     valid = false;}
  
  if(digitalRead(SINAL_11) == LOW)
   {Serial.println("teste11");
     valid = false;}
  
  if(digitalRead(SINAL_12) == LOW)
   {Serial.println("teste12");
     valid = false;}
  
  if(digitalRead(SINAL_13) == LOW)
   {Serial.println("teste13");
     valid = false;}   

    if(digitalRead(SINAL_14) == LOW ) 
   {Serial.println("teste14");
     valid = false;}
    
  if(digitalRead(SINAL_15) == LOW)
   {Serial.println("teste15");
     valid = false;}
    
  if(digitalRead(SINAL_16) == LOW)
   {Serial.println("teste16");
     valid = false;}
  
  if(digitalRead(SINAL_17) == LOW)
   {Serial.println("teste17");
     valid = false;}
     
  if(digitalRead(SINAL_18) == LOW)
   {Serial.println("teste18");
     valid = false;}
     
  if(digitalRead(SINAL_19) == LOW)
   {Serial.println("teste19");
     valid = false;}
  
  if(digitalRead(SINAL_20) == LOW)
   {Serial.println("teste20");
     valid = false;}
  /*
  if(digitalRead(SINAL_21) == LOW)
   {Serial.println("\n");
     Serial.println("teste21");
     valid = false;}
  
  if(digitalRead(SINAL_22) == LOW)
   {Serial.println("\n");
     Serial.println("teste22");
     valid = false;}
  
  if(digitalRead(SINAL_23) == LOW)
   {Serial.println("\n");
     Serial.println("teste23");
     valid = false;}
  
  if(digitalRead(SINAL_24) == LOW)
   {Serial.println("\n");
     Serial.println("teste24");
     valid = false;}
  
  if(digitalRead(SINAL_25) == LOW)
   {Serial.println("\n");
     Serial.println("teste25");
     valid = false;}
  
  if(digitalRead(SINAL_26) == LOW)
   {Serial.println("\n");
     Serial.println("teste26");
     valid = false;} 
    */ 
     
     // PENDENTE ADICIONAR OS OUTROS SINAIS VAI DEPENDER DE COMO SERA MEDIDO OS OUTROS DEFEITOS 
     
digitalWrite(led,HIGH);
delay(1);  
digitalWrite(led,LOW);
return(valid);
}

 


