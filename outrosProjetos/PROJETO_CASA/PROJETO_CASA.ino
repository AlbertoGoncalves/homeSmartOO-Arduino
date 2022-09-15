#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <IRremote.h>
#include "ESP8266.h"
#include "DS1307.h"
//#include "RTClib.h"

#define LIGA    LOW
#define DESLIGA HIGH

#define LIMITE      70 //QUARTO 1 LUZ 1 
#define COLUNA     4 //QUARTO 1 LUZ 2

#define R1_L1_Q1      22 //QUARTO 1 LUZ 1 
#define R2_L2_Q1      23 //QUARTO 1 LUZ 2 
#define R3_L3_Q1      24 //QUARTO 1 LUZ 3
#define R4_L4_Q1      25 //QUARTO 1 LUZ 4

#define R9_T1_Q1      26 //QUARTO 1 TOMADA 1
#define RA_T2_Q1      27 //QUARTO 1 TOMADA 2
#define RB_T3_Q1      28 //QUARTO 1 TOMADA 3
#define RC_T4_Q1      29 //QUARTO 1 TOMADA 4


#define R1_L1_Q2      30 //QUARTO 2 LUZ 1 
#define R2_L2_Q2      31 //QUARTO 2 LUZ 2 
#define R3_L3_Q2      32 //QUARTO 2 LUZ 3
#define R4_L4_Q2      33 //QUARTO 2 LUZ 4

#define R5_T1_Q2      34 //QUARTO 2 TOMADA 1
#define R6_T2_Q2      35 //QUARTO 2 TOMADA 2
#define R7_T3_Q2      36 //QUARTO 2 TOMADA 3
#define R8_T4_Q2      37 //QUARTO 2 TOMADA 4


#define R1_L1_Q3      38 //QUARTO 3 LUZ 1 
#define R2_L2_Q3      39 //QUARTO 3 LUZ 2 
#define R3_L3_Q3      40 //QUARTO 3 LUZ 3
#define R4_L4_Q3      41 //QUARTO 3 LUZ 4

#define R5_T1_Q3      42 //QUARTO 3 TOMADA 1
#define R6_T2_Q3      43 //QUARTO 3 TOMADA 2
#define R7_T3_Q3      44 //QUARTO 3 TOMADA 3
#define R8_T4_Q3      45 //QUARTO 3 TOMADA 4


#define R1_L1_Q4      46 //QUARTO 4 LUZ 1 
#define R2_L2_Q4      47 //QUARTO 4 LUZ 2 
#define R3_L3_Q4      48 //QUARTO 4 LUZ 3
#define R4_L4_Q4      49 //QUARTO 4 LUZ 4

#define R5_T1_Q4      50 //QUARTO 4 TOMADA 1
#define R6_T2_Q4      51 //QUARTO 4 TOMADA 2
#define R7_T3_Q4      52 //QUARTO 4 TOMADA 3
#define R8_T4_Q4      53 //QUARTO 4 TOMADA 4

#define S1_PIR_Q1  2 //Pino ligado ao sensor PIR (SENSOR 1_PIR_QUARTO 1 )
#define S2_PIR_Q2  3 //Pino ligado ao sensor PIR (SENSOR 2_PIR_QUARTO 2 )
#define S1_PIR_Q3  4 //Pino ligado ao sensor PIR (SENSOR 1_PIR_QUARTO 1 )
#define S2_PIR_Q4  5 //Pino ligado ao sensor PIR (SENSOR 2_PIR_QUARTO 2 )

#define BOZINA_Q1  6 //BOZINA






//------------------------relogio--------------------------//
 //Modulo RTC DS1307 ligado as portas A4 e A5 do Arduino 
 DS1307 rtc(A1, A2);
 //RTC_DS1307 RTC;
//------------------------relogio--------------------------//

//_______________________CONTROLE_________________________//
  IRsend irsend; //variável para poder enviar o código a TV   
  const int ledIR = 9; 
  //inicia o botão com o status 0    
  int buttonState = 0; 
//_______________________CONTROLE_________________________//


//------------------------wifi--------------------------// 
#define CH_PD 7
#define RST   8
#define GPIO0 10
//Coloque nos campos indicados o nome e senha da sua rede WiFi
#define SSID        "TP-LINK_AJ"
#define PASSWORD    "AJ121212"

//Cria objeto de conexão wifi com o módulo, usando a Serial1 do Mega.
  ESP8266 wifi(Serial3);
//------------------------wifi--------------------------//


//------------------------DISPLAY--------------------------//
  // Inicializa o display no endereco 0x27
  LiquidCrystal_I2C lcd(0x27,20,4);
  //------------------------DISPLAY--------------------------//








void setup()
{ 

  //------------------------relogio--------------------------//
//Aciona o relogio
  rtc.halt(false);
  
  //Definicoes do pino SQW/Out
  rtc.setSQWRate(SQW_RATE_1);
  rtc.enableSQW(true);
  
  //As linhas abaixo setam a data e hora do modulo
  //e podem ser comentada apos a primeira utilizacao
  //rtc.setDOW(SUNDAY);      //Define o dia da semana
  //rtc.setTime(20,12,00);     //Define o horario
  //rtc.setDate(14,05,2017);  //Define o dia, mes e ano

  //MONDAY   - segunda 
  //TUESDAY   - terça
  //WEDNESDAY - quarta
  //THURSDAY  - quinta
  //FRIDAY    - sexta 
  //SATURDAY  - sabado
  //SUNDAY    - domingo
  
  
  
//Wire.begin();
//    RTC.begin();    
//    // RTC initialization
//  RTC.begin();
//  if (!RTC.isrunning()){
//    // data e hora ajustar como a data e hora do computador PC
//    rtc.adjust(DateTime(__DATE__, __TIME__)); 
//  }
  //------------------------relogio--------------------------//
  
  
 //------------------------PORTAS--------------------------//
  pinMode(R1_L1_Q1,   OUTPUT); //Define o pino como saida (QUARTO 01)
  pinMode(R2_L2_Q1,   OUTPUT); //Define o pino como saida
  pinMode(R3_L3_Q1,   OUTPUT); //Define o pino como saida
  pinMode(R4_L4_Q1,   OUTPUT); //Define o pino como saida
  
  pinMode(R9_T1_Q1,   OUTPUT); //Define o pino como saida (QUARTO 01)
  pinMode(RA_T2_Q1,   OUTPUT); //Define o pino como saida
  pinMode(RB_T3_Q1,   OUTPUT); //Define o pino como saida
  pinMode(RC_T4_Q1,   OUTPUT); //Define o pino como saida
    
    
  pinMode(R1_L1_Q2,   OUTPUT); //Define o pino como saida (QUARTO 02 = COZINHA)
  pinMode(R2_L2_Q2,   OUTPUT); //Define o pino como saida
  pinMode(R3_L3_Q2,   OUTPUT); //Define o pino como saida
  pinMode(R4_L4_Q2,   OUTPUT); //Define o pino como saida  
  
  pinMode(R5_T1_Q2,   OUTPUT); //Define o pino como saida (QUARTO 02 = COZINHA)
  pinMode(R6_T2_Q2,   OUTPUT); //Define o pino como saida
  pinMode(R7_T3_Q2,   OUTPUT); //Define o pino como saida
  pinMode(R8_T4_Q2,   OUTPUT); //Define o pino como saida
  
  
  pinMode(R1_L1_Q3,   OUTPUT); //Define o pino como saida (QUARTO 03)
  pinMode(R2_L2_Q3,   OUTPUT); //Define o pino como saida
  pinMode(R3_L3_Q3,   OUTPUT); //Define o pino como saida
  pinMode(R4_L4_Q3,   OUTPUT); //Define o pino como saida
  
  pinMode(R5_T1_Q3,   OUTPUT); //Define o pino como saida (QUARTO 03)
  pinMode(R6_T2_Q3,   OUTPUT); //Define o pino como saida
  pinMode(R7_T3_Q3,   OUTPUT); //Define o pino como saida
  pinMode(R8_T4_Q3,   OUTPUT); //Define o pino como saida
  
  
  pinMode(R1_L1_Q4,   OUTPUT); //Define o pino como saida (QUARTO 04)
  pinMode(R2_L2_Q4,   OUTPUT); //Define o pino como saida
  pinMode(R3_L3_Q4,   OUTPUT); //Define o pino como saida
  pinMode(R4_L4_Q4,   OUTPUT); //Define o pino como saida
  
  pinMode(R5_T1_Q4,   OUTPUT); //Define o pino como saida (QUARTO 04)
  pinMode(R6_T2_Q4,   OUTPUT); //Define o pino como saida
  pinMode(R7_T3_Q4,   OUTPUT); //Define o pino como saida
  pinMode(R8_T4_Q4,   OUTPUT); //Define o pino como saida
  
  pinMode(S1_PIR_Q1, INPUT);   //Define pino sensor como entrada  (QUARTO 01)
  pinMode(S2_PIR_Q2, INPUT);   //Define pino sensor como entrada  (QUARTO 02 = COZINHA)
  
  digitalWrite(R1_L1_Q1, DESLIGA);
  digitalWrite(R2_L2_Q1, DESLIGA);
  digitalWrite(R3_L3_Q1, DESLIGA);
  digitalWrite(R4_L4_Q1, DESLIGA);
  
  digitalWrite(R9_T1_Q1, DESLIGA);
  digitalWrite(RA_T2_Q1, DESLIGA);
  digitalWrite(RB_T3_Q1, DESLIGA);
  digitalWrite(RC_T4_Q1, DESLIGA);
  
  digitalWrite(R1_L1_Q2, DESLIGA);
  digitalWrite(R2_L2_Q2, DESLIGA);
  digitalWrite(R3_L3_Q2, DESLIGA);
  digitalWrite(R4_L4_Q2, DESLIGA);

  digitalWrite(R5_T1_Q2, DESLIGA);
  digitalWrite(R6_T2_Q2, DESLIGA);
  digitalWrite(R7_T3_Q2, DESLIGA);
  digitalWrite(R8_T4_Q2, DESLIGA);
  //------------------------PORTAS--------------------------//
  
  

  //------------------------DISPLAY--------------------------//
  
  // Inicializa o display no endereco 0x27
     lcd.init(); 
  //------------------------DISPLAY--------------------------//
  
  
  //------------------------SERIAL--------------------------//
  Serial.begin(115200); //Inicializa a serial
  Serial2.begin(115200); //Inicializa a serial
  Serial3.begin(115200); //Inicializa a serial
 //------------------------SERIAL--------------------------//
 
 
   //------------------------wifi--------------------------//
    pinMode(CH_PD,OUTPUT);
    pinMode(RST,OUTPUT);
    pinMode(GPIO0,OUTPUT);
    pinMode(BOZINA_Q1,   OUTPUT); //Define o pino como saida
      
    digitalWrite(CH_PD,HIGH); //setado em ALTO - operacao normal
    digitalWrite(RST,HIGH); //setado em ALTO - operhttp://www.embarcados.com.br/arduino-mega-2560/acao normal
    digitalWrite(GPIO0,HIGH); //setado em ALTO - operacao normal 
    reset_wifi();
   //------------------------wifi--------------------------//
 

} //void setup()



//--------variaveis globais todas os loop's podem velas-------------//
String HORA_SIST;
int    indice = 0; 
String HORA_ACAO[LIMITE][COLUNA];//vetor
int    LED = 1; // 1 LIGADO // 2 DESLIGADO
//------------------------DISPLAY----------------------------------//
int linha = -1;
//------------------------DISPLAY----------------------------------//



//------------------------QUARTO 1----------------------------------//
boolean A_L1_Q1 = true; //(A_R_L_Q1 == auto_rele_quarto1_luz)
boolean A_L2_Q1 = false; 
boolean A_L3_Q1 = false; 
boolean A_L4_Q1 = false;

boolean C_L1_Q1 = false; //(C_R_L_Q1 == chave_rele_quarto1_luz 1)
boolean C_L2_Q1 = false; 
boolean C_L3_Q1 = false; 
boolean C_L4_Q1 = false;

boolean C_T1_Q1 = false; //(C_R_L_Q1 == chave_rele_quarto1_luz 1)
boolean C_T2_Q1 = false; 
boolean C_T3_Q1 = false; 
boolean C_T4_Q1 = false;

boolean A_T1_Q1 = false; //(A_R_L_Q1 == auto_rele_quarto1_luz)
boolean A_T2_Q1 = false; 
boolean A_T3_Q1 = false; 
boolean A_T4_Q1 = false;

//SENSOR
boolean HORA_vild_Q1 = true;
String  HORA_S1_PIR_Q1;
int     TEMP_AUTO_Q1 = 1;
//SENSOR


//------------------------QUARTO 1----------------------------------//



//------------------------QUARTO 2----------------------------------//

//QUARTO 2
boolean A_L1_Q2 = false; //(A_R_L_Q1 == auto_rele_quarto1_luz)
boolean A_L2_Q2 = false; 
boolean A_L3_Q2 = false; 
boolean A_L4_Q2 = false;

boolean C_L1_Q2 = false; //(C_R_L_Q1 == chave_rele_quarto1_luz 1)
boolean C_L2_Q2 = false; 
boolean C_L3_Q2 = false; 
boolean C_L4_Q2 = false;

boolean C_T1_Q2 = false; //(C_R_L_Q1 == chave_rele_quarto1_luz 1)
boolean C_T2_Q2 = false; 
boolean C_T3_Q2 = false; 
boolean C_T4_Q2 = false;

boolean A_T1_Q2 = false; //(A_R_L_Q1 == auto_rele_quarto1_luz)
boolean A_T2_Q2 = false; 
boolean A_T3_Q2 = false; 
boolean A_T4_Q2 = false;


//SENSOR
boolean HORA_vild_Q2 = true;
String  HORA_S1_PIR_Q2;
int     TEMP_AUTO_Q2 = 5;
//SENSOR



//------------------------QUARTO 2----------------------------------//


//------------------------QUARTO 3----------------------------------//
boolean A_L1_Q3 = false; //(A_R_L_Q1 == auto_rele_quarto1_luz)
boolean A_L2_Q3 = false; 
boolean A_L3_Q3 = false; 
boolean A_L4_Q3 = false;

boolean C_L1_Q3 = false; //(C_R_L_Q1 == chave_rele_quarto1_luz 1)
boolean C_L2_Q3 = false; 
boolean C_L3_Q3 = false; 
boolean C_L4_Q3 = false;

boolean C_T1_Q3 = false; //(C_R_L_Q1 == chave_rele_quarto1_luz 1)
boolean C_T2_Q3 = false; 
boolean C_T3_Q3 = false; 
boolean C_T4_Q3 = false;

boolean A_T1_Q3 = false; //(A_R_L_Q1 == auto_rele_quarto1_luz)
boolean A_T2_Q3 = false; 
boolean A_T3_Q3 = false; 
boolean A_T4_Q3 = false;

//SENSOR
boolean HORA_vild_Q3 = true;
String  HORA_S1_PIR_Q3;
int     TEMP_AUTO_Q3 = 3;
//SENSOR

//------------------------QUARTO 3----------------------------------//




//------------------------QUARTO 4----------------------------------//
boolean A_L1_Q4 = false; //(A_R_L_Q1 == auto_rele_quarto1_luz)
boolean A_L2_Q4 = false; 
boolean A_L3_Q4 = false; 
boolean A_L4_Q4 = false;

boolean C_L1_Q4 = false; //(C_R_L_Q1 == chave_rele_quarto1_luz 1)
boolean C_L2_Q4 = false; 
boolean C_L3_Q4 = false; 
boolean C_L4_Q4 = false;

boolean C_T1_Q4 = false; //(C_R_L_Q1 == chave_rele_quarto1_luz 1)
boolean C_T2_Q4 = false; 
boolean C_T3_Q4 = false; 
boolean C_T4_Q4 = false;

boolean A_T1_Q4 = false; //(A_R_L_Q1 == auto_rele_quarto1_luz)
boolean A_T2_Q4 = false; 
boolean A_T3_Q4 = false; 
boolean A_T4_Q4 = false;

//SENSOR
boolean HORA_vild_Q4 = true;
String  HORA_S1_PIR_Q4;
int     TEMP_AUTO_Q4 = 3;
//SENSOR


//------------------------QUARTO 4----------------------------------//


//--------variaveis globais todas os loop's podem velas-------------//












//------------------------LCD()----------------------------------//
  void LUZ_LED(){
   
   if (LED == 1){ 
   lcd.noBacklight(); 
   Serial.println("Desliga Led LCD");
   LED = 2;
   }
   else{
   lcd.backlight();
   Serial.println("Liga Led LCD");
   LED = 1; }
  }
//------------------------LCD()----------------------------------//




