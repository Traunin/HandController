#include <Servo.h>

#define MIN1 60
#define MAX1 120
#define MIN2 60
#define MAX2 120
#define MIN3 90
#define MAX3 160
#define LOG_DELAY 100
#define K 0.5

Servo servo1;
Servo servo2;
Servo servo3;
Servo tactile1;
Servo tactile2;
Servo tactile3;

long lastLog = 0;
long current = 0;

float baseline1;
int tactileStrength1 = 0;
float baseline2;
int tactileStrength2 = 0;
float baseline3;
int tactileStrength3 = 0;

void setup() {
  servo1.attach(3);
  servo2.attach(5);
  tactile1.attach(6);
  servo3.attach(9);
  tactile2.attach(10);
  tactile3.attach(11);
  pinMode(A7, INPUT);
  pinMode(A6, INPUT);
  pinMode(A5, INPUT);
  baseline1 = analogRead(A7);
  baseline2 = analogRead(A6);
  baseline3 = analogRead(A5);
  Serial.begin(9600);
}

void loop() {
    if (Serial.available()) {
        int number1 = Serial.parseInt();
        int number2 = Serial.parseInt();
        int number3 = Serial.parseInt();
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

        if (number3 >= MIN3 && number3 <= MAX3) {
//          Serial.print("Servo 3: ");
//          Serial.println(number3);
          servo3.write(number3);
        }
    }

    current = millis();
    if (current - lastLog > LOG_DELAY) {
      lastLog = current;
      updateTactile(analogRead(A7), tactileStrength1, baseline1, tactile1);
      updateTactile(analogRead(A6), tactileStrength2, baseline2, tactile2);
      updateTactile(analogRead(A5), tactileStrength3, baseline3, tactile3);
    }
}

int updateTactile(int inp, int &currentTactile, float &baseline, Servo &tactile) {
//  Serial.print(inp); Serial.print(" ");
  float diff = inp - baseline;
  baseline += diff * K;
  if (abs(diff) > 5) {
      currentTactile = min(max(currentTactile - (int) (diff / 2), 0), 90);
//      Serial.print(tactileStrength);
      tactile.write(currentTactile);
  }
//  Serial.println();
}
