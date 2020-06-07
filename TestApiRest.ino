#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266HTTPClient.h>
#include <FormsGoogle.h>
#define INCREMENT 20000
#define WAITING_LOOP 10000
int waiting_loop = WAITING_LOOP;

const char *ssid = "TIGO-B13F";
const char *password = "2NB112101391";
const char fingerprint[] PROGMEM = "1C 9A D3 68 40 3A 92 46 DC D1 51 A2 71 CF 71 67 5A AC F5 5B";//docs.google.com
const String keyConnect =  "1FAIpQLSdal5EO0E42S8dvgnGJzjhsj88afyhHqbBa9fTRU5FXZh-5Qw";
String params[] = {"entry.802876412="//Campo
                ,"entry.1605107394="//campo
                ,"entry.1627871440="//campo value isOpen
                ,"entry.428488488="//campo
                };//
String paramsSend[4];

FormsGoogle form;
void setup() {
  pinMode(LED_BUILTIN,OUTPUT);
  Serial.begin(115200);
  WiFi.mode(WIFI_OFF);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid,password);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
  }
  form.setFingerPrint(fingerprint);
  form.setKeyConnect(keyConnect);
  form.activeDebugMode();
  digitalWrite(LED_BUILTIN,0);
}

void loop() {
  digitalWrite(LED_BUILTIN,0);
  sending();
  delay(waiting_loop);
}

void blind(int times){
  digitalWrite(LED_BUILTIN,0);
  digitalWrite(LED_BUILTIN,1);
  delay(times);
  digitalWrite(LED_BUILTIN,0);
  digitalWrite(LED_BUILTIN,0);
}

void sending(){
  paramsSend[0] = params[0]+"0";
  paramsSend[1] = params[1]+"0";
  paramsSend[2] = params[2]+"isOpen";
  paramsSend[3] = params[3]+"0"; 
  form.addParams(paramsSend);
  if(form.send()){
    Serial.println("Enviado correctamente");
    waiting_loop = WAITING_LOOP;
    blind(1000);
  }else{
    waiting_loop += INCREMENT;
    blind(1000);
    blind(1000);
    Serial.println("Error en el envio verifique activando modeDebug");
    Serial.println(String("Siguiente ciclo en ")+(waiting_loop/1000)+" seg.");
  }
 }