//------------------------FUNC_COMANDO()----------------------------------//


  void FUNC_COMANDO(String comando, int AGENTE){

 int  Vld_P      = 1; // VALIDAÇÃO PARA PERFIL

/*
String comando;
String comando1 = comando_wifi();
String comando2 = leStringSerial();

if ( comando1 != "" ){
Serial.println("comando1");  
comando = comando1;
}
else{
//Serial.println("comando2");  
comando = comando2;
}
*/

//#Q1*L1*L*D0000*L0000@  luz ou tomada TIPO 01
String V_INI1, COMODO1, V_11, COMPONENTE1, V_21, ACAO1, V_31, AUTODESLIGA1, V_41, AUTOLIGA1, V_FIN1,DIAS,V_FIN21 ;

V_INI1       = comando.substring(0,1);
COMODO1      = comando.substring(1,3);
V_11         = comando.substring(3,4);
COMPONENTE1  = comando.substring(4,6);
V_21         = comando.substring(6,7);
ACAO1        = comando.substring(7,8);
V_31         = comando.substring(8,9);
AUTODESLIGA1 = comando.substring(9,14);
V_41         = comando.substring(14,15);
AUTOLIGA1    = comando.substring(15,20);
V_FIN1       = comando.substring(20,21);
DIAS         = comando.substring(21,28);
V_FIN21      = comando.substring(28,29);

/*
Serial.println(comando);
Serial.println(V_INI1);
Serial.println(COMODO1);
Serial.println(V_11);
//Serial.println(DISPOSITIVO);
//Serial.println(V_2);
Serial.println(COMPONENTE1);
Serial.println(V_21);
Serial.println(ACAO1);
Serial.println(V_31);
Serial.println(AUTODESLIGA1);
Serial.println(V_41);
Serial.println(AUTOLIGA1);
Serial.println(V_FIN1);
Serial.println(DIAS);
Serial.println(V_FIN21);

Serial.println(COMODO1 + COMPONENTE1 + ACAO1 + AUTODESLIGA1 + AUTOLIGA1 + DIAS);
Serial.println(V_INI1 + COMODO1 + V_11 + COMPONENTE1 + V_21 + ACAO1 + V_31 + AUTODESLIGA1 +V_41+ AUTOLIGA1+V_FIN1+V_FIN21);
 //COMODO + DISPOSITIVO + COMPONENTE + ACAO + AUTODESLIGA + AUTOLIGA #Q1*R1*L1*L*D0000*L0000@ = 24   
delay(3000);
*/


//#Q1*HOME000*XXXXXX*D0000*L0000@  controle remoto  TIPO 02
String V_INI2, COMODO2, V_12, COMPONENTE2, V_22, ACAO2, V_32, AUTODESLIGA2, V_42, AUTOLIGA2, V_FIN2;

V_INI2 = comando.substring(0,1);
COMODO2 = comando.substring(1,3);
V_12 = comando.substring(3,4);
COMPONENTE2 =  comando.substring(4,11);
V_22 = comando.substring(11,12);
ACAO2 =  comando.substring(12,18);
V_32 = comando.substring(18,19);
AUTODESLIGA2 =  comando.substring(19,24);
V_42 = comando.substring(24,25);
AUTOLIGA2 =  comando.substring(25,30);
V_FIN2 = comando.substring(30,31);

/*
Serial.println(comando);
Serial.println(V_INI2);
Serial.println(COMODO2);
Serial.println(V_12);
Serial.println(COMPONENTE2);
Serial.println(V_22);
Serial.println(ACAO2);
Serial.println(V_32);
Serial.println(AUTODESLIGA2);
Serial.println(V_42);
Serial.println(AUTOLIGA2);
Serial.println(V_FIN2);

Serial.println(COMODO2 + COMPONENTE2 + ACAO2 + AUTODESLIGA2 + AUTOLIGA2);
Serial.println(V_INI2 + COMODO2 +V_12+ COMPONENTE2 +V_22+ ACAO2 +V_32+ AUTODESLIGA2 +V_42+ AUTOLIGA2+V_FIN2);
 //COMODO + DISPOSITIVO + COMPONENTE + ACAO + AUTODESLIGA + AUTOLIGA #Q1*R1*L1*L*D0000*L0000@ = 24   
delay(3000);
*/


if ( (V_INI1+COMODO1) == "#HR") //VALIDAÇÃO DIGITOS VERIFICADORES DO PROTOCOLO
   {
   
   //#HR*10*10*10@    
   //As linhas abaixo setam a data e hora do modulo
   //e podem ser comentada apos a primeira utilizacao
   //  rtc.setDOW(MONDAY);      //Define o dia da semana
   Serial.println(comando.substring(4,6) + comando.substring(7,9) );
   
   int hora = atoi(comando.substring(4,6).c_str());
   int minuto = atoi(comando.substring(7,9).c_str());
    
    rtc.setTime(hora,minuto,00);     //Define o horario
   //  rtc.setDate(03,04,2017);  //Define o dia, mes e ano
   
   }// FIM 
   
                                     
if ( (V_INI1+V_11+V_21+V_31+V_41+V_FIN1) == "#****@") //VALIDAÇÃO DIGITOS VERIFICADORES DO PROTOCOLO
   {
     //Serial.println("valido");
    if (COMODO1 ==  "Q1") // SE O COMODO É IGUAL AO Q1=QUARTO1 ENTRA NO BLOCO DE IFs DESSE QUARTO 
    {
      Serial.println("Q1");
               if (COMPONENTE1.substring(0,1) == "L")  // SE O COMPONENTE É IGUAL AO L = LUZ ENTRA NO BLOCO DE IFs DE LUZES
                   Serial.println("LUZ");
                   
                   
                   if ( ACAO1 == "L") //ATIVA OU NAO FUNÇÃO AUTO DE LUZES
                     {
                        if ( ((COMPONENTE1) == "L1")) // RELE_1 LIZ_1
                           {
                            if (digitalRead(R1_L1_Q1) == DESLIGA)  
                               {Serial.println("liga R_L_Q1_1 chave");
                                lcd.setCursor(0,linha_lcd());
                                lcd.print("Liga R1_L1_Q1");         
                                digitalWrite(R1_L1_Q1, LIGA);
                                C_L1_Q1 = true;  
                             }

                                 else    
                                   {Serial.println("desliga R_L_Q1_1 chave");
                                    lcd.setCursor(0,linha_lcd());
                                    lcd.print("Desliga R1_L1_Q1");
                                    digitalWrite(R1_L1_Q1, DESLIGA);
                                    C_L1_Q1 = false; 
                                   } 
                        } 
    
                        if (  ((COMPONENTE1) == "L2") )
                         {
                             if (digitalRead(R2_L2_Q1) == DESLIGA)  
                               {Serial.println("liga R2_L2_Q1 chave");
                                lcd.setCursor(0,linha_lcd());
                                lcd.print("Liga R2_L2_Q1");
                                digitalWrite(R2_L2_Q1, LIGA);
                                C_L2_Q1 = true;  
                             }
    
                                 else    
                                   {Serial.println("desliga R2_L2_Q1 chave");
                                    lcd.setCursor(0,linha_lcd());
                                    lcd.print("Desliga R2_L2_Q1");
                                    digitalWrite(R2_L2_Q1, DESLIGA);
                                    C_L2_Q1 = false; 
                                   } 
                          }
    
                        if (  ((COMPONENTE1) == "L3") )
                         {
                           if (digitalRead(R3_L3_Q1) == DESLIGA)  
                               {Serial.println("liga R3_L3_Q1 chave");
                                lcd.setCursor(0,linha_lcd());
                                lcd.print("Liga R3_L3_Q1");
                                digitalWrite(R3_L3_Q1, LIGA);
                                C_L3_Q1 = true;
                               }
    
                                 else    
                                   {Serial.println("desliga R_L_Q1_3 chave");
                                    lcd.setCursor(0,linha_lcd());
                                    lcd.print("Desliga R3_L3_Q1");
                                    digitalWrite(R3_L3_Q1, DESLIGA);
                                    C_L3_Q1 = false;
                                   } 
                         }
    
                        if (((COMPONENTE1) == "L4") )
                         {
                             if (digitalRead(R4_L4_Q1) == DESLIGA)  
                               {Serial.println("liga R4_L4_Q1 chave");
                                lcd.setCursor(0,linha_lcd());
                                lcd.print("Liga R4_L4_Q1");
                                digitalWrite(R4_L4_Q1, LIGA);
                                C_L4_Q1 = true;
                               }
    
                                else    
                                  {Serial.println("desliga R4_L4_Q1 chave");
                                   lcd.setCursor(0,linha_lcd());
                                   lcd.print("Desliga R4_L4_Q1");
                                   digitalWrite(R4_L4_Q1, DESLIGA);
                                   C_L4_Q1 = false;
                                  } 
                          }
    
                       // PERFIL ILUMINAÇÃO QUARTO 1
                         if ( (COMPONENTE1 == "L5") ) // ILUMINAÇÃO PRINCIPAL  L5=PERFIL 1 
                          {Vld_P = 1 ;
                             if ((digitalRead(R1_L1_Q1) == LIGA) && (digitalRead(R4_L4_Q1) == LIGA) && (Vld_P == 1))  
                              {Serial.println("DESLIGA R_L_Q1_1 e R_L_Q1_4 PERFIL PRINCIPAL");
                               lcd.setCursor(0,linha_lcd());
                               lcd.print("DESLIGA PERFIL 01");
                               digitalWrite(R1_L1_Q1, DESLIGA);
                               C_L1_Q1 = false;
                               digitalWrite(R4_L4_Q1, DESLIGA);
                               C_L4_Q1 = false;
                               Vld_P++ ;
                               } 

                          if ( ((digitalRead(R1_L1_Q1) == DESLIGA) || (digitalRead(R4_L4_Q1) == DESLIGA)) && (Vld_P == 1))  
                           {Serial.println("LIGA R_L_Q1_1 e R_L_Q1_4 PERFIL PRINCIPAL");
                            lcd.setCursor(0,linha_lcd());
                            lcd.print("LIGA PERFIL 01");
   
                            //DESLIGA LUZES DO PERFIL 2
                            digitalWrite(R2_L2_Q1, DESLIGA);
                            C_L2_Q1 = false;
                            digitalWrite(R3_L3_Q1, DESLIGA);
                            C_L3_Q1 = false;
                             
                            //LIGA LUZES DO PERFIL 1
                            digitalWrite(R1_L1_Q1, LIGA);
                            C_L1_Q1 = true;
                            digitalWrite(R4_L4_Q1, LIGA); 
                            C_L4_Q1 = true;
                            Vld_P++ ; 
                            }
                          }


                      if (  (COMPONENTE1 == "L6") ) // ILUMINAÇÃO QUARTO 1  L6 = DECORATIVA PERFIL 2 
                       {Vld_P = 1 ;
                         if ((digitalRead(R2_L2_Q1) == LIGA) && (digitalRead(R3_L3_Q1) == LIGA) && (Vld_P == 1))  
                          {Serial.println("DESLIGA R_L_Q1_1 e R_L_Q1_4 PERFIL PRINCIPAL");
                           lcd.setCursor(0,linha_lcd());
                           lcd.print("DESLIGA PERFIL 02");
                           digitalWrite(R2_L2_Q1, DESLIGA);
                           C_L2_Q1 = false;
                           digitalWrite(R3_L3_Q1, DESLIGA);
                           C_L3_Q1 = false;
                           Vld_P++ ;
                          } 
    
                          if ( ((digitalRead(R2_L2_Q1) == DESLIGA) || (digitalRead(R3_L3_Q1) == DESLIGA)) && (Vld_P == 1))  
                           {Serial.println("LIGA R_L_Q1_1 e R_L_Q1_4 PERFIL PRINCIPAL");
                            lcd.setCursor(0,linha_lcd());
                            lcd.print("LIGA PERFIL 02");
   
                            //DESLIGA LUZES DO PERFIL 1
                            digitalWrite(R1_L1_Q1, DESLIGA);
                            C_L1_Q1 = false;
                            digitalWrite(R4_L4_Q1, DESLIGA);
                            C_L4_Q1 = false;
                            
                            //LIGA LUZES DO PERFIL 2
                            digitalWrite(R2_L2_Q1, LIGA);
                            C_L2_Q1 = true;  
                            digitalWrite(R3_L3_Q1, LIGA); 
                            C_L3_Q1 = true;
                            Vld_P++ ;
                           } 
                  }
    
    
    
    
    
                 if ((COMPONENTE1 == "L7") ) // L7 ILUMINAÇÃO LIGA e DESLIGA TOTAL QUARTO 1
                  {Vld_P = 1 ;
     
                    if ( ((digitalRead(R1_L1_Q1) == DESLIGA) || (digitalRead(R4_L4_Q1) == DESLIGA) ||(digitalRead(R2_L2_Q1) == DESLIGA) || (digitalRead(R3_L3_Q1) == DESLIGA)) && (Vld_P == 1))
                     {Serial.println("LIGA L FULL Q1");
                      lcd.setCursor(0,linha_lcd());
                      lcd.print("LIGA L FULL Q1");
   
                      //LIGA LUZES DO PERFIL 1
                      digitalWrite(R1_L1_Q1, LIGA);
                      C_L1_Q1 = true;
                      digitalWrite(R4_L4_Q1, LIGA);
                      C_L4_Q1 = true;
                      //LIGA LUZES DO PERFIL 2
                      digitalWrite(R2_L2_Q1, LIGA);
                      C_L2_Q1 = true;
                      digitalWrite(R3_L3_Q1, LIGA);
                      C_L3_Q1 = true;
                      Vld_P++ ;
                     } 
    
                    if ( ((digitalRead(R1_L1_Q1) == LIGA) || (digitalRead(R4_L4_Q1) == LIGA) ||(digitalRead(R2_L2_Q1) == LIGA) || (digitalRead(R3_L3_Q1) == LIGA)) && (Vld_P == 1))
                     {Serial.println("DESLIGA L FULL Q1");
                      lcd.setCursor(0,linha_lcd());
                      lcd.print("DESLIGA L FULL Q1");
                      
                      //DESLIGA LUZES DO PERFIL 1
                      digitalWrite(R1_L1_Q1, DESLIGA);
                      C_L1_Q1 = false;
                      digitalWrite(R4_L4_Q1, DESLIGA);
                      C_L4_Q1 = false;
                      //DESLIGA LUZES DO PERFIL 2
                      digitalWrite(R2_L2_Q1, DESLIGA);
                      C_L2_Q1 = false;
                      digitalWrite(R3_L3_Q1, DESLIGA);} 
                      C_L3_Q1 = false;
                      Vld_P++ ; 
                     }
                     
                     
                     
                    if ((COMPONENTE1 == "L8") ) // L8 ILUMINAÇÃO LIGA e DESLIGA TOTAL QUARTO 1
                   {Vld_P = 1 ;
     
                     Serial.println("DESLIGA L FULL Q1");
                      lcd.setCursor(0,linha_lcd());
                      lcd.print("DESLIGA L FULL Q1");
                      
                      //DESLIGA LUZES DO PERFIL 1
                      digitalWrite(R1_L1_Q1, DESLIGA);
                      C_L1_Q1 = false;
                      digitalWrite(R4_L4_Q1, DESLIGA);
                      C_L4_Q1 = false;
                      //DESLIGA LUZES DO PERFIL 2
                      digitalWrite(R2_L2_Q1, DESLIGA);
                      C_L2_Q1 = false;
                      digitalWrite(R3_L3_Q1, DESLIGA);
                      C_L3_Q1 = false;
                      }
                     
                     }//AÇAO L = LIGAR
                     
                     
                     
                    
                      //TOMADAS                    
                      if ( (COMPONENTE1.substring(0,1)) == "T")  // SE O COMPONENTE É IGUAL AO L = LUZ ENTRA NO BLOCO DE IFs DE LUZES
                     Serial.println("TOMADA");
                     
                   if ( ACAO1 == "L") //LIGA DESLIGA
                     {
                        if ( ((COMPONENTE1) == "T1")) // RELE_1 LIZ_1
                           {
                            if (digitalRead(R9_T1_Q1) == DESLIGA)  
                               {Serial.println("LIGA R9_T1_Q1 chave");
                                lcd.setCursor(0,linha_lcd());
                                lcd.print("LIGA R9_T1_Q1");
                                digitalWrite(R9_T1_Q1, LIGA);
                                C_T1_Q1 = true;  
                             }
    
                                 else    
                                   {Serial.println("DESLIGA R9_T1_Q1 chave");
                                    lcd.setCursor(0,linha_lcd());
                                    lcd.print("DESLIGA R9_T1_Q1");
                                    digitalWrite(R9_T1_Q1, DESLIGA);
                                    C_T1_Q1 = false; 
                                   } 
                        } 
    
                        if (  ((COMPONENTE1) == "T2") )
                         {
                             if (digitalRead(RA_T2_Q1) == DESLIGA)  
                               {Serial.println("LIGA RA_T2_Q1 chave");
                                lcd.setCursor(0,linha_lcd());
                                lcd.print("LIGA RA_T2_Q1");
                                digitalWrite(RA_T2_Q1, LIGA);
                                C_T2_Q1 = true;  
                             }
    
                                 else    
                                   {Serial.println("DESLIGA RA_T2_Q1 chave");
                                    lcd.setCursor(0,linha_lcd());
                                    lcd.print("DESLIGA RA_T2_Q1");
                                    digitalWrite(RA_T2_Q1, DESLIGA);
                                    C_T2_Q1 = false; 
                                   } 
                          }
    
                        if (  ((COMPONENTE1) == "T3") )
                         {
                           if (digitalRead(RB_T3_Q1) == DESLIGA)  
                               {Serial.println("LIGA RB_T3_Q1 chave");
                                lcd.setCursor(0,linha_lcd());
                                lcd.print("LIGA RB_T3_Q1");
                                digitalWrite(RB_T3_Q1, LIGA);
                                C_T3_Q1 = true;
                               }
    
                                 else    
                                   {Serial.println("DESLIGA RB_T3_Q1 chave");
                                    lcd.setCursor(0,linha_lcd());
                                    lcd.print("DESLIGA RB_T3_Q1");
                                    digitalWrite(RB_T3_Q1, DESLIGA);
                                    C_T3_Q1 = false;
                                   } 
                         }
    
                        if (((COMPONENTE1) == "T4") )
                         {
                             if (digitalRead(RC_T4_Q1) == DESLIGA)  
                               {Serial.println("LIGA RC_T4_Q1 chave");
                                lcd.setCursor(0,linha_lcd());
                                lcd.print("LIGA RC_T4_Q1");
                                digitalWrite(RC_T4_Q1, LIGA);
                                C_T4_Q1 = true;
                               }
    
                                else    
                                  {Serial.println("DESLIGA R_T_Q1_4 chave");
                                   lcd.setCursor(0,linha_lcd());
                                   lcd.print("DESLIGA RC_T4_Q1");
                                   digitalWrite(RC_T4_Q1, DESLIGA);
                                   C_T4_Q1 = false;
                                  } 
                          }
    

        
                 if ((COMPONENTE1 == "T5") ) // T5 ILUMINAÇÃO LIGA e DESLIGA TOTAL QUARTO 1
                  {Vld_P = 1 ;
     
                    if ( ((digitalRead(R9_T1_Q1) == DESLIGA) || (digitalRead(RC_T4_Q1) == DESLIGA) ||(digitalRead(RA_T2_Q1) == DESLIGA) || (digitalRead(RB_T3_Q1) == DESLIGA)) && (Vld_P == 1))
                     {Serial.println("LIGA T FULL Q1");
                      lcd.setCursor(0,linha_lcd());
                      lcd.print("LIGA T FULL Q1");
   
                      //LIGA LUZES DO PERFIL 1
                      digitalWrite(R9_T1_Q1, LIGA);
                      C_T1_Q1 = true;
                      digitalWrite(RC_T4_Q1, LIGA);
                      C_T4_Q1 = true;
                      //LIGA LUZES DO PERFIL 2
                      digitalWrite(RA_T2_Q1, LIGA);
                      C_T2_Q1 = true;
                      digitalWrite(RB_T3_Q1, LIGA);
                      C_T3_Q1 = true;
                      Vld_P++ ;
                     } 
    
                    if ( ((digitalRead(R9_T1_Q1) == LIGA) || (digitalRead(RC_T4_Q1) == LIGA) ||(digitalRead(RA_T2_Q1) == LIGA) || (digitalRead(RB_T3_Q1) == LIGA)) && (Vld_P == 1))
                     {Serial.println("DESLIGA T FULL Q1");
                      lcd.setCursor(0,linha_lcd());
                      lcd.print("DESLIGA T FULL Q1");
   
                      //DESLIGA LUZES DO PERFIL 1
                      digitalWrite(R9_T1_Q1, DESLIGA);
                      C_T1_Q1 = false;
                      digitalWrite(RC_T4_Q1, DESLIGA);
                      C_T4_Q1 = false;
                      //DESLIGA LUZES DO PERFIL 2
                      digitalWrite(RA_T2_Q1, DESLIGA);
                      C_T2_Q1 = false;
                      digitalWrite(RB_T3_Q1, DESLIGA);}
                      C_T3_Q1 = false;
                      Vld_P++ ; 
                     }
                     
                     
                     if ((COMPONENTE1 == "T6") ) // T5 ILUMINAÇÃO LIGA e DESLIGA TOTAL QUARTO 1
                       {Serial.println("DESLIGA T FULL Q1");
                        lcd.setCursor(0,linha_lcd());
                        lcd.print("DESLIGA T FULL Q1");
   
                        //DESLIGA LUZES DO PERFIL 1
                        digitalWrite(R9_T1_Q1, DESLIGA);
                        C_T1_Q1 = false;
                        digitalWrite(RC_T4_Q1, DESLIGA);
                        C_T4_Q1 = false;
                        //DESLIGA LUZES DO PERFIL 2
                        digitalWrite(RA_T2_Q1, DESLIGA);
                        C_T2_Q1 = false;
                        digitalWrite(RB_T3_Q1, DESLIGA);
                        C_T3_Q1 = false;
                        } 

              
                     
                     }//AÇAO L = LIGAR
                     
                     
                     
                     
                     
                     
                     
                     
                     
                     
                     
    
    
if ( ACAO1 == "A")  //ATIVA OU NAO FUNÇÃO AUTO DE LUZES 
    {
     Serial.println("ACAO A"); 
     
     
     if (COMODO1 ==  "Q1")  
     {
    
   if (COMPONENTE1.substring(0,1) == "L")  // SE O COMPONENTE É IGUAL AO L = LUZ ENTRA NO BLOCO DE IFs DE LUZES
   {Serial.println("LUZ");
   
   if ((COMPONENTE1) == "L1" && A_L1_Q1 == true && (Vld_P == 1))
   {//C__L1_Q1 = false;
    A_L1_Q1 =  false;
    Serial.println("AUTO_DEST_1");
    lcd.setCursor(0,linha_lcd());
    lcd.print("AUTO_DEST_1");
    Vld_P++ ; } 
    if ((COMPONENTE1) == "L1" && A_L1_Q1 == false && (Vld_P == 1))
   {C_L1_Q1 = false;
    A_L1_Q1 =  true;
    Serial.println("AUTO_ATIV_1");
    lcd.setCursor(0,linha_lcd());
    lcd.print("AUTO_ATIV_1");
    Vld_P++ ; }
   
    if ((COMPONENTE1) == "L2" && A_L2_Q1 == true && (Vld_P == 1) )
   {//C_R2_L2_Q1 = false;
    A_L2_Q1 =  false;
    Serial.println("AUTO_DEST_2");
    lcd.setCursor(0,linha_lcd());
    lcd.print("AUTO_DEST_2");
    Vld_P++ ;}
    if ((COMPONENTE1) == "L2" && A_L2_Q1 == false && (Vld_P == 1) )
   {C_L2_Q1 = false;
    A_L2_Q1 =  true;
    Serial.println("AUTO_ATIV_2");
    lcd.setCursor(0,linha_lcd());
    lcd.print("AUTO_ATIV_2");
    Vld_P++ ;}
    
    if ((COMPONENTE1) == "L3" && A_L3_Q1 == true && (Vld_P == 1))
   {//C_R1_L1_Q1 = false;
    A_L3_Q1 =  false;
    Serial.println("AUTO_DEST_3");
    lcd.setCursor(0,linha_lcd());
    lcd.print("AUTO_DEST_3");
    Vld_P++ ; } 
    if ((COMPONENTE1) == "L3" && A_L3_Q1 == false && (Vld_P == 1))
   {C_L3_Q1 = false;
    A_L3_Q1 =  true;
    Serial.println("AUTO_ATIV_3");
    lcd.setCursor(0,linha_lcd());
    lcd.print("AUTO_ATIV_3");
    Vld_P++ ; }
   
    if ((COMPONENTE1) == "L4" && A_L4_Q1 == true && (Vld_P == 1) )
   {//C_R2_L2_Q1 = false;
    A_L4_Q1 =  false;
    Serial.println("AUTO_DEST_4");
    lcd.setCursor(0,linha_lcd());
    lcd.print("AUTO_DEST_4");
    Vld_P++ ;}
    if ((COMPONENTE1) == "L4" && A_L4_Q1 == false && (Vld_P == 1) )
   {C_L4_Q1 = false;
    A_L4_Q1 =  true;
    Serial.println("AUTO_ATIV_4");
    lcd.setCursor(0,linha_lcd());
    lcd.print("AUTO_ATIV_4");
    Vld_P++ ;}  
   
 }// SE O COMPONENTE É IGUAL AO L = LUZ ENTRA NO BLOCO DE IFs DE LUZES Serial.println("LUZ");
 
 if (COMPONENTE1.substring(0,1) == "T")  // SE O COMPONENTE É IGUAL AO L = LUZ ENTRA NO BLOCO DE IFs DE LUZES
   {Serial.println("TOMADA");
   
   if ((COMPONENTE1) == "T1" && A_T1_Q1 == true && (Vld_P == 1))
   {//C__T1_Q1 = false;
    A_T1_Q1 =  false;
    Serial.println("AUTO_DEST_T1");
    lcd.setCursor(0,linha_lcd());
    lcd.print("AUTO_DEST_T1");
    Vld_P++ ; } 
    if ((COMPONENTE1) == "T1" && A_T1_Q1 == false && (Vld_P == 1))
   {C_T1_Q1 = false;
    A_T1_Q1 =  true;
    Serial.println("AUTO_ATIV_T1");
    lcd.setCursor(0,linha_lcd());
    lcd.print("AUTO_ATIV_T1");
    Vld_P++ ; }
   
    if ((COMPONENTE1) == "T2" && A_T2_Q1 == true && (Vld_P == 1) )
   {//C_R2_T2_Q1 = false;
    A_T2_Q1 =  false;
    Serial.println("AUTO_DEST_2");
    lcd.setCursor(0,linha_lcd());
    lcd.print("AUTO_DEST_2");
    Vld_P++ ;}
    if ((COMPONENTE1) == "T2" && A_T2_Q1 == false && (Vld_P == 1) )
   {C_T2_Q1 = false;
    A_T2_Q1 =  true;
    Serial.println("AUTO_ATIV_2");
    lcd.setCursor(0,linha_lcd());
    lcd.print("AUTO_ATIV_2");
    Vld_P++ ;}
    
    if ((COMPONENTE1) == "T3" && A_T3_Q1 == true && (Vld_P == 1))
   {//C_R1_T1_Q1 = false;
    A_T3_Q1 =  false;
    Serial.println("AUTO_DEST_3");
    lcd.setCursor(0,linha_lcd());
    lcd.print("AUTO_DEST_3");
    Vld_P++ ; } 
    if ((COMPONENTE1) == "T3" && A_T3_Q1 == false && (Vld_P == 1))
   {C_T3_Q1 = false;
    A_T3_Q1 =  true;
    Serial.println("AUTO_ATIV_3");
    lcd.setCursor(0,linha_lcd());
    lcd.print("AUTO_ATIV_3");
    Vld_P++ ; }
   
    if ((COMPONENTE1) == "T4" && A_T4_Q1 == true && (Vld_P == 1) )
   {//C_R2_T2_Q1 = false;
    A_T4_Q1 =  false;
    Serial.println("AUTO_DEST_4");
    lcd.setCursor(0,linha_lcd());
    lcd.print("AUTO_DEST_4");
    Vld_P++ ;}
    if ((COMPONENTE1) == "T4" && A_T4_Q1 == false && (Vld_P == 1) )
   {C_T4_Q1 = false;
    A_T4_Q1 =  true;
    Serial.println("AUTO_ATIV_4");
    lcd.setCursor(0,linha_lcd());
    lcd.print("AUTO_ATIV_4");
    Vld_P++ ;}  
   
 }// SE O COMPONENTE É IGUAL AO T = TOAMDA ENTRA NO BLOCO DE IFs DE LUZES Serial.println("LUZ");
 
 
    } 
 }//ATIVA OU NAO FUNÇÃO AUTO DE LUZES     


    
    if (COMPONENTE1 == "S1")  // SE O COMPONENTE É IGUAL AO L = LUZ ENTRA NO BLOCO DE IFs DE LUZES
    {
                   Serial.println("SENSOR PIR Q1");
                   lcd.setCursor(0,linha_lcd());
                   lcd.print("SENSOR PIR Q1");
                   TEMP_AUTO_Q1 = atoi( ACAO1.c_str() ) ;
                   Serial.println("TEMP SENSOR PIR 01: " + ACAO1 + " MINUTOS");
                   lcd.setCursor(0,linha_lcd());
                   lcd.print("TP S_PIR Q1:" + ACAO1 + " MIN");
    }                
        
  } //FIM IFs Q1 = QUARTO 1



















if (COMODO1 ==  "Q2") // SE O COMODO É IGUAL AO Q1=QUARTO1 ENTRA NO BLOCO DE IFs DESSE QUARTO 
    {
      Serial.println("Q2");
               if (COMPONENTE1.substring(0,1) == "L")  // SE O COMPONENTE É IGUAL AO L = LUZ ENTRA NO BLOCO DE IFs DE LUZES
                   Serial.println("LUZ");
                   
                   
                   if ( ACAO1 == "L") //ATIVA OU NAO FUNÇÃO AUTO DE LUZES
                     {
                        if ( ((COMPONENTE1) == "L1")) // RELE_1 LIZ_1
                           {
                            if (digitalRead(R1_L1_Q2) == DESLIGA)  
                               {Serial.println("liga R1_L1_Q2 chave");
                                lcd.setCursor(0,linha_lcd());
                                lcd.print("Liga R1_L1_Q2");         
                                digitalWrite(R1_L1_Q2, LIGA);
                                C_L1_Q2 = true;  
                             }

                                 else    
                                   {Serial.println("desliga R1_L1_Q2 chave");
                                    lcd.setCursor(0,linha_lcd());
                                    lcd.print("Desliga R1_L1_Q2");
                                    digitalWrite(R1_L1_Q2, DESLIGA);
                                    C_L1_Q2 = false; 
                                   } 
                        } 
    
                        if (  ((COMPONENTE1) == "L2") )
                         {
                             if (digitalRead(R2_L2_Q2) == DESLIGA)  
                               {Serial.println("liga R2_L2_Q2 chave");
                                lcd.setCursor(0,linha_lcd());
                                lcd.print("Liga R2_L2_Q2");
                                digitalWrite(R2_L2_Q2, LIGA);
                                C_L2_Q2 = true;  
                             }
    
                                 else    
                                   {Serial.println("desliga R2_L2_Q2 chave");
                                    lcd.setCursor(0,linha_lcd());
                                    lcd.print("Desliga R2_L2_Q2");
                                    digitalWrite(R2_L2_Q2, DESLIGA);
                                    C_L2_Q2 = false; 
                                   } 
                          }
    
                        if (  ((COMPONENTE1) == "L3") )
                         {
                           if (digitalRead(R3_L3_Q2) == DESLIGA)  
                               {Serial.println("liga R3_L3_Q2 chave");
                                lcd.setCursor(0,linha_lcd());
                                lcd.print("Liga R3_L3_Q2");
                                digitalWrite(R3_L3_Q2, LIGA);
                                C_L3_Q2 = true;
                               }
    
                                 else    
                                   {Serial.println("desliga R_L_Q2_3 chave");
                                    lcd.setCursor(0,linha_lcd());
                                    lcd.print("Desliga R3_L3_Q2");
                                    digitalWrite(R3_L3_Q2, DESLIGA);
                                    C_L3_Q2 = false;
                                   } 
                         }
    
                        if (((COMPONENTE1) == "L4") )
                         {
                             if (digitalRead(R4_L4_Q2) == DESLIGA)  
                               {Serial.println("liga R4_L4_Q2 chave");
                                lcd.setCursor(0,linha_lcd());
                                lcd.print("Liga R4_L4_Q2");
                                digitalWrite(R4_L4_Q2, LIGA);
                                C_L4_Q2 = true;
                               }
    
                                else    
                                  {Serial.println("desliga R4_L4_Q2 chave");
                                   lcd.setCursor(0,linha_lcd());
                                   lcd.print("Desliga R4_L4_Q2");
                                   digitalWrite(R4_L4_Q2, DESLIGA);
                                   C_L4_Q2 = false;
                                  } 
                          }
    
                       // PERFIL ILUMINAÇÃO QUARTO 1
                         if ( (COMPONENTE1 == "L5") ) // ILUMINAÇÃO PRINCIPAL  L5=PERFIL 1 
                          {Vld_P = 1 ;
                             if ((digitalRead(R1_L1_Q2) == LIGA) && (digitalRead(R4_L4_Q2) == LIGA) && (Vld_P == 1))  
                              {Serial.println("DESLIGA R2_L2_Q2 e R4_L4_Q2 PERFIL PRINCIPAL");
                               lcd.setCursor(0,linha_lcd());
                               lcd.print("DESLIGA PERFIL 01");
                               digitalWrite(R1_L1_Q2, DESLIGA);
                               C_L1_Q2 = false;
                               digitalWrite(R4_L4_Q2, DESLIGA);
                               C_L4_Q2 = false;
                               Vld_P++ ;
                               } 

                          if ( ((digitalRead(R1_L1_Q2) == DESLIGA) || (digitalRead(R4_L4_Q2) == DESLIGA)) && (Vld_P == 1))  
                           {Serial.println("LIGA R1_L1_Q2 e R4_L4_Q2 PERFIL PRINCIPAL");
                            lcd.setCursor(0,linha_lcd());
                            lcd.print("LIGA PERFIL 01");
   
                            //DESLIGA LUZES DO PERFIL 2
                            digitalWrite(R2_L2_Q2, DESLIGA);
                            C_L2_Q2 = false;
                            digitalWrite(R3_L3_Q2, DESLIGA);
                            C_L3_Q2 = false;
                             
                            //LIGA LUZES DO PERFIL 1
                            digitalWrite(R1_L1_Q2, LIGA);
                            C_L1_Q2 = true;
                            digitalWrite(R4_L4_Q2, LIGA); 
                            C_L4_Q2 = true;
                            Vld_P++ ; 
                            }
                          }


                      if (  (COMPONENTE1 == "L6") ) // ILUMINAÇÃO QUARTO 1  L6 = DECORATIVA PERFIL 2 
                       {Vld_P = 1 ;
                         if ((digitalRead(R2_L2_Q2) == LIGA) && (digitalRead(R3_L3_Q2) == LIGA) && (Vld_P == 1))  
                          {Serial.println("DESLIGA R2_L2_Q2 e R3_L3_Q2 PERFIL PRINCIPAL");
                           lcd.setCursor(0,linha_lcd());
                           lcd.print("DESLIGA PERFIL 02");
                           digitalWrite(R2_L2_Q2, DESLIGA);
                           C_L2_Q2 = false;
                           digitalWrite(R3_L3_Q2, DESLIGA);
                           C_L3_Q2 = false;
                           Vld_P++ ;
                          } 
    
                          if ( ((digitalRead(R2_L2_Q2) == DESLIGA) || (digitalRead(R3_L3_Q2) == DESLIGA)) && (Vld_P == 1))  
                           {Serial.println("LIGA R2_L2_Q2 e R3_L3_Q2 PERFIL PRINCIPAL");
                            lcd.setCursor(0,linha_lcd());
                            lcd.print("LIGA PERFIL 02");
   
                            //DESLIGA LUZES DO PERFIL 1
                            digitalWrite(R1_L1_Q2, DESLIGA);
                            C_L1_Q2 = false;
                            digitalWrite(R4_L4_Q2, DESLIGA);
                            C_L4_Q2 = false;
                            
                            //LIGA LUZES DO PERFIL 2
                            digitalWrite(R2_L2_Q2, LIGA);
                            C_L2_Q2 = true;  
                            digitalWrite(R3_L3_Q2, LIGA); 
                            C_L3_Q2 = true;
                            Vld_P++ ;
                           } 
                  }
    
    
    
    
    
                 if ((COMPONENTE1 == "L7") ) // L7 ILUMINAÇÃO LIGA e DESLIGA TOTAL QUARTO 1
                  {Vld_P = 1 ;
     
                    if ( ((digitalRead(R1_L1_Q2) == DESLIGA) || (digitalRead(R4_L4_Q2) == DESLIGA) ||(digitalRead(R2_L2_Q2) == DESLIGA) || (digitalRead(R3_L3_Q2) == DESLIGA)) && (Vld_P == 1))
                     {Serial.println("LIGA L FULL Q2");
                      lcd.setCursor(0,linha_lcd());
                      lcd.print("LIGA L FULL Q2");
   
                      //LIGA LUZES DO PERFIL 1
                      digitalWrite(R1_L1_Q2, LIGA);
                      C_L1_Q2 = true;
                      digitalWrite(R4_L4_Q2, LIGA);
                      C_L4_Q2 = true;
                      //LIGA LUZES DO PERFIL 2
                      digitalWrite(R2_L2_Q2, LIGA);
                      C_L2_Q2 = true;
                      digitalWrite(R3_L3_Q2, LIGA);
                      C_L3_Q2 = true;
                      Vld_P++ ;
                     } 
    
                    if ( ((digitalRead(R1_L1_Q2) == LIGA) || (digitalRead(R4_L4_Q2) == LIGA) ||(digitalRead(R2_L2_Q2) == LIGA) || (digitalRead(R3_L3_Q2) == LIGA)) && (Vld_P == 1))
                     {Serial.println("DESLIGA L FULL Q2");
                      lcd.setCursor(0,linha_lcd());
                      lcd.print("DESLIGA L FULL Q2");
                      
                      //DESLIGA LUZES DO PERFIL 1
                      digitalWrite(R1_L1_Q2, DESLIGA);
                      C_L1_Q2 = false;
                      digitalWrite(R4_L4_Q2, DESLIGA);
                      C_L4_Q2 = false;
                      //DESLIGA LUZES DO PERFIL 2
                      digitalWrite(R2_L2_Q2, DESLIGA);
                      C_L2_Q2 = false;
                      digitalWrite(R3_L3_Q2, DESLIGA);} 
                      C_L3_Q2 = false;
                      Vld_P++ ; 
                     }
                     
                     
                     
                    if ((COMPONENTE1 == "L8") ) // L8 ILUMINAÇÃO LIGA e DESLIGA TOTAL QUARTO 1
                   {Vld_P = 1 ;
     
                     Serial.println("DESLIGA L FULL Q2");
                      lcd.setCursor(0,linha_lcd());
                      lcd.print("DESLIGA L FULL Q2");
                      
                      //DESLIGA LUZES DO PERFIL 1
                      digitalWrite(R1_L1_Q2, DESLIGA);
                      C_L1_Q2 = false;
                      digitalWrite(R4_L4_Q2, DESLIGA);
                      C_L4_Q2 = false;
                      //DESLIGA LUZES DO PERFIL 2
                      digitalWrite(R2_L2_Q2, DESLIGA);
                      C_L2_Q2 = false;
                      digitalWrite(R3_L3_Q2, DESLIGA);
                      C_L3_Q2 = false;
                      }
                     
                     }//AÇAO L = LIGAR
                     
                     
                     
                    
                      //TOMADAS                    
                      if ( (COMPONENTE1.substring(0,1)) == "T")  // SE O COMPONENTE É IGUAL AO L = LUZ ENTRA NO BLOCO DE IFs DE LUZES
                     Serial.println("TOMADA");
                     
                   if ( ACAO1 == "L") //LIGA DESLIGA
                     {
                        if ( ((COMPONENTE1) == "T1")) // RELE_1 LIZ_1
                           {
                            if (digitalRead(R5_T1_Q2) == DESLIGA)  
                               {Serial.println("LIGA R5_T1_Q2 chave");
                                lcd.setCursor(0,linha_lcd());
                                lcd.print("LIGA R3_T1_Q2");
                                digitalWrite(R5_T1_Q2, LIGA);
                                C_T1_Q2 = true;  
                             }
    
                                 else    
                                   {Serial.println("DESLIGA R5_T1_Q2 chave");
                                    lcd.setCursor(0,linha_lcd());
                                    lcd.print("DESLIGA R5_T1_Q2");
                                    digitalWrite(R5_T1_Q2, DESLIGA);
                                    C_T1_Q2 = false; 
                                   } 
                        } 
    
                        if (  ((COMPONENTE1) == "T2") )
                         {
                             if (digitalRead(R6_T2_Q2) == DESLIGA)  
                               {Serial.println("LIGA R6_T2_Q2 chave");
                                lcd.setCursor(0,linha_lcd());
                                lcd.print("LIGA R6_T2_Q2");
                                digitalWrite(R6_T2_Q2, LIGA);
                                C_T2_Q2 = true;  
                             }
    
                                 else    
                                   {Serial.println("DESLIGA R6_T2_Q2 chave");
                                    lcd.setCursor(0,linha_lcd());
                                    lcd.print("DESLIGA R6_T2_Q2");
                                    digitalWrite(R6_T2_Q2, DESLIGA);
                                    C_T2_Q2 = false; 
                                   } 
                          }
    
                        if (  ((COMPONENTE1) == "T3") )
                         {
                           if (digitalRead(R7_T3_Q2) == DESLIGA)  
                               {Serial.println("LIGA R7_T3_Q2 chave");
                                lcd.setCursor(0,linha_lcd());
                                lcd.print("LIGA R7_T3_Q2");
                                digitalWrite(R7_T3_Q2, LIGA);
                                C_T3_Q2 = true;
                               }
    
                                 else    
                                   {Serial.println("DESLIGA R7_T3_Q2 chave");
                                    lcd.setCursor(0,linha_lcd());
                                    lcd.print("DESLIGA R7_T3_Q2");
                                    digitalWrite(R7_T3_Q2, DESLIGA);
                                    C_T3_Q2 = false;
                                   } 
                         }
    
                        if (((COMPONENTE1) == "T4") )
                         {
                             if (digitalRead(R8_T4_Q2) == DESLIGA)  
                               {Serial.println("LIGA R8_T4_Q2 chave");
                                lcd.setCursor(0,linha_lcd());
                                lcd.print("LIGA R8_T4_Q2");
                                digitalWrite(R8_T4_Q2, LIGA);
                                C_T4_Q2 = true;
                               }
    
                                else    
                                  {Serial.println("DESLIGA R8_T4_Q2 chave");
                                   lcd.setCursor(0,linha_lcd());
                                   lcd.print("DESLIGA R8_T4_Q2");
                                   digitalWrite(R8_T4_Q2, DESLIGA);
                                   C_T4_Q2 = false;
                                  } 
                          }
    

        
                 if ((COMPONENTE1 == "T5") ) // T5 ILUMINAÇÃO LIGA e DESLIGA TOTAL QUARTO 1
                  {Vld_P = 1 ;
     
                    if ( ((digitalRead(R5_T1_Q2) == DESLIGA) || (digitalRead(R8_T4_Q2) == DESLIGA) ||(digitalRead(R6_T2_Q2) == DESLIGA) || (digitalRead(R7_T3_Q2) == DESLIGA)) && (Vld_P == 1))
                     {Serial.println("LIGA T FULL Q2");
                      lcd.setCursor(0,linha_lcd());
                      lcd.print("LIGA T FULL Q2");
   
                      //LIGA LUZES DO PERFIL 1
                      digitalWrite(R5_T1_Q2, LIGA);
                      C_T1_Q2 = true;
                      digitalWrite(R8_T4_Q2, LIGA);
                      C_T4_Q2 = true;
                      //LIGA LUZES DO PERFIL 2
                      digitalWrite(R6_T2_Q2, LIGA);
                      C_T2_Q2 = true;
                      digitalWrite(R7_T3_Q2, LIGA);
                      C_T3_Q2 = true;
                      Vld_P++ ;
                     } 
    
                    if ( ((digitalRead(R5_T1_Q2) == LIGA) || (digitalRead(R8_T4_Q2) == LIGA) ||(digitalRead(R6_T2_Q2) == LIGA) || (digitalRead(R7_T3_Q2) == LIGA)) && (Vld_P == 1))
                     {Serial.println("DESLIGA T FULL Q2");
                      lcd.setCursor(0,linha_lcd());
                      lcd.print("DESLIGA T FULL Q2");
   
                      //DESLIGA LUZES DO PERFIL 1
                      digitalWrite(R5_T1_Q2, DESLIGA);
                      C_T1_Q2 = false;
                      digitalWrite(R8_T4_Q2, DESLIGA);
                      C_T4_Q2 = false;
                      //DESLIGA LUZES DO PERFIL 2
                      digitalWrite(R6_T2_Q2, DESLIGA);
                      C_T2_Q2 = false;
                      digitalWrite(R7_T3_Q2, DESLIGA);}
                      C_T3_Q2 = false;
                      Vld_P++ ; 
                     }
                     
                     
                     if ((COMPONENTE1 == "T6") ) // T5 ILUMINAÇÃO LIGA e DESLIGA TOTAL QUARTO 1
                       {Serial.println("DESLIGA T FULL Q1");
                        lcd.setCursor(0,linha_lcd());
                        lcd.print("DESLIGA T FULL Q1");
   
                        //DESLIGA LUZES DO PERFIL 1
                        digitalWrite(R5_T1_Q2, DESLIGA);
                        C_T1_Q2 = false;
                        digitalWrite(R8_T4_Q2, DESLIGA);
                        C_T4_Q2 = false;
                        //DESLIGA LUZES DO PERFIL 2
                        digitalWrite(R6_T2_Q2, DESLIGA);
                        C_T2_Q2 = false;
                        digitalWrite(R7_T3_Q2, DESLIGA);
                        C_T3_Q2 = false;
                        } 

              
                     
                     }//AÇAO L = LIGAR
                     
                     
                     
                     
                     
                     
                     
                     
                     
                     
                     
    
    
if ( ACAO1 == "A")  //ATIVA OU NAO FUNÇÃO AUTO DE LUZES 
    {
     Serial.println("ACAO A"); 
     
     
     if (COMODO1 ==  "Q2")  
     {
    
   if (COMPONENTE1.substring(0,1) == "L")  // SE O COMPONENTE É IGUAL AO L = LUZ ENTRA NO BLOCO DE IFs DE LUZES
   {Serial.println("LUZ");
   
   if ((COMPONENTE1) == "L1" && A_L1_Q2 == true && (Vld_P == 1))
   {//C_L1_Q2 = false;
    A_L1_Q2 =  false;
    Serial.println("AUTO_DEST_1");
    lcd.setCursor(0,linha_lcd());
    lcd.print("AUTO_DEST_1");
    Vld_P++ ; } 
    if ((COMPONENTE1) == "L1" && A_L1_Q2 == false && (Vld_P == 1))
   {C_L1_Q2 = false;
    A_L1_Q2 =  true;
    Serial.println("AUTO_ATIV_1");
    lcd.setCursor(0,linha_lcd());
    lcd.print("AUTO_ATIV_1");
    Vld_P++ ; }
   
    if ((COMPONENTE1) == "L2" && A_L2_Q2 == true && (Vld_P == 1) )
   {//C_R2_L2_Q2 = false;
    A_L2_Q2 =  false;
    Serial.println("AUTO_DEST_2");
    lcd.setCursor(0,linha_lcd());
    lcd.print("AUTO_DEST_2");
    Vld_P++ ;}
    if ((COMPONENTE1) == "L2" && A_L2_Q2 == false && (Vld_P == 1) )
   {C_L2_Q2 = false;
    A_L2_Q2 =  true;
    Serial.println("AUTO_ATIV_2");
    lcd.setCursor(0,linha_lcd());
    lcd.print("AUTO_ATIV_2");
    Vld_P++ ;}
    
    if ((COMPONENTE1) == "L3" && A_L3_Q2 == true && (Vld_P == 1))
   {//C_R1_L1_Q2 = false;
    A_L3_Q2 =  false;
    Serial.println("AUTO_DEST_3");
    lcd.setCursor(0,linha_lcd());
    lcd.print("AUTO_DEST_3");
    Vld_P++ ; } 
    if ((COMPONENTE1) == "L3" && A_L3_Q2 == false && (Vld_P == 1))
   {C_L3_Q2 = false;
    A_L3_Q2 =  true;
    Serial.println("AUTO_ATIV_3");
    lcd.setCursor(0,linha_lcd());
    lcd.print("AUTO_ATIV_3");
    Vld_P++ ; }
   
    if ((COMPONENTE1) == "L4" && A_L4_Q2 == true && (Vld_P == 1) )
   {//C_R2_L2_Q2 = false;
    A_L4_Q2 =  false;
    Serial.println("AUTO_DEST_4");
    lcd.setCursor(0,linha_lcd());
    lcd.print("AUTO_DEST_4");
    Vld_P++ ;}
    if ((COMPONENTE1) == "L4" && A_L4_Q2 == false && (Vld_P == 1) )
   {C_L4_Q2 = false;
    A_L4_Q2 =  true;
    Serial.println("AUTO_ATIV_4");
    lcd.setCursor(0,linha_lcd());
    lcd.print("AUTO_ATIV_4");
    Vld_P++ ;}  
   
 }// SE O COMPONENTE É IGUAL AO L = LUZ ENTRA NO BLOCO DE IFs DE LUZES Serial.println("LUZ");
 
 if (COMPONENTE1.substring(0,1) == "T")  // SE O COMPONENTE É IGUAL AO L = LUZ ENTRA NO BLOCO DE IFs DE LUZES
   {Serial.println("TOMADA");
   
   if ((COMPONENTE1) == "T1" && A_T1_Q2 == true && (Vld_P == 1))
   {//C__T1_Q2 = false;
    A_T1_Q2 =  false;
    Serial.println("AUTO_DEST_T1");
    lcd.setCursor(0,linha_lcd());
    lcd.print("AUTO_DEST_T1");
    Vld_P++ ; } 
    if ((COMPONENTE1) == "T1" && A_T1_Q2 == false && (Vld_P == 1))
   {C_T1_Q2 = false;
    A_T1_Q2 =  true;
    Serial.println("AUTO_ATIV_T1");
    lcd.setCursor(0,linha_lcd());
    lcd.print("AUTO_ATIV_T1");
    Vld_P++ ; }
   
    if ((COMPONENTE1) == "T2" && A_T2_Q2 == true && (Vld_P == 1) )
   {//C_R2_T2_Q2 = false;
    A_T2_Q2 =  false;
    Serial.println("AUTO_DEST_2");
    lcd.setCursor(0,linha_lcd());
    lcd.print("AUTO_DEST_2");
    Vld_P++ ;}
    if ((COMPONENTE1) == "T2" && A_T2_Q2 == false && (Vld_P == 1) )
   {C_T2_Q2 = false;
    A_T2_Q2 =  true;
    Serial.println("AUTO_ATIV_2");
    lcd.setCursor(0,linha_lcd());
    lcd.print("AUTO_ATIV_2");
    Vld_P++ ;}
    
    if ((COMPONENTE1) == "T3" && A_T3_Q2 == true && (Vld_P == 1))
   {//C_R1_T1_Q2 = false;
    A_T3_Q2 =  false;
    Serial.println("AUTO_DEST_3");
    lcd.setCursor(0,linha_lcd());
    lcd.print("AUTO_DEST_3");
    Vld_P++ ; } 
    if ((COMPONENTE1) == "T3" && A_T3_Q2 == false && (Vld_P == 1))
   {C_T3_Q2 = false;
    A_T3_Q2 =  true;
    Serial.println("AUTO_ATIV_3");
    lcd.setCursor(0,linha_lcd());
    lcd.print("AUTO_ATIV_3");
    Vld_P++ ; }
   
    if ((COMPONENTE1) == "T4" && A_T4_Q2 == true && (Vld_P == 1) )
   {//C_R2_T2_Q2 = false;
    A_T4_Q2 =  false;
    Serial.println("AUTO_DEST_4");
    lcd.setCursor(0,linha_lcd());
    lcd.print("AUTO_DEST_4");
    Vld_P++ ;}
    if ((COMPONENTE1) == "T4" && A_T4_Q2 == false && (Vld_P == 1) )
   {C_T4_Q2 = false;
    A_T4_Q2 =  true;
    Serial.println("AUTO_ATIV_4");
    lcd.setCursor(0,linha_lcd());
    lcd.print("AUTO_ATIV_4");
    Vld_P++ ;}  
   
 }// SE O COMPONENTE É IGUAL AO T = TOAMDA ENTRA NO BLOCO DE IFs DE LUZES Serial.println("LUZ");
 
 
    } 
 }//ATIVA OU NAO FUNÇÃO AUTO DE LUZES     


    
    if (COMPONENTE1 == "S1")  // SE O COMPONENTE É IGUAL AO L = LUZ ENTRA NO BLOCO DE IFs DE LUZES
    {
                   Serial.println("SENSOR PIR Q2");
                   lcd.setCursor(0,linha_lcd());
                   lcd.print("SENSOR PIR Q2");
                   TEMP_AUTO_Q2 = atoi( ACAO1.c_str() ) ;
                   Serial.println("TEMP SENSOR PIR 02: " + ACAO1 + " MINUTOS");
                   lcd.setCursor(0,linha_lcd());
                   lcd.print("TP S_PIR Q2:" + ACAO1 + " MIN");
    }                
        
  } //FIM IFs Q2 = QUARTO 1


  
}//FIM VALIDAÇÃO DIGITOS VERIFICADORES DO PROTOCOLO    










if ( (V_INI1+V_11+V_21+V_31+V_41+V_FIN1+V_FIN21) == "#*****@") //VALIDAÇÃO DIGITOS VERIFICADORES DO PROTOCOLO DIA HORA LIGA DESLIGA
   {
     //Serial.println("valido");
//    if (COMODO1 ==  "Q1") // SE O COMODO É IGUAL AO Q1=QUARTO1 ENTRA NO BLOCO DE IFs DESSE QUARTO 
//    {
//      Serial.println("Q1");

                
 if ( ACAO1 == "T")  //FUNÇÃO TIMER PARA LUZES LIGAR E DESLIGAR DETERMINADO HORARIO 
    { boolean valid_nv = true;
     Serial.println("ACAO T = PROGRAMAR TEMPO"); 
           //LUZES                       
                    
                 for(int i = 0;i<=indice;i++)
                 {
                 
                   if(comando == HORA_ACAO[i][1])
                   {
                   valid_nv = false;
                   Serial.println("PROGRAMACAO JA ATIVA");  
                   }
                   
                 }//for
                 
                 if (valid_nv == true)
                 {indice = indice + 1;
                 
                 digitalWrite(BOZINA_Q1,HIGH);
                 delay(30);
                 digitalWrite(BOZINA_Q1,LOW); 
                 Serial.println("NOVA PROGRAMACAO");  
                 Serial.println(indice);
                 Serial.println(comando);
                 
                 Serial.print("LIGAR AS: ");
                 Serial.println(AUTOLIGA1.substring(1,3)+":"+AUTOLIGA1.substring(3,5)+":00");
                 
                 Serial.print("DESLIGAR AS: ");
                 Serial.println (AUTODESLIGA1.substring(1,3)+":"+AUTODESLIGA1.substring(3,5)+":00");
                 
                 Serial.print("SEQUENCIA DE DIAS: ");
                 Serial.println (DIAS);
                 
                 HORA_ACAO[indice][1] = comando;
                 HORA_ACAO[indice][2] = (AUTOLIGA1.substring(1,3)+":"+AUTOLIGA1.substring(3,5)+":00");
                 HORA_ACAO[indice][3] = (AUTODESLIGA1.substring(1,3)+":"+AUTODESLIGA1.substring(3,5)+":00");
                 HORA_ACAO[indice][4] = (DIAS);
                 
//                 Serial.println (HORA_ACAO[indice][4].substring(0,1)); 
//                 Serial.println (HORA_ACAO[indice][4].substring(1,2));
//                 Serial.println (HORA_ACAO[indice][4].substring(2,3));
//                 Serial.println (HORA_ACAO[indice][4].substring(3,4));
//                 Serial.println (HORA_ACAO[indice][4].substring(4,5));
//                 Serial.println (HORA_ACAO[indice][4].substring(5,6));
//                 Serial.println (HORA_ACAO[indice][4].substring(6,7));
                 }
                 
      
    }//FUNÇÃO TIMER PARA LUZES LIGAR E DESLIGAR DETERMINADO HORARIO  
        
 //} //FIM IFs Q1 = QUARTO 1
        
}//FIM VALIDAÇÃO DIGITOS VERIFICADORES DO PROTOCOLO DIA HORA LIGA DESLIGA   



















    if ( comando == "HORA")  
    {
  
  //Mostra as informações no Serial Monitor
  Serial.print("Hora : ");
  Serial.print(rtc.getTimeStr());
  Serial.print(" ");
  Serial.print("Data : ");
  Serial.print(rtc.getDateStr(FORMAT_SHORT));
  Serial.print(" ");
  Serial.println(rtc.getDOWStr(FORMAT_SHORT));
  
    String dia = rtc.getDOWStr(FORMAT_SHORT);   
  if (dia == "Monday" )
        {Serial.println("SEG");}
  if (dia == "Tuesday")  
        {Serial.println("TER");} 
  if (dia == "Wednesday")  
        {Serial.println("QUA");}  
  if (dia == "Thursday")   
        {Serial.println("QUI");}   
  if (dia == "Friday")   
        {Serial.println("SEX");}   
  if (dia == "Saturday")   
        {Serial.println("SAB");}   
  if (dia == "Sunday")  
        {Serial.println("DOM");} 
  //Serial.println(rtc.getDOWStr(FORMAT_SHORT));

  
  linha = -1;
  lcd.setCursor(0,linha_lcd());
  lcd.print("Hora: ");
  lcd.print(rtc.getTimeStr());
  
  lcd.setCursor(0,linha_lcd());
  lcd.print("Data: ");
  lcd.print(rtc.getDateStr(FORMAT_SHORT));
  
  lcd.setCursor(0,linha_lcd());
  
  if (dia == "Monday" )
        {lcd.print("SEGUNDA");}
  if (dia == "Tuesday")  
        {lcd.print("TERCA");} 
  if (dia == "Wednesday")  
        {lcd.print("QUARTA");}  
  if (dia == "Thursday")   
        {lcd.print("QUINTA");}   
  if (dia == "Friday")   
        {lcd.print("SEXTA");}   
  if (dia == "Saturday")   
        {lcd.print("SABADO");}   
  if (dia == "Sunday")  
        {lcd.print("DOMINGO");} 
  //lcd.print(rtc.getDOWStr(FORMAT_SHORT));
  
  //MONDAY   - segunda 
  //TUESDAY   - terça
  //WEDNESDAY - quarta
  //THURSDAY  - quinta
  //FRIDAY    - sexta 
  //SATURDAY  - sabado
  //SUNDAY    - domingo
    
  
   
  /*
  // Send date over serial connection
  Serial.print("Today is the ");
  Serial.print(tempo.date, DEC);
  Serial.print(". day of ");
  Serial.print(rtc.getMonthStr());
  Serial.print(" in the year ");
  Serial.print(tempo.year, DEC);
  Serial.println(".");
  // Send Day-of-Week and time
  Serial.print("It is the ");
  Serial.print(tempo.dow, DEC);
  Serial.print(". day of the week (counting monday as the 1th), and it has passed ");
  Serial.print(tempo.hour, DEC);
  Serial.print(" hour(s), ");
  Serial.print(tempo.min, DEC);
  Serial.print(" minute(s) and ");
  Serial.print(tempo.sec, DEC);
  Serial.println(" second(s) since midnight.");
  // Send a divider for readability
  Serial.println("  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -");
  */
  
  }//fim hora
 
 

 
 
 
     if ( comando == "LCD")  
    {
     
     //LIGA E DESLIGA LED DO LCD
     LUZ_LED();
 
  }//fim LCD
 
 
 
 
 
 
 
 
   
 //_______________________CONTROLE_________________________// 

if ( (V_INI2+V_12+V_22+V_32+V_42+V_FIN2) == "#****@") //VALIDAÇÃO DIGITOS VERIFICADORES DO PROTOCOLO
   {
     //Serial.println("valido");
    if (COMODO2 ==  "Q1") // SE O COMODO É IGUAL AO Q1=QUARTO1 ENTRA NO BLOCO DE IFs DESSE QUARTO 
    {
      Serial.println("Q1");
               
               
               if (COMPONENTE2 == "HOME...")  // SE O COMPONENTE É IGUAL AO L = LUZ ENTRA NO BLOCO DE IFs DE LUZES
                 { Serial.println("HOME");
                   
                   
                   if ( ACAO2 == "LIGA..") //ATIVA OU NAO FUNÇÃO AUTO DE LUZES
                     {        //irsend.sendNEC(0xFF30CF, 32);// código que sera enviado a tv para aumentar o volume
                               for (int i = 0; i < 10; i++) {
                               irsend.sendNEC(0xFF30CF, 32);// código que sera enviado a tv para aumentar o volume
                               }
                               Serial.println("LIGA HOME");
                                lcd.setCursor(0,linha_lcd());
                                lcd.print("LIGA HOME");  
                           }
                           
                   if ( ACAO2 == "MODE..") //ATIVA OU NAO FUNÇÃO AUTO DE LUZES
                     {         irsend.sendNEC(0xFF30CF, 32);// código que sera enviado a tv para aumentar o volume
                               Serial.println("MODE HOME");
                                lcd.setCursor(0,linha_lcd());
                                lcd.print("MODE HOME");  
                           }
                   if ( ACAO2 == "VOL+..") //ATIVA OU NAO FUNÇÃO AUTO DE LUZES
                     {          irsend.sendNEC(0xFFE817, 32);// código que sera enviado a tv para aumentar o volume     
                                Serial.println("VOL+ HOME");
                                lcd.setCursor(0,linha_lcd());
                                lcd.print("VOL+ HOME");  
                           }
                   if ( ACAO2 == "VOL-..") //ATIVA OU NAO FUNÇÃO AUTO DE LUZES
                     {         irsend.sendNEC(0xFFD827, 32);// código que sera enviado a tv para aumentar o volume
                               Serial.println("VOL- HOME");
                                lcd.setCursor(0,linha_lcd());
                                lcd.print("VOL- HOME");  
                           }
                   if ( ACAO2 == "AUDIO.") //ATIVA OU NAO FUNÇÃO AUTO DE LUZES
                     {         irsend.sendNEC(0xFF00FF, 32);// código que sera enviado a tv para aumentar o volume
                               Serial.println("AUDIO HOME");
                                lcd.setCursor(0,linha_lcd());
                                lcd.print("AUDIO HOME");  
                           }
                   if ( ACAO2 == "MUTE..") //ATIVA OU NAO FUNÇÃO AUTO DE LUZES
                     {         irsend.sendNEC(0xFF20DF, 32);// código que sera enviado a tv para aumentar o volume
                               Serial.println("MUTE HOME");
                                lcd.setCursor(0,linha_lcd());
                                lcd.print("MUTE HOME");  
                           }
                   if ( ACAO2 == "PALSE.") //ATIVA OU NAO FUNÇÃO AUTO DE LUZES
                     {         irsend.sendNEC(0xFF08F7, 32);// código que sera enviado a tv para aumentar o volume
                               Serial.println("PALSE HOME");
                                lcd.setCursor(0,linha_lcd());
                                lcd.print("PALSE HOME");  
                           }
                   if ( ACAO2 == "CIMA..") //ATIVA OU NAO FUNÇÃO AUTO DE LUZES
                     {         irsend.sendNEC(0xFFA05F, 32);// código que sera enviado a tv para aumentar o volume
                               Serial.println("CIMA HOME");
                                lcd.setCursor(0,linha_lcd());
                                lcd.print("CIMA HOME");  
                           }
                   if ( ACAO2 == "BAIXO.") //ATIVA OU NAO FUNÇÃO AUTO DE LUZES
                     {         irsend.sendNEC(0xFFE01F, 32);// código que sera enviado a tv para aumentar o volume
                               Serial.println("BAIXO HOME");
                                lcd.setCursor(0,linha_lcd());
                                lcd.print("BAIXO HOME");  
                           }
                   if ( ACAO2 == "ESQ...") //ATIVA OU NAO FUNÇÃO AUTO DE LUZES
                     {         irsend.sendNEC(0xFF40BF, 32);// código que sera enviado a tv para aumentar o volume
                               Serial.println("ESQUERDA HOME");
                                lcd.setCursor(0,linha_lcd());
                                lcd.print("ESQUERDA HOME");  
                           }
                   if ( ACAO2 == "DIR...") //ATIVA OU NAO FUNÇÃO AUTO DE LUZES
                     {         irsend.sendNEC(0xFF48B7, 32);// código que sera enviado a tv para aumentar o volume
                               Serial.println("DIREITA HOME");
                                lcd.setCursor(0,linha_lcd());
                                lcd.print("DIREITA HOME");  
                           }
                 
               } //if (COMPONENTE2 == "HOME...")     
                           
        } //ENDIF Q1
    
    
   }//FIM VALIDAÇÃO DIGITOS VERIFICADORES DO PROTOCOLO
 //_______________________CONTROLE_________________________// 
 
 
       
   } 
