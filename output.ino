#define USE_ARDUINO_INTERRUPTS true
#include <PulseSensorPlayground.h>

const int buzz = 9;
const int green = 8;
const int red = 7;
String command = "";

void setup() {
  Serial.begin(9600);
  pinMode(green, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(buzz, OUTPUT);
}

void loop() {
  // if serial communication
  if (Serial.available()) {
    command = Serial.read();
    Serial.println(command);
    // if 1 is sent over from the readings as in a lie is detected, set off the buzzer and turn on the red led
    if (command.toInt() == 1) {
      tone(buzz, 9000, 500);
      digitalWrite(red, HIGH);
      digitalWrite(green, LOW);
    } else {
      // the other board sent over a zero so no lie was detected, light up the green led, silence the buzzer and turn off the red led
      noTone(buzz);
      digitalWrite(green, HIGH);
      digitalWrite(red, LOW);
    }
  }
}
