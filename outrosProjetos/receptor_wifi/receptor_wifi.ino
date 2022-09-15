
#include "ESP8266.h"


//------------------------wifi--------------------------// 
#define CH_PD 12
#define RST   11
#define GPIO0 10
//Coloque nos campos indicados o nome e senha da sua rede WiFi
#define SSID        "(ALBERTO_JUNIOR)"
#define PASSWORD    "ALBERTOjunior121212"

//Cria objeto de conexão wifi com o módulo, usando a Serial1 do Mega.
ESP8266 wifi(Serial1);
//------------------------wifi--------------------------//



void setup() {
  // put your setup code here, to run once:
 
 //------------------------SERIAL--------------------------//
  Serial.begin(9600); //Inicializa a serial
  Serial2.begin(9600); //Inicializa a serial
 //------------------------SERIAL--------------------------//

   //------------------------wifi--------------------------//
    pinMode(CH_PD,OUTPUT);
    pinMode(RST,OUTPUT);
    pinMode(GPIO0,OUTPUT);
    
    digitalWrite(CH_PD,HIGH); //setado em ALTO - operacao normal
    digitalWrite(RST,HIGH); //setado em ALTO - operhttp://www.embarcados.com.br/arduino-mega-2560/acao normal
    digitalWrite(GPIO0,HIGH); //setado em ALTO - operacao normal
  
  
  Serial.println("Iniciando Setup.");
  
  Serial.println("Reset fisico ESP");
  digitalWrite(RST,LOW);
  delay(100);
  digitalWrite(RST,HIGH);
  delay(3000);
  
  Serial.println("Reset logico ESP");
  if (wifi.restart()) {
        Serial.println("reset AP OK.");
    } else {
        Serial.println("Erro em reset  AP.");
    } 
  Serial.println("Reset logico ESP FIM"); 

        
    Serial.print("Versao de Firmware ESP8266: ");
    //A funcao wifi.getVersion() retorna a versao de firmware informada pelo modulo no inicio da comunicacao
    Serial.println(wifi.getVersion().c_str());
      
    //Vamos setar o modulo para operar em modo Station (conecta em WiFi) e modo AP (é um ponto de WiFi tambem)
    //modo ap e Station
    
    //if (wifi.setOprToSoftAP()) {
    if (wifi.setOprToStation()) { 
      Serial.println("Station e AP OK.");
      //Serial.println("Station OK.");
    } else {
        //Serial.println("Erro em setar Station e AP.");
        Serial.println("Erro em setar Station");
    }
    

 
    //Agora vamos conectar no ponto de WiFi informado no inicio do codigo, e ver se corre tudo certo
    if (wifi.joinAP(SSID, PASSWORD)) {
        Serial.println("Conectado com Sucesso.");
        Serial.println("IP: ");
        //rotina wifi.getLocalIP() retorna o IP usado na conexao com AP conectada.
        Serial.println(wifi.getLocalIP().c_str());    
    } else {
        Serial.println("Falha na conexao AP.");
    }
    
    //Agora vamos habiliar a funcionalidade MUX, que permite a realizacao de varias conexoes TCP/UDP
    if (wifi.enableMUX()) {
        Serial.println("Multiplas conexoes OK.");
    } else {
        Serial.println("Erro ao setar multiplas conexoes.");
    }
    
    //Inicia servidor TCP na porta 8090 (veja depois a funcao "startServer(numero_porta)", que serve para UDP!
    if (wifi.startTCPServer(8090)) {
        Serial.println("Servidor iniciado com sucesso.");
    } else {
        Serial.println("Erro ao iniciar servidor.");
    }
    
    
    if (wifi.setTCPServerTimeout(10)) { 
        Serial.print("set tcp server timout 10 seconds\r\n");
    } else {
        Serial.print("set tcp server timout err\r\n");
    }
    
    Serial.println("Setup finalizado!");
   //------------------------wifi--------------------------//
  
}