//------------------------FUNC_COMANDO()----------------------------------//























//------------------------FUNC_TEMP()----------------------------------//


  void FUNC_TEMP(String comando, int CHAVE){

 int  Vld_P      = 1; // VALIDAÇÃO PARA PERFIL

//#Q1*L1*L*D0000*L0000@  luz ou tomada TIPO 01
String V_INI1, COMODO1, V_11, COMPONENTE1, V_21, ACAO1, V_31, AUTODESLIGA1, V_41, AUTOLIGA1, V_FIN1,DIAS,V_FIN21 ;

V_INI1       = comando.substring(0,1);
COMODO1      = comando.substring(1,3);
V_11         = comando.substring(3,4);
COMPONENTE1  = comando.substring(4,6);
V_21         = comando.substring(6,7);
ACAO1        = "L"; //comando.substring(7,8);
V_31         = comando.substring(8,9);
AUTODESLIGA1 = comando.substring(9,14);
V_41         = comando.substring(14,15);
AUTOLIGA1    = comando.substring(15,20);
V_FIN1       = comando.substring(20,21);
DIAS         = comando.substring(21,28);
V_FIN21      = comando.substring(28,29);

                                     
if ( (V_INI1+V_11+V_21+V_31+V_41+V_FIN1+V_FIN21) == "#*****@") //VALIDAÇÃO DIGITOS VERIFICADORES DO PROTOCOLO
   {
     
    if (COMODO1 ==  "Q1") // SE O COMODO É IGUAL AO Q1=QUARTO1 ENTRA NO BLOCO DE IFs DESSE QUARTO 
    {
      Serial.println("Q1");
               if (COMPONENTE1.substring(0,1) == "L")  // SE O COMPONENTE É IGUAL AO L = LUZ ENTRA NO BLOCO DE IFs DE LUZES
                   Serial.println("LUZ");
                   
                   
                   if ( ACAO1 == "L") //ATIVA OU NAO FUNÇÃO AUTO DE LUZES
                     {
                        if ( ((COMPONENTE1) == "L1")) // RELE_1 LIZ_1
                           {
                            if (CHAVE == 1)  
                               {Serial.println("liga R_L_Q1_1 chave");
                                lcd.setCursor(0,linha_lcd());
                                lcd.print("Liga R1_L1_Q1");         
                                digitalWrite(R1_L1_Q1, LIGA);
                                C_L1_Q1 = true;  
                             }

                                 else    
                                   {Serial.println("desliga R_L_Q1_1 chave");
                                    lcd.setCursor(0,linha_lcd());
                                    lcd.print("Desliga R1_L1_Q1");
                                    digitalWrite(R1_L1_Q1, DESLIGA);
                                    C_L1_Q1 = false; 
                                   } 
                        } 
    
                        if (  ((COMPONENTE1) == "L2") )
                         {
                             if (CHAVE == 1)  
                               {Serial.println("liga R2_L2_Q1 chave");
                                lcd.setCursor(0,linha_lcd());
                                lcd.print("Liga R2_L2_Q1");
                                digitalWrite(R2_L2_Q1, LIGA);
                                C_L2_Q1 = true;  
                             }
    
                                 else    
                                   {Serial.println("desliga R2_L2_Q1 chave");
                                    lcd.setCursor(0,linha_lcd());
                                    lcd.print("Desliga R2_L2_Q1");
                                    digitalWrite(R2_L2_Q1, DESLIGA);
                                    C_L2_Q1 = false; 
                                   } 
                          }
    
                        if (  ((COMPONENTE1) == "L3") )
                         {
                           if (CHAVE == 1)  
                               {Serial.println("liga R3_L3_Q1 chave");
                                lcd.setCursor(0,linha_lcd());
                                lcd.print("Liga R3_L3_Q1");
                                digitalWrite(R3_L3_Q1, LIGA);
                                C_L3_Q1 = true;
                               }
    
                                 else    
                                   {Serial.println("desliga R_L_Q1_3 chave");
                                    lcd.setCursor(0,linha_lcd());
                                    lcd.print("Desliga R3_L3_Q1");
                                    digitalWrite(R3_L3_Q1, DESLIGA);
                                    C_L3_Q1 = false;
                                   } 
                         }
    
                        if (((COMPONENTE1) == "L4") )
                         {
                             if (CHAVE == 1)  
                               {Serial.println("liga R4_L4_Q1 chave");
                                lcd.setCursor(0,linha_lcd());
                                lcd.print("Liga R4_L4_Q1");
                                digitalWrite(R4_L4_Q1, LIGA);
                                C_L4_Q1 = true;
                               }
    
                                else    
                                  {Serial.println("desliga R4_L4_Q1 chave");
                                   lcd.setCursor(0,linha_lcd());
                                   lcd.print("Desliga R4_L4_Q1");
                                   digitalWrite(R4_L4_Q1, DESLIGA);
                                   C_L4_Q1 = false;
                                  } 
                          }
    
                       // PERFIL ILUMINAÇÃO QUARTO 1
                         if ( (COMPONENTE1 == "L5") ) // ILUMINAÇÃO PRINCIPAL  L5=PERFIL 1 
                          {Vld_P = 1 ;
                             if ( (CHAVE == 2) && (CHAVE == 2) && (Vld_P == 1))  
                              {Serial.println("DESLIGA R_L_Q1_1 e R_L_Q1_4 PERFIL PRINCIPAL");
                               lcd.setCursor(0,linha_lcd());
                               lcd.print("DESLIGA PERFIL 01");
                               digitalWrite(R1_L1_Q1, DESLIGA);
                               C_L1_Q1 = false;
                               digitalWrite(R4_L4_Q1, DESLIGA);
                               C_L4_Q1 = false;
                               Vld_P++ ;
                               } 

                          if ( ((CHAVE == 1) || (CHAVE == 1)) && (Vld_P == 1))  
                           {Serial.println("LIGA R_L_Q1_1 e R_L_Q1_4 PERFIL PRINCIPAL");
                            lcd.setCursor(0,linha_lcd());
                            lcd.print("LIGA PERFIL 01");
   
                            //DESLIGA LUZES DO PERFIL 2
                            digitalWrite(R2_L2_Q1, DESLIGA);
                            C_L2_Q1 = false;
                            digitalWrite(R3_L3_Q1, DESLIGA);
                            C_L3_Q1 = false;
                             
                            //LIGA LUZES DO PERFIL 1
                            digitalWrite(R1_L1_Q1, LIGA);
                            C_L1_Q1 = true;
                            digitalWrite(R4_L4_Q1, LIGA); 
                            C_L4_Q1 = true;
                            Vld_P++ ; 
                            }
                          }


                      if (  (COMPONENTE1 == "L6") ) // ILUMINAÇÃO QUARTO 1  L6 = DECORATIVA PERFIL 2 
                       {Vld_P = 1 ;
                         if ((CHAVE == 2) && (CHAVE == 2) && (Vld_P == 1))  
                          {Serial.println("DESLIGA R_L_Q1_1 e R_L_Q1_4 PERFIL PRINCIPAL");
                           lcd.setCursor(0,linha_lcd());
                           lcd.print("DESLIGA PERFIL 02");
                           digitalWrite(R2_L2_Q1, DESLIGA);
                           C_L2_Q1 = false;
                           digitalWrite(R3_L3_Q1, DESLIGA);
                           C_L3_Q1 = false;
                           Vld_P++ ;
                          } 
    
                          if ( ((CHAVE == 1) || (CHAVE == 1)) && (Vld_P == 1))  
                           {Serial.println("LIGA R_L_Q1_1 e R_L_Q1_4 PERFIL PRINCIPAL");
                            lcd.setCursor(0,linha_lcd());
                            lcd.print("LIGA PERFIL 02");
   
                            //DESLIGA LUZES DO PERFIL 1
                            digitalWrite(R1_L1_Q1, DESLIGA);
                            C_L1_Q1 = false;
                            digitalWrite(R4_L4_Q1, DESLIGA);
                            C_L4_Q1 = false;
                            
                            //LIGA LUZES DO PERFIL 2
                            digitalWrite(R2_L2_Q1, LIGA);
                            C_L2_Q1 = true;  
                            digitalWrite(R3_L3_Q1, LIGA); 
                            C_L3_Q1 = true;
                            Vld_P++ ;
                           } 
                  }
    
    
    
    
    
                 if ((COMPONENTE1 == "L7") ) // L7 ILUMINAÇÃO LIGA e DESLIGA TOTAL QUARTO 1
                  {Vld_P = 1 ;
     
                    if ( (CHAVE == 1 ) && (Vld_P == 1))
                     {Serial.println("LIGA L FULL Q1");
                      lcd.setCursor(0,linha_lcd());
                      lcd.print("LIGA L FULL Q1");
   
                      //LIGA LUZES DO PERFIL 1
                      digitalWrite(R1_L1_Q1, LIGA);
                      C_L1_Q1 = true;
                      digitalWrite(R4_L4_Q1, LIGA);
                      C_L4_Q1 = true;
                      //LIGA LUZES DO PERFIL 2
                      digitalWrite(R2_L2_Q1, LIGA);
                      C_L2_Q1 = true;
                      digitalWrite(R3_L3_Q1, LIGA);
                      C_L3_Q1 = true;
                      Vld_P++ ;
                     } 
    
                    if ( (CHAVE == 2 ) && (Vld_P == 1))
                     {Serial.println("DESLIGA L FULL Q1");
                      lcd.setCursor(0,linha_lcd());
                      lcd.print("DESLIGA L FULL Q1");
                      
                      //DESLIGA LUZES DO PERFIL 1
                      digitalWrite(R1_L1_Q1, DESLIGA);
                      C_L1_Q1 = false;
                      digitalWrite(R4_L4_Q1, DESLIGA);
                      C_L4_Q1 = false;
                      //DESLIGA LUZES DO PERFIL 2
                      digitalWrite(R2_L2_Q1, DESLIGA);
                      C_L2_Q1 = false;
                      digitalWrite(R3_L3_Q1, DESLIGA);} 
                      C_L3_Q1 = false;
                      Vld_P++ ; 
                     }
                     
                     
                 }//AÇAO L = LIGAR
                     
                     
                     
                    
                      //TOMADAS                    
                      if ( (COMPONENTE1.substring(0,1)) == "T")  // SE O COMPONENTE É IGUAL AO L = LUZ ENTRA NO BLOCO DE IFs DE LUZES
                     Serial.println("TOMADA");
                     
                   if ( ACAO1 == "L") //LIGA DESLIGA
                     {
                        if ( ((COMPONENTE1) == "T1")) // RELE_1 LIZ_1
                           {
                            if (CHAVE == 1)  
                               {Serial.println("LIGA R9_T1_Q1 chave");
                                lcd.setCursor(0,linha_lcd());
                                lcd.print("LIGA R9_T1_Q1");
                                digitalWrite(R9_T1_Q1, LIGA);
                                C_T1_Q1 = true;  
                             }
    
                                 else    
                                   {Serial.println("DESLIGA R9_T1_Q1 chave");
                                    lcd.setCursor(0,linha_lcd());
                                    lcd.print("DESLIGA R9_T1_Q1");
                                    digitalWrite(R9_T1_Q1, DESLIGA);
                                    C_T1_Q1 = false; 
                                   } 
                        } 
    
                        if (  ((COMPONENTE1) == "T2") )
                         {
                             if (CHAVE == 1)  
                               {Serial.println("LIGA RA_T2_Q1 chave");
                                lcd.setCursor(0,linha_lcd());
                                lcd.print("LIGA RA_T2_Q1");
                                digitalWrite(RA_T2_Q1, LIGA);
                                C_T2_Q1 = true;  
                             }
    
                                 else    
                                   {Serial.println("DESLIGA RA_T2_Q1 chave");
                                    lcd.setCursor(0,linha_lcd());
                                    lcd.print("DESLIGA RA_T2_Q1");
                                    digitalWrite(RA_T2_Q1, DESLIGA);
                                    C_T2_Q1 = false; 
                                   } 
                          }
    
                        if (  ((COMPONENTE1) == "T3") )
                         {
                           if (CHAVE == 1)  
                               {Serial.println("LIGA RB_T3_Q1 chave");
                                lcd.setCursor(0,linha_lcd());
                                lcd.print("LIGA RB_T3_Q1");
                                digitalWrite(RB_T3_Q1, LIGA);
                                C_T3_Q1 = true;
                               }
    
                                 else    
                                   {Serial.println("DESLIGA RB_T3_Q1 chave");
                                    lcd.setCursor(0,linha_lcd());
                                    lcd.print("DESLIGA RB_T3_Q1");
                                    digitalWrite(RB_T3_Q1, DESLIGA);
                                    C_T3_Q1 = false;
                                   } 
                         }
    
                        if (((COMPONENTE1) == "T4") )
                         {
                             if(CHAVE == 1)  
                               {Serial.println("LIGA RC_T4_Q1 chave");
                                lcd.setCursor(0,linha_lcd());
                                lcd.print("LIGA RC_T4_Q1");
                                digitalWrite(RC_T4_Q1, LIGA);
                                C_T4_Q1 = true;
                               }
    
                                else    
                                  {Serial.println("DESLIGA R_T_Q1_4 chave");
                                   lcd.setCursor(0,linha_lcd());
                                   lcd.print("DESLIGA RC_T4_Q1");
                                   digitalWrite(RC_T4_Q1, DESLIGA);
                                   C_T4_Q1 = false;
                                  } 
                          }
    

        
                 if ((COMPONENTE1 == "T5") ) // T5 ILUMINAÇÃO LIGA e DESLIGA TOTAL QUARTO 1
                  {Vld_P = 1 ;
     
                    if ( ( CHAVE == 1 ) && (Vld_P == 1) )
                     {Serial.println("LIGA T FULL Q1");
                      lcd.setCursor(0,linha_lcd());
                      lcd.print("LIGA T FULL Q1");
   
                      //LIGA LUZES DO PERFIL 1
                      digitalWrite(R9_T1_Q1, LIGA);
                      C_T1_Q1 = true;
                      digitalWrite(RC_T4_Q1, LIGA);
                      C_T4_Q1 = true;
                      //LIGA LUZES DO PERFIL 2
                      digitalWrite(RA_T2_Q1, LIGA);
                      C_T2_Q1 = true;
                      digitalWrite(RB_T3_Q1, LIGA);
                      C_T3_Q1 = true;
                      Vld_P++ ;
                     } 
    
                    if ( (CHAVE == 2) && (Vld_P == 1))
                     {Serial.println("DESLIGA T FULL Q1");
                      lcd.setCursor(0,linha_lcd());
                      lcd.print("DESLIGA T FULL Q1");
   
                      //DESLIGA LUZES DO PERFIL 1
                      digitalWrite(R9_T1_Q1, DESLIGA);
                      C_T1_Q1 = false;
                      digitalWrite(RC_T4_Q1, DESLIGA);
                      C_T4_Q1 = false;
                      //DESLIGA LUZES DO PERFIL 2
                      digitalWrite(RA_T2_Q1, DESLIGA);
                      C_T2_Q1 = false;
                      digitalWrite(RB_T3_Q1, DESLIGA);}
                      C_T3_Q1 = false;
                      Vld_P++ ; 
                     }
                     
                     
                     }//AÇAO L = LIGAR
 
 
       } //FIM IFs Q1 = QUARTO 1        
       
       
       
       
       
       
       
       
       
       
       
       
       if (COMODO1 ==  "Q2") // SE O COMODO É IGUAL AO Q2=QUARTO1 ENTRA NO BLOCO DE IFs DESSE QUARTO 
    {
      Serial.println("Q2");
               if (COMPONENTE1.substring(0,1) == "L")  // SE O COMPONENTE É IGUAL AO L = LUZ ENTRA NO BLOCO DE IFs DE LUZES
                   Serial.println("LUZ");
                   
                   
                   if ( ACAO1 == "L") //ATIVA OU NAO FUNÇÃO AUTO DE LUZES
                     {
                        if ( ((COMPONENTE1) == "L1")) // RELE_1 LIZ_1
                           {
                            if (CHAVE == 1)  
                               {Serial.println("liga R1_L1_Q2 chave");
                                lcd.setCursor(0,linha_lcd());
                                lcd.print("Liga R1_L1_Q2");         
                                digitalWrite(R1_L1_Q2, LIGA);
                                C_L1_Q2 = true;  
                             }

                                 else    
                                   {Serial.println("desliga R1_L1_Q2 chave");
                                    lcd.setCursor(0,linha_lcd());
                                    lcd.print("Desliga R1_L1_Q2");
                                    digitalWrite(R1_L1_Q2, DESLIGA);
                                    C_L1_Q2 = false; 
                                   } 
                        } 
    
                        if (  ((COMPONENTE1) == "L2") )
                         {
                             if (CHAVE == 1)  
                               {Serial.println("liga R2_L2_Q2 chave");
                                lcd.setCursor(0,linha_lcd());
                                lcd.print("Liga R2_L2_Q2");
                                digitalWrite(R2_L2_Q2, LIGA);
                                C_L2_Q2 = true;  
                             }
    
                                 else    
                                   {Serial.println("desliga R2_L2_Q2 chave");
                                    lcd.setCursor(0,linha_lcd());
                                    lcd.print("Desliga R2_L2_Q2");
                                    digitalWrite(R2_L2_Q2, DESLIGA);
                                    C_L2_Q2 = false; 
                                   } 
                          }
    
                        if (  ((COMPONENTE1) == "L3") )
                         {
                           if (CHAVE == 1)  
                               {Serial.println("liga R3_L3_Q2 chave");
                                lcd.setCursor(0,linha_lcd());
                                lcd.print("Liga R3_L3_Q2");
                                digitalWrite(R3_L3_Q2, LIGA);
                                C_L3_Q2 = true;
                               }
    
                                 else    
                                   {Serial.println("desliga R3_L3_Q2 chave");
                                    lcd.setCursor(0,linha_lcd());
                                    lcd.print("Desliga R3_L3_Q2");
                                    digitalWrite(R3_L3_Q2, DESLIGA);
                                    C_L3_Q2 = false;
                                   } 
                         }
    
                        if (((COMPONENTE1) == "L4") )
                         {
                             if (CHAVE == 1)  
                               {Serial.println("liga R4_L4_Q2 chave");
                                lcd.setCursor(0,linha_lcd());
                                lcd.print("Liga R4_L4_Q2");
                                digitalWrite(R4_L4_Q2, LIGA);
                                C_L4_Q2 = true;
                               }
    
                                else    
                                  {Serial.println("desliga R4_L4_Q2 chave");
                                   lcd.setCursor(0,linha_lcd());
                                   lcd.print("Desliga R4_L4_Q2");
                                   digitalWrite(R4_L4_Q2, DESLIGA);
                                   C_L4_Q2 = false;
                                  } 
                          }
    
                       // PERFIL ILUMINAÇÃO QUARTO 1
                         if ( (COMPONENTE1 == "L5") ) // ILUMINAÇÃO PRINCIPAL  L5=PERFIL 1 
                          {Vld_P = 1 ;
                             if ( (CHAVE == 2) && (CHAVE == 2) && (Vld_P == 1))  
                              {Serial.println("DESLIGA R1_L1_Q2 e R4_L4_Q2 PERFIL PRINCIPAL");
                               lcd.setCursor(0,linha_lcd());
                               lcd.print("DESLIGA PERFIL 01");
                               digitalWrite(R1_L1_Q2, DESLIGA);
                               C_L1_Q2 = false;
                               digitalWrite(R4_L4_Q2, DESLIGA);
                               C_L4_Q2 = false;
                               Vld_P++ ;
                               } 

                          if ( ((CHAVE == 1) || (CHAVE == 1)) && (Vld_P == 1))  
                           {Serial.println("LIGA R1_L1_Q2 e R4_L4_Q2 PERFIL PRINCIPAL");
                            lcd.setCursor(0,linha_lcd());
                            lcd.print("LIGA PERFIL 01");
   
                            //DESLIGA LUZES DO PERFIL 2
                            digitalWrite(R2_L2_Q2, DESLIGA);
                            C_L2_Q2 = false;
                            digitalWrite(R3_L3_Q2, DESLIGA);
                            C_L3_Q2 = false;
                             
                            //LIGA LUZES DO PERFIL 1
                            digitalWrite(R1_L1_Q2, LIGA);
                            C_L1_Q2 = true;
                            digitalWrite(R4_L4_Q2, LIGA); 
                            C_L4_Q2 = true;
                            Vld_P++ ; 
                            }
                          }


                      if (  (COMPONENTE1 == "L6") ) // ILUMINAÇÃO QUARTO 1  L6 = DECORATIVA PERFIL 2 
                       {Vld_P = 1 ;
                         if ((CHAVE == 2) && (CHAVE == 2) && (Vld_P == 1))  
                          {Serial.println("DESLIGA R2_L2_Q2 e R3_L3_Q2 PERFIL PRINCIPAL");
                           lcd.setCursor(0,linha_lcd());
                           lcd.print("DESLIGA PERFIL 02");
                           digitalWrite(R2_L2_Q2, DESLIGA);
                           C_L2_Q2 = false;
                           digitalWrite(R3_L3_Q2, DESLIGA);
                           C_L3_Q2 = false;
                           Vld_P++ ;
                          } 
    
                          if ( ((CHAVE == 1) || (CHAVE == 1)) && (Vld_P == 1))  
                           {Serial.println("LIGA R2_L2_Q2 e R3_L3_Q2 PERFIL PRINCIPAL");
                            lcd.setCursor(0,linha_lcd());
                            lcd.print("LIGA PERFIL 02");
   
                            //DESLIGA LUZES DO PERFIL 1
                            digitalWrite(R1_L1_Q2, DESLIGA);
                            C_L1_Q2 = false;
                            digitalWrite(R4_L4_Q2, DESLIGA);
                            C_L4_Q2 = false;
                            
                            //LIGA LUZES DO PERFIL 2
                            digitalWrite(R2_L2_Q2, LIGA);
                            C_L2_Q2 = true;  
                            digitalWrite(R3_L3_Q2, LIGA); 
                            C_L3_Q2 = true;
                            Vld_P++ ;
                           } 
                  }
    
    
    
    
    
                 if ((COMPONENTE1 == "L7") ) // L7 ILUMINAÇÃO LIGA e DESLIGA TOTAL QUARTO 1
                  {Vld_P = 1 ;
     
                    if ( (CHAVE == 1 ) && (Vld_P == 1))
                     {Serial.println("LIGA L FULL Q2");
                      lcd.setCursor(0,linha_lcd());
                      lcd.print("LIGA L FULL Q2");
   
                      //LIGA LUZES DO PERFIL 1
                      digitalWrite(R1_L1_Q2, LIGA);
                      C_L1_Q2 = true;
                      digitalWrite(R4_L4_Q2, LIGA);
                      C_L4_Q2 = true;
                      //LIGA LUZES DO PERFIL 2
                      digitalWrite(R2_L2_Q2, LIGA);
                      C_L2_Q2 = true;
                      digitalWrite(R3_L3_Q2, LIGA);
                      C_L3_Q2 = true;
                      Vld_P++ ;
                     } 
    
                    if ( (CHAVE == 2 ) && (Vld_P == 1))
                     {Serial.println("DESLIGA L FULL Q2");
                      lcd.setCursor(0,linha_lcd());
                      lcd.print("DESLIGA L FULL Q2");
                      
                      //DESLIGA LUZES DO PERFIL 1
                      digitalWrite(R1_L1_Q2, DESLIGA);
                      C_L1_Q2 = false;
                      digitalWrite(R4_L4_Q2, DESLIGA);
                      C_L4_Q2 = false;
                      //DESLIGA LUZES DO PERFIL 2
                      digitalWrite(R2_L2_Q2, DESLIGA);
                      C_L2_Q2 = false;
                      digitalWrite(R3_L3_Q2, DESLIGA);} 
                      C_L3_Q2 = false;
                      Vld_P++ ; 
                     }
                     
                     
                 }//AÇAO L = LIGAR
                     
                     
                     
                    
                      //TOMADAS                    
                      if ( (COMPONENTE1.substring(0,1)) == "T")  // SE O COMPONENTE É IGUAL AO L = LUZ ENTRA NO BLOCO DE IFs DE LUZES
                     Serial.println("TOMADA");
                     
                   if ( ACAO1 == "L") //LIGA DESLIGA
                     {
                        if ( ((COMPONENTE1) == "T1")) // RELE_1 LIZ_1
                           {
                            if (CHAVE == 1)  
                               {Serial.println("LIGA R5_T1_Q2 chave");
                                lcd.setCursor(0,linha_lcd());
                                lcd.print("LIGA R5_T1_Q2");
                                digitalWrite(R5_T1_Q2, LIGA);
                                C_T1_Q2 = true;  
                             }
    
                                 else    
                                   {Serial.println("DESLIGA R5_T1_Q2 chave");
                                    lcd.setCursor(0,linha_lcd());
                                    lcd.print("DESLIGA R5_T1_Q2");
                                    digitalWrite(R5_T1_Q2, DESLIGA);
                                    C_T1_Q2 = false; 
                                   } 
                        } 
    
                        if (  ((COMPONENTE1) == "T2") )
                         {
                             if (CHAVE == 1)  
                               {Serial.println("LIGA R6_T2_Q2 chave");
                                lcd.setCursor(0,linha_lcd());
                                lcd.print("LIGA R6_T2_Q2");
                                digitalWrite(R6_T2_Q2, LIGA);
                                C_T2_Q2 = true;  
                             }
    
                                 else    
                                   {Serial.println("DESLIGA R6_T2_Q2 chave");
                                    lcd.setCursor(0,linha_lcd());
                                    lcd.print("DESLIGA R6_T2_Q2");
                                    digitalWrite(R6_T2_Q2, DESLIGA);
                                    C_T2_Q2 = false; 
                                   } 
                          }
    
                        if (  ((COMPONENTE1) == "T3") )
                         {
                           if (CHAVE == 1)  
                               {Serial.println("LIGA R7_T3_Q2 chave");
                                lcd.setCursor(0,linha_lcd());
                                lcd.print("LIGA R7_T3_Q2");
                                digitalWrite(R7_T3_Q2, LIGA);
                                C_T3_Q2 = true;
                               }
    
                                 else    
                                   {Serial.println("DESLIGA R7_T3_Q2 chave");
                                    lcd.setCursor(0,linha_lcd());
                                    lcd.print("DESLIGA R7_T3_Q2");
                                    digitalWrite(R7_T3_Q2, DESLIGA);
                                    C_T3_Q2 = false;
                                   } 
                         }
    
                        if (((COMPONENTE1) == "T4") )
                         {
                             if(CHAVE == 1)  
                               {Serial.println("LIGA R8_T4_Q2 chave");
                                lcd.setCursor(0,linha_lcd());
                                lcd.print("LIGA R8_T4_Q2");
                                digitalWrite(R8_T4_Q2, LIGA);
                                C_T4_Q2 = true;
                               }
    
                                else    
                                  {Serial.println("DESLIGA R8_T4_Q2 chave");
                                   lcd.setCursor(0,linha_lcd());
                                   lcd.print("DESLIGA R8_T4_Q2");
                                   digitalWrite(R8_T4_Q2, DESLIGA);
                                   C_T4_Q2 = false;
                                  } 
                          }
    

        
                 if ((COMPONENTE1 == "T5") ) // T5 ILUMINAÇÃO LIGA e DESLIGA TOTAL QUARTO 1
                  {Vld_P = 1 ;
     
                    if ( ( CHAVE == 1 ) && (Vld_P == 1) )
                     {Serial.println("LIGA T FULL Q2");
                      lcd.setCursor(0,linha_lcd());
                      lcd.print("LIGA T FULL Q2");
   
                      //LIGA LUZES DO PERFIL 1
                      digitalWrite(R5_T1_Q2, LIGA);
                      C_T1_Q2 = true;
                      digitalWrite(R8_T4_Q2, LIGA);
                      C_T4_Q2 = true;
                      //LIGA LUZES DO PERFIL 2
                      digitalWrite(R6_T2_Q2, LIGA);
                      C_T2_Q2 = true;
                      digitalWrite(R7_T3_Q2, LIGA);
                      C_T3_Q2 = true;
                      Vld_P++ ;
                     } 
    
                    if ( (CHAVE == 2) && (Vld_P == 1))
                     {Serial.println("DESLIGA T FULL Q2");
                      lcd.setCursor(0,linha_lcd());
                      lcd.print("DESLIGA T FULL Q2");
   
                      //DESLIGA LUZES DO PERFIL 1
                      digitalWrite(R5_T1_Q2, DESLIGA);
                      C_T1_Q2 = false;
                      digitalWrite(R8_T4_Q2, DESLIGA);
                      C_T4_Q2 = false;
                      //DESLIGA LUZES DO PERFIL 2
                      digitalWrite(R6_T2_Q2, DESLIGA);
                      C_T2_Q1 = false;
                      digitalWrite(R7_T3_Q2, DESLIGA);}
                      C_T3_Q2 = false;
                      Vld_P++ ; 
                     }
                     
                     
                     }//AÇAO L = LIGAR
 
 
       } //FIM IFs Q1 = QUARTO 1        
    }//FIM VALIDAÇÃO DIGITOS VERIFICADORES DO PROTOCOLO    
}
//------------------------FUNC_TEMP()----------------------------------//






















