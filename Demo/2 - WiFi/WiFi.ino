#include <ESP8266WiFi.h>

const char* ssid = "***";
const char* password = "***";

void setup(void){
  Serial.begin(9600);
  
  WiFi.begin(ssid, password);
  delay(6000);
  
  Serial.println(WiFi.localIP());

}

void loop(void){
}
