#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <IRremote.h>
#include "ESP8266.h"
#include "DS1307.h"
#include <SPI.h>
#include <SD.h>


#define LIGA    LOW
#define DESLIGA HIGH

//#define R1_L1_Q1      22 //QUARTO 1 LUZ 1
//#define R2_L2_Q1      23 //QUARTO 1 LUZ 2
//#define R3_L3_Q1      24 //QUARTO 1 LUZ 3
//#define R4_L4_Q1      25 //QUARTO 1 LUZ 4
//
//#define R9_T1_Q1      26 //QUARTO 1 TOMADA 1
//#define RA_T2_Q1      27 //QUARTO 1 TOMADA 2
//#define RB_T3_Q1      28 //QUARTO 1 TOMADA 3
//#define RC_T4_Q1      29 //QUARTO 1 TOMADA 4

//#define R1_L1_Q2      30 //QUARTO 2 LUZ 1
//#define R2_L2_Q2      31 //QUARTO 2 LUZ 2
//#define R3_L3_Q2      32 //QUARTO 2 LUZ 3
//#define R4_L4_Q2      33 //QUARTO 2 LUZ 4
//
//#define R5_T1_Q2      34 //QUARTO 2 TOMADA 1
//#define R6_T2_Q2      35 //QUARTO 2 TOMADA 2
//#define R7_T3_Q2      36 //QUARTO 2 TOMADA 3
//#define R8_T4_Q2      37 //QUARTO 2 TOMADA 4
//
//
//#define R1_L1_Q3      38 //QUARTO 3 LUZ 1
//#define R2_L2_Q3      39 //QUARTO 3 LUZ 2
//#define R3_L3_Q3      40 //QUARTO 3 LUZ 3
//#define R4_L4_Q3      41 //QUARTO 3 LUZ 4
//
//#define R5_T1_Q3      42 //QUARTO 3 TOMADA 1
//#define R6_T2_Q3      43 //QUARTO 3 TOMADA 2
//#define R7_T3_Q3      44 //QUARTO 3 TOMADA 3
//#define R8_T4_Q3      45 //QUARTO 3 TOMADA 4
//
//
//#define R1_L1_Q4      46 //QUARTO 4 LUZ 1
//#define R2_L2_Q4      47 //QUARTO 4 LUZ 2
//#define R3_L3_Q4      48 //QUARTO 4 LUZ 3
//#define R4_L4_Q4      49 //QUARTO 4 LUZ 4
//
//#define R5_T1_Q4      50 //QUARTO 4 TOMADA 1
//#define R6_T2_Q4      51 //QUARTO 4 TOMADA 2
//#define R7_T3_Q4      52 //QUARTO 4 TOMADA 3
//#define R8_T4_Q4      53 //QUARTO 4 TOMADA 4

//#define S1_PIR_Q1  2 //Pino ligado ao sensor PIR (SENSOR 1_PIR_QUARTO 1 )
//#define S2_PIR_Q2  3 //Pino ligado ao sensor PIR (SENSOR 2_PIR_QUARTO 2 )
//#define S1_PIR_Q3  4 //Pino ligado ao sensor PIR (SENSOR 1_PIR_QUARTO 1 )
//#define S2_PIR_Q4  5 //Pino ligado ao sensor PIR (SENSOR 2_PIR_QUARTO 2 )

//#define BOZINA_Q1  6 //BOZINA


//------------------------DISPLAY--------------------------//
// Inicializa o display no endereco 0x27
LiquidCrystal_I2C lcd(0x27, 20, 4);
//------------------------DISPLAY--------------------------//

DS1307  rtc(A1, A2);

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
#define SSID        "Include <WIFI.CH>"
#define PASSWORD    "SystemAlberto2901922524@@"

//Cria objeto de conexão wifi com o módulo, usando a Serial1 do Mega.
ESP8266 wifi(Serial3);
//------------------------wifi--------------------------//



//--------variaveis globais todas os loop's podem velas-------------//

int    LED = 1; // 1 LIGADO // 2 DESLIGADO


//------------------------DISPLAY----------------------------------//
int linha = -1;
//------------------------DISPLAY----------------------------------//



//------------------------QUARTO 1----------------------------------//



//------------------------QUARTO 1----------------------------------//




//--------variaveis globais todas os loop's podem velas-------------//


//------------------------linha_lcd()----------------------------------//
int linha_lcd() {
  if (linha < 3)
  {
    linha = linha + 1;
    lcd.setCursor(0, linha);
    lcd.print("                    ");
  }
  else
  { linha = 0;
    lcd.setCursor(0, linha);
    //lcd.print("                    ");
    lcd.clear();
  }
  return linha;
}
//------------------------linha_lcd()----------------------------------//







class Alarme {
  private:
    
    int    _Pino = 6; // sirene
    bool   _Status = false;
//    String _Sensor_Ativ[10][2];//vetor



  public:
    Alarme();
    bool VerificSensor();
    void AtiDesatAlarme();
    void Vigilancia();
    void Bip();
    void LigSirene();
    void DesligSirene();
};

Alarme::Alarme()
{
  pinMode(_Pino, OUTPUT);   //Define pino sensor como entrada
  _Status = false; //ativa alarme por defull
}

void Alarme::AtiDesatAlarme()
{
  if (_Status == false) {
    lcd.setCursor(0, linha_lcd());
    lcd.print("Alarme Ativado");
    Serial.println("Alarme Ativado");
    _Status = true;
  }
  else {
    lcd.setCursor(0, linha_lcd());
    lcd.print("Alarme Desativado");
    Serial.println("Alarme Desativado");
    _Status = false;
    DesligSirene();
  }

}

void Alarme::LigSirene()
{Serial.println("Liga Sirene");
 digitalWrite(_Pino, LIGA);}

void Alarme::DesligSirene()
{Serial.println("Desliga Sirene");
 digitalWrite(_Pino, DESLIGA);}
   
   
   
void Alarme::Vigilancia()
{
  if (_Status == true) {
    lcd.setCursor(0, linha_lcd());
    lcd.print("INVASAO ALARME ATIVADO");
    Serial.println("INVASAO ALARME ATIVADO");
    LigSirene();
    
   }

}

void Alarme::Bip()
 {Serial.println("BIP");
  LigSirene();
  delay(10);
  DesligSirene();
  delay(20);}






Alarme *Alarme1;







class Clock {
  private:
    String    _Tempo;
    String    _Data;
    
    int       _Hora;
    int       _Minuto;
    int       _Segundo;
    
    int       _Dia;
    int       _Mes;
    int       _Ano;
    
    String    _Ndia;
    
    int    indic = 0;    //MELHORAR ALBERTO   PADRÃO
    String _Acao ;
    bool   valid_nv = true;    // MELHORAR ALBERTO
    String HORA_ACAO[10][4];   // MELHORAR ALBERTO
      
  public:
    Clock(int hora, int minuto, int segundo, int dia, int mes, int ano, String ndia);
    String CalcTemp(int par);
    String Hora();
    bool   VerifHora(String par);
    //void   VerifDataHora();
    void   MostraHora(String par, String par1);
    void   MostraData(String par, String par1);
    void   AjustTemp(int hora, int minuto, int segundo, int dia, int mes, int ano, String ndia);
    void   FuncTimer(String comando,String horaligar,String horadesligar, String dias, int par);
};