//------------------------linha_lcd()----------------------------------//
  int linha_lcd(){
     if (linha < 3)
       {
        linha = linha + 1;
        lcd.setCursor(0,linha);
        lcd.print("                    ");    
        }
          else
              {linha = 0;
               lcd.setCursor(0,linha);
               //lcd.print("                    ");
               lcd.clear();
              }
   return linha;  
   } 
//------------------------linha_lcd()----------------------------------//   
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
   
   
//------------------------CALC_TEMP(int Q)----------------------------------//      
String CALC_TEMP(int Q){
 
 String time = rtc.getTimeStr();
  //time = "00:10:00";
    
    //IMPRIME HORARIO DA AÇÃO
    Serial.println(time);
    
    //DESMENBRA A STRING EM HORAS, MINUTOS E SEGUNDOS 
    String hora    = time.substring(0,2);
    String minuto  = time.substring(3,5);
    String segundo = time.substring(6,8);
     
     //TRANSFORMA STRING EM INT
     int HORA = atoi( hora.c_str() );
     int MINUTO = atoi( minuto.c_str() );
     
     //TRATA RELAÇÃO HORA MINUTO
     if ( Q == 1)
     {MINUTO = MINUTO + TEMP_AUTO_Q1;}
     
     if ( Q == 2)
     {MINUTO = MINUTO + TEMP_AUTO_Q2;} 
     
     if ( Q == 3)
     {MINUTO = MINUTO + TEMP_AUTO_Q3;}
     
     if ( Q == 4)
     {MINUTO = MINUTO + TEMP_AUTO_Q4;} 
     
     
     if (MINUTO > 59)
     
     {if (HORA == 23)
       {HORA = 0;}
         else
          {HORA++ ;}
     MINUTO = MINUTO - 60;}
     
     //Serial.println(HORA);
     //Serial.println(MINUTO);
     //TRANSFORMA RESULTADO EM STRING NOVAMENTE
     hora = String(HORA);
     if (hora.length() == 1)
     {hora = ("0" + hora);}
     minuto = String(MINUTO);
     if (minuto.length() == 1)
     {minuto = ("0" + minuto);}
     Serial.println(hora + ":" + minuto + ":" + segundo);
  return (hora + ":" + minuto + ":" + segundo);
} 
//------------------------CALC_TEMP(int Q)----------------------------------//

























