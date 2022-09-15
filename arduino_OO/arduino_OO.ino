//############  CODIGO DA CLASSE BOTAO  ################
class Botao {
  private:
    int _pino_botao;
    int _debounce_delay;
    int _leitura_anterior;
    int _leitura_anterior_db;
    long _time_ultimo_debounce;
    long _debounce_ok;
    bool _pressionou;
    bool _soltou;
  public:
    Botao(int pin, int debounce);
    void atualiza();
    bool pressionou();
    bool soltou();
    long tempo_pressionado();
};

Botao::Botao(int pin, int debounce){
  _pressionou     = false;
  _soltou         = false;
  _pino_botao     = pin;
  _debounce_delay = debounce;
  pinMode(_pino_botao, INPUT);
}

void Botao::atualiza(){  
  int leitura_atual = digitalRead(_pino_botao);
  if (leitura_atual != _leitura_anterior    )                  { _time_ultimo_debounce = millis(); _debounce_ok = 0; }
  if (  (millis() - _time_ultimo_debounce) > _debounce_delay ) { _debounce_ok = 1;                                   }
  if (_debounce_ok == 1) { 
    _pressionou          = (leitura_atual == 1 && _leitura_anterior_db == 0) ; 
    _soltou              = (leitura_atual == 0 && _leitura_anterior_db == 1) ;
    _leitura_anterior_db = leitura_atual; 
  }
  _leitura_anterior = leitura_atual;  
}

bool Botao::pressionou()        {  return _pressionou;  }
bool Botao::soltou()            {  return _soltou;      }
long Botao::tempo_pressionado() {  
  if ( _leitura_anterior_db ) {
    return ( millis()-_time_ultimo_debounce );
  } else {
    return 0;
  }  
}

//##############  FIM CODIGO DA CLASSE BOTAO  #############

const int PINO_LED_1 = 8;
const int PINO_LED_2 = 9;
const int PINO_LED_3 = 10;

Botao *b; //ponteiro para botao
Botao *b2; //ponteiro para botao

void setup() {
  b = new Botao(11, 100); //pino 11 , debounce time 100
  b2 = new Botao(12, 100); //pino 12 , debounce time 100
  Serial.begin(9600);
}

void loop() { 
  b->atualiza(); //faz a leitura do estado do pino e atualiza as variaveis de controle
  
  if ( b->pressionou() )               {  led_1(); Serial.println("pressionou"); } //liga led 1
  if ( b->soltou() )                   {  led_2(); Serial.println("soltou"); } //liga led 2
  if ( b->tempo_pressionado() > 3000 ) {  led_3(); Serial.println("3 segundos"); } //aciona beep depois de 3 segundos pressionado
  
  
  b2->atualiza(); //faz a leitura do estado do pino e atualiza as variaveis de controle
  
  if ( b2->pressionou() )               {  led_1(); Serial.println("pressionou"); } //liga led 1
  if ( b2->soltou() )                   {  led_2(); Serial.println("soltou"); } //liga led 2
  if ( b2->tempo_pressionado() > 3000 ) {  led_3(); Serial.println("3 segundos"); } //aciona beep depois de 3 segundos pressionado  
  
}

void led_1() { digitalWrite(PINO_LED_1, !digitalRead(PINO_LED_1)); }
void led_2() { digitalWrite(PINO_LED_2, !digitalRead(PINO_LED_2)); }
void led_3() { digitalWrite(PINO_LED_3, true); }
