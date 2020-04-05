/*
 * Date: Sun, 05/04/2020
 * Desc: ESP8266, SPIFFS websocket
 * Info: Turn ON/OFF LED 16
 */
#include "settings.h"
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <FS.h>
#include <ArduinoJson.h>
#include <WebSocketsServer.h>

ESP8266WebServer server;
WebSocketsServer webSocket = WebSocketsServer(88);

uint8_t pin_led = 16;
char* ssid = my_ssid;
char* password = my_pass;

int websockMillis = 50;
String website, JSONtxt;
boolean LEDonoff = true;



void WebSite()
{
  server.send(200, "text/html", webSiteCont);
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length){
  String payloadString = (const char *)payload;
  Serial.print("payloadString= ");
  Serial.println(payloadString);

  if(type == WStype_TEXT){
    byte separator = payloadString.indexOf('=');
    String var = payloadString.substring(0, separator);
    Serial.print("var= ");
    Serial.println(var);
    String val = payloadString.substring(separator+1);
    Serial.print("val= ");
    Serial.println(val);
    Serial.println("------------");

    if(var == "LEDonoff"){
      LEDonoff = false;
      if(val == "ON"){
        LEDonoff = true;
      }
    }
  }
}

void setup()
{
  SPIFFS.begin();
  pinMode(pin_led, OUTPUT);
  WiFi.begin(ssid,password);
  Serial.begin(115200);
  while(WiFi.status()!=WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.print("MAC Address: ");
  Serial.println(WiFi.macAddress());

  server.on("/", WebSite);
  server.begin();

  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}

void loop()
{
  server.handleClient();
  webSocket.loop();
  if(LEDonoff == true){
    digitalWrite(pin_led, LOW);
  }else{
    digitalWrite(pin_led, HIGH);
  }
  
  String LEDswitch = "OFF";
  if(LEDonoff == true){
    LEDswitch = "ON";
  }
  JSONtxt = "{\"LEDonoff\":\"" + LEDswitch + "\"}";
  webSocket.broadcastTXT(JSONtxt);
}
