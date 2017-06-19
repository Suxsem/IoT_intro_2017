#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoOTA.h>
#include <Servo.h> 

#define SERVO_PIN D7

Servo myservo;

const char* ssid = "***";
const char* password = "***";

#define MQTTid              "esp8266-1"                  //id of this mqtt client
#define MQTTip              "192.168.137.1"              //ip address or hostname of the mqtt broker
#define MQTTport            1883                         //port of the mqtt broker
#define MQTTuser            ""                       //username of this mqtt client
#define MQTTpsw             ""                   //password of this mqtt client
#define MQTTpubQos          2                            //qos of publish (see README)
#define MQTTsubQos          1                            //qos of subscribe
#define PRELE D6

void mqttDataCb(char* topic, byte* payload, unsigned int length);

WiFiClient wclient;
PubSubClient client(MQTTip, MQTTport, mqttDataCb, wclient);

/* ------------ */

void setup() {
  myservo.attach(SERVO_PIN);
  pinMode(PRELE, OUTPUT);
  digitalWrite(PRELE, HIGH);
  WiFi.begin(ssid, password);
  delay(6000);
  ArduinoOTA.begin();
  client.connect(MQTTid, MQTTuser, MQTTpsw);
  client.publish("test", "hello", MQTTpubQos, false);
  client.subscribe("valvola/posizione", MQTTsubQos);
}

void loop() {
  client.loop();
  ArduinoOTA.handle();
}

void mqttDataCb(char* topic, byte* payload, unsigned int length) {
  char* message = (char *) payload;
  message[length] = 0;
  myservo.write(String(message).toInt());
}
