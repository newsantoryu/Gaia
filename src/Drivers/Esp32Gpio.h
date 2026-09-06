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

    void setPwm(
        uint8_t percentage
    ) override {

        if (percentage > 100) {
            percentage = 100;
        }

        const uint8_t duty = map(
            percentage,
            0,
            100,
            0,
            255
        );

        analogWrite(
            pin_,
            duty
        );
    }

private:

    uint8_t pin_;
};
