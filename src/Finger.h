#pragma once
#include <Arduino.h>
#include <Servo.h>

#define LOG_DELAY 50
#define FORCE_K 0.5
#define BEND_K 0.5

class Finger {
private:
    Servo finger;
    Servo tactile;
    int bendPin;
    int forcePin;
    bool hasBend = false;
    bool hasForce = false;
    bool hasTactile = false;
    int maxBend;
    int minBend;
    int bend;
    int force;
    int lastForce;
    int tactileForce;
    long current;
    long lastTick;
    void updateForce(int newForce);
    void updateBend(int newBend);
    void updateTactile();

public:
    Finger(int servoPin, int min, int max);
    void attachBend(int pin);
    void attachTactile(int pin);
    void attachForce(int pin);

    void setBend(unsigned char angle);

    int getBend();
    int getForce();

    void tick();
};