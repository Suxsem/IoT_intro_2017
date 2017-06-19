#define PIR_PIN D3

void setup() {
  Serial.begin(9600);
}

void loop() {
  boolean value = digitalRead(PIR_PIN);
  Serial.println(value);
}
