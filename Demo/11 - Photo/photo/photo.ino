#define PHOTO_PIN A0

void setup() {
  pinMode(PHOTO_PIN, INPUT);
  Serial.begin(9600);
}

void loop() {
  double value = analogRead(PHOTO_PIN);
  Serial.println(value);
}
