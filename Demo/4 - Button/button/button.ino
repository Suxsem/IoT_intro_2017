#define BUTTON_PIN D8

void setup() {
  pinMode(BUTTON_PIN, INPUT);
  Serial.begin(9600);
}

void loop() {
  boolean value = digitalRead(BUTTON_PIN);
  Serial.println(value);
}
