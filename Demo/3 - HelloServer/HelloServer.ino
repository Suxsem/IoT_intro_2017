#include <ESP8266WiFi.h>

#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#define LED_PIN D8

const char* ssid = "***";
const char* password = "***";

ESP8266WebServer server(80);

void handleRoot() {
  server.send(200, "text/plain", "led high");
  digitalWrite(LED_PIN,HIGH);
}

void setup() {
  Serial.begin(9600);

  pinMode(LED_PIN,OUTPUT);
  
  WiFi.begin(ssid, password);
  delay(6000);
  
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  
  server.begin();
}

void loop() {
  server.handleClient();
}
