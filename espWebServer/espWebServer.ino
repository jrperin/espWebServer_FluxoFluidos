/*
    OPALA TUBARAO - Web Server
    Versao....: 1.0.0
    Autor.....: Yuri Camara
    Data......: 21/10/2019
    Descrição.: Permite que dados sejam enviados pela porta serial e atualiza
                o WebServer com SSID = OPALA_TUBARAO no IP = 192.168.0.1
                A WebPage será atualizada a cada 5 segundos.
                Os dados devem ser enviados pela usb no padrão: #@{"vazao" : "10.0 l/seg", "volume" : "10 m3"}@#
                #@ e @# são sentinelas dos dados e devem ser enviados antes e depois dos dados no formato json.
    Hardware..: Foi utilizada a placa para BootLoad do ESP8266 do site www.eletroafinidade.com
*/

/*
   NOTAS:
   ---------------------------------------
   ESP8266 - 01
   Memoria = 512Kb (64Kb SPIFFS)
   ---------------------------------------
   
   ---------------------------------------
   Equivalencia das saidas Digitais entre
   NodeMCU e ESP8266 (na IDE do Arduino)
   NodeMCU - ESP8266
     D0    =   16;
     D1    =    5;
     D2    =    4;
     D3    =    0;
     D4    =    2;
     D5    =   14;
     D6    =   12;
     D7    =   13;
     D8    =   15;
     D9    =    3;
     D10   =    1;

   -------------------------------------------
    ESP8266-01 - PIN NUMBERS
   ------------PIN----    ------------PIN-----
    1- GND   = N/A         2- GPIO1 = 1 = TX
    3- GPIO2 = 2           4- CH_PD = N/A
    5- GPIO0 = 0           6- RESET = N/A
    7- GPIO3 = 3 = RX      8- VCC   = N/A
   
*/

/* -----------------------------------------------
 *  DEBUG MODE -> imprime na Serial myprint e myprintln -> Util.ino
*/
#define DEVMODE



/* -----------------------------------------------*/
#include <FS.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>       // Install from libraries (So funciona Versao 5)

const char* pgmVersion   = "1.0.0"      ;
const char* filename     = "/config.json";

const char* SSIDName     = "OPALAO_TUBARAO";
/*
 * struct Config -> usado principalmente 
 * em Config.ino para carga das variáveis
 */
struct Config {
  char     vazao[64];
  char     volume[64];
  char     custo[64];
};
Config config;


String ipAp;
IPAddress myIpAp(192, 168, 0, 1);     // IP para conectar no modo de SETUP
IPAddress myIpSubmask( 255, 255, 255, 0);
ESP8266WebServer server(80);
WiFiClient wifiClient;                //Instância do WiFiClient

String jsonStr;

/* ----------------------------- SETUP ---------------------------------------- */

void setup() {


  Serial.begin(115200);

  delay(10);

  server.stop();
  
  setInitialConfigValues(false); // Config.ino  true = Formatar / false = Nao formatar

  /* Configurando o IP do AP */
  WiFi.mode(WIFI_AP);
  delay(150);
  WiFi.softAPConfig(myIpAp, myIpAp, myIpSubmask);
  WiFi.softAP(SSIDName);

  myprintln("AP MODE - ON");

  String ip =
    String(WiFi.localIP()[0]) + "." +
    String(WiFi.localIP()[1]) + "." +
    String(WiFi.localIP()[2]) + "." +
    String(WiFi.localIP()[3]);

  String ipApStr =
    String(WiFi.softAPIP()[0]) + "." +
    String(WiFi.softAPIP()[1]) + "." +
    String(WiFi.softAPIP()[2]) + "." +
    String(WiFi.softAPIP()[3]);

  ipAp = ipApStr;

  myprint  ("SSID: ");
  myprint  (SSIDName);
  myprint  (" | IP: ");
  myprint  (ipApStr);
  myprint  (" | Local IP: ");
  myprintln(ip);

  serverInit(); //WebServer.ino

}

/* ----------------------------- LOOP ----------------------------------------- */
void loop() {

  server.handleClient();  // Administra as requisicoes dos clientes

  jsonStr = "";

  // Verifica se chegou algo na serial (rx/tx) para ser salvo
  while (Serial.available()){

    delay(3);
    char c = Serial.read();
    jsonStr += c;
    
  }

  if (jsonStr.length() > 4){
    String jsonAux = "";
    int index1 = jsonStr.indexOf("#@");
    int index2 = jsonStr.indexOf("@#");

    if (index1 > -1 and index2 > index1){
      jsonAux = jsonStr.substring(index1 + 2, index2);
      
      if (setJson(jsonAux, config) == 0){
        if (saveConfiguration(filename, config) == 0){
          myprintln("Json e Arquivos vindos da serial salvos");
        }else{
          myprint("Erro ao salvar o arquivo do json vindo pela serial [");
          myprint(filename);
          myprintln("]");
        }
      }else{
        myprint("Erro ao fazer o parse do Json vindo da serial ");
        myprintln(jsonAux);
      }
      
    }else{
      myprint("index1 = ");
      myprint(String(index1));
      myprint(" | index2 = ");
      myprintln(String(index2));
    }
    
    myprint("jsonStr = ");
    myprintln(jsonAux);  
  }
  
}
