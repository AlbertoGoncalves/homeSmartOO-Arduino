#include "ESP8266.h"
 
#define CH_PD 44
#define RST 46
#define GPIO0 48
 
//Coloque nos campos indicados o nome e senha da sua rede WiFi
#define SSID        "(ALBERTO_JUNIOR)"
#define PASSWORD    "ALBERTOjunior121212"
 
//Cria objeto de conexão wifi com o módulo, usando a Serial1 do Mega.
ESP8266 wifi(Serial1);
 
void setup(void)
{
    pinMode(CH_PD,OUTPUT);
    pinMode(RST,OUTPUT);
    pinMode(GPIO0,OUTPUT);
    digitalWrite(CH_PD,HIGH); //setado em ALTO - operacao normal
    digitalWrite(RST,HIGH); //setado em ALTO - operhttp://www.embarcados.com.br/arduino-mega-2560/acao normal
    digitalWrite(GPIO0,HIGH); //setado em ALTO - operacao normal
 
    Serial.begin(9600);
    Serial.println("Iniciando Setup.");
    
    Serial.print("Versao de Firmware ESP8266: ");
    //A funcao wifi.getVersion() retorna a versao de firmware informada pelo modulo no inicio da comunicacao
    Serial.println(wifi.getVersion().c_str());
      
    //Vamos setar o modulo para operar em modo Station (conecta em WiFi) e modo AP (é um ponto de WiFi tambem)
    if (wifi.setOprToStationSoftAP()) {
        Serial.println("Station e AP OK.");
    } else {
        Serial.println("Erro em setar Station e AP.");
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
    Serial.println("Setup finalizado!");
}
 
//Na conexao TCP, basicamente a funcionalidade a ser mostrada sera a de "echo", ou seja, a aplicacao ira retornar todos os //dados enviados para ela via socket TCP.
void loop(void)
{
    //Variavel para buffer de dados de trasmissao
    uint8_t buffer[128] = {0};
 
    //Como usamos multiplas conexoes, cada conexao tem sua ID, e precisa ser armazenada para referencia no programa. Usamos    //essa variavel para isso.
    uint8_t mux_id;
 
    //E esta variavel len serve para armazenar o comprimento de dados recebidos por meio da rotina wifi.recv(), que tambem     //associa ao buffer os dados recebidos e ao mux_id a id responsavel pela transmissao
    uint32_t len = wifi.recv(&mux_id, buffer, sizeof(buffer), 100);
    if (len > 0) {
        Serial.print("Status:[");
        Serial.print(wifi.getIPStatus().c_str());
        Serial.println("]");
        
        Serial.print("Recebido de :");
        Serial.print(mux_id);
        Serial.print("[");
        for(uint32_t i = 0; i < len; i++) {
            Serial.print((char)buffer[i]);
        }
        Serial.print("]\r\n");
        
        //Agora envia de volta. A referencia para o socket TCP criado é o mux_id, ou id da conexao, usado aqui na rotina
        //wifi.send, veja abaixo:
        //if(wifi.send(mux_id, buffer, len)) {
       //     Serial.print("Enviado de volta...\r\n");
      //  } else {
      //      Serial.print("Erro ao enviar de volta\r\n");
      //  }
        
        //E, como sempre, liberar a conexao TCP, de modo a permitir que novas conexoes sejam realizadas.
        if (wifi.releaseTCP(mux_id)) {
            Serial.print("Liberando conexao TCP com ID: ");
            Serial.print(mux_id);
            Serial.println(" OK");
        } else {
            Serial.print("Erro ao liberar TCP com ID: ");
            Serial.print(mux_id);
        }
        
        Serial.print("Status:[");
        Serial.print(wifi.getIPStatus().c_str());
        Serial.println("]");
    }
}

