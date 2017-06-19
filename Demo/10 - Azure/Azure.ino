#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoOTA.h>

#define PHOTO_PIN A0

const char* ssid = "***";
const char* password = "***";

#define MQTTid              "test_device"                  //id of this mqtt client
#define MQTTip              "192.168.137.1"              //ip address or hostname of the mqtt broker
#define MQTTport            8883                         //port of the mqtt broker
#define MQTTuser            "***"                       //username of this mqtt client
#define MQTTpsw             "***"                   //password of this mqtt client
#define MQTTpubQos          1                            //qos of publish (see README)
#define MQTTsubQos          1                            //qos of subscribe

void mqttDataCb(char* topic, byte* payload, unsigned int length);

WiFiClient wclient;
PubSubClient client(MQTTip, MQTTport, mqttDataCb, wclient);

/* ------------ */

void setup() {
  pinMode(PHOTO_PIN, INPUT);
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  delay(6000);
  ArduinoOTA.begin();
  Serial.println(WiFi.localIP());
  client.connect(MQTTid, MQTTuser, MQTTpsw);
  delay(6000);
  client.publish("devices/test_device/messages/events/", "{ 'messaggio':'hello azure!' }", MQTTpubQos, false);
  client.subscribe("devices/test_device/messages/devicebound/#", MQTTsubQos);
  //(String("a") + String(10) + String("b")).c_str()
}

double lastMillis = millis();

void loop() {
  client.loop();
  ArduinoOTA.handle();
  if ((millis() - lastMillis) > 2000) {
    lastMillis = millis();
    double value = analogRead(PHOTO_PIN);
    String messaggio = String("{ 'luce':'") + String(value) + String("' }");
    client.publish("devices/test_device/messages/events/", messaggio.c_str(), MQTTpubQos, false);
    delay(5000);
    Serial.println(messaggio);
  }
}

void mqttDataCb(char* topic, byte* payload, unsigned int length) {
  char* message = (char *) payload;
  message[length] = 0;
  Serial.println(message);
}
