#include <Finger.h>
#include <Arduino.h>

#define FINGER_SERVO 3
#define TACTILE_SERVO 6
#define MIN_ANGLE 60
#define MAX_ANGLE 120
#define BEND_PIN A7
#define FORCE_PIN A4

Finger finger(FINGER_SERVO, MIN_ANGLE, MAX_ANGLE);

void setup() {
  finger.attachBend(BEND_PIN);
  finger.attachTactile(TACTILE_SERVO);
  finger.attachForce(FORCE_PIN);
  Serial.begin(9600);
}

void loop() {
    finger.tick();
    Serial.print(finger.getBend()); Serial.print(" "); Serial.println(finger.getForce());
}
