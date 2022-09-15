
#define B1_L1_Q1     22  //QUARTO 1 LUZ 1
#define B2_L2_Q1     23  //QUARTO 1 LUZ 2
#define B3_L3_Q1     24  //QUARTO 1 LUZ 3
#define B4_L4_Q1     25  //QUARTO 1 LUZ 4

#define B5_T1_Q1     26  //QUARTO 1 TOMADA 1
#define B6_T2_Q1     27  //QUARTO 1 TOMADA 2
#define B7_T3_Q1     28  //QUARTO 1 TOMADA 3
#define B8_T4_Q1     29  //QUARTO 1 TOMADA 4

#define B1_L1_Q2     30  //QUARTO 2 LUZ 1
#define B2_L2_Q2     31  //QUARTO 2 LUZ 2
#define B3_L3_Q2     32  //QUARTO 2 LUZ 3
#define B4_L4_Q2     33  //QUARTO 2 LUZ 4

#define B5_T1_Q2     34  //QUARTO 2 TOMADA 1
#define B6_T2_Q2     35  //QUARTO 2 TOMADA 2
#define B7_T3_Q2     36  //QUARTO 2 TOMADA 3
#define B8_T4_Q2     37  //QUARTO 2 TOMADA 4

#define B1_L1_Q3     38  //QUARTO 1 LUZ 1
#define B2_L2_Q3     39  //QUARTO 1 LUZ 2
#define B3_L3_Q3     40  //QUARTO 1 LUZ 3
#define B4_L4_Q3     41  //QUARTO 1 LUZ 4

#define B5_T1_Q3     42  //QUARTO 1 TOMADA 1
#define B6_T2_Q3     43  //QUARTO 1 TOMADA 2
#define B7_T3_Q3     44  //QUARTO 1 TOMADA 3
#define B8_T4_Q3     45  //QUARTO 1 TOMADA 4

#define B1_L1_Q4     46  //QUARTO 1 LUZ 1
#define B2_L2_Q4     47  //QUARTO 1 LUZ 2
#define B3_L3_Q4     48  //QUARTO 1 LUZ 3
#define B4_L4_Q4     49  //QUARTO 1 LUZ 4

#define B5_T1_Q4     50  //QUARTO 1 TOMADA 1
#define B6_T2_Q4     51  //QUARTO 1 TOMADA 2
#define B7_T3_Q4     52  //QUARTO 1 TOMADA 3
#define B8_T4_Q4     53  //QUARTO 1 TOMADA 4

