#define RELE_PIN D7

void setup() {
  pinMode(RELE_PIN, OUTPUT);
}

void loop() {
  digitalWrite(RELE_PIN, HIGH);
}
