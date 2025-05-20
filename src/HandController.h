#pragma once
#include <Arduino.h>
#include "Finger.h"

class Hand {
private:
    Finger** fingers;
    int count;

public:
    Hand(int fingerCount);

    Finger& getFinger(int index);
    void setFinger(int index, Finger* finger);

    void tick();

    void setAll(unsigned char angle);
    void setFromSerial();
    void logForce();
    void logBend();
};
