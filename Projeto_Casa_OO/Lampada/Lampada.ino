class Lampada{
  private:
  int _pino;
  String _CodRef;

  public:
  Lampada(int pin, String codref, bool inicia);
  void LigarLamp();  
  void DesligarLamp();
  void ChaveLamp();
  bool EstadoLamp();
};
 
Lampada::Lampada(int pin, String codref, bool inicia)
{
  _pino   = pin;
  _CodRef = codref;
  pinMode(_pino,   OUTPUT); //Define o pino como saida
  
  // inicia sistema ligada ou desligada
  if(inicia == true)
    {digitalWrite(_pino, LIGA);}
  else
    {digitalWrite(_pino, DESLIGA);}
   
}

void Lampada::LigarLamp()
{                         
       Serial.println("Liga chave" + _CodRef);
//     lcd.setCursor(0,linha_lcd());
//     lcd.print("Desliga R4_L4_Q1");
     digitalWrite(_pino, LIGA);
//     C_L4_Q1 = false;                                  
}


void Lampada::DesligarLamp()
{
         Serial.println("Desliga chave" + _CodRef);
//       lcd.setCursor(0,linha_lcd());
//       lcd.print("Desliga R4_L4_Q1");
       digitalWrite(_pino, DESLIGA);
//       C_L4_Q1 = false;
}


void Lampada::ChaveLamp()
{                        
        if (digitalRead(_pino) == DESLIGA)  
           {Serial.println("Liga chave" + _CodRef);
            //lcd.setCursor(0,linha_lcd());
            //lcd.print("Liga R4_L4_Q1");
            digitalWrite(_pino, LIGA);
            //C_L4_Q1 = true;
           }
    
        else    
           {Serial.println("Desliga chave" + _CodRef);
            //lcd.setCursor(0,linha_lcd());
            //lcd.print("Desliga R4_L4_Q1");
            digitalWrite(_pino, DESLIGA);
            //C_L4_Q1 = false;
           } 
}

bool Lampada::EstadoLamp()
{                        
        if (digitalRead(_pino) == LIGA)  
           {return(true);}
        else    
           {return(false);} 
}
