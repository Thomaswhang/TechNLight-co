const int soundSensor = 2;
const int lamp = 13;

bool lampState = false;

int clapCount = 0;
unsigned long firstClapTime = 0;

const unsigned long clapWindow = 800; // Time allowed between claps

void setup() {
  pinMode(soundSensor, INPUT);
  pinMode(lamp, OUTPUT);

  digitalWrite(lamp, LOW);

  Serial.begin(9600);
}

void loop() {

  // Detect a sound
  if (digitalRead(soundSensor) == HIGH) {

    // First clap
    if (clapCount == 0) {
      clapCount = 1;
      firstClapTime = millis();

      Serial.println("First clap detected!");
    }

    // Second clap
    else if (clapCount == 1) {

      // Check if the second clap happened quickly enough
      if (millis() - firstClapTime <= clapWindow) {

        clapCount = 0;

        // Toggle lamp
        lampState = !lampState;
        digitalWrite(lamp, lampState);

        Serial.println("Double clap! Lamp toggled.");

        delay(300);
      }
    }

    // Prevent the same clap from being detected multiple times
    delay(100);
  }

  // Reset if the second clap didn't happen in time
  if (clapCount == 1 && millis() - firstClapTime > clapWindow) {
    clapCount = 0;

    Serial.println("Clap timeout.");
  }
}