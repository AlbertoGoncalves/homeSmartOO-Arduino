#define CH_PD 12 //sinal de controle de CH_PD
#define RST   11 //sinal de controle de RST
#define GPIO0 10 //sinal de controle de GPIO0

void setup() {
  pinMode(CH_PD,OUTPUT);
  pinMode(RST,OUTPUT);
  pinMode(GPIO0,OUTPUT);
  
  digitalWrite(CH_PD,HIGH); //Setado em alto - funcionamento normal
  digitalWrite(RST,HIGH); //RST em alto - funcionamento normal
  digitalWrite(GPIO0,HIGH); //GPIO0 em alto - funcionamento no rmal
  
  // Inicializa ambas as portas
  Serial.begin(115200);
  Serial3.begin(115200);
  Serial.println("Iniciando Setup.");
}
 
void loop() {
  // Ve se tem sinal na Serial1 e manda para a Serial
  if (Serial3.available()) {
    int inByte = Serial3.read();
    Serial.write(inByte);
  }
 
  // Analogamente, ve se tem sinal na Serial, e manda para Serial1
  if (Serial3.available()) {
    int inByte = Serial3.read();
    Serial1.write(inByte);
  }
}
