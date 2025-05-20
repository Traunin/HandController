#include <Hand.h>

// pin, open angle, closed angle
Finger* finger1;
Finger* finger2;
Finger* finger3;
Hand hand(3); // initialize a hand with 3 fingers

void setup() {
  // attaching bend sensors
  finger1 = new Finger(3, 60, 120);
  finger2 = new Finger(5, 60, 120);
  finger3 = new Finger(9, 90, 160);
  finger1 -> attachBend(A7);
  finger2 -> attachBend(A6);
  finger3 -> attachBend(A5);
  // attaching force sensors
  finger1 -> attachForce(A4);
  finger2 -> attachForce(A3);
  finger3 -> attachForce(A2);
  
  // joining fingers into a hand
  hand.setFinger(0, finger1);
  hand.setFinger(1, finger2);
  hand.setFinger(2, finger3);
  
  Serial.begin(115200);
}

void loop() {
  // every loop, call tick to update sensors
  hand.tick();
  // if there is data in serial, bend fingers
  // for 3 fingers: [0-255] [0-255] [0-255]
  hand.setFromSerial();
  // print tactile forces to serial
  hand.logForce();
}
