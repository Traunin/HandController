#include "Hand.h"
#include <Arduino.h>

Hand::Hand(int fingerCount) {
    count = fingerCount;
    fingers = new Finger*[count];
    for (int i = 0; i < count; i++) {
        fingers[i] = nullptr;
    }
}

Finger& Hand::getFinger(int index) {
    return *fingers[index];
}

void Hand::setFinger(int index, Finger* finger) {
    if (index >= 0 && index < count) {
        fingers[index] = finger;
    }
}

void Hand::setAll(unsigned char angle) {
    for (int i = 0; i < count; i++) {
        if (fingers[i]) {
            fingers[i]->setBend(angle);
        }
    }
}

void Hand::setFromSerial() {
    if (!Serial.available()) return;

    for (int i = 0; i < count; i++) {
        int angle = Serial.parseInt();
        fingers[i]->setBend(angle);
    }
}

void Hand::tick() {
    for (int i = 0; i < count; i++) {
        if (fingers[i]) {
            fingers[i]->tick();
        }
    }
}

void Hand::logBend() {
    for (int i = 0; i < count; i++) {
        if (fingers[i]) {
            int bend = fingers[i]->getBend();
            if (bend >= 0) {
                Serial.print(bend);
            }
            Serial.print("no bend sensor");
        } else {
            Serial.print("no finger");
        }
        if (i < count - 1) {
            Serial.print(" ");
        }
    }
    Serial.println();
}

void Hand::logForce() {
    for (int i = 0; i < count; i++) {
        if (fingers[i]) {
            int force = fingers[i]->getForce()
            if (force >= 0) {
                Serial.print(force);
            } else {
                Serial.print("no force sensor")
            }
        } else {
            Serial.print("no finger");
        }
        if (i < count - 1) {
            Serial.print(" ");
        }
    }
    Serial.println();
}
