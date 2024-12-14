#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#ifndef STASSID
#define STASSID "your-ssid"
#define STAPSK  "your-password"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

class WidmoMaskController{
  static ESP8266WebServer *server;
  int eyePins[]={5,4,2,13,12,14,15};
  static void eyeTurnOff(){
    for(int i=0;i<7;i++){
      digitalWrite(i, 0);
    }
  }
  static bool setEyeDirection(int led){
    if(led>=0&&led<7){
      eyeTurnOff();
      digitalWrite(eyePins[led], 1);
      return true;
    }else{
      return false;
    }
  }
  static void eyeSwitch(bool turnOn){
    eyeTurnOff();
    if(turnOn){
      digitalWrite(eyePins[3], 1);
    }
  }
  /*
   * eye map
   *  5    4
   * 2  13  12
   *  14  15
   */
  Controller(int port){
    server=new ESP8266WebServer(port);
  }
  void setupServer(){
    server.on("/", [](){
      WidmoMaskController::
      server.send(200, "text/plain", "this works as well");
    });

    server.on("/direct", []() {
      if(WidmoMaskController::setEyeDirection()){
        
      }else{
        WidmoMaskController::server->send(200, "application/json", "{\"echo\":\"ok\"}");
      }
    });
    server.onNotFound(handleNotFound);
  
    server.begin();
  }
  hostServer(){
    server.handleClient();
  }
};
void handleRoot() {
  digitalWrite(led, 1);
  server.send(200, "text/plain", "hello from esp8266!");
  digitalWrite(led, 0);
}

void handleNotFound() {
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}

void setup(void) {
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  
  Serial.println("HTTP server started");
}

void loop(void) {
  
  MDNS.update();
}