Clock::Clock(int hora, int minuto, int segundo, int dia, int mes, int ano, String ndia)
{

  // Init a Time-data structure
  Time  t;

  // Set the clock to run-mode
  rtc.halt(false);
  //MONDAY   - segunda
  //TUESDAY   - terça
  //WEDNESDAY - quarta
  //THURSDAY  - quinta
  //FRIDAY    - sexta
  //SATURDAY  - sabado
  //SUNDAY    - domingo
  // The following lines can be commented out to use the values already stored in the DS1307
//      if (ndia == "SEGUNDA" )
//          {_Ndia = MONDAY;}
//      if (ndia == "TERCA")
//          {_Ndia = TUESDAY;}
//      if (ndia == "QUARTA")
//          {_Ndia = WEDNESDAY;}
//      if (ndia == "QUINTA")
//          {_Ndia = THURSDAY;}
//      if (ndia == "SEXTA")
//          {_Ndia = FRIDAY;}
//      if (ndia == "SABADO")
//          {_Ndia = SATURDAY;}
//      if (ndia == "DOMINGO")
//          {_Ndia = SUNDAY;}
          
      
      _Hora    = hora;
      _Minuto  = minuto;
      _Segundo = segundo;
      _Dia     = dia;
      _Mes     = mes; 
      _Ano     = ano;
  
// rtc.setDOW(_Ndia);        // Set Day-of-Week to SUNDAY
//  rtc.setTime(_Hora,_Minuto,_Segundo);   // Set the time to 12:00:00 (24hr format)
//  rtc.setDate(_Dia,_Mes,_Ano); // Set the date to October 3th, 2010
}

void Clock::AjustTemp(int hora, int minuto, int segundo, int dia, int mes, int ano, String ndia)
{
  
      _Hora    = hora;
      _Minuto  = minuto;
      _Segundo = segundo;
      _Dia     = dia;
      _Mes     = mes; 
      _Ano     = ano;

  //rtc.setDOW(_Ndia);        // Set Day-of-Week to SUNDAY
  rtc.setTime(_Hora,_Minuto,_Segundo);   // Set the time to 12:00:00 (24hr format)
  rtc.setDate(_Dia,_Mes,_Ano); // Set the date to October 3th, 2010
}



String Clock::CalcTemp(int par) {

  _Tempo = rtc.getTimeStr();
  //time = "00:10:00";

  //IMPRIME HORARIO DA AÇÃO
  Serial.println(_Tempo);

  //DESMENBRA A STRING EM HORAS, MINUTOS E SEGUNDOS
  String hora    = _Tempo.substring(0, 2);
  String minuto  = _Tempo.substring(3, 5);
  String segundo = _Tempo.substring(6, 8);

  //TRANSFORMA STRING EM INT
  int HORA = atoi( hora.c_str() );
  int MINUTO = atoi( minuto.c_str() );


  MINUTO = MINUTO + par;


  if (MINUTO > 59)

  { if (HORA == 23)
    {
      HORA = 0;
    }
    else
    {
      HORA++ ;
    }
    MINUTO = MINUTO - 60;
  }

  //Serial.println(HORA);
  //Serial.println(MINUTO);
  //TRANSFORMA RESULTADO EM STRING NOVAMENTE
  hora = String(HORA);
  if (hora.length() == 1)
  {
    hora = ("0" + hora);
  }
  minuto = String(MINUTO);
  if (minuto.length() == 1)
  {
    minuto = ("0" + minuto);
  }
  Serial.println(hora + ":" + minuto + ":" + segundo);
  return (hora + ":" + minuto + ":" + segundo);
}


void Clock::MostraHora(String par, String par1) {

  if (par == "DIA")
  {}
  if (par == "MES")
  {}
  if (par == "ANO")
  {}

  if (par == "FULL")
  { if (par1 == "LCD")
      {lcd.setCursor(0, linha_lcd());
       lcd.print("Hora: ");
       lcd.print(rtc.getTimeStr());
      }
      
    if (par1 == "SERIAL")
      {Serial.print("Hora : ");
       Serial.println(rtc.getTimeStr());
      }
  }

}

void Clock::MostraData(String par, String par1) {
  if (par == "DIA")
  {}
  if (par == "MES")
  {}
  if (par == "ANO")
  {}

  if (par == "FULL")
  { if (par1 == "LCD")
     {lcd.setCursor(0, linha_lcd());
      lcd.print("Data: ");
      lcd.print(rtc.getDateStr(FORMAT_SHORT));
      //lcd.setCursor(0, linha_lcd());
      String dia = rtc.getDOWStr(FORMAT_SHORT);
      
         if (dia == "Monday" )
           {lcd.println("-SEG");}
         if (dia == "Tuesday")
           {lcd.println("-TER");}
         if (dia == "Wednesday")
           {lcd.println("-QUA");}
         if (dia == "Thursday")
           {lcd.println("-QUI");}
         if (dia == "Friday")
           {lcd.println("-SEX");}
         if (dia == "Saturday")
           {lcd.println("-SAB");}
         if (dia == "Sunday")
           {lcd.println("-DOM");}
     }
    
    if (par1 == "SERIAL")
       {Serial.print(" ");
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
      }
  }
}


bool Clock::VerifHora(String par)
{
  _Tempo = rtc.getTimeStr();
  if ( (par.substring(0, 5) == _Tempo.substring(0, 5))) // transformar validação em numerico
  {
    return (true);
  }
  else
  {
    return (false);
  }
}

String Clock::Hora()
{ _Tempo = rtc.getTimeStr();
  return (_Tempo);
}




