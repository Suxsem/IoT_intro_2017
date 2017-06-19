#include <ESP8266WiFi.h>
#include <ArduinoOTA.h>

const char* ssid = "***";
const char* password = "***";

void setup(void){
  WiFi.begin(ssid, password);
  delay(6000);
  
  ArduinoOTA.begin();
}

void loop(void){
  ArduinoOTA.handle();
}
