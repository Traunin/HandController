#include <HandController.h>
#include <Arduino.h>

#define FINGER_SERVO 3
#define TACTILE_SERVO 6
#define MIN_ANGLE 60
#define MAX_ANGLE 120
#define BEND_PIN A7
#define FORCE_PIN A4

// initializing a finger
Finger* finger;


void setup() {
  // attach finger servo
  finger = new Finger(FINGER_SERVO, MIN_ANGLE, MAX_ANGLE);
  // bend sensor, pin and exponential smoothing coeff
  finger->attachBend(BEND_PIN, 0.9);
  // tactile servo
  finger->attachTactile(TACTILE_SERVO);
  // force sensor, pin and exponential smoothing coeff
  finger->attachForce(FORCE_PIN, 0.9);
  Serial.begin(9600);
}

void loop() {
  // call tick to read sensor values  
  finger->tick();

  // print sensor values to serial
  Serial.print(finger->getBend()); 
  Serial.print(" ");
  Serial.println(finger->getForce());
}
