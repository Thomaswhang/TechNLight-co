const int clapSensor = 2;
const int lamp = 13;

bool lampState = false;

int clapCount = 0;

unsigned long firstClapTime = 0;

const unsigned long clapWindow = 800;

void setup() {

  pinMode(clapSensor, INPUT_PULLUP);

  pinMode(lamp, OUTPUT);

  digitalWrite(lamp, LOW);

  Serial.begin(9600);
}

void loop() {

  // Button pressed = clap detected
  if (digitalRead(clapSensor) == LOW) {

    if (clapCount == 0) {

      clapCount = 1;
      firstClapTime = millis();

      Serial.println("First clap!");

    }

    else if (clapCount == 1) {

      if (millis() - firstClapTime <= clapWindow) {

        clapCount = 0;

        lampState = !lampState;

        digitalWrite(lamp, lampState);

        Serial.println("Double clap! Lamp toggled.");

        delay(300);
      }
    }

    // Wait until button is released
    while (digitalRead(clapSensor) == LOW) {
      delay(10);
    }
  }

  // Reset if second clap takes too long
  if (clapCount == 1 &&
      millis() - firstClapTime > clapWindow) {

    clapCount = 0;

    Serial.println("Too slow!");
  }
}