void Clock::FuncTimer(String comando,String horaligar,String horadesligar, String dias, int par)
{  _Acao = comando;
   if(par == 1)
     {for(int i = 0;i<=indic;i++)
           {if((_Acao.substring(0, 7) + "L" + _Acao.substring(8, 20) + "@") == HORA_ACAO[i][1])
               {valid_nv = false;
                Serial.println("PROGRAMACAO JA ATIVA");
                HORA_ACAO[indic][1] = "";
                HORA_ACAO[indic][2] = "";
                HORA_ACAO[indic][3] = "";
                HORA_ACAO[indic][4] = "";
                Serial.println("ja tem PROGRAMACAO vou retirar"+(_Acao.substring(0, 7) + "L" + _Acao.substring(8, 20) + "@"));
                lcd.setCursor(0, linha_lcd());
                lcd.print("TIMER DESATIV: " + (_Acao.substring(0, 7) + "L" + _Acao.substring(8, 20) + "@"));
               }
      
           }//for
      
         if (valid_nv == true)
           {indic++;  //MELHORAR ALBERTO
      
           //Alarme1->Bip();
           Serial.println("NOVA PROGRAMACAO");
           Serial.println(indic);
//           Serial.println(_Acao);
           Serial.println(_Acao.substring(0, 7) + "L" + _Acao.substring(8, 20) + "@");
           
           Serial.print("LIGAR AS: ");
           Serial.println(horaligar.substring(1,3)+":"+horaligar.substring(3,5)+":00");
      
           Serial.print("DESLIGAR AS: ");
           Serial.println (horadesligar.substring(1,3)+":"+horadesligar.substring(3,5)+":00");
      
           Serial.print("SEQUENCIA DE DIAS: ");
           Serial.println (dias);
           
//#Q1*L1*L*D0000*L0000@  luz ou tomada TIPO 01
//  V_INI1       = comando.substring(0, 1);   #
//  COMODO1      = comando.substring(1, 3);   Q1
//  V_11         = comando.substring(3, 4);   *
//  COMPONENTE1  = comando.substring(4, 6);   L1
//  V_21         = comando.substring(6, 7);   *
//  ACAO1        = comando.substring(7, 8);   L
//  V_31         = comando.substring(8, 9);   *
//  AUTODESLIGA1 = comando.substring(9, 14);  D0000
//  V_41         = comando.substring(14, 15); *
//  AUTOLIGA1    = comando.substring(15, 20); L0000
//  V_FIN1       = comando.substring(20, 21); @
//  DIAS         = comando.substring(21, 28);
//  V_FIN21      = comando.substring(28, 29);

      
           HORA_ACAO[indic][1] = (_Acao.substring(0, 7) + "L" + _Acao.substring(8, 20) + "@");
           HORA_ACAO[indic][2] = (horaligar.substring(1,3)+":"+horaligar.substring(3,5)+":00");
           HORA_ACAO[indic][3] = (horadesligar.substring(1,3)+":"+horadesligar.substring(3,5)+":00");
           HORA_ACAO[indic][4] = (dias);
      
//           Serial.println (HORA_ACAO[indic][4].substring(0,1));
//           Serial.println (HORA_ACAO[indic][4].substring(1,2));
//           Serial.println (HORA_ACAO[indic][4].substring(2,3));
//           Serial.println (HORA_ACAO[indic][4].substring(3,4));
//           Serial.println (HORA_ACAO[indic][4].substring(4,5));
//           Serial.println (HORA_ACAO[indic][4].substring(5,6));
//           Serial.println (HORA_ACAO[indic][4].substring(6,7));
//           Serial.println (HORA_ACAO[indic][1]);
           }

   }//if par ==1 incluir


   if(par == 2)
      {_Ndia = rtc.getDOWStr(FORMAT_SHORT);
//       Serial.println(_Ndia);
       
                 for(int i = 0;i<=indic;i++)
                     {
//                      Serial.println("hora 1  " + Hora());
//                      Serial.println("hora 2  " + HORA_ACAO[i][2]);
//                      Serial.println(i);
                      if(Hora() == HORA_ACAO[i][2])
                       
                       {if (_Ndia == "Monday"    && HORA_ACAO[i][4].substring(0,1) == "1" )
                            {Serial.println("SEG");
                             Serial.println(" HORA PROGRAMADA PARA LIGAR");
                             Serial.println(HORA_ACAO[i][1]);  
                             FUNC_COMANDO(HORA_ACAO[i][1],2);
                             }
                         if (_Ndia == "Tuesday"   && HORA_ACAO[i][4].substring(1,2) == "1")  
                            {Serial.println("TER");
                             Serial.println(" HORA PROGRAMADA PARA LIGAR");
                             Serial.println(HORA_ACAO[i][1]);  
                             FUNC_COMANDO(HORA_ACAO[i][1],2);
                            } 
                         if (_Ndia == "Wednesday" && HORA_ACAO[i][4].substring(2,3) == "1")  
                            {Serial.println("QUA");
                             Serial.println(" HORA PROGRAMADA PARA LIGAR");
                             Serial.println(HORA_ACAO[i][1]);  
                             FUNC_COMANDO(HORA_ACAO[i][1],2);
                            }  
                         if (_Ndia == "Thursday"  && HORA_ACAO[i][4].substring(3,4) == "1")   
                            {Serial.println("QUI");
                             Serial.println(" HORA PROGRAMADA PARA LIGAR");
                             Serial.println(HORA_ACAO[i][1]);  
                             FUNC_COMANDO(HORA_ACAO[i][1],2);
                            }   
                         if (_Ndia == "Friday"    && HORA_ACAO[i][4].substring(4,5) == "1")   
                            {Serial.println("SEX");
                             Serial.println(" HORA PROGRAMADA PARA LIGAR");
                             Serial.println(HORA_ACAO[i][1]);  
                             FUNC_COMANDO(HORA_ACAO[i][1],2);
                            }   
                         if (_Ndia == "Saturday"  && HORA_ACAO[i][4].substring(5,6) == "1")   
                            {Serial.println("SAB");
                             Serial.println(" HORA PROGRAMADA PARA LIGAR");
                             Serial.println(HORA_ACAO[i][1]);  
                             FUNC_COMANDO(HORA_ACAO[i][1],2);
                            }   
                         if (_Ndia == "Sunday"    && HORA_ACAO[i][4].substring(6,7) == "1")  
                            {Serial.println("DOM");
                             Serial.println(" HORA PROGRAMADA PARA LIGAR");
                             Serial.println(HORA_ACAO[i][1]);  
                             FUNC_COMANDO(HORA_ACAO[i][1],2);
                            }
               
                       }
                       
                       if(Hora() == HORA_ACAO[i][3])
                         {if (_Ndia == "Monday"    && HORA_ACAO[i][4].substring(0,1) == "1" )
                              {Serial.println("SEG");
                               Serial.println(" HORA PROGRAMADA PARA DESLIGAR");
                               Serial.println(HORA_ACAO[i][1]);  
                               FUNC_COMANDO(HORA_ACAO[i][1],3);
                              }
                           if (_Ndia == "Tuesday"   && HORA_ACAO[i][4].substring(1,2) == "1")  
                              {Serial.println("TER");
                               Serial.println(" HORA PROGRAMADA PARA DESLIGAR");
                               Serial.println(HORA_ACAO[i][1]);  
                               FUNC_COMANDO(HORA_ACAO[i][1],3);
                              } 
                           if (_Ndia == "Wednesday" && HORA_ACAO[i][4].substring(2,3) == "1")  
                              {Serial.println("QUA");
                               Serial.println(" HORA PROGRAMADA PARA DESLIGAR");
                               Serial.println(HORA_ACAO[i][1]);  
                               FUNC_COMANDO(HORA_ACAO[i][1],3);
                              }  
                           if (_Ndia == "Thursday"  && HORA_ACAO[i][4].substring(3,4) == "1")   
                              {Serial.println("QUI");
                               Serial.println(" HORA PROGRAMADA PARA DESLIGAR");
                               Serial.println(HORA_ACAO[i][1]);  
                               FUNC_COMANDO(HORA_ACAO[i][1],3);
                              }   
                           if (_Ndia == "Friday"    && HORA_ACAO[i][4].substring(4,5) == "1")   
                              {Serial.println("SEX");
                               Serial.println(" HORA PROGRAMADA PARA DESLIGAR");
                               Serial.println(HORA_ACAO[i][1]);  
                               FUNC_COMANDO(HORA_ACAO[i][1],3);
                              }   
                           if (_Ndia == "Saturday"  && HORA_ACAO[i][4].substring(5,6) == "1")   
                              {Serial.println("SAB");
                               Serial.println(" HORA PROGRAMADA PARA DESLIGAR");
                               Serial.println(HORA_ACAO[i][1]);  
                               FUNC_COMANDO(HORA_ACAO[i][1],3);
                              }   
                           if (_Ndia == "Sunday"    && HORA_ACAO[i][4].substring(6,7) == "1")  
                              {Serial.println("DOM");
                               Serial.println(" HORA PROGRAMADA PARA DESLIGAR");
                               Serial.println(HORA_ACAO[i][1]);  
                               FUNC_COMANDO(HORA_ACAO[i][1],3);
                              }
                        
                        }
                       
                  }//for

     }//if par == 2 acao


} // :FuncTimer



Clock *Clock1;












class _SD {
  private:
    
    int    _Pino = 53; 
    String _Ini_Log = "Ini_Log.txt";  // Tamanho maximo do nome 8 
    String _Logs    = "Logs.txt";  // Tamanho maximo do nome 8 
    String _TM_PORG = "TM_PORG.txt";  // Tamanho maximo do nome 8 
    File   myFile;  
   String _Texto;
  
  public:
        _SD();
   void GravSD(int tplog,String texto);

};

