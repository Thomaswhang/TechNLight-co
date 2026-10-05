const int soundSensor = 2;
const int lamp = 13;

bool lampState = false;

void setup() {
  pinMode(soundSensor, INPUT);
  pinMode(lamp, OUTPUT);

  digitalWrite(lamp, LOW);
}
void loop() {
  if (digitalRead(soundSensor) == HIGH) {
    lampState = !lampState;

    digitalWrite(lamp, lampState);

    delay(500);
  }
}