void setup() {
  
 //------------------------SERIAL--------------------------//
  Serial.begin(115200); //Inicializa a serial
  Serial3.begin(115200); //Inicializa a serial
 //------------------------SERIAL--------------------------//
  
  pinMode(B1_L1_Q1    ,INPUT_PULLUP); //CONFIGURA PORTA COMO ENTRADA DE SINAL
  pinMode(B2_L2_Q1    ,INPUT_PULLUP); //CONFIGURA PORTA COMO ENTRADA DE SINAL
  pinMode(B3_L3_Q1    ,INPUT_PULLUP); //CONFIGURA PORTA COMO ENTRADA DE SINAL
  pinMode(B4_L4_Q1    ,INPUT_PULLUP); //CONFIGURA PORTA COMO ENTRADA DE SINAL
  
  pinMode(B5_T1_Q1    ,INPUT_PULLUP); //CONFIGURA PORTA COMO ENTRADA DE SINAL
  pinMode(B6_T2_Q1    ,INPUT_PULLUP); //CONFIGURA PORTA COMO ENTRADA DE SINAL
  pinMode(B7_T3_Q1    ,INPUT_PULLUP); //CONFIGURA PORTA COMO ENTRADA DE SINAL
  pinMode(B8_T4_Q1    ,INPUT_PULLUP); //CONFIGURA PORTA COMO ENTRADA DE SINAL
  
  
  
  pinMode(B1_L1_Q2    ,INPUT_PULLUP); //CONFIGURA PORTA COMO ENTRADA DE SINAL
  pinMode(B2_L2_Q2    ,INPUT_PULLUP); //CONFIGURA PORTA COMO ENTRADA DE SINAL
  pinMode(B3_L3_Q2    ,INPUT_PULLUP); //CONFIGURA PORTA COMO ENTRADA DE SINAL
  pinMode(B4_L4_Q2    ,INPUT_PULLUP); //CONFIGURA PORTA COMO ENTRADA DE SINAL
  
  pinMode(B5_T1_Q2    ,INPUT_PULLUP); //CONFIGURA PORTA COMO ENTRADA DE SINAL
  pinMode(B6_T2_Q2    ,INPUT_PULLUP); //CONFIGURA PORTA COMO ENTRADA DE SINAL
  pinMode(B7_T3_Q2    ,INPUT_PULLUP); //CONFIGURA PORTA COMO ENTRADA DE SINAL
  pinMode(B8_T4_Q2    ,INPUT_PULLUP); //CONFIGURA PORTA COMO ENTRADA DE SINAL
  
  
  
  pinMode(B1_L1_Q3    ,INPUT_PULLUP); //CONFIGURA PORTA COMO ENTRADA DE SINAL
  pinMode(B2_L2_Q3    ,INPUT_PULLUP); //CONFIGURA PORTA COMO ENTRADA DE SINAL
  pinMode(B3_L3_Q3    ,INPUT_PULLUP); //CONFIGURA PORTA COMO ENTRADA DE SINAL
  pinMode(B4_L4_Q3    ,INPUT_PULLUP); //CONFIGURA PORTA COMO ENTRADA DE SINAL
  
  pinMode(B5_T1_Q3    ,INPUT_PULLUP); //CONFIGURA PORTA COMO ENTRADA DE SINAL
  pinMode(B6_T2_Q3    ,INPUT_PULLUP); //CONFIGURA PORTA COMO ENTRADA DE SINAL
  pinMode(B7_T3_Q3    ,INPUT_PULLUP); //CONFIGURA PORTA COMO ENTRADA DE SINAL
  pinMode(B8_T4_Q3    ,INPUT_PULLUP); //CONFIGURA PORTA COMO ENTRADA DE SINAL
  
  
  
  pinMode(B1_L1_Q4    ,INPUT_PULLUP); //CONFIGURA PORTA COMO ENTRADA DE SINAL
  pinMode(B2_L2_Q4    ,INPUT_PULLUP); //CONFIGURA PORTA COMO ENTRADA DE SINAL
  pinMode(B3_L3_Q4    ,INPUT_PULLUP); //CONFIGURA PORTA COMO ENTRADA DE SINAL
  pinMode(B4_L4_Q4    ,INPUT_PULLUP); //CONFIGURA PORTA COMO ENTRADA DE SINAL
  
  pinMode(B5_T1_Q4    ,INPUT_PULLUP); //CONFIGURA PORTA COMO ENTRADA DE SINAL
  pinMode(B6_T2_Q4    ,INPUT_PULLUP); //CONFIGURA PORTA COMO ENTRADA DE SINAL
  pinMode(B7_T3_Q4    ,INPUT_PULLUP); //CONFIGURA PORTA COMO ENTRADA DE SINAL
  pinMode(B8_T4_Q4    ,INPUT_PULLUP); //CONFIGURA PORTA COMO ENTRADA DE SINAL
  
  }

void loop() {
  // put your main code here, to run repeatedly:

 if ( digitalRead(B1_L1_Q1) == LOW ) // verifica se o botão para buzina foi apertado
   {Serial3.println("#Q1*L1*L*D0000*L0000@");
    Serial.println("#Q1*L1*L*D0000*L0000@");
    delay(300);} 
 
 if ( digitalRead(B2_L2_Q1) == LOW ) // verifica se o botão para buzina foi apertado
   {Serial3.println("#Q1*L2*L*D0000*L0000@");
    Serial.println("#Q1*L2*L*D0000*L0000@");
    delay(300);} 
     
 if ( digitalRead(B5_T1_Q1) == LOW ) // verifica se o botão para buzina foi apertado
   {Serial3.println("#Q1*T1*L*D0000*L0000@");
    Serial.println("#Q1*L2*L*D0000*L0000@");
    delay(300);}   
 
 
 
 
   
}