_SD::_SD()
{
  /*
 ** MOSI - pin 51
 ** MISO - pin 50
 ** CLK  - pin 52
 ** CS   - pin 53
*/
 
//criar um objeto File para manipular um arquivo

  while (!Serial);
 
  Serial.print("Inicializa SD card: ");
 
  if (!SD.begin(_Pino)) {
    Serial.println("Nao inicializado. ERRO");
    //return;
  }
  Serial.println("SD OK!");
 
  /* A biblioteca SD tem um metodo para abrir arquivos e esse arquivo aberto
  sera armazenado no objeto myFile, descrito ao inicio desse codigo. Somente 
  um arquivo pode ser aberto por vez, portanto nao se esqueca de fecha-lo
  antes de abrir um novo ou voce tera problemas.
  */
 
  myFile = SD.open(_Ini_Log, FILE_WRITE);
 
//'  Se o arquivo foi aberto com sucesso, escreve nele
  if (myFile) {
    Serial.print("Escrevendo em:" + _Ini_Log);
    myFile.println("Smart HOME ");
    myFile.println("Versao v2.0");
    myFile.println("Alberto Goncalves");
 
    // Terminou de escrever, fecha-se o arquivo:
    myFile.close();
 
    Serial.println("Escrevinhado.");
 
  }
  else {
    // Se nao deu certo, comeca a dar merda desse ponto
    Serial.println("Nao foi possivel abrir o arquivo");
  }
 
  // Agora vamos abri-lo para leitura
  myFile = SD.open(_Ini_Log);
  if (myFile) {
    Serial.println(_Ini_Log + ":");
 
    // Le todo o arquivo...
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    //Finalizado, fecha-se o arquivo
    myFile.close();
  }
  else {
    // Se deu erro acima, aqui tambem dara.
    Serial.println("Nao pude abrir o arquivo.");
  }
 
}






void _SD::GravSD(int tplog,String texto)//1 = _Ini_Log  //2 = _Logs  //3 =_TM_PORG 
{
  _Texto = texto;
////criar um objeto File para manipular um arquivo
//  while (!Serial);
// 
//  Serial.print("Inicializa SD card: ");
// 
  if (!SD.begin(_Pino)) {
    Serial.println("Nao inicializado. ERRO");
    }
  Serial.println("SD OK!");
 
 if (tplog == 1) 
    { myFile = SD.open(_Ini_Log, FILE_WRITE);}
 if (tplog == 2)
    { myFile = SD.open(_Logs, FILE_WRITE);}
 if (tplog == 3)
    { myFile = SD.open(_TM_PORG, FILE_WRITE);}
     
//'  Se o arquivo foi aberto com sucesso, escreve nele
  if (myFile) {
    Serial.print("Escrevendo");
    myFile.print  (_Texto);
    myFile.println(" /" + Clock1->Hora() );
    
    // Terminou de escrever, fecha-se o arquivo:
    myFile.close();
    Serial.println("txt.close");
 
  }
  else {
    // Se nao deu certo, comeca a dar merda desse ponto
    Serial.println("Nao foi possivel abrir o arquivo");
  }
 
//  // Agora vamos abri-lo para leitura
//  myFile = SD.open(_Ini_Log);
//  if (myFile) {
//    Serial.println(_Ini_Log + ":");
// 
//    // Le todo o arquivo...
//    while (myFile.available()) {
//      Serial.write(myFile.read());
//    }
//    //Finalizado, fecha-se o arquivo
//    myFile.close();
//  }
//  else {
//    // Se deu erro acima, aqui tambem dara.
//    Serial.println("Nao pude abrir o arquivo.");
//  }
 
}



_SD *SD1;
















class Lampada {
  private:
    int _pino;
    String _CodRef;
    String _NomeChave;
    
  public:
    Lampada(int pin, String codref,String nomechave, bool inicia);
    void Ligar();
    void Desligar();
    void Chave();
    bool Estado();
};

Lampada::Lampada(int pin, String codref,String nomechave, bool inicia)
{
  _pino   = pin;
  _CodRef = codref;
  _NomeChave = nomechave;
  pinMode(_pino,   OUTPUT); //Define o pino como saida

  // inicia sistema ligada ou desligada
  if (inicia == true)
  {
    digitalWrite(_pino, LIGA);
  }
  else
  {
    digitalWrite(_pino, DESLIGA);
  }

}

void Lampada::Ligar()
{
  if (!Estado())
   {Serial.println("LIG " + _CodRef);
    Serial.println("LIG " + _NomeChave);
    lcd.setCursor(0,linha_lcd());
    lcd.print("LIG " + _NomeChave);
    //SD1->GravSD(2,"LIG " + _NomeChave + _CodRef);//1 = _Ini_Log  //2 = _Logs  //3 =_TM_PORG 
    digitalWrite(_pino, LIGA);
    //     C_L4_Q1 = false;
   }
}


void Lampada::Desligar()
{
    if (Estado())
   {Serial.println("DES " + _CodRef);
    Serial.println("DES " + _NomeChave);
    lcd.setCursor(0,linha_lcd());
    lcd.print("DES " + _NomeChave);
    //SD1->GravSD(2,"DES " + _NomeChave + _CodRef);//1 = _Ini_Log  //2 = _Logs  //3 =_TM_PORG 
    digitalWrite(_pino, DESLIGA);
    //C_L4_Q1 = false;
    }
}


void Lampada::Chave()
{
  if (digitalRead(_pino) == DESLIGA)
   {Serial.println("LIG C " + _CodRef);
    Serial.println("LIG C " + _NomeChave);
    lcd.setCursor(0,linha_lcd());
    lcd.print("LIG C " + _NomeChave);
    //SD1->GravSD(2,"LIG C " + _NomeChave + _CodRef);//1 = _Ini_Log  //2 = _Logs  //3 =_TM_PORG 
    digitalWrite(_pino, LIGA);
  }

  else
   {Serial.println("DES C " + _CodRef);
    Serial.println("DES C " + _NomeChave);
    lcd.setCursor(0,linha_lcd());
    lcd.print("DES C " + _NomeChave);
    //SD1->GravSD(2,"DES C " + _NomeChave + _CodRef);//1 = _Ini_Log  //2 = _Logs  //3 =_TM_PORG 
    digitalWrite(_pino, DESLIGA);
    //C_L4_Q1 = false;
   }
}

bool Lampada::Estado()
{
  if (digitalRead(_pino) == LIGA)
  {
    return (true);
  }
  else
  {
    return (false);
  }
}


Lampada *L1_Q1; //ponteiro para Lampada
Lampada *L2_Q1;
Lampada *L3_Q1;
Lampada *L4_Q1;





















class Tomada {
  private:
    int _pino;
    String _CodRef;
    String _NomeChave;
    
  public:
    Tomada(int pin, String codref,String nomechave, bool inicia);
    void Ligar();
    void Desligar();
    void Chave();
    bool Estado();
};

Tomada::Tomada(int pin, String codref,String nomechave, bool inicia)
{
  _pino   = pin;
  _CodRef = codref;
  _NomeChave = nomechave;
  pinMode(_pino,   OUTPUT); //Define o pino como saida

  // inicia sistema ligada ou desligada
  if (inicia == true)
  {
    digitalWrite(_pino, LIGA);
  }
  else
  {
    digitalWrite(_pino, DESLIGA);
  }

}

void Tomada::Ligar()
{
  if (!Estado())
   {Serial.println("LIG " + _CodRef);
    Serial.println("LIG " + _NomeChave);
    lcd.setCursor(0,linha_lcd());
    lcd.print("LIG " + _NomeChave);
    //SD1->GravSD(2,"LIG " + _NomeChave + _CodRef);//1 = _Ini_Log  //2 = _Logs  //3 =_TM_PORG 
    digitalWrite(_pino, LIGA);
    //     C_L4_Q1 = false;
   }
}


