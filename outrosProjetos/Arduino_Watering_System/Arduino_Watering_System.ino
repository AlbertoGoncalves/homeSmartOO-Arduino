/*
#####################################################################################
#  	File:               Arduino_Watering_sustem.ino                                             
#       Processor:          Arduino UNO, MEGA ou Teensy++ 2.0      
#  	Language:	    Wiring / C /Processing /Fritzing / Arduino IDE          
#						
#	Objectives:         Watering System - Irrigation
#										  
#	Behavior:	    When the soil is dry,
#                           
#
#			
#   Author:                 Marcelo Moraes 
#   Date:                   12/10/12	
#   place:                  Brazil, Sorocaba City	
#					
#####################################################################################
 
  This project contains public domain code.
  The modification is allowed without notice.
  
 */

// libraries definition
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "RTClib.h"



// frequency musical notes
#define NOTE_C6  1047
#define NOTE_C3  131
#define NOTE_G3  196

// pins definition
int NIVELSensorPin = 0;
int humidSensorPin = 1;
int audioPin = 2;
int encharcLEDPin = 3;
int soloUmidoLEDPin = 4;
int soloSecoLEDPin = 5;
int bombaLEDPin = 6;
int bombaPin = 7;

// variables
int NIVELSensorValue;       // armazena os valores do sensor de nível
int umidadeSensorValue;    // armazena os valores do sensor de umidade
int j = 0;

// system messages
const char *string_table[] =
{   
  "    Bem Vindo! = )",
  "nivel BAIXO tanque",
  "      Solo Seco",
  "     Solo Umido",
  "  Solo Encharcado!",
  "Ligada Bomba de Agua",
  "    IRRIG-AUTO",
  "     AGROBRAS",
  "  Por favor, espere!"
};

// objects definition
RTC_DS1307 RTC;
LiquidCrystal_I2C lcd(0x27,20,4);


void setup(){
  // serial initialization
  Serial.begin(9600);
  
  // LCD initialization
  lcd.init();          
  lcd.backlight();     // with Backlight
  lcd.clear();         // clearscreen
  
  // Wire initialization
  Wire.begin();
  
  // RTC initialization
  RTC.begin();
  if (!RTC.isrunning()){
    // data e hora ajustar como a data e hora do computador PC
    RTC.adjust(DateTime(__DATE__, __TIME__)); 
  }
  
  // Arduino pins initalization
  pinMode(audioPin, OUTPUT);
  pinMode(encharcLEDPin, OUTPUT);
  pinMode(soloUmidoLEDPin,OUTPUT);
  pinMode(soloSecoLEDPin,OUTPUT);
  pinMode(bombaLEDPin,OUTPUT);
  
            
  pinMode( bombaPin,OUTPUT);
  
  // desligar a bomba
  digitalWrite( bombaPin,HIGH);
  
  // LCD initial messages
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(string_table[6]); 
  lcd.setCursor(0,1);
  lcd.print(string_table[7]); 
  lcd.setCursor(0,3);
  lcd.print(string_table[0]); 
  // initialization delay
  delay(5000); 
}


