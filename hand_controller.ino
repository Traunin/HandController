#include <Servo.h>


#define MIN 90
#define MAX 180
Servo servo;
int incomingByte = 0;


void setup() {
  // put your setup code here, to run once:
  servo.attach(3);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
//  servo.write(MIN);
//  delay(1000);
//  servo.write(MAX);
//  delay(1000);

    if (Serial.available()) {
        int number = Serial.parseInt(); // Read an integer
        if (number >= MIN and number <= MAX) {
          Serial.print("Received number: ");
          Serial.println(number);
          servo.write(number);
        }
    }
}
