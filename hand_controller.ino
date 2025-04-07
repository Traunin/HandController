#include <Servo.h>

#define MIN1 60
#define MAX1 120
#define MIN2 60
#define MAX2 120
#define LOG_DELAY 100
#define IDLE_RESISTANCE 775

Servo servo1;
Servo servo2;
Servo tactile;

long last_log = 0;
long current = 0;

void setup() {
  servo1.attach(3);
  servo2.attach(5);
  tactile.attach(6);
  pinMode(A7, INPUT);
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

    current = millis();
    if (current - last_log > LOG_DELAY) {
      last_log = millis();
      updateTactile(analogRead(A7));
    }
}

void updateTactile(int inp) {
  Serial.println(inp);
  float diff = ((float) abs(inp - IDLE_RESISTANCE)) / 50.0;
  int angle = min(90, max(0, (int) (diff * 90)));
//  Serial.println(angle);
  tactile.write(angle);
}
