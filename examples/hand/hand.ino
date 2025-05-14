#include <Hand.h>

Finger finger1(3, 60, 120);
Finger finger2(5, 60, 120);
Finger finger3(9, 90, 160);
Hand hand(3);


void setup() {
  finger1.attachBend(A7);
  finger2.attachBend(A6);
  finger3.attachBend(A5);
  finger1.attachForce(A4);
  finger2.attachForce(A3);
  finger3.attachForce(A2);
  
  hand.setFinger(0, &finger1);
  hand.setFinger(1, &finger2);
  hand.setFinger(2, &finger3);
  
  Serial.begin(115200);
}

void loop() {
  hand.tick();
  hand.setFromSerial();

  hand.logForce();
}