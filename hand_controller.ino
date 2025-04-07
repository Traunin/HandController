#include <Servo.h>

#define MIN1 60
#define MAX1 120
#define MIN2 60
#define MAX2 120
#define LOG_DELAY 100
#define K 0.5

Servo servo1;
Servo servo2;
Servo tactile;

long lastLog = 0;
long current = 0;

float baseline;
int tactileStrength = 0;

void setup() {
  servo1.attach(3);
  servo2.attach(5);
  tactile.attach(6);
  pinMode(A7, INPUT);
  baseline = analogRead(A7);
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
    if (current - lastLog > LOG_DELAY) {
      lastLog = current;
      updateTactile(analogRead(A7));
    }
}

void updateTactile(int inp) {
  Serial.print(inp); Serial.print(" ");
  float diff = inp - baseline;
  baseline += diff * K;
  if (abs(diff) > 5) {
      tactileStrength = min(max(tactileStrength - (int) (diff / 2), 0), 90);
      Serial.print(tactileStrength);
      tactile.write(tactileStrength);
  }
  Serial.println();
}
