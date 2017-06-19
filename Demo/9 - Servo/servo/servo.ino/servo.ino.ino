#include <Servo.h> 
#include <ArduinoOTA.h>
#define SERVO_PIN D7

Servo myservo;

void setup() 
{ 
  ArduinoOTA.begin();
  myservo.attach(SERVO_PIN);
} 

int posizione = 0;
void loop()
{
  ArduinoOTA.handle();
  myservo.write(posizione);              // tell servo to go to position in variable 'pos' 
  delay(10);
  posizione++;
  if (posizione == 180)
    posizione = 0;
} 

