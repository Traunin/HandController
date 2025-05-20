#include <Hand.h>

Finger* finger1;
Finger* finger2;
Finger* finger3;
Hand hand(3);

void setup() {
  finger1 = new Finger(3, 60, 120);
  finger2 = new Finger(5, 60, 120);
  finger3 = new Finger(9, 90, 160);
  finger1.attachBend(A7);
  finger2.attachBend(A6);
  finger3.attachBend(A5);
  finger1.attachForce(A4);
  finger2.attachForce(A3);
  finger3.attachForce(A2);
  
  hand.setFinger(0, finger1);
  hand.setFinger(1, finger2);
  hand.setFinger(2, finger3);
  
  Serial.begin(115200);
}

void loop() {
  hand.tick();
  hand.setFromSerial();

  hand.logForce();
}