void reset_wifi(){  
  
  Serial.println("Reset logico ESP");
  
  if (wifi.restart()) {
        Serial.println("reset AP OK.");
    } else {
        Serial.println("Erro em reset  AP.");
    } 
  Serial.println("Reset logico ESP FIM"); 
           
    //Vamos setar o modulo para operar em modo Station (conecta em WiFi) e modo AP (é um ponto de WiFi tambem)
    //modo ap e Station
    
    //if (wifi.setOprToSoftAP()){
    if (wifi.setOprToStation()) {   
     //Serial.println("Station e AP OK.");
     Serial.println("Station OK.");
    } else {
        //Serial.println("Erro em setar Station e AP.");
       Serial.println("Erro em setar Station");
    }
 
    //Agora vamos conectar no ponto de WiFi informado no inicio do codigo, e ver se corre tudo certo
    if (wifi.joinAP(SSID, PASSWORD)) {
        Serial.println("Conectado com Sucesso.");
        Serial.println("IP: ");
        //rotina wifi.getLocalIP() retorna o IP usado na conexao com AP conectada.
       Serial.println(wifi.getLocalIP().c_str());    
      } else {
      Serial.println("Falha na conexao AP.");
    }
     
    //Agora vamos habiliar a funcionalidade MUX, que permite a realizacao de varias conexoes TCP/UDP
    if (wifi.enableMUX()) {
        Serial.println("Multiplas conexoes OK.");
    } else {
        Serial.println("Erro ao setar multiplas conexoes.");
    }
    
    //Inicia servidor TCP na porta 8090 (veja depois a funcao "startServer(numero_porta)", que serve para UDP!
    if (wifi.startTCPServer(8090)) {
        Serial.println("Servidor iniciado com sucesso.");
    } else {
        Serial.println("Erro ao iniciar servidor.");
    }
    
   
    if (wifi.setTCPServerTimeout(10)) { 
       Serial.print("set tcp server timout 10 seconds\r\n");
    } else {
       Serial.print("set tcp server timout err\r\n");
    }
    
    Serial.println("Setup finalizado!");
   } 





















void loop() {
  
  String result;
  boolean valid = false;
  //Serial.println("inicia leitura wifi");  
  //Variavel para buffer de dados de trasmissao
    uint8_t buffer[128] = {0};
 
    //Como usamos multiplas conexoes, cada conexao tem sua ID, e precisa ser armazenada para referencia no programa. Usamos    //essa variavel para isso.
    uint8_t mux_id;
    
    //E esta variavel len serve para armazenar o comprimento de dados recebidos por meio da rotina wifi.recv(), que tambem     //associa ao buffer os dados recebidos e ao mux_id a id responsavel pela transmissao
    uint32_t len = wifi.recv(&mux_id, buffer, sizeof(buffer), 1000);
    
    if (len > 0) {
      Serial.println("lendo wifi");
      valid = true; 
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
   if (valid == true){
   Serial.println("vou enviar para seiral");
     Serial2.println(result);
   } 



  if (wifi.kick()) {
       //Serial.println("vivo");


    } else {
        Serial.println("2Erro ");
        //reset_wifi();
       
        delay(2500);
         Serial.println(wifi.getLocalIP().c_str());
    
        //Agora vamos habiliar a funcionalidade MUX, que permite a realizacao de varias conexoes TCP/UDP
    if (wifi.enableMUX()) {
        Serial.println("enable Multiplas conexoes OK.");
    } else {
        Serial.println("enable Erro ao setar multiplas conexoes.");
    }

       //Inicia servidor TCP na porta 8090 (veja depois a funcao "startServer(numero_porta)", que serve para UDP!
    if (wifi.startTCPServer(8090)) {
        Serial.println("Servidor iniciado com sucesso.");
    } else {
        Serial.println("Erro ao iniciar servidor.");
    }
        
      }





}