void Tomada::Desligar()
{
    if (Estado())
   {Serial.println("DES " + _CodRef);
    Serial.println("DES " + _NomeChave);
    lcd.setCursor(0,linha_lcd());
    lcd.print("DES " + _NomeChave);
    //SD1->GravSD(2,"DES " + _NomeChave + _CodRef);//1 = _Ini_Log  //2 = _Logs  //3 =_TM_PORG 
    digitalWrite(_pino, DESLIGA);
    //C_L4_Q1 = false;
    }
}


void Tomada::Chave()
{
  if (digitalRead(_pino) == DESLIGA)
   {Serial.println("LIG C " + _CodRef);
    Serial.println("LIG C " + _NomeChave);
    lcd.setCursor(0,linha_lcd());
    lcd.print("LIG C " + _NomeChave);
    //SD1->GravSD(2,"LIG C " + _NomeChave + _CodRef);//1 = _Ini_Log  //2 = _Logs  //3 =_TM_PORG 
    digitalWrite(_pino, LIGA);
    //     C_L4_Q1 = false;
   }

  else
   {Serial.println("DES C " + _CodRef);
    Serial.println("DES C " + _NomeChave);
    lcd.setCursor(0,linha_lcd());
    lcd.print("DES C " + _NomeChave);
    //SD1->GravSD(2,"DES C " + _NomeChave + _CodRef);//1 = _Ini_Log  //2 = _Logs  //3 =_TM_PORG 
    digitalWrite(_pino, DESLIGA);
    //C_L4_Q1 = false;
   }
}

bool Tomada::Estado()
{
  if (digitalRead(_pino) == LIGA)
  {
    return (true);
  }
  else
  {
    return (false);
  }
}


Tomada  *T1_Q1; //ponteiro para Tomada
Tomada  *T2_Q1;
Tomada  *T3_Q1;
Tomada  *T4_Q1;
















class Sensor {
  private:
    int    _Pino;
    String _CodRef;
    String _Local;
    int    _Tempo = 1;
    bool   HORA_vild = true;
    String _Sensor_Ativ[10][2];//vetor
    int    _Indice = 0;
    String _Hora_PIR;


  public:
    Sensor(int pin, String codref, String local, int tempo);
    bool VerificSensor();
    void ListAcaoSensor(int par, String acao);
    void AlterTempsensor(int tempo);
};

Sensor::Sensor(int pin, String codref, String local, int tempo)
{
  _Pino   = pin;
  _CodRef = codref;
  _Local  = local;
  _Tempo  = tempo;
  

  pinMode(_Pino, INPUT);   //Define pino sensor como entrada
}

void Sensor::AlterTempsensor(int tempo)
{
  _Tempo  = tempo;
  
        Serial.println("SENSOR " + _CodRef);
        lcd.setCursor(0, linha_lcd());
        lcd.print("SENSOR " + _Local);
        
        Serial.println("SENSOR "+ _Local +_CodRef + _Tempo + " MINUTOS");
        lcd.setCursor(0, linha_lcd());
        lcd.print("SENSOR "+ _Local +" "+ _Tempo + " MIN");
  
}

void Sensor::ListAcaoSensor(int par, String acao)
{
  bool vldNv = false;

  if (par == 1) //incluir novo sensor
  { Serial.println("ListAcaoSensor");

    for (int i = 0; i <= _Indice; i++)
    { if ( _Sensor_Ativ[i][1] == acao)
      { vldNv = true;
        _Sensor_Ativ[i][1] = "";
        Serial.println("ja tem SENSOR vou retirar");
        lcd.setCursor(0, linha_lcd());
        lcd.print("AUTO DESATIV: " + _Sensor_Ativ[i][1]);
      }
    }

    if (vldNv == false)
    { _Indice++; //melhorar condição pra pegar vazio    MELHORAR ALBERTO

      Serial.println("NOVO SENSOR");
      Serial.println(_Indice);
      Serial.println(acao);
      _Sensor_Ativ[_Indice][1] = acao;
      Serial.println(_Sensor_Ativ[_Indice][1]);
      lcd.setCursor(0, linha_lcd());
      lcd.print("AUTO ATIV: " + _Sensor_Ativ[_Indice][1]);
      
    }

  }

  if (par == 2) //verificar sensores
  { Serial.println("verificar lista SENSOR ligar");
    for (int i = 0; i <= _Indice; i++)
    {
      Serial.println(_Sensor_Ativ[i][1]);
      //Serial.println(i);


      if ((_Sensor_Ativ[i][1]) == "L1_Q1") // RELE_1 LIZ_1
      {
        L1_Q1->Ligar();
      }

      if ((_Sensor_Ativ[i][1]) == "L2_Q1")
      {
        L2_Q1->Ligar();
      }

      if ((_Sensor_Ativ[i][1]) == "L3_Q1")
      {
        L3_Q1->Ligar();
      }

      if ((_Sensor_Ativ[i][1]) == "L4_Q1")
      {
        L4_Q1->Ligar();
      }


      if ((_Sensor_Ativ[i][1]) == "T1_Q1") // RELE_1 LIZ_1
      {
        T1_Q1->Ligar();
      }

      if ((_Sensor_Ativ[i][1]) == "T2_Q1")
      {
        T2_Q1->Ligar();
      }

      if ((_Sensor_Ativ[i][1]) == "T3_Q1")
      {
        T3_Q1->Ligar();
      }

      if ((_Sensor_Ativ[i][1]) == "T4_Q1")
      {
        T4_Q1->Ligar();
      }
    }

  }

  if (par == 3) //verificar sensores
  { Serial.println("verificar lista SENSOR Desligar");
    for (int i = 0; i <= _Indice; i++)
    {
      Serial.println(_Sensor_Ativ[_Indice][i]);

      if ((_Sensor_Ativ[i][1]) == "L1_Q1") // RELE_1 LIZ_1
      {
        L1_Q1->Desligar();
      }

      if ((_Sensor_Ativ[i][1]) == "L2_Q1")
      {
        L2_Q1->Desligar();
      }

      if ((_Sensor_Ativ[i][1]) == "L3_Q1")
      {
        L3_Q1->Desligar();
      }

      if ((_Sensor_Ativ[i][1]) == "L4_Q1")
      {
        L4_Q1->Desligar();
      }

      if ((_Sensor_Ativ[i][1]) == "T1_Q1") // RELE_1 LIZ_1
      {
        T1_Q1->Desligar();
      }

      if ((_Sensor_Ativ[i][1]) == "T2_Q1")
      {
        T2_Q1->Desligar();
      }

      if ((_Sensor_Ativ[i][1]) == "T3_Q1")
      {
        T3_Q1->Desligar();
      }

      if ((_Sensor_Ativ[i][1]) == "T4_Q1")
      {
        T4_Q1->Desligar();
      }

    }

  }

}


