#pragma once

#include <Arduino.h>
#include "HAL/IGpio.h"

class Esp32Gpio final : public IGpio {

public:

    explicit Esp32Gpio(uint8_t pin)
        : pin_(pin) {}

    void begin() override {
        pinMode(pin_, OUTPUT);
        setLow();
    }

    void setHigh() override {
        digitalWrite(pin_, HIGH);
    }

    void setLow() override {
        digitalWrite(pin_, LOW);
    }

    bool read() const override {
        return digitalRead(pin_) == HIGH;
    }

private:

    uint8_t pin_;
};