void loop(){
  
  
  // RTC definição de parâmetros
  DateTime myRTC = RTC.now();
  int H = myRTC.hour();
  int M = myRTC.minute();
  int S = myRTC.second();
  
  // chamada de função Relógio
  //RightHour();
  
  // lê os sensores
  NIVELSensorValue = analogRead(NIVELSensorPin);
  umidadeSensorValue = analogRead(humidSensorPin);
  Serial.println(umidadeSensorValue);
  
  // se baixo nível de água : toca o alarme de baixo nível
  /*
  if(NIVELSensorValue > 600){
    // mensagens do sistema
    lcd.clear();
    RightHour();
    lcd.setCursor(0,3);
    lcd.print(string_table[1]); 
    // reproduz o som de alarme
    for(int i=0;i<2;i++){
      tone(audioPin, NOTE_G3, 200);
      delay(200);
      tone(audioPin, NOTE_C3, 200);
      delay(200);
      noTone(audioPin);
    }
  }
  */
  
  // verifique a faixa de umidade
  if(umidadeSensorValue >= 700){
    // em caso de solo seco :
    // mensagens do sistema
    lcd.clear();
    RightHour();
    lcd.setCursor(0,3);
    lcd.print(string_table[2]);
    // acende-se o LED correto
    digitalWrite(soloSecoLEDPin,HIGH);
    digitalWrite(soloUmidoLEDPin,LOW);
    digitalWrite(encharcLEDPin,LOW);
    // reproduz o som de alarme
    tone(audioPin, NOTE_C6, 100);
    delay(250);
    noTone(audioPin);
  }
  if((umidadeSensorValue < 700) && (umidadeSensorValue >= 300)){
    // em caso de solo úmido :
    // mensagens do sistema
    lcd.clear();
    RightHour();
    lcd.setCursor(0,3);
    lcd.print(string_table[3]);
    // acende-se o LED correto
    digitalWrite(soloSecoLEDPin,LOW);
    digitalWrite(soloUmidoLEDPin,HIGH);
    digitalWrite(encharcLEDPin,LOW);
    delay(250);
  }
  if(umidadeSensorValue < 200){
    // no caso de solo encharcado :
    // mensagens do sistema
    lcd.clear();
    RightHour();
    lcd.setCursor(0,3);
    lcd.print(string_table[4]); 
    // lights up the correct LED
    digitalWrite(soloSecoLEDPin,LOW);
    digitalWrite(soloUmidoLEDPin,LOW);
    digitalWrite(encharcLEDPin,HIGH);
    delay(100);
  }
  
  // Se o solo está seco e se é o momento certo : ligar a bomba durante 1 minuto
  if((H == 01) && (M == 47) && (S == 00)){
    Serial.println("deu a hora");
    while(umidadeSensorValue >= 700){
      // system messages
      lcd.clear();
      RightHour();
      lcd.setCursor(0,1);
      lcd.print(string_table[8]);
      lcd.setCursor(0,3);
      lcd.print(string_table[5]);
      // turn the pump on
      digitalWrite( bombaPin,LOW);
      Serial.println("ligar bomba");
      digitalWrite(bombaLEDPin,HIGH);
      delay(800);
      
      // turn the pump off
    digitalWrite( bombaPin,HIGH);
    Serial.println("desligar bomba");
    digitalWrite(bombaLEDPin,LOW);
    Serial.println(umidadeSensorValue);
      
      delay(2000);
      
      // se o solo não ESTA úmido até agora
      // Lê o sensor de humidade mais uma vez
      umidadeSensorValue = analogRead(humidSensorPin);
      Serial.println(umidadeSensorValue);
    }
    // turn the pump off
    digitalWrite( bombaPin,HIGH);
    Serial.println("desligar bomba");
    digitalWrite(bombaLEDPin,LOW);
    Serial.println(umidadeSensorValue);
  }
  
  
  // Se o solo está seco e se é o momento certo : ligar a bomba durante 1 minuto
  if((H == 23) && (M == 40) && (S == 00)){
    Serial.println("deu a hora");
    while(umidadeSensorValue >= 700){
      // system messages
      lcd.clear();
      RightHour();
      lcd.setCursor(0,1);
      lcd.print(string_table[8]);
      lcd.setCursor(0,3);
      lcd.print(string_table[5]);
      // turn the pump on
      digitalWrite( bombaPin,LOW);
      Serial.println("ligar bomba");
      digitalWrite(bombaLEDPin,HIGH);
      delay(10000);
      // se o solo não ESTA úmido até agora
      // Lê o sensor de humidade mais uma vez
      umidadeSensorValue = analogRead(humidSensorPin);
      Serial.println(umidadeSensorValue);
    }
    // turn the pump off
    digitalWrite( bombaPin,HIGH);
    digitalWrite(bombaLEDPin,LOW);
    Serial.println(umidadeSensorValue);
  }
  
}

// Função Time Clock real
void RightHour()
{
  DateTime Now = RTC.now();
  String clock_date = "  Date: ";
  String clock_hour = "   Time: ";
  
  int _day = Now.day();
  int _month = Now.month();
  int _year = Now.year();
  
  clock_date += fixZero(_day);
  clock_date += "/";
  clock_date += fixZero(_month);
  clock_date += "/";
  clock_date += _year;
  
  int _hour = Now.hour();
  int _minute = Now.minute();
  int _second = Now.second();
  
  clock_hour += fixZero(_hour);
  clock_hour += ":";
  clock_hour += fixZero(_minute);
  clock_hour += ":";
  clock_hour += fixZero(_second);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(clock_date);
  lcd.setCursor(0, 1);
  lcd.print(clock_hour);
  
  delay(500);
}


String fixZero(int i)
{
  String ret;
  if (i < 10) ret += "0";
  ret += i;
  return ret;
}