//------------------------comando_wifi----------------------------------//
String comando_wifi(){
  String result;
  //Serial.println("inicia leitura wifi");  
  //Variavel para buffer de dados de trasmissao
    uint8_t buffer[128] = {0};
 
    //Como usamos multiplas conexoes, cada conexao tem sua ID, e precisa ser armazenada para referencia no programa. Usamos    
    //essa variavel para isso.
    uint8_t mux_id;
    
    //E esta variavel len serve para armazenar o comprimento de dados recebidos por meio da rotina wifi.recv(), que tambem     
    //associa ao buffer os dados recebidos e ao mux_id a id responsavel pela transmissao
    uint32_t len = wifi.recv(&mux_id, buffer, sizeof(buffer), 20);
    
    if (len > 0) {
      Serial.println("lendo wifi");
        digitalWrite(BOZINA_Q1,HIGH);
        delay(50);
        digitalWrite(BOZINA_Q1,LOW); 
        /*
        Serial.print("Status:[");
        Serial.print(wifi.getIPStatus().c_str());
        Serial.println("]");
        
        Serial.print("Recebido de :");
        Serial.print(mux_id);
        Serial.println("[");
        */
        for(uint32_t i = 0; i < len; i++) {
            //Serial.print((char)buffer[i]);
            result = result + (char)buffer[i];
        }
       // Serial.print("]\r\n");
        
        //Agora envia de volta. A referencia para o socket TCP criado é o mux_id, ou id da conexao, usado aqui na rotina
        //wifi.send, veja abaixo:
       //if(wifi.send(mux_id, buffer, len)) {
          // Serial.print("Enviado de volta...\r\n");
        //} else {
          //  Serial.print("Erro ao enviar de volta\r\n");
        //}
         
        //E, como sempre, liberar a conexao TCP, de modo a permitir que novas conexoes sejam realizadas.
      // if (wifi.releaseTCP()) {
       //     Serial.print("Liberando conexao TCP com ID: ");
         //   Serial.print(mux_id);
        //    Serial.println(" OK");
       // } else {
        //   Serial.print("Erro ao liberar TCP com ID: ");
        //    Serial.print(mux_id);
     //  }
       /*
        Serial.print("Status:[");
        Serial.print(wifi.getIPStatus().c_str());
        Serial.println("]");
        */   
    }
    //Serial.println("finaliza leitura wifi"); 
  return result;
}
//------------------------comando_wifi----------------------------------//















