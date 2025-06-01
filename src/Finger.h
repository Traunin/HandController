#pragma once
#include <Arduino.h>
#include <Servo.h>

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
    float forceK;
    float bendK;
    long current;
    long lastTick = 0;
    int tickDelay = 50;
    void updateForce(int newForce);
    void updateBend(int newBend);
    void updateTactile();

public:
    Finger(int servoPin, int min, int max);
    void attachBend(int pin, float k);
    void attachTactile(int pin);
    void attachForce(int pin, float k);
    void setTickDelay(int newTickDelay);

    void setBend(unsigned char angle);

    int getBend();
    int getForce();

    void tick();
};