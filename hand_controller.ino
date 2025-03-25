#include <Servo.h>

#define MIN1 70
#define MAX1 150
#define MIN2 40
#define MAX2 110

Servo servo1;
Servo servo2;

void setup() {
  servo1.attach(3);
  servo2.attach(5);
  Serial.begin(9600);
}

void loop() {
    if (Serial.available()) {
        int number1 = Serial.parseInt();
        int number2 = Serial.parseInt();
//        Serial.println("Read");
        if (number1 >= MIN1 && number1 <= MAX1) {
//          Serial.print("Servo 1: ");
//          Serial.println(number1);
          servo1.write(number1);
        }

        if (number2 >= MIN2 && number2 <= MAX2) {
//          Serial.print("Servo 2: ");
//          Serial.println(number2);
          servo2.write(number2);
        }
    }
}
