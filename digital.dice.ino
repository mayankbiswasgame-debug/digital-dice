// -------- PIN DEFINITIONS --------
#define TRIG_PIN 5
#define ECHO_PIN 18

int leds[5] = {13, 12, 14, 27, 26};

// -------- VARIABLES --------
bool rolled = false;

// -------- SETUP --------
void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  for (int i = 0; i < 5; i++) {
    pinMode(leds[i], OUTPUT);
  }

  randomSeed(micros());
}

// -------- DISTANCE FUNCTION --------
long getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000); // timeout for stability
  return duration * 0.034 / 2;
}

// -------- MAIN LOOP --------
void loop() {
  long distance = getDistance();

  // Trigger when hand is very close (BONUS TIP APPLIED)
  if (distance > 0 && distance < 7 && !rolled) {
    rolled = true;

    rollAnimation();

    int number = random(1, 7);
    displayDice(number);
  }

  // Reset when hand removed
  if (distance > 12) {
    rolled = false;
  }
}

// -------- ROLL ANIMATION --------
void rollAnimation() {
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 5; j++) {
      digitalWrite(leds[j], random(0, 2));
    }
    delay(80);
  }
}

// -------- DISPLAY DICE --------
void displayDice(int num) {

  // Turn OFF all LEDs
  for (int i = 0; i < 5; i++) {
    digitalWrite(leds[i], LOW);
  }

  switch (num) {

    case 1:
      digitalWrite(leds[2], HIGH);
      break;

    case 2:
      digitalWrite(leds[0], HIGH);
      digitalWrite(leds[4], HIGH);
      break;

    case 3:
      digitalWrite(leds[0], HIGH);
      digitalWrite(leds[2], HIGH);
      digitalWrite(leds[4], HIGH);
      break;

    case 4:
      digitalWrite(leds[0], HIGH);
      digitalWrite(leds[1], HIGH);
      digitalWrite(leds[3], HIGH);
      digitalWrite(leds[4], HIGH);
      break;

    case 5:
      for (int i = 0; i < 5; i++) {
        digitalWrite(leds[i], HIGH);
      }
      break;

    case 6:
      // Blink all LEDs
      for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 5; j++) {
          digitalWrite(leds[j], HIGH);
        }
        delay(120);

        for (int j = 0; j < 5; j++) {
          digitalWrite(leds[j], LOW);
        }
        delay(120);
      }
      break;
  }
}