//------------------------reset_wifi----------------------------------//
void reset_wifi()
{  
  lcd.setBacklight(LOW);
  digitalWrite(BOZINA_Q1,HIGH);
  delay(50);
  digitalWrite(BOZINA_Q1,LOW);
  delay(90);
  digitalWrite(BOZINA_Q1,HIGH);
  delay(50);
  digitalWrite(BOZINA_Q1,LOW);
  delay(90);
  digitalWrite(BOZINA_Q1,HIGH);
  delay(50);
  digitalWrite(BOZINA_Q1,LOW);
  delay(90);
  lcd.setBacklight(HIGH);
  lcd.setCursor(0,linha_lcd());
  lcd.print("Iniciando Setup");
  Serial.println("Iniciando Setup.");
  
  lcd.setCursor(0,linha_lcd());
  lcd.print("Reset fisico ESP");
  Serial.println("Reset fisico ESP");
  digitalWrite(RST,LOW);
  delay(100);
  digitalWrite(RST,HIGH);
  delay(4000);
  lcd.setCursor(0,linha_lcd()); 
  lcd.print("Reset logico ESP");
  Serial.println("Reset logico ESP");
  
  if (wifi.restart()) 
    {Serial.println("reset WIFI OK.");
     lcd.setCursor(0,linha_lcd());
     lcd.print("reset WIFI OK.");
     if (wifi.setOprToStation())        
       {Serial.println("Station OK.");
        lcd.setCursor(0,linha_lcd());
        lcd.print("Station OK.");
        if (wifi.joinAP(SSID, PASSWORD)) 
          {Serial.println("Conectado com Sucesso.");
           lcd.setCursor(0,linha_lcd());
           lcd.print("Conectado ");
           Serial.println("IP: ");
           lcd.setCursor(0,linha_lcd());
           lcd.print("IP:");
           //rotina wifi.getLocalIP() retorna o IP usado na conexao com AP conectada.
           Serial.println(wifi.getLocalIP());    
           lcd.print(wifi.getLocalIP().substring(14,30));
           //delay(2000);   //MODIFIQUEI
           if (wifi.enableMUX()) 
             {Serial.println("Multiplas conexoes OK.");
              lcd.setCursor(0,linha_lcd());
              lcd.print("MultI conexoes OK.");
              //delay(500);   //MODIFIQUEI
             if (wifi.startTCPServer(8090)) 
               {Serial.println("SERV port 8090 OK");
                lcd.setCursor(0,linha_lcd());
                lcd.print("SERV port 8090 OK");
                if (wifi.setTCPServerTimeout(10)) 
                  {Serial.println("timout 10 seconds");
                   lcd.setCursor(0,linha_lcd());
                   lcd.print("timout 10 seconds");
                   lcd.setCursor(0,linha_lcd());
                   lcd.print("Setup finalizado!");
                   Serial.println("Setup finalizado!");
                   //delay(1500);     //MODIFIQUEI
                   lcd.clear();
                   Serial.println("SMART_HOME");
                   linha = -1; 
                   //delay(1000);
                   //lcd.setBacklight(LOW);
                   digitalWrite(BOZINA_Q1,HIGH);
                   delay(60);
                   digitalWrite(BOZINA_Q1,LOW);
                  }
                  else {Serial.println("Erro server timout");
                  //lcd.clear ();
                  lcd.setCursor(0,linha_lcd());
                  lcd.print("Erro server timout");
        reset_wifi();}
                  
               }
              else {Serial.println("Erro INIC Serv TCP");
              //lcd.clear ();
              lcd.setCursor(0,linha_lcd());
              lcd.print("Erro INIC Serv TCP");
        reset_wifi();} 
             }
             else {Serial.println("Erro Multi conex");
                   //lcd.clear ();
                   lcd.setCursor(0,linha_lcd());
                   lcd.print("Erro Multi conex");
        reset_wifi();}
          }
          else {Serial.println("Erro ConectaR AP");
                //lcd.clear ();
                lcd.setCursor(0,linha_lcd());
                lcd.print("Erro ConectaR AP");
        reset_wifi();}
       }
       else {Serial.println("Erro SET WIFI Station");
             //lcd.clear ();
             lcd.setCursor(0,linha_lcd());
             lcd.print("Erro SET WF Station");
        reset_wifi();}
    } 
    
    else {Serial.println("Erro resetar WIFI");
          //lcd.clear ();
          lcd.setCursor(0,linha_lcd());
          lcd.print("Erro resetar WIFI");
        reset_wifi();}
}
//------------------------reset_wifi----------------------------------//





