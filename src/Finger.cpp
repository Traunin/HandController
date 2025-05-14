#include <Arduino.h>
#include <Finger.h>

Finger::Finger(int servoPin, int min, int max) {
    finger.attach(servoPin);
    maxBend = max;
    minBend = min;
}

void Finger::attachBend(int pin) {
    hasBend = true;
    bendPin = pin;
    pinMode(pin, INPUT);
    force = analogRead(pin);
}

void Finger::attachForce(int pin) {
    hasForce = true;
    forcePin = pin;
    pinMode(pin, INPUT);
    force = analogRead(pin);
}

void Finger::attachTactile(int pin) {
    hasTactile = true;
    tactile.attach(pin);
}

void Finger::setBend(unsigned char angle) {
    int mapped = map(angle, 0, 255, minBend, maxBend);
    finger.write(mapped);
}

int Finger::getBend() {
    if (hasBend) {
        return bend;
    }
    return -1;
}

int Finger::getForce() {
    if (hasForce) {
        return force;
    }
    return -1;
}

void Finger::tick() {
    current = millis();
    if (current - lastTick > LOG_DELAY) {
        lastTick = current;
        if (hasForce) {
            updateForce(analogRead(forcePin));
        }
        if (hasBend) {
            updateBend(analogRead(bendPin));
        }
        if (hasTactile) {
            updateTactile();
        }
    }
}

void Finger::updateForce(int newForce) {
    force += (int) ((newForce - force) * FORCE_K);
}

void Finger::updateBend(int newBend) {
    bend += (int) ((newBend - bend) * BEND_K);
}

void Finger::updateTactile() {
    int diff = lastForce - force;
    if (abs(diff) > 5) {
        tactileForce = min(max(tactileForce - (int) (diff / 2), 0), 90);
        tactile.write(tactileForce);
    }
    lastForce = force;
}