bool Sensor::VerificSensor()
{

  if (digitalRead(_Pino) == HIGH &&  HORA_vild == true ) //Caso seja detectado um movimento
  { //Serial.println("COM MOVIMENTO");
    //lcd.setCursor(0, linha_lcd());
    //lcd.print("MOVIMENTO");

    _Hora_PIR = Clock1->CalcTemp(_Tempo);  //CALCULA TEMPO (1)= QUARTO 1
    HORA_vild = false;

    ListAcaoSensor(2, "");
    Alarme1->Vigilancia();
    //T3_Q1->Ligar();

    Serial.println("MOV: " + _Local +" : "+ _CodRef);
    lcd.setCursor(0, linha_lcd());
    lcd.print("MOV: " + _Local);
    

  }//função auto ligar desligar


  if ( Clock1->VerifHora(_Hora_PIR) && (HORA_vild == false)) //verificar sensor para saber se deve delisgar
  { 
    Serial.println("verificar sensor: " + _Local+" : "+ _CodRef);
    //lcd.setCursor(0, linha_lcd());
    //lcd.print("DELIG" + _Local);
    
    //lcd.print(Clock1->Hora());
    Serial.println(Clock1->Hora());

    if ((digitalRead(_Pino) == HIGH))
    { //Serial.println("ainda COM MOVIMENTO entAo nAo deslige e calcule tempo de novo");
      //lcd.setCursor(0, linha_lcd());
      //lcd.print("MOVIMENTO");
      _Hora_PIR = Clock1->CalcTemp(_Tempo);  //CALCULA TEMPO

      ListAcaoSensor(2, "");
      //T3_Q1->Ligar();

      Serial.println("AINDA COM MOV: " + _Local+" : "+ _CodRef);
      lcd.setCursor(0, linha_lcd());
      lcd.print("MOV+:" + _Local);

    }
    else
    { HORA_vild = true;
      Serial.println("sem movimento desligue");

      ListAcaoSensor(3, "");
      //T3_Q1->Desligar();

      Serial.println("SEM MOV: " + _Local+" : "+ _CodRef);
      lcd.setCursor(0, linha_lcd());
      lcd.print("DELIG:" + _Local);
    } //else desligar

  }

}

Sensor *S1_Q1;




















void setup()
{
  //------------------------DISPLAY--------------------------//

  // Inicializa o display no endereco 0x27
  lcd.init();
  //------------------------DISPLAY--------------------------//

  //------------------------SERIAL--------------------------//
  Serial.begin (115200); //Inicializa a serial
  Serial2.begin(115200); //Inicializa a serial
  Serial3.begin(115200); //Inicializa a serial
  //------------------------SERIAL--------------------------//

  //------------------------relogio--------------------------//
  //int hora, int minuto, int segundo, int dia, int mes, int ano, int ndia
  Clock1 = new Clock(23, 40, 00, 1, 11, 2017, "QUARTA");

  //------------------------relogio--------------------------//

  //-----------------Declarando Objetos--------------------------//

  L1_Q1 = new Lampada(22, "L1_Q1","SUITE 01", false); //pino 22 , CodRef, Inicia
  L2_Q1 = new Lampada(23, "L2_Q1","SUITE 02", false);
  L3_Q1 = new Lampada(24, "L3_Q1","SUITE 03", true);
  L4_Q1 = new Lampada(25, "L4_Q1","SUITE 04", false);

  T1_Q1 = new Tomada(26, "T1_Q1","TV SUITE", false); //pino 22 , CodRef, Inicia
  T2_Q1 = new Tomada(27, "T2_Q1","TOMADA 02", false);
  T3_Q1 = new Tomada(28, "T3_Q1","T CAMA", false);
  T4_Q1 = new Tomada(29, "T4_Q1","VENTILADOR", true );
  
  Alarme1 = new Alarme();

  S1_Q1 = new Sensor( 2, "S1_Q1", "SUITE ALBERTO", 1);
  //-----------------Declarando Objetos--------------------------//
  
    //------------------------wifi--------------------------//
  pinMode(CH_PD, OUTPUT);
  pinMode(RST, OUTPUT);
  pinMode(GPIO0, OUTPUT);

  digitalWrite(CH_PD, HIGH); //setado em ALTO - operacao normal
  digitalWrite(RST, HIGH); //setado em ALTO - operhttp://www.embarcados.com.br/arduino-mega-2560/acao normal
  digitalWrite(GPIO0, HIGH); //setado em ALTO - operacao normal
  reset_wifi();
  //------------------------wifi--------------------------//

_SD();

} //void setup()






//------------------------LCD()----------------------------------//
void LUZ_LED() {

  if (LED == 1) {
    lcd.noBacklight();
    Serial.println("Desliga Led LCD");
    LED = 2;
  }
  else {
    lcd.backlight();
    Serial.println("Liga Led LCD");
    LED = 1;
  }
}
//------------------------LCD()----------------------------------//




//------------------------FUNC_COMANDO()----------------------------------//