//------------------------LER SERIAL----------------------------------//
String leStringSerial(){
  String conteudo = "";
  char caractere;
  // Enquanto receber algo pela serial
  while(Serial2.available() > 0) {
    // Lê byte da serial
    caractere = Serial2.read();
    // Ignora caractere de quebra de linha
    if (caractere != '\n'){
      // Concatena valores
      conteudo.concat(caractere);
    }
    // Aguarda buffer serial ler próximo caractere
    delay(10);
  }
 //Serial.print("Recebi: ");
 //Serial.println(conteudo);
 //delay(4000);
 
  return conteudo;
}
//------------------------LER SERIAL----------------------------------//
























void loop()
{      

 HORA_SIST = rtc.getTimeStr();

//String comando;
String comando1 = comando_wifi();
String comando2 = leStringSerial();

if ( comando1 != "" ){
Serial.println("comando1");  
FUNC_COMANDO(comando1, 1);
}
else{
//Serial.println("comando2");  
FUNC_COMANDO(comando2, 1);
}



//----------------SENSOR DE MOVIMENTO QUARTO 1---------------------------//
 if ((digitalRead(S1_PIR_Q1) == HIGH) && (HORA_vild_Q1 == true) && ((A_L1_Q1 ==  true) || (A_L2_Q1 ==  true) || (A_L3_Q1 ==  true) || (A_L4_Q1 ==  true) )    ) //Caso seja detectado um movimento, (A_R_L_Q1_1 == auto_rele_quarto1_luz) && (C_R_L_Q1_1 == chave_rele_quarto1_luz)
   { Serial.println("COM MOVIMENTO");
     lcd.setCursor(0,linha_lcd());
     lcd.print("MOVIMENTO");
     
     HORA_S1_PIR_Q1 = CALC_TEMP(1);  //CALC_TEMP(1) CALCULA TEMPO (1)= QUARTO 1 
     HORA_vild_Q1 = false;
     
    if ((A_L1_Q1 ==  true) && (C_L1_Q1 == false))
     {digitalWrite(R1_L1_Q1, LIGA);
      Serial.println("COM MOVIMENTO_1");
      lcd.setCursor(0,linha_lcd());
      lcd.print("MOVIMENTO L1");
      
      //A_R1_L1_Q1 = true;
     }
    
    if ((A_L2_Q1 == true) && (C_L2_Q1 == false))
     {digitalWrite(R2_L2_Q1, LIGA);
      Serial.println("COM MOVIMENTO_2");
      lcd.setCursor(0,linha_lcd());
      lcd.print("MOVIMENTO L2");
      //A_R2_L2_Q1 = true;
     }
    
    if ((A_L3_Q1 == true) && (C_L3_Q1 == false))
     {digitalWrite(R3_L3_Q1, LIGA);
      Serial.println("COM MOVIMENTO_3");
      lcd.setCursor(0,linha_lcd());
      lcd.print("MOVIMENTO L3");
      //A_R3_L3_Q1 = true;
     }
  
    if ((A_L4_Q1 == true) && (C_L4_Q1 == false))
     {digitalWrite(R4_L4_Q1, LIGA);
      Serial.println("COM MOVIMENTO_4");
      lcd.setCursor(0,linha_lcd());
      lcd.print("MOVIMENTO L4");
      //A_R4_L4_Q1 = true;
     }  
   
    }//função auto ligar desligar   
 //Serial.print("TEMP: "); 
 //Serial.println(HORA_S1_PIR_Q1.substring(0,7));
 //Serial.print("HORA SISTEMA: ");
 //Serial.println(HORA_SIST.substring(0,7));
 
 if ((HORA_S1_PIR_Q1.substring(0,7) == HORA_SIST.substring(0,7)) && (HORA_vild_Q1 == false))  //Caso seja detectado um movimento, (A_R_L_Q1_1 == auto_rele_quarto1_luz) && (C_R_L_Q1_1 == chave_rele_quarto1_luz)
   {Serial.print("temp chegou: ");
    lcd.setCursor(0,linha_lcd());
    lcd.print("temp chegou: ");
    lcd.print(HORA_SIST);
    Serial.println(HORA_SIST); 
    
    if ((digitalRead(S1_PIR_Q1) == HIGH)) 
    {Serial.println("ainda COM MOVIMENTO entAo nAo deslige e calcule tempo de novo");
     lcd.setCursor(0,linha_lcd());
     lcd.print("MOVIMENTO");
     HORA_S1_PIR_Q1 = CALC_TEMP(1);  //CALCULA TEMPO (1)= QUARTO 1 
     
    if ((A_L1_Q1 ==  true) && (C_L1_Q1 == false))
     {digitalWrite(R1_L1_Q1, LIGA);
      Serial.println("COM MOVIMENTO_1");
      lcd.setCursor(0,linha_lcd());
      lcd.print("MOVIMENTO L1");
      
      //A_R1_L1_Q1 = true;
     }
    
    if ((A_L2_Q1 == true) && (C_L2_Q1 == false))
     {digitalWrite(R2_L2_Q1, LIGA);
      Serial.println("COM MOVIMENTO_2");
      lcd.setCursor(0,linha_lcd());
      lcd.print("MOVIMENTO L2");
      //A_R2_L2_Q1 = true;
     }
    
    if ((A_L3_Q1 == true) && (C_L3_Q1 == false))
     {digitalWrite(R3_L3_Q1, LIGA);
      Serial.println("COM MOVIMENTO_3");
      lcd.setCursor(0,linha_lcd());
      lcd.print("MOVIMENTO L3");
      //A_R3_L3_Q1 = true;
     }
  
    if ((A_L4_Q1 == true) && (C_L4_Q1 == false))
     {digitalWrite(R4_L4_Q1, LIGA);
      Serial.println("COM MOVIMENTO_4");
      lcd.setCursor(0,linha_lcd());
      lcd.print("MOVIMENTO L4");
      //A_R4_L4_Q1 = true;
     }
    }
    else
    {
    HORA_vild_Q1 = true;
    Serial.println("sem movimento desligue");
    if ((A_L1_Q1 ==  true) && (C_L1_Q1 == false))
     {digitalWrite(R1_L1_Q1, DESLIGA);
      Serial.println("desliga temp_auto_1");
      lcd.setCursor(0,linha_lcd());
      lcd.print("desliga temp_auto_1");
      
      //A_R1_L1_Q1 = true;
     }
    
    if ((A_L2_Q1 == true) && (C_L2_Q1 == false))
     {digitalWrite(R2_L2_Q1, DESLIGA);
      Serial.println("desliga temp_auto_2");
      lcd.setCursor(0,linha_lcd());
      lcd.print("desliga temp_auto_2");
      //A_R2_L2_Q1 = true;
     }
    
    if ((A_L3_Q1 == true) && (C_L3_Q1 == false))
     {digitalWrite(R3_L3_Q1, DESLIGA);
      Serial.println("desliga temp_auto_3");
      lcd.setCursor(0,linha_lcd());
      lcd.print("desliga temp_auto_3");
      //A_R3_L3_Q1 = true;
     }
  
    if ((A_L4_Q1 == true) && (C_L4_Q1 == false))
     {digitalWrite(R4_L4_Q1, DESLIGA);
      Serial.println("desliga temp_auto_4");
      lcd.setCursor(0,linha_lcd());
      lcd.print("desliga temp_auto_4");
      //A_R4_L4_Q1 = true;
     }
    
       } //else desligar 
   }
//----------------SENSOR DE MOVIMENTO QUARTO 1---------------------------//
 
  



      
  //____________________________matriz grava tempo desliga liga__________________________________//
      
      String dia = rtc.getDOWStr(FORMAT_SHORT);
      
                 for(int i = 0;i<=indice;i++)
                 {
                 
                   if(HORA_SIST == HORA_ACAO[i][2])
                   {
               if (dia == "Monday"    && HORA_ACAO[i][4].substring(0,1) == "1" )
                  {Serial.println("SEG");
                   Serial.println(" HORA PROGRAMADA PARA LIGAR");
                   Serial.println(HORA_ACAO[i][1]);  
                   FUNC_TEMP(HORA_ACAO[i][1],1);
                  }
               if (dia == "Tuesday"   && HORA_ACAO[i][4].substring(1,2) == "1")  
                  {Serial.println("TER");
                   Serial.println(" HORA PROGRAMADA PARA LIGAR");
                   Serial.println(HORA_ACAO[i][1]);  
                   FUNC_TEMP(HORA_ACAO[i][1],1);
                  } 
               if (dia == "Wednesday" && HORA_ACAO[i][4].substring(2,3) == "1")  
                  {Serial.println("QUA");
                   Serial.println(" HORA PROGRAMADA PARA LIGAR");
                   Serial.println(HORA_ACAO[i][1]);  
                   FUNC_TEMP(HORA_ACAO[i][1],1);
                  }  
               if (dia == "Thursday"  && HORA_ACAO[i][4].substring(3,4) == "1")   
                  {Serial.println("QUI");
                   Serial.println(" HORA PROGRAMADA PARA LIGAR");
                   Serial.println(HORA_ACAO[i][1]);  
                   FUNC_TEMP(HORA_ACAO[i][1],1);
                  }   
               if (dia == "Friday"    && HORA_ACAO[i][4].substring(4,5) == "1")   
                  {Serial.println("SEX");
                   Serial.println(" HORA PROGRAMADA PARA LIGAR");
                   Serial.println(HORA_ACAO[i][1]);  
                   FUNC_TEMP(HORA_ACAO[i][1],1);
                  }   
               if (dia == "Saturday"  && HORA_ACAO[i][4].substring(5,6) == "1")   
                  {Serial.println("SAB");
                   Serial.println(" HORA PROGRAMADA PARA LIGAR");
                   Serial.println(HORA_ACAO[i][1]);  
                   FUNC_TEMP(HORA_ACAO[i][1],1);
                  }   
               if (dia == "Sunday"    && HORA_ACAO[i][4].substring(6,7) == "1")  
                  {Serial.println("DOM");
                   Serial.println(" HORA PROGRAMADA PARA LIGAR");
                   Serial.println(HORA_ACAO[i][1]);  
                   FUNC_TEMP(HORA_ACAO[i][1],1);
                  }
           
                   }
                   
                   if(HORA_SIST == HORA_ACAO[i][3])
                   {
                   
               if (dia == "Monday"    && HORA_ACAO[i][4].substring(0,1) == "1" )
                  {Serial.println("SEG");
                   Serial.println(" HORA PROGRAMADA PARA DESLIGAR");
                   Serial.println(HORA_ACAO[i][1]);  
                   FUNC_TEMP(HORA_ACAO[i][1],2);
                  }
               if (dia == "Tuesday"   && HORA_ACAO[i][4].substring(1,2) == "1")  
                  {Serial.println("TER");
                   Serial.println(" HORA PROGRAMADA PARA DESLIGAR");
                   Serial.println(HORA_ACAO[i][1]);  
                   FUNC_TEMP(HORA_ACAO[i][1],2);
                  } 
               if (dia == "Wednesday" && HORA_ACAO[i][4].substring(2,3) == "1")  
                  {Serial.println("QUA");
                   Serial.println(" HORA PROGRAMADA PARA DESLIGAR");
                   Serial.println(HORA_ACAO[i][1]);  
                   FUNC_TEMP(HORA_ACAO[i][1],2);
                  }  
               if (dia == "Thursday"  && HORA_ACAO[i][4].substring(3,4) == "1")   
                  {Serial.println("QUI");
                   Serial.println(" HORA PROGRAMADA PARA DESLIGAR");
                   Serial.println(HORA_ACAO[i][1]);  
                   FUNC_TEMP(HORA_ACAO[i][1],2);
                  }   
               if (dia == "Friday"    && HORA_ACAO[i][4].substring(4,5) == "1")   
                  {Serial.println("SEX");
                   Serial.println(" HORA PROGRAMADA PARA DESLIGAR");
                   Serial.println(HORA_ACAO[i][1]);  
                   FUNC_TEMP(HORA_ACAO[i][1],2);
                  }   
               if (dia == "Saturday"  && HORA_ACAO[i][4].substring(5,6) == "1")   
                  {Serial.println("SAB");
                   Serial.println(" HORA PROGRAMADA PARA DESLIGAR");
                   Serial.println(HORA_ACAO[i][1]);  
                   FUNC_TEMP(HORA_ACAO[i][1],2);
                  }   
               if (dia == "Sunday"    && HORA_ACAO[i][4].substring(6,7) == "1")  
                  {Serial.println("DOM");
                   Serial.println(" HORA PROGRAMADA PARA DESLIGAR");
                   Serial.println(HORA_ACAO[i][1]);  
                   FUNC_TEMP(HORA_ACAO[i][1],2);
                  }
                  
                   }
                   
                 }//for
                    
   //____________________________matriz grava tempo desliga liga__________________________________//
 
 
 
/*
        digitalWrite(BOZINA_Q1,HIGH);
        delay(50);
        digitalWrite(BOZINA_Q1,LOW);    
        
  if (wifi.kick()) {
       //Serial.println("vivo");
       //Serial.print("Hora : ");
       //Serial.println(HORA_SIST);

      } else {
        Serial.println("ERRO COMUNICACAO WIFI");
        lcd.setCursor(0,linha_lcd());
        lcd.print("ERRO COMUNICACAO WIFI");
        reset_wifi();
      }
    */
 
  
 }//fim void