void FUNC_COMANDO(String comando, int AGENTE) {

  //int  Vld_P      = 1; // VALIDAÇÃO PARA PERFIL
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
  String V_INI1, COMODO1, V_11, COMPONENTE1, V_21, ACAO1, V_31, AUTODESLIGA1, V_41, AUTOLIGA1, V_FIN1, DIAS, V_FIN21 ;

  V_INI1       = comando.substring(0, 1);
  COMODO1      = comando.substring(1, 3);
  V_11         = comando.substring(3, 4);
  COMPONENTE1  = comando.substring(4, 6);
  V_21         = comando.substring(6, 7);
  ACAO1        = comando.substring(7, 8);
  V_31         = comando.substring(8, 9);
  AUTODESLIGA1 = comando.substring(9, 14);
  V_41         = comando.substring(14, 15);
  AUTOLIGA1    = comando.substring(15, 20);
  V_FIN1       = comando.substring(20, 21);
  DIAS         = comando.substring(21, 28);
  V_FIN21      = comando.substring(28, 29);

/*  
  Serial.println(comando);
  Serial.println(V_INI1);
  Serial.println(COMODO1);
  Serial.println(V_11);
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

  V_INI2 = comando.substring(0, 1);
  COMODO2 = comando.substring(1, 3);
  V_12 = comando.substring(3, 4);
  COMPONENTE2 =  comando.substring(4, 11);
  V_22 = comando.substring(11, 12);
  ACAO2 =  comando.substring(12, 18);
  V_32 = comando.substring(18, 19);
  AUTODESLIGA2 =  comando.substring(19, 24);
  V_42 = comando.substring(24, 25);
  AUTOLIGA2 =  comando.substring(25, 30);
  V_FIN2 = comando.substring(30, 31);

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




  if ( (V_INI1 + COMODO1) == "#HR") //VALIDAÇÃO DIGITOS VERIFICADORES DO PROTOCOLO
    {//#HR*10:1001:12:2017@ EXEMPLO
      //  rtc.setDOW(MONDAY);      //Define o dia da semana
      //Serial.println("HORA: " + comando.substring(4, 6)  + ":" + comando.substring(7, 9) );
      //Serial.println("DATA: " + comando.substring(10, 12)+ ":" + comando.substring(12, 14) + ":" + comando.substring(14, 18));
     Clock1->AjustTemp(atoi(comando.substring(4 , 6 ).c_str()),atoi(comando.substring(7 , 9 ).c_str()),00,atoi(comando.substring(10, 12).c_str()), atoi(comando.substring(12, 14).c_str()), atoi(comando.substring(14, 18).c_str()),"SEGUNDA");
    }// FIM





  if ( (V_INI1 + V_11 + V_21 + V_31 + V_41 + V_FIN1) == "#****@") //VALIDAÇÃO DIGITOS VERIFICADORES DO PROTOCOLO
      {//Serial.println("valido");
       if (COMODO1 ==  "Q1") // SE O COMODO É IGUAL AO Q1=QUARTO1 ENTRA NO BLOCO DE IFs DESSE QUARTO
         {//Serial.println("Q1");
          if (COMPONENTE1.substring(0, 1) == "L") // SE O COMPONENTE É IGUAL AO L = LUZ ENTRA NO BLOCO DE IFs DE LUZES
            //Serial.println("LUZ");
    
    
            if ( ACAO1 == "L") //ATIVA OU NAO FUNÇÃO AUTO DE LUZES
            {
              if ( ((COMPONENTE1)  == "L1")) // RELE_1 LIZ_1
                {if (AGENTE == 1) //chave
                     {L1_Q1->Chave();}
                 if (AGENTE == 2) //chave
                     {L1_Q1->Ligar();}
                 if (AGENTE == 3) //chave
                     {L1_Q1->Desligar();}
                }
    
              if (  ((COMPONENTE1) == "L2") )
              {if (AGENTE == 1) //chave
                     {L2_Q1->Chave();}
               if (AGENTE == 2) //chave
                     {L2_Q1->Ligar();}
               if (AGENTE == 3) //chave
                     {L2_Q1->Desligar();}
              }
    
              if (  ((COMPONENTE1) == "L3") )
              {if (AGENTE == 1) //chave
                     {L3_Q1->Chave();}
               if (AGENTE == 2) //chave
                     {L3_Q1->Ligar();}
               if (AGENTE == 3) //chave
                     {L3_Q1->Desligar();}
              }
              if (((COMPONENTE1)   == "L4") )
              {if (AGENTE == 1) //chave
                     {L4_Q1->Chave();}
               if (AGENTE == 2) //chave
                     {L4_Q1->Ligar();}
               if (AGENTE == 3) //chave
                     {L4_Q1->Desligar();}
              }
            }//AÇAO L = LIGAR
    
    
    
    
          //TOMADAS
          if ((COMPONENTE1.substring(0, 1)) == "T") // SE O COMPONENTE É IGUAL AO L = LUZ ENTRA NO BLOCO DE IFs DE LUZES
               {Serial.println("TOMADA");    
                if ( ACAO1 == "L") //LIGA DESLIGA
                    {if ( ((COMPONENTE1) == "T1")) // RELE_1 LIZ_1
                      {if (AGENTE == 1) //chave
                         {T1_Q1->Chave();}
                     if (AGENTE == 2) //chave
                         {T1_Q1->Ligar();}
                     if (AGENTE == 3) //chave
                         {T1_Q1->Desligar();}
                    }
                    if (  ((COMPONENTE1) == "T2") )
                      {if (AGENTE == 1) //chave
                         {T2_Q1->Chave();}
                       if (AGENTE == 2) //chave
                         {T2_Q1->Ligar();}
                       if (AGENTE == 3) //chave
                         {T2_Q1->Desligar();}
                     }
                    if (  ((COMPONENTE1) == "T3") )
                      {if (AGENTE == 1) //chave
                         {T3_Q1->Chave();}
                       if (AGENTE == 2) //chave
                         {T3_Q1->Ligar();}
                       if (AGENTE == 3) //chave
                         {T3_Q1->Desligar();}
                     }
                    if (((COMPONENTE1) == "T4") )
                      {if (AGENTE == 1) //chave
                         {T4_Q1->Chave();}
                       if (AGENTE == 2) //chave
                         {T4_Q1->Ligar();}
                       if (AGENTE == 3) //chave
                         {T4_Q1->Desligar();}
                     }
                   }//AÇAO L = LIGAR
              } //TOMADAS
    
    
          if ( ACAO1 == "A")  //ATIVA OU NAO FUNÇÃO AUTO DE LUZES
            {Serial.println("ACAO A");
             S1_Q1->ListAcaoSensor(1, (COMPONENTE1 + "_" + COMODO1));
            }//ATIVA OU NAO FUNÇÃO AUTO DE LUZES OU TOMADAS
    
    
    
          if (COMPONENTE1 == "S1")  // Alterar tempo do Sensor
          {S1_Q1->AlterTempsensor( atoi(ACAO1.c_str()) );
          }
    
      } //FIM IFs Q1 = QUARTO 1
    

  }//FIM VALIDAÇÃO DIGITOS VERIFICADORES DO PROTOCOLO



  if ( (V_INI1 + V_11 + V_21 + V_31 + V_41 + V_FIN1 + V_FIN21) == "#*****@") //VALIDAÇÃO DIGITOS VERIFICADORES DO PROTOCOLO DIA HORA LIGA DESLIGA
     {Serial.println("valido");
        if (COMODO1 ==  "Q1") // SE O COMODO É IGUAL AO Q1=QUARTO1 ENTRA NO BLOCO DE IFs DESSE QUARTO
          {Serial.println("Q1");
          
            if ( ACAO1 == "T")  //FUNÇÃO TIMER PARA LUZES LIGAR E DESLIGAR DETERMINADO HORARIO
             {Serial.println("ACAO T = PROGRAMAR TEMPO");
              Clock1->FuncTimer(comando,AUTOLIGA1,AUTODESLIGA1,DIAS,1);
             }//FUNÇÃO TIMER PARA LUZES LIGAR E DESLIGAR DETERMINADO HORARIO

          }//FIM IFs Q1 = QUARTO 1

  }//FIM VALIDAÇÃO DIGITOS VERIFICADORES DO PROTOCOLO DIA HORA LIGA DESLIGA





  if ( comando == "HORA")
  {

    Clock1->MostraData("FULL", "LCD");
    Clock1->MostraHora("FULL", "LCD");

    Clock1->MostraData("FULL", "SERIAL");
    Clock1->MostraHora("FULL", "SERIAL");

  }//fim hora






  if ( comando == "LCD")
  {//LIGA E DESLIGA LED DO LCD
    LUZ_LED();
  }//fim LCD
  
  
  if ( comando == "ALARME01011415")
    {Alarme1->AtiDesatAlarme();}








  //_______________________CONTROLE_________________________//

  if ( (V_INI2 + V_12 + V_22 + V_32 + V_42 + V_FIN2) == "#****@") //VALIDAÇÃO DIGITOS VERIFICADORES DO PROTOCOLO
  {
    //Serial.println("valido");
    if (COMODO2 ==  "Q1") // SE O COMODO É IGUAL AO Q1=QUARTO1 ENTRA NO BLOCO DE IFs DESSE QUARTO
    {
      Serial.println("Q1");


      if (COMPONENTE2 == "HOME...")  // SE O COMPONENTE É IGUAL AO L = LUZ ENTRA NO BLOCO DE IFs DE LUZES
      { Serial.println("HOME");


        if ( ACAO2 == "LIGA..") //ATIVA OU NAO FUNÇÃO AUTO DE LUZES
        { //irsend.sendNEC(0xFF30CF, 32);// código que sera enviado a tv para aumentar o volume
          for (int i = 0; i < 10; i++) {
            irsend.sendNEC(0xFF30CF, 32);// código que sera enviado a tv para aumentar o volume
          }
          Serial.println("LIGA HOME");
          lcd.setCursor(0, linha_lcd());
          lcd.print("LIGA HOME");
        }

        if ( ACAO2 == "MODE..") //ATIVA OU NAO FUNÇÃO AUTO DE LUZES
        { irsend.sendNEC(0xFF30CF, 32);// código que sera enviado a tv para aumentar o volume
          Serial.println("MODE HOME");
          lcd.setCursor(0, linha_lcd());
          lcd.print("MODE HOME");
        }
        if ( ACAO2 == "VOL+..") //ATIVA OU NAO FUNÇÃO AUTO DE LUZES
        { irsend.sendNEC(0xFFE817, 32);// código que sera enviado a tv para aumentar o volume
          Serial.println("VOL+ HOME");
          lcd.setCursor(0, linha_lcd());
          lcd.print("VOL+ HOME");
        }
        if ( ACAO2 == "VOL-..") //ATIVA OU NAO FUNÇÃO AUTO DE LUZES
        { irsend.sendNEC(0xFFD827, 32);// código que sera enviado a tv para aumentar o volume
          Serial.println("VOL- HOME");
          lcd.setCursor(0, linha_lcd());
          lcd.print("VOL- HOME");
        }
        if ( ACAO2 == "AUDIO.") //ATIVA OU NAO FUNÇÃO AUTO DE LUZES
        { irsend.sendNEC(0xFF00FF, 32);// código que sera enviado a tv para aumentar o volume
          Serial.println("AUDIO HOME");
          lcd.setCursor(0, linha_lcd());
          lcd.print("AUDIO HOME");
        }
        if ( ACAO2 == "MUTE..") //ATIVA OU NAO FUNÇÃO AUTO DE LUZES
        { irsend.sendNEC(0xFF20DF, 32);// código que sera enviado a tv para aumentar o volume
          Serial.println("MUTE HOME");
          lcd.setCursor(0, linha_lcd());
          lcd.print("MUTE HOME");
        }
        if ( ACAO2 == "PALSE.") //ATIVA OU NAO FUNÇÃO AUTO DE LUZES
        { irsend.sendNEC(0xFF08F7, 32);// código que sera enviado a tv para aumentar o volume
          Serial.println("PALSE HOME");
          lcd.setCursor(0, linha_lcd());
          lcd.print("PALSE HOME");
        }
        if ( ACAO2 == "CIMA..") //ATIVA OU NAO FUNÇÃO AUTO DE LUZES
        { irsend.sendNEC(0xFFA05F, 32);// código que sera enviado a tv para aumentar o volume
          Serial.println("CIMA HOME");
          lcd.setCursor(0, linha_lcd());
          lcd.print("CIMA HOME");
        }
        if ( ACAO2 == "BAIXO.") //ATIVA OU NAO FUNÇÃO AUTO DE LUZES
        { irsend.sendNEC(0xFFE01F, 32);// código que sera enviado a tv para aumentar o volume
          Serial.println("BAIXO HOME");
          lcd.setCursor(0, linha_lcd());
          lcd.print("BAIXO HOME");
        }
        if ( ACAO2 == "ESQ...") //ATIVA OU NAO FUNÇÃO AUTO DE LUZES
        { irsend.sendNEC(0xFF40BF, 32);// código que sera enviado a tv para aumentar o volume
          Serial.println("ESQUERDA HOME");
          lcd.setCursor(0, linha_lcd());
          lcd.print("ESQUERDA HOME");
        }
        if ( ACAO2 == "DIR...") //ATIVA OU NAO FUNÇÃO AUTO DE LUZES
        { irsend.sendNEC(0xFF48B7, 32);// código que sera enviado a tv para aumentar o volume
          Serial.println("DIREITA HOME");
          lcd.setCursor(0, linha_lcd());
          lcd.print("DIREITA HOME");
        }

      } //if (COMPONENTE2 == "HOME...")

    } //ENDIF Q1


  }//FIM VALIDAÇÃO DIGITOS VERIFICADORES DO PROTOCOLO
  //_______________________CONTROLE_________________________//



}
//------------------------FUNC_COMANDO()----------------------------------//























//------------------------comando_wifi----------------------------------//
String comando_wifi() {
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
    //Alarme1->Bip();
    /*
    Serial.print("Status:[");
    Serial.print(wifi.getIPStatus().c_str());
    Serial.println("]");

    Serial.print("Recebido de :");
    Serial.print(mux_id);
    Serial.println("[");
    */
    for (uint32_t i = 0; i < len; i++) {
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
  
  Alarme1->Bip();
  

  lcd.setBacklight(HIGH);
  lcd.setCursor(0, linha_lcd());
  lcd.print("Iniciando Setup");
  Serial.println("Iniciando Setup.");

  lcd.setCursor(0, linha_lcd());
  lcd.print("Reset fisico ESP");
  Serial.println("Reset fisico ESP");
  digitalWrite(RST, LOW);
  delay(100);
  digitalWrite(RST, HIGH);
  delay(4000);
  lcd.setCursor(0, linha_lcd());
  lcd.print("Reset logico ESP");
  Serial.println("Reset logico ESP");

  if (wifi.restart())
  { Serial.println("reset WIFI OK.");
    lcd.setCursor(0, linha_lcd());
    lcd.print("reset WIFI OK.");
    if (wifi.setOprToStation())
    { Serial.println("Station OK.");
      lcd.setCursor(0, linha_lcd());
      lcd.print("Station OK.");
      if (wifi.joinAP(SSID, PASSWORD))
      { Serial.println("Conectado com Sucesso.");
        lcd.setCursor(0, linha_lcd());
        lcd.print("Conectado ");
        Serial.println("IP: ");
        lcd.setCursor(0, linha_lcd());
        lcd.print("IP:");
        //rotina wifi.getLocalIP() retorna o IP usado na conexao com AP conectada.
        Serial.println(wifi.getLocalIP());
        lcd.print(wifi.getLocalIP().substring(14, 30));
        //delay(2000);   //MODIFIQUEI
        if (wifi.enableMUX())
        { Serial.println("Multiplas conexoes OK.");
          lcd.setCursor(0, linha_lcd());
          lcd.print("MultI conexoes OK.");
          //delay(500);   //MODIFIQUEI
          if (wifi.startTCPServer(8090))
          { Serial.println("SERV port 8090 OK");
            lcd.setCursor(0, linha_lcd());
            lcd.print("SERV port 8090 OK");
            if (wifi.setTCPServerTimeout(10))
            { Serial.println("timout 10 seconds");
              lcd.setCursor(0, linha_lcd());
              lcd.print("timout 10 seconds");
              lcd.setCursor(0, linha_lcd());
              lcd.print("Setup finalizado!");
              Serial.println("Setup finalizado!");
              //delay(1500);     //MODIFIQUEI
              lcd.clear();
              Serial.println("SMART_HOME");
              linha = -1;
              //delay(1000);
              //lcd.setBacklight(LOW);
              Alarme1->Bip();
            }
            else {
              Serial.println("Erro server timout");
              //lcd.clear ();
              lcd.setCursor(0, linha_lcd());
              lcd.print("Erro server timout");
              reset_wifi();
            }

          }
          else {
            Serial.println("Erro INIC Serv TCP");
            //lcd.clear ();
            lcd.setCursor(0, linha_lcd());
            lcd.print("Erro INIC Serv TCP");
            reset_wifi();
          }
        }
        else {
          Serial.println("Erro Multi conex");
          //lcd.clear ();
          lcd.setCursor(0, linha_lcd());
          lcd.print("Erro Multi conex");
          reset_wifi();
        }
      }
      else {
        Serial.println("Erro ConectaR AP");
        //lcd.clear ();
        lcd.setCursor(0, linha_lcd());
        lcd.print("Erro ConectaR AP");
        reset_wifi();
      }
    }
    else {
      Serial.println("Erro SET WIFI Station");
      //lcd.clear ();
      lcd.setCursor(0, linha_lcd());
      lcd.print("Erro SET WF Station");
      reset_wifi();
    }
  }

  else {
    Serial.println("Erro resetar WIFI");
    //lcd.clear ();
    lcd.setCursor(0, linha_lcd());
    lcd.print("Erro resetar WIFI");
    reset_wifi();
  }
}
//------------------------reset_wifi----------------------------------//





//------------------------LER SERIAL----------------------------------//
String leStringSerial() {
  String conteudo = "";
  char caractere;
  // Enquanto receber algo pela serial
  while (Serial2.available() > 0) {
    // Lê byte da serial
    caractere = Serial2.read();
    // Ignora caractere de quebra de linha
    if (caractere != '\n') {
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

  //String comando;
  String comando1 = comando_wifi();
  //String comando2 = leStringSerial();

  if ( comando1 != "" ) {
    Serial.println("comando1");
    FUNC_COMANDO(comando1, 1);
  }
  //else {
    //Serial.println("comando2");
    //FUNC_COMANDO(comando2, 1);
  //}


  S1_Q1->VerificSensor();
  Clock1->FuncTimer("","","","",2);